#include "Paciente.hpp"
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

// Constructor por defecto
Paciente::Paciente() : id(0), edad(0), genero(' '), cantidadCitas(0) {
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(cedula, "");
    strcpy(telefono, "");
    strcpy(direccion, "");
    strcpy(email, "");
    strcpy(contactoEmergencia, "");
    strcpy(telefonoEmergencia, "");
    strcpy(tipoSangre, "");
    
    for (int i = 0; i < MAX_CITAS; i++) {
        citasIDs[i] = 0;
    }
    
    inicializarFechas();
}

// Constructor con parámetros principales
Paciente::Paciente(int id, const char* nombre, const char* apellido, const char* cedula)
    : id(id), edad(0), genero(' '), cantidadCitas(0) {
    
    setNombre(nombre);
    setApellido(apellido);
    setCedula(cedula);
    
    strcpy(telefono, "");
    strcpy(direccion, "");
    strcpy(email, "");
    strcpy(contactoEmergencia, "");
    strcpy(telefonoEmergencia, "");
    strcpy(tipoSangre, "");
    
    for (int i = 0; i < MAX_CITAS; i++) {
        citasIDs[i] = 0;
    }
    
    inicializarFechas();
}

// Constructor de copia
Paciente::Paciente(const Paciente& otro) : id(otro.id), edad(otro.edad), 
                                         genero(otro.genero), cantidadCitas(otro.cantidadCitas),
                                         fechaCreacion(otro.fechaCreacion),
                                         fechaUltimaModificacion(otro.fechaUltimaModificacion) {
    
    strcpy(nombre, otro.nombre);
    strcpy(apellido, otro.apellido);
    strcpy(cedula, otro.cedula);
    strcpy(telefono, otro.telefono);
    strcpy(direccion, otro.direccion);
    strcpy(email, otro.email);
    strcpy(contactoEmergencia, otro.contactoEmergencia);
    strcpy(telefonoEmergencia, otro.telefonoEmergencia);
    strcpy(tipoSangre, otro.tipoSangre);
    
    for (int i = 0; i < MAX_CITAS; i++) {
        citasIDs[i] = otro.citasIDs[i];
    }
}

// Destructor
Paciente::~Paciente() {
    // No hay recursos dinámicos que liberar
}

// GETTERS
int Paciente::getId() const { return id; }
const char* Paciente::getNombre() const { return nombre; }
const char* Paciente::getApellido() const { return apellido; }
const char* Paciente::getCedula() const { return cedula; }
int Paciente::getEdad() const { return edad; }
char Paciente::getGenero() const { return genero; }
const char* Paciente::getTelefono() const { return telefono; }
const char* Paciente::getDireccion() const { return direccion; }
const char* Paciente::getEmail() const { return email; }
const char* Paciente::getContactoEmergencia() const { return contactoEmergencia; }
const char* Paciente::getTelefonoEmergencia() const { return telefonoEmergencia; }
const char* Paciente::getTipoSangre() const { return tipoSangre; }
int Paciente::getCantidadCitas() const { return cantidadCitas; }
const int* Paciente::getCitasIDs() const { return citasIDs; }
time_t Paciente::getFechaCreacion() const { return fechaCreacion; }
time_t Paciente::getFechaUltimaModificacion() const { return fechaUltimaModificacion; }

// SETTERS CON VALIDACIÓN
void Paciente::setNombre(const char* nombre) {
    if (strlen(nombre) < MAX_NOMBRE) {
        strcpy(this->nombre, nombre);
        actualizarFechaModificacion();
    }
}

void Paciente::setApellido(const char* apellido) {
    if (strlen(apellido) < MAX_APELLIDO) {
        strcpy(this->apellido, apellido);
        actualizarFechaModificacion();
    }
}

void Paciente::setCedula(const char* cedula) {
    if (strlen(cedula) < MAX_CEDULA) {
        strcpy(this->cedula, cedula);
        actualizarFechaModificacion();
    }
}

void Paciente::setEdad(int edad) {
    if (edad >= 0 && edad <= 120) {
        this->edad = edad;
        actualizarFechaModificacion();
    } else {
        cerr << "Error: Edad debe estar entre 0 y 120 años" << endl;
    }
}

void Paciente::setGenero(char genero) {
    if (genero == 'M' || genero == 'F' || genero == ' ') {
        this->genero = genero;
        actualizarFechaModificacion();
    } else {
        cerr << "Error: Género debe ser 'M' o 'F'" << endl;
    }
}

void Paciente::setTelefono(const char* telefono) {
    if (strlen(telefono) < MAX_TELEFONO) {
        strcpy(this->telefono, telefono);
        actualizarFechaModificacion();
    }
}

void Paciente::setDireccion(const char* direccion) {
    if (strlen(direccion) < MAX_DIRECCION) {
        strcpy(this->direccion, direccion);
        actualizarFechaModificacion();
    }
}

void Paciente::setEmail(const char* email) {
    if (strlen(email) < MAX_EMAIL) {
        strcpy(this->email, email);
        actualizarFechaModificacion();
    }
}

void Paciente::setContactoEmergencia(const char* contacto) {
    if (strlen(contacto) < MAX_CONTACTO_EMERGENCIA) {
        strcpy(this->contactoEmergencia, contacto);
        actualizarFechaModificacion();
    }
}

void Paciente::setTelefonoEmergencia(const char* telefono) {
    if (strlen(telefono) < MAX_TELEFONO) {
        strcpy(this->telefonoEmergencia, telefono);
        actualizarFechaModificacion();
    }
}

void Paciente::setTipoSangre(const char* tipoSangre) {
    if (strlen(tipoSangre) < 4) {
        strcpy(this->tipoSangre, tipoSangre);
        actualizarFechaModificacion();
    }
}

// MÉTODOS DE VALIDACIÓN
bool Paciente::validarDatos() const {
    if (strlen(nombre) == 0) {
        cerr << "Error: Nombre no puede estar vacío" << endl;
        return false;
    }
    
    if (strlen(apellido) == 0) {
        cerr << "Error: Apellido no puede estar vacío" << endl;
        return false;
    }
    
    if (!cedulaEsValida()) {
        cerr << "Error: Cédula no válida" << endl;
        return false;
    }
    
    if (edad < 0 || edad > 120) {
        cerr << "Error: Edad fuera de rango (0-120)" << endl;
        return false;
    }
    
    if (genero != 'M' && genero != 'F' && genero != ' ') {
        cerr << "Error: Género debe ser 'M' o 'F'" << endl;
        return false;
    }
    
    if (!tieneContactoEmergencia()) {
        cerr << "Advertencia: Contacto de emergencia incompleto" << endl;
    }
    
    return true;
}

bool Paciente::esMayorDeEdad() const {
    return edad >= 18;
}

bool Paciente::cedulaEsValida() const {
    // Validación básica de cédula venezolana
    if (strlen(cedula) < 6 || strlen(cedula) > 10) {
        return false;
    }
    
    // Verificar que todos los caracteres sean dígitos
    for (size_t i = 0; i < strlen(cedula); i++) {
        if (!isdigit(cedula[i])) {
            return false;
        }
    }
    
    return true;
}

bool Paciente::tieneContactoEmergencia() const {
    return strlen(contactoEmergencia) > 0 && strlen(telefonoEmergencia) > 0;
}

// GESTIÓN DE RELACIONES CON CITAS
bool Paciente::agregarCitaID(int citaID) {
    if (cantidadCitas >= MAX_CITAS) {
        cerr << "Error: Límite de citas alcanzado" << endl;
        return false;
    }
    
    if (citaID <= 0) {
        cerr << "Error: ID de cita inválido" << endl;
        return false;
    }
    
    // Verificar que no exista ya
    if (citaExiste(citaID)) {
        cerr << "Error: Cita ya registrada" << endl;
        return false;
    }
    
    citasIDs[cantidadCitas] = citaID;
    cantidadCitas++;
    actualizarFechaModificacion();
    return true;
}

bool Paciente::eliminarCitaID(int citaID) {
    for (int i = 0; i < cantidadCitas; i++) {
        if (citasIDs[i] == citaID) {
            // Mover elementos restantes
            for (int j = i; j < cantidadCitas - 1; j++) {
                citasIDs[j] = citasIDs[j + 1];
            }
            cantidadCitas--;
            citasIDs[cantidadCitas] = 0; // Limpiar última posición
            actualizarFechaModificacion();
            return true;
        }
    }
    return false;
}

bool Paciente::tieneCitas() const {
    return cantidadCitas > 0;
}

bool Paciente::citaExiste(int citaID) const {
    for (int i = 0; i < cantidadCitas; i++) {
        if (citasIDs[i] == citaID) {
            return true;
        }
    }
    return false;
}

// MÉTODOS DE PRESENTACIÓN
void Paciente::mostrarInformacionBasica() const {
    cout << "\n=== INFORMACIÓN BÁSICA DEL PACIENTE ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Cédula: " << cedula << endl;
    cout << "Edad: " << edad << " años" << endl;
    cout << "Género: " << (genero == 'M' ? "Masculino" : 
                         genero == 'F' ? "Femenino" : "No especificado") << endl;
}

void Paciente::mostrarInformacionCompleta() const {
    mostrarInformacionBasica();
    cout << "Teléfono: " << telefono << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Email: " << email << endl;
    cout << "Tipo de sangre: " << tipoSangre << endl;
    cout << "Contacto de emergencia: " << contactoEmergencia << endl;
    cout << "Teléfono emergencia: " << telefonoEmergencia << endl;
    cout << "Citas registradas: " << cantidadCitas << endl;
    
    // Mostrar fechas
    char buffer[100];
    struct tm* timeinfo;
    
    timeinfo = localtime(&fechaCreacion);
    strftime(buffer, 100, "%d/%m/%Y %H:%M:%S", timeinfo);
    cout << "Fecha de creación: " << buffer << endl;
    
    timeinfo = localtime(&fechaUltimaModificacion);
    strftime(buffer, 100, "%d/%m/%Y %H:%M:%S", timeinfo);
    cout << "Última modificación: " << buffer << endl;
}

void Paciente::mostrarCitas() const {
    if (cantidadCitas == 0) {
        cout << "No tiene citas registradas" << endl;
        return;
    }
    
    cout << "\n=== CITAS DEL PACIENTE ===" << endl;
    for (int i = 0; i < cantidadCitas; i++) {
        cout << i + 1 << ". Cita ID: " << citasIDs[i] << endl;
    }
}

// MÉTODOS AUXILIARES
void Paciente::actualizarFechaModificacion() {
    fechaUltimaModificacion = time(nullptr);
}

void Paciente::inicializarFechas() {
    time_t ahora = time(nullptr);
    fechaCreacion = ahora;
    fechaUltimaModificacion = ahora;
}

// MÉTODO ESTÁTICO
size_t Paciente::obtenerTamano() {
    return sizeof(Paciente);
}