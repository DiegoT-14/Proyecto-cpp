# Proyecto-cpp
## Diego Alejandro Torres Cely, Juan Carlos Muñoz Muñoz

## Librerias implementadas

Una parte fundamental del programa recae en las librerías que son usadas para llevar a cabo el correcto funcionamiento del sistema. A continuación se muestra cada una de estas junto con su respectivo aporte al desarrollo del código.

```cpp
<string>
```

Esta librería permite el uso de la clase string en C++. Esta clase facilita la manipulación de cadenas de texto de forma segura y flexible. Dentro de sus funciones se encuentra .c_str(), la cual permite convertir un objeto string en un un *C-string* (arreglo de caracteres terminado en \0), lo cual resulta útil cuando se requiere compatibilidad con funciones de la librería <cstring> o con operaciones de bajo nivel.

```cpp
<sstream>
```

Esta librería fue utilizada para implementar mecanismos de procesamiento de texto mediante *flujos de datos en memoria*. Permite tratar una cadena de caracteres como si fuera un flujo de entrada o salida, facilitando la separación y procesamiento de información.

Las funciones utilizadas provenientes de la librería <sstream> fueron:

- std::stringstream ss(linea)  
  Permite convertir una cadena de texto en un flujo de datos, lo que facilita su procesamiento secuencial.

- getline(ss, token, 'delim')  
  Permite leer segmentos de texto dentro del flujo hasta encontrar un delimitador específico. Esta función resulta especialmente útil para *tokenizar líneas provenientes de archivos de texto*, como en el caso de la lectura de archivos .csv o archivos de configuración.

```cpp
<cstring>
```

La librería <cstring> permite trabajar con *cadenas de caracteres estilo C (C-strings)* y realizar operaciones de manipulación y comparación entre ellas.

Las funciones utilizadas en el desarrollo del proyecto fueron:

- strncpy(destino, origen, N)  
  Permite copiar una cadena de caracteres desde una posición de memoria hacia otra, controlando el número máximo de caracteres copiados.

- strcmp(str1, str2)  
  Permite comparar dos cadenas de caracteres para determinar si son iguales. Esta función retorna 0 cuando ambas cadenas son idénticas.

- strncmp(str1, str2, N)  
  Similar a strcmp, pero permite comparar únicamente los primeros N caracteres de ambas cadenas.

Estas funciones fueron utilizadas principalmente para *copiar información leída desde archivos y realizar comparaciones entre identificadores o tipos de variables*.

```cpp
<fstream> ; <iostream>
```

Estas dos librerías son fundamentales para la correcta lectura y escritura de archivos, tanto de texto como binarios.

La librería <iostream> permite realizar operaciones de entrada y salida estándar mediante cout y cin, lo cual facilita la interacción del usuario con el programa.

Por su parte, <fstream> permite manipular archivos almacenados en el sistema. En el desarrollo del proyecto se utilizaron diferentes modos de apertura:

- ios::in para abrir archivos en modo lectura.
- ios::out para abrir archivos en modo escritura.
- ios::app para agregar contenido al final de un archivo existente sin sobrescribir su contenido.
- ios::binary para indicar que el archivo será tratado como *archivo binario*.

Además, esta librería permite el uso de funciones como:

- read() para leer datos desde archivos binarios.
- write() para escribir datos en archivos binarios.

Estas herramientas fueron utilizadas para leer el archivo binario que contiene las mediciones médicas de los pacientes y para generar archivos de salida con los resultados del análisis.

```cpp
<cmath>
```

Esta librería proporciona funciones matemáticas utilizadas en el programa. En particular, se empleó la función fabs(), la cual permite obtener el *valor absoluto de un número de tipo double*. Esta función fue utilizada durante el proceso de detección de anomalías en señales ECG.

```cpp
<cstdlib>
```

Esta librería fue implementada para hacer uso de la función atof(), la cual permite convertir una cadena de caracteres (char*) en un valor numérico de tipo double. Esta conversión fue utilizada al momento de leer los valores mínimo y máximo desde el archivo de configuración, permitiendo transformar los datos almacenados como texto en valores numéricos que pueden ser utilizados en las comparaciones del sistema.

## Archivos creados

En primera instancia, se crearon un total de 7 archivos .h, dentro de los cuales se almacenan todas las estructuras y funciones correspondientes para que el programa final funcione.

Los archivos .h son los siguientes:

- Configuracion.h
- Paciente.h
- ArchivoPacientes.h
- Lectura.h
- Medicion.h
- Maquina.h
- Sala.h

## Configuración.h
Yo

## Pacientes.h
Yo

## ArchivoPacientes.h

Este archivo define la estructura ArchivoPacientes, la cual se utiliza para gestionar la información de todos los pacientes cargados desde el archivo pacientes.csv, asi como la cantidad de estos.

Dentro de esta estructura se declaran dos atributos principales:

- Paciente* pacientes  
  El cual es un arreglo dinámico de estructuras Paciente, el cual almacena la información de todos los pacientes leídos desde el archivo.  
  La estructura Paciente es definida en Paciente.h y contiene los siguientes datos:

  - id del paciente
  - tipo de documento
  - número de documento
  - nombre
  - apellido
  - fecha de nacimiento
  - teléfono
  - correo electrónico
  - tipo de sangre
  - entidad de salud
  - medicina prepagada

- int cantidad  
  Esta variable almacena la cantidad total de pacientes cargados en memoria.

Posteriormente se define un constructor para la estructura, cuyo objetivo es inicializar correctamente los atributos antes de que la estructura sea utilizada. Este tipo de constructores no se vieron en el curso sin embargo, fue diseñana con ayuda de ChatGPT con el fin de evitar que las variables guarden "Basura" al momento de crearlas como dinamicas.

### Prompt:
Cuando creo un arreglo dinamico dentro de un struct es necesario inicializar esas variables para que no guarden basura, o el programa no les asigna nada al momento de ser creados?

```cpp
ArchivoPacientes() {
    pacientes = nullptr;
    cantidad = 0;
}
```

Como bien se menciono anteriormente, este constructor inicializa el puntero pacientes como nullptr para indicar que aún no existe memoria reservada para almacenar pacientes, y establece cantidad en 0, indicando que inicialmente no hay pacientes cargados en el sistema.

Finalmente, se define la función:

```cpp
void AgregarPaciente(ArchivoPacientes &archivo)
```

Esta función recibe la estructura ArchivoPacientes por referencia, lo cual permite modificar directamente su contenido sin crear copias innecesarias en memoria.

Dentro de esta función se llama a:

```cpp
leer_datos_paciente(archivo.cantidad)
```

Funcion la cual se declaro en Paciente.h , esta función es la encargada de:

1. Leer el archivo pacientes.csv con ayuda de getline.
2. Separar cada línea del archivo en los diferentes campos del paciente con la ayuda de los tokens.
3. Crear dinámicamente un arreglo de estructuras Paciente con la ayuda de new.
4. Cargar la información correspondiente en cada una de ellas con la funcion cargarDatosPaciente.

El arreglo dinámico resultante es asignado al puntero archivo.pacientes, mientras que la variable archivo.cantidad almacena el número total de pacientes cargados.

## Lectura.h
TORO

## Medición.h
YO

## Máquina.h
TORO

## Sala.h
CHAT
