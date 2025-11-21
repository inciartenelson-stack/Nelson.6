//* PROYECTO 2: SISTEMA DE GESTIÓN HOSPITALARIA v2 
 //* Universidad Rafael Urdaneta - Ingeniería de Computación


#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <iomanip>
using namespace std;

// ======================================================================
//  ESTRUCTURAS DE DATOS (según Proyecto 2)
// ======================================================================

struct ArchivoHeader {
    int cantidadRegistros;
    int proximoID;
    int registrosActivos;
    int version;
};

struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];
    
    int siguienteIDPaciente;
    int siguienteIDDoctor;
    int siguienteIDCita;
    int siguienteIDConsulta;
    
    int totalPacientesRegistrados;
    int totalDoctoresRegistrados;
    int totalCitasAgendadas;
    int totalConsultasRealizadas;
};

struct Paciente {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    char sexo;
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    char alergias[500];
    char observaciones[500];
    bool activo;
    
    int cantidadConsultas;
    int primerConsultaID;
    int cantidadCitas;
    int citasIDs[20];
    
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
};

struct Doctor {
    int id;
    char nombre[50];
    char apellido[50];
    char cedulaProfesional[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    bool disponible;
    
    int cantidadPacientes;
    int pacientesIDs[50];
    int cantidadCitas;
    int citasIDs[30];
    
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
};


struct Cita {
    int id;
    int pacienteID;        
    int doctorID;          
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];
    char observaciones[200];
    bool atendida;
    int consultaID;
    bool eliminado;
    time_t fechaCreacion;
    time_t fechaModificacion;
};

struct HistorialMedico {
    int id;
    int pacienteID;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int doctorID;
    float costo;
    int siguienteConsultaID;
    bool eliminado;
    time_t fechaRegistro;
};

// ======================================================================
//  FUNCIONES DE VALIDACIÓN
// ======================================================================

bool esNombreValido(const char* nombre) {
    if (!nombre || strlen(nombre) == 0) return false;
    for (int i = 0; nombre[i] != '\0'; i++) {
        char c = nombre[i];
        if (!(c == ' ' || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return false;
        }
    }
    return true;
}

bool esCedulaValida(const char* cedula) {
    if (!cedula || strlen(cedula) == 0) return false;
    for (int i = 0; cedula[i] != '\0'; i++) {
        if (cedula[i] < '0' || cedula[i] > '9') {
            return false;
        }
    }
    return true;
}

bool validarFecha(const char* fecha) {
    if (!fecha || strlen(fecha) != 10) return false;
    if (fecha[4] != '-' || fecha[7] != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (fecha[i] < '0' || fecha[i] > '9') return false;
    }
    int anio = (fecha[0]-'0')*1000 + (fecha[1]-'0')*100 + (fecha[2]-'0')*10 + (fecha[3]-'0');
    int mes = (fecha[5]-'0')*10 + (fecha[6]-'0');
    int dia = (fecha[8]-'0')*10 + (fecha[9]-'0');
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30) return false;
    }
    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (esBisiesto) {
            if (dia > 29) return false;
        } else {
            if (dia > 28) return false;
        }
    }
    return true;
}

bool validarHora(const char* hora) {
    if (!hora || strlen(hora) != 5) return false;
    if (hora[2] != ':') return false;
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (hora[i] < '0' || hora[i] > '9') return false;
    }
    int h = (hora[0]-'0')*10 + (hora[1]-'0');
    int m = (hora[3]-'0')*10 + (hora[4]-'0');
    return (h >= 0 && h <= 23) && (m >= 0 && m <= 59);
}

bool validarEmail(const char* email) {
    if (!email) return false;
    if (strlen(email) < 5) return false;
    if (!strchr(email, '@')) return false;
    if (!strchr(email, '.')) return false;
    char* arroba = strchr(email, '@');
    char* punto = strchr(email, '.');
    if (arroba > punto) return false;
    return true;
}

void toLower(char* str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] = str[i] + 32;
    }
}

bool strEqualsIgnoreCase(const char* a, const char* b) {
    if (!a || !b) return false;
    char aLow[200], bLow[200];
    strcpy(aLow, a);
    strcpy(bLow, b);
    toLower(aLow);
    toLower(bLow);
    return strcmp(aLow, bLow) == 0;
}

bool contiene(const char* cadena, const char* subcadena) {
    if (!cadena || !subcadena) return false;
    char cad[200], sub[200];
    strcpy(cad, cadena);
    strcpy(sub, subcadena);
    toLower(cad);
    toLower(sub);
    return strstr(cad, sub) != nullptr;
}

// ======================================================================
//  FUNCIONES DE ARCHIVO: HEADER
// ======================================================================

bool inicializarArchivo(const char* nombre) {
    fstream archivo(nombre, ios::binary | ios::out);
    if (!archivo.is_open()) return false;
    
    ArchivoHeader header;
    header.cantidadRegistros = 0;
    header.proximoID = 1;
    header.registrosActivos = 0;
    header.version = 1;
    
    archivo.write((char*)&header, sizeof(ArchivoHeader));
    archivo.close();
    return true;
}

bool verificarArchivo(const char* nombre) {
    ifstream archivo(nombre, ios::binary);
    if (!archivo.is_open()) {
        return inicializarArchivo(nombre);
    }
    
    ArchivoHeader header;
    archivo.read((char*)&header, sizeof(ArchivoHeader));
    archivo.close();
    
    return header.version == 1;
}

ArchivoHeader leerHeader(const char* nombre) {
    ArchivoHeader header;
    ifstream archivo(nombre, ios::binary);
    if (!archivo.is_open()) {
        inicializarArchivo(nombre);
        archivo.open(nombre, ios::binary);
    }
    archivo.read((char*)&header, sizeof(ArchivoHeader));
    archivo.close();
    return header;
}

bool actualizarHeader(const char* nombre, ArchivoHeader& header) {
    fstream archivo(nombre, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    archivo.seekp(0);
    archivo.write((char*)&header, sizeof(ArchivoHeader));
    archivo.close();
    return true;
}

// ======================================================================
//  FUNCIONES DEL HOSPITAL
// ======================================================================

Hospital* cargarDatosHospital() {
    Hospital* h = new Hospital;
    
    if (!verificarArchivo("hospital.bin")) {
        fstream archivo("hospital.bin", ios::binary | ios::out);
        strcpy(h->nombre, "Hospital Central Urdaneta");
        strcpy(h->direccion, "Av. Universidad, Maracaibo");
        strcpy(h->telefono, "0261-1234567");
        h->siguienteIDPaciente = 1;
        h->siguienteIDDoctor = 1;
        h->siguienteIDCita = 1;
        h->siguienteIDConsulta = 1;
        h->totalPacientesRegistrados = 0;
        h->totalDoctoresRegistrados = 0;
        h->totalCitasAgendadas = 0;
        h->totalConsultasRealizadas = 0;
        archivo.write((char*)h, sizeof(Hospital));
        archivo.close();
    } else {
        ifstream archivo("hospital.bin", ios::binary);
        archivo.read((char*)h, sizeof(Hospital));
        archivo.close();
    }
    
    verificarArchivo("pacientes.bin");
    verificarArchivo("doctores.bin");
    verificarArchivo("citas.bin");
    verificarArchivo("historiales.bin");
    
    return h;
}

bool guardarDatosHospital(Hospital* h) {
    fstream archivo("hospital.bin", ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) return false;
    archivo.seekp(0);
    archivo.write((char*)h, sizeof(Hospital));
    archivo.close();
    return true;
}

// ======================================================================
//  FUNCIONES DE PACIENTES
// ======================================================================

long calcularPosicionPaciente(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(Paciente));
}

int buscarIndicePacientePorID(int id) {
    ArchivoHeader header = leerHeader("pacientes.bin");
    ifstream archivo("pacientes.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    
    Paciente p;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&p, sizeof(Paciente));
        if (p.id == id && !p.eliminado) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}

bool agregarPaciente(Hospital* h, const char* nombre, const char* apellido,
                     const char* cedula, int edad, char sexo,
                     const char* telefono, const char* email) {
    if (!esNombreValido(nombre)) {
        cout << "Error: El nombre no debe contener numeros ni símbolos.\n";
        return false;
    }
    if (!esNombreValido(apellido)) {
        cout << "Error: El apellido no debe contener numeros ni símbolos.\n";
        return false;
    }
    if (!esCedulaValida(cedula)) {
        cout << "Error: La cédula debe contener solo digitos.\n";
        return false;
    }
    if (edad < 0 || edad > 120) {
        cout << "Error: Edad debe estar entre 0 y 120.\n";
        return false;
    }
    if (sexo != 'M' && sexo != 'F') {
        cout << "Error: Sexo debe ser 'M' o 'F'.\n";
        return false;
    }
    if (strlen(telefono) < 7 || strlen(telefono) > 15) {
        cout << "Error: Telefono debe tener entre 7 y 15 dígitos.\n";
        return false;
    }
    if (!validarEmail(email)) {
        cout << "Error: Formato de email inválido.\n";
        return false;
    }
    
    ArchivoHeader header = leerHeader("pacientes.bin");
    ifstream archivo("pacientes.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    Paciente p;
    bool cedulaRepetida = false;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&p, sizeof(Paciente));
        if (p.id != -1 && !p.eliminado && strcmp(p.cedula, cedula) == 0) {
            cedulaRepetida = true;
            break;
        }
    }
    archivo.close();
    if (cedulaRepetida) {
        cout << "Error: Cedula ya registrada.\n";
        return false;
    }
    
    Paciente nuevo;
    nuevo.id = h->siguienteIDPaciente++;
    strcpy(nuevo.nombre, nombre);
    strcpy(nuevo.apellido, apellido);
    strcpy(nuevo.cedula, cedula);
    nuevo.edad = edad;
    nuevo.sexo = sexo;
    nuevo.tipoSangre[0] = '\0';
    strcpy(nuevo.telefono, telefono);
    nuevo.direccion[0] = '\0';
    strcpy(nuevo.email, email);
    nuevo.alergias[0] = '\0';
    nuevo.observaciones[0] = '\0';
    nuevo.activo = true;
    nuevo.cantidadConsultas = 0;
    nuevo.primerConsultaID = -1;
    nuevo.cantidadCitas = 0;
    for (int i = 0; i < 20; i++) nuevo.citasIDs[i] = -1;
    nuevo.eliminado = false;
    time_t ahora = time(0);
    nuevo.fechaCreacion = ahora;
    nuevo.fechaModificacion = ahora;
    
    fstream archivo2("pacientes.bin", ios::binary | ios::app);
    archivo2.write((char*)&nuevo, sizeof(Paciente));
    archivo2.close();
    
    header.cantidadRegistros++;
    header.registrosActivos++;
    header.proximoID = h->siguienteIDPaciente;
    actualizarHeader("pacientes.bin", header);
    
    h->totalPacientesRegistrados++;
    return true;
}

Paciente leerPacientePorIndice(int indice) {
    Paciente p;
    ifstream archivo("pacientes.bin", ios::binary);
    long pos = calcularPosicionPaciente(indice);
    archivo.seekg(pos);
    archivo.read((char*)&p, sizeof(Paciente));
    archivo.close();
    return p;
}

Paciente leerPacientePorID(int id) {
    int idx = buscarIndicePacientePorID(id);
    if (idx == -1) {
        Paciente vacio;
        vacio.id = -1;
        return vacio;
    }
    return leerPacientePorIndice(idx);
}

bool actualizarPaciente(Paciente p) {
    int idx = buscarIndicePacientePorID(p.id);
    if (idx == -1) return false;
    
    fstream archivo("pacientes.bin", ios::binary | ios::in | ios::out);
    long pos = calcularPosicionPaciente(idx);
    archivo.seekp(pos);
    p.fechaModificacion = time(0);
    archivo.write((char*)&p, sizeof(Paciente));
    archivo.close();
    return true;
}

bool eliminarPaciente(Hospital* h, int id) {
    int idx = buscarIndicePacientePorID(id);
    if (idx == -1) return false;
    
    Paciente p = leerPacientePorIndice(idx);
    p.eliminado = true;
    
    fstream archivo("pacientes.bin", ios::binary | ios::in | ios::out);
    long pos = calcularPosicionPaciente(idx);
    archivo.seekp(pos);
    archivo.write((char*)&p, sizeof(Paciente));
    archivo.close();
    
    ArchivoHeader header = leerHeader("pacientes.bin");
    header.registrosActivos--;
    actualizarHeader("pacientes.bin", header);
    
    h->totalPacientesRegistrados--;
    return true;
}

void listarTodosPacientes() {
    ArchivoHeader header = leerHeader("pacientes.bin");
    ifstream archivo("pacientes.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    
    Paciente p;
    int activos = 0;
    cout << "\n-------------------------------------------------\n";
    cout << "¦ ID  ¦ NOMBRE COMPLETO     ¦ CEDULA       ¦ EDAD ¦\n";
    cout << "¦-----+---------------------+--------------+------¦\n";
    
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&p, sizeof(Paciente));
        if (!p.eliminado) {
            cout << "¦ " << setw(3) << p.id
                 << " ¦ " << setw(19) << (string(p.nombre) + " " + p.apellido).c_str()
                 << " ¦ " << setw(12) << p.cedula
                 << " ¦ " << setw(4) << p.edad << " ¦\n";
            activos++;
        }
    }
    
    archivo.close();
    cout << "-------------------------------------------------\n";
    cout << "Total de pacientes activos: " << activos << "\n";
}

// ======================================================================
//  FUNCIONES DE HISTORIAL MÉDICO
// ======================================================================

long calcularPosicionHistorial(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(HistorialMedico));
}

int buscarIndiceHistorialPorID(int id) {
    ArchivoHeader header = leerHeader("historiales.bin");
    ifstream archivo("historiales.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    
    HistorialMedico h;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&h, sizeof(HistorialMedico));
        if (h.id == id && !h.eliminado) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}


HistorialMedico leerHistorialPorIndice(int indice) {
    HistorialMedico h;
    ifstream archivo("historiales.bin", ios::binary);
    long pos = calcularPosicionHistorial(indice);
    archivo.seekg(pos);
    archivo.read((char*)&h, sizeof(HistorialMedico));
    archivo.close();
    return h;
}

bool actualizarHistorial(HistorialMedico historial) {
    int idx = buscarIndiceHistorialPorID(historial.id);
    if (idx == -1) return false;
    
    fstream archivo("historiales.bin", ios::binary | ios::in | ios::out);
    long pos = calcularPosicionHistorial(idx);
    archivo.seekp(pos);
    archivo.write((char*)&historial, sizeof(HistorialMedico));
    archivo.close();
    return true;
}

bool agregarConsultaAlHistorial(Hospital* h, int pacienteID, HistorialMedico nueva) {
    Paciente p = leerPacientePorID(pacienteID);
    if (p.id == -1) return false;
    
    ArchivoHeader header = leerHeader("historiales.bin");
    nueva.id = h->siguienteIDConsulta++;
    nueva.pacienteID = pacienteID;
    nueva.eliminado = false;
    nueva.fechaRegistro = time(0);
    
    fstream archivo("historiales.bin", ios::binary | ios::app);
    archivo.write((char*)&nueva, sizeof(HistorialMedico));
    archivo.close();
    
    if (p.primerConsultaID == -1) {
        p.primerConsultaID = nueva.id;
        nueva.siguienteConsultaID = -1;
    } else {
        int actualID = p.primerConsultaID;
        HistorialMedico actual;
        while (true) {
            int idxHist = buscarIndiceHistorialPorID(actualID);
            if (idxHist == -1) break;
            actual = leerHistorialPorIndice(idxHist);
            if (actual.siguienteConsultaID == -1) {
                actual.siguienteConsultaID = nueva.id;
                actualizarHistorial(actual);
                break;
            }
            actualID = actual.siguienteConsultaID;
        }
        nueva.siguienteConsultaID = -1;
    }
    
    int idxNueva = buscarIndiceHistorialPorID(nueva.id);
    fstream archivo2("historiales.bin", ios::binary | ios::in | ios::out);
    long pos = calcularPosicionHistorial(idxNueva);
    archivo2.seekp(pos);
    archivo2.write((char*)&nueva, sizeof(HistorialMedico));
    archivo2.close();
    
    p.cantidadConsultas++;
    actualizarPaciente(p);
    
    header.cantidadRegistros++;
    header.registrosActivos++;
    header.proximoID = h->siguienteIDConsulta;
    actualizarHeader("historiales.bin", header);
    
    h->totalConsultasRealizadas++;
    return true;
}

HistorialMedico* leerHistorialCompleto(int pacienteID, int* cantidad) {
    Paciente p = leerPacientePorID(pacienteID);
    if (p.id == -1 || p.primerConsultaID == -1) {
        *cantidad = 0;
        return nullptr;
    }
    
    *cantidad = p.cantidadConsultas;
    HistorialMedico* historial = new HistorialMedico[*cantidad];
    
    int idx = 0;
    int actualID = p.primerConsultaID;
    while (actualID != -1 && idx < *cantidad) {
        int indiceHist = buscarIndiceHistorialPorID(actualID);
        if (indiceHist == -1) break;
        historial[idx] = leerHistorialPorIndice(indiceHist);
        actualID = historial[idx].siguienteConsultaID;
        idx++;
    }
    
    return historial;
}

void mostrarHistorialMedico(int pacienteID) {
    int cantidad;
    HistorialMedico* historial = leerHistorialCompleto(pacienteID, &cantidad);
    if (!historial || cantidad == 0) {
        cout << "No hay historial médico.\n";
        return;
    }
    
    cout << "\n--------------------------------------------------------------------------------\n";
    cout << "¦                                HISTORIAL MÉDICO                                ¦\n";
    cout << "¦--------------------------------------------------------------------------------¦\n";
    cout << "¦ ID   ¦ FECHA      ¦ HORA   ¦ DIAGNÓSTICO                                      ¦\n";
    cout << "¦------+------------+--------+---------------------------------------------------¦\n";
    for (int i = 0; i < cantidad; i++) {
        cout << "¦ " << setw(4) << historial[i].id
             << " ¦ " << setw(10) << historial[i].fecha
             << " ¦ " << setw(6) << historial[i].hora
             << " ¦ " << setw(48) << historial[i].diagnostico << " ¦\n";
    }
    cout << "--------------------------------------------------------------------------------\n";
    
    delete[] historial;
}

// ======================================================================
//  FUNCIONES DE DOCTORES
// ======================================================================

long calcularPosicionDoctor(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(Doctor));
}

int buscarIndiceDoctorPorID(int id) {
    ArchivoHeader header = leerHeader("doctores.bin");
    ifstream archivo("doctores.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    Doctor d;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&d, sizeof(Doctor));
        if (d.id == id && !d.eliminado) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}

bool agregarDoctor(Hospital* h, const char* nombre, const char* apellido,
                   const char* cedula, const char* especialidad,
                   int aniosExperiencia, float costoConsulta,
                   const char* telefono, const char* email) {
    if (!esNombreValido(nombre)) {
        cout << "Error: El nombre no debe contener números ni símbolos.\n";
        return false;
    }
    if (!esNombreValido(apellido)) {
        cout << "Error: El apellido no debe contener números ni símbolos.\n";
        return false;
    }
    if (!esCedulaValida(cedula)) {
        cout << "Error: La cédula debe contener solo dígitos.\n";
        return false;
    }
    if (aniosExperiencia < 0) {
        cout << "Error: Años de experiencia no pueden ser negativos.\n";
        return false;
    }
    if (costoConsulta <= 0) {
        cout << "Error: El costo de consulta debe ser positivo.\n";
        return false;
    }
    if (strlen(telefono) < 7 || strlen(telefono) > 15) {
        cout << "Error: Teléfono debe tener entre 7 y 15 dígitos.\n";
        return false;
    }
    if (!validarEmail(email)) {
        cout << "Error: Formato de email inválido.\n";
        return false;
    }
    
    ArchivoHeader header = leerHeader("doctores.bin");
    ifstream archivo("doctores.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    Doctor d;
    bool cedulaRepetida = false;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&d, sizeof(Doctor));
        if (d.id != -1 && !d.eliminado && strcmp(d.cedulaProfesional, cedula) == 0) {
            cedulaRepetida = true;
            break;
        }
    }
    archivo.close();
    if (cedulaRepetida) {
        cout << "Error: Cédula profesional ya registrada.\n";
        return false;
    }
    
    Doctor nuevo;
    nuevo.id = h->siguienteIDDoctor++;
    strcpy(nuevo.nombre, nombre);
    strcpy(nuevo.apellido, apellido);
    strcpy(nuevo.cedulaProfesional, cedula);
    strcpy(nuevo.especialidad, especialidad);
    nuevo.aniosExperiencia = aniosExperiencia;
    nuevo.costoConsulta = costoConsulta;
    nuevo.horarioAtencion[0] = '\0';
    strcpy(nuevo.telefono, telefono);
    strcpy(nuevo.email, email);
    nuevo.disponible = true;
    nuevo.cantidadPacientes = 0;
    for (int i = 0; i < 50; i++) nuevo.pacientesIDs[i] = -1;
    nuevo.cantidadCitas = 0;
    for (int i = 0; i < 30; i++) nuevo.citasIDs[i] = -1;
    nuevo.eliminado = false;
    time_t ahora = time(0);
    nuevo.fechaCreacion = ahora;
    nuevo.fechaModificacion = ahora;
    
    fstream archivo2("doctores.bin", ios::binary | ios::app);
    archivo2.write((char*)&nuevo, sizeof(Doctor));
    archivo2.close();
    
    header.cantidadRegistros++;
    header.registrosActivos++;
    header.proximoID = h->siguienteIDDoctor;
    actualizarHeader("doctores.bin", header);
    
    h->totalDoctoresRegistrados++;
    return true;
}

Doctor leerDoctorPorID(int id) {
    int idx = buscarIndiceDoctorPorID(id);
    if (idx == -1) {
        Doctor vacio;
        vacio.id = -1;
        return vacio;
    }
    Doctor d;
    ifstream archivo("doctores.bin", ios::binary);
    long pos = calcularPosicionDoctor(idx);
    archivo.seekg(pos);
    archivo.read((char*)&d, sizeof(Doctor));
    archivo.close();
    return d;
}

bool actualizarDoctor(Doctor d) {
    int idx = buscarIndiceDoctorPorID(d.id);
    if (idx == -1) return false;
    fstream archivo("doctores.bin", ios::binary | ios::in | ios::out);
    long pos = calcularPosicionDoctor(idx);
    archivo.seekp(pos);
    d.fechaModificacion = time(0);
    archivo.write((char*)&d, sizeof(Doctor));
    archivo.close();
    return true;
}

void listarTodosDoctores() {
    ArchivoHeader header = leerHeader("doctores.bin");
    ifstream archivo("doctores.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    
    Doctor d;
    int activos = 0;
    cout << "\n+-------------------------------------------------------------------+\n";
    cout << "¦ ID  ¦ NOMBRE COMPLETO     ¦ ESPECIALIDAD       ¦ COSTO CONSULTA   ¦\n";
    cout << "¦-----+---------------------+--------------------+------------------¦\n";
    
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&d, sizeof(Doctor));
        if (!d.eliminado) {
            cout << "¦ " << setw(3) << d.id
                 << " ¦ " << setw(19) << (string(d.nombre) + " " + d.apellido).c_str()
                 << " ¦ " << setw(18) << d.especialidad
                 << " ¦ $" << setw(14) << fixed << setprecision(2) << d.costoConsulta << " ¦\n";
            activos++;
        }
    }
    
    archivo.close();
    cout << "+-------------------------------------------------------------------+\n";
    cout << "Total de doctores activos: " << activos << "\n";
}

// ======================================================================
//  FUNCIONES DE CITAS
// ======================================================================

long calcularPosicionCita(int indice) {
    return sizeof(ArchivoHeader) + (indice * sizeof(Cita));
}

int buscarIndiceCitaPorID(int id) {
    ArchivoHeader header = leerHeader("citas.bin");
    ifstream archivo("citas.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    Cita c;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (c.id == id && !c.eliminado) {
            archivo.close();
            return i;
        }
    }
    archivo.close();
    return -1;
}

bool verificarDisponibilidad(int idDoctor, const char* fecha, const char* hora) {
    ArchivoHeader header = leerHeader("citas.bin");
    ifstream archivo("citas.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    Cita c;
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (c.doctorID == idDoctor && 
            strcmp(c.fecha, fecha) == 0 && 
            strcmp(c.hora, hora) == 0 &&
            strcmp(c.estado, "Agendada") == 0 &&
            !c.eliminado) {
            archivo.close();
            return false;
        }
    }
    archivo.close();
    return true;
}

bool agregarCita(Hospital* h, int idPaciente, int idDoctor,
                 const char* fecha, const char* hora, const char* motivo) {
    Paciente p = leerPacientePorID(idPaciente);
    Doctor d = leerDoctorPorID(idDoctor);
    if (p.id == -1) {
        cout << "Error: Paciente no encontrado.\n";
        return false;
    }
    if (d.id == -1) {
        cout << "Error: Doctor no encontrado.\n";
        return false;
    }
    
    if (!validarFecha(fecha) || !validarHora(hora)) {
        cout << "Error: Fecha u hora inválida.\n";
        return false;
    }
    
    if (!verificarDisponibilidad(idDoctor, fecha, hora)) {
        cout << "Error: El doctor no esta disponible en esa fecha/hora.\n";
        return false;
    }
    
    Cita nueva;
    nueva.id = h->siguienteIDCita++;
    nueva.pacienteID = idPaciente;
    nueva.doctorID = idDoctor;
    strcpy(nueva.fecha, fecha);
    strcpy(nueva.hora, hora);
    strcpy(nueva.motivo, motivo);
    strcpy(nueva.estado, "Agendada");
    nueva.observaciones[0] = '\0';
    nueva.atendida = false;
    nueva.consultaID = -1;
    nueva.eliminado = false;
    time_t ahora = time(0);
    nueva.fechaCreacion = ahora;
    nueva.fechaModificacion = ahora;
    
    fstream archivo("citas.bin", ios::binary | ios::app);
    archivo.write((char*)&nueva, sizeof(Cita));
    archivo.close();
    
    ArchivoHeader header = leerHeader("citas.bin");
    header.cantidadRegistros++;
    header.registrosActivos++;
    header.proximoID = h->siguienteIDCita;
    actualizarHeader("citas.bin", header);
    
    h->totalCitasAgendadas++;
    
    if (p.cantidadCitas < 20) {
        p.citasIDs[p.cantidadCitas] = nueva.id;
        p.cantidadCitas++;
        actualizarPaciente(p);
    }
    
    if (d.cantidadCitas < 30) {
        d.citasIDs[d.cantidadCitas] = nueva.id;
        d.cantidadCitas++;
        actualizarDoctor(d);
    }
    
    return true;
}

bool cancelarCita(int idCita) {
    int idx = buscarIndiceCitaPorID(idCita);
    if (idx == -1) return false;
    
    Cita c;
    ifstream archivo("citas.bin", ios::binary);
    long pos = calcularPosicionCita(idx);
    archivo.seekg(pos);
    archivo.read((char*)&c, sizeof(Cita));
    archivo.close();
    
    if (strcmp(c.estado, "Agendada") != 0) {
        cout << "Error: La cita ya fue atendida o cancelada.\n";
        return false;
    }
    
    c.eliminado = true;
    strcpy(c.estado, "Cancelada");
    
    fstream archivo2("citas.bin", ios::binary | ios::in | ios::out);
    archivo2.seekp(pos);
    archivo2.write((char*)&c, sizeof(Cita));
    archivo2.close();
    
    ArchivoHeader header = leerHeader("citas.bin");
    header.registrosActivos--;
    actualizarHeader("citas.bin", header);
    
    return true;
}

bool atenderCita(Hospital* h, int idCita, const char* diagnostico,
                 const char* tratamiento, const char* medicamentos) {
    int idx = buscarIndiceCitaPorID(idCita);
    if (idx == -1) return false;
    
    Cita c;
    ifstream archivo("citas.bin", ios::binary);
    long pos = calcularPosicionCita(idx);
    archivo.seekg(pos);
    archivo.read((char*)&c, sizeof(Cita));
    archivo.close();
    
    if (strcmp(c.estado, "Agendada") != 0) {
        cout << "Error: La cita ya fue atendida o cancelada.\n";
        return false;
    }
    
    Paciente p = leerPacientePorID(c.pacienteID);
    Doctor d = leerDoctorPorID(c.doctorID);
    if (p.id == -1 || d.id == -1) {
        cout << "Error: Paciente o doctor no encontrado.\n";
        return false;
    }
    
    HistorialMedico hist;
    hist.pacienteID = c.pacienteID;
    strcpy(hist.fecha, c.fecha);
    strcpy(hist.hora, c.hora);
    strcpy(hist.diagnostico, diagnostico);
    strcpy(hist.tratamiento, tratamiento);
    strcpy(hist.medicamentos, medicamentos);
    hist.doctorID = d.id;
    hist.costo = d.costoConsulta;
    
    if (!agregarConsultaAlHistorial(h, c.pacienteID, hist)) {
        cout << "Error: No se pudo agregar al historial médico.\n";
        return false;
    }
    
    c.estado[0] = '\0';
    strcpy(c.estado, "Atendida");
    c.atendida = true;
    c.consultaID = hist.id;
    c.fechaModificacion = time(0);
    
    fstream archivo2("citas.bin", ios::binary | ios::in | ios::out);
    archivo2.seekp(pos);
    archivo2.write((char*)&c, sizeof(Cita));
    archivo2.close();
    
    return true;
}

void listarCitasPendientes() {
    ArchivoHeader header = leerHeader("citas.bin");
    ifstream archivo("citas.bin", ios::binary);
    archivo.seekg(sizeof(ArchivoHeader));
    
    Cita c;
    bool hay = false;
    cout << "\n+-------------------------------------------------------------------------------+\n";
    cout << "¦ ID  ¦ PACIENTE     ¦ DOCTOR     ¦ FECHA      ¦ MOTIVO                           ¦\n";
    cout << "¦-----+--------------+------------+------------+----------------------------------¦\n";
    
    for (int i = 0; i < header.cantidadRegistros; i++) {
        archivo.read((char*)&c, sizeof(Cita));
        if (strcmp(c.estado, "Agendada") == 0 && !c.eliminado) {
            hay = true;
            Paciente p = leerPacientePorID(c.pacienteID);
            Doctor d = leerDoctorPorID(c.doctorID);
            cout << "¦ " << setw(3) << c.id
                 << " ¦ " << setw(12) << (p.id != -1 ? p.nombre : "???")
                 << " ¦ " << setw(10) << (d.id != -1 ? d.nombre : "???")
                 << " ¦ " << setw(10) << c.fecha
                 << " ¦ " << setw(32) << c.motivo << " ¦\n";
        }
    }
    
    if (!hay) cout << "¦                        No hay citas pendientes.                              ¦\n";
    cout << "+---------------------------------------------------------------------------------+\n";
    archivo.close();
}

// ======================================================================
//  MENÚS Y FUNCIÓN PRINCIPAL
// ======================================================================

void menuPacientes(Hospital* h) {
    int op;
    do {
        cout << "\n--- GESTION DE PACIENTES ---\n";
        cout << "1. Registrar paciente\n2. Ver paciente por ID\n3. Eliminar paciente\n";
        cout << "4. Listar todos\n5. Ver historial médico\n6. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();
        if (op == 1) {
            char nombre[50], apellido[50], cedula[20], telefono[15], email[50];
            int edad; char sexo;
            cout << "Nombre: "; cin.getline(nombre, 50);
            cout << "Apellido: "; cin.getline(apellido, 50);
            cout << "Cedula (solo números): "; cin.getline(cedula, 20);
            cout << "Edad: "; cin >> edad;
            cout << "Sexo (M/F): "; cin >> sexo;
            cout << "Telefono: "; cin.ignore(); cin.getline(telefono, 15);
            cout << "Email: "; cin.getline(email, 50);
            agregarPaciente(h, nombre, apellido, cedula, edad, sexo, telefono, email);
        } else if (op == 2) {
            int id; cout << "ID: "; cin >> id;
            Paciente p = leerPacientePorID(id);
            if (p.id != -1) {
                cout << "Paciente: " << p.nombre << " " << p.apellido << "\n";
                cout << "Cédula: " << p.cedula << ", Edad: " << p.edad << "\n";
            } else {
                cout << "Paciente no encontrado.\n";
            }
        } else if (op == 3) {
            int id; cout << "ID: "; cin >> id;
            if (eliminarPaciente(h, id)) {
                cout << "Paciente eliminado.\n";
            } else {
                cout << "Error al eliminar.\n";
            }
        } else if (op == 4) {
            listarTodosPacientes();
        } else if (op == 5) {
            int id; cout << "ID: "; cin >> id;
            mostrarHistorialMedico(id);
        }
    } while (op != 6);
}

void menuDoctores(Hospital* h) {
    int op;
    do {
        cout << "\n--- GESTION DE DOCTORES ---\n";
        cout << "1. Registrar doctor\n2. Listar todos\n3. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();
        if (op == 1) {
            char nombre[50], apellido[50], cedula[20], especialidad[50], telefono[15], email[50];
            int exp; float costo;
            cout << "Nombre: "; cin.getline(nombre, 50);
            cout << "Apellido: "; cin.getline(apellido, 50);
            cout << "Cedula: "; cin.getline(cedula, 20);
            cout << "Especialidad: "; cin.getline(especialidad, 50);
            cout << "Años experiencia: "; cin >> exp;
            cout << "Costo consulta: "; cin >> costo;
            cout << "Telefono: "; cin.ignore(); cin.getline(telefono, 15);
            cout << "Email: "; cin.getline(email, 50);
            agregarDoctor(h, nombre, apellido, cedula, especialidad, exp, costo, telefono, email);
        } else if (op == 2) {
            listarTodosDoctores();
        }
    } while (op != 3);
}

void menuCitas(Hospital* h) {
    int op;
    do {
        cout << "\n--- GESTION DE CITAS ---\n";
        cout << "1. Agendar cita\n2. Cancelar cita\n3. Atender cita\n";
        cout << "4. Ver citas pendientes\n5. Volver\nOpcion: ";
        cin >> op;
        cin.ignore();
        if (op == 1) {
            int idP, idD;
            char fecha[11], hora[6], motivo[150];
            cout << "ID Paciente: "; cin >> idP;
            cout << "ID Doctor: "; cin >> idD;
            cout << "Fecha (YYYY-MM-DD): "; cin.ignore(); cin.getline(fecha, 11);
            cout << "Hora (HH:MM): "; cin.getline(hora, 6);
            cout << "Motivo: "; cin.getline(motivo, 150);
            agregarCita(h, idP, idD, fecha, hora, motivo);
        } else if (op == 2) {
            int id; cout << "ID Cita: "; cin >> id;
            if (cancelarCita(id)) {
                cout << "Cita cancelada.\n";
            } else {
                cout << "Error al cancelar.\n";
            }
        } else if (op == 3) {
            int id;
            char diag[200], trat[200], meds[150];
            cout << "ID Cita: "; cin >> id;
            cout << "Diagnóstico: "; cin.ignore(); cin.getline(diag, 200);
            cout << "Tratamiento: "; cin.getline(trat, 200);
            cout << "Medicamentos: "; cin.getline(meds, 150);
            atenderCita(h, id, diag, trat, meds);
        } else if (op == 4) {
            listarCitasPendientes();
        }
    } while (op != 5);
}

int main() {
    Hospital* h = cargarDatosHospital();
    
    int op;
    do {
        cout << "\n----------------------------------------\n";
        cout << "¦   SISTEMA DE GESTION HOSPITALARIA v2   ¦\n";
        cout << "----------------------------------------\n";
        cout << "1. Gestion de Pacientes\n2. Gestion de Doctores\n3. Gestion de Citas\n4. Salir\n";
        cout << "Opción: ";
        cin >> op;
        if (op == 1) menuPacientes(h);
        else if (op == 2) menuDoctores(h);
        else if (op == 3) menuCitas(h);
    } while (op != 4);
    
    guardarDatosHospital(h);
    delete h;
    return 0;
}