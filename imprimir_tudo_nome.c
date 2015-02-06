#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"

void printall2(){
	int final_h, final_m,h;
	char e[15], d[15];
	char nome[40];
	List l;
	List2 g;
	getchar();
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

	l=loadallnome(nome);
	printf("                               RESERVAS\n");
	if (l->previous==NULL)	
		printf("Nada a apresentar\n");
	else{
		while(l->previous!=NULL)
			l=l->previous;
		if(l->next!=NULL)
			l=l->next;
		while(l->next!=NULL){
			final_h = l->horas;
			final_m = l->minutos;

			for(h=0;h<l->blocos;h++)
				ajustar(&final_h,&final_m);

			printf("Sala: %d\nData: %d/%d/%d\nHorario: %d:%d-%d:%d -- %s",l->sala, l->data.dia, l->data.mes, l->data.ano, l->horas,l->minutos,final_h,final_m, l->nome_reserva);
			l=l->next;
		}

		final_h = l->horas;
		final_m = l->minutos;

		for(h=0;h<l->blocos;h++)
			ajustar(&final_h,&final_m);

		printf("Sala: %d\nData: %d/%d/%d\nHorario: %d:%d-%d:%d -- %s",l->sala, l->data.dia, l->data.mes, l->data.ano, l->horas,l->minutos,final_h,final_m, l->nome_reserva);
		destroylists(l);
	}

	printf("                               PRÉ RESERVAS\n");
	g=loadallnome2(nome);
	if (g->previous==NULL)
		printf("Nada a apresentar\n");
	else{
		while(g->previous!=NULL)
			g=g->previous;
		if(g->next!=NULL)
			g=g->next;
		while(g->next!=NULL){
			final_h = g->horas;
			final_m = g->minutos;

			for(h=0;h<1;h++)
				ajustar(&final_h,&final_m);

			printf("Sala: %d\nData: %d/%d/%d\nHorario: %d:%d-%d:%d -- %s", g->sala, g->data.dia, g->data.mes, g->data.ano, g->horas,g->minutos,final_h,final_m, g->nome_pre);
			g=g->next;
		}
		final_h = g->horas;
		final_m = g->minutos;

		for(h=0;h<1;h++)
			ajustar(&final_h,&final_m);

		printf("Sala: %d\nData: %d/%d/%d\nHorario: %d:%d-%d:%d -- %s", g->sala, g->data.dia, g->data.mes, g->data.ano, g->horas,g->minutos,final_h,final_m, g->nome_pre);
	}
}

List2 loadallnome2(char nome[]){
	int salax,diax,mesx,blocos, horas, minutos, id, read_id=0, anox, k=0;
	char aux[60];
	char a[30],b[30];
	FILE *f;
	List2 previous;
	List2 l=cria_listanome2(nome);
	f = fopen("pre-reservas.txt", "r");
    if (f != NULL){
        rewind(f);
        while(feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %d %s %s", &salax, &diax, &mesx, &anox, &horas, &minutos, &blocos, &id, a, b);
            //read_id = procura_id(id);
            k=search_id(id);
            strcpy(aux,a);
			strcat(aux," ");
			strcat(aux,b);
			strcat(aux,"\n");
            if (read_id==0 && k == 0){
                if(strcmp(aux,nome) == 0){
                    l->next = (List2) malloc (sizeof(List2_Node2));
                    previous = l;
                    l=l->next;
                    l->id = id;
                    l->data.dia = diax;
                    l->data.mes = mesx;
                    l->data.ano = anox;
                    l->horas= horas;
                    l->minutos= minutos;
                    l->sala = salax;
                    strcpy(l->nome_pre,nome);
                    l->next=NULL;
                    l->previous=previous;
                }
            }
        }
    }
    return l;
}

List2 cria_listanome2(char nome[]){
	List2 aux;
	aux = (List2) malloc (sizeof(List2_Node2));
	if (aux!=NULL){
		strcpy(aux->nome_pre,nome);
		aux->next = NULL;
		aux->previous = NULL;
	}
	return aux;
}

List loadallnome(char nome[]){
	int salax,diax,mesx,blocos, horas, minutos, id, read_id=0, anox;
	char aux[40];
	char a[30],b[30];
	FILE *f;
	List previous;
	List l=cria_listanome(nome);
	f = fopen("reservas.txt", "r");
    if (f != NULL){
        rewind(f);
        while(feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %d %s %s", &salax, &diax, &mesx, &anox, &horas, &minutos, &blocos, &id, a, b);
            read_id = procura_id(id);
            strcpy(aux,a);
			strcat(aux," ");
			strcat(aux,b);
			strcat(aux,"\n");
            if (read_id==0 && strcmp(aux,nome) == 0){
            	if(id==l->id)
            		break;
                if (l->id!=id){
                    l->next = (List) malloc (sizeof(List_node));
                    previous = l;
                    l=l->next;
                    l->id = id;
                    l->data.dia = diax;
                    l->data.mes = mesx;
                    l->data.ano = anox;
                    l->blocos= blocos;
                    l->horas= horas;
                    l->minutos= minutos;
                    l->sala = salax;
                    strcpy(l->nome_reserva,nome);	
                    l->next=NULL;
                    l->previous=previous;
                }
            }
        }
    }
    return l;
}

List cria_listanome(char nome[]){
	List aux;
	aux = (List) malloc (sizeof(List_node));
	if (aux!=NULL){
		strcpy(aux->nome_reserva,nome);
		aux->next = NULL;
		aux->previous = NULL;
	}
	return aux;
}