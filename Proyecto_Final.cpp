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
char **inicializacionDeTableros(char **tableroJugador);//Función que crea una martriz con tableros para que estos sean llenados por el usuario con los botes correspondientes

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
	printf("\t\tMen%c\n", 163);//Menú con las opciones que ofrece el juego
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
			system("pause");
			system("cls");
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
	char **tableroJugador1, **tableroJugador2, **tableroDeAtaqueJugador1, **tableroDeAtaqueJugador2;
	int contadorTurno=1;
	bool inicializador1=false, inicializador2=false;
	EST_jugadores jugador[2];//Se crea una estructura de tipo EST_jugadores para guardar los datos de cada jugador
	for(int i=0;i<2;i++){//Se capturam los nombres de los dos jugadores 
		printf("\tInformaci%cn Jugador %d\n\n", 162, i+1);
		printf("\nDeme su nombre de usuario: \n");
		cin>>jugador[i].nombre;
		system("pause");
		system("cls");
	}//Fin del for
	jugador[0].puntaje=0;//Se inicializan los puntos de cada jugador en 0
	jugador[1].puntaje=0;
	tableroJugador1=inicializacionDeTableros(tableroJugador1);//Se inicializa el tablero para el jugador 1
	tableroJugador2=inicializacionDeTableros(tableroJugador2);//Se inicializa el tablero para el jugador 2 
	tableroDeAtaqueJugador1=inicializacionDeTableros(tableroDeAtaqueJugador1);//Se inicializa el tablero el jugador 1
	tableroDeAtaqueJugador2=inicializacionDeTableros(tableroDeAtaqueJugador2);//Se inicializa el tablero para el jugador 2
	do{
		switch(contadorTurno){
			case 1:
				printf("\t\t\tTablero jugador 1:\n\n");
				printf("Tablero:\n  ");
				for(int i=97;i<117;i++){
					printf("%c", i);
				}//Fin del for
				printf("\n");
				for(int i=0;i<10;i++){//Se despliega el tablero con los botes del jugador
					printf("%d ", i);
					for(int j=0;j<20;j++){
						printf("%c", tableroJugador1[i][j]);
					}//Fin del for
					printf("\n");
				}//fin del for
				inicializador1=true;//Se activa hasta que ambos hayan terminado de acomodar su barco
				system("pause");
				system("cls");
				if(inicializador1 && inicializador2){//si los jugadores terminaron de acomodar sus barcos, pueden proceder a atacar
					printf("Selecciona la coordenada para atacar jugador 1:\n  ");
					for(int i=97;i<117;i++){
						printf("%c", i);
					}//Fin del for
					printf("\n");
					for(int i=0;i<10;i++){//Se despliega el tablero de coordenadas de ataques
						printf("%d ", i);
						for(int j=0;j<20;j++){
							printf("%c", tableroDeAtaqueJugador1[i][j]);
						}//Fin del for
						printf("\n");
					}//fin del for
					system("pause");
					system("cls");
				}//Fin del if
				contadorTurno++;//Si termina el turno del jugador1, se aumenta el contador para que siga el jugador 2
				break;
			case 2:
				printf("\t\t\tTablero jugador 2:\n\n");
				printf("Tablero: \n  ");
				for(int i=97;i<117;i++){
					printf("%c", i);
				}//Fin del for
				printf("\n");
				for(int i=0;i<10;i++){//Se despliega el tablero con los botes del jugador
					printf("%d ", i);
					for(int j=0;j<20;j++){
						printf("%c", tableroJugador2[i][j]);
					}//Fin del for
					printf("\n");
				}//fin del for
				inicializador2=true;//Se activa hasta que ambos hayan terminado de acomodar su barco
				system("pause");
				system("cls");
				if(inicializador1 && inicializador2){//si los jugadores terminaron de acomodar sus barcos, pueden proceder a atacar
					printf("Selecciona la coordenada para atacar jugador 2:\n  ");
					for(int i=97;i<117;i++){
						printf("%c", i);
					}//Fin del for
					printf("\n");
					for(int i=0;i<10;i++){//Se despliega el tablero de coordenadas de ataques
						printf("%d ", i);
						for(int j=0;j<20;j++){
							printf("%c", tableroDeAtaqueJugador2[i][j]);
						}//Fin del for
						printf("\n");
					}//fin del for
					system("pause");
					system("cls");
				}//Fin del if
				contadorTurno--;//Si termina el turno del jugador1, se decrementa el contador para que siga el jugador 1
				break;	
		}//Fin del switch
	}while(jugador[0].puntaje!=8 || jugador[0].puntaje!=8);//Fin del do while
}//Fin de la función

char **inicializacionDeTableros(char **tableroJugador){
	//Se inicializa el tableros
	tableroJugador=(char**)malloc(10*sizeof(char**));
	for(int i=0;i<10;i++){
		*(tableroJugador+i)=(char*)malloc(20*sizeof(char*));
	}//Fin del for
	for(int i=0;i<10;i++){//Se llenan los tableros con las textura base
		for(int j=0;j<20;j++){
			tableroJugador[i][j]=177;
		}//Fin del for
	}//fin del for
	return tableroJugador;
}//Fin de la función
