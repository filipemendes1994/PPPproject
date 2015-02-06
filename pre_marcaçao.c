#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"
#define MAX 100

void pre_marcacao(){
	int h,m,blocos,sala,dia,mes,ano, a,aux,i;
	int aux_h,aux_m;
	char d[14], e[14];
	List l;
	List2 g;
	char nome[MAX];
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
		} while(mes>12 || mes<1 || dia<1 || dia>30 || ano<2012|| ano>2030);
	}

	printf("Hora de Inicio da Pré-Reserva: hh/mm \n");
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
	printf("Tempo de Pre-Reserva (em minutos): \n");
	scanf("%d", &blocos);
	
	if (blocos%30){
		printf("BLOCOS DE 30 MINUTOS!!\n");
		do{
			printf("Tempo de Pre-Reserva (em minutos): \n");
			scanf("%d", &blocos);
		} while(blocos%30);
	}
	blocos = blocos/30;

	l = load_data(sala,dia,mes,ano);
	aux_h=h;
	aux_m=m;
	getchar();
	for (i=0; i<blocos; i++){
		aux = check(l,aux_h,aux_m);

		if (aux){
			printf("Bloco livre para Reserva. Deseja efectuá-la?(S|N)  \n");
			a=fgetc(stdin);
			if (a=='S' || a=='s')
				check_do(l,aux_h,aux_m,1);
		}

		else{
			do{
				printf("Primeiro Nome: \n");
				fgets(d,14,stdin);
				size_t ln = strlen(d) - 1;
				if (d[ln] == '\n')
		   			d[ln] = '\0';
			} while(d[0]=='\0');
			do{
				printf("Ultimo Nome: \n");
				fgets(e,14,stdin);
				size_t ln = strlen(e) - 1;
				if (e[ln] == '\n')
		   			e[ln] = '\0';
			} while(e[0]=='\0');
			strcpy(nome,d);
			strcat(nome," ");
			strcat(nome,e);
			strcat(nome,"\n");
	
			g = cria_pre_lista(sala,dia,mes,ano,aux_h,aux_m);
			load_pre(g);
			nova_prereserva(g,nome);
			save_id2(g);
			save_pre(g);
			printf("Pre-Marcação terminada com êxito!\n");
		}
		ajustar(&aux_h,&aux_m);
	}
}