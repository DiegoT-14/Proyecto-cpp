#ifndef PACIENTE_H
#define PACIENTE_H
#include <string> 
#include <sstream>   // para usar stringstream y separar texto
#include <cstring>   // para strncpy
#include <fstream>   // para manejo de archivos
#include <iostream>  // para mostrar mensajes de error

struct Paciente {

    char* id_paciente;
    char* tipo_doc;
    char* documento;
    char* nombre;
    char* apellido;
    char* fecha_nacimiento;
    char* telefono;
    char* email;
    char* tipo_sangre;
    char* entidad_salud;
    char* medicina_Prepagada;

    // --------------------------------------------------------
    // Constructor que inicializa todos los punteros en nullptr
    // para evitar referencias a memoria no inicializada
    // --------------------------------------------------------
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

    // --------------------------------------------------------
    // Función que separa una línea del archivo
    // usando ';' como delimitador
    // --------------------------------------------------------
    void separarLineaPaciente(std::string linea, std::string tokens[11]) {
        std::stringstream ss(linea); // tratar la línea como flujo de texto

        for (int i = 0; i < 11; i++) {
            std::getline(ss, tokens[i], ';');

            // eliminar espacio inicial si existe
            if (tokens[i].length() > 0 && tokens[i][0] == ' ') {
                tokens[i].erase(0, 1); 
            }
        }
    }

    // --------------------------------------------------------
    // Copia los datos obtenidos del archivo en los atributos
    // de la estructura usando memoria dinámica
    // --------------------------------------------------------
    void cargarDatosPaciente(std::string datos[11]){

        int tam_id_paciente = datos[0].length();
        id_paciente = new char[tam_id_paciente + 1];
        std::strncpy(id_paciente, datos[0].c_str(), tam_id_paciente);
        id_paciente[tam_id_paciente] = '\0';

        int tam_tipo_doc = datos[1].length();
        tipo_doc = new char[tam_tipo_doc + 1];
        std::strncpy(tipo_doc, datos[1].c_str(), tam_tipo_doc);
        tipo_doc[tam_tipo_doc] = '\0';

        int tam_documento = datos[2].length();
        documento = new char[tam_documento + 1];    
        std::strncpy(documento, datos[2].c_str(), tam_documento);
        documento[tam_documento] = '\0';

        int tam_nombre = datos[3].length();
        nombre = new char[tam_nombre + 1];
        std::strncpy(nombre, datos[3].c_str(), tam_nombre);
        nombre[tam_nombre] = '\0';

        int tam_apellido = datos[4].length();
        apellido = new char[tam_apellido + 1];
        std::strncpy(apellido, datos[4].c_str(), tam_apellido);
        apellido[tam_apellido] = '\0';

        int tam_fecha_nacimiento = datos[5].length();
        fecha_nacimiento = new char[tam_fecha_nacimiento + 1];
        std::strncpy(fecha_nacimiento, datos[5].c_str(), tam_fecha_nacimiento);
        fecha_nacimiento[tam_fecha_nacimiento] = '\0';

        int tam_telefono = datos[6].length();
        telefono = new char[tam_telefono + 1];
        std::strncpy(telefono, datos[6].c_str(), tam_telefono);
        telefono[tam_telefono] = '\0';

        int tam_email = datos[7].length();
        email = new char[tam_email + 1];
        std::strncpy(email, datos[7].c_str(), tam_email);
        email[tam_email] = '\0';

        int tam_tipo_sangre = datos[8].length();
        tipo_sangre = new char[tam_tipo_sangre + 1];
        std::strncpy(tipo_sangre, datos[8].c_str(), tam_tipo_sangre);
        tipo_sangre[tam_tipo_sangre] = '\0';

        int tam_entidad_salud = datos[9].length();
        entidad_salud = new char[tam_entidad_salud + 1];
        std::strncpy(entidad_salud, datos[9].c_str(), tam_entidad_salud);
        entidad_salud[tam_entidad_salud] = '\0';

        int tam_medicina_Prepagada = datos[10].length();
        medicina_Prepagada = new char[tam_medicina_Prepagada + 1];
        std::strncpy(medicina_Prepagada, datos[10].c_str(), tam_medicina_Prepagada);
        medicina_Prepagada[tam_medicina_Prepagada] = '\0';
    }
};

// --------------------------------------------------------
// Cuenta la cantidad de pacientes en el archivo 
// --------------------------------------------------------
int contarPacientes() {

    std::string linea;
    std::fstream lectura("data/pacientes.csv", std::ios::in);

    if (lectura.fail()) {
        std::cout << "No se pudo abrir el archivo de pacientes." << std::endl; 
        return 0; 
    }

    int contador = 0;

    // contar líneas del archivo
    while (std::getline(lectura, linea)) { 
        contador++; 
    }

    lectura.close();
    return contador;
}

// --------------------------------------------------------
// Lee los datos del archivo y crea un arreglo
// dinámico de estructuras Paciente
// --------------------------------------------------------
Paciente* leer_datos_paciente(int &cantidad) {

    int total = contarPacientes();
    if (total <= 0) return nullptr;

    Paciente* lista = new Paciente[total]; 

    std::fstream lectura("data/pacientes.csv", std::ios::in);

    if (lectura.fail()) { 
        std::cout << "No se pudo abrir el archivo de pacientes." << std::endl;
        delete[] lista; 
        return nullptr; 
    }

    std::string linea;
    int i = 0;

    // leer cada línea y cargar los datos del paciente
    while(std::getline(lectura, linea) && i < total) {
        std::string tokens[11];
        
        lista[i].separarLineaPaciente(linea, tokens); 
        lista[i].cargarDatosPaciente(tokens);
        i++;
    }

    lectura.close();
    cantidad = total; 
    return lista;
}

// --------------------------------------------------------
// Libera la memoria dinámica utilizada por los pacientes
// --------------------------------------------------------
void liberarPacientes(Paciente* pacientes, int cantidad){

    for(int i=0;i<cantidad;i++){
        delete[] pacientes[i].id_paciente;
        delete[] pacientes[i].tipo_doc;
        delete[] pacientes[i].documento;
        delete[] pacientes[i].nombre;
        delete[] pacientes[i].apellido;
        delete[] pacientes[i].fecha_nacimiento;
        delete[] pacientes[i].telefono;
        delete[] pacientes[i].email;
        delete[] pacientes[i].tipo_sangre;
        delete[] pacientes[i].entidad_salud;
        delete[] pacientes[i].medicina_Prepagada;
    }

    delete[] pacientes;
}

#endif // PACIENTE_H