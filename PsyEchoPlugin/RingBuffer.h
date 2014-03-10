#if !defined(__RingBuffer_hdr__)
#define __RingBuffer_hdr__

#include <cassert>
#include<cmath>
#include"Util.h"
#include"PluginTools.h"



template <class T>

class CRingBuffer
{
public:
    CRingBuffer (int iBufferLengthInSamples) :
        m_iBuffLength(iBufferLengthInSamples),
        m_iReadIdx(0),
        frac(0),
        m_iWriteIdx(0),
        m_ptBuff(0)
    
    {
        assert(iBufferLengthInSamples > 0);

        m_ptBuff        = new T [m_iBuffLength];
        x_coordinate    = new int[m_iBuffLength];
        for (int i = 0 ; i < m_iBuffLength; i++) {
            x_coordinate[i] = i;
        }
        resetInstance();
    };

    virtual ~CRingBuffer ()
    {
        delete [] m_ptBuff;
        m_ptBuff    = 0;
    };

    /*! add a new value of type T to write index and increment write index
    \param T tNewValue the new value
    \return void
    */
    void putPostInc (T tNewValue)
    {
        put(tNewValue);
        incIdx(m_iWriteIdx);
    };
    /*! add new values of type T to write index and increment write index
    \param const T * ptNewBuff: new values
    \param int iLength: number of values
    \return void
    */
    void putPostInc (const T* ptNewBuff, int iLength)
    {
        put(ptNewBuff, iLength);
        incIdx(m_iWriteIdx, iLength);
    }
    /*! add a new value of type T to write index
    \param T tNewValue the new value
    \return void
    */
    void put(T tNewValue)
    {
        m_ptBuff[m_iWriteIdx]   = tNewValue;
    }
    /*! add new values of type T to write index
    \param const T * ptNewBuff: new values
    \param int iLength: number of values
    \return void
    */
//    void put(const T* ptNewBuff, int iLength)
//    {
//        assert(iLength <= m_iBuffLength && iLength >= 0);
//
//        // copy two parts: to the end of buffer and after wrap around
//        int iNumValues2End      = std::min(iLength,m_iBuffLength - m_iWriteIdx);
//
//        memcpy (&m_ptBuff[m_iWriteIdx], ptNewBuff, sizeof(T)*iNumValues2End);
//        if ((iLength - iNumValues2End)>0)
//            memcpy (m_ptBuff, &ptNewBuff[iNumValues2End], sizeof(T)*(iLength - iNumValues2End));
//    }
    
    /*! return the value at the current read index and increment the read pointer
    \return float the value from the read index
    */
    T getPostInc ()
    {
        T tValue = get();
        incIdx(m_iReadIdx);
        return tValue;
    };
    /*! return the values starting at the current read index and increment the read pointer
    \param T * ptBuff: pointer to where the values will be written
    \param int iLength: number of values
    \return void
    */
    void getPostInc (T* ptBuff, int iLength)
    {
        get(ptBuff, iLength);
        incIdx(m_iReadIdx, iLength);
    }

    /*! return the value at the current read index
    \param float fOffset: read at offset from read index
    \return float the value from the read index
    */
    
    // the fOffset is the actual delay time in sample if it is not equal to 0
    T get (float fOffset = 0) const
    
    {
        if (fOffset == 0)
            return m_ptBuff[m_iReadIdx];
        else
        {
            
            assert(fabs(fOffset) <= m_iBuffLength);
            fOffset = this->getWriteIdx() - fOffset;
            if (fOffset<0) {
                fOffset += m_iBuffLength;
            }
            if (fOffset>m_iBuffLength) {
                fOffset -= m_iBuffLength;
            }
            // compute fraction for lagrange interpolation
            return lagrangeInterp<T>(x_coordinate,m_ptBuff,8,fOffset);
            

        }
    }
    /*! return the values starting at the current read index
    \param T * ptBuffpointer to where the values will be written
    \param int iLength: number of values
    \return void
    */
//    void get (T* ptBuff, int iLength) const
//    {
//        assert(iLength <= m_iBuffLength && iLength >= 0);
//
//        // copy two parts: to the end of buffer and after wrap around
//        int iNumValues2End      = std::min(iLength, m_iBuffLength - m_iReadIdx);
//
//        memcpy (ptBuff, &m_ptBuff[m_iReadIdx], sizeof(T)*iNumValues2End);
//        if ((iLength - iNumValues2End)>0)
//            memcpy (&ptBuff[iNumValues2End], m_ptBuff, sizeof(T)*(iLength - iNumValues2End));
//    }
//    T getInterpolationPostInc()
//    {
//        T result  = this->getPostInc()*(1-frac)+this->getPostInc()*(frac) ;
//        return result;
//    }
    /*! set buffer content and indices to 0
    \return void
    */
    void resetInstance ()
    {
        CUtil::setZero(m_ptBuff, m_iBuffLength);
        m_iReadIdx = 0;

        m_iWriteIdx = 0;
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

    /*! move the read index to a new position
    \param int iNewReadIdx: new position
    \return void
    */
    void setReadIdx (int iNewReadIdx)
    {
        incIdx(m_iReadIdx, iNewReadIdx - m_iReadIdx);
    }

    /*! returns the number of values currently buffered (note: 0 could also mean the buffer is full!)
    \return int
    */
    int getNumValuesInBuffer () const
    {
        return (m_iWriteIdx - m_iReadIdx + m_iBuffLength)%m_iBuffLength;
    }
  
    
    /*! returns the length of the internal buffer
    \return int
    */
    int getLength () const
    {
        return m_iBuffLength;
    }
private:
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
    
    float frac;
    T   *m_ptBuff;                  //!< data buffer
    int * x_coordinate;
};
#endif // __RingBuffer_hdr__
