///////////////////////////////////////////////////////////////
//
// Controls.h
//
//   Defined Variables to Control the Program
//
// by Song Peng ( songpeng@ustc.edu.cn )
// 
// 11/May/2015
//
///////////////////////////////////////////////////////////////


#ifndef _CONTROLS
#define _CONTROLS


//**************************************************************************************//
//                                Control Parameters 
//**************************************************************************************//

// For Debug 
#define DEBUG_SAVE_CONF      1   
//#define DEBUG_COLLISION      1
//#define DEBUG_SAVE_STATES    1




//**************************************************************************************//
//                                Variables for Debug 
//**************************************************************************************//



//**************************************************************************************//
//                              Variables for Application 
//**************************************************************************************//

#define QUAD_INTERSECT              0
#define QUAD_SEPARATE               1
#define QUAD_CONTACT                2

#define GAP_TYPE_ZERO               0
#define GAP_TYPE_ONE                1
#define GAP_TYPE_TWO                2

#define LARGE_GAP_SIZE_THRES        10   // For general case
//#define LARGE_GAP_SIZE_THRES      12   // For Cube_5x5x5
//#define LARGE_GAP_SIZE_THRES      8    // For Cube_4x4x4
//#define LARGE_GAP_SIZE_THRES      3    // For general case




//**************************************************************************************//
//                              Default Variable Values
//**************************************************************************************//



#endif
