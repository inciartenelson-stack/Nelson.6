// doctores/Doctor.cpp
#include "Doctor.hpp"
#include "../utilidades/Validaciones.hpp"
#include <iostream>
#include <cstring>
#include <ctime>

Doctor::Doctor() {
    id = 0;
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(cedula, "");
    strcpy(especialidad, "");
    strcpy(telefono, "");
    strcpy(email, "");
    costoConsulta = 0.0f;
    disponible = true;
    cantidadPacientes = 0;
    fechaCreacion = time(nullptr);
    fechaModificacion = fechaCreacion;
}

Doctor::Doctor(int id, const char* nombre, const char* apellido, const char* cedula, const char* especialidad) {
    this->id = id;
    strncpy(this->nombre, nombre, 99);
    this->nombre[99] = '\0';
    strncpy(this->apellido, apellido, 99);
    this->apellido[99] = '\0';
    strncpy(this->cedula, cedula, 19);
    this->cedula[19] = '\0';
    strncpy(this->especialidad, especialidad, 49);
    this->especialidad[49] = '\0';
    strcpy(this->telefono, "");
    strcpy(this->email, "");
    costoConsulta = 0.0f;
    disponible = true;
    cantidadPacientes = 0;
    fechaCreacion = time(nullptr);
    fechaModificacion = fechaCreacion;
}

Doctor::Doctor(const Doctor& otro) {
    id = otro.id;
    strcpy(nombre, otro.nombre);
    strcpy(apellido, otro.apellido);
    strcpy(cedula, otro.cedula);
    strcpy(especialidad, otro.especialidad);
    strcpy(telefono, otro.telefono);
    strcpy(email, otro.email);
    costoConsulta = otro.costoConsulta;
    disponible = otro.disponible;
    cantidadPacientes = otro.cantidadPacientes;
    memcpy(pacienteIDs, otro.pacienteIDs, sizeof(pacienteIDs));
    fechaCreacion = otro.fechaCreacion;
    fechaModificacion = otro.fechaModificacion;
}

Doctor::~Doctor() {}

void Doctor::setNombre(const char* nuevoNombre) {
    if (nuevoNombre && strlen(nuevoNombre) > 0 && strlen(nuevoNombre) < 100) {
        strcpy(nombre, nuevoNombre);
        fechaModificacion = time(nullptr);
    }
}

void Doctor::setApellido(const char* nuevoApellido) {
    if (nuevoApellido && strlen(nuevoApellido) > 0 && strlen(nuevoApellido) < 100) {
        strcpy(apellido, nuevoApellido);
        fechaModificacion = time(nullptr);
    }
}

void Doctor::setCedula(const char* nuevaCedula) {
    if (nuevaCedula && Validaciones::validarCedula(nuevaCedula)) {
        strncpy(cedula, nuevaCedula, 19);
        cedula[19] = '\0';
        fechaModificacion = time(nullptr);
    }
}

void Doctor::setEspecialidad(const char* nuevaEspecialidad) {
    if (nuevaEspecialidad && strlen(nuevaEspecialidad) > 0 && strlen(nuevaEspecialidad) < 50) {
        strcpy(especialidad, nuevaEspecialidad);
        fechaModificacion = time(nullptr);
    }
}

void Doctor::setTelefono(const char* nuevoTelefono) {
    if (nuevoTelefono && Validaciones::validarTelefono(nuevoTelefono)) {
        strncpy(telefono, nuevoTelefono, 29);
        telefono[29] = '\0';
        fechaModificacion = time(nullptr);
    }
}

void Doctor::setEmail(const char* nuevoEmail) {
    if (nuevoEmail && Validaciones::validarEmail(nuevoEmail)) {
        strncpy(email, nuevoEmail, 99);
        email[99] = '\0';
        fechaModificacion = time(nullptr);
    }
}

void Doctor::setCostoConsulta(float nuevoCosto) {
    if (nuevoCosto >= 0 && nuevoCosto <= 10000) {
        costoConsulta = nuevoCosto;
        fechaModificacion = time(nullptr);
    }
}

void Doctor::setDisponible(bool estado) {
    disponible = estado;
    fechaModificacion = time(nullptr);
}

bool Doctor::especialidadEsValida() const {
    const char* validas[] = {"Cardiología", "Pediatría", "Dermatología", "Neurología", "Ginecología"};
    for (int i = 0; i < 5; i++) {
        if (strcmp(especialidad, validas[i]) == 0) return true;
    }
    return false;
}

bool Doctor::cedulaProfesionalValida() const {
    return Validaciones::validarCedula(cedula);
}

bool Doctor::costoConsultaValido() const {
    return costoConsulta >= 0 && costoConsulta <= 10000;
}

bool Doctor::validarDatos() const {
    return (id > 0) &&
           (strlen(nombre) > 0) &&
           (strlen(apellido) > 0) &&
           cedulaProfesionalValida() &&
           especialidadEsValida() &&
           (strlen(telefono) > 0) &&
           (strlen(email) > 0) &&
           costoConsultaValido();
}

bool Doctor::agregarPacienteID(int pacienteID) {
    if (cantidadPacientes < 100) {
        pacienteIDs[cantidadPacientes++] = pacienteID;
        fechaModificacion = time(nullptr);
        return true;
    }
    return false;
}

bool Doctor::eliminarPacienteID(int pacienteID) {
    for (int i = 0; i < cantidadPacientes; i++) {
        if (pacienteIDs[i] == pacienteID) {
            for (int j = i; j < cantidadPacientes - 1; j++) {
                pacienteIDs[j] = pacienteIDs[j + 1];
            }
            cantidadPacientes--;
            fechaModificacion = time(nullptr);
            return true;
        }
    }
    return false;
}

void Doctor::mostrarInformacionBasica() const {
    std::cout << "Dr. " << nombre << " " << apellido
              << " | Esp: " << especialidad
              << " | Tel: " << telefono
              << " | Email: " << email << "\n";
}

void Doctor::mostrarInformacionCompleta() const {
    mostrarInformacionBasica();
    std::cout << "Cédula: " << cedula
              << " | Costo: $" << costoConsulta
              << " | Disponible: " << (disponible ? "Sí" : "No") << "\n";
}