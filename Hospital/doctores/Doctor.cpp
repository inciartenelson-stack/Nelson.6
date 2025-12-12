#include "Doctor.hpp"
#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

// Constructor por defecto
Doctor::Doctor() : id(0), aniosExperiencia(0), costoConsulta(0.0), 
                   disponible(true), cantidadPacientes(0), cantidadCitas(0) {
    strcpy(nombre, "");
    strcpy(apellido, "");
    strcpy(cedula, "");
    strcpy(especialidad, "");
    strcpy(telefono, "");
    strcpy(cedulaProfesional, "");
    strcpy(horarioTrabajo, "Lunes-Viernes 8:00-16:00");
    
    for (int i = 0; i < MAX_PACIENTES; i++) {
        pacientesIDs[i] = 0;
    }
    
    for (int i = 0; i < MAX_CITAS; i++) {
        citasIDs[i] = 0;
    }
    
    inicializarFechas();
}

// Constructor con parámetros principales
Doctor::Doctor(int id, const char* nombre, const char* apellido, const char* cedula,
               const char* especialidad) 
    : id(id), aniosExperiencia(0), costoConsulta(0.0), disponible(true),
      cantidadPacientes(0), cantidadCitas(0) {
    
    setNombre(nombre);
    setApellido(apellido);
    setCedula(cedula);
    setEspecialidad(especialidad);
    
    strcpy(telefono, "");
    strcpy(cedulaProfesional, "");
    strcpy(horarioTrabajo, "Lunes-Viernes 8:00-16:00");
    
    for (int i = 0; i < MAX_PACIENTES; i++) {
        pacientesIDs[i] = 0;
    }
    
    for (int i = 0; i < MAX_CITAS; i++) {
        citasIDs[i] = 0;
    }
    
    inicializarFechas();
}

// Constructor de copia
Doctor::Doctor(const Doctor& otro) 
    : id(otro.id), aniosExperiencia(otro.aniosExperiencia), 
      costoConsulta(otro.costoConsulta), disponible(otro.disponible),
      cantidadPacientes(otro.cantidadPacientes), cantidadCitas(otro.cantidadCitas),
      fechaCreacion(otro.fechaCreacion), fechaUltimaModificacion(otro.fechaUltimaModificacion) {
    
    strcpy(nombre, otro.nombre);
    strcpy(apellido, otro.apellido);
    strcpy(cedula, otro.cedula);
    strcpy(especialidad, otro.especialidad);
    strcpy(telefono, otro.telefono);
    strcpy(cedulaProfesional, otro.cedulaProfesional);
    strcpy(horarioTrabajo, otro.horarioTrabajo);
    
    for (int i = 0; i < MAX_PACIENTES; i++) {
        pacientesIDs[i] = otro.pacientesIDs[i];
    }
    
    for (int i = 0; i < MAX_CITAS; i++) {
        citasIDs[i] = otro.citasIDs[i];
    }
}

// Destructor
Doctor::~Doctor() {
    // No hay recursos dinámicos que liberar
}

// GETTERS
int Doctor::getId() const { return id; }
const char* Doctor::getNombre() const { return nombre; }
const char* Doctor::getApellido() const { return apellido; }
const char* Doctor::getCedula() const { return cedula; }
const char* Doctor::getEspecialidad() const { return especialidad; }
int Doctor::getAniosExperiencia() const { return aniosExperiencia; }
const char* Doctor::getTelefono() const { return telefono; }
const char* Doctor::getCedulaProfesional() const { return cedulaProfesional; }
double Doctor::getCostoConsulta() const { return costoConsulta; }
bool Doctor::getDisponible() const { return disponible; }
const char* Doctor::getHorarioTrabajo() const { return horarioTrabajo; }
int Doctor::getCantidadPacientes() const { return cantidadPacientes; }
const int* Doctor::getPacientesIDs() const { return pacientesIDs; }
int Doctor::getCantidadCitas() const { return cantidadCitas; }
const int* Doctor::getCitasIDs() const { return citasIDs; }
time_t Doctor::getFechaCreacion() const { return fechaCreacion; }
time_t Doctor::getFechaUltimaModificacion() const { return fechaUltimaModificacion; }

// SETTERS CON VALIDACIÓN
void Doctor::setNombre(const char* nombre) {
    if (strlen(nombre) < MAX_NOMBRE) {
        strcpy(this->nombre, nombre);
        actualizarFechaModificacion();
    }
}

void Doctor::setApellido(const char* apellido) {
    if (strlen(apellido) < MAX_APELLIDO) {
        strcpy(this->apellido, apellido);
        actualizarFechaModificacion();
    }
}

void Doctor::setCedula(const char* cedula) {
    if (strlen(cedula) < MAX_CEDULA) {
        strcpy(this->cedula, cedula);
        actualizarFechaModificacion();
    }
}

void Doctor::setEspecialidad(const char* especialidad) {
    if (strlen(especialidad) < MAX_ESPECIALIDAD) {
        strcpy(this->especialidad, especialidad);
        actualizarFechaModificacion();
    }
}

void Doctor::setAniosExperiencia(int anios) {
    if (anios >= 0 && anios <= 60) {
        this->aniosExperiencia = anios;
        actualizarFechaModificacion();
    } else {
        cerr << "Error: Años de experiencia deben estar entre 0 y 60" << endl;
    }
}

void Doctor::setTelefono(const char* telefono) {
    if (strlen(telefono) < MAX_TELEFONO) {
        strcpy(this->telefono, telefono);
        actualizarFechaModificacion();
    }
}

void Doctor::setCedulaProfesional(const char* cedula) {
    if (strlen(cedula) < MAX_CEDULA_PROFESIONAL) {
        strcpy(this->cedulaProfesional, cedula);
        actualizarFechaModificacion();
    }
}

void Doctor::setCostoConsulta(double costo) {
    if (costo >= 0 && costo <= 100000) {
        this->costoConsulta = costo;
        actualizarFechaModificacion();
    } else {
        cerr << "Error: Costo de consulta debe estar entre 0 y 100,000" << endl;
    }
}

void Doctor::setDisponible(bool disponible) {
    this->disponible = disponible;
    actualizarFechaModificacion();
}

void Doctor::setHorarioTrabajo(const char* horario) {
    if (strlen(horario) < 100) {
        strcpy(this->horarioTrabajo, horario);
        actualizarFechaModificacion();
    }
}

// MÉTODOS DE VALIDACIÓN
bool Doctor::validarDatos() const {
    if (strlen(nombre) == 0) {
        cerr << "Error: Nombre no puede estar vacío" << endl;
        return false;
    }
    
    if (strlen(apellido) == 0) {
        cerr << "Error: Apellido no puede estar vacío" << endl;
        return false;
    }
    
    if (strlen(cedula) == 0) {
        cerr << "Error: Cédula no puede estar vacía" << endl;
        return false;
    }
    
    if (!especialidadEsValida()) {
        cerr << "Error: Especialidad no válida" << endl;
        return false;
    }
    
    if (aniosExperiencia < 0 || aniosExperiencia > 60) {
        cerr << "Error: Años de experiencia fuera de rango (0-60)" << endl;
        return false;
    }
    
    if (!costoConsultaValido()) {
        cerr << "Error: Costo de consulta no válido" << endl;
        return false;
    }
    
    return true;
}

bool Doctor::especialidadEsValida() const {
    // Lista de especialidades médicas válidas
    const char* especialidadesValidas[] = {
        "Medicina General", "Pediatría", "Cardiología", "Dermatología",
        "Ginecología", "Ortopedia", "Neurología", "Psiquiatría",
        "Oftalmología", "Otorrinolaringología", "Urología", "Oncología",
        "Endocrinología", "Gastroenterología", "Nefrología", "Reumatología",
        "Cirugía General", "Traumatología", "Anestesiología", "Radiología"
    };
    
    int numEspecialidades = sizeof(especialidadesValidas) / sizeof(especialidadesValidas[0]);
    
    for (int i = 0; i < numEspecialidades; i++) {
        if (strcmp(especialidad, especialidadesValidas[i]) == 0) {
            return true;
        }
    }
    
    return false;
}

bool Doctor::cedulaProfesionalValida() const {
    // Validación básica de cédula profesional
    if (strlen(cedulaProfesional) < 5) {
        return false;
    }
    
    // Debe contener números y/o letras
    bool tieneDigito = false;
    for (size_t i = 0; i < strlen(cedulaProfesional); i++) {
        if (isdigit(cedulaProfesional[i])) {
            tieneDigito = true;
            break;
        }
    }
    
    return tieneDigito;
}

bool Doctor::costoConsultaValido() const {
    return costoConsulta >= 0 && costoConsulta <= 100000;
}

bool Doctor::estaDisponible() const {
    return disponible;
}

// GESTIÓN DE RELACIONES CON PACIENTES Y CITAS
bool Doctor::agregarPacienteID(int pacienteID) {
    if (cantidadPacientes >= MAX_PACIENTES) {
        cerr << "Error: Límite de pacientes alcanzado" << endl;
        return false;
    }
    
    if (pacienteID <= 0) {
        cerr << "Error: ID de paciente inválido" << endl;
        return false;
    }
    
    // Verificar que no exista ya
    if (pacienteExiste(pacienteID)) {
        cerr << "Error: Paciente ya registrado" << endl;
        return false;
    }
    
    pacientesIDs[cantidadPacientes] = pacienteID;
    cantidadPacientes++;
    actualizarFechaModificacion();
    return true;
}

bool Doctor::eliminarPacienteID(int pacienteID) {
    for (int i = 0; i < cantidadPacientes; i++) {
        if (pacientesIDs[i] == pacienteID) {
            // Mover elementos restantes
            for (int j = i; j < cantidadPacientes - 1; j++) {
                pacientesIDs[j] = pacientesIDs[j + 1];
            }
            cantidadPacientes--;
            pacientesIDs[cantidadPacientes] = 0;
            actualizarFechaModificacion();
            return true;
        }
    }
    return false;
}

bool Doctor::agregarCitaID(int citaID) {
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

bool Doctor::eliminarCitaID(int citaID) {
    for (int i = 0; i < cantidadCitas; i++) {
        if (citasIDs[i] == citaID) {
            // Mover elementos restantes
            for (int j = i; j < cantidadCitas - 1; j++) {
                citasIDs[j] = citasIDs[j + 1];
            }
            cantidadCitas--;
            citasIDs[cantidadCitas] = 0;
            actualizarFechaModificacion();
            return true;
        }
    }
    return false;
}

bool Doctor::pacienteExiste(int pacienteID) const {
    for (int i = 0; i < cantidadPacientes; i++) {
        if (pacientesIDs[i] == pacienteID) {
            return true;
        }
    }
    return false;
}

bool Doctor::citaExiste(int citaID) const {
    for (int i = 0; i < cantidadCitas; i++) {
        if (citasIDs[i] == citaID) {
            return true;
        }
    }
    return false;
}

// MÉTODOS DE PRESENTACIÓN
void Doctor::mostrarInformacionBasica() const {
    cout << "\n=== INFORMACIÓN BÁSICA DEL DOCTOR ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Cédula: " << cedula << endl;
    cout << "Especialidad: " << especialidad << endl;
    cout << "Años experiencia: " << aniosExperiencia << endl;
    cout << "Disponible: " << (disponible ? "Sí" : "No") << endl;
}

void Doctor::mostrarInformacionCompleta() const {
    mostrarInformacionBasica();
    cout << "Teléfono: " << telefono << endl;
    cout << "Cédula profesional: " << cedulaProfesional << endl;
    cout << "Costo consulta: $" << costoConsulta << endl;
    cout << "Horario de trabajo: " << horarioTrabajo << endl;
    cout << "Pacientes asignados: " << cantidadPacientes << endl;
    cout << "Citas programadas: " << cantidadCitas << endl;
    
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

void Doctor::mostrarPacientes() const {
    if (cantidadPacientes == 0) {
        cout << "No tiene pacientes asignados" << endl;
        return;
    }
    
    cout << "\n=== PACIENTES ASIGNADOS AL DOCTOR ===" << endl;
    for (int i = 0; i < cantidadPacientes; i++) {
        cout << i + 1 << ". Paciente ID: " << pacientesIDs[i] << endl;
    }
}

void Doctor::mostrarCitas() const {
    if (cantidadCitas == 0) {
        cout << "No tiene citas programadas" << endl;
        return;
    }
    
    cout << "\n=== CITAS DEL DOCTOR ===" << endl;
    for (int i = 0; i < cantidadCitas; i++) {
        cout << i + 1 << ". Cita ID: " << citasIDs[i] << endl;
    }
}

// MÉTODOS AUXILIARES
void Doctor::actualizarFechaModificacion() {
    fechaUltimaModificacion = time(nullptr);
}

void Doctor::inicializarFechas() {
    time_t ahora = time(nullptr);
    fechaCreacion = ahora;
    fechaUltimaModificacion = ahora;
}

// MÉTODO ESTÁTICO
size_t Doctor::obtenerTamano() {
    return sizeof(Doctor);
}