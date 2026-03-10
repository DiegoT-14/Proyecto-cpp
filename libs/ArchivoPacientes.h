#ifndef ARCHIVOPACIENTES_H
#define ARCHIVOPACIENTES_H
#include "Paciente.h" 

struct ArchivoPacientes {

    Paciente* pacientes;
    int cantidad;
    
    // --------------------------------------------------------
    // Constructor que inicializa el arreglo en nullptr
    // --------------------------------------------------------
    ArchivoPacientes() {
        pacientes = nullptr;
        cantidad = 0;
    }

    // --------------------------------------------------------
    // Carga los pacientes desde el archivo
    // --------------------------------------------------------
    void cargarPacientes() {
        pacientes = leer_datos_paciente(cantidad);
    }

    // --------------------------------------------------------
    // Libera la memoria utilizada por los pacientes cargados
    // --------------------------------------------------------
    void liberar() {

        // verificar que exista memoria reservada
        if (pacientes != nullptr) {
            liberarPacientes(pacientes, cantidad);
            pacientes = nullptr;
            cantidad = 0;
        }
    }
};

#endif // ARCHIVOPACIENTES_H