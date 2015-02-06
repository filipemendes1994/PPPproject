#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projecto.h"

int main(){
    system("clear"); 
    int x=0;
    printf("                                    MENU\n");
    printf("1: Reservar espaco\n2: Pre-reservar um espaco \n3: Cancelar uma reserva\n4: Cancelar uma pre-reserva\n5: Listar todas as reservas e pre-reservas, por sala\n6: Listar todas as reservas e pre-reservas, por nome\n7: Sair do programa\nEscolha: ");
    while(1){
        scanf("%d",&x);
        if(x==1){
            marcacao();
            printf("1: Reservar espaco\n2: Pre-reservar um espaco \n3: Cancelar uma reserva\n4: Cancelar uma pre-reserva\n5: Listar todas as reservas e pre-reservas, por sala\n6: Listar todas as reservas e pre-reservas, por nome\n7: Sair do programa\nEscolha: ");
        }
        else if(x==2){
            pre_marcacao();
            printf("1: Reservar espaco\n2: Pre-reservar um espaco \n3: Cancelar uma reserva\n4: Cancelar uma pre-reserva\n5: Listar todas as reservas e pre-reservas, por sala\n6: Listar todas as reservas e pre-reservas, por nome\n7: Sair do programa\nEscolha: ");
        }
        else if(x==3){
            cancelar_reserva();
            printf("1: Reservar espaco\n2: Pre-reservar um espaco \n3: Cancelar uma reserva\n4: Cancelar uma pre-reserva\n5: Listar todas as reservas e pre-reservas, por sala\n6: Listar todas as reservas e pre-reservas, por nome\n7: Sair do programa\nEscolha: ");
        }
        else if(x==4){
            cancelar_prereserva();
            printf("1: Reservar espaco\n2: Pre-reservar um espaco \n3: Cancelar uma reserva\n4: Cancelar uma pre-reserva\n5: Listar todas as reservas e pre-reservas, por sala\n6: Listar todas as reservas e pre-reservas, por nome\n7: Sair do programa\nEscolha: ");
        }
        else if(x==5){
            printall();
            printf("1: Reservar espaco\n2: Pre-reservar um espaco \n3: Cancelar uma reserva\n4: Cancelar uma pre-reserva\n5: Listar todas as reservas e pre-reservas, por sala\n6: Listar todas as reservas e pre-reservas, por nome\n7: Sair do programa\nEscolha: ");
        }
        else if(x==6){
            printall2();
            printf("1: Reservar espaco\n2: Pre-reservar um espaco \n3: Cancelar uma reserva\n4: Cancelar uma pre-reserva\n5: Listar todas as reservas e pre-reservas, por sala\n6: Listar todas as reservas e pre-reservas, por nome\n7: Sair do programa\nEscolha: ");
        } 
        else if(x==7)
            return 0;
        else
            main(); 
    }
    return 0;
}