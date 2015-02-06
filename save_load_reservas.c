#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"
#define MAX 100

void save_data(List l){
    FILE *f;
    f = fopen("reservas.txt", "r");
    if (f != NULL){
        fclose(f);
        f = fopen("reservas.txt", "a");
        if(f!=NULL){
            while(l->next!=NULL){
                l=l->next;
            }
            fprintf(f,"%d %d %d %d %d %d %d %d %s", l->sala, l->data.dia, l->data.mes, l->data.ano, l->horas, l->minutos, l->blocos, l->id, l->nome_reserva);
           // printf("save() %d\n", l->horas);
            fclose(f);
            //printf("----->Done!\n");
        }
        else   
            printf("Erro. Tente Novamente\n");
    }
    else{
        f=fopen("reservas.txt","w");
        if(f!=NULL){
            if(l->next != NULL)
                l=l->next;

            fprintf(f,"%d %d %d %d %d %d %d %d %s", l->sala, l->data.dia, l->data.mes, l->data.ano, l->horas, l->minutos, l->blocos, l->id,l->nome_reserva);
            //printf("save() %d\n", l->horas);
            fclose(f);
            //printf("->Done!\n");
        }
        else
            printf("Erro. Tente Novamente\n");
    }
    if(destroylists(l)==0)
        printf("Reserva realizada com Sucesso\n");

}

void save_reserva_cancelada(List l){
    int sala,dia,mes,ano,blocos, horas, minutos, id;
    char a[30],b[30];
    
    FILE *f;
    FILE *g;
    f = fopen("reservas.txt", "r");
    if (f!=NULL){
        rewind(f);
        while(feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %d %s %s", &sala, &dia, &mes, &ano, &horas, &minutos, &blocos, &id, a, b);
            if(sala == l->sala && dia == l->data.dia && mes == l->data.mes && ano == l->data.ano && horas == l->horas && minutos == l->minutos && blocos == l->blocos && id == l->id){
                g=fopen("cancelamentos.txt", "r+");
                if (g!=NULL){
                    fseek(g,0l,SEEK_END);
                    fprintf(g,"%d\n", l->id);
                    fclose(g);
                }
                else{
                    g=fopen("cancelamentos.txt", "w");
                    fprintf(g,"%d\n", l->id);
                    fclose(g);
                }
                break;
            }
        }
        fclose(f);
    }
}

List load_data(int sala, int dia, int mes, int ano){
    int salax,diax,mesx,blocos, horas, minutos, id, read_id=0, anox;
    char a[30], b[30];

    List l = cria_lista(sala,dia,mes,ano);
    List previous;

    FILE *f;
    f = fopen("reservas.txt", "r");

    if (f != NULL){
        rewind(f);
        while(feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %d %s %s", &salax, &diax, &mesx, &anox, &horas, &minutos, &blocos, &id, a, b);
            read_id = procura_id(id);
            if (read_id==0){
                if (salax == sala && diax == dia && mesx == mes && anox == ano){
                    l->next = (List) malloc (sizeof(List_node));
                    previous = l;
                    l=l->next;
                    l->id = id;
                    l->data.dia = dia;
                    l->data.mes = mes;
                    l->data.ano = ano;
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

void load_pre(List2 l){
    int salax, diax, mesx, anox, horas,minutos,id,k;
    int aux;
    char a[30], b[30];
    List2 previous;
    FILE *f;
    f = fopen("pre-reservas.txt", "r");
    if (f!=NULL){
        rewind(f);
        while (feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %s %s", &salax, &diax, &mesx, &anox, &horas, &minutos, &id, a, b);
            aux = search_id(id);
            k = procura_id(id);
            if (aux==0 && k==0){
                if (salax == l->sala && diax == l->data.dia && mesx == l->data.mes && anox == l->data.ano && horas == l->horas && minutos == l->minutos && id!=l->id){
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
                    strcpy(l->nome_pre,a);
                    strcat(l->nome_pre," ");
                    strcat(l->nome_pre,b);
                    strcat(l->nome_pre, "\n");
                    l->next=NULL;
                    l->previous=previous;
                }
            }
        }
    }
}

void save_pre(List2 l){
    FILE *f;
    f = fopen("pre-reservas.txt", "r");
    if (f != NULL){
        fclose(f);
        f = fopen("pre-reservas.txt", "a");
        if(f!=NULL){
            while(l->next!=NULL)
                l=l->next;
            
            fprintf(f,"%d %d %d %d %d %d %d %s", l->sala, l->data.dia, l->data.mes, l->data.ano, l->horas, l->minutos, l->id, l->nome_pre);
           // printf("save() %d\n", l->horas);
            fclose(f);
            //printf("----->Done!\n");
        }   
    }
    else{
        f=fopen("pre-reservas.txt","w");
        if(f!=NULL){
            if(l->next != NULL)
                l=l->next;

            fprintf(f,"%d %d %d %d %d %d %d %s", l->sala, l->data.dia, l->data.mes, l->data.ano, l->horas, l->minutos, l->id, l->nome_pre);
            //printf("save() %d\n", l->horas);
            fclose(f);
            //printf("->Done!\n");
        }
    }
}

void save_prereserva_cancelada(List2 l, char nome[]){
    int sala,dia,mes,ano,horas, minutos, id;
    char a[MAX], b[MAX];
    char aux_nome[MAX];
    
    FILE *f;
    FILE *g;
    f = fopen("pre-reservas.txt", "r");
    if (f!=NULL){
        rewind(f);
        while(feof(f)==0){
            fscanf(f,"%d %d %d %d %d %d %d %s %s", &sala, &dia, &mes, &ano, &horas, &minutos, &id, a,b);
            strcpy(aux_nome,a);
            strcat(aux_nome," ");
            strcat(aux_nome,b);
            strcat(aux_nome, "\n");
            if(strcmp(nome,aux_nome)==0){
                g=fopen("cancelamentos.txt", "r+");
                if (g!=NULL){
                    fseek(g,0l,SEEK_END);
                    fprintf(g,"%d\n", l->id);
                    fclose(g);
                }
                else{
                    g=fopen("cancelamentos.txt", "w");
                    fprintf(g,"%d\n", l->id);
                    fclose(g);
                }
                break;
            }
        }
        fclose(f);
    }
}


