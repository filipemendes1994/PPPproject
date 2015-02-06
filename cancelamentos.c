#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"
#define MAX 100

void cancelar_reserva(){
	int sala,dia,mes,ano,h,m,aux,blocos;
	List l;
	printf("Sala: \n");
	scanf("%d", &sala);
	if (sala<1){
		do{
			printf("Sala \n");
			scanf("%d", &sala);
		} while(sala<1);
	}
	printf("Data: dd/mm/aaaa\n");
	scanf("%d %d %d", &dia, &mes, &ano);
	if (mes>12 || mes<1 || dia<1 || dia>30 || ano<2012 || ano>2030){
		do{
			printf("Data: dd/mm/aaaa\n");
			scanf("%d %d %d", &dia, &mes, &ano);
		} while(mes>12 || mes<1 || dia<1 || dia>30 || ano<2012 || ano>2030);
	}

	l=load_data(sala,dia,mes,ano);
	while(l->previous!=NULL)
		l=l->previous;


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

	while(l->next!=NULL){
		if (l->horas == h && l->minutos == m){
			aux=0;
			break;
		}
		l=l->next;
	}
	if (l->horas == h && l->minutos == m)
			aux=0;
		
	blocos=l->blocos;
	if (aux){
		printf("Bloco não encontrado!!\n");
		return;
	}
	else{
		save_reserva_cancelada(l);
		destroylists(l);
		printf("RESERVA CANCELADA\n");
		turntoreservations(sala,dia,mes,ano,h,m,blocos);
	}

}

void cancelar_prereserva(){
	int sala,dia,mes,ano,h,m,aux,i,blocos;
	List2 l;
	char nome[MAX], a[14], b[14];
	printf("Sala: \n");
	scanf("%d", &sala);
	if (sala<1){
		do{
			printf("Sala \n");
			scanf("%d", &sala);
		} while(sala<1);
	}
	printf("Data: dd/mm/aaaa\n");
	scanf("%d %d %d", &dia, &mes, &ano);
	if (mes>12 || mes<1 || dia<1 || dia>30 || ano<2012|| ano>2030){
		do{
			printf("Data: dd/mm/aaaa\n");
			scanf("%d %d %d", &dia, &mes, &ano);
		} while(mes>12 || mes<1 || dia<1 || dia>30 || ano<2012|| ano>2030);
	}

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
	printf("Tempo da Pre-Reserva: (em minutos) \n");
	scanf("%d", &blocos);
	if (blocos%30){
		printf("BLOCOS DE 30 MINUTOS!!\n");
		do{
			printf("Tempo de Pre-Reserva (em minutos): \n");
			scanf("%d", &blocos);
		} while(blocos%30);
	}
	blocos = blocos/30;

	getchar();
	do{
		printf("Primeiro Nome: \n");
		fgets(a,14,stdin);
		size_t ln = strlen(a) - 1;
		if (a[ln] == '\n')
   			a[ln] = '\0';
	} while(a[0]=='\0');
	do{
		printf("Ultimo Nome: \n");
		fgets(b,14,stdin);
		size_t ln = strlen(b) - 1;
		if (b[ln] == '\n')
   			b[ln] = '\0';
	} while(b[0]=='\0');
	strcpy(nome,a);
	strcat(nome," ");
	strcat(nome,b);
	strcat(nome,"\n");

	for (i=0;i<blocos;i++){
		l=cria_pre_lista(sala,dia,mes,ano,h,m);
		load_pre(l);

		while(l->previous!=NULL)
			l=l->previous;

		while(l->next!=NULL){
			if(strcmp(nome,l->nome_pre)==0){
				aux=1;
				break;
			}
			l=l->next;
		}

		if (aux==0){
			printf("Bloco não encontrado!!\n");
		}
		else{
			save_prereserva_cancelada(l,nome);
		}
	}
	if(destroylists2(l)==0)
		printf("Bloco de pré-reservas cancelado\n");
}