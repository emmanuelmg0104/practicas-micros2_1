//Analog input to FRDM KL25Z pin E20 (PTE20)
//PWM output from FRDM KL25Z pin C2  (PTC2)

// LAB 4

#include "MKL25Z4.h"
void ADC0_init(void);
void PWM_vfnDriverInit(void);
int option = 2;

int main(void) {

    short int result;
    BOARD_InitBootClocks();

   PWM_vfnDriverInit() ;                     /* Configure PWM */
   ADC0_init() ;                     /* Configure ADC0 */

    while (1) {
        ADC0->SC1[0] = 0;           /* start conversion on channel 0 */
        while(!(ADC0->SC1[0] & 0x80)) { } /* wait for conversion complete */
        result = ADC0->R[0];        /* read conversion result and clear COCO flag */
        TPM0->CONTROLS[1].CnV = 1500 + result*3/2;  /* Set up channel value between 2.5% and 12.5%*/
    }
}

void PWM_vfnDriverInit (void)
{
    SIM->SCGC5 |= 0x0800;       		   /* HABILITAR PUERTO  C*/
    SIM->SCGC6 |= 0x01000000;   		   /* HABILITAR EL RELOJ DE TPM0 */
    PORTC->PCR[2] = 0x0400;     		   /* PUERTO C2 USADO POR TPM0 */
    SIM->SOPT2 |= 0x01000000;   		   /* USO DE MCGFLLCLK COMO RELOJ */

    TPM0->SC = 0;               		  /* DESHABILITAR TIMER */
    TPM0->CONTROLS[1].CnSC = 0x28;        /*  PWM MODO EDGE ALIGNED, pulse high MSB:MSA=10, ELSB:ELSA=10*/
    TPM0->MOD = 60000;          		  /* Set up modulo register for 50 Hz - 48.00 MHz */
    TPM0->CONTROLS[1].CnV = 1500;  		  /* Set up channel value for 2.5% duty-cycle */
    TPM0->SC = 0x0C;            		  /* HABILITAR TPM0 COMO pre-scaler div /16 */
}

void ADC0_init(void)
{
    SIM->SCGC5 |= 0x2000;       /* HABILITAR RELOJ PORT E */
    PORTE->PCR[20] = 0;         /*  PTE20 ENTRADA ANALOGA */

    SIM->SCGC6 |= 0x8000000;    /* HABILITACION RELOJ ADC0 */
    ADC0->SC2 &= ~0x40;         /* software trigger */

    /* clock div by 4, long sample time, single ended 12 bit, bus clock */
    ADC0->CFG1 = 0x54;

}
