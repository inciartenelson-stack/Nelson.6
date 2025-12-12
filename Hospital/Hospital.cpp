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

// Constructor de copia
Hospital::Hospital(const Hospital& otro) {
    strcpy(nombre, otro.nombre);
    strcpy(direccion, otro.direccion);
    strcpy(telefono, otro.telefono);
    
    contadorPacientes = otro.contadorPacientes;
    contadorDoctores = otro.contadorDoctores;
    contadorCitas = otro.contadorCitas;
    contadorConsultas = otro.contadorConsultas;
    
    proximoIDPaciente = otro.proximoIDPaciente;
    proximoIDDoctor = otro.proximoIDDoctor;
    proximoIDCita = otro.proximoIDCita;
    proximoIDConsulta = otro.proximoIDConsulta;
}

// Destructor
Hospital::~Hospital() {
    // No hay recursos dinámicos que liberar
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
    if (strlen(nombre) < MAX_NOMBRE) {
        strcpy(this->nombre, nombre);
    }
}

void Hospital::setDireccion(const char* direccion) {
    if (strlen(direccion) < MAX_DIRECCION) {
        strcpy(this->direccion, direccion);
    }
}

void Hospital::setTelefono(const char* telefono) {
    if (strlen(telefono) < MAX_TELEFONO) {
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

void Hospital::decrementarPacientesRegistrados() {
    if (contadorPacientes > 0) contadorPacientes--;
}

void Hospital::decrementarDoctoresRegistrados() {
    if (contadorDoctores > 0) contadorDoctores--;
}

void Hospital::decrementarCitasRegistradas() {
    if (contadorCitas > 0) contadorCitas--;
}

void Hospital::decrementarConsultasRegistradas() {
    if (contadorConsultas > 0) contadorConsultas--;
}

// MÉTODOS DE PRESENTACIÓN
void Hospital::mostrarInformacion() const {
    cout << "\n=== INFORMACIÓN DEL HOSPITAL ===" << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Teléfono: " << telefono << endl;
}

void Hospital::mostrarEstadisticas() const {
    cout << "\n=== ESTADÍSTICAS DEL SISTEMA ===" << endl;
    cout << "Pacientes registrados: " << contadorPacientes << endl;
    cout << "Doctores registrados: " << contadorDoctores << endl;
    cout << "Citas registradas: " << contadorCitas << endl;
    cout << "Consultas médicas: " << contadorConsultas << endl;
    cout << "Próximo ID Paciente: " << proximoIDPaciente << endl;
    cout << "Próximo ID Doctor: " << proximoIDDoctor << endl;
    cout << "Próximo ID Cita: " << proximoIDCita << endl;
    cout << "Próximo ID Consulta: " << proximoIDConsulta << endl;
}

// VALIDACIÓN
bool Hospital::validarDatos() const {
    if (strlen(nombre) == 0) {
        cerr << "Error: Nombre del hospital no puede estar vacío" << endl;
        return false;
    }
    
    if (strlen(direccion) == 0) {
        cerr << "Error: Dirección no puede estar vacía" << endl;
        return false;
    }
    
    if (strlen(telefono) == 0) {
        cerr << "Error: Teléfono no puede estar vacío" << endl;
        return false;
    }
    
    if (contadorPacientes < 0 || contadorDoctores < 0 || 
        contadorCitas < 0 || contadorConsultas < 0) {
        cerr << "Error: Contadores no pueden ser negativos" << endl;
        return false;
    }
    
    return true;
}

// MÉTODO ESTÁTICO
size_t Hospital::obtenerTamano() {
    return sizeof(Hospital);
}