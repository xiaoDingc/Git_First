/**********************************************************************
 *                                                                     *
 *                        Software License Agreement                   *
 *                                                                     *
 *    The software supplied herewith by Microchip Technology           *
 *    Incorporated (the "Company") for its dsPIC controller            *
 *    is intended and supplied to you, the Company's customer,         *
 *    for use solely and exclusively on Microchip dsPIC                *
 *    products. The software is owned by the Company and/or its        *
 *    supplier, and is protected under applicable copyright laws. All  *
 *    rights are reserved. Any use in violation of the foregoing       *
 *    restrictions may subject the user to criminal sanctions under    *
 *    applicable laws, as well as to civil liability for the breach of *
 *    the terms and conditions of this license.                        *
 *                                                                     *
 *    THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION.  NO           *
 *    WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING,    *
 *    BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND    *
 *    FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE     *
 *    COMPANY SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL,  *
 *    INCIDENTAL OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.  *
 *                                                                     *
  **********************************************************************/

 /**********************************************************************
 *                                                                     * 
 *    Author: CADC
 *    Date:           1/11/06                                          *
 *    File Version:   pre-release version for Belta customers use only *
 *    Project:        Front-end of tri-phase power meter               *
                                              
 *                                                                     *
 *    Tools used:    MPLAB C30 Compiler v 1.32                         *
 *                                                                     *
 *    Linker File:    p30f3013.gld   		
 **********************************************************************/
 

    /* global symbols */
    .global _ComputeMagnitude

    /* code */
    .section .text

/**********************************************************************
*
*   Function:    ComputeMagnitude()
*   Arguments:   fractional *, pointer to FFTData (stored in W0)
*                fractional *, pointer to FFTMagnitude (stored in W1)
*                int, magnitude size to compute (stored in W2) 
*   Returns:     void (FFTMagnitude[] is updated)
*
*   This assembly function computes the magnitude squared of the complex 
*   vector pointed to by W0.  The magnitude squared is computed as:
*        Real*Real + Imag*Imag  --> required for each bin
*   The computed magnitude is stored to the array pointed to by W1.
*
*   NOTE:  Due to the nature of the data, scaling will be required
*          when storing out the computed magnitude from the accumulator.
*
/***********************************************************************/
_ComputeMagnitude:

    mov     w0, w10                    ; FFT Data stored in Y memory!
    dec     w2, w2                     ; decrement loop counter for DO loop
    mov     [w10++], w4                ; fetch first real value
    do      w2, end_mag                ; use a DO loop to save time
    mpy     w4*w4, a, [w10]+=2, w4     ; compute real*real
    mac     w4*w4, a, [w10]+=2, w4     ; add in imag*imag
end_mag:    
    sac.r   a, #-4, [w1++]             ; store result with scale

    return                             ; return from function
		
   .end
