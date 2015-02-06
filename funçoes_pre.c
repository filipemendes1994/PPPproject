#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"
#define MAX 100

List2 cria_pre_lista(int sala, int dia, int mes, int ano, int h, int m){
	List2 aux;
	aux = (List2) malloc (sizeof(List2_Node2));
	if (aux!=NULL){
		aux->sala = sala;
		aux->data.dia = dia;
		aux->data.mes = mes;
		aux->data.ano = ano;
		aux->horas = h;
		aux->minutos = m;
		aux->next = NULL;
		aux->previous = NULL;
	}		
	return aux;
}



void turntoreservations(int sala,int dia, int mes, int ano, int h, int m, int blocos){
	FILE *g;
	int i;
    for(i=0; i<blocos; i++){

	    List2 l = cria_pre_lista(sala,dia,mes,ano,h,m);
	    load_pre(l);

	    while(l->previous!=NULL)
	    	l=l->previous;
	    if (l->next!=NULL){
	    	l=l->next;
		    g=fopen("passagens.txt", "r+");
		    if (g!=NULL){
		        fseek(g,0l,SEEK_END);
		        fprintf(g,"%d\n", l->id);
		        fclose(g);
		    }
		    else{
		        g=fopen("passagens.txt", "w");
		        fprintf(g,"%d\n", l->id);
		        fclose(g);
		    }
		    g = fopen("reservas.txt", "a");
		    if (g!=NULL){
		    	fprintf(g,"%d %d %d %d %d %d 1 %d %s", l->sala, l->data.dia, l->data.mes, l->data.ano, l->horas, l->minutos, l->id, l->nome_pre);
		    	fclose(g);
		   	}
		}
		ajustar(&h,&m);
	}
}

void nova_prereserva(List2 l, char a[]){
	int sala = l->sala;
	List2 aux;
	while(l->next != NULL)
		l = l->next; 
	l->next = (List2) malloc(sizeof(List2_Node2));
	aux=l;
	l=l->next;
	l->id = load_id()+1;
	l->previous = aux;
	l->horas = l->previous->horas;
	l->minutos = l->previous->minutos;
	l->sala = l->previous->sala;
	l->data.dia = l->previous->data.dia;
	l->data.mes = l->previous->data.mes;
	l->data.ano = l->previous->data.ano;
	strcpy(l->nome_pre, a);
	l->next = NULL;
}





int destroylists2(List2 l){
	while(l->next!=NULL)
		l=l->next;
	while(l->previous!=NULL){
		l=l->previous;
		free(l->next);
	}
	free(l);
	return 0;
}