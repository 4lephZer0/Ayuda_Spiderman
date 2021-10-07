// Inclusion de librerias

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estas lineas son en caso de que se corra el programa en linux esto no se lee
// Y en caso de windows si se lee, esto para no generar conflictos con linux.
#ifdef _WIN32
  #include<windows.h>
#endif  

// Se define una pequeña funcion para poder limpiar la terminal y no quede todo acumulado.
void limpiar_pantalla(){

    // En caso de que si estemos en windows, usa system("cls").
    #ifdef _WIN32
        system("cls");
    
    // En caso de que esté en linux u otro SO utiliza el system("clear").
    #else
        system("clear");
    #endif
}

/*
Se define una funcion para crear una "matriz bidimensional cuadrada" y las llena de 0's
queda con el siguiente formato para una matriz 5x5

Matriz

0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

*/
int ** crear_matriz_bidimensional_cuadrada(int dato_fila){


    int ** matriz_auxiliar = (int **)malloc(sizeof(int *)*dato_fila);

    for (int i = 0; i < dato_fila; ++i){
        
        matriz_auxiliar[i] = (int *)malloc(sizeof(int)* dato_fila);
    }

    for (int i = 0; i < dato_fila; ++i){

        for (int j = 0; j < dato_fila; ++j){

            matriz_auxiliar[i][j] = 0;
        }
    }

    return matriz_auxiliar;

}

/*
Se define la funcion que va a generar todas las matrices auxiliares para ser utilizadas en este proyecto.
algunas de ellas, van a quedar con datos extraidos de los archivos dentro.
y el resto van a queedar rellenas con 0's

ej en una matriz 5x5:

matriz 1:

2 1 1 0 0 0
5 1 2 2 2 1
4 1 2 1 1 0
3 1 2 1 0 0
2 1 1 0 0 0

Matriz 2:

1 0 0 0 0 0
3 0 0 0 0 0
5 0 0 0 0 0
5 0 0 0 0 0
2 0 0 0 0 0

Matriz 3:

1 0 0 0 0 0
2 1 1 0 0 0
1 2 2 2 1 0 
1 2 1 1 1 0
1 1 0 0 0 0

Y las otras 3 son auxiliares y van a ser unicamente matrices con 0's
ej:

0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

*/

int *** crear_espacio(FILE * fichero){

    int filas;
    int columnas;

    char caracter;
    char caracteres[100];

    rewind(fichero);
    
 	fgets(caracteres,100,fichero);

    filas = strtol(caracteres, NULL, 10);
    
    // Apartado para generar las matrices.

    int ** matriz_auxiliar = crear_matriz_bidimensional_cuadrada(filas);
    int ** matriz_auxiliar2 = crear_matriz_bidimensional_cuadrada(filas);
    int ** matriz_auxiliar3 = crear_matriz_bidimensional_cuadrada(filas);
    int ** matriz_auxiliar4 = crear_matriz_bidimensional_cuadrada(filas);
    int ** matriz_auxiliar5 = crear_matriz_bidimensional_cuadrada(filas);
    int ** matriz_mapa = crear_matriz_bidimensional_cuadrada(filas);

    int *** matriz_general = (int ***)malloc(sizeof(int **)*6);


    int i = 0;
    int j = 0;

    /*
    Este while es para leer la primera mitad del archivo (datos de las Filas)
    Que son almacenadas en la matriz_auxiliar:

    Matriz auxiliar:

    2 1 1 0 0 0
    5 1 2 2 2 1
    4 1 2 1 1 0
    3 1 2 1 0 0
    2 1 1 0 0 0

    */

    while((caracter = fgetc(fichero)) != EOF){
        
        if (caracter != ' '){
            if (caracter != '\n'){

                matriz_auxiliar[j][i] = caracter - '0';
                i = i + 1;
            }
        }

        if (caracter == '\n'){

            j = j + 1;
            i = 0;
        }

        if (j == filas){

            break;
        }
    }

    i = 0;
    j = 0;
    int contador = 1;

    /*
    Este 2do while es para leer la segunda mitad del archivo (datos de las columnas)
    Que son almacenadas en la matriz_auxiliar2 y matriz_auxiliar3:

    Matriz auxiliar2:

    1 0 0 0 0 0
    3 0 0 0 0 0
    5 0 0 0 0 0
    5 0 0 0 0 0
    2 0 0 0 0 0

    Matriz auxiliar3:

    1 0 0 0 0 0
    2 1 1 0 0 0
    1 2 2 2 1 0 
    1 2 1 1 1 0
    1 1 0 0 0 0

    */

    while((caracter = fgetc(fichero)) != EOF){
        
        if (caracter != '\n'){
            if (caracter != '0'){
                
                if (i == 0){

                    matriz_auxiliar2[j][i+1] = caracter - '0';
                }

                else if (caracter  == '-'){
                
                    contador = contador + 1;
                    caracter = fgetc(fichero);
                    matriz_auxiliar2[j][i+1] = caracter - '0';
                }

                else if (caracter == ' '){

                    caracter = fgetc(fichero); 
                    matriz_auxiliar3[j][i-contador] = caracter - '0';

                    matriz_auxiliar2[j][0] = contador;
                    
                }
            }

            else if (caracter == '0'){

                matriz_auxiliar2[j][i+1] = caracter - '0';

                matriz_auxiliar2[j][0] = contador;
                contador = 1;
            }


            i = i + 1;
        }

        if ((caracter == '\n') || (caracter == EOF)){

            j = j + 1;
            i = 0;
            contador = 1;

        }
    }

    // Se almacenan todas en la matriz general.

    matriz_general[0] = matriz_auxiliar;
    matriz_general[1] = matriz_auxiliar2;
    matriz_general[2] = matriz_auxiliar3;
    matriz_general[3] = matriz_auxiliar4;
    matriz_general[4] = matriz_mapa;
    matriz_general[5] = matriz_auxiliar5;

    return matriz_general;
}

/*
Se define una pequeña matriz la cual extrae del archivo el valor de las filas
para luego ser utilizada en la generacion del mapa

ej de lectura del archivo:

Si el archivo tiene de entrada lo siguiente:

5
2 1 1
5 1 2 2 2 1
4 1 2 1 1
3 1 2 1
2 1 1
1 1
3 2 1 1
5 1 2 2 2 1
5 1 2 1 1 1
2 1 1

solamente toma el valor de la primera linea, osea el "5".
*/
int buscar_filas(FILE* fichero){

    int filas;
    char caracteres[100];

    rewind(fichero);

 	fgets(caracteres,100,fichero);

    filas = strtol(caracteres, NULL, 10);

    return filas;

}

/*
Se crea una funcion que va a separar los datos extraidos en la funcion crear_espacio.
y las va a separar entre las matrices.
ej:

matriz fila:

1 1 0 0 0
1 2 2 2 1
1 2 1 1 0
1 2 1 0 0
1 1 0 0 0

matriz datos fila:

2 0 0 0 0
5 0 0 0 0
4 0 0 0 0
3 0 0 0 0
2 0 0 0 0

matriz columna:

1 0 0 0 0 
2 1 1 0 0 
1 2 2 2 1 
1 2 1 1 1 
1 1 0 0 0 

matriz datos columna:

1 0 0 0 0
3 0 0 0 0
5 0 0 0 0
5 0 0 0 0
2 0 0 0 0

matriz mapa:

1 2 1 1 1
0 1 2 2 1
0 1 2 1 0
0 0 2 1 0
0 0 1 1 0

matriz auxiliar(a utilizar como almacen de caso anterior):

0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

*/
int *** llenar_matrices(int *** matriz_general, int filas){

    // Se les da a cada matriz un nombre para no confundirlas con tanto matriz_general
    // Ya que se les dá la direccion de memoria, por lo que, modificar una de estas, modifica tambien a la que se encuentra dentro de la matriz_general.
    int ** matriz_mapa = matriz_general[0];
    int ** matriz_datos_columna = matriz_general[1];
    int ** matriz_columna = matriz_general[2];
    int ** matriz_datos_fila = matriz_general[3];
    int ** matriz_fila = matriz_general[4];
    int ** matriz_auxiliar = matriz_general[5];
    int longitud;

    // Se hace un ciclo para darle a la matriz fila los valores que iran dentro de ella sin la cantidad
    // ej: 4 1 1 2 1 pasa a ser 1 1 2 1.
    for (int i = 0; i < filas; ++i){

        // Se le da el valor auxiliar para pasar solo los datos que seran de utilidad.
        longitud = matriz_mapa[i][0];
        
        for (int j = 0; j < filas; ++j){
            
            if ((j + 1) <= longitud){

                matriz_fila[i][j] = matriz_mapa[i][j+1];
                
            }

            else if((j + 1) > longitud){

                matriz_fila[i][j] = 0;
                
            }
        }
        
    }

    // Se crea otro ciclo para pasar los datos que iran dentro de las columnas
    // Osea, los datos con - como el 1-1-1
    for (int i = 0; i < filas; ++i){

        longitud = matriz_datos_columna[i][0];

        for (int j = 0; j < filas; ++j){

            if(j > longitud){

                matriz_datos_columna[i][j] = 0;
                
            }
        }
    }

    // Lo mismo para los datos de las filas
    // como el 4 del 4 1 1 2 1.

    for (int i = 0; i < filas; ++i){

        longitud = 1;

        for (int j = 0; j < filas; ++j){

            if(j >= longitud){

                matriz_datos_fila[i][j] = 0;
            }
            else{

                matriz_datos_fila[i][0] = matriz_mapa[i][0];

            }
        }
    }
    


    // Hacemos 0 la matriz mapa, ya que extraimos todos los datos de ahí.
    for (int i = 0; i < filas; ++i){

        for (int j = 0; j < filas; ++j){

            matriz_mapa[i][j] = 0;
        }
    }

    // los datos de la columna los reflejamos diagonalmente para luego utilizarlos para generar el mapa.

    for (int i = 0; i < filas; ++i){

        for (int j = 0; j < filas; ++j){

            matriz_mapa[i][j] = matriz_columna[j][i];  
        }
    }
    
    // Se retorna la matriz general.
    return matriz_general;
       
}

/*
Esta funcion va a generar la primera salida a partir de la generacion del mapa
A pesar de estar arriba, su llamado ocurre despues
va a ingresar el mapa a un archivo con nombre primerasalida.out
ej de salida:

0 0 1 1 0
1 2 2 2 1
0 1 2 1 1
0 1 2 1 0
0 0 1 1 0

*/
void generar_primera_salida(int ** matriz_mapa, int filas){
    // Se definen los tipos de datos.
    FILE* archivo_salida;
    char caracter;
    // Se abre el archivo de PrimeraSalida.out con el formato de escritura.
    archivo_salida = fopen("PrimeraSalida.out", "w+t");
    // Se hace un ciclo para ingresar cada caracter dentro del archivo
    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < filas; ++j){
            if (j == (filas - 1)){
                caracter = matriz_mapa[i][j] + '0';
                fputc(caracter, archivo_salida);
            }
            else{
                caracter = matriz_mapa[i][j] + '0';
                fputc(caracter, archivo_salida);
                caracter = ' ';
                fputc(caracter, archivo_salida);
            }
        }
        if (i < (filas - 1)){
            caracter = '\n';
            fputc(caracter, archivo_salida);
        }
    }
    // Una vez terminada la ingresion cierra el archivo.
    fclose(archivo_salida);
}

/*
Idea principal para la generacion de mapa : Hacer un programa que vaya detectando acorde a las filas, "coincidencias de iguales"

a partir de la siguiente entrada:

10
4 1 2 1 1
2 2 1
2 1 2
5 1 1 1 2 1
2 1 1
3 1 2 1
1 1
3 1 2 2
4 1 3 3 2
2 2 2
0
0
1-1-1 1 1 1
4-1-2 2 2 2 1 1 2 1
2-1-5 1 1 1 2 1 2 3 2
1-3-2 1 1 1 1 3 2
2-1 2 1 2
1 1
0
0

ejemplo de saklida: la matriz de las que se generan las columnas tendrá siguiente diseño:

                    1 2 1 1 2 1             y las de las filas , el siguiente 1 2 1 1
                    1 2 1 1 1                                                 2 1
                    1 2 1 1 2                                                 1 2    
                      1 2 1                                                   1 1 1 2 1
                      1 1 3                                                   1 1
                      2 2 2                                                   1 2 1
                      1 3                                                     1
                        2                                                     1 2 2
                                                                              1 3 3 2
                                                                              2 2

 Por lo que iremos usando a de las columnas, e iremos comparando donde encontramos el patron de las filas:

    1 2 1 1 2 1     =   1 2 1 1         =   1 2 1 1         =   1 2 1 1         =   1 2 1 1         =   1 2 1 1
    1 2 1 1 1       =   1 2 1 1 2 1     =     2 1           =     2 1           =     2 1           =     2 1
    1 2 1 1 2       =   1 2 1 1 1       =   1 2 1 1 2 1     =   1 2             =   1 2             =   1 2
      1 2 1         =     1 2 1 2       =   1 1 2 1 1       =   1 1 1 1 2 1     =     1 1 1 2 1     =     1 1 1 2 1
      1 1 3         =     1 1 3         =     1 1 1 2       =     1 2 1 1       =   1 1 2 1 1       =         1 1
      2 2 2         =     2 2 2         =     2 2 3         =     2 1 3 2       =     2 1 3 2       =     1 2 1 
      1 3           =     1 3           =     1 3 2         =     1 2 2         =     1 2 2         =       1 
        2           =       2           =       2           =     2 3           =     2 3           =   1 2 2
                                                                    2           =     1 2           =     1 3 3 2
                                                                                                            2 2

    Donde los espacios que queden vacios , se rellenaran con 0's y tendriamos el mapa
    solo faltaria mandarlo a verificar y lo tendriamos hecho.
*/

int *** realizar_mapa(int *** matriz_general, int filas){

    // Se les da a cada matriz un nombre para no confundirlas con tanto matriz_general
    // Ya que se les dá la direccion de memoria, por lo que, modificar una de estas, modifica tambien a la que se encuentra dentro de la matriz_general.
    int ** matriz_mapa = matriz_general[0];
    int ** matriz_datos_columna = matriz_general[1];
    int ** matriz_columna = matriz_general[2];
    int ** matriz_datos_fila = matriz_general[3];
    int ** matriz_fila = matriz_general[4];
    int ** matriz_auxiliar = matriz_general[5];

    // Se definen los valores auxiliares que nos serviran para la generacion del mapa
    int auxiliar = 0, auxiliar2 = 0, auxiliar3 = 0, auxiliar4 = 0, salida = 0, auxiliar5 = 0, auxiliar6 = 0;

    // Se definen las variables que seran utilizadas en los ciclos for.
    int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, p = 0;

    // Variable auxiliar que servirá para mover las columnas mas adelante.
    int contador = 0;

    // Comienza el ciclo que va a revisar la totalidad de las filas.
    for (i = 0; i < filas; ++i){
        // Se guarda en auxiliar el valor de los datos que van en la primera fila (4 en el primer caso).
        auxiliar = matriz_datos_fila[i][0];
        // Se guarda un contador para usarse mas adelante.
        contador = filas-1;
        // Comienza el ciclo que va a revisar cada dato de la fila, en el primer ciclo es: (0 0 1 2 1 1 2 1 0 0)
        for (j = auxiliar6; j < filas; ++j){
            // En caso de que el dato que esta tomando de la matriz mapa sea igual al que deberia ir en la fila, comenzará el ciclo de revision!.
            if (matriz_mapa[i][j] == matriz_fila[i][l]){
                // Se va a guardar el valor de j en auxiliar 3 y en auxiliar 4, en caso de que haya algun problema , tener ese valor almacenado.
                if (l == 0){
                    auxiliar3 = j - 1;
                    auxiliar4 = j;
                }
                // Se hace un ciclo para verificar si es que hay coincidencia entre los datos almacenados.
                for (l = 0; l < auxiliar; ++l){
                    // En caso de que se encuentre que no hay coincidencia l pasa a ser auxiliar, j pasa a ser auxiliar 4 y auxiliar 3 pasa a ser 0.
                    if (matriz_mapa[i][j] != matriz_fila[i][l]){
                        l = auxiliar;
                        j = auxiliar4;
                        auxiliar3 = 0;
                    }
                    // En caso de que se revise la totalidad de los datos y no se haya encontrado una "no coincidencia" ocurre lo siguiente:
                    else if (l == auxiliar-1){
                        // Se guarda el mapa en caso de que en la siguiente linea no se pueda generar la fila.
                        for (o = 0; o < filas; ++o){
                            for (p = 0; p < filas; ++p){
                                matriz_auxiliar[o][p] = matriz_mapa[o][p];
                            }
                        }
                        // Se guarda el valor de auxiliar 4 en 5 , ya que este va a servir en caso de que no se pueda generar la fila.
                        auxiliar5 = auxiliar4;
                        // a j se le suma 1 para pasar a realizar las acciones en la siguiente columna.
                        j = j + 1;
                        auxiliar2 = j;
                        // Se hace un ciclo que va a revisar todos los datos de la derecha del programa.
                        for (n = 0; n < (filas-auxiliar2); ++n){
                            // Se crea un ciclo que va a mover hacia abajo todos los datos que no esten en la misma columna de los datos que coinciden.
                            for (m = 0; m < contador; ++m){                               
                                // Se guarda el valor de salida con 1, en caso de que si se pudo generar la fila.
                                salida = 1;
                                // En caso de que no se haya llegado a la fila del cambio, se va a correr 1 espacio hacia abajo.
                                if ((contador-1-m) >= i){
                                    matriz_mapa[contador-m][j] = matriz_mapa[contador-1-m][j];
                                }
                                // una vez corrido, se verifica si es la fila del cambio, en caso de que si, se reemplaza el valor por un 0.
                                if ((contador-1-m) == i){                                    
                                    matriz_mapa[contador-1-m][j] = 0;
                                }
                            }
                            j = j + 1;  
                            m = 0;
                        }
                        // una vez terminado el ciclo de corer para abajo la fila de la derecha, se hace 0 j para hacerlo desde el inicio.
                        j = 0;
                    
                        // Comienza a hacer lo mismo de correr para abajo la columna, pero esta vez para la izquierda.
                        for (n = 0; n <= auxiliar3; ++n){
                            // Se crea el ciclo para mover las columnas de la izquierda.
                            for (m = 0; m < contador; ++m){                                
                                if ((contador-1-m) >= i){
                                    matriz_mapa[contador-m][j] = matriz_mapa[contador-1-m][j];
                                }
                                if ((contador-1-m) == i){                                    
                                    matriz_mapa[contador-1-m][j] = 0;
                                }
                            }
                            j = j + 1;
                        }
                        // le damos a j el valor de la fila, para que termine el ciclo y pase a la siguiente fila.
                        j = filas;
                        l = auxiliar;
                    }
                    // En caso de que haya coincidencia, a j se le suma 1.
                    else if (l < auxiliar-1){
                        j = j + 1;
                    }
                }
                l = 0;
            }
        }
        // En caso de que el valor de salida sea 0, quiere decir que no encontró una coincidencia, por lo que revierte todo lo hecho en 1 fila
        // PROBLEMA: si encuentra un error en 2 filas siguientes, el caso queda en un bucle infinito..
        // No se me pudo ocurrir como resolver ese problema..
        if (salida == 0){
            // Revierte el mapa, al caso anterior.
            for (o = 0; o < filas; ++o){
                for (p = 0; p < filas; ++p){
                    matriz_mapa[o][p] = matriz_auxiliar[o][p];
                }
            }
            // Y coloca los casos bases para revisar de nuevo la fila previa.
            auxiliar6 = auxiliar5 + 1;
            i = i - 2;               
        }
        // En caso de que si encontró coincidencia, el valor de salida vuelve a 0, y el auxiliar 6 tambien.
        else if (salida == 1){
            salida = 0;
            auxiliar6 = 0;
        }
    }
    // Se hace el llamado a generar_primera_salida.
    generar_primera_salida(matriz_mapa, filas);
    // Se retorna la matriz general.
    return matriz_general;
}

/*
Se crea una funcion que se va a utilizar en la Entrada2.in

esta crea una matriz bidimensional de tamaño rectangular, en especifico: matriz de (n)*(n+1)

ej:

0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0
0 0 0 0 0 0

*/
int ** crear_matriz_bidimensional_rectangular(int dato_fila){

    int filas_2;

    filas_2 = dato_fila + 1;

    int ** matriz_auxiliar = (int **)malloc(sizeof(int *)*dato_fila);

    for (int i = 0; i < dato_fila; ++i){
        
        matriz_auxiliar[i] = (int *)malloc(sizeof(int)* dato_fila);
    }

    for (int i = 0; i < dato_fila; ++i){

        for (int j = 0; j < filas_2; ++j){

            matriz_auxiliar[i][j] = 0;
        }
    }

    return matriz_auxiliar;


}

/*
A la matriz_entrada_2 se va a rellenar con los datos de la Entrada2.in

quedando la siguiente matriz:

matriz_mapa:

0 0 1 1 0
1 2 2 2 1
0 1 2 1 1
0 1 2 1 0
0 0 1 1 0
*/
int ** llenar_matriz_entrada_2(FILE* fichero, int ** matriz_entrada_2){

    char caracter;
    char caracteres[100];
    strtol(caracteres, NULL, 10);

    int i = 0, j = 0, contador = 0;

    while((caracter = fgetc(fichero)) != EOF){

        
        matriz_entrada_2[i][j] = caracter - '0';

        j = j + 1;
        caracter = fgetc(fichero);

        if (caracter == '\n'){

            i = i + 1;
            j = 0;
        }
    }

    return matriz_entrada_2;
}

/*
Esta funcion va a separar la matriz_entrada_2 en 3 matrices que seran auxiliares para generar el mapa
va a quedar de la siguiente forma

matriz auxiliar 1:

2 1 1 0 0 0
5 1 2 2 2 1
4 1 2 1 1 0
3 1 2 1 0 0
2 1 1 0 0 0

matriz auxiliar 2:

1 0 0 0 0 0
3 0 0 0 0 0
5 0 0 0 0 0
5 0 0 0 0 0
2 0 0 0 0 0

matriz auxiliar 3:

1 0 0 0 0 0
2 1 1 0 0 0
1 2 2 2 1 0
1 2 1 1 1 0
1 1 0 0 0 0

y van a ser guardadas en una matriz general.
*/
int *** generar_salida_entrada_2(FILE* fichero, int ** matriz_entrada_2, int filas_2){

    int *** matriz_general = (int ***)malloc(sizeof(int **)*3);

    int ** matriz_auxiliar = crear_matriz_bidimensional_rectangular(filas_2);
    int ** matriz_auxiliar_2 = crear_matriz_bidimensional_rectangular(filas_2);
    int ** matriz_auxiliar_3 = crear_matriz_bidimensional_rectangular(filas_2);

    int auxiliar = 0, auxiliar_2 = 0, k = 0, l = 0, m = 0, n = 0;

    for (int i = 0; i < filas_2; ++i){

        for (int j = 0; j < filas_2; ++j){

            if (matriz_entrada_2[i][j] != 0){

                auxiliar = auxiliar + 1;
                matriz_auxiliar[k][l+1] = matriz_entrada_2[i][j];
                l = l + 1;

            }

        }
        l = 0;
        matriz_auxiliar[k][l] = auxiliar;
        auxiliar = 0;
        k = k + 1;
    }
    k = 0;

    for (int i = 0; i < filas_2; ++i){

        for (int j = 0; j < filas_2; ++j){

            if (matriz_entrada_2[j][i] != 0){
                
                auxiliar = auxiliar + 1;
                matriz_auxiliar_2[k][l] = matriz_entrada_2[j][i];
                l = l + 1;

                if ((j + 1) != filas_2){

                    if (matriz_entrada_2[j+1][i] == 0){

                        matriz_auxiliar_3[m][n] = auxiliar;
                        auxiliar = 0;
                        n = n + 1;
                    }
                }

                else if ((j + 1) == filas_2){

                    matriz_auxiliar_3[m][n] = auxiliar;
                    auxiliar = 0;
                    n = n + 1;
                }       
            }
        }

        k = k + 1;
        m = m + 1;
        n = 0;
        l = 0;
    }

    matriz_general[0] = matriz_auxiliar;
    matriz_general[1] = matriz_auxiliar_2;
    matriz_general[2] = matriz_auxiliar_3;

    return matriz_general;
}

/*
Se crea la ultima funcion que trabajará con la Entrada2.in
esta va a generar el archivo de salida con nombre SalidaEntrada2.in

si el archivo de entrada es:

5
0 0 1 1 0
1 2 2 2 1
0 1 2 1 1
0 1 2 1 0
0 0 1 1 0

el archivo de salida es:

5
2 1 1
5 1 2 2 2 1
4 1 2 1 1
3 1 2 1
2 1 1
1 1
3 2 1 1
5 1 2 2 2 1
5 1 2 1 1 1
2 1 1

*/

void realizar_SalidaEntrada2(int ** matriz_datos_fila, int ** matriz_datos_columna, int ** matriz_cantidad_columna, int filas_2){


    FILE* archivo_salida;
    char caracter;
    char caracteres[2];
    
    archivo_salida = fopen("SalidaEntrada2.in", "w+t");
    
    // Se ingresa primero el valor del tamaño de la matriz.
    itoa(filas_2, caracteres, 10);
    fputs(caracteres, archivo_salida);

    caracter = '\n';
    fputc(caracter, archivo_salida);

    // Luego un ciclo para ingresar los valores de las filas.    
    for (int i = 0; i < filas_2; ++i){
        
        for (int j = 0; j < (filas_2+1); ++j){

            if ((matriz_datos_fila[i][j] != 0) && (j != filas_2)){

                caracter = matriz_datos_fila[i][j] + '0';
                fputc(caracter, archivo_salida);
                
                if (matriz_datos_fila[i][j+1] != 0){

                    caracter = ' ';
                    fputc(caracter, archivo_salida);

                }
            }

            else if ((matriz_datos_fila[i][j] != 0) && (j == filas_2)){

                caracter = matriz_datos_fila[i][j] + '0';
                fputc(caracter, archivo_salida);
            }
        }

        caracter = '\n';
        fputc(caracter, archivo_salida);
        
    }

    // Por ultimo, un ciclo para ingresar los valores de las columnas.
    int k = 0, l = 0;

    for (int i = 0; i < filas_2; ++i){
        
        for (int j = 0; j < (filas_2+1); ++j){

            if (j == 0){

                if (matriz_cantidad_columna[i][j] == 0){

                    caracter = '0';
                    fputc(caracter, archivo_salida);

                }
            }

            if (matriz_cantidad_columna[i][j] != 0){

                caracter = matriz_cantidad_columna[i][j] + '0';
                fputc(caracter, archivo_salida);
                
                if (matriz_cantidad_columna[i][j+1] != 0){

                    caracter = '-';
                    fputc(caracter, archivo_salida);
                }
            }

            else if (matriz_cantidad_columna[i][j] == 0){

                if (matriz_datos_columna[k][l] != 0){

                    caracter = ' ';
                    fputc(caracter, archivo_salida);

                    caracter = matriz_datos_columna[k][l] + '0';
                    fputc(caracter, archivo_salida);

                }
                l = l + 1;
            }
        }

        k = k + 1;
        l = 0;

        if (i < (filas_2 - 1)){

            caracter = '\n';
            fputc(caracter, archivo_salida);
        }
    }

    fclose(archivo_salida);
}

/*
Se crea la funcion la cual va a contener toda la partida del recorrido manual.

si el mapa es el siguiente:

0 0 1 1 0
1 2 2 2 1
0 1 2 1 1
0 1 2 1 0
0 0 1 1 0

el objetivo es que quede sin ninguun numero no 0.
osea:

0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

si queda al menos un numero distinto de 0, esta va a ser una derrota inminente.

0 0 1 0 0
0 1 0 0 0
0 0 0 0 0
0 0 0 0 0
0 0 0 0 0

*/
void empezar_partida(int *** matriz_general, int filas){

    // Se crean los espacios de memoria para la matriz a utilizar en el recorrido manual.
    int ** matriz_mapa = (int **)malloc(sizeof(int *)*filas);

    for (int i = 0; i < filas; ++i){
        
        matriz_mapa[i] = (int *)malloc(sizeof(int)* filas);
    }

    // Cada dato de la matriz que contiene el mapa se guarda dentro de esta nueva matriz.
    for (int i = 0; i < filas; ++i){

        for (int j = 0; j < filas; ++j){

            matriz_mapa[i][j] = matriz_general[0][i][j];
        }
    }

    limpiar_pantalla();

    int continuar = 0, ciclo = 0, ciclo2 = 0, auxiliar = 0 , coordenada_fila = 0, coordenada_columna = 0, correcto = 0;
    char opcion[100], str_fila[100], str_columna[100];
    // Se crea un ciclo infinito que va a imprimir toda la matriz, y que va a tener numeros en orden para marcar las filas y columnas para el usuario.
    // todo esto para que en caso de error, se repita dentro de un bucle infinito.
    while (ciclo<1){

        printf("\n\n Para empezar a jugar debe elegir una posicion ingresando sus coordenadas\n\n");
        printf(" Esta posicion seleccionada debe ser exclusivamente un borde de los numeros no 0\n\n");
        printf(" (Las coordenadas estara dada primero por el dato de las filas y luego el dato de las columnas)\n\n");

        printf("  ");
        for (int i = 0; i < filas; ++i){

            printf("  %d", i);

        }
        printf("\n  ");
        for (int i = 0; i < filas; ++i){

            printf("  _");

        }
        printf("\n");

        for (int i = 0; i < filas; ++i){
            printf("%d |", i);
            for (int j = 0; j < filas; ++j){
            
                printf(" %d ", matriz_mapa[i][j]);
            }
            
            printf(" |\n");
        }
        
        // se guardan los datos de la coordenada X en str fila, verifica y luego si es valido lo ingresa en coordenada fila.
        printf("\n\n Ingrese la coordenada de la Fila de donde desea empezar: ");
        scanf("%s", &str_fila);
        printf("\n\n");

        if((strcmp("1", str_fila) == 0) || (strcmp("2", str_fila) == 0) || (strcmp("3", str_fila) == 0) || (strcmp("4", str_fila) == 0) || (strcmp("5", str_fila) == 0)
            || (strcmp("6", str_fila) == 0) || (strcmp("7", str_fila) == 0) || (strcmp("8", str_fila) == 0) || (strcmp("9", str_fila) == 0) || (strcmp("0", str_fila) == 0)){

            coordenada_fila = strtol(str_fila, NULL, 10);
        }

        else{

            limpiar_pantalla();
            printf("\n\n Valor ingresado para Fila no valido, por favor ingrese un NUMERO... \n\n");

            continue;

        }

        // se guardan los datos de la coordenada Y en str columna, verifica y luego si es valido lo ingresa en coordenada columna.
        printf(" Ingrese la coordenada de la Columna de donde desea empezar: ");
        scanf("%s", &str_columna);
        printf("\n\n");

        if((strcmp("1", str_columna) == 0) || (strcmp("2", str_columna) == 0) || (strcmp("3", str_columna) == 0) || (strcmp("4", str_columna) == 0) || (strcmp("5", str_columna) == 0)
            || (strcmp("6", str_columna) == 0) || (strcmp("7", str_columna) == 0) || (strcmp("8", str_columna) == 0) || (strcmp("9", str_columna) == 0) || (strcmp("0", str_columna) == 0)){

            coordenada_columna = strtol(str_columna, NULL, 10);
        }

        else{

            limpiar_pantalla();
            printf("\n\n Valor ingresado para columna no valido, por favor ingrese un NUMERO... \n\n");
            continue;

        }

        // En caso de errores se muestra por pantalla un error y se repite el ciclo.
        if (matriz_mapa[coordenada_fila][coordenada_columna] != 0){

            if (matriz_mapa[coordenada_fila][coordenada_columna-1] != 0){
                
                if (matriz_mapa[coordenada_fila][coordenada_columna+1] != 0){

                    limpiar_pantalla();
                    printf("\n\n los datos ingresados, no corresponden a un borde...\n\n");

                }

                else{

                    ciclo = 1;
                }
            }

            else{

                ciclo = 1;
            }
        }

        else{

            limpiar_pantalla();
            printf("\n\n los datos ingresados, no corresponden a un borde...\n\n");

        }
    }

    // Al valor de la posicion seleccionada se le resta 1
    limpiar_pantalla();
    matriz_mapa[coordenada_fila][coordenada_columna] = matriz_mapa[coordenada_fila][coordenada_columna] - 1;

    // Y volvemos a otro ciclo infinito en donde va a imprimir de nuevo el mapa
    // y va a tener todo el juego hasta una posible victoria o derrota.
    while (ciclo2 < 1){

        printf("\n\n");
        for (int i = 0; i < filas; ++i){
            printf(" |");
            for (int j = 0; j < filas; ++j){
                
                if ((i == coordenada_fila) && (j == coordenada_columna)){

                    printf("{%d}", matriz_mapa[i][j]);
                }

                else{

                    printf(" %d ", matriz_mapa[i][j]);
                } 
            }
            printf(" |\n");
        }

        // Se implementa un menu de opciones para el movimiento
        printf("\n\n --Menu de opciones--\n\n\n");
        printf(" Debe ingresar:\n\n\n");
        printf(" N - Para moverse hacia el Norte / Arriba.\n\n");
        printf(" S - Para moverse hacia el Sur / Abajo.\n\n");
        printf(" E - Para moverse hacia el Este / Derecha.\n\n");
        printf(" O - Para moverse hacia el Oeste / Izquierda.\n\n");
        printf(" 1 - Para salir del juego.\n\n");

        printf(" Ingrese una de las opciones: ");
        scanf("%s", opcion);
        printf("\n\n");
        limpiar_pantalla();

        // en caso de algun error a la hora de entregar una direccion,
        // Que no haya mas movimiento o que sea incorrecto el caracter,
        // Lo va a mostrar por pantalla
        // Y en caso de que no haya problemas, realiza el movimiento correspondiente
        // o cierra el juego en caso de 1.

        if ((strcmp(opcion, "N") == 0) || (strcmp(opcion, "n") == 0)){

            if (coordenada_fila == 0){

                printf("\n\n No se puede mover hacia el Norte, por favor ingrese otra direccion...\n\n");
            }

            else{

                if(matriz_mapa[coordenada_fila-1][coordenada_columna] == 0){

                    printf("\n\n No se puede mover hacia el Norte, por favor ingrese otra direccion...\n\n");
                }

                else{

                    coordenada_fila = coordenada_fila - 1;
                    matriz_mapa[coordenada_fila][coordenada_columna] = matriz_mapa[coordenada_fila][coordenada_columna] - 1;
                }
            }
            
        }
        else if ((strcmp(opcion, "S") == 0) || (strcmp(opcion, "s") == 0)){

            if (coordenada_fila == filas-1){

                printf("\n\n No se puede mover hacia el Sur, por favor ingrese otra direccion...\n\n");

            }

            else{

                if(matriz_mapa[coordenada_fila+1][coordenada_columna] == 0){

                    printf("\n\n No se puede mover hacia el Sur, por favor ingrese otra direccion...\n\n");

                }

                else{

                    coordenada_fila = coordenada_fila + 1;
                    matriz_mapa[coordenada_fila][coordenada_columna] = matriz_mapa[coordenada_fila][coordenada_columna] - 1;
                }
            }
            
            
        }
        else if ((strcmp(opcion, "E") == 0) || (strcmp(opcion, "e") == 0)){


            if (coordenada_columna == filas-1){

                printf("\n\n No se puede mover hacia el Este, por favor ingrese otra direccion...\n\n");

            }

            else{

                if(matriz_mapa[coordenada_fila][coordenada_columna+1] == 0){

                    printf("\n\n No se puede mover hacia el Este, por favor ingrese otra direccion...\n\n");

                }

                else{
                    
                    coordenada_columna = coordenada_columna + 1;
                    matriz_mapa[coordenada_fila][coordenada_columna] = matriz_mapa[coordenada_fila][coordenada_columna] - 1;
                }
            }
            
        }
        else if ((strcmp(opcion, "O") == 0) || (strcmp(opcion, "o") == 0)){

            if (coordenada_columna == 0){

                printf("\n\n No se puede mover hacia el Oeste, por favor ingrese otra direccion...\n\n");

            }

            else{

                if(matriz_mapa[coordenada_fila][coordenada_columna-1] == 0){

                    printf("\n\n No se puede mover hacia el Oeste, por favor ingrese otra direccion...\n\n");

                }

                else{
                    
                    coordenada_columna = coordenada_columna - 1;
                    matriz_mapa[coordenada_fila][coordenada_columna] = matriz_mapa[coordenada_fila][coordenada_columna] - 1;
                }
            }
        }
        else if (strcmp(opcion, "1") == 0){

            ciclo2 = 1;
                
        }

        else{

            printf("\n\n El caracter ingresado no es valido...\n\n");

        }

        // Bifurcacion en caso de que se llegue a un camino sin salida.

        if ((coordenada_fila+1) == filas){

            if ((coordenada_columna+1) == filas){

                if ((matriz_mapa[coordenada_fila-1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna-1] == 0)){

                    correcto = 1;

                }
            }

            else if (coordenada_columna == 0){

                if ((matriz_mapa[coordenada_fila-1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna+1] == 0)){

                    correcto = 1;
                }

            }

            else{

                if ((matriz_mapa[coordenada_fila-1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna+1] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna-1] == 0)){

                    correcto = 1;
                }

            }

        }

        else if (coordenada_fila == 0){

            if ((coordenada_columna+1) == filas){

                if ((matriz_mapa[coordenada_fila+1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna-1] == 0)){

                    correcto = 1;

                }
            }

            else if (coordenada_columna == 0){

                if ((matriz_mapa[coordenada_fila+1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna+1] == 0)){

                    correcto = 1;
                }

            }

            else{

                if ((matriz_mapa[coordenada_fila+1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna+1] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna-1] == 0)){

                    correcto = 1;
                }

            }

        }

        else{

            if ((coordenada_columna+1) == filas){
                
                if ((matriz_mapa[coordenada_fila+1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila-1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna-1] == 0)){

                    correcto = 1;

                }
            }

            else if (coordenada_columna == 0){
                
                if ((matriz_mapa[coordenada_fila+1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila-1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna+1] == 0)){

                    correcto = 1;

                }
            }

            else{

                if ((matriz_mapa[coordenada_fila+1][coordenada_columna] == 0) && (matriz_mapa[coordenada_fila-1][coordenada_columna] == 0)
                && (matriz_mapa[coordenada_fila][coordenada_columna+1] == 0) && (matriz_mapa[coordenada_fila][coordenada_columna-1] == 0)){

                    correcto = 1;

                }
            }

        }

        if (correcto == 1){

            for (int i = 0; i < filas; ++i){
                    
                for (int j = 0; j < filas; ++j){

                    // En caso de que queden datos se muestra la derrota   
                    if (matriz_mapa[i][j] != 0){

                        limpiar_pantalla();
                        printf("\n\n Perdiste...\n\n");
                        auxiliar = 1;

                    }

                }
            }
            if (auxiliar == 0){

                // Y en caso de ganar, la victoria.
                limpiar_pantalla();
                printf("\n\n Has Ganado :D\n\n");
            }
            ciclo2 = 1;

        }
    }

    // Se libera la matriz creada para el juego
    for (int i = 0; i < filas; ++i){

        free(matriz_mapa[i]);
    }

    free(matriz_mapa);
    // y como es una funcion void, volvemos a la main.
}

// Funcion principal //
int main(){

    // Se le da el tipo de dato a la varible fichero
    FILE* fichero;
    FILE* fichero_2;

    int *** matriz_general;
    int *** matriz_general_2;

    int filas, filas_2;

    // Se abre el archivo
    fichero = fopen("Entrada.in", "r+");
    fichero_2 = fopen("Entrada2.in", "r+");

    // se llama a las funciones que van a generar todo el mapeado.
    matriz_general = crear_espacio(fichero);
    filas = buscar_filas(fichero);
    filas_2 = buscar_filas(fichero_2);

    matriz_general = llenar_matrices(matriz_general, filas);
    matriz_general = realizar_mapa(matriz_general, filas);

    // luego se llaman a las funciones para generar la SalidaEntrada2.in.
    int ** matriz_entrada_2 = crear_matriz_bidimensional_cuadrada(filas_2);
    matriz_entrada_2 = llenar_matriz_entrada_2(fichero_2, matriz_entrada_2);
    matriz_general_2 = generar_salida_entrada_2(fichero_2, matriz_entrada_2, filas_2);

    realizar_SalidaEntrada2(matriz_general_2[0], matriz_general_2[1], matriz_general_2[2], filas_2);

    int ciclo = 0;
    char opcion[100];

    limpiar_pantalla();

    // Comienza un ciclo infinito a prueba de errores
    // para mostrar por pantalla un mmenu, y repetir en caso de algun caracter invalido.
    while (ciclo < 1){

        printf("\n\n --Menu de opciones--\n\n\n");
        printf(" Debe ingresar:\n\n\n");
        printf(" 1 - Para empezar nueva partida.\n\n");
        printf(" 2 - Para cerrar el programa.\n\n");

        printf(" Ingrese una de las opciones: ");
        scanf("%s", &opcion);

        // En caso de ser 1, empieza el juego y en caso de 2 termina el programa.
        if (strcmp("1", opcion) == 0){

            empezar_partida(matriz_general, filas);
        }

        else if (strcmp("2", opcion) == 0){

            limpiar_pantalla();
            ciclo = 1;
        }

        else{

            limpiar_pantalla();
            printf("\n\n\n Valor Ingresado no valido...\n");
        }

    }

    // Se libera la memoria de todas las matrices utilizadas en este programa.
    for (int i = 0; i < 6; ++i){

        for (int j = 0; j < filas; ++j){

            free(matriz_general[i][j]);
        }
        
        free(matriz_general[i]);
        free(matriz_entrada_2[i]);
    }


    for (int i = 0; i < 3; i++){

        for (int j = 0; j < filas_2; ++j){

            free(matriz_general_2[i][j]);
        }

        free(matriz_general_2[i]);
    }


    free(matriz_entrada_2);
    free(matriz_general);
    free(matriz_general_2);


    // se cierra el archivo
    fclose(fichero);
    fclose(fichero_2);

    /*
    Programa creado por:

    Alan Donoso Villegas

    Documentacion para el manejo de archivos extraido de la siguiente web:

    https://es.wikibooks.org/wiki/Programaci%C3%B3n_en_C/Manejo_de_archivos

    Funcion para limpiar pantalla, encontrada en esta pagina:

    https://es.stackoverflow.com/questions/218943/existe-una-manera-est%C3%A1ndar-de-limpiar-la-pantalla-en-c-c

    Todo el resto de funciones son diseñadas por el creador.
    */
}