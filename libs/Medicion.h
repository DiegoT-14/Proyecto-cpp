#ifndef MEDICION_H
#define MEDICION_H
#include "Lectura.h"        
#include "Configuracion.h"

struct Medicion { 

    char* id_paciente;
    char* fecha_y_hora; 
    unsigned int numlecturas;
    Lectura* lecturas; 

    // --------------------------------------------------------
    // Constructor que inicializa los punteros en nullptr
    // --------------------------------------------------------
    Medicion() {
        id_paciente = nullptr;
        fecha_y_hora = nullptr;
        lecturas = nullptr;
        numlecturas = 0;
    }

    // --------------------------------------------------------
    // Libera la memoria dinámica utilizada por la medición
    // --------------------------------------------------------
    void liberar() {

        if (id_paciente != nullptr) {
            delete[] id_paciente;
            id_paciente = nullptr;
        }
        
        if (fecha_y_hora != nullptr) {
            delete[] fecha_y_hora;
            fecha_y_hora = nullptr;
        }
        
        if (lecturas != nullptr) {
            delete[] lecturas;
            lecturas = nullptr;
        }
        
        numlecturas = 0;
    }
};

// --------------------------------------------------------
// Determina si la presión sistólica está fuera de rango
// --------------------------------------------------------
bool detectarAnomaliaSistolica(Lectura lec, Configuracion cfg) {
    if (lec.tipo == 'P') {
        if (lec.sistolica < cfg.presion_sistolica.min || lec.sistolica > cfg.presion_sistolica.max) return true;
    }
    return false;
}

// --------------------------------------------------------
// Determina si la presión diastólica está fuera de rango
// --------------------------------------------------------
bool detectarAnomaliaDiastolica(Lectura lec, Configuracion cfg) {
    if (lec.tipo == 'P') {
        if (lec.diastolica < cfg.presion_diastolica.min || lec.diastolica > cfg.presion_diastolica.max) return true;
    }
    return false;
}

// --------------------------------------------------------
// Determina si una lectura está fuera del rango permitido
// según la configuración cargada
// --------------------------------------------------------
bool detectarAnomalia(Lectura lec, Configuracion cfg) {

    // las lecturas de tipo ECG no se evalúan como anomalía
    if (lec.tipo == 'E') return false; 
    
    // Temperatura
    if (lec.tipo == 'T') {
        if (lec.valor < cfg.temperatura.min || lec.valor > cfg.temperatura.max) return true; 
    }
    
    // Oxígeno
    if (lec.tipo == 'O') {
        if (lec.valor < cfg.oxigeno.min || lec.valor > cfg.oxigeno.max) return true; 
    }

    // Presión
    if (lec.tipo == 'P') {
        if (detectarAnomaliaSistolica(lec, cfg) || detectarAnomaliaDiastolica(lec, cfg)) return true;
    }

    return false; 
}

// --------------------------------------------------------
// Compara dos fechas en formato texto
// Retorna true si f1 es posterior a f2
// --------------------------------------------------------
bool compararFecha(char f1[], char f2[]) {

    // comparar año
    for (int i = 6; i <= 9; i++) {
        if (f1[i] > f2[i]) return true;  
        if (f1[i] < f2[i]) return false; 
    }

    // comparar mes
    for (int i = 3; i <= 4; i++) {
        if (f1[i] > f2[i]) return true;
        if (f1[i] < f2[i]) return false;
    }

    // comparar día
    for (int i = 0; i <= 1; i++) {
        if (f1[i] > f2[i]) return true;
        if (f1[i] < f2[i]) return false;
    }

    // comparar hora
    for (int i = 11; i < 24; i++) {
        if (f1[i] == '\0') break; 
        if (f1[i] > f2[i]) return true;
        if (f1[i] < f2[i]) return false;
    }

    return false; 
}

// --------------------------------------------------------
// Ordena las mediciones por fecha usando bubble sort
// --------------------------------------------------------
void ordenarMedicionesPorFecha(Medicion mediciones[], int n) {

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - 1 - i; j++) {

            if (compararFecha(mediciones[j].fecha_y_hora, mediciones[j + 1].fecha_y_hora)) {

                // intercambio de posiciones
                Medicion tmp = mediciones[j];
                mediciones[j] = mediciones[j + 1];
                mediciones[j + 1] = tmp;
            }
        }
    }
}

#endif // MEDICION_H