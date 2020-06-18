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
char **llenadoTablero(char **tablero);//Función que permite la introducción de los barcos de cada jugador al tablero

int main(){
	int continuar;
	printf("\t\t\tBienvenido a Batalla Naval\n\n");
	system("pause");
	system("cls");
	do{
		continuar=menuDeSeleccion();//Menu se despliega a menos que se retorne el valor 5, que corresponde a la opción de salida
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
	cin>>opcion;//Se lee el dato que brinde el usuario para posteriormente desplegar el resultado correspondiente
	switch(opcion){
		case 1:
			system("pause");
			system("cls");
			interfazDeJuego();//se da inicio al juego
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
		default://En caso de introducir un dato no valido se vuelve a solicitar al usuario el dato
			printf("\nEsa no es una opci%cn\n", 162);
			system("pause");
			system("cls");
			break;					
	}//Fin del switch
	return opcion;//Se retorna la opción para que de haber seleccionado 5 concluya el programa
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
				if(!inicializador1){//En caso de que el inicializador no se haya activado, el jugador deberá de llenar su tablero con sus respectivos barcos
					tableroJugador1=llenadoTablero(tableroJugador1);
				}//Fin del if
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
				if(!inicializador2){//En caso de que el inicializador no se haya activado, el jugador deberá de llenar su tablero con sus respectivos barcos
					tableroJugador2=llenadoTablero(tableroJugador2);
				}//Fin del if
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
	}while(jugador[0].puntaje!=25 || jugador[0].puntaje!=25);//Fin del do while
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

char **llenadoTablero(char**tablero){
	char coordenadaX;
	int disposicion, coordenadaY;
	bool validacion, validacionCoordenada;
	printf("\nAcomoda los barcos de 2 casillas '<>' donde quieras");//Se le solicita al usuario que decida las coordenadas para cada tipo de barco
	for(int i=0;i<3;i++){
		validacion=false;
		while(!validacion){//Mientras el usuario no ingresé una respuesta valida, se le seguirá solicitando el dato
			printf("\nSelecciona la dispocisi%cn del barco %d:", 162, i+1);//Se le pregunta al usuario si desea acomodar su barco horizontal o verticalmente
			printf("\n1.-Vertical");
			printf("\n2.-Horizontal");
			printf("\nSelecciona una opci%cn: \n", 162);
			cin>>disposicion;
			switch(disposicion){
				case 1:
					validacionCoordenada=false;//Se pone en false el validador para que se valide hasta que se de un resultado correcto
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena alfabetica del eje x donde se posiconar%c: ", 160);//Se le solicita al usuario una coordenada para posicionar su barco
						cin>>coordenadaX;
						if(coordenadaX>=97 && coordenadaX<117){
							validacionCoordenada=true;//Se rompe el while, pues el valor dado es valido
						}//Fin del if
						else{
							printf("\nDa una coordenada entre a y t\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else	
					}//Fin del while
					validacionCoordenada=false;//Se vuelve a negar para la validación de la siguiente variable
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena num%crica del eje y donde se posiconar%c: ", 130, 160);//Se le solicita al usuario una coordenada en el eje y para posicionar su barco
						cin>>coordenadaY;
						if(coordenadaY>=0 && coordenadaY<10){
							validacionCoordenada=true;
						}//Fin del if
						else{
							printf("\nDa una coordenada entre 0 y 9\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else
					}//Fin del while
					//Se posiciona el objeto en las coordenadas dadas
					for(int i=0;i<10;i++){
						for(int j=0;j<20;j++){
							if(i==coordenadaY && j==coordenadaX-97 && tablero[i][j]==-79){
								if(coordenadaY==9 && tablero[i-1][j]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=94;
									tablero[i-1][j]=94;	
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i+1][j]==-79){
									tablero[i][j]=94;
									tablero[i+1][j]=94;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del else
							}//Fin del if
						}//Fin del for
					}//Fin del for
					break;
				case 2:
					validacionCoordenada=false;//Se pone en false el validador para que se valide hasta que se de un resultado correcto
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena alfabetica del eje x donde se posicionar%c: ", 160);//Se le solicita al usuario una coordenada para posicionar su barco
						fflush(stdin);
						cin>>coordenadaX;
						if(coordenadaX>=97 && coordenadaX<117){
							validacionCoordenada=true;//Se rompe el while, pues el valor dado es valido
						}//Fin del if
						else{
							printf("\nDa una coordenada entre a y t\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else	
					}//Fin del while
					validacionCoordenada=false;//Se vuelve a negar para la validación de la siguiente variable
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena num%crica del eje y donde se posiconar%c: ", 130, 160);//Se le solicita al usuario una coordenada en el eje y para posicionar su barco
						cin>>coordenadaY;
						if(coordenadaY>=0 && coordenadaY<10){
							validacionCoordenada=true;
						}//Fin del if
						else{
							printf("\nDa una coordenada entre 0 y 9\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else
					}//Fin del while
					//Se posiciona el objeto en las coordenadas dadas
					for(int i=0;i<10;i++){
						for(int j=0;j<20;j++){
							if(i==coordenadaY && j==coordenadaX-97 && tablero[i][j]==-79){
								if(coordenadaX==116 && tablero[i][j-1]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=62;
									tablero[i][j-1]=60;	
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i][j+1]==-79){
									tablero[i][j]=60;
									tablero[i][j+1]=62;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}
							}//Fin del if
						}//Fin del for
					}//Fin del for
					break;
				default:
					printf("\nSelecciona una opcion valida\n");//Se le seguirán solicitando los datos al usuario hasta que sean correctos
					break;		
			}//Fin del switch	
			if(!validacion){
				printf("\nEn esas coordenadas ya hay parte de un barco\n");
			}//Fin del if
		}//Fin del while			
	}//Fin del for
	printf("\nAcomoda los barcos de 3 casillas '<=>' donde quieras");//Aquí se acomodan los barcos de 3 casillas
	for(int i=0;i<2;i++){
		validacion=false;
		while(!validacion){//Mientras el usuario no ingresé una respuesta valida, se le seguirá solicitando el dato
			printf("\nSelecciona la dispocisi%cn del barco %d:", 162, i+1);//Se le pregunta al usuario si desea acomodar su barco horizontal o verticalmente
			printf("\n1.-Vertical");
			printf("\n2.-Horizontal");
			printf("\nSelecciona una opci%cn: \n", 162);
			cin>>disposicion;
			switch(disposicion){
				case 1:
					validacionCoordenada=false;//Se pone en false el validador para que se valide hasta que se de un resultado correcto
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena alfabetica del eje x donde se posiconar%c: ", 160);//Se le solicita al usuario una coordenada para posicionar su barco
						cin>>coordenadaX;
						if(coordenadaX>=97 && coordenadaX<117){
							validacionCoordenada=true;//Se rompe el while, pues el valor dado es valido
						}//Fin del if
						else{
							printf("\nDa una coordenada entre a y t\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else	
					}//Fin del while
					validacionCoordenada=false;//Se vuelve a negar para la validación de la siguiente variable
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena num%crica del eje y donde se posiconar%c: ", 130, 160);//Se le solicita al usuario una coordenada en el eje y para posicionar su barco
						cin>>coordenadaY;
						if(coordenadaY>=0 && coordenadaY<10){
							validacionCoordenada=true;
						}//Fin del if
						else{
							printf("\nDa una coordenada entre 0 y 9\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else
					}//Fin del while
					//Se posiciona el objeto en las coordenadas dadas
					for(int i=0;i<10;i++){
						for(int j=0;j<20;j++){
							if(i==coordenadaY && j==coordenadaX-97 && tablero[i][j]==-79){
								if(coordenadaY>7 &&coordenadaY<=9 && tablero[i-1][j]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=94;
									tablero[i-1][j]=94;
									tablero[i-2][j]=94;	
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i+1][j]==-79){
									tablero[i][j]=94;
									tablero[i+1][j]=94;
									tablero[i+2][j]=94;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del else
							}//Fin del if
						}//Fin del for
					}//Fin del for
					break;
				case 2:
					validacionCoordenada=false;//Se pone en false el validador para que se valide hasta que se de un resultado correcto
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena alfabetica del eje x donde se posicionar%c: ", 160);//Se le solicita al usuario una coordenada para posicionar su barco
						fflush(stdin);
						cin>>coordenadaX;
						if(coordenadaX>=97 && coordenadaX<117){
							validacionCoordenada=true;//Se rompe el while, pues el valor dado es valido
						}//Fin del if
						else{
							printf("\nDa una coordenada entre a y t\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else	
					}//Fin del while
					validacionCoordenada=false;//Se vuelve a negar para la validación de la siguiente variable
					while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
						printf("Dime la coordena num%crica del eje y donde se posiconar%c: ", 130, 160);//Se le solicita al usuario una coordenada en el eje y para posicionar su barco
						cin>>coordenadaY;
						if(coordenadaY>=0 && coordenadaY<10){
							validacionCoordenada=true;
						}//Fin del if
						else{
							printf("\nDa una coordenada entre 0 y 9\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
						}//Fin del else
					}//Fin del while
					//Se posiciona el objeto en las coordenadas dadas
					for(int i=0;i<10;i++){
						for(int j=0;j<20;j++){
							if(i==coordenadaY && j==coordenadaX-97 && tablero[i][j]==-79){
								if(coordenadaX>114 && coordenadaX<=116 && tablero[i][j-1]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=62;
									tablero[i][j-1]=61;
									tablero[i][j-2]=60;	
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i][j+1]==-79){
									tablero[i][j]=60;
									tablero[i][j+1]=61;
									tablero[i][j+2]=62;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}
							}//Fin del if
						}//Fin del for
					}//Fin del for
					break;
				default:
					printf("\nSelecciona una opcion valida\n");//Se le seguirán solicitando los datos al usuario hasta que sean correctos
					break;		
			}//Fin del switch	
			if(!validacion){
				printf("\nEn esas coordenadas ya hay parte de un barco\n");
			}//Fin del if
		}//Fin del while			
	}//Fin del for
	return tablero;//se retorna el tablero con los nuevos valores
}//Fin de la función
