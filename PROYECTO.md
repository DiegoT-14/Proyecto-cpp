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

## Paciente.h

Este archivo define la estructura **Paciente**, la cual se utiliza para almacenar la información correspondiente a cada paciente registrada dentro del sistema.  
Los datos de los pacientes son leídos desde el archivo **pacientes.csv**, procesados y posteriormente almacenados en memoria mediante estructuras dinámicas.

Dentro de esta estructura se declaran múltiples atributos, los cuales representan la información básica de cada paciente registrada en el archivo.

Los atributos definidos son los siguientes:

- char* id_paciente  
  Almacena el identificador único del paciente dentro del sistema.

- char* tipo_doc  
  Indica el tipo de documento del paciente (por ejemplo CC, TI, CE, entre otros).

- char* documento  
  Contiene el número de documento correspondiente al paciente.

- char* nombre  
  Almacena el nombre del paciente.

- char* apellido  
  Almacena el apellido del paciente.

- char* fecha_nacimiento  
  Guarda la fecha de nacimiento del paciente.

- char* telefono  
  Contiene el número de teléfono de contacto del paciente.

- char* email  
  Almacena el correo electrónico del paciente.

- char* tipo_sangre  
  Indica el tipo de sangre del paciente.

- char* entidad_salud  
  Representa la entidad de salud o EPS a la cual se encuentra afiliado el paciente.

- char* medicina_Prepagada  
  Indica si el paciente posee servicio de medicina prepagada.

Todos estos atributos se manejan mediante **punteros a char**, lo cual permite almacenar dinámicamente la información leída desde el archivo de texto.

Posteriormente se define un **constructor para la estructura**, cuyo objetivo es inicializar todos los punteros en **nullptr**.  
Esto se realiza con el fin de evitar que las variables contengan referencias a memoria no inicializada al momento de crear nuevas estructuras Paciente.

```cpp
Paciente() {
    id_paciente = nullptr;
    tipo_doc = nullptr;
    documento = nullptr;
    nombre = nullptr;
    apellido = nullptr;
    fecha_nacimiento = nullptr;
    telefono = nullptr;
    email = nullptr;
    tipo_sangre = nullptr;
    entidad_salud = nullptr;
    medicina_Prepagada = nullptr;
}
```

Este constructor garantiza que cada estructura Paciente comience en un estado seguro antes de que se carguen los datos provenientes del archivo.

---

### Separación de datos del archivo

Dentro de la estructura también se define la función:

```cpp
void separarLineaPaciente(std::string linea, std::string tokens[11])
```

Esta función tiene como objetivo **procesar una línea completa del archivo pacientes.csv y separar sus diferentes campos de información**.

Para lograr esto se utiliza la clase **stringstream**, la cual permite tratar la cadena de texto como un flujo de datos y dividirla utilizando el carácter **';'** como delimitador.

El proceso que realiza esta función es el siguiente:

1. Recibe una línea completa del archivo CSV.
2. Convierte la línea en un flujo de datos utilizando **stringstream**.
3. Separa cada uno de los campos utilizando **getline** con el delimitador ';'.
4. Almacena cada campo en el arreglo **tokens**, el cual contiene los 11 datos correspondientes al paciente.
5. En caso de que algún campo tenga un espacio inicial, este es eliminado para mantener los datos limpios.

---

### Carga de datos en la estructura

Posteriormente se define la función:

```cpp
void cargarDatosPaciente(std::string datos[11])
```

Esta función se encarga de **copiar la información previamente separada en los atributos de la estructura Paciente utilizando memoria dinámica**.

Para cada uno de los campos se realiza el siguiente procedimiento:

1. Se obtiene el tamaño de la cadena de texto utilizando **length()**.
2. Se reserva memoria dinámica utilizando **new**.
3. Se copia el contenido de la cadena utilizando **strncpy**.
4. Se agrega manualmente el carácter de terminación **'\0'** para garantizar que la cadena sea válida en formato C.

Este procedimiento se realiza para cada uno de los atributos de la estructura, permitiendo almacenar la información del paciente de manera independiente en memoria.

---

### Conteo de pacientes en el archivo

Fuera de la estructura se define la función:

```cpp
int contarPacientes()
```

Esta función tiene como objetivo **determinar cuántos pacientes existen dentro del archivo pacientes.csv**.

Para ello se realiza el siguiente proceso:

1. Se abre el archivo utilizando **fstream** en modo lectura.
2. Se verifica que el archivo haya sido abierto correctamente.
3. Se recorre el archivo línea por línea utilizando **getline**.
4. Por cada línea encontrada se incrementa un contador.
5. Finalmente se retorna la cantidad total de pacientes encontrados.

Esta información es utilizada posteriormente para determinar el tamaño del arreglo dinámico que almacenará las estructuras Paciente.

---

### Lectura de pacientes desde el archivo

A continuación se define la función:

```cpp
Paciente* leer_datos_paciente(int &cantidad)
```

Esta función es la encargada de **leer el archivo pacientes.csv y cargar la información en un arreglo dinámico de estructuras Paciente**.

El proceso que realiza esta función es el siguiente:

1. Llama a la función **contarPacientes()** para determinar cuántos registros existen en el archivo.
2. Reserva memoria dinámica para un arreglo de estructuras **Paciente** utilizando **new**.
3. Abre nuevamente el archivo en modo lectura.
4. Lee cada línea del archivo utilizando **getline**.
5. Para cada línea:
   - Se separan los datos utilizando **separarLineaPaciente()**.
   - Se cargan los datos en la estructura correspondiente utilizando **cargarDatosPaciente()**.
6. Una vez finalizada la lectura, se asigna la cantidad total de pacientes al parámetro **cantidad**.
7. Finalmente se retorna el arreglo dinámico de pacientes cargados en memoria.

---

### Liberación de memoria dinámica

Finalmente se define la función:

```cpp
void liberarPacientes(Paciente* pacientes, int cantidad)
```

Esta función se encarga de **liberar toda la memoria dinámica utilizada para almacenar la información de los pacientes**.

El procedimiento que realiza es el siguiente:

1. Recorre el arreglo de pacientes utilizando un ciclo.
2. Para cada paciente libera la memoria reservada para cada uno de sus atributos mediante **delete[]**.
3. Una vez liberados todos los atributos, se libera el arreglo completo de pacientes utilizando **delete[]**.

Esta función es fundamental para evitar **fugas de memoria (memory leaks)** dentro del programa.

## ArchivoPacientes.h

Este archivo define la estructura ArchivoPacientes, la cual se utiliza para gestionar la información de todos los pacientes cargados desde el archivo pacientes.csv, asi como la cantidad de estos.

Dentro de esta estructura se declaran dos atributos principales:

- Paciente* pacientes  
  El cual es un arreglo dinámico de estructuras Paciente, el cual almacena la información de todos los pacientes leídos desde el archivo.  
  La estructura Paciente es definida en Paciente.h.

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
