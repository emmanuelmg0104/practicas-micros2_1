/*
 * ADC.c
 *
 *  Created on: 24 jun. 2021
 *      Author: Personal
 */

#include "MKL25Z4.h"
#include<stdio.h>
#include "adc.h"

void ADC_vfnDriverInit (void);
unsigned short ADC_bfnReadADC (unsigned short bChannel);

void ADC_vfnDriverInit (void){

    SIM->SCGC5 |= 0x2000;       /* HABILITAR RELOJ PORT E */
    PORTE->PCR[20] = 0;         /*  PTE20 ENTRADA ANALOGA */

    SIM->SCGC6 |= 0x8000000;    /* HABILITACION RELOJ ADC0 */

    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    ADC0->CFG1 = 0x54;

}

unsigned short ADC_bfnReadADC (unsigned short bChannel){

    ADC0->SC1[0] = bChannel;           /* start conversion on channel 0 */
    while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
    return ADC0->R[0];        /* read conversion result and clear COCO flag */
}
