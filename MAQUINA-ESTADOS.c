//EMMANUEL A. MORALES
//4503888 UAG



#include <stdio.h>
#include "MKL25Z4.h"

/*Actualmente los vehiculos puede haber de lo mas moderno a lo mas basico, en los
 * coches mas modernos de lujo, podemos elegir regular de forma digital nuestra temperatura
 *podiendo elegir entre ciertos valores, usualmente entre 18-30°C en vez de una perilla tradicional
  como lo hemos visto por muchos años y con ello se me ocurrio hacer una pequeña maquina
 *de estados donde represento de manera general su funcionamiemto */

unsigned char CurrentValue_Celsius;  //valor actual de temperatura en el habitaculo(teoricamente tendera a enfriar hasta el limite definido por el usuario)

struct sEstadoAC
{
    unsigned char ubCurrentState;
};

struct sEvento
{
    unsigned char Entrada_Temperatura_User;    //temperatura a elegir por el usuario  18-30°C
    unsigned char Entrada_Temperatura_Externa;    // Entrada_Temperatura_Externa( del habitaculo)

};

void EsperarTemperatura(struct sEstadoAC *StateCar, struct sEvento *Evento);
void LeerTemperatura(struct sEstadoAC *StateCar, struct sEvento *Evento);


enum Estados
{
   Estado_EsperarTemperatura,  //   0  (solo opera de 18-30°C), espera que sea una temperatura valida, si es valida va al otro estado
    Estado_LeerTemperatura,    //   1   leer temperatura del ambiente
    Estado_ActivarCompresor,	//  2   si la temperatura(habitaculo) es mayor que la temp solicitada, compresor ON
	Estado_DesactivarCompresor, //  3   Si la temperatura(habitaculo) es igual que la temp habitaculo, compresor OFF
	Estado_EntregarTemperatura,  //  4   Entregar al usuario la temperatura adecuada(mostrarla en pantalla y frescura interna)
};

int main (void)
{
    struct sEstadoAC StateCar;
    struct sEvento Evento;

    StateCar.ubCurrentState=Estado_EsperarTemperatura;
    Evento.Entrada_Temperatura_Externa = 30;  //la brinda el ambiente
    Evento.Entrada_Temperatura_User= 24;   //elegidos por el usuario   se pueden variar en el debugeo


    void (* state_machine[])(struct sEstadoAC *, struct sEvento *) = {EsperarTemperatura, LeerTemperatura};
    while(1)
    {
    	 (*state_machine[StateCar.ubCurrentState])(&StateCar, &Evento);

    }

}

void EsperarTemperatura(struct sEstadoAC *StateCar, struct sEvento *Evento)   //tu la elijes
{
    printf("Elije la temperatura...\n");
    if( Evento->Entrada_Temperatura_User >=18){   //si la temp elegida es valida, se va al siguiente estado leer temp
        printf("%c", Evento->Entrada_Temperatura_User);
    StateCar->ubCurrentState = Estado_LeerTemperatura;
    }
    else {
    	StateCar->ubCurrentState = Estado_EsperarTemperatura;
    }
}



void LeerTemperatura(struct sEstadoAC *StateCar, struct sEvento *Evento)    // del exterior
{

    if (Evento->Entrada_Temperatura_Externa >Evento->Entrada_Temperatura_User )   //si temp habitaculo mayor que la del usuario habilita el compresor
    {
        printf("Leyendo temperatura...\n");
         printf("%c", Evento->Entrada_Temperatura_Externa);
         StateCar->ubCurrentState = Estado_ActivarCompresor;
          printf("La temperatura aumentó, compresor ON...\n");


   } else if (Evento->Entrada_Temperatura_Externa <Evento->Entrada_Temperatura_User )   //si la temperatura habitaculo menor que la temp del usuario genera error.
   {
    printf("La temperatura no es valida\n");
    printf("%c", Evento->Entrada_Temperatura_Externa);
         StateCar->ubCurrentState = Estado_LeerTemperatura;
         printf("La temperatura es no suficiente, compresor OFF...\n");

    } else if (Evento->Entrada_Temperatura_Externa == Evento->Entrada_Temperatura_User){   // si las temperaturas ya se igualaron apaga el compresor y mecanismos internos para ahorrar combustible
    	StateCar->ubCurrentState = Estado_DesactivarCompresor;
    }
    StateCar->ubCurrentState= Estado_EntregarTemperatura;
    CurrentValue_Celsius=Evento->Entrada_Temperatura_Externa;
    if(StateCar->ubCurrentState= Estado_EntregarTemperatura){
    	StateCar->ubCurrentState= Estado_EsperarTemperatura;
    }

}

