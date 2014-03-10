//
//  PluginTools.h
//  PSYeCHO
//
//  Created by Raja Raman on 3/8/14.
//
//

#ifndef _PluginTools_h
#define _PluginTools_h

#define _MATH_DEFINES_DEFINED
#include <math.h>

// pi
#define  pi 3.1415926535897932384626433832795

// max between two values
#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
// min between two values
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

// Gain/Decible conversion control
inline float gainTOdB(float gain)
{
    return (20.0f * log10(gain));
}

inline float dBTOgain(float dB)
{
    return (powf(10, dB/ 20.0f));
}

/*
 Function:	lagrpol() implements n-order Lagrange Interpolation
 
 Inputs:	float* x	Pointer to an array containing the x-coordinates of the input values
 float* y	Pointer to an array containing the y-coordinates of the input values
 int n		The order of the interpolator, this is also the length of the x,y input arrays
 float xbar	The x-coorinates whose y-value we want to interpolate
 
 Returns		The interpolated value y at xbar. xbar ideally is between the middle two values in the input array,
 but can be anywhere within the limits, which is needed for interpolating the first few or last few samples
 in a table with a fixed size.
 */

template <class T>
inline T lagrangeInterp(int* x, T* y, int n, float xbar)
{
    T fx = 0.0;
    T l=1.0;
    for (int i=0; i<n; i++)
    {
        l=1.0;
        for (int j=0; j<n; j++)
		{
            if (j != i)
                l *= (xbar-x[j])/(x[i]-x[j]);
		}
		fx += l*y[i];
    }
    return (fx);
}


#endif
