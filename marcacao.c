#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"
 
void marcacao(){
	int h,m,blocos,sala,dia,mes,ano;
	List l;
	printf("Sala: \n");
	scanf("%d", &sala);
	if (sala<1){
		do{
			printf("Sala \n");
			scanf("%d", &sala);
		} while(sala<1);
	}
	fflush(stdin);
	printf("Data: dd/mm/aaaa\n");
	scanf("%d %d %d", &dia, &mes, &ano);
	if (mes>12 || mes<1 || dia<1 || dia>30 || ano<2012 || ano>2030){
		do{
			printf("Data: dd/mm/aaaa\n");
			scanf("%d %d %d", &dia, &mes, &ano);
		} while(mes>12 || mes<1 || dia<1 || dia>30 || ano<2012 || ano>2030);
	}

	l=load_data(sala,dia,mes,ano);
	printf("Hora de Inicio de Reserva: hh/mm \n");
	scanf("%d %d", &h, &m);


	if (h>23 || h<10){
		printf("VERIFICAR HÓRÁRIO DE FUNCIONAMENTO \n");
		do{
			printf("Hora de Inicio de Reserva: hh/mm \n");
			scanf("%d %d", &h, &m);
		} while(h>23 || h<10);
	}
	else if (m!=0 && m!=30){
		printf("RESERVA APENAS DISPONÍVEL PARA BLOCOS DE 30 MINUTOS\n");
		do{
			printf("Hora de Inicio de Reserva: hh/mm \n");
			scanf("%d %d", &h, &m);
		} while(h>23 || h<10);
	}
	printf("Tempo de Reserva (em minutos): \n");
	scanf("%d", &blocos);
	
	if (blocos%30){
		printf("BLOCOS DE 30 MINUTOS!!\n");
		do{
			printf("Tempo de Reserva (em minutos): \n");
			scanf("%d", &blocos);
		} while(blocos%30);
	}

	blocos= blocos/30;
	check_do(l,h,m,blocos);
	
}