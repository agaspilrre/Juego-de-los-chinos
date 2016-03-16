#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//declaro estructura que voy a necesitar
  typedef struct {
          
     char nombre[100];
     int apuesta;
     int num_dedos;     
  
  }JUGADOR; //el nombre de la estructura lo cambio con un typedef a JUGADOR

int pintar_menu();			//indico las cabeceras de las funciones
void funcion_jugar();
void ultima_jugada();


int main(int argc, char *argv[])
{
  
  
   
   	int opc;   //declaro variables que voy ha utilizar en el main
	
	do{
	opc=pintar_menu(); //llamo a la funcion pintar menu esta me devuelve un valor que se guarda en OPC
	
	switch(opc){
		
		case 1:
			funcion_jugar();//si opc vale uno llama a la funcion jugar
			break;
			
		case 2:
			ultima_jugada();// si opc vale dos llama a la funcion ultimajugada
			
	}
	
  }while(opc!=3);//condicion si opc es igual a 3 se sale del programa
	
  
  
  
  
  
  system("PAUSE");	
  return 0;
}


int pintar_menu(){
	int opcion;
	
	do{
	
	system("cls");
	printf("*************** MENU:***************\n");
	printf("1-Jugar\n");
	printf("2-Mostrar ultima partida\n");
	printf("3-Salir\n");
	fflush(stdin);scanf("%i",&opcion);
	
	
    }while(opcion<1||opcion>3);//pintamos el menu y lo condicionamos para que nos meta numeros del 1 al 3
    
    return opcion; //le devolvemos a main la opcion que hemos introducido
 }







void funcion_jugar(){
     
     //semilla rand hace que cada vez que compilamos genera numeros aleatorios distintos
     srand(time(NULL)); //declaro variables que me van hacer falta
     JUGADOR jugadores[4]; //DEFINO la estructura jugador como un array de 4 elementos ya que son 4 los jugadores que participan en el juego
     int i,total=0;// el total lo pongo a cero porque luego lo voy a usar para sumar el total de dedos y si no lo pongo a cero me dara la suma un valor cualquiera
      
  
     //abrimos el fichero ya que queremos que queden registrados los datos de la jugada
      FILE *fichero;  
      char letra;
      
      fichero = fopen("registro.txt","w");//w para escribir en fichero
      if (fichero==NULL)//condicion para que avise si se produce algun error al abrir el fichero si encuentra un valor nulo el fichero no se abre
      {
       printf( "No se puede abrir el fichero.\n" );
       exit( 1 );
      } 
     
     
     
     
     
     //REALIZAR APUESTAS
     
    
     for(i=0;i<4;i++){
          printf("Jugador %i\n",i+1);
          printf("Introduce nombre:\n");
         
          fflush(stdin);scanf("%s",&jugadores[i].nombre);
          
		   //fprintf(fichero,"Nombre: %s  Jugador %i \n",jugadores[i].nombre,i+1);//escribimos el nombre del jugador y numero en el fichero con fprintf
           do{
          
            system("cls");
            
            printf ("Jugador %i\n",i+1 );
            
            
            printf("Introduce apuesta(no mayor a 20):\n");
            fflush(stdin);scanf("%i",&jugadores[i].apuesta);
            
           }while(jugadores[i].apuesta<1||jugadores[i].apuesta>20);//aqui condicionamos para que cuando introduzcamos la apuesta por teclado esta no se mayor que 20 y menor que 1
           
          }//recorro el array con un bucle for y en cada posicion le indico el nombre de jugador y la apuesta que hace
          
                      
      //REFLEJAR APUESTA
        
      //fprintf (fichero, "\n \n \n");// para hacer retorno de carro en fichero
          
      for(i=0;i<4;i++){
           printf("Nombre: %s\n",jugadores[i].nombre);
           printf("Su apuesta: %i\n",jugadores[i].apuesta); 
           
        //   fprintf (fichero, "Jugador %i ha apostado %i dedos \n", i+1, jugadores[i].apuesta);
           }//recorro de nuevo todas las posiciones del array y en cada elemento le pongo que me pinte los datos que introduci en el anterior bucle para cerciorarme de que los datos se introdujeron correctamente             
     
     
     
     getch("\n");//con esto hasta que no pulsamos enter el programa no continua ejecutandose
     
     //REALIZAR JUGADA
     
     //fprintf (fichero, "\n \n \n");
     
     printf("\n\n Realizando jugada...\n");
         
     for(i=0;i<4;i++){
           jugadores[i].num_dedos=rand()%(5+1);//rand()%(max+1) esta es la formula si queremos que el rand genere valores entre 0 y 5.
           printf("El jugador %s ha sacado: %i dedos\n", jugadores[i].nombre,jugadores[i].num_dedos);
           total+=jugadores[i].num_dedos;//recordar que al declarar int total hay que igualarlo a cero para que no sume valor residual
           }
     
    //recorro todas las posiciones del array y en cada posicion hago que se genere un numero aleatorio de dedos que saca el jugador limitados del uno al cinco
    //saco el resultado generado por pantalla y por ultimo voy sumando todos los resultados aleatorios para obtener el total de dedos que se han sacado en el turno
     
     
     printf("\n El total de dedos en la ronda es de %i\n",total);//aqui me pinta el total que se saco de dedos en la tirada
     //fprintf (fichero, "El total de dedos es: %i \n", total);
     getch("\n");//otra pausa
     
     //COMPROBAR GANADOR
     
     //fprintf (fichero, "\n \n \n");
     
     int resultados[4];//me creo un array donde voy a guardar la diferencia de cada jugador
     
     for(i=0;i<4;i++){
     		resultados[i]=abs(total-jugadores[i].apuesta); //abs es una funcion que convierte un numero en su valor absoluto por lo que si tenemos un valor negativo en la diferencia este nos lo transforma a positivo
     	
         	//fprintf (fichero, "Jugador %i tiene una diferencia de %i dedos\n", i+1, resultados[i]);
             
             	
     	fwrite(&jugadores[i],sizeof(jugadores[i]),1,fichero);//fwrite le paso la direccion de memoria del array jugadores, el tamaño del tipo de dato a escribir con siezof, 
     	//el numero de datos que se va ha introducir, y el puntero fichero
     	//aprovecho el bucle para escribir los datos de los 4 jugadores.
     }
     
     //fprintf (fichero, "\n \n \n"); //fwrite
     
     JUGADOR ganador;//declaro variable de tipo Jugador en donde guardo los datos del ganador
     
     
     //Acto seguido igualo los datos de ganador a los datos del array jugadores en su primera posicion
     
     //strcpy lo uso para copiar un dato de tipo string el resto al ser integer con igualarlo nos bastaria
     
	 strcpy (ganador.nombre, jugadores[0].nombre);//esto seria lo mismo que poner ganador=jugadores[0].nombre pero esto da error por lo que uso strcpy
	 ganador.apuesta = jugadores[0].apuesta;
	 ganador.num_dedos = jugadores[0].num_dedos;
	 
     int aux=resultados[0];// declaro aux y guardo la primera posicion del array resultados donde tengo guardada las diferencias de cada jugador
                        //ANOTACION todo el proceso anterior me lo puedo ahorrar si le doy un valor a aux inicial, entonces
                        //empezaria el bucle desde la posicion cero y lo igualaria todo a la posicion del array dentro del bucle.
                        
     
     for(i=1;i<4;i++){//aqui empiezo a recorre desde la posicion dos del array porque antes el aux lo he igualado a la primera y ahora quiero compararlas con las posiciones siguientes
     	if(aux>resultados[i]){//si aux es mayor que la actual posicion que estoy recorriendo se iguala esa posicion a aux con esto conseguimos poner de ganador al jugador que tenga la menor diferencia
     		aux=resultados[i];
     		strcpy(ganador.nombre, jugadores[i].nombre);//aqui igualo ganador a la posicion que tenga menor diferencia
     		ganador.apuesta = jugadores[i].apuesta;
			 ganador.num_dedos = jugadores[i].num_dedos;
     	
     	}//en caso de que hubiese empate ganaria el primer jugador que tenga el valor ya que el segundo aunque tenga el mismo valor no lo guardaria en aux ya que la condicion es > y no >=
     		
     	
     }
     
     printf("\n \n El GANADOR es %s\n",ganador.nombre);
     //fprintf (fichero, "El GANADOR es : %s \n", ganador);
     
     fwrite(&ganador,sizeof(ganador),1,fichero);//con este fwrite registro al ganador ya que contiene la variable ganador
     
     getch("\n");
     
     fclose (fichero); // con esto cierro el fichero que abri para escribir la partida
     	printf( "Problemas al cerrar el fichero\n" );
}

void ultima_jugada(){
	
	FILE *fichero;//puntero fichero
      //char letra;
      JUGADOR registrar;//me creo una variable tipo jugador que usare para leer los datos del fichero
      
      fichero = fopen("registro.txt","r");// abro fichero para lectura
      if (fichero==NULL)//si el valor de fichero es nulo
      {
       printf( "No se puede abrir el fichero.\n" );//da mensaje de error
       exit( 1 );//funcion que utilizamos para salir el 1 indica al sistema operativo que se han producido errores
      }
	   
       printf( "Ultima jugada:\n" );
       int i=1;//declaro contador que vy ha usar en condicion posterior
       
       //fread
      // letra=getc(fichero); //lee el dato al que apunta el puntero llamado fichero, y además hace un fetch, es decir, desplaza el puntero hasta el siguiente caracter.
       while (feof(fichero)==0)//comprueba si se ha llegado al final del fichero en cuyo caso devuelve un valor distinto de cero
        {
        	//hacemos con esta condicion ya que la forma en que escribimos en el fichero fue 5 veces 4 para registrar los datos de los jugadores y la quinta donde escribimos el ganador
        	//como queremos poner el ganador en la ultima parte lo diferenciamos con un else para que el printf nos saque otra frase.
        	//con el if y el fread dentro estamos comprobando que lee un valor correcto si es correcto te manda uno y si devuelve otro valor es q hay error de lectura
        	if (fread(&registrar,sizeof(registrar),1,fichero)&&i<=4){
        	
        		printf("Nombre jugador:%s\n Apuesta:%i\n numero de dedos:%i\n",registrar.nombre,registrar.apuesta,registrar.num_dedos);
        		printf("\n");
				i++;
				}
			else if(i==5){
				
				printf("\n\n");
				printf("El nombre del ganador es:%s",registrar.nombre);
				fread(&registrar,sizeof(registrar),1,fichero);//este fread lo ponemos aqui porque cuando el contador es 5 y se mete en el else sacamos con el printf el ultimo registro y poniendo fread al final situamos
				//el carro al final del fichero por lo que vuelve al while y al no encontrar nada devuelve un valor distinto de 0 y se sale del bucle
			}
        //  printf( "%c",letra );
         // letra=getc(fichero);
        }
        
       if (fclose(fichero)!=0) //funcion que cierra el fichero, si todo va bien devuelve un cero si no devuelve otro valor
         printf( "Problemas al cerrar el fichero\n" );//por lo que se meteria aqui y mostraria este mensaje de error
         
         //
         
         
         
        
     
     getch("\n");
         
         
} 
	
	
     
    
     

