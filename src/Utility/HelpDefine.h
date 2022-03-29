///////////////////////////////////////////////////////////////
//
// HelpDefine.h
//
//   General defines, parameter setting, etc.
//
// by Yingjie Cheng and Peng SONG
//
// 06/Dec/2020
//
//
///////////////////////////////////////////////////////////////


#ifndef _HELP_DEFINE_H
#define _HELP_DEFINE_H


#include <cmath>



///=========================================================================================///
///                                     Math Related
///=========================================================================================///

// Max and min integer/float
#define  MIN_INT                   -10000000
#define  MAX_INT                    10000000
#define  MIN_FLOAT                 -10000000.0
#define  MAX_FLOAT                  10000000.0

#define FLOAT_ERROR_SMALL           0.0000001
#define FLOAT_ERROR_LARGE           0.0001
//#define double_ERROR_SMALL          0.000000001
//#define double_ERROR_LARGE          0.0000001

#define _ToRadian(X)		((X)/180.0*M_PI)
#define _ToDegree(X)		((X)*180.0/M_PI)

#ifndef _EPSILON
#define _EPSILON		1e-7
#endif

#ifndef _MAX
#define _MAX(a,b)		( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef _MIN
#define _MIN(a,b)		( ((a) < (b)) ? (a) : (b) )
#endif

#ifndef _IN_BETWEEN
#define _IN_BETWEEN(v,a,b)	( ((v) >= (a)) && ((v) <= (b)) )
#endif

#ifndef M_PI
#define M_PI			3.1415926535897932384626433832795
#endif


#endif
