/* ----------------------------------------------------------------------
 * Project:      PULP DSP Library
 * Title:        plp_dwt_q8_parallel.c
 * Description:  8bit Fixed-point Discret Wavelet Transform
 *
 * $Date:        10. Juli 2021
 * $Revision:    V1
 *
 * Target Processor: PULP cores with "F" support (wolfe)
 * -------------------------------------------------------------------- */
/*
 * Copyright (C) 2021 ETH Zurich and University of Bologna. All rights reserved.
 *
 * Author: Jakub Mandula, ETH Zurich
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "plp_math.h"
#include "plp_dwt_common.h"

/**
  @ingroup groupTransforms
 */

/**
  @defgroup dwt  DWT transforms
  This module contains the code to perform DWT transforms.


 */

/**
   @addtogroup dwt
   @{
*/

/**
   @brief  8bit Parallel Fixed-point DWT on real input data for XPULPV2 extension.
   @param[in]   pSrc     points to the input buffer (q8)
   @param[in]   length   length of input buffer
   @param[in]   wavelet  wavelet structure for calculating DWT
   @param[in]   mode     boundary extension mode
   @param[in]   nPE      Number of cores to use

   @param[out]  pDstA    points to ouput buffer with Approximate coefficients
   @param[out]  pDstD    points to ouput buffer with Detailed coefficients
   @return      none
*/
void plp_dwt_q8_parallel(const int8_t *__restrict__ pSrc,
                 uint32_t length,
                 const plp_dwt_wavelet_q8 wavelet,
                 plp_dwt_extension_mode mode,
                 uint32_t nPE,
                 int8_t *__restrict__ pDstA,
                 int8_t *__restrict__ pDstD) {

   if((mode == PLP_DWT_MODE_ANTIREFLECT || mode == PLP_DWT_MODE_REFLECT) && length <= 1){
      printf("F Cannot run [anti]reflect mode on length 1 signal.\n");
      return;
   }

   int8_t *dec_hi_l1;
   int8_t *dec_lo_l1;
   plp_dwt_wavelet_q8 temp_wavelet;
    
   if (hal_cluster_id() == ARCHI_FC_CID) {
      printf("parallel processing supported only for cluster side\n");
      return;
   } else {
      plp_dwt_instance_q8 args = {
         .pSrc = pSrc,
         .length = length,
         .wavelet = wavelet,
         .mode = mode,
         .nPE = nPE,
         .pDstA = pDstA,
         .pDstD = pDstD
      };
      
      switch(wavelet.type) {
      case PLP_DWT_WAVELET_HAAR:
      case PLP_DWT_WAVELET_DB1:
         hal_cl_team_fork(nPE, plp_dwt_haar_q8p_xpulpv2, (void *)&args);
         break;
      default:

         dec_hi_l1 = hal_cl_l1_malloc(sizeof(int8_t) * (wavelet.length));
         dec_lo_l1 = hal_cl_l1_malloc(sizeof(int8_t) * (wavelet.length));

         copy_coefs_q8(dec_hi_l1, dec_lo_l1, wavelet);
         temp_wavelet = (plp_dwt_wavelet_q8){
            .length = wavelet.length,
            .type = wavelet.type,
            .dec_hi = dec_hi_l1,
            .dec_lo = dec_lo_l1
         };
         args.wavelet = temp_wavelet;

         hal_cl_team_fork(nPE, plp_dwt_q8p_xpulpv2, (void *)&args);

         hal_cl_l1_free(dec_hi_l1, sizeof(int8_t) * (wavelet.length));
         hal_cl_l1_free(dec_lo_l1, sizeof(int8_t) * (wavelet.length));
         break;
      }
   }


}

/**
   @} end of DWT group
*/
