#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;

struct EST_jugadores{//Estructura en que se almacenan los datos de un jugador
	char nombre[80];
	int puntaje;
	int tiempoDeJuego;
	int id;
};

struct EST_archivoDeGuardado{//Esctructura en que se almacenan los valores de la partida guardada
	EST_jugadores jugador[2];
	int contadorTurno;
	char tableroJugador1[10][20];
	char tableroJugador2[10][20];
	char tableroDeAtaqueJugador1[10][20];
	char tableroDeAtaqueJugador2[10][20];
	bool inicializador1, inicializador2, atacado;
	double tiempo;
};

struct EST_records{//Estructura en que se guardan los records de los jugadores que han usado el programa
	char nombre[80];
	int puntuacion;
	double tiempoSegundos;
};

int menuDeSeleccion();//Función que despliega el menú a base de un switch para la selección de opciones que ofrece el programa
void interfazDeJuego(bool guardado);//Función que despliega la interfaz con la que el jugador ha de interactuar
void inicializacionDeTableros(char tableroJugador[10][20]);//Función que crea una martriz con tableros para que estos sean llenados por el usuario con los botes correspondientes
void llenadoTablero(char tablero[10][20]);//Función que permite la introducción de los barcos de cada jugador al tablero
void desplegarAyuda();//Funcion que se encarga de desplegar un instructivo para el manejo del programa
void ataqueAlEnemigo(char tableroDeAtaque[10][20], char tableroEnemigo[10][20], EST_jugadores *puntaje, int numeroDeJugador, bool *atacado);//Función encargada de direccionar los ataques del jugador al contricante
void mostrarTablero(char tablero[10][20]);//Función encargada de desplegar el tablero
void lecturaGuardado(EST_archivoDeGuardado registro);//Funcion que guarda los datos 
EST_archivoDeGuardado cambiarGuardado(EST_archivoDeGuardado registro);//Funcion que sobreescribe los datos
void imprimirRecords();//muestra los records
void registroRecords(char nombre[80], int record, int tiempo);//Guardar los records
void ordenarRecords();//ondena los records de la lista
double contabilizarTiempo(double tiempoInicial, double tiempoFinal, double tiempoAcomulado);//Funcion para transformar a segundos el tiempo

int main(){
	int continuar;
	printf("\t\t\t\t   Bienvenido a Batalla Naval\n\n\n");
	printf("\t\t\t\t                ________               \n");
	printf("\t\t\t\t               ||       \\             \n");
	printf("\t\t\t\t               ||        \\            \n");
	printf("\t\t\t\t               ||        /           \n");
	printf("\t\t\t\t               ||_______/            \n");
	printf("\t\t\t\t               ||             \n");
	printf("\t\t\t\t_______________||________________\n");
	printf("\t\t\t\t\\                               /\n");
	printf("\t\t\t\t~\\_____O_____O_____O_____O_____/~~~~~~~~~~\n");
	printf("\t\t\t\t  \\___________________________/\n");
	printf("\t\t\t\t   \\_________________________/\n\n\n");
	system("pause");
	system("cls");
	do{
		continuar=menuDeSeleccion();//Menu se despliega a menos que se retorne el valor 5, que corresponde a la opción de salida
	} while(continuar!=5);//Fin del do while
	return 0;
}//Fin de la función

int menuDeSeleccion(){
	int opcion=0;
	bool guardado=false;
	printf("\t\tMen%c\n", 163);//Menú con las opciones que ofrece el juego
	printf("\t\n1.-Iniciar nueva partida");
	printf("\t\n2.-Abrir partida guardada");
	printf("\t\n3.-Records");
	printf("\t\n4.-Ayuda");
	printf("\t\n5.-Salir");
	printf("\t\nEscoja una opci%cn:\n\n", 162);
	fflush(stdin);
	opcion=0;
	scanf("%d", &opcion);//Se lee el dato que brinde el usuario para posteriormente desplegar el resultado correspondiente
	switch(opcion){
		case 1:
			system("pause");
			system("cls");
			interfazDeJuego(guardado);//se da inicio al juego
			system("pause");
			system("cls");
			break;
		case 2:
			system("pause");
			system("cls");
			guardado=true;
			interfazDeJuego(guardado);//se da inicio al juego con el guardado activado
			system("pause");
			system("cls");
			break;
		case 3:
			imprimirRecords();
			system("pause");
			system("cls");
			break;
		case 4:
			system("pause");
			system("cls");
			desplegarAyuda();
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

void interfazDeJuego(bool guardado){
	//Se inicializan las variables básicas 
	EST_archivoDeGuardado registro, archivoGuardado;
	char tableroJugador1[10][20], tableroJugador2[10][20], tableroDeAtaqueJugador1[10][20], tableroDeAtaqueJugador2[10][20], respuesta;
	int contadorTurno;
	double tiempoInicial, tiempoFinal, tiempoAcomulado, tiempoTotal;
	bool inicializador1, inicializador2, atacado, final;
	//inicializacion de las matrices de guardado, para evitar errores
	inicializacionDeTableros(registro.tableroJugador1);
	inicializacionDeTableros(registro.tableroJugador2);
	inicializacionDeTableros(registro.tableroDeAtaqueJugador1);
	inicializacionDeTableros(registro.tableroDeAtaqueJugador2);
	//Se inicializa en 0 el archivo de guardado
	inicializacionDeTableros(archivoGuardado.tableroJugador1);
	inicializacionDeTableros(archivoGuardado.tableroJugador2);
	inicializacionDeTableros(archivoGuardado.tableroDeAtaqueJugador1);
	inicializacionDeTableros(archivoGuardado.tableroDeAtaqueJugador2);
	final=false;//la partida se mantendrá activa a menos que el jugador gane el juego o indique lo contrario
	EST_jugadores jugador[2];//Se crea una estructura de tipo EST_jugadores para guardar los datos de cada jugador
	if(!guardado){//Si se inicia una partida sin datos guardados, se restablecen los valores iniciales
		tiempoInicial=clock(); //Se toma la hora de comienzo del juego para su posterior contabilizacion
		tiempoAcomulado=0; //iguala el tiempo contado a 0 por ser una nueva partida
		contadorTurno=1;//Se establece el contador de turno en 1 para que el turno sea del jugador 1
		inicializador1=false;//Se establecen los inicializadores de partida en false para que los jugadores acomoden sus barcos antes de empezar a jugar
		inicializador2=false;
		atacado=false;
		for(int i=0;i<2;i++){//Se capturam los nombres de los dos jugadores 
			printf("\tInformaci%cn Jugador %d\n\n", 162, i+1);
			printf("\nDeme su nombre de usuario: \n");
			cin>>jugador[i].nombre;
			system("pause");
			system("cls");
		}//Fin del for
		jugador[0].puntaje=0;//Se inicializan los puntos de cada jugador en 0
		jugador[1].puntaje=0;
		inicializacionDeTableros(tableroJugador1);//Se inicializa el tablero para el jugador 1
		inicializacionDeTableros(tableroJugador2);//Se inicializa el tablero para el jugador 2 
		inicializacionDeTableros(tableroDeAtaqueJugador1);//Se inicializa el tablero el jugador 1
		inicializacionDeTableros(tableroDeAtaqueJugador2);//Se inicializa el tablero para el jugador 2	
	}//Fin del if
	else{//Si se inicia una partida con datos guardados, se establecen los valores previos
		tiempoInicial=clock(); //Se toma la hora de comienzo del juego para su posterior contabilizacion
		//aqui no se iguala el tiempo acomulado a 0, ya que el tiempo acomulado se extrae del archivo de guardado
		jugador[0].puntaje=0;//Se inicializan los puntos de cada jugador en 0
		jugador[1].puntaje=0;
		inicializacionDeTableros(tableroJugador1);//Se inicializa el tablero para el jugador 1
		inicializacionDeTableros(tableroJugador2);//Se inicializa el tablero para el jugador 2 
		inicializacionDeTableros(tableroDeAtaqueJugador1);//Se inicializa el tablero el jugador 1
		inicializacionDeTableros(tableroDeAtaqueJugador2);//Se inicializa el tablero para el jugador 2		
		archivoGuardado=cambiarGuardado(archivoGuardado);
		jugador[0]=archivoGuardado.jugador[0];
		jugador[1]=archivoGuardado.jugador[1];
		for(int i=0;i<10;i++){
			for(int j=0;j<20;j++){
				tableroJugador1[i][j]=archivoGuardado.tableroJugador1[i][j];
				tableroJugador2[i][j]=archivoGuardado.tableroJugador2[i][j];
				tableroDeAtaqueJugador1[i][j]=archivoGuardado.tableroDeAtaqueJugador1[i][j];
				tableroDeAtaqueJugador2[i][j]=archivoGuardado.tableroDeAtaqueJugador2[i][j];
			}//Fin del for
		}//Fin del for
		inicializador1=archivoGuardado.inicializador1;
		inicializador2=archivoGuardado.inicializador2;
		atacado=archivoGuardado.atacado;
		contadorTurno=archivoGuardado.contadorTurno;
		tiempoAcomulado=archivoGuardado.tiempo;
	}//Fin del else
	do{
		switch(contadorTurno){
			case 1:
				printf("\t\t\tTablero jugador 1:\n\n");
				printf("Tablero: \t\t\t\t\tPuntos: %d\n", jugador[0].puntaje);
				mostrarTablero(tableroJugador1);//Se despliega el tablero del jugador
				if(!inicializador1){//En caso de que el inicializador no se haya activado, el jugador deberá de llenar su tablero con sus respectivos barcos
					system("pause");
					system("cls");
					printf("Jugador 2, deja el ordenador al jugador 1 para que acomode sus barcos\n");
					system("pause");
					system("cls");				
					printf("Disposici%cn de barcos jugador 1: \n", 162);
					llenadoTablero(tableroJugador1);//Se modifica la disposición de los barcos dentro de la función
					system("pause");
					system("cls");
					printf("Ahora deja el computador a tu contrincante\n");
					printf("Ser%c m%cs divertido si no ves las posiciones de tu contrincante\n", 160, 160);
				}//Fin del if
				inicializador1=true;//Se activa hasta que ambos hayan terminado de acomodar su barco
				system("pause");
				system("cls");
				if(inicializador1 && inicializador2){//si los jugadores terminaron de acomodar sus barcos, pueden proceder a atacar
					printf("Puntos jugador 1: %d\n\n", jugador[0].puntaje);
					mostrarTablero(tableroDeAtaqueJugador1);
					ataqueAlEnemigo(tableroDeAtaqueJugador1, tableroJugador2, jugador, 1, &atacado);//Se despliega la funcion en que se introducen las coordenadas de ataque al enemigo
					system("pause");
					system("cls");
					mostrarTablero(tableroDeAtaqueJugador1);//Se despliega el tablero con los ataques efectuados
					system("pause");
					system("cls");
					if(jugador[0].puntaje!=25){
						printf("%cDeseas guardar partida y salir? (S para salir y guardar, cualquier otro caracter para continuar)\n\n", 168);
						fflush(stdin);
						scanf("%c", &respuesta);
						if(respuesta=='S'){
							
							guardado=true;
							final=true;
							
							
							tiempoFinal=clock();//se detiene el conteo del tiempo
							registro.tiempo+=contabilizarTiempo(tiempoInicial,tiempoFinal, tiempoAcomulado);
							
							//se guardan los datos de la partida en un struct para un manejo mas sencillo
							registro.jugador[0]=jugador[0];
							registro.jugador[1]=jugador[1];
							for(int i=0;i<10;i++){
							for(int j=0;j<20;j++){
								registro.tableroJugador1[i][j]=tableroJugador1[i][j];
								registro.tableroJugador2[i][j]=tableroJugador2[i][j];
								registro.tableroDeAtaqueJugador1[i][j]=tableroDeAtaqueJugador1[i][j];
								registro.tableroDeAtaqueJugador2[i][j]=tableroDeAtaqueJugador2[i][j];
								}//Fin del for
							}//Fin del for
							registro.inicializador1=inicializador1;
							registro.inicializador2=inicializador2;
							registro.atacado=atacado;
							registro.contadorTurno=2;
							//se manda este struct a la funcion de guardado
							lecturaGuardado(registro);
							break;
						}
						system("pause");
						system("cls");
						printf("\n\nAhora deja el computador a tu contrincante\n\n");
						system("pause");
						system("cls");
					}//Fin del if
				}//Fin del if
				contadorTurno++;//Si termina el turno del jugador1, se aumenta el contador para que siga el jugador 2
				break;
			case 2:
				printf("\t\t\tTablero jugador 2:\n\n");
				printf("Tablero: \t\t\t\t\tPuntos: %d\n", jugador[1].puntaje);
				mostrarTablero(tableroJugador2);//Se despliega el tablero del juhador 2
				if(!inicializador2){//En caso de que el inicializador no se haya activado, el jugador deberá de llenar su tablero con sus respectivos barcos
					system("pause");
					system("cls");
					printf("Disposici%cn de barcos jugador 2: \n", 162);
					llenadoTablero(tableroJugador2);
					system("pause");
					system("cls");
					printf("Ahora deja el computador a tu contrincante\n");
				}//Fin del if
				system("pause");
				system("cls");
				if(inicializador1 && inicializador2){//si los jugadores terminaron de acomodar sus barcos, pueden proceder a atacar
					printf("Puntos jugador 2: %d\n\n", jugador[1].puntaje);
					printf("Selecciona la coordenada para atacar jugador 2:\n");
					mostrarTablero(tableroDeAtaqueJugador2);
					ataqueAlEnemigo(tableroDeAtaqueJugador2, tableroJugador1, jugador, 2, &atacado);//Se despliega la funcion en que se introducen las coordenadas de ataque al enemigo
					system("pause");
					system("cls");
					mostrarTablero(tableroDeAtaqueJugador2);//Se despliega el tablero con los ataques efectuados
					system("pause");
					system("cls");
					if(jugador[1].puntaje!=25){
						printf("%cDeseas guardar partida y salir? (S para salir y guardar, cualquier otro caracter para continuar)\n\n", 168);
						fflush(stdin);
						scanf("%c", &respuesta);
						if(respuesta=='S'){
							guardado=true;
							final=true;
							
							tiempoFinal=clock();//se detiene el conteo del tiempo
							registro.tiempo+=contabilizarTiempo(tiempoInicial,tiempoFinal, tiempoAcomulado);
							
							//se guardan los datos de la partida en un struct para un manejo mas sencillo
							registro.jugador[0]=jugador[0];
							registro.jugador[1]=jugador[1];
							for(int i=0;i<10;i++){
								for(int j=0;j<20;j++){
									registro.tableroJugador1[i][j]=tableroJugador1[i][j];
									registro.tableroJugador2[i][j]=tableroJugador2[i][j];
									registro.tableroDeAtaqueJugador1[i][j]=tableroDeAtaqueJugador1[i][j];
									registro.tableroDeAtaqueJugador2[i][j]=tableroDeAtaqueJugador2[i][j];
								}//Fin del for
							}//Fin del for
							registro.inicializador1=inicializador1;
							registro.inicializador2=inicializador2;
							registro.atacado=atacado;
							registro.contadorTurno=1;
							//se manda este struct a la funcion de guardado
							lecturaGuardado(registro);
							
							break;
						}//Fin del if
						system("pause");
						system("cls");
						printf("Ahora deja el computador a tu contrincante\n\n");
						system("pause");
						system("cls");
					}//Fin del if
				}//Fin del if
				inicializador2=true;//Se activa hasta que ambos hayan terminado de acomodar su barco
				contadorTurno--;//Si termina el turno del jugador1, se decrementa el contador para que siga el jugador 1
				break;	
		}//Fin del switch
	}while(jugador[0].puntaje!=25 && jugador[1].puntaje!=25 && !final);//Fin del do while
	if(jugador[0].puntaje==25){//Si cualquiera de los jugadores gana, se le felicita
		printf("Felicidades Jugador 1, ha ganado\n");
		
		tiempoFinal=clock();//se detiene el conteo del tiempo
		tiempoTotal=contabilizarTiempo(tiempoInicial,tiempoFinal, tiempoAcomulado);
		registroRecords(jugador[0].nombre, jugador[0].puntaje, tiempoTotal);
		registroRecords(jugador[1].nombre, jugador[1].puntaje, tiempoTotal);
		ordenarRecords();
	}//Fin del if
	if(jugador[1].puntaje==25){
		printf("Felicidades Jugador 2, ha ganado\n");
		
		tiempoFinal=clock();//se detiene el conteo del tiempo
		tiempoTotal=contabilizarTiempo(tiempoInicial,tiempoFinal, tiempoAcomulado);
		registroRecords(jugador[0].nombre, jugador[0].puntaje, tiempoTotal);
		registroRecords(jugador[1].nombre, jugador[1].puntaje, tiempoTotal);
		ordenarRecords();
	}//Fin del if
}//Fin de la función

void mostrarTablero(char tablero[10][20]){
	printf("\n  ");
	for(int i=97;i<117;i++){
		printf("%c", i);
	}//Fin del for
	printf("\n");
	for(int i=0;i<10;i++){//Se despliega el tablero con los botes del jugador
		printf("%d ", i);
		for(int j=0;j<20;j++){
			printf("%c", tablero[i][j]);
		}//Fin del for
		printf("\n");
	}//fin del for
}//Fin de la función
void inicializacionDeTableros(char tableroJugador[10][20]){
	for(int i=0;i<10;i++){//Se llenan los tableros con las textura base
		for(int j=0;j<20;j++){
			tableroJugador[i][j]=177;
		}//Fin del for
	}//fin del for
}//Fin de la función

void llenadoTablero(char tablero[10][20]){
	char coordenadaX;
	int coordenadaY, disposicion;
	bool validacion, validacionCoordenada;
	printf("\nAcomoda los barcos de 2 casillas '<>' donde quieras\n\n");//Se le solicita al usuario que decida las coordenadas para cada tipo de barco
	for(int i=0;i<3;i++){
		validacion=false;
		while(!validacion){//Mientras el usuario no ingresé una respuesta valida, se le seguirá solicitando el dato
			mostrarTablero(tablero);//Se despliega el tablero del jugador
			printf("\nSelecciona la dispocisi%cn del barco %d:", 162, i+1);//Se le pregunta al usuario si desea acomodar su barco horizontal o verticalmente
			printf("\n1.-Vertical");
			printf("\n2.-Horizontal");
			printf("\nSelecciona una opci%cn: \n", 162);
			disposicion=0;
			fflush(stdin);
			scanf("%d", &disposicion);
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
						coordenadaY=-1;
						fflush(stdin);
						scanf("%d", &coordenadaY);
						if(coordenadaY>=0 && coordenadaY<=9){
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
					if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
						printf("\nEn esas coordenadas ya hay parte de un barco\n");
					}//Fin del if
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
						coordenadaY=-1;
						fflush(stdin);
						scanf("%d", &coordenadaY);
						if(coordenadaY>=0 && coordenadaY<=9){
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
					if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
						printf("\nEn esas coordenadas ya hay parte de un barco\n");
					}//Fin del if
					break;
				default:
					printf("\nSelecciona una opcion valida\n");//Se le seguirán solicitando los datos al usuario hasta que sean correctos
					break;		
			}//Fin del switch	
			system("pause");
			system("cls");
		}//Fin del while			
	}//Fin del for
	printf("\nAcomoda los barcos de 3 casillas '<=>' donde quieras\n\n");//Aquí se acomodan los barcos de 3 casillas
	for(int i=0;i<2;i++){
		validacion=false;
		while(!validacion){//Mientras el usuario no ingresé una respuesta valida, se le seguirá solicitando el dato
			mostrarTablero(tablero);//Se despliega el tablero del jugador
			printf("\nSelecciona la dispocisi%cn del barco %d:", 162, i+1);//Se le pregunta al usuario si desea acomodar su barco horizontal o verticalmente
			printf("\n1.-Vertical");
			printf("\n2.-Horizontal");
			printf("\nSelecciona una opci%cn: \n", 162);
			disposicion=0;
			fflush(stdin);
			scanf("%d", &disposicion);
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
						coordenadaY=-1;
						fflush(stdin);
						scanf("%d", &coordenadaY);
						if(coordenadaY>=0 && coordenadaY<=9){
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
								if(coordenadaY>7 &&coordenadaY<=9 && tablero[i-1][j]==-79 && tablero[i-2][j]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=94;
									tablero[i-1][j]=94;
									tablero[i-2][j]=94;	
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i+1][j]==-79 && tablero[i+2][j]==-79){
									tablero[i][j]=94;
									tablero[i+1][j]=94;
									tablero[i+2][j]=94;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del else
							}//Fin del if
						}//Fin del for
					}//Fin del for
					if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
						printf("\nEn esas coordenadas ya hay parte de un barco\n");
					}//Fin del if
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
						coordenadaY=-1;
						fflush(stdin);
						scanf("%d", &coordenadaY);
						if(coordenadaY>=0 && coordenadaY<=9){
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
								if(coordenadaX>114 && coordenadaX<=116 && tablero[i][j-1]==-79 && tablero[i][j-2]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=62;
									tablero[i][j-1]=61;
									tablero[i][j-2]=60;	
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i][j+1]==-79 && tablero[i][j+2]==-79){
									tablero[i][j]=60;
									tablero[i][j+1]=61;
									tablero[i][j+2]=62;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}
							}//Fin del if
						}//Fin del for
					}//Fin del for
					if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
						printf("\nEn esas coordenadas ya hay parte de un barco\n");
					}//Fin del if
					break;
				default:
					printf("\nSelecciona una opcion valida\n");//Se le seguirán solicitando los datos al usuario hasta que sean correctos
					break;		
			}//Fin del switch	
			system("pause");
			system("cls");
		}//Fin del while			
	}//Fin del for
	printf("\nAcomoda los barcos de 4 casillas '<==>' donde quieras\n\n");//Aquí se acomodan los barcos de 4 casillas
	for(int i=0;i<2;i++){
		validacion=false;
		while(!validacion){//Mientras el usuario no ingresé una respuesta valida, se le seguirá solicitando el dato
			mostrarTablero(tablero);//Se despliega el tablero del jugador
			printf("\nSelecciona la dispocisi%cn del barco %d:", 162, i+1);//Se le pregunta al usuario si desea acomodar su barco horizontal o verticalmente
			printf("\n1.-Vertical");
			printf("\n2.-Horizontal");
			printf("\nSelecciona una opci%cn: \n", 162);
			disposicion=0;
			fflush(stdin);
			scanf("%d", &disposicion);
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
						coordenadaY=-1;
						fflush(stdin);
						scanf("%d", &coordenadaY);
						if(coordenadaY>=0 && coordenadaY<=9){
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
								if(coordenadaY>6 &&coordenadaY<=9 && tablero[i-1][j]==-79 && tablero[i-2][j]==-79 && tablero[i-3][j]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=94;
									tablero[i-1][j]=94;
									tablero[i-2][j]=94;
									tablero[i-3][j]=94;	
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i+1][j]==-79 && tablero[i+2][j]==-79 && tablero[i+3][j]==-79){
									tablero[i][j]=94;
									tablero[i+1][j]=94;
									tablero[i+2][j]=94;
									tablero[i+3][j]=94;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del else
							}//Fin del if
						}//Fin del for
					}//Fin del for
					if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
						printf("\nEn esas coordenadas ya hay parte de un barco\n");
					}//Fin del if
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
						coordenadaY=-1;
						fflush(stdin);
						scanf("%d", &coordenadaY);
						if(coordenadaY>=0 && coordenadaY<=9){
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
								if(coordenadaX>113 && coordenadaX<=116 && tablero[i][j-1]==-79 && tablero[i][j-2]==-79 && tablero[i][j-3]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
									tablero[i][j]=62;
									tablero[i][j-1]=61;
									tablero[i][j-2]=61;	
									tablero[i][j-3]=60;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}//Fin del if
								else if(tablero[i][j+1]==-79 && tablero[i][j+2]==-79 && tablero[i][j+3]==-79){
									tablero[i][j]=60;
									tablero[i][j+1]=61;
									tablero[i][j+2]=61;
									tablero[i][j+3]=62;
									validacion=true;//Se rompe el while, pues el valor dado es valido
								}
							}//Fin del if
						}//Fin del for
					}//Fin del for
					if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
						printf("\nEn esas coordenadas ya hay parte de un barco\n");
					}//Fin del if
					break;
				default:
					printf("\nSelecciona una opcion valida\n");//Se le seguirán solicitando los datos al usuario hasta que sean correctos
					break;		
			}//Fin del switch	
			system("pause");
			system("cls");
		}//Fin del while			
	}//Fin del for
	printf("\nAcomoda el barco de 5 casillas '<===>' donde quieras\n\n");//Aquí se acomodan los barcos de 5 casillas
	validacion=false;
	while(!validacion){//Mientras el usuario no ingresé una respuesta valida, se le seguirá solicitando el dato
		mostrarTablero(tablero);//Se despliega el tablero del jugador
		printf("\nSelecciona la dispocisi%cn del barco:", 162);//Se le pregunta al usuario si desea acomodar su barco horizontal o verticalmente
		printf("\n1.-Vertical");
		printf("\n2.-Horizontal");
		printf("\nSelecciona una opci%cn: \n", 162);
		disposicion=0;
		fflush(stdin);
		scanf("%d", &disposicion);
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
					coordenadaY=-1;
					fflush(stdin);
					scanf("%d", &coordenadaY);
					if(coordenadaY>=0 && coordenadaY<=9){
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
							if(coordenadaY>5 &&coordenadaY<=9 && tablero[i-1][j]==-79 && tablero[i-2][j]==-79 && tablero[i-3][j]==-79 && tablero[i-4][j]==-79){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
								tablero[i][j]=94;
								tablero[i-1][j]=94;
								tablero[i-2][j]=94;
								tablero[i-3][j]=94;	
								tablero[i-4][j]=94;
								validacion=true;//Se rompe el while, pues el valor dado es valido
							}//Fin del if
							else if(tablero[i+1][j]==-79 && tablero[i+2][j]==-79 && tablero[i+3][j]==-79 && tablero[i+4][j]==-79){
								tablero[i][j]=94;
								tablero[i+1][j]=94;
								tablero[i+2][j]=94;
								tablero[i+3][j]=94;
								tablero[i+4][j]=94;
								validacion=true;//Se rompe el while, pues el valor dado es valido
							}//Fin del else
						}//Fin del if
					}//Fin del for
				}//Fin del for
				if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
					printf("\nEn esas coordenadas ya hay parte de un barco\n");
				}//Fin del if
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
					coordenadaY=-1;
					fflush(stdin);
					scanf("%d", &coordenadaY);
					if(coordenadaY>=0 && coordenadaY<=9){
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
							if(coordenadaX>112 && coordenadaX<=116 && tablero[i][j-1]==-79 && tablero[i][j-2]==-79 && tablero[i][j-3]==-79 && tablero[i][j-4]==-79 ){//Si la coordenada está en el borde inferior, se acomoda la continuación arriba
								tablero[i][j]=62;
								tablero[i][j-1]=61;
								tablero[i][j-2]=61;	
								tablero[i][j-3]=61;
								tablero[i][j-4]=60;
								validacion=true;//Se rompe el while, pues el valor dado es valido
							}//Fin del if
							else if(tablero[i][j+1]==-79 && tablero[i][j+2]==-79 && tablero[i][j+3]==-79 && tablero[i][j+4]==-79){
								tablero[i][j]=60;
								tablero[i][j+1]=61;
								tablero[i][j+2]=61;
								tablero[i][j+3]=61;
								tablero[i][j+4]=62;
								validacion=true;//Se rompe el while, pues el valor dado es valido
							}
						}//Fin del if
					}//Fin del for
				}//Fin del for
				if(!validacion){//Si no se valida la coordenada, se vuelve a solicitar 
					printf("\nEn esas coordenadas ya hay parte de un barco\n");
				}//Fin del if
				break;
			default:
				printf("\nSelecciona una opcion valida\n");//Se le seguirán solicitando los datos al usuario hasta que sean correctos
				break;		
		}//Fin del switch	
		system("pause");
		system("cls");
	}//Fin del while				
}//Fin de la función

void ataqueAlEnemigo(char tableroDeAtaque[10][20], char tableroEnemigo[10][20], EST_jugadores *puntaje,int numeroDeJugador, bool *atacado){
	char coordenadaX;
	int coordenadaY;
	bool validacionCoordenada, validacionAtaque;
	do{//Se repite el proceso mientras sea valido atacar
		system("pause");
		system("cls");
		printf("Selecciona la coordenada para atacar jugador %d\n", numeroDeJugador);
		printf("\t\t\t\tPuntaje jugador %d: %d\n\n", numeroDeJugador, puntaje[numeroDeJugador-1].puntaje);//Se despliega el tablero y el puntaje
		mostrarTablero(tableroDeAtaque);
		validacionAtaque=true;//se valida el ataque
		validacionCoordenada=false;
		while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
			printf("Dime la coordena alfabetica del eje x donde atacar%c: ", 160);//Se le solicita al usuario una coordenada para posicionar su barco
			fflush(stdin);
			scanf("%c", &coordenadaX);
			if(coordenadaX>=97 && coordenadaX<117){
				validacionCoordenada=true;//Se rompe el while, pues el valor dado es valido
			}//Fin del if
			else{
				printf("\nDa una coordenada entre a y t\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
			}//Fin del else	
		}//Fin del while
		validacionCoordenada=false;//Se vuelve a negar para la validación de la siguiente variable
		while(!validacionCoordenada){//Mientras el usuario no ingrese un valor valido, seguirá solicitándolo
			printf("Dime la coordena num%crica del eje y donde atacar%c: ", 130, 160);//Se le solicita al usuario una coordenada en el eje y para posicionar su barco
			coordenadaY=0;
			fflush(stdin);
			scanf("%d", &coordenadaY);
			if(coordenadaY>=0 && coordenadaY<=9){
				validacionCoordenada=true;
			}//Fin del if
			else{
				printf("\nDa una coordenada entre 0 y 9\n");//Se le seguirán solicitando datos al usuario pues las coordenadas no son validas
			}//Fin del else
		}//Fin del while
		for(int i=0;i<10;i++){
			for(int j=0;j<20;j++){
				if(i==coordenadaY && j==coordenadaX-97){
					if(tableroEnemigo[i][j]=='X' || tableroEnemigo[i][j]=='O'){//Si el ataque es en una zona que ya atacó, debe repetirlo
						printf("\nYa atacaste esa zona\n");
					}//Fin del if
					if(tableroEnemigo[i][j]==94 || tableroEnemigo[i][j]==60 || tableroEnemigo[i][j]==61 || tableroEnemigo[i][j]==62){//Si la coordenada coincide con la coordenada en que se encuentra un barco, se pone una X y se le suma un punto al jugador
						tableroDeAtaque[i][j]='X';
						tableroEnemigo[i][j]='X';
						puntaje[numeroDeJugador-1].puntaje++;
						printf("\nEnhorabuena, le has dado\n");
					}//Fin del if
					if(tableroEnemigo[i][j]==-79){//Se coloca un circulo si la zona en que ataca hay agua
						tableroDeAtaque[i][j]='O';
						tableroEnemigo[i][j]='O';
						validacionAtaque=false;//Si en esa zona hay agua, ya no puede atacar
						printf("\nNo le diste a nada\n");
					}//Fin del if
				}//Fin del if
			}//Fin del for
		}//Fin del for
	}while(validacionAtaque && puntaje[0].puntaje!=25 && puntaje[1].puntaje!=25);//Fin del do while
}

void desplegarAyuda(){
	fstream instructivo;//Se crea un archivo de la clase fsream
	instructivo.open("Ayuda.txt", ios::in);
	if (!instructivo) { //Se verifica si el archivo se puede abrir
		cout << " No se pudo abrir el archivo " << endl ;
		cin.get();
	}//fin del if
	char c;
	instructivo.get(c);
	while(!instructivo.eof()){//Se imprime el archivo a base de capturar los caracteres individuales
		cout<<c;	
		instructivo.get(c);
	}//Fin del while
	instructivo.close();
}//Fin de la función

void lecturaGuardado(EST_archivoDeGuardado registro){
	fstream archivo; //se crea un archivo de la clase fsream
	
	remove("partidaGuardada.dat");
	
	archivo.open("partidaGuardada.dat",ios::binary|ios::app);//se abre el archivo en modo de sobreescritura
	if(!archivo){//se verifica que el archivo exista
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}
	
	archivo.seekg((0)*sizeof(EST_archivoDeGuardado),ios::beg);
	archivo.write(reinterpret_cast<char*>(&registro), sizeof(EST_archivoDeGuardado));
	
	archivo.close();
}//Fin de la función

EST_archivoDeGuardado cambiarGuardado(EST_archivoDeGuardado registro){
	EST_archivoDeGuardado archivoGuardado;
	fstream archivo;
	archivo.open("partidaGuardada.dat",ios::binary|ios::in);
	if(!archivo){
		cout<<endl<<"Error de apertura"<<endl;
		exit(0);
	}//Fin del if
	
	/*while(!archivo.eof() && archivo.read(reinterpret_cast<char*>(&archivoGuardado), sizeof(EST_archivoDeGuardado))){
		registro=archivoGuardado;
	}//Fin del while*/
	
	archivo.seekp((0)*sizeof(EST_archivoDeGuardado),ios::beg);
	archivo.read(reinterpret_cast<char*>(&registro), sizeof(EST_archivoDeGuardado));
	archivo.close();
	
	return registro;
}//Fin de la función

void imprimirRecords(){
	ordenarRecords();
	
	fstream archivo; 
	archivo.open("records.txt",ios::in);
	if ( !archivo ) { // verifica la existencia del archivo
		cout << " No se pudo abrir el arcivo, puede que no haya records guardados " << endl;
		exit(0); // termina el programa
	}//Fin del if
	char nombre[80];
	int puntuacion;
	double tiempo;
	archivo.clear(); // restablece el eof para la sig entrada
	archivo.seekg( 0 ); // se mueve al inicio del archivo
	archivo >> nombre >> puntuacion >> tiempo;
	while( !archivo.eof() ) // iterar hasta fin de archivo
	{
		cout << "nombre :" << nombre << "	puntuacion :" << puntuacion << "	tiempo :" << tiempo <<endl;
		// mandamos el flujo de extraccion del archivo a las variables
		archivo >> nombre >> puntuacion >> tiempo;
	}//Fin del while
	archivo.close(); // cierra el archivo
}//Fin de la función

void registroRecords(char nombre[80], int record, int tiempo){
	fstream archivo;
	archivo.open("records.txt", ios::out|ios::app);
	if (!archivo){
		cerr << " No se pudo abrir el archivo " << endl ;
		exit(0);
	}//Fin del if
    archivo << nombre << " " << record << " " << tiempo << endl;
	archivo.close(); // cierra el archivo
}//Fin de la función

void ordenarRecords(){
	EST_records jugador[10], auxiliar;
	int contador=0;
	fstream archivo; // crea un objeto de tipo file-stream
	// abrimos el archivo en modo de lectura
	archivo.open("records.txt",ios::in);
	if ( !archivo ) { // verifica la existencia del archivo
		cerr << " No se pudo abrir el arcivo " << endl;
		exit(0);
	}//Fin del if
	
	
	while( !archivo.eof() ) // iterar hasta fin de archivo
	{
		archivo >> jugador[contador].nombre >> jugador[contador].puntuacion >> jugador[contador].tiempoSegundos;
		contador++;
	}//Fin del while
	contador--;
	archivo.close();
	
	for (int i=0; i<contador;i++) {
        for (int j=0; j<contador-1; j++) {
            if (jugador[j].puntuacion < jugador[i+1].puntuacion) {
            	auxiliar.puntuacion=jugador[j].puntuacion;
            	auxiliar.tiempoSegundos=jugador[j].tiempoSegundos;
            	strcpy(auxiliar.nombre,jugador[j].nombre);
                
                jugador[j].puntuacion=jugador[j+1].puntuacion;
                jugador[j].tiempoSegundos=jugador[j+1].tiempoSegundos;
                strcpy(jugador[j].nombre,jugador[j+1].nombre);
                
                jugador[j+1].puntuacion=auxiliar.puntuacion;
                jugador[j+1].tiempoSegundos=auxiliar.tiempoSegundos;
                strcpy(jugador[j+1].nombre,auxiliar.nombre);
            }//Fin del if
        }//Fin del for
    }//Fin del for
    
    remove("records.txt");
    
    archivo.open("records.txt", ios::out|ios::app);
	if (!archivo){
		cerr << " No se pudo abrir el archivo " << endl ;
		exit(0);
	}//Fin del if
	
	for(int i=0; i<contador; i++){
		archivo << jugador[i].nombre << " " << jugador[i].puntuacion << " " << jugador[i].tiempoSegundos << endl;
	}//Fin del for
    archivo.close();
}//Fin de la función

double contabilizarTiempo(double tiempoInicial,double tiempoFinal,double tiempoAcomulado){
	double tiempoTotal;
	
	tiempoTotal=(double(tiempoFinal-tiempoInicial)/CLOCKS_PER_SEC);
	tiempoTotal+=tiempoAcomulado;
	
	return(tiempoTotal);
}//Fin del for

