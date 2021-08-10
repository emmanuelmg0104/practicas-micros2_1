/*
 * PWM.c
 *
 *  Created on: 9 jul. 2021
 *      Author: Personal
 */

#include "MKL25Z4.h"
#include "adc.h"

void PWM_vfnDriverInit(void);
unsigned int DPY_bInitialPosition (void);
unsigned int PWM_bfnAngleAdjustment (int bNewAngle);
void delayMs(int n);

void PWM_vfnDriverInit (void)
{
    SIM->SCGC5 |= 0x800;       		   /* HABILITAR PUERTO  C*/
    SIM->SCGC6 |= 0x1000000;   		   /* HABILITAR EL RELOJ DE TPM0 */
    PORTC->PCR[2] = 0x400;     		   /* PUERTO C2 USADO POR TPM0. es salida de PWM*/
    SIM->SOPT2 |= 0x1000000;   		   /* USO DE RELOJ DE 21MHz MCGFLLCLK COMO RELOJ */

    TPM0->CONTROLS[1].CnSC = 0x28;        /* PWM MODO EDGE ALIGNED, pulse high MSB:MSA=10, ELSB:ELSA=10*/
    TPM0->MOD = 26249;          		  /* Set up modulo register for 21 MHz y T=20ms */
    TPM0->CONTROLS[1].CnV = 1;  		  /* Set up channel value for 50% duty-cycle */
    TPM0->SC = 0x0C;            		  /* HABILITAR TPM0 COMO pre-scaler div /16 */
}

unsigned int DPY_bInitialPosition (void){
	  TPM0->CONTROLS[1].CnV = 500; //servo en 0°
	  delayMs(500);
}

unsigned int PWM_bfnAngleAdjustment (int bNewAngle){
	int result;
	   while (1) {
		   result = ADC_bfnReadADC(0); //pte20 adc in
		   if(bNewAngle == 180){
			   TPM0->CONTROLS[1].CnV =  result-1091;   /* duty cicle 10%, señal en alto de 2ms, permite girar hasta 180°*/

		   } else if(bNewAngle == 90){
			   TPM0->CONTROLS[1].CnV = result-2596;  /* duty cicle 5%, señal en alto de 1ms, permite girar hasta 90°*/

		   }
	   }
}

void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for(j = 0 ; j < 7000; j++)
	{ }
}

