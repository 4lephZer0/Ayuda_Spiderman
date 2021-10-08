# Proyecto en C

**Creado y editado por Alan Donoso**
## Instalación

Una vez clonado/descargado el proyecto debes ejecutar "Proyecto.exe" el cual va a contener tanto la creacion de los archivos de salida como el "juego" base en el cual se debe recorrer el mapa la generación de las salidas es automatica, aun a pesar de no existir dichos archivos de salida; sin las entradas correspondientes el archivo no puede funcionar.

## Contexto
Este proyecto se hizo con la base de un nonograma y de la idea de generar un mapa a partir de una entrada con el siguiente formato:



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

Donde la primera linea contiene el tamaño del mapa/matriz el cual llamaremos a ese numero **n**.
Luego en las siguientes **n** filas tendremos como primer numero, la cantidad de datos que posee dicha fila, el cual van a ser necesariamente consecutivas para el fin de este proyecto.

En las siguientes **n** filas tendremos los datos de las columnas los cuales los primeros datos y los que esten concatenados con un **-** van a ser la cantidad de datos consecutivos que posee dicha fila y el - representa espacio entre cada cadena consecutiva.

Luego los siguientes numeros van a ser todos los datos que posee dicha columna
ej:

Si está la siguiente cadena **1-2-3 1 3 1 4 4 2**

El mapa para esa columna debe ser:


    1
    0
    3
    1
    0
    4
    4
    2


Donde el espacio entre cada numero es representado por 0 y este puede ser de cualquier tamaño, siempre y cuando los espacios mas la cantidad de numeros, nunca superen a **n**

Este programa leyendo bien cada una de las entradas, siendo estas entregadas sin errores (falta de pruebas de errores) para ese sentido.

Luego el mapa generado con la entrada de ejemplo de arriba, será el siguiente:



    0 0 1 2 1 1 0 0 0 0
    0 0 0 2 1 0 0 0 0 0
    0 0 1 2 0 0 0 0 0 0
    0 0 0 1 1 1 2 1 0 0
    0 0 0 0 0 1 1 0 0 0
    0 0 0 1 2 1 0 0 0 0
    0 0 0 0 1 0 0 0 0 0
    0 0 1 2 2 0 0 0 0 0
    0 0 0 1 3 3 2 0 0 0
    0 0 0 0 2 2 0 0 0 0

Eso seria la primera funcionalidad, para la segunda funcionalidad, vamos a realizar el proceso inverso, con una entrada con el mapa ya generado pero con una primera linea con el tamaño del mapa, se debe generar una salida como la primera entrada, ejemplo:



    5
    0 0 1 1 0
    1 2 2 2 1
    0 1 2 1 1
    0 1 2 1 0
    0 0 1 1 0


Luego la salida generada para este ejemplo, debe ser la siguiente:



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

Por ultimo se encuentra el juego el cual , al mapa de la primera entrada lo transforma en un juego el cual debe recorrerse de manera manual, se puede empezar donde el usuario defina y se debe pasar por cada casilla la cantidad de veces que indica el numero, se ganará cuando se vacien todas las casillas, y se perderá cuando el jugador no tenga mas opciones de movimiento.


Para interactuar con el menú debe elegir el caracter correspondiente escribiendolo por pantalla. en caso de error, este se va a repetir hasta elegir una opcion valida.

## Bibliografia y documentación utilizada

**Funcion para limpiar pantalla, extraida de esta pagina:**
 https://es.stackoverflow.com/questions/218943/existe-una-manera-est%C3%A1ndar-de-limpiar-la-pantalla-en-c-c

 **Documentacion para manejo de archivos:**
 https://es.wikibooks.org/wiki/Programaci%C3%B3n_en_C/Manejo_de_archivos
