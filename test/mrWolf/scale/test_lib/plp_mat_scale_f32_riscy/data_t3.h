#ifndef __PULP_DSP_TEST__DATA_T3_H__
#define __PULP_DSP_TEST__DATA_T3_H__

// include the common header
#include "common.h"

float* t3__pSrc;
RT_L2_DATA uint32_t t3__pSrc__l2__int[26] = {
    0x3f70cb17, 0x3f2c8edf, 0xbcf2f63d, 0xbf19288d, 0xbecff209, 0xbf18a987, 0xbeaa2da5, 0x3f05c5df,
    0xbf04c305, 0xbebb7715, 0xbf3f2224, 0xbf69983a, 0x3f36b0d5, 0x3dacc181, 0x3e0587ed, 0x3e5da639,
    0x3f51bca6, 0xbf0d6415, 0xbe90a4a1, 0xbf28d4a8, 0xbdbab6d5, 0x3f242200, 0x3c519ccc, 0xbf398233,
    0xbea1f05d, 0xbe826cb1
};

float* t3__pSrc__l2 = (float*)((void*)t3__pSrc__l2__int);
                
__u2f t3__scaleFactor = {.u = 0xbd73c58eU};

float* t3__pDst;
RT_L2_DATA uint32_t t3__pDst__l2__int[26] = {
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};

float* t3__pDst__l2 = (float*)((void*)t3__pDst__l2__int);
                
uint32_t t3__blockSize = 26;

RT_L2_DATA uint32_t t3__pDst__reference__int[26] = {
    0xbd654a99, 0xbd2450c7, 0x3ae75b3a, 0x3d11d7af, 0x3cc60337, 0x3d115eba, 0x3ca20ca7, 0xbcfec41c,
    0x3cfcd723, 0x3cb282b4, 0x3d3600e7, 0x3d5e6fc3, 0xbd2df6d6, 0xbba480fe, 0xbbfe4e23, 0xbc530fd4,
    0xbd47b7ec, 0x3d06a31c, 0x3c89bbe4, 0x3d20c425, 0x3bb1cba2, 0xbd1c4aef, 0xba479998, 0x3d30a5bf,
    0x3c9a3420, 0x3c7863a4
};

float* t3__pDst__reference = (float*)((void*)t3__pDst__reference__int);


#endif//__PULP_DSP_TEST__DATA_T3_H__