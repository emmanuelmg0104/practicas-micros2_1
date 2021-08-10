/*
 * LCD16x2.c
 *
 *  Created on: 23 jun. 2021
 *      Author: Personal
 */

#include "MKL25Z4.h"
#include "pinSetting.h"

void delayMs(int n);
void InitPins(void);
void StepSet(void);
void Step1Clear(void);
void StepReturnH(void);
void StepOnOff(void);
void writeT(void);
void writeE(void);
void writeM(void);
void writeP(void);
void write2points(void);

void DPY_vfnDriverInit (void){

	InitPins();
	StepSet(); //SE ESPECIFICAN LINEAS EN EL DISPLAY INTERFAZ 8 BITS
	Step1Clear();  //LIMPIA PANTALLA
	StepReturnH(); //COLOCA EL CURSOR DEL LADO IZQ
	StepOnOff(); //PARPADEA EL CURSOR
	writeH();
	writeO();
	writeL();
	writeA();
	write2points();
}

void InitPins(void){
	pinMode('B',8, 1); //D0
	pinMode('B',9, 1); //D1
	pinMode('A',17, 1); //D2
	pinMode('A',16, 1); //D3
	pinMode('C',17, 1); //D4
	pinMode('C',16, 1); //D5
	pinMode('C',13, 1); //D6
	pinMode('C',12, 1); //D7

	pinMode('C',11, 1); //RS
	pinMode('C',10, 1); //RW
	pinMode('C',6, 1); //E

}

void Step1Clear(void){
	digitalWrite('C',11, 0); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 1); //E

	digitalWrite('B',8, 1); //D0
	digitalWrite('B',9, 0); //D1
	digitalWrite('A',17, 0); //D2
	digitalWrite('A',16, 0); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 0); //D6
	digitalWrite('C',12, 0); //D7


	delayMs(500);
}

void StepReturnH(void){

	digitalWrite('C',11, 0); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 1); //E

	digitalWrite('B',8, 0); //D0
	digitalWrite('B',9, 1); //D1   //ES PARA QUE SE MUEVA DE IZQ A DERECHA
	digitalWrite('A',17, 0); //D2   //ES OPCIONAL EL 1
	digitalWrite('A',16, 0); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 0); //D6
	digitalWrite('C',12, 0); //D7

	delayMs(500);

	digitalWrite('C',6, 0); //E
	digitalWrite('B',9, 0); //D1
	delayMs(500);

}

void StepSet(void){  //1

	digitalWrite('C',6, 1); //E

	digitalWrite('B',8, 0); //D0
	digitalWrite('B',9, 0); //D1
	digitalWrite('A',17, 0); //D2
	digitalWrite('A',16, 1); //D3
	digitalWrite('C',17, 1); //D4
	digitalWrite('C',16, 1); //D5
	digitalWrite('C',13, 0); //D6
	digitalWrite('C',12, 0); //D7

	digitalWrite('C',11, 0); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 0); //E

	delayMs(500);

	digitalWrite('C',6, 0); //E
	digitalWrite('B',8, 0); //D0
	digitalWrite('B',9, 0); //D1
	digitalWrite('A',17, 0); //D2
	digitalWrite('A',16, 0); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 0); //D6
	digitalWrite('C',12, 0); //D7
	delayMs(500);
}

void StepOnOff(void){
	digitalWrite('C',6, 1); //E
	digitalWrite('C',11, 0); //RS
	digitalWrite('C',10, 0); //RW


	digitalWrite('B',8, 1); //D0 = Parpadeo
	digitalWrite('B',9, 0); //D1 = Cursor
	digitalWrite('A',17, 1); //D2
	digitalWrite('A',16, 1); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 0); //D6
	digitalWrite('C',12, 0); //D7


	//Delay
	delayMs(500);

	digitalWrite('C',11, 0); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 0); //E

	digitalWrite('B',8, 0); //D0
	digitalWrite('B',9, 0); //D1
	digitalWrite('A',17, 0); //D2
	digitalWrite('A',16, 0); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 0); //D6
	digitalWrite('C',12, 0); //D7
	delayMs(500);
}

void writeA(void){

	digitalWrite('C',11, 1); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 0); //E

	digitalWrite('B',8, 1); //D0
	digitalWrite('B',9, 0); //D1
	digitalWrite('A',17, 0); //D2
	digitalWrite('A',16, 0); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 1); //D6
	digitalWrite('C',12, 0); //D7

	digitalWrite('C',6, 1); //E

	digitalWrite('C',6, 0); //E

}

void writeL(void){

	digitalWrite('C',11, 1); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 0); //E

	digitalWrite('B',8, 0); //D0
	digitalWrite('B',9, 0); //D1
	digitalWrite('A',17, 1); //D2
	digitalWrite('A',16, 1); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 1); //D6
	digitalWrite('C',12, 0); //D7

	digitalWrite('C',6, 1); //E

	digitalWrite('C',6, 0); //E

}

void writeO(void){

	digitalWrite('C',11, 1); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 0); //E

	digitalWrite('B',8, 1); //D0
	digitalWrite('B',9, 1); //D1
	digitalWrite('A',17, 1); //D2
	digitalWrite('A',16, 1); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 1); //D6
	digitalWrite('C',12, 0); //D7

	digitalWrite('C',6, 1); //E

	digitalWrite('C',6, 0); //E

}

void writeH(void){

	digitalWrite('C',11, 1); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 0); //E

	digitalWrite('B',8, 0); //D0
	digitalWrite('B',9, 0); //D1
	digitalWrite('A',17, 0); //D2
	digitalWrite('A',16, 1); //D3
	digitalWrite('C',17, 0); //D4
	digitalWrite('C',16, 0); //D5
	digitalWrite('C',13, 1); //D6
	digitalWrite('C',12, 0); //D7

	digitalWrite('C',6, 1); //E

	digitalWrite('C',6, 0); //E

}

void write2points(void){
	digitalWrite('C',11, 1); //RS
	digitalWrite('C',10, 0); //RW
	digitalWrite('C',6, 0); //E

	digitalWrite('B',8, 0); //D0
	digitalWrite('B',9, 1); //D1
	digitalWrite('A',17, 0); //D2
	digitalWrite('A',16, 1); //D3
	digitalWrite('C',17, 1); //D4
	digitalWrite('C',16, 1); //D5
	digitalWrite('C',13, 0); //D6
	digitalWrite('C',12, 0); //D7

	digitalWrite('C',6, 1); //E

	digitalWrite('C',6, 0); //E

}

void delayMs(int n) {
	int i;
	int j;
	for(i = 0 ; i < n; i++)
	for(j = 0 ; j < 7000; j++)
	{ }
}
