#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"

List cria_lista(int sala, int dia, int mes, int ano){
	List aux;
	aux = (List) malloc (sizeof(List_node));
	if (aux!=NULL){
		aux->sala = sala;
		aux->data.dia = dia;
		aux->data.mes = mes;
		aux->data.ano = ano;
		aux->blocos = -3;
		aux->next = NULL;
		aux->previous = NULL;
	}		
	return aux;
}

void nova_entrada(List l, int h, int m, int blocos){
	int sala = l->sala;
	List aux;
	char a[14], b[14];
	while(l->next != NULL)
		l = l->next; 
	l->next = (List) malloc(sizeof(List_node));
	aux=l;
	l=l->next;
	l->id = load_id()+1;
	l->previous = aux;
	l->horas = h;
	l->minutos = m;
	l->blocos = blocos;
	l->sala = sala;
	l->data.dia = l->previous->data.dia;
	l->data.mes = l->previous->data.mes;
	l->data.ano = l->previous->data.ano;
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
	strcpy(l->nome_reserva,a);
	strcat(l->nome_reserva," ");
	strcat(l->nome_reserva,b);
	strcat(l->nome_reserva,"\n");
}

int destroylists(List l){
	while(l->next!=NULL)
		l=l->next;
	while(l->previous!=NULL){
		l=l->previous;
		free(l->next);
	}
	//free(l);
	return 0;
}

void ajustar(int *h, int *m){
	*m +=30;
	if (*m == 60){
		*m = 0;
		(*h)++;
	}
}