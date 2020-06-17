#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

struct EST_jugadores{//Estructura en que se almacenan los datos de un jugador
	char nombre[80];
	int puntaje;
	int tiempoDeJuego;
};

int menuDeSeleccion();//Función que despliega el menú a base de un switch para la selección de opciones que ofrece el programa
void interfazDeJuego();//Función que despliega la interfaz con la que el jugador ha de interactuar
void manejoDeTableros();//

int main(){
	int continuar;
	printf("\t\t\tBienvenido a Batalla Naval\n\n");
	system("pause");
	system("cls");
	do{
		continuar=menuDeSeleccion();	
	} while(continuar!=5);//Fin del do while
	return 0;
}//Fin de la función

int menuDeSeleccion(){
	int opcion=0;
	printf("\t\tMen%c\n", 163);
	printf("\t\n1.-Iniciar nueva partida");
	printf("\t\n2.-Abrir partida guardada");
	printf("\t\n3.-Records");
	printf("\t\n4.-Ayuda");
	printf("\t\n5.-Salir");
	printf("\t\nEscoja una opci%cn:\n\n", 162);
	cin>>opcion;
	switch(opcion){
		case 1:
			system("pause");
			system("cls");
			interfazDeJuego();
			break;
		case 2:
			system("pause");
			system("cls");
			break;
		case 3:
			system("pause");
			system("cls");
			break;
		case 4:
			system("pause");
			system("cls");
			break;
		case 5:
			printf("\nGracias por usar el programa\n");
			system("pause");
			system("cls");
			break;
		default:
			printf("\nEsa no es una opci%cn\n", 162);
			system("pause");
			system("cls");
			break;					
	}//Fin del switch
	return opcion;
}//Fin de la función

void interfazDeJuego(){
	EST_jugadores jugador[2];
	for(int i=0;i<2;i++){
		printf("\tInformaci%cn Jugador %d\n\n", 162, i+1);
		printf("\nDeme su nombre de usuario: \n");
		cin>>jugador[i].nombre;
		system("pause");
		system("cls");
	}//Fin del for
}//Fin de la función

