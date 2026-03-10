# Proyecto-cpp
## Diego Alejandro Torres Cely, Juan Carlos Muñoz Muñoz

## Descripción del proyecto

Este proyecto implementa un sistema de análisis de mediciones médicas simuladas en un entorno hospitalario.

El sistema permite:

- Leer información de pacientes desde un archivo CSV.
- Cargar mediciones médicas desde un archivo binario.
- Analizar las lecturas fisiológicas registradas por diferentes sensores.
- Detectar anomalías en variables como temperatura, presión arterial, oxígeno y ECG.
- Generar reportes de anomalías detectadas.
- Exportar pacientes con anomalías en señales ECG.

La arquitectura del sistema se basa en múltiples estructuras interrelacionadas que representan pacientes, lecturas médicas, mediciones, máquinas de monitoreo y salas hospitalarias.

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

## Configuracion.h

Este archivo define las estructuras necesarias para **gestionar los valores de configuración del sistema**, los cuales establecen los rangos mínimos y máximos permitidos para diferentes variables médicas monitoreadas.

Estos valores son leídos desde el archivo **configuracion.txt**, el cual contiene los rangos permitidos para cada una de las variables fisiológicas analizadas por el sistema.

Dentro de este archivo se definen dos estructuras principales: **Rango** y **Configuracion**.

---

### Estructura Rango

La estructura **Rango** se utiliza para representar los límites mínimo y máximo permitidos para una variable médica específica.

Dentro de esta estructura se declaran dos atributos principales:

- double min  
  Representa el valor mínimo permitido para una determinada variable.

- double max  
  Representa el valor máximo permitido para dicha variable.

Esta estructura permite almacenar de forma organizada los límites aceptables de cada señal médica evaluada por el sistema.

---

### Estructura Configuracion

La estructura **Configuracion** se utiliza para almacenar los rangos permitidos de todas las variables fisiológicas que son analizadas dentro del sistema.

Para cada variable se utiliza un atributo de tipo **Rango**, lo cual permite almacenar de manera clara sus valores mínimo y máximo.

Los atributos definidos dentro de esta estructura son los siguientes:

- Rango temperatura  
- Rango presion_sistolica  
- Rango presion_diastolica  
- Rango oxigeno  
- Rango ecg
  
Cada uno de estos atributos será cargado posteriormente con los valores obtenidos desde el archivo de configuración.

---

### Separación de datos del archivo de configuración

Dentro de la estructura **Configuracion** se define la función:

```cpp
void separarLineaConfig(std::string linea, char resultado[3][20])
```

Esta función se encarga de **procesar cada línea del archivo de configuración y separar sus diferentes campos de información**.

El formato esperado dentro del archivo es el siguiente:

```
VARIABLE,MIN,MAX
```

Donde:

- **VARIABLE** indica el tipo de señal médica.
- **MIN** corresponde al valor mínimo permitido.
- **MAX** corresponde al valor máximo permitido.

Para realizar esta separación se utiliza **stringstream**, el cual permite tratar la línea de texto como un flujo de datos y dividirla utilizando la coma **','** como delimitador.

El proceso realizado por esta función es el siguiente:

1. Recibe una línea completa del archivo de configuración.
2. Convierte la línea en un flujo de datos utilizando **stringstream**.
3. Separa cada elemento utilizando **getline** con el delimitador ','.
4. Copia cada uno de los valores obtenidos en el arreglo **resultado**, el cual almacena:
   - resultado[0] → tipo de variable  
   - resultado[1] → valor mínimo  
   - resultado[2] → valor máximo  

---

### Carga de datos en la estructura

Posteriormente se define la función:

```cpp
void cargarDatosConfig(char resultado[3][20])
```

Esta función tiene como objetivo **asignar los valores mínimos y máximos obtenidos desde el archivo de configuración a los atributos correspondientes de la estructura Configuracion**.

Para lograr esto se realiza el siguiente procedimiento:

1. Se identifica el tipo de variable utilizando la función **strcmp**.
2. Dependiendo del identificador encontrado, se determina a qué atributo de la estructura corresponde el rango.
3. Los valores mínimo y máximo son convertidos de texto a tipo **double** utilizando la función **atof**.
4. Finalmente estos valores son almacenados en la estructura **Rango** correspondiente.

De esta manera, cada línea del archivo de configuración actualiza los valores de la variable médica correspondiente dentro del sistema.

---

### Lectura del archivo de configuración

Finalmente se define la función:

```cpp
int leer_archivo_configuracion()
```

Esta función es la encargada de **leer el archivo configuracion.txt y cargar todos los rangos definidos dentro de la estructura Configuracion**.

El procedimiento que realiza esta función es el siguiente:

1. Se define la ruta del archivo de configuración ubicado en **data/configuracion.txt**.
2. Se abre el archivo utilizando **fstream** en modo lectura.
3. Se verifica si el archivo fue abierto correctamente.
4. Se recorre el archivo línea por línea utilizando **getline**.
5. Para cada línea:
   - Se separan los datos mediante la función **separarLineaConfig()**.
   - Se cargan los valores correspondientes mediante **cargarDatosConfig()**.
6. Una vez finalizada la lectura, el archivo es cerrado.
7. Finalmente la función retorna **1** si la lectura fue exitosa, o **0** en caso de que no se haya podido abrir el archivo.

Esta función permite inicializar los parámetros de funcionamiento del sistema antes de realizar el análisis de las mediciones médicas.

## Paciente.h

Este archivo define la estructura **Paciente**, la cual se utiliza para almacenar la información correspondiente a cada paciente registrada dentro del sistema.  
Los datos de los pacientes son leídos desde el archivo **pacientes.csv**, procesados y posteriormente almacenados en memoria mediante estructuras dinámicas.

Dentro de esta estructura se declaran múltiples atributos, los cuales representan la información básica de cada paciente registrada en el archivo.

Los atributos definidos son los siguientes:

- char* id_paciente
- char* tipo_doc  
- char* documento  
- char* nombre  
- char* apellido  
- char* fecha_nacimiento  
- char* telefono  
- char* email  
- char* tipo_sangre  
- char* entidad_salud  
- char* medicina_Prepagada  

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

Esta función es fundamental para evitar **fugas de memoria** dentro del programa.

## ArchivoPacientes.h

Este archivo define la estructura ArchivoPacientes, la cual se utiliza para gestionar la información de todos los pacientes cargados desde el archivo pacientes.csv, así como la cantidad de estos.

Dentro de esta estructura se declaran dos atributos principales:

- Paciente* pacientes  
  El cual es un arreglo dinámico de estructuras Paciente, el cual almacena la información de todos los pacientes leídos desde el archivo.  
  La estructura Paciente es definida en Paciente.h.

- int cantidad  
  Esta variable almacena la cantidad total de pacientes cargados en memoria.

Posteriormente se define un constructor para la estructura, cuyo objetivo es inicializar correctamente los atributos antes de que la estructura sea utilizada. Este tipo de constructores no se vieron en el curso sin embargo, fue diseñada con ayuda de ChatGPT con el fin de evitar que las variables guarden "Basura" al momento de crearlas como dinamicas.

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

Este archivo define la estructura **Lectura**, la cual se utiliza para representar una lectura individual proveniente de un sensor médico.

Cada medición realizada por una máquina de monitoreo puede contener múltiples lecturas correspondientes a diferentes variables fisiológicas, como temperatura corporal, presión arterial, nivel de oxígeno en sangre o señales de electrocardiograma (ECG).

La estructura **Lectura** permite almacenar estos valores de manera organizada para que posteriormente puedan ser analizados por el sistema y comparados con los rangos definidos en el archivo de configuración.

---

### Estructura Lectura

La estructura **Lectura** representa una única lectura obtenida por un sensor médico.

Dentro de esta estructura se definen los siguientes atributos:

- char tipo  
  Indica el tipo de sensor que generó la lectura. Este carácter permite identificar qué variable fisiológica está siendo registrada.

  Los valores posibles son:

  - **T** → Temperatura corporal  
  - **O** → Nivel de oxígeno en sangre  
  - **P** → Presión arterial  
  - **E** → Señal de electrocardiograma (ECG)

- double valor  
  Almacena el valor numérico de la lectura para los sensores que registran **una sola medición**, como temperatura, oxígeno o ECG.

- double sistolica  
  Contiene el valor de **presión sistólica**.

- double diastolica  
  Contiene el valor de **presión diastólica**.

---

### Uso dentro del sistema

Las estructuras **Lectura** son utilizadas dentro de la estructura **Medicion**, donde se almacenan en un **arreglo dinámico de lecturas**.

Cada medición puede contener múltiples lecturas provenientes de diferentes sensores.  
Posteriormente, estas lecturas son analizadas para determinar si alguno de los valores se encuentra **fuera de los rangos permitidos definidos en el archivo de configuración**.

Dependiendo del tipo de sensor, el sistema utilizará diferentes atributos de la estructura:

- Para **temperatura, oxígeno o ECG**, se utiliza el atributo **valor**.
- Para **presión arterial**, se utilizan los atributos **sistolica** y **diastolica**.

Esta estructura constituye la **unidad básica de información médica dentro del sistema de monitoreo**, ya que representa cada valor registrado por los sensores.

## Medicion.h

Este archivo define la estructura **Medicion**, la cual se utiliza para almacenar la información correspondiente a una medición médica realizada a un paciente.

Cada medición contiene un conjunto de **lecturas fisiológicas** tomadas en un momento específico, como temperatura, presión arterial, nivel de oxígeno o señales ECG.  
Estas lecturas son posteriormente analizadas por el sistema para determinar si alguna de ellas se encuentra fuera de los rangos permitidos definidos en el archivo de configuración.

Para poder realizar estas operaciones, este archivo utiliza las estructuras definidas en **Lectura.h** y **Configuracion.h**.

---

### Estructura Medicion

La estructura **Medicion** se utiliza para almacenar toda la información relacionada con una medición médica realizada a un paciente.

Dentro de esta estructura se declaran los siguientes atributos:

- char* id_paciente  
- char* fecha_y_hora  
- unsigned int numlecturas  
- Lectura* lecturas
  
Este arreglo permite almacenar múltiples valores fisiológicos asociados a un mismo momento de registro.

---

### Constructor de la estructura

Dentro de la estructura se define un constructor cuyo objetivo es **inicializar los punteros en nullptr y los contadores en cero**, evitando referencias a memoria no inicializada.

```cpp
Medicion() {
    id_paciente = nullptr;
    fecha_y_hora = nullptr;
    lecturas = nullptr;
    numlecturas = 0;
}
```

Este constructor garantiza que cada estructura **Medicion** comience en un estado seguro antes de cargar los datos provenientes del sistema de medición.

---

### Liberación de memoria dinámica

Posteriormente se define la función:

```cpp
void liberar()
```

Esta función se encarga de **liberar la memoria dinámica utilizada por una medición**.

El procedimiento realizado es el siguiente:

1. Verifica si el puntero **id_paciente** contiene memoria reservada.
2. En caso afirmativo, libera la memoria utilizando **delete[]**.
3. Realiza el mismo procedimiento para el atributo **fecha_y_hora**.
4. Libera el arreglo dinámico de **lecturas** si este existe.
5. Finalmente restablece los punteros a **nullptr** y el contador de lecturas a **0**.

Este procedimiento permite evitar **fugas de memoria** dentro del programa.

---

### Detección de anomalías en presión sistólica

A continuación se define la función:

```cpp
bool detectarAnomaliaSistolica(Lectura lec, Configuracion cfg)
```

Esta función determina si una **lectura de presión sistólica se encuentra fuera del rango permitido** definido en la configuración del sistema.

El proceso realizado es el siguiente:

1. Verifica si la lectura corresponde al tipo **P** (presión arterial).
2. Compara el valor de presión sistólica con los límites mínimo y máximo definidos en la configuración.
3. Si el valor se encuentra fuera del rango permitido, retorna **true**, indicando la presencia de una anomalía.

---

### Detección de anomalías en presión diastólica

Posteriormente se define la función:

```cpp
bool detectarAnomaliaDiastolica(Lectura lec, Configuracion cfg)
```

Esta función realiza el mismo procedimiento que la anterior, pero aplicado a la **presión arterial diastólica**.

El procedimiento consiste en:

1. Verificar que la lectura sea del tipo **P**.
2. Comparar el valor de presión diastólica con los límites permitidos.
3. Retornar **true** si el valor se encuentra fuera del rango establecido.

---

### Detección general de anomalías

La función principal de análisis se define como:

```cpp
bool detectarAnomalia(Lectura lec, Configuracion cfg)
```

Esta función permite **determinar si una lectura fisiológica se encuentra fuera de los rangos permitidos definidos en el archivo de configuración**.

El proceso realizado es el siguiente:

1. Si la lectura corresponde a un **ECG**, esta no se evalúa como anomalía y la función retorna **false**.
2. Si la lectura es de **temperatura**, se compara con el rango definido para temperatura.
3. Si la lectura corresponde al **nivel de oxígeno**, se compara con su rango permitido.
4. Si la lectura corresponde a **presión arterial**, se utilizan las funciones:
   - **detectarAnomaliaSistolica()**
   - **detectarAnomaliaDiastolica()**

Si cualquiera de estos valores se encuentra fuera de los límites permitidos, la función retorna **true**, indicando la presencia de una anomalía.

---

### Comparación de fechas de medición

A continuación se define la función:

```cpp
bool compararFecha(char f1[], char f2[])
```

Esta función se utiliza para **comparar dos fechas almacenadas en formato texto**.

El objetivo es determinar si la fecha **f1** es posterior a la fecha **f2**.

El procedimiento consiste en comparar secuencialmente los componentes de la fecha:

1. Primero se comparan los **años**.
2. Si los años son iguales, se comparan los **meses**.
3. Posteriormente se comparan los **días**.
4. Finalmente se comparan las **horas**.

Si en cualquiera de estas comparaciones se determina que **f1 es posterior a f2**, la función retorna **true**.

---

### Ordenamiento de mediciones por fecha

Finalmente se define la función:

```cpp
void ordenarMedicionesPorFecha(Medicion mediciones[], int n)
```

Esta función se encarga de **ordenar un arreglo de mediciones según la fecha en la que fueron realizadas**.

Para realizar este proceso se utiliza el algoritmo **Bubble Sort**, el cual compara elementos consecutivos del arreglo e intercambia sus posiciones cuando se encuentran en un orden incorrecto.

El procedimiento realizado es el siguiente:

1. Se recorre el arreglo de mediciones múltiples veces.
2. En cada iteración se comparan dos mediciones consecutivas utilizando la función **compararFecha()**.
3. Si una medición se encuentra posterior a la siguiente, ambas posiciones son intercambiadas.
4. El proceso se repite hasta que todas las mediciones quedan ordenadas cronológicamente.

Este ordenamiento permite analizar las mediciones médicas **siguiendo la secuencia temporal en la que fueron registradas**.

## Maquina.h

Este archivo define la estructura **Maquina**, la cual representa un dispositivo de monitoreo médico dentro de una sala hospitalaria.

Cada máquina es responsable de registrar múltiples **mediciones médicas** realizadas a diferentes pacientes.  
Cada medición contiene a su vez varias **lecturas fisiológicas**, las cuales son analizadas posteriormente para detectar posibles anomalías en los signos vitales.

Las estructuras definidas en este archivo permiten organizar y gestionar las mediciones registradas por cada máquina dentro del sistema.

---

### Estructura Maquina

La estructura **Maquina** se utiliza para almacenar la información correspondiente a una máquina de monitoreo médico y las mediciones que ha registrado.

Dentro de esta estructura se declaran los siguientes atributos:

- char id_maquina  
- unsigned int num_mediciones  
- Medicion* mediciones  

Cada medición contiene información del paciente, la fecha en que se realizó el registro y las lecturas fisiológicas capturadas por los sensores.

---

### Constructor de la estructura

Dentro de la estructura se define un constructor cuyo objetivo es **inicializar el arreglo de mediciones en nullptr y el contador en cero**, evitando referencias a memoria no inicializada.

```cpp
Maquina() {
    mediciones = nullptr;
    num_mediciones = 0;
}
```

Este constructor garantiza que cada estructura **Maquina** comience en un estado seguro antes de que se carguen los datos provenientes del archivo binario.

---

### Liberación de memoria dinámica

Posteriormente se define la función:

```cpp
void liberar()
```

Esta función se encarga de **liberar la memoria dinámica utilizada para almacenar las mediciones registradas por la máquina**.

El procedimiento realizado es el siguiente:

1. Verifica si el arreglo de mediciones contiene memoria reservada.
2. Recorre cada medición almacenada en la máquina.
3. Para cada medición se llama a su función **liberar()**, la cual libera las lecturas asociadas.
4. Finalmente se libera el arreglo dinámico de mediciones utilizando **delete[]**.

Este proceso evita **fugas de memoria** y garantiza que el programa libere correctamente los recursos utilizados.

---

### Generación de reportes de anomalías

A continuación se define la función:

```cpp
void generarReporteMaquina(Maquina &maq, Configuracion cfg)
```

Esta función se encarga de **analizar todas las lecturas registradas por una máquina y generar un reporte de las anomalías detectadas**.

El reporte generado es almacenado en el archivo **reporte_anomalias.txt**.

El procedimiento que realiza esta función es el siguiente:

1. Se abre el archivo de reporte en modo escritura utilizando **fstream**.
2. Se verifica que el archivo haya sido abierto correctamente.
3. Se recorren todas las mediciones registradas por la máquina.
4. Para cada medición se recorren todas las lecturas almacenadas.
5. Cada lectura es evaluada mediante la función **detectarAnomalia()**, la cual compara el valor registrado con los rangos definidos en la configuración del sistema.

Si se detecta una anomalía, se escribe en el archivo la siguiente información:

- Identificador de la máquina.
- Identificador del paciente.
- Fecha y hora de la medición.
- Tipo de sensor que generó la anomalía.
- Valor registrado por el sensor.

En el caso de **presión arterial**, la función también identifica si la anomalía corresponde a:

- **Presión sistólica**, o
- **Presión diastólica**.

De esta manera el archivo de reporte permite identificar fácilmente qué mediciones presentan valores fuera de los rangos normales definidos por el sistema.

---

### Uso dentro del sistema

Las estructuras **Maquina** son utilizadas dentro de la estructura **Sala**, donde se almacenan en un arreglo dinámico que representa todas las máquinas presentes en una sala de monitoreo.

Cada máquina gestiona sus propias mediciones, las cuales posteriormente son utilizadas para:

- Detectar anomalías en los signos vitales.
- Generar reportes médicos.
- Analizar el comportamiento de las señales fisiológicas de los pacientes.

De esta manera, la estructura **Maquina** funciona como el componente encargado de **gestionar y analizar las mediciones médicas registradas por cada dispositivo de monitoreo** dentro del sistema.

## Sala.h

Este archivo define la estructura **Sala**, la cual se utiliza para representar una sala de monitoreo dentro del sistema médico.

Cada sala contiene un conjunto de **máquinas de monitoreo**, las cuales registran mediciones médicas de diferentes pacientes.  
Estas máquinas almacenan múltiples mediciones, y cada medición a su vez contiene diversas lecturas fisiológicas.

La información de las salas, máquinas, mediciones y lecturas es cargada desde un **archivo binario de simulación**, el cual representa los datos generados por el sistema de monitoreo médico.

Para el correcto funcionamiento de esta estructura, el archivo utiliza las definiciones presentes en **Maquina.h**, **Medicion.h**, **Lectura.h**, **Paciente.h** y **ArchivoPacientes.h**.

---

### Estructura Sala

La estructura **Sala** se utiliza para almacenar la información de una sala de monitoreo y las máquinas que se encuentran dentro de ella.

Dentro de esta estructura se definen los siguientes atributos:

- char id_sala  
- uint8_t num_maquinas  
- Maquina* maquinas

Este arreglo permite organizar todas las mediciones médicas generadas por los dispositivos de monitoreo.

---

### Constructor de la estructura

Dentro de la estructura se define un constructor cuyo objetivo es **inicializar los punteros en nullptr y los contadores en cero**, evitando referencias a memoria no inicializada.

```cpp
Sala(){
    maquinas = nullptr;
    num_maquinas = 0;
}
```

Este constructor garantiza que cada estructura **Sala** comience en un estado seguro antes de cargar la información proveniente del archivo binario.

---

### Liberación de memoria dinámica

Posteriormente se define la función:

```cpp
void liberar()
```

Esta función se encarga de **liberar la memoria dinámica utilizada por las máquinas almacenadas dentro de la sala**.

El procedimiento realizado es el siguiente:

1. Verifica si el arreglo de máquinas contiene memoria reservada.
2. Recorre cada máquina de la sala.
3. Llama a la función **liberar()** de cada máquina para liberar sus mediciones.
4. Libera el arreglo dinámico de máquinas utilizando **delete[]**.
5. Finalmente restablece el puntero a **nullptr** y el número de máquinas a **0**.

Este proceso permite evitar **fugas de memoria** dentro del sistema.

---

### Lectura del archivo binario de mediciones

A continuación se define la función:

```cpp
int leer_binario(Sala salas[], int max)
```

Esta función es la encargada de **leer el archivo binario que contiene las mediciones simuladas de los pacientes y cargar dicha información en el arreglo de salas**.

El archivo utilizado es **patient_readings_simulation.bsf**, el cual contiene la estructura completa de datos del sistema de monitoreo.

El procedimiento que realiza esta función es el siguiente:

1. Abre el archivo binario en modo lectura utilizando **fstream** con la bandera **ios::binary**.
2. Verifica que el archivo haya sido abierto correctamente.
3. Lee el **identificador de la sala**.
4. Lee el **número de máquinas presentes en la sala**.
5. Se valida que el número de máquinas sea correcto para evitar datos corruptos.
6. Se crea dinámicamente el arreglo de **Maquina** correspondiente.
7. Para cada máquina se realiza el siguiente proceso:
   - Se lee el identificador de la máquina.
   - Se lee la cantidad de mediciones registradas.
   - Se valida que el número de mediciones sea válido.
8. Para cada medición se realizan las siguientes operaciones:
   - Se reserva memoria para el **ID del paciente**.
   - Se reserva memoria para la **fecha y hora de la medición**.
   - Se lee el número de lecturas registradas.
   - Se crea el arreglo dinámico de **Lectura**.
9. Finalmente se leen todas las lecturas registradas por los sensores.

Dependiendo del tipo de sensor, se almacenan diferentes valores:

- Para **presión arterial (P)** se almacenan los valores sistólico y diastólico.
- Para **temperatura, oxígeno o ECG** se almacena un único valor numérico.

La función retorna el número total de salas cargadas correctamente desde el archivo.

---

### Detección de anomalías en señales ECG

Posteriormente se define la función:

```cpp
bool detectar_anomalia_ecg(Sala salas[], int num_salas, char* paciente_buscado, Configuracion cfg)
```

Esta función permite **analizar las lecturas ECG de un paciente específico y determinar si existe una anomalía en dichas mediciones**.

El proceso realizado es el siguiente:

1. Se recorren todas las salas cargadas en memoria.
2. Dentro de cada sala se recorren todas las máquinas disponibles.
3. Se analizan todas las mediciones registradas por cada máquina.
4. Se verifica si la medición corresponde al paciente buscado.
5. Si la lectura es de tipo **ECG (E)** se registra su valor.

Durante el recorrido se identifican:

- El valor mínimo registrado en las lecturas ECG.
- El valor máximo registrado en las lecturas ECG.

Posteriormente se calcula:

- La suma del valor absoluto del mínimo y el máximo encontrados.
- La suma de los valores absolutos de los límites permitidos definidos en la configuración.

Si la suma de las mediciones supera la suma de los límites configurados, se determina que el paciente presenta **una anomalía en sus lecturas ECG**.

---

### Estructura temporal para exportación de ECG

Dentro de este archivo también se define la estructura:

```cpp
struct DatoECGExportar
```

Esta estructura se utiliza como **estructura temporal para almacenar las lecturas ECG de un paciente antes de ser exportadas a un archivo binario**.

Sus atributos son:

- char fecha_y_hora[24]  
  Almacena la fecha y hora en la que se realizó la lectura ECG.

- double valor  
  Contiene el valor registrado por el sensor ECG.

---

### Exportación de pacientes con anomalías ECG

A continuación se define la función:

```cpp
void exportar_pacientes_ecg_anomalos(...)
```

Esta función se encarga de **generar un archivo binario que contiene los pacientes que presentan anomalías en sus señales ECG**.

El procedimiento realizado es el siguiente:

1. Se crea un archivo binario llamado **pacientes_ecg_anomalos.bsf**.
2. Se recorren todos los pacientes almacenados en la base de datos.
3. Para cada paciente se ejecuta la función **detectar_anomalia_ecg()**.
4. Si el paciente presenta anomalías:
   - Se recopilan todas sus lecturas ECG.
   - Se almacenan temporalmente en un arreglo de estructuras **DatoECGExportar**.
5. Posteriormente se escriben en el archivo binario:
   - El identificador del paciente.
   - El número de lecturas ECG registradas.
   - La fecha y hora de cada lectura.
   - El valor correspondiente a cada medición.

Finalmente se muestra un mensaje indicando la cantidad de pacientes exportados.

---

### Liberación de memoria de las salas

Finalmente se define la función:

```cpp
void liberarSalas(Sala salas[], int total_salas)
```

Esta función se encarga de **liberar toda la memoria dinámica utilizada por las salas cargadas en el sistema**.

El procedimiento consiste en:

1. Recorrer el arreglo de salas.
2. Para cada sala llamar a su función **liberar()**.
3. De esta manera se liberan todas las máquinas, mediciones y lecturas asociadas.

Este proceso asegura que el programa finalice sin dejar memoria reservada innecesariamente.
