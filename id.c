#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"

int procura_id(int id){
	int read_id;
	FILE *f;
	f = fopen("cancelamentos.txt", "r");
	if (f!=NULL){
		rewind(f);
		while(feof(f)==0){
			fscanf(f,"%d", &read_id);
			if (read_id == id){
				return 1;
			}
		}
	}
	return 0;
}

void save_id(List l){
    FILE *f;
    if(l->next!=NULL)
        l=l->next;
    
    f = fopen("id.txt","w");
    if(f!=NULL){
        rewind(f);
        fprintf(f,"%d", l->id);
        fclose(f);
    }
    else
        printf("Erro!\n");

}

int load_id(){
	int id=0;
	FILE *f;
	f=fopen("id.txt", "r");
	if (f!=NULL){
		rewind(f);
		fscanf(f,"%d",&id);
		fclose(f);
	}
	else
		printf("Erro!\n");
	return id;
}

int search_id(int id){
	int read_id=0;
	FILE *f;
	f=fopen("passagens.txt", "r");
	if (f!=NULL){
		rewind(f);
		while(feof(f)==0){
			fscanf(f,"%d", &read_id);
			if(read_id == id)
				return 1;
		}
	}
	return 0;
}

void save_id2(List2 l){
    FILE *f;
    while(l->next!=NULL)
        l=l->next;
    
    f = fopen("id.txt","w");
    if(f!=NULL){
        rewind(f);
        fprintf(f,"%d", l->id);
        fclose(f);
    }
}