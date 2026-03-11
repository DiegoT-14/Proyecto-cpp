#ifndef SALA_H
#define SALA_H
#include "Maquina.h"
#include "ArchivoPacientes.h"
#include "Paciente.h"
#include <cmath>  // para usar fabs

struct Sala {

    char id_sala;
    uint8_t num_maquinas;
    Maquina* maquinas;

    // --------------------------------------------------------
    // Constructor que inicializa el arreglo en nullptr
    // --------------------------------------------------------
    Sala(){
        maquinas = nullptr;
        num_maquinas = 0;
    }

    // --------------------------------------------------------
    // Libera la memoria utilizada
    // --------------------------------------------------------
    void liberar() {
        if (maquinas != nullptr) {

            for (unsigned int i = 0; i < num_maquinas; i++) {
                maquinas[i].liberar(); 
            }

            delete[] maquinas;
            maquinas = nullptr;
            num_maquinas = 0;
        }
    }
};

// --------------------------------------------------------
// Lee el archivo binario con las mediciones simuladas
// y carga la información en el arreglo
// --------------------------------------------------------
int leer_binario(Sala salas[], int max){

    std::string nombrearchivo = "patient_readings_simulation_small.bsf";
    std::fstream archivo;

    archivo.open(nombrearchivo.c_str(), std::ios::in | std::ios::binary);

    if (archivo.fail()){
        std::cout << "No se pudo abrir el archivo binario\n";
        return 0;
    }

    int contador = 0;

    while (contador < max) {
       
        // leer ID de la sala
        archivo.read(&salas[contador].id_sala, sizeof(char));
        if (archivo.fail()) {
            break;
        }

        unsigned int num_maquinas_temp;

        // leer número de máquinas
        archivo.read((char*)&num_maquinas_temp, sizeof(unsigned int));
        if (archivo.fail()) {
            break;
        }

        salas[contador].num_maquinas = num_maquinas_temp;
        
        // validación de datos del archivo
        if (salas[contador].num_maquinas == 0 || salas[contador].num_maquinas > 100) {
            std::cout << "Error: Numero de maquinas inválido (" << (int)salas[contador].num_maquinas << "). Archivo corrupto.\n";
            break;
        }
        
        // crear arreglo de máquinas
        salas[contador].maquinas = new Maquina[salas[contador].num_maquinas];
        bool lectura_valida = true;

        for (unsigned int i = 0; i < salas[contador].num_maquinas && lectura_valida; i++) {
            
            // leer ID de máquina y número de mediciones
            archivo.read(&salas[contador].maquinas[i].id_maquina, sizeof(char));
            if (archivo.fail()) {
                lectura_valida = false;
                break;
            }

            archivo.read((char*)&salas[contador].maquinas[i].num_mediciones, sizeof(unsigned int));
            if (archivo.fail()) {
                lectura_valida = false;
                break;
            }

            if (salas[contador].maquinas[i].num_mediciones == 0 || salas[contador].maquinas[i].num_mediciones > 1000000) {
                std::cout << "Error: Numero de mediciones inválido (" << salas[contador].maquinas[i].num_mediciones << "). Archivo corrupto.\n";
                lectura_valida = false;
                break;
            }

            // crear arreglo de mediciones
            salas[contador].maquinas[i].mediciones = new Medicion[salas[contador].maquinas[i].num_mediciones];
            
            for (unsigned int j = 0; j < salas[contador].maquinas[i].num_mediciones && lectura_valida; j++) {
                
                // reservar memoria para los datos de la medición
                salas[contador].maquinas[i].mediciones[j].id_paciente = new char[11];
                salas[contador].maquinas[i].mediciones[j].fecha_y_hora = new char[24];

                // leer ID del paciente
                char id_temp;
                archivo.read(&id_temp, 1);
                if (archivo.fail()) {
                    lectura_valida = false;
                    break;
                }

                salas[contador].maquinas[i].mediciones[j].id_paciente[0] = id_temp;
                salas[contador].maquinas[i].mediciones[j].id_paciente[1] = '\0';
                
                // leer fecha y hora
                archivo.read(salas[contador].maquinas[i].mediciones[j].fecha_y_hora, 24);
                if (archivo.fail()) {
                    lectura_valida = false;
                    break;
                }
                
                // leer número de lecturas
                archivo.read((char*)&salas[contador].maquinas[i].mediciones[j].numlecturas, sizeof(unsigned int));
                if (archivo.fail()) {
                    lectura_valida = false;
                    break;
                }

                // validación de número de lecturas
                if (salas[contador].maquinas[i].mediciones[j].numlecturas == 0 || salas[contador].maquinas[i].mediciones[j].numlecturas > 1000000) {
                    std::cout << "Error: Numero de lecturas inválido (" << salas[contador].maquinas[i].mediciones[j].numlecturas << "). Archivo corrupto.\n";
                    lectura_valida = false;
                    break;
                }

                // crear arreglo de lecturas
                salas[contador].maquinas[i].mediciones[j].lecturas = new Lectura[salas[contador].maquinas[i].mediciones[j].numlecturas];

                for (unsigned int k = 0; k < salas[contador].maquinas[i].mediciones[j].numlecturas; k++) {
                
                    // leer tipo de sensor
                    archivo.read(&salas[contador].maquinas[i].mediciones[j].lecturas[k].tipo, sizeof(char));
                    if (archivo.fail()) {
                        lectura_valida = false;
                        break;
                    }
                    
                    if (salas[contador].maquinas[i].mediciones[j].lecturas[k].tipo == 'P') {
                        // presión arterial: sistólica y diastólica
                        archivo.read((char*)&salas[contador].maquinas[i].mediciones[j].lecturas[k].sistolica, sizeof(double));
                        if (archivo.fail()) {
                            lectura_valida = false;
                            break;
                        }

                        archivo.read((char*)&salas[contador].maquinas[i].mediciones[j].lecturas[k].diastolica, sizeof(double));
                        if (archivo.fail()) {
                            lectura_valida = false;
                            break;
                        }
                    } 
                    else {
                        // temperatura, oxígeno o ECG
                        archivo.read((char*)&salas[contador].maquinas[i].mediciones[j].lecturas[k].valor, sizeof(double));
                        if (archivo.fail()) {
                            lectura_valida = false;
                            break;
                        }
                    }
                }
            }
        }
        
        if (!lectura_valida) {
            std::cout << "Se detiene la lectura del archivo debido a datos corruptos.\n";
            break;
        }

        contador++;
    }

    archivo.close();
    return contador;
}

// --------------------------------------------------------
// Detecta si un paciente tiene anomalías en sus lecturas ECG
// --------------------------------------------------------
bool detectar_anomalia_ecg(Sala salas[], int num_salas, char* paciente_buscado, Configuracion cfg) 
{
    bool encontro_ecg = false;
    double minimo = 0.0;
    double maximo = 0.0;

    for (int s = 0; s < num_salas; s++) {
        for (unsigned int i = 0; i < salas[s].num_maquinas; i++) {
            for (unsigned int j = 0; j < salas[s].maquinas[i].num_mediciones; j++) {
                
                // comparar ID del paciente
                if (std::strncmp(salas[s].maquinas[i].mediciones[j].id_paciente, paciente_buscado, 11) == 0) {

                    for (unsigned int k = 0; k < salas[s].maquinas[i].mediciones[j].numlecturas; k++) {

                        if (salas[s].maquinas[i].mediciones[j].lecturas[k].tipo == 'E') {

                            double v = salas[s].maquinas[i].mediciones[j].lecturas[k].valor;

                            if (!encontro_ecg) {
                                minimo = v;
                                maximo = v;
                                encontro_ecg = true;
                            } 
                            else {
                                if (v < minimo) minimo = v;
                                if (v > maximo) maximo = v;
                            }
                        }
                    }
                }
            }
        }
    }

    if (!encontro_ecg) return false;

    double suma_mediciones = std::fabs(minimo) + std::fabs(maximo);
    double suma_limites    = std::fabs(cfg.ecg.min) + std::fabs(cfg.ecg.max);

    return (suma_mediciones > suma_limites);
}

// --------------------------------------------------------
// Estructura temporal para almacenar datos ECG antes
// de exportarlos al archivo binario
// --------------------------------------------------------
struct DatoECGExportar {
    char fecha_y_hora[24];
    double valor;
};

// --------------------------------------------------------
// Exporta a un archivo binario los pacientes con anomalías
// detectadas en las lecturas ECG
// --------------------------------------------------------
void exportar_pacientes_ecg_anomalos(Sala salas[], int num_salas, ArchivoPacientes base_pacientes, Configuracion cfg) {
    
    std::ofstream archivo_salida("pacientes_ecg_anomalos.bsf", std::ios::out | std::ios::binary);

    if (!archivo_salida) {
        std::cout << "Error al crear el archivo de exportacion.\n";
        return;
    }

    int exportados = 0;

    for (int p = 0; p < base_pacientes.cantidad; p++) {
        
        Paciente* paciente_actual = &base_pacientes.pacientes[p];

        if (detectar_anomalia_ecg(salas, num_salas, paciente_actual->id_paciente, cfg) == true) {
            
            DatoECGExportar ecgs_temporales[200]; 
            unsigned int contador_ecg = 0;        

            for (int s = 0; s < num_salas; s++) {
                for (unsigned int i = 0; i < salas[s].num_maquinas; i++) {
                    for (unsigned int j = 0; j < salas[s].maquinas[i].num_mediciones; j++) {
                        
                        if (std::strncmp(salas[s].maquinas[i].mediciones[j].id_paciente, paciente_actual->id_paciente, 11) == 0) {

                            for (unsigned int k = 0; k < salas[s].maquinas[i].mediciones[j].numlecturas; k++) {
                                
                                if (salas[s].maquinas[i].mediciones[j].lecturas[k].tipo == 'E') {

                                    std::strncpy(ecgs_temporales[contador_ecg].fecha_y_hora,
                                                 salas[s].maquinas[i].mediciones[j].fecha_y_hora, 24);

                                    ecgs_temporales[contador_ecg].valor =
                                        salas[s].maquinas[i].mediciones[j].lecturas[k].valor;

                                    contador_ecg++;
                                }
                            }
                        }
                    }
                }
            }

            // escribir datos del paciente en el archivo
            archivo_salida.write(paciente_actual->id_paciente, 11);
            archivo_salida.write((char*)&contador_ecg, sizeof(unsigned int));
            
            for (unsigned int e = 0; e < contador_ecg; e++) {
                archivo_salida.write(ecgs_temporales[e].fecha_y_hora, 24);
                archivo_salida.write((char*)&ecgs_temporales[e].valor, sizeof(double));
            }

            exportados++;
        }
    }

    archivo_salida.close();

    std::cout << "-> Exportacion exitosa. Se exportaron "
              << exportados
              << " pacientes a 'pacientes_ecg_anomalos.bsf'\n";
}

// --------------------------------------------------------
// Libera la memoria de todas las salas cargadas
// --------------------------------------------------------
void liberarSalas(Sala salas[], int total_salas) {

    for(int s = 0; s < total_salas; s++) {
        salas[s].liberar();
    }
}

#endif // SALA_H