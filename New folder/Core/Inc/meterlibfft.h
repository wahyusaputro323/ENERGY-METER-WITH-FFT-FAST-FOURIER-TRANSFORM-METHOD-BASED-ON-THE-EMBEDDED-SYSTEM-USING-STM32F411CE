/*
 * meterlibfft.h
 *
 *  Created on: Jul 11, 2021
 *      Author: wahyu utoro saputro
 */

#ifndef INC_METERLIBFFT_H_
#define INC_METERLIBFFT_H_

#ifdef __cplusplus
 extern "C"
 {
#endif

#include "main.h"

// FFT Calculation and Signal-Conditioning Processing Function
void METERLIBFFT1PH_CalcMain (tMETERLIBFFT1PH_DATA *p)

// Reactive Energy Calculation Function
long METERLIBFFT1PH_CalcVarHours (tMETERLIBFFT1PH_DATA *p, unsigned long *varh_i, unsigned long *varh_e, unsigned long frequency)

// Active Energy Calculation Function
long METERLIBFFT1PH_CalcWattHours (tMETERLIBFFT1PH_DATA *p, unsigned long *wh_i, unsigned long *wh_e, unsigned long frequency)Active Energy Calculation Functio)

// Non-Billing (U,I,P,Q,PF,THD)
void METERLIBFFT1PH_GetAvrgValues (tMETERLIBFFT1PH_DATA *p, double *urms, double *irms, double *w, double *var, double *va, double *pf, double *thd_u, double *thd_i)

// Non-Billing (U,I,P,Q,PF,THD) Instantaneous Variables Reading Function
METERLIBFFT1PH_GetInstValues (tMETERLIBFFT1PH_DATA *p, double *urms, double *irms, double *w, double *var, double *va, double *pf, double *thd_u, double *thd_i)

// Harmonic Magnitude Calculation Function
void METERLIBFFT1PH_GetMagnitudes (tMETERLIBFFT1PH_DATA *p, unsigned long magn_fft)

// Harmonnic Phase Shifts Calculation Function
void METERLIBFFT1PH_GetPhases (tMETERLIBFFT1PH_DATA *p, unsigned long ph_fft)

// Auxiliary Buffers Initialization Function
void METERLIBFFT1PH_InitAuxBuff (tMETERLIBFFT1PH_DATA *p, Frac24 *mag_u, Frac24 *mag_i, long *ph_u, long *ph_i)

// Main Buffer Initialization Function
void METERLIBFFT1PH_InitMainBuff (tMETERLIBFFT1PH_DATA *p, Frac24 *u_re, Frac24 *i_re, Frac24 *u_im, Frac24 *i_im, long *shift)

// Parameters Initialization Function
long METERLIBFFT1PH_InitParam (tMETERLIBFFT1PH_DATA *p, unsigned long samples, unsigned long sensor, unsigned long kwh_cnt, unsigned long kvarh_cnt, unsigned long en_res)

// Interpolation Function
long METERLIBFFT1PH_Interpolation (tMETERLIBFFT1PH_DATA *p, unsigned long u_ord, unsigned long i_ord, unsigned long samples_inp)

// Set Calibration	Coeficient Function
long METERLIBFFT1PH_SetCalibCoeff (tMETERLIBFFT1PH_DATA *p, double u_max, double i_max, Frac24 *i_offs, double p_offs, double q_offs)

#ifdef __cplusplus
}
#endif

#endif /* INC_METERLIBFFT_H_ */
