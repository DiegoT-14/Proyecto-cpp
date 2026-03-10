#ifndef CONFIGURACION_H
#define CONFIGURACION_H
#include <iostream>
#include <string> 
#include <sstream>   // para usar stringstream y separar texto
#include <cstdlib>   // para usar atof
#include <cstring>   // para strcmp y strncpy
#include <fstream>   // para manejo de archivos

struct Rango {
    double min;
    double max;
};

struct Configuracion {
   
    Rango temperatura;
    Rango presion_sistolica;
    Rango presion_diastolica;
    Rango oxigeno;
    Rango ecg;

    // --------------------------------------------------------
    // Función que separa una línea del archivo de configuración
    // Formato esperado: VARIABLE,MIN,MAX
    // --------------------------------------------------------
    void separarLineaConfig(std::string linea, char resultado[3][20]){
        std::stringstream ss(linea); // permite tratar la línea como flujo de texto
        std::string token;
        int i = 0;

        // Separar la línea usando ',' como delimitador
        while(std::getline(ss,token,',') && i < 3){
            std::strncpy(resultado[i],token.c_str(),19); // copiar token al arreglo
            resultado[i][19] = '\0'; // asegurar fin de cadena
            i++;
        }
    }

    // --------------------------------------------------------
    // Carga los valores numéricos en la estructura correspondiente
    // resultado[0] -> tipo de variable
    // resultado[1] -> valor mínimo
    // resultado[2] -> valor máximo
    // --------------------------------------------------------
    void cargarDatosConfig(char resultado[3][20]){

        // Temperatura
        if (std::strcmp(resultado[0], "T") == 0) {
            temperatura.min = std::atof(resultado[1]);
            temperatura.max = std::atof(resultado[2]);

        // Presión sistólica
        } else if (std::strcmp(resultado[0], "P_SIS") == 0) {
            presion_sistolica.min = std::atof(resultado[1]);
            presion_sistolica.max = std::atof(resultado[2]);

        // Presión diastólica
        } else if (std::strcmp(resultado[0], "P_DIA") == 0) {
            presion_diastolica.min = std::atof(resultado[1]);
            presion_diastolica.max = std::atof(resultado[2]);

        // ECG
        } else if (std::strcmp(resultado[0], "E") == 0) {
            ecg.min = std::atof(resultado[1]);
            ecg.max = std::atof(resultado[2]);

        // Oxígeno
        } else if (std::strcmp(resultado[0], "O") == 0) {
            oxigeno.min = std::atof(resultado[1]);
            oxigeno.max = std::atof(resultado[2]);
        }
    }

    // --------------------------------------------------------
    // Lee el archivo de configuración
    // --------------------------------------------------------
    int leer_archivo_configuracion(){

        std::fstream archivo;
        std::string linea;
        char resultado [3][20]; // almacenará variable, min y max

        // ruta del archivo de configuración
        std::string nombrearchivo = "data/configuracion.txt";

        // abrir archivo en modo lectura
        archivo.open(nombrearchivo.c_str(), std::ios::in);

        // verificar si el archivo se abrió correctamente
        if(archivo.fail()){
            std::cout<<"no se pudo abrir"<<std::endl;
            return 0;
        }

        // leer el archivo línea por línea
        while (std::getline(archivo,linea)){
            separarLineaConfig(linea, resultado); // separar la línea
            cargarDatosConfig(resultado);         // cargar los valores
        }

        archivo.close(); // cerrar archivo
        return 1; // indicar que se leyó correctamente
    }
};

#endif // CONFIGURACION_H