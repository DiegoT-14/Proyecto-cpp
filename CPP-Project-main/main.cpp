#include "../libs/Configuracion.h"
#include "../libs/Paciente.h"
#include "../libs/Medicion.h"
#include "../libs/Lectura.h"
#include "../libs/Sala.h"
#include "../libs/Maquina.h"
#include "../libs/ArchivoPacientes.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

void printMenu();

int main() {

    // --------------------------------------------------------
    // Inicialización de variables principales del sistema
    // --------------------------------------------------------
    Configuracion cfg;
    ArchivoPacientes base_pacientes;
    base_pacientes.cantidad = 0;
    Sala salas[5];        
    int total_salas = 0;  // número de salas leídas del archivo binario

    int option;

    do {

        printMenu();

        cout << "\nIngrese una opcion (0 para salir): ";
        cin >> option;

        switch (option) {

            // ========================================================
            // OPCION 1: CARGAR CONFIGURACION Y PACIENTES
            // ========================================================
            case 1: {

                cout << "\n===== CARGANDO CONFIGURACION Y PACIENTES =====\n" << endl;

                // 1. Cargar archivo de configuración
                if (cfg.leer_archivo_configuracion() == 0) {
                    cout << "Error: no se pudo cargar el archivo de configuracion.\n";
                } 
                else {
                    cout << "-> Archivo de configuracion cargado exitosamente.\n";
                }

                // 2. Liberar memoria previa (por si se carga más de una vez)
                liberarPacientes(base_pacientes.pacientes, base_pacientes.cantidad);
                base_pacientes.pacientes = nullptr;
                base_pacientes.cantidad = 0;

                // 3. Cargar pacientes desde el CSV
                base_pacientes.pacientes = leer_datos_paciente(base_pacientes.cantidad);

                cout << "-> Se cargaron " << base_pacientes.cantidad << " pacientes desde el CSV.\n\n";

                break;
            }

            // ========================================================
            // OPCION 2: LEER ARCHIVO BINARIO CON MEDICIONES
            // ========================================================
            case 2: {

                cout << "\n===== LEYENDO ARCHIVO BINARIO (.bsf) =====\n" << endl;
                
                // liberar memoria previa para evitar fugas
                liberarSalas(salas, total_salas);
                total_salas = 0;

                // leer archivo binario
                total_salas = leer_binario(salas, 5);

                if (total_salas > 0) {
                    cout << "-> Lectura exitosa. Se leyeron " << total_salas << " sala(s) del archivo.\n";
                } 
                else {
                    cout << "-> Error: No se pudo leer el archivo .bsf o esta vacio.\n";
                }

                break;
            }

            // ========================================================
            // OPCION 3: GENERAR REPORTE DE ANOMALIAS
            // ========================================================
            case 3: {

                cout << "\n===== GENERANDO REPORTE DE ANOMALIAS =====\n" << endl;
                 
                if (total_salas == 0) {
                    cout << "Error: Primero debe leer el archivo .bsf (Opcion 2).\n";
                    break;
                }

                cout << "Analizando lecturas...\n";
                
                // recorrer salas y máquinas para generar el reporte
                for (int s = 0; s < total_salas; s++) {
                    for (unsigned int m = 0; m < salas[s].num_maquinas; m++) {

                        generarReporteMaquina(salas[s].maquinas[m], cfg);
                    }
                }

                cout << "-> Analisis finalizado. Reporte generado en 'reporte_anomalias.txt'.\n";
                break;
            }

            // ========================================================
            // OPCION 4: CALCULAR ESTADISTICAS (ECG)
            // ========================================================
            case 4: {

                cout << "\n===== CALCULAR ESTADISTICAS (Analisis de ECG) =====\n" << endl;

                if (base_pacientes.cantidad == 0) {
                    cout << "Error: Primero debe cargar los datos de pacientes (Opcion 1).\n";
                    break;
                }

                if (total_salas == 0) {
                    cout << "Error: Primero debe leer el archivo .bsf (Opcion 2).\n";
                    break;
                }

                cout << "Calculando estadisticas y evaluando ECG para todos los pacientes...\n";
                cout << "--------------------------------------------------------------\n";

                int pacientes_con_anomalia = 0;

                // recorrer todos los pacientes
                for (int p = 0; p < base_pacientes.cantidad; p++) {
                    
                    bool peligro_ecg = detectar_anomalia_ecg(
                        salas,
                        total_salas,
                        base_pacientes.pacientes[p].id_paciente,
                        cfg
                    );

                    if (peligro_ecg == true) {

                        cout << "[ ALERTA ] Paciente: "
                             << base_pacientes.pacientes[p].nombre
                             << " "
                             << base_pacientes.pacientes[p].apellido
                             << " (ID: "
                             << base_pacientes.pacientes[p].id_paciente
                             << ") presenta ANOMALIA en el ECG.\n";

                        pacientes_con_anomalia++;
                    }
                }

                cout << "--------------------------------------------------------------\n";
                cout << "-> ESTADISTICA FINAL: Se detectaron "
                     << pacientes_con_anomalia
                     << " paciente(s) con anomalias de ECG.\n";

                break;
            }

            // ========================================================
            // OPCION 5: EXPORTAR PACIENTES CON ECG ANOMALO
            // ========================================================
            case 5: {

                cout << "\n===== EXPORTAR DATOS PROCESADOS =====\n" << endl;
                
                if (base_pacientes.cantidad == 0 || total_salas == 0) {
                    cout << "Error: Faltan datos. Ejecute las opciones 1 y 2 primero.\n";
                    break;
                }

                exportar_pacientes_ecg_anomalos(
                    salas,
                    total_salas,
                    base_pacientes,
                    cfg
                );

                break;
            }

            // ========================================================
            // OPCION 0: SALIR DEL PROGRAMA
            // ========================================================
            case 0:

                cout << "\nSaliendo del sistema y liberando memoria..." << endl;
                break;

            default:

                cout << "\nOpcion invalida. Por favor seleccione un numero del 0 al 5." << endl;
                break;
        }

    } while (option != 0);

    // --------------------------------------------------------
    // LIMPIEZA TOTAL DE MEMORIA AL FINALIZAR EL PROGRAMA
    // --------------------------------------------------------

    liberarPacientes(base_pacientes.pacientes, base_pacientes.cantidad);

    base_pacientes.pacientes = nullptr;
    base_pacientes.cantidad = 0;
    
    liberarSalas(salas, total_salas);
    
    return 0;
}

// --------------------------------------------------------
// Muestra el menú principal del programa
// --------------------------------------------------------
void printMenu() {

    cout << "\n===== MENU PRINCIPAL =====\n" << endl;
    cout << "1. Cargar archivo de configuracion y datos de pacientes" << endl;
    cout << "2. Leer archivo .bsf" << endl;
    cout << "3. Generar reporte de anomalias" << endl;
    cout << "4. Calcular estadisticas" << endl;
    cout << "5. Exportar datos procesados" << endl;
    cout << "0. Salir" << endl;
}