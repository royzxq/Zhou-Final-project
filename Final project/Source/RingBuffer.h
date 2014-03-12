#if !defined(__RingBuffer_hdr__)
#define __RingBuffer_hdr__

#include <cassert>
#include"Util.h"
template <class T>
class CRingBuffer
{
public:
    CRingBuffer (int iBufferLengthInSamples) :
    m_iBuffLength(iBufferLengthInSamples),
    m_iReadIdx(0),
    m_iWriteIdx(0),
    frac(0),
    n(8),
    m_ptBuff(0)
    
    {
        assert(iBufferLengthInSamples > 0);
        
        m_ptBuff        = new T [m_iBuffLength];
        langrang    = new T[n];
        x_coordinate = new int[n];
        for (int i = 0 ; i < n ; i++) {
            x_coordinate[i] = i ;
        }
        resetInstance();
    };
    
    virtual ~CRingBuffer ()
    {
        delete m_ptBuff;
        delete langrang;
        delete x_coordinate;
        langrang = 0;
        m_ptBuff    = 0;
    };
    
    /*! add a new value of type T to write index and increment write index
     \param T tNewValue the new value
     \return void
     */
    void putPostInc (T tNewValue)
    {
        m_ptBuff[m_iWriteIdx]   = tNewValue;
        incIdx(m_iWriteIdx);
    };
    
    /*! add a new value of type T to write index
     \param T tNewValue the new value
     \return void
     */
    void put(T tNewValue)
    {
        m_ptBuff[m_iWriteIdx]   = tNewValue;
    }
    
    /*! return the value at the current read index and increment the read pointer
     \return float the value from the read index
     */
    T getPostInc ()
    {
        int iCurrIdx    = m_iReadIdx;
        incIdx(m_iReadIdx);
        return m_ptBuff[iCurrIdx];
    };
    /*
     get the linear interpolation value of the ringbuffer
     */
    T getInterpolationPostInc()
    {
        /*
        for (int i = n ; i >= 0 ; i--) {
            langrang[n-i] = getPastSamples(i);
        }
        T result = lagrangeInterp(x_coordinate,langrang,n,n+frac);
         */
        T result  = this->getPostInc()*(1-frac)+this->getPostInc()*(frac) ;
        return result;
    }
    /*! return the value at the current read index
     \return float the value from the read index
     */
    T get () const
    {
        return m_ptBuff[m_iReadIdx];
    }
    
    /*! set buffer content and indices to 0
     \return void
     */
    void resetInstance ()
    {
        CUtil::setZero(m_ptBuff, m_iBuffLength);
        m_iReadIdx  = 0;
        m_iWriteIdx = 0;
        frac = 0 ;
    }
    
    /*! return the current index for writing/put
     \return int
     */
    int getWriteIdx () const
    {
        return m_iWriteIdx;
    }
    
    /*! move the write index to a new position
     \param int iNewWriteIdx: new position
     \return void
     */
    void setWriteIdx (int iNewWriteIdx)
    {
        incIdx(m_iWriteIdx, iNewWriteIdx - m_iWriteIdx);
    }
    
    /*! return the current index for reading/get
     \return int
     */
    int getReadIdx () const
    {
        return m_iReadIdx;
    }
    float getFloatReadIdx () const
    {
        return (m_iReadIdx+frac);
    }
    /*! move the read index to a new position
     \param int iNewReadIdx: new position
     \return void
     */
    void setReadIdx (int iNewReadIdx)
    {
        incIdx(m_iReadIdx, iNewReadIdx - m_iReadIdx);
    }
    
    // set the ReadIdx with float number for linear interpolation
    void setDelayIdx(float iNewReadIdx)
    {
        
        int i = static_cast<int>(iNewReadIdx);
        int WriteIdx = getWriteIdx();
        if (i == iNewReadIdx) {
            frac = 0 ;
            setReadIdx(WriteIdx - i);
            return;
        }
        else{
            frac =  (iNewReadIdx - i);
            setReadIdx(WriteIdx - i);
        }
    }
    
    /*! returns the number of values currently buffered (note: 0 could also mean the buffer is full!)
     \return int
     */
    int getNumValuesInBuffer () const
    {
        return (m_iWriteIdx - m_iReadIdx + m_iBuffLength)%m_iBuffLength;
    }
    
private:
    T getPastSamples(int nPastSample)
    {
        int k = m_iReadIdx - nPastSample;
        if (k < 0) //make sure we don't flow back off the array
            k += m_iBuffLength;
        return m_ptBuff[k];
    }
    
    T lagrangeInterp(int * x, T* y, int n, float xbar)
    {
        int i,j;
        T fx=0.0;
        float l=1.0;
        for (i=0; i<n; i++)
        {
            l=1.0;
            for (j=0; j<n; j++)
            {
                if (j != i)
                    l *= (xbar-x[j])/(x[i]-x[j]);
            }
            fx += l*y[i];
            
        }
        return (fx);
    }

    void incIdx (int &iIdx, int iOffset = 1)
    {
        while ((iIdx + iOffset) < 0)
        {
            // avoid negative buffer indices
            iOffset += m_iBuffLength;
        }
        iIdx    = (iIdx + iOffset) % m_iBuffLength;
    };
    
    int m_iBuffLength,              //!< length of the internal buffer
    m_iReadIdx,                 //!< current read index
    m_iWriteIdx;                //!< current write index
    float frac;                // the fraction of interpolation
    int n;
    T * langrang;
    int * x_coordinate;
    T   *m_ptBuff;                  //!< data buffer
};
#endif // __RingBuffer_hdr__
