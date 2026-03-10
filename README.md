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

Este proyecto fue desarrollado y probado utilizando **Visual Studio**.

## Abrir el proyecto

1. Abrir **Visual Studio**.
2. Seleccionar **Open Folder** o abrir la solución del proyecto si existe.
3. Verificar que el archivo **main.cpp** esté incluido en el proyecto.

## Compilar el programa

Para compilar el programa:

1. Ir al menú **Build**.
2. Seleccionar **Build Solution**
   o presionar:

CTRL + SHIFT + B

Si no existen errores de compilación, Visual Studio generará el ejecutable del programa.

## Ejecutar el programa

Para ejecutar el programa:

1. Presionar el botón **Local Windows Debugger**
   o presionar:

CTRL + F5

Esto abrirá la consola donde se ejecutará el sistema.

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
