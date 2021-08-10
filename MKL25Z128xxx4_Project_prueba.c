/*
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Project_prueba.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "Arduino.h"
//#include "LCD1.H"
/* TODO: insert other include files here. */
/* TODO: insert other definitions and declarations here. */
#define uart UART0
void UART_vfnDriverInit (void);
void Serial_READ(uint8_t *recived);

void transmit(char *DATA);
uint_8 UART_bfnRead (unsigned int *bpRxData);

/*void enteroACadena(unsigned int numero, char *bufer){
    // Recuerda: u es para un unsigned int
    sprintf(bufer, "%u", numero);
}
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
							BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    UART_vfnDriverInit ();
    unsigned char r0=0;
    char buffer[11];
    char dato[]="HALLO WELT ";
    while(1)
    {

     Serial_READ(&r0);
     //UART_bfnRead(&r0);
     printf("%c",r0);
     //transmit(dato);
    // LCD_command(DISPLAY_CLEAR);
     //DPY_bfnWriteMsg("resistencia=");
     //charACadena(r0,buffer);
     //LCD_data(r0);
     //DPY_bfnWriteMsg(r0);
    // delayMs(500);
    }
    return 0 ;
}


void UART_vfnDriverInit (void)
{
	MCG->C4=0xA0;
	SIM->SOPT2 |= SIM_SOPT2_UART0SRC(1);
	SIM->SCGC4|=SIM_SCGC4_UART0_MASK;
	SIM->SCGC5|=SIM_SCGC5_PORTA_MASK;
	PORTA->PCR[1]|=PORT_PCR_MUX(2);
	PORTA->PCR[2]|=PORT_PCR_MUX(2);
	UART0->BDL=0x38;
	UART0->BDH=0x1;
	UART0->C1=0x0;
	UART0->C2=0xC;
}

void transmit(char *DATA)
{
	while(*DATA)
	{

		UART0->D=*DATA;
		delayMs(500);
		while(!(UART0->S1&UART_S1_TDRE_MASK));
		DATA++;
	}

}



void Serial_READ(uint8_t *recived)
{
  UART0->C2=0X4;
  //while(!(UART0->S1 & UART0_S1_RDRF_MASK));
  *recived=UART0->D;
  //wait for receive buffer full
}

uint_8 UART_bfnRead (unsigned int *bpRxData){
	uint_8 bStatus=0;
	UART0->C2=0X4;
		if(UART_S1_RDRF_MASK & UART0->S1){// RDRF Receive Data Register Full Flag, THE RECIVE BUFFER IS FULL THE MASK IS 1<<21, ITS TO CHECK IF RDRF ITS ON
			bStatus=1;
			*bpRxData= UART0-> D;
		}else{
			bStatus=0;
		}
			return bStatus;
	}

/*
void UART0_tx(int tx0)
{while ((UART0->S1 & UART_S1_TDRE_MASK) == 0);
 UART0->D=tx0;}
*/
