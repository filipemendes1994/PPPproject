#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"

void check_do(List l, int h, int m, int blocos){
	int aux_h=h, aux_m=m, final=0, i, g, aux, final_h, final_m;
	int a;

	for(i=1; i<=blocos; i++){
		final += check(l,aux_h,aux_m);
		ajustar(&aux_h,&aux_m);
	}
	getchar();
	if(blocos==final){
		printf("Período totalmente disponível\nA realizar reserva...\n");   
		nova_entrada(l,h,m,blocos);
		save_id(l);
		save_data(l);
		return;
	}

	else if (final){
		printf("Período não totalmente disponível\n");
		aux_h = h;
		aux_m = m;

		for(i=1;i<=blocos;i++){
			aux=check(l,aux_h,aux_m);
			if(aux == 0)
				ajustar(&aux_h,&aux_m);
			else{
				if (i!=blocos){
					final_h=aux_h;
					final_m=aux_m;
					for(g=i;g<=blocos;g++){
						ajustar(&final_h,&final_m);
						if(check(l,final_h,final_m) != 1){
							printf("Disponível das %d:%d as %d:%d\nReservar? (S|N)", aux_h,aux_m,final_h,final_m);
							a=fgetc(stdin);
							if (a=='S'){
								getchar();
								nova_entrada(l,aux_h,aux_m,blocos-g);
								save_id(l);
								save_data(l);
								break;
							}
						}
					}
				}
				else{
					final_h=aux_h;
					final_m=aux_m;

					ajustar(&final_h,&final_m);

					printf("Disponível das %d:%d as %d:%d\nReservar? (S|N)", aux_h,aux_m,final_h,final_m);
					a=fgetc(stdin);
					if (a=='S'){
						getchar();
						nova_entrada(l,aux_h,aux_m,1);
						save_id(l);
						save_data(l);
						break;
					}
				}		
				i=g;
			}
		}
	}
	else
		printf("Bloco totalmente ocupado\n");
}

int check(List l, int h, int m){
	int aux_h, aux_m, i;
	while(l->previous!=NULL)
		l=l->previous;
	if (l->next != NULL)
		l=l->next;
	while(l->next!=NULL){
		aux_h=l->horas;
		aux_m=l->minutos;

		for (i=0; i<l->blocos; i++){
			if (h == aux_h && m == aux_m)
				return 0;
			ajustar(&aux_h,&aux_m);
		}
		l=l->next;
	}

	aux_h=l->horas;
	aux_m=l->minutos;

	for (i=0; i<l->blocos; i++){
		if (h == aux_h && m == aux_m)
			return 0;
		ajustar(&aux_h,&aux_m);
	}

	return 1;
}
