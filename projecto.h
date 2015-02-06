#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Data{
	int dia,mes,ano;
}data;

typedef struct Node* List;
typedef struct Node{
	int id;
	int horas, minutos;								
	int sala, blocos;
	char nome_reserva[100];
	data data;
	struct Node* next;
	struct Node* previous;
} List_node;

typedef struct Node2* List2;
typedef struct Node2{
	int id;
	int horas, minutos;
	int sala;
	char nome_pre[100];
	data data;
	struct Node2* next;
	struct Node2* previous;
}List2_Node2;



List cria_lista(int sala,int dia, int mes, int ano);
void nova_entrada(List l, int h, int m, int blocos);
void save_data(List l);
List load_data(int sala,int dia, int mes, int ano);
int check(List l, int h, int m);
void check_do(List l, int h, int m, int blocos);
void imprimir_reservas();
void ajustar(int *h, int *m);
void cancelar_reserva();
void save_reserva_cancelada(List l);
int load_id();
void save_id(List l);
int procura_id(int id);
int destroylists(List l);
List loadallreservations(int sala);
List cria_listainteira(int sala);


int search_id(int id);
void turntoreservations(int sala,int dia, int mes, int ano, int h, int m, int blocos);
void load_pre(List2 l);
List2 cria_pre_lista(int sala, int dia, int mes, int ano, int h, int m);
void nova_prereserva(List2 l, char* a);
void save_pre(List2 l);
void save_id2(List2 l);
void save_prereserva_cancelada(List2 l, char nome[]);
void cancelar_prereserva();
int destroylists2(List2 l);

int compara_data(data d1, data d2);
void printall();
List2 cria_listapre(int sala);
List2 loadallreservations2(int sala);
List loadallnome(char nome[]);
List cria_listanome(char nome[]);
List2 loadallnome2(char nome[]);
List2 cria_listanome2(char nome[]);
void marcacao();
void pre_marcacao();
void printall();
void printall2();
