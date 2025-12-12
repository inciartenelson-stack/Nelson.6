#include "Hospital.hpp"
#include <iostream>
#include <cstring>

using namespace std;

// Constructor por defecto
Hospital::Hospital() : contadorPacientes(0), contadorDoctores(0), 
                      contadorCitas(0), contadorConsultas(0),
                      proximoIDPaciente(1), proximoIDDoctor(1),
                      proximoIDCita(1), proximoIDConsulta(1) {
    strcpy(nombre, "");
    strcpy(direccion, "");
    strcpy(telefono, "");
}

// Constructor con parámetros
Hospital::Hospital(const char* nombre, const char* direccion, const char* telefono) 
    : contadorPacientes(0), contadorDoctores(0), contadorCitas(0), contadorConsultas(0),
      proximoIDPaciente(1), proximoIDDoctor(1), proximoIDCita(1), proximoIDConsulta(1) {
    setNombre(nombre);
    setDireccion(direccion);
    setTelefono(telefono);
}

// GETTERS
const char* Hospital::getNombre() const { return nombre; }
const char* Hospital::getDireccion() const { return direccion; }
const char* Hospital::getTelefono() const { return telefono; }
int Hospital::getContadorPacientes() const { return contadorPacientes; }
int Hospital::getContadorDoctores() const { return contadorDoctores; }
int Hospital::getContadorCitas() const { return contadorCitas; }
int Hospital::getContadorConsultas() const { return contadorConsultas; }

// SETTERS
void Hospital::setNombre(const char* nombre) {
    if (nombre != nullptr && strlen(nombre) < MAX_NOMBRE) {
        strcpy(this->nombre, nombre);
    }
}

void Hospital::setDireccion(const char* direccion) {
    if (direccion != nullptr && strlen(direccion) < MAX_DIRECCION) {
        strcpy(this->direccion, direccion);
    }
}

void Hospital::setTelefono(const char* telefono) {
    if (telefono != nullptr && strlen(telefono) < MAX_TELEFONO) {
        strcpy(this->telefono, telefono);
    }
}

// GENERADORES DE ID
int Hospital::generarNuevoIDPaciente() {
    return proximoIDPaciente++;
}

int Hospital::generarNuevoIDDoctor() {
    return proximoIDDoctor++;
}

int Hospital::generarNuevoIDCita() {
    return proximoIDCita++;
}

int Hospital::generarNuevoIDConsulta() {
    return proximoIDConsulta++;
}

// INCREMENTADORES
void Hospital::incrementarPacientesRegistrados() {
    contadorPacientes++;
}

void Hospital::incrementarDoctoresRegistrados() {
    contadorDoctores++;
}

void Hospital::incrementarCitasRegistradas() {
    contadorCitas++;
}

void Hospital::incrementarConsultasRegistradas() {
    contadorConsultas++;
}

// MÉTODOS DE PRESENTACIÓN
void Hospital::mostrarInformacion() const {
    cout << "\n=== INFORMACION DEL HOSPITAL ===" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Direccion: " << direccion << endl;
    cout << "Telefono: " << telefono << endl;
}

void Hospital::mostrarEstadisticas() const {
    cout << "\n=== ESTADISTICAS DEL SISTEMA ===" << endl;
    cout << "Pacientes registrados: " << contadorPacientes << endl;
    cout << "Doctores registrados: " << contadorDoctores << endl;
    cout << "Citas registradas: " << contadorCitas << endl;
    cout << "Consultas medicas: " << contadorConsultas << endl;
    cout << "Proximo ID Paciente: " << proximoIDPaciente << endl;
    cout << "Proximo ID Doctor: " << proximoIDDoctor << endl;
    cout << "Proximo ID Cita: " << proximoIDCita << endl;
    cout << "Proximo ID Consulta: " << proximoIDConsulta << endl;
}

// VALIDACIÓN
bool Hospital::validarDatos() const {
    return (strlen(nombre) > 0 && strlen(direccion) > 0 && strlen(telefono) > 0);
}

// MÉTODO ESTÁTICO
size_t Hospital::obtenerTamano() {
    return sizeof(Hospital);
}