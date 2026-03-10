# Sistema de Monitoreo de Señales Médicas

## Autores

* Diego Alejandro Torres Cely
* Juan Carlos Muñoz Muñoz

---

# Descripción del proyecto

Este proyecto implementa un sistema en **C++** que permite procesar y analizar mediciones médicas simuladas provenientes de diferentes sensores hospitalarios.

El sistema trabaja con datos almacenados en archivos **CSV**, **TXT** y **binarios (.bsf)** que contienen información de pacientes y lecturas médicas registradas por máquinas de monitoreo.

Entre las mediciones que se analizan se encuentran:

* Temperatura corporal
* Presión arterial (sistólica y diastólica)
* Nivel de oxígeno en sangre
* Señales de electrocardiograma (ECG)

El programa analiza estas lecturas utilizando rangos definidos en un archivo de configuración para detectar **posibles anomalías médicas**.

Además, el sistema permite generar reportes y exportar información procesada de pacientes con anomalías en ECG.

---

# Estructura general del sistema

El sistema está organizado jerárquicamente utilizando estructuras:

Sala
→ contiene varias **Máquinas**

Maquina
→ contiene varias **Mediciones**

Medicion
→ contiene varias **Lecturas**

Lectura
→ representa el valor individual registrado por un sensor médico.

Esto permite organizar los datos de forma similar a cómo se registrarían en un entorno hospitalario real.

---

# Archivos de entrada utilizados

El programa utiliza los siguientes archivos de datos:

**configuracion.txt**
Contiene los rangos mínimos y máximos permitidos para cada tipo de sensor médico.

**pacientes.csv**
Contiene la información básica de los pacientes registrados en el sistema.

**patient_readings_simulation_small.bsf**
Archivo binario que contiene las mediciones médicas simuladas generadas por las máquinas de monitoreo.

---

# Archivos generados por el programa

Durante la ejecución del sistema se generan los siguientes archivos:

**reporte_anomalias.txt**
Contiene un reporte detallado de todas las anomalías detectadas en las mediciones.

**pacientes_ecg_anomalos.bsf**
Archivo binario que almacena los pacientes que presentan anomalías en sus lecturas ECG junto con sus mediciones.

---

# Compilación y ejecución del programa (Visual Studio)

El proyecto fue desarrollado utilizando **Visual Studio / Visual Studio Code** y se entrega como un archivo **.zip** descargado desde GitHub.

## 1. Descomprimir el proyecto

Descargar el archivo `.zip` del repositorio y **descomprimirlo** en cualquier carpeta del computador.

Al descomprimirlo se obtendrá una estructura similar a la siguiente:

```
Proyecto
│
├── .vscode
│
├── CPP-Project-main
│   │
│   ├── .github
│   │
│   ├── data
│   │   ├── configuracion.txt
│   │   ├── pacientes.csv
│   │   └── generate binary file
│   │        └── patient_readings_simulation.txt
│   │
│   ├── generate_binary_files.cpp
│   ├── patient_readings_simulation.bsf
│   └── main.cpp
│
└── libs
    ├── Configuracion.h
    ├── Paciente.h
    ├── ArchivoPacientes.h
    ├── Lectura.h
    ├── Medicion.h
    ├── Maquina.h
    └── Sala.h
```

---

# 2. Abrir el proyecto

1. Abrir **Visual Studio Code**.
2. Seleccionar la opción **Open Folder**.
3. Elegir la carpeta raíz del proyecto que contiene:

```
CPP-Project-main
libs
.vscode
```

Esto cargará todos los archivos fuente del proyecto.

---

# 3. Ejecutar el programa

Una vez abierto el proyecto:

1. Abrir el archivo:

```
CPP-Project-main/main.cpp
```

2. Ejecutar el programa utilizando:

**Run / Start Debugging**

o presionando:

```
CTRL + F5
```

Esto abrirá una **consola** donde se mostrará el menú interactivo del sistema.

---

# 4. Ubicación de los archivos del proyecto

## Código fuente principal

El archivo principal del programa se encuentra en:

```
CPP-Project-main/main.cpp
```

Este archivo contiene:

* el menú principal del sistema
* la ejecución de las funcionalidades
* la carga de archivos
* el flujo general del programa

---

## Librerías del sistema

Las estructuras y funciones principales del sistema se encuentran en la carpeta:

```
libs/
```

Allí se encuentran los siguientes archivos:

* `Configuracion.h`
* `Paciente.h`
* `ArchivoPacientes.h`
* `Lectura.h`
* `Medicion.h`
* `Maquina.h`
* `Sala.h`

Estos archivos definen toda la lógica del sistema de monitoreo.

---

## Archivos de datos

Los archivos utilizados por el programa se encuentran en:

```
CPP-Project-main/data/
```

Entre ellos:

* `configuracion.txt`
  Contiene los rangos médicos permitidos.

* `pacientes.csv`
  Contiene la información de los pacientes.

* `patient_readings_simulation.txt`
  Contiene el formato del archivo binario que alimenta todas las estructuras de las máquinas, mediciones y lecturas.
  
---

# Funcionamiento del programa

Al ejecutarse, el programa muestra el siguiente menú:

1. Cargar archivo de configuracion y datos de pacientes
2. Leer archivo .bsf
3. Generar reporte de anomalias
4. Calcular estadisticas
5. Exportar datos procesados
6. Salir

Cada opción realiza una operación específica dentro del sistema.

---

# Flujo recomendado de ejecución

Para utilizar correctamente el programa se recomienda ejecutar las opciones en el siguiente orden:

**Paso 1 — Cargar configuración y pacientes**

Opción 1

El programa:

* Lee el archivo **configuracion.txt**
* Carga los rangos médicos permitidos
* Lee el archivo **pacientes.csv**
* Almacena los pacientes en memoria dinámica

---

**Paso 2 — Leer archivo binario de mediciones**

Opción 2

El programa:

* Abre el archivo **patient_readings_simulation_small.bsf**
* Lee las salas, máquinas, mediciones y lecturas
* Carga toda la información en memoria

---

**Paso 3 — Generar reporte de anomalías**

Opción 3

El sistema:

* Analiza todas las lecturas registradas por las máquinas
* Detecta valores fuera de los rangos permitidos
* Genera el archivo:

reporte_anomalias.txt

Este archivo contiene alertas detalladas indicando:

* máquina
* paciente
* fecha
* tipo de sensor
* valor detectado

---

**Paso 4 — Calcular estadísticas (ECG)**

Opción 4

El programa analiza las lecturas ECG de cada paciente para detectar posibles anomalías.

Si se detecta un problema, se muestra un mensaje en consola indicando el paciente afectado.

Al finalizar se muestra una estadística general indicando cuántos pacientes presentan anomalías ECG.

---

**Paso 5 — Exportar pacientes con ECG anómalo**

Opción 5

El sistema:

* identifica pacientes con anomalías ECG
* recopila sus lecturas ECG
* exporta los datos al archivo:

pacientes_ecg_anomalos.bsf

---

# Gestión de memoria

El sistema utiliza **memoria dinámica** para almacenar:

* pacientes
* salas
* máquinas
* mediciones
* lecturas

Por esta razón se implementaron funciones específicas para **liberar memoria correctamente** cuando:

* se recargan archivos
* se termina la ejecución del programa

Esto evita **fugas de memoria**.

---

# Validaciones implementadas

El programa incluye validaciones para detectar:

* archivos que no pueden abrirse
* datos corruptos en archivos binarios
* números inválidos de máquinas, mediciones o lecturas

Cuando se detecta un error, el sistema detiene la lectura y muestra un mensaje informativo en consola.

---

# Observaciones

Este proyecto fue desarrollado con fines académicos para practicar:

* manejo de **archivos binarios**
* manejo de **archivos CSV**
* uso de **memoria dinámica**
* organización de datos mediante **estructuras en C++**
* detección de anomalías en datos simulados de sensores médicos
