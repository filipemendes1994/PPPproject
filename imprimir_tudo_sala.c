#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"

void printall(){
	int sala, h;
	int final_h,final_m;

	List l;
	List2 g;
	printf("Sala: \n");
	scanf("%d", &sala);
	if (sala<1){
		do{
			printf("Sala \n");
			scanf("%d", &sala);
		} while(sala<1);
	}
	l = loadallreservations(sala);
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

			printf("%d %d %d %d:%d-%d:%d -- %s", l->data.dia, l->data.mes, l->data.ano, l->horas,l->minutos,final_h,final_m, l->nome_reserva);
			l=l->next;
		}

		final_h = l->horas;
		final_m = l->minutos;

		for(h=0;h<l->blocos;h++)
			ajustar(&final_h,&final_m);

		printf("%d %d %d %d:%d-%d:%d -- %s", l->data.dia, l->data.mes, l->data.ano, l->horas,l->minutos,final_h,final_m, l->nome_reserva);
		destroylists(l);
	}


	printf("                               PRÉ RESERVAS\n");
	g=loadallreservations2(sala);
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

			printf("%d %d %d %d:%d-%d:%d -- %s\n", g->data.dia, g->data.mes, g->data.ano, g->horas,g->minutos,final_h,final_m, g->nome_pre);
			g=g->next;
		}
		final_h = g->horas;
		final_m = g->minutos;

		for(h=0;h<1;h++)
			ajustar(&final_h,&final_m);

		printf("%d %d %d %d:%d-%d:%d -- %s\n", g->data.dia, g->data.mes, g->data.ano, g->horas,g->minutos,final_h,final_m, g->nome_pre);
	}
}

List2 loadallreservations2(int sala){
    int salax,diax,mesx,horas, minutos, id, read_id=0, anox,k;
    char a[30], b[30];
    List2 previous;

    List2 l = cria_listapre(sala);

    FILE *f;
    f = fopen("pre-reservas.txt", "r");
    if (f != NULL){
        rewind(f);
        while(feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %s %s", &salax, &diax, &mesx, &anox, &horas, &minutos, &id, a, b);
            read_id = procura_id(id);
            k = search_id(id);
            //printf("%d %d %d %d %d %d %d\n", salax,diax,mesx,anox,horas,minutos,id);
            if (read_id==0 && k ==0){
            	if(id == l->id)
            		break;
                if (salax == sala && l->id!=id){
                    l->next = (List2) malloc (sizeof(List2_Node2));
                    previous = l;
                    l=l->next;
                    l->id = id;
                    l->data.dia = diax;
                    l->data.mes = mesx;
                    l->data.ano = anox;
                    l->horas= horas;
                    l->minutos= minutos;
                    l->sala = sala;
                    strcpy(l->nome_pre,a);
                    strcat(l->nome_pre," ");
                    strcat(l->nome_pre,b);
                   // strcat(l->nome_pre,"\n");
                    l->next=NULL;
                    l->previous=previous;
                }
            }
        }
    }
    return l;
}

List2 cria_listapre(int sala){
	List2 aux;
	aux = (List2) malloc (sizeof(List2_Node2));
	if (aux!=NULL){
		aux->sala = sala;
		aux->next = NULL;
		aux->previous = NULL;
	}		
	return aux;
}

List loadallreservations(int sala){
    int salax,diax,mesx,blocos, horas, minutos, id, read_id=0, anox;
    char a[30], b[30];
    List previous;

    List l = cria_listainteira(sala);

    FILE *f;
    f = fopen("reservas.txt", "r");
    if (f != NULL){
        rewind(f);
        while(feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %d %s %s", &salax, &diax, &mesx, &anox, &horas, &minutos, &blocos, &id, a, b);
            read_id = procura_id(id);
            if (read_id==0){
            	if(id==l->id)
            		break;
                if (salax == sala && l->id!=id){
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
                    l->sala = sala;
                    strcpy(l->nome_reserva,a);
                    strcat(l->nome_reserva," ");
                    strcat(l->nome_reserva,b);
                    strcat(l->nome_reserva,"\n");
                    l->next=NULL;
                    l->previous=previous;
                }
            }
        }
    }
    return l;
}

List cria_listainteira(int sala){
	List aux;
	aux = (List) malloc (sizeof(List_node));
	if (aux!=NULL){
		aux->sala = sala;
		aux->next = NULL;
		aux->previous = NULL;
	}		
	return aux;
}

int compara_data(data d1, data d2){
	if (d1.ano>d2.ano)
		return 1;
	else if (d1.ano == d2.ano){
		if(d1.mes>d2.mes)
			return 1;
		else if (d1.mes == d2.mes){
			if(d1.dia>d2.dia)
				return 1;
			else if(d1.dia == d2.dia)
				return 0;
			else
				return -1;
		}
		else
			return -1;

	}
	else
		return -1;
}