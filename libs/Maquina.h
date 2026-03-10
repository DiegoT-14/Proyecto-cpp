#ifndef MAQUINA_H
#define MAQUINA_H
#include "Medicion.h" 
#include <fstream>      // para manejo de archivos
#include <iostream>     // para mostrar mensajes de error

struct Maquina {

    char id_maquina;
    unsigned int num_mediciones;
    Medicion* mediciones;

    // --------------------------------------------------------
    // Constructor que inicializa el arreglo en nullptr
    // --------------------------------------------------------
    Maquina() {
        mediciones = nullptr;
        num_mediciones = 0;
    }

    // --------------------------------------------------------
    // Libera la memoria utilizada por las mediciones
    // --------------------------------------------------------
    void liberar() {

        if (mediciones != nullptr) {
            
            // liberar cada medición almacenada
            for (unsigned int i = 0; i < num_mediciones; i++) {
                mediciones[i].liberar();
            }
            
            delete[] mediciones;
            mediciones = nullptr;
            num_mediciones = 0;
        }
    }
};

// --------------------------------------------------------
// Genera un reporte de anomalías detectadas por la máquina
// --------------------------------------------------------
void generarReporteMaquina(Maquina &maq, Configuracion cfg) {
    
    // abrir archivo de reporte en modo escritura
    std::fstream archivo_reporte("reporte_anomalias.txt", std::ios::out);

    // verificar que el archivo se haya abierto correctamente
    if (!archivo_reporte.is_open()) {
        std::cout << "Error al abrir el archivo de reporte." << std::endl;
        return; 
    }

    // recorrer todas las mediciones de la máquina
    for (unsigned int i = 0; i < maq.num_mediciones; i++) {
        
        // recorrer todas las lecturas de cada medición
        for (unsigned int j = 0; j < maq.mediciones[i].numlecturas; j++) {
            
            Lectura lectura_actual = maq.mediciones[i].lecturas[j];

            // verificar si la lectura está fuera del rango permitido
            if (detectarAnomalia(lectura_actual, cfg) == true) {
                
                // escribir información de la anomalía en el reporte
                archivo_reporte << "--- ALERTA ---" << std::endl;
                archivo_reporte << "Maquina ID: " << (int)maq.id_maquina << std::endl;
                archivo_reporte << "Paciente ID: " << maq.mediciones[i].id_paciente << std::endl;
                archivo_reporte << "Fecha: " << maq.mediciones[i].fecha_y_hora << std::endl;
                
                // detallar el tipo de anomalía
                if (lectura_actual.tipo == 'P') {
                    // anomalía de presión - detallar si es sistólica o diastólica
                    if (detectarAnomaliaSistolica(lectura_actual, cfg)) {
                        archivo_reporte << "Sensor: P SIS || Valor: " << lectura_actual.sistolica << std::endl;
                    }
                    if (detectarAnomaliaDiastolica(lectura_actual, cfg)) {
                        archivo_reporte << "Sensor: P DIA || Valor: " << lectura_actual.diastolica << "\n" << std::endl;
                    }
                } else {
                    // otros tipos de anomalía
                    archivo_reporte << "Sensor: " << lectura_actual.tipo << " || Valor: " << lectura_actual.valor << "\n" << std::endl;
                }
            }
        }
    }

    archivo_reporte.close(); // cerrar archivo de reporte
}

#endif // MAQUINA_H