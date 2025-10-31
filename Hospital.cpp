#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
using namespace std;


struct HistorialMedico {
    int idConsulta;
    char fecha[11];         
    char hora[6];           
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;
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
    
    HistorialMedico* historial;
    int cantidadConsultas;
    int capacidadHistorial;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    char alergias[500];
    char observaciones[500];
    
    bool activo;
};

struct Doctor {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    char especialidad[50];
    int aniosExperiencia;
    float costoConsulta;
    char horarioAtencion[50];
    char telefono[15];
    char email[50];
    
    int* pacientesAsignados;
    int cantidadPacientes;
    int capacidadPacientes;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    bool disponible;
};

struct Cita {
    int id;
    int idPaciente;
    int idDoctor;
    char fecha[11];
    char hora[6];
    char motivo[150];
    char estado[20];        
    char observaciones[200];
    bool atendida;
};

struct Hospital {
    char nombre[100];
    char direccion[150];
    char telefono[15];
    
    Paciente* pacientes;
    int cantidadPacientes;
    int capacidadPacientes;
    
    Doctor* doctores;
    int cantidadDoctores;
    int capacidadDoctores;
    
    Cita* citas;
    int cantidadCitas;
    int capacidadCitas;
    
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;
};


char* copiarString(const char* origen) {
    if (!origen) return NULL;
    size_t len = strlen(origen);
    char* copia = new char[len + 1];
    strcpy(copia, origen);
    return copia;
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
    return strstr(cad, sub) != NULL;
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
 
    if (mes == 2) return dia <= 29; 
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return dia <= 30;
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


bool verificarDisponibilidad(Hospital* hospital, int idDoctor, const char* fecha, const char* hora) {
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita* c = &hospital->citas[i];
        if (c->idDoctor == idDoctor && 
            strcmp(c->fecha, fecha) == 0 && 
            strcmp(c->hora, hora) == 0 &&
            strcmp(c->estado, "Agendada") == 0) {
            return false; 
        }
    }
    return true;
}



Hospital* inicializarHospital(const char* nombre, int capacidadInicial = 10) {
    Hospital* h = new Hospital;
    strcpy(h->nombre, nombre);
    h->direccion[0] = '\0';
    h->telefono[0] = '\0';
    
    h->pacientes = new Paciente[capacidadInicial];
    h->capacidadPacientes = capacidadInicial;
    h->cantidadPacientes = 0;
    
    h->doctores = new Doctor[capacidadInicial];
    h->capacidadDoctores = capacidadInicial;
    h->cantidadDoctores = 0;
    
    h->citas = new Cita[capacidadInicial * 2];
    h->capacidadCitas = capacidadInicial * 2;
    h->cantidadCitas = 0;
    
    h->siguienteIdPaciente = 1;
    h->siguienteIdDoctor = 1;
    h->siguienteIdCita = 1;
    h->siguienteIdConsulta = 1;
    
    return h;
}

void destruirHospital(Hospital* hospital) {
    if (!hospital) return;
    
    
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        delete[] hospital->pacientes[i].historial;
        delete[] hospital->pacientes[i].citasAgendadas;
    }
    delete[] hospital->pacientes;
    
 
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        delete[] hospital->doctores[i].pacientesAsignados;
        delete[] hospital->doctores[i].citasAgendadas;
    }
    delete[] hospital->doctores;
    
 
    delete[] hospital->citas;
    
    delete hospital;
}



void redimensionarArrayPacientes(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadPacientes * 2;
    Paciente* nuevoArray = new Paciente[nuevaCapacidad];
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        nuevoArray[i] = hospital->pacientes[i];
    }
    delete[] hospital->pacientes;
    hospital->pacientes = nuevoArray;
    hospital->capacidadPacientes = nuevaCapacidad;
}

void redimensionarArrayDoctores(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadDoctores * 2;
    Doctor* nuevoArray = new Doctor[nuevaCapacidad];
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        nuevoArray[i] = hospital->doctores[i];
    }
    delete[] hospital->doctores;
    hospital->doctores = nuevoArray;
    hospital->capacidadDoctores = nuevaCapacidad;
}

void redimensionarArrayCitas(Hospital* hospital) {
    int nuevaCapacidad = hospital->capacidadCitas * 2;
    Cita* nuevoArray = new Cita[nuevaCapacidad];
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        nuevoArray[i] = hospital->citas[i];
    }
    delete[] hospital->citas;
    hospital->citas = nuevoArray;
    hospital->capacidadCitas = nuevaCapacidad;
}



Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedula) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strEqualsIgnoreCase(hospital->pacientes[i].cedula, cedula)) {
            return &hospital->pacientes[i];
        }
    }
    return NULL;
}

Paciente* buscarPacientePorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            return &hospital->pacientes[i];
        }
    }
    return NULL;
}

Paciente** buscarPacientesPorNombre(Hospital* hospital, const char* nombre, int* cantidad) {
    *cantidad = 0;
    
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        char nombreCompleto[101];
        strcpy(nombreCompleto, hospital->pacientes[i].nombre);
        strcat(nombreCompleto, " ");
        strcat(nombreCompleto, hospital->pacientes[i].apellido);
        if (contiene(nombreCompleto, nombre)) {
            (*cantidad)++;
        }
    }
    if (*cantidad == 0) return NULL;
    
    Paciente** resultados = new Paciente*[*cantidad];
    int idx = 0;
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        char nombreCompleto[101];
        strcpy(nombreCompleto, hospital->pacientes[i].nombre);
        strcat(nombreCompleto, " ");
        strcat(nombreCompleto, hospital->pacientes[i].apellido);
        if (contiene(nombreCompleto, nombre)) {
            resultados[idx++] = &hospital->pacientes[i];
        }
    }
    return resultados;
}

Paciente* crearPaciente(Hospital* hospital, const char* nombre, const char* apellido,
                        const char* cedula, int edad, char sexo) {
    if (buscarPacientePorCedula(hospital, cedula)) {
        cout << "Error: Cedula ya registrada.\n";
        return NULL;
    }
    if (edad < 0 || edad > 120) {
        cout << "Error: Edad invalida.\n";
        return NULL;
    }
    if (sexo != 'M' && sexo != 'F') {
        cout << "Error: Sexo debe ser 'M' o 'F'.\n";
        return NULL;
    }
    
    if (hospital->cantidadPacientes >= hospital->capacidadPacientes) {
        redimensionarArrayPacientes(hospital);
    }
    
    Paciente* p = &hospital->pacientes[hospital->cantidadPacientes];
    p->id = hospital->siguienteIdPaciente++;
    strcpy(p->nombre, nombre);
    strcpy(p->apellido, apellido);
    strcpy(p->cedula, cedula);
    p->edad = edad;
    p->sexo = sexo;
    p->tipoSangre[0] = '\0';
    p->telefono[0] = '\0';
    p->direccion[0] = '\0';
    p->email[0] = '\0';
    p->alergias[0] = '\0';
    p->observaciones[0] = '\0';
    p->activo = true;
    
    
    p->historial = new HistorialMedico[5];
    p->capacidadHistorial = 5;
    p->cantidadConsultas = 0;
    
    p->citasAgendadas = new int[5];
    p->capacidadCitas = 5;
    p->cantidadCitas = 0;
    
    hospital->cantidadPacientes++;
    return p;
}

void agregarConsultaAlHistorial(Paciente* paciente, HistorialMedico consulta) {
    if (paciente->cantidadConsultas >= paciente->capacidadHistorial) {
        int nuevaCap = paciente->capacidadHistorial * 2;
        HistorialMedico* nuevo = new HistorialMedico[nuevaCap];
        for (int i = 0; i < paciente->cantidadConsultas; i++) {
            nuevo[i] = paciente->historial[i];
        }
        delete[] paciente->historial;
        paciente->historial = nuevo;
        paciente->capacidadHistorial = nuevaCap;
    }
    paciente->historial[paciente->cantidadConsultas++] = consulta;
}

void mostrarHistorialMedico(Paciente* paciente) {
    if (paciente->cantidadConsultas == 0) {
        cout << "No hay historial medico.\n";
        return;
    }
    cout << "=============================================================================================================================================================================================================================== \n";
    cout << "==                                HISTORIAL MEDICO                               ==\n";
    cout << "================================================================================================================================================================================================================================\n";
    cout << "=== ID   == FECHA      == HORA   == DIAGNOSTICO                                      ==n";
    cout << "================================================================================================================================================================================================================================\n";
    for (int i = 0; i < paciente->cantidadConsultas; i++) {
        cout << "============" << setw(4) << paciente->historial[i].idConsulta
             << "============" << setw(10) << paciente->historial[i].fecha
             << "============" << setw(6) << paciente->historial[i].hora
             << "============" << setw(48) << paciente->historial[i].diagnostico << " ==\n";
    }
    cout << "=================================================================================================================================================================================================================================\n";
}

void listarPacientes(Hospital* hospital) {
    if (hospital->cantidadPacientes == 0) {
        cout << "No hay pacientes registrados.\n";
        return;
    }
    cout << "==============================================================================================================================\n";
    cout << "== ID  == NOMBRE COMPLETO     == CEDULA       == EDAD == CONSULTAS==\n";
    cout << "==============================================================================================================================\n";
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        Paciente* p = &hospital->pacientes[i];
        cout << "==" << setw(3) << p->id
             << "==" << setw(19) << (string(p->nombre) + " " + p->apellido).c_str()
             << "==" << setw(12) << p->cedula
             << "==" << setw(4) << p->edad
             << "==" << setw(8) << p->cantidadConsultas << "==\n";
    }
    cout << "==============================================================================================================================\n";
}



Doctor* buscarDoctorPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id) {
            return &hospital->doctores[i];
        }
    }
    return NULL;
}

Doctor** buscarDoctoresPorEspecialidad(Hospital* hospital, const char* especialidad, int* cantidad) {
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (strEqualsIgnoreCase(hospital->doctores[i].especialidad, especialidad)) {
            (*cantidad)++;
        }
    }
    if (*cantidad == 0) return NULL;
    
    Doctor** resultados = new Doctor*[*cantidad];
    int idx = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (strEqualsIgnoreCase(hospital->doctores[i].especialidad, especialidad)) {
            resultados[idx++] = &hospital->doctores[i];
        }
    }
    return resultados;
}

Doctor* crearDoctor(Hospital* hospital, const char* nombre, const char* apellido,
                    const char* cedula, const char* especialidad, int aniosExperiencia,
                    float costoConsulta) {
    if (aniosExperiencia < 0) {
        cout << "Error: Anios de experiencia invÃ¡lidos.\n";
        return NULL;
    }
    if (costoConsulta <= 0) {
        cout << "Error: Costo de consulta debe ser positivo.\n";
        return NULL;
    }
    
    if (hospital->cantidadDoctores >= hospital->capacidadDoctores) {
        redimensionarArrayDoctores(hospital);
    }
    
    Doctor* d = &hospital->doctores[hospital->cantidadDoctores];
    d->id = hospital->siguienteIdDoctor++;
    strcpy(d->nombre, nombre);
    strcpy(d->apellido, apellido);
    strcpy(d->cedula, cedula);
    strcpy(d->especialidad, especialidad);
    d->aniosExperiencia = aniosExperiencia;
    d->costoConsulta = costoConsulta;
    d->horarioAtencion[0] = '\0';
    d->telefono[0] = '\0';
    d->email[0] = '\0';
    d->disponible = true;
    
    d->pacientesAsignados = new int[5];
    d->capacidadPacientes = 5;
    d->cantidadPacientes = 0;
    
    d->citasAgendadas = new int[10];
    d->capacidadCitas = 10;
    d->cantidadCitas = 0;
    
    hospital->cantidadDoctores++;
    return d;
}

bool asignarPacienteADoctor(Doctor* doctor, int idPaciente) {
  
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        if (doctor->pacientesAsignados[i] == idPaciente) return false;
    }
    
    if (doctor->cantidadPacientes >= doctor->capacidadPacientes) {
        int nuevaCap = doctor->capacidadPacientes * 2;
        int* nuevo = new int[nuevaCap];
        for (int i = 0; i < doctor->cantidadPacientes; i++) {
            nuevo[i] = doctor->pacientesAsignados[i];
        }
        delete[] doctor->pacientesAsignados;
        doctor->pacientesAsignados = nuevo;
        doctor->capacidadPacientes = nuevaCap;
    }
    
    doctor->pacientesAsignados[doctor->cantidadPacientes++] = idPaciente;
    return true;
}

void listarDoctores(Hospital* hospital) {
    if (hospital->cantidadDoctores == 0) {
        cout << "No hay doctores registrados.\n";
        return;
    }
    cout << "================================================================================================\n";
    cout << "== ID  == NOMBRE COMPLETO     == ESPECIALIDAD       == COSTO CONSULTA   ==\n";
    cout << "================================================================================================\n";
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        Doctor* d = &hospital->doctores[i];
        cout << "== " << setw(3) << d->id
             << "==" << setw(19) << (string(d->nombre) + " " + d->apellido).c_str()
             << "==" << setw(18) << d->especialidad
             << "== $" << setw(14) << fixed << setprecision(2) << d->costoConsulta << " ==\n";
    }
    cout << "================================================================================================================================================================================================================================\n";
}

// ================================
// GESTIÃ“N DE CITAS
// ================================

Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor,
                  const char* fecha, const char* hora, const char* motivo) {
    Paciente* p = buscarPacientePorId(hospital, idPaciente);
    Doctor* d = buscarDoctorPorId(hospital, idDoctor);
    if (!p || !d) {
        cout << "Error: Paciente o doctor no encontrado.\n";
        return NULL;
    }
    if (!validarFecha(fecha) || !validarHora(hora)) {
        cout << "Error: Fecha u hora invalida.\n";
        return NULL;
    }
    if (!verificarDisponibilidad(hospital, idDoctor, fecha, hora)) {
        cout << "Error: El doctor no esta disponible en esa fecha/hora.\n";
        return NULL;
    }
    
    if (hospital->cantidadCitas >= hospital->capacidadCitas) {
        redimensionarArrayCitas(hospital);
    }
    
    Cita* c = &hospital->citas[hospital->cantidadCitas];
    c->id = hospital->siguienteIdCita++;
    c->idPaciente = idPaciente;
    c->idDoctor = idDoctor;
    strcpy(c->fecha, fecha);
    strcpy(c->hora, hora);
    strcpy(c->motivo, motivo);
    strcpy(c->estado, "Agendada");
    c->observaciones[0] = '\0';
    c->atendida = false;
    
   
    if (p->cantidadCitas >= p->capacidadCitas) {
        int nuevaCap = p->capacidadCitas * 2;
        int* nuevo = new int[nuevaCap];
        for (int i = 0; i < p->cantidadCitas; i++) nuevo[i] = p->citasAgendadas[i];
        delete[] p->citasAgendadas;
        p->citasAgendadas = nuevo;
        p->capacidadCitas = nuevaCap;
    }
    p->citasAgendadas[p->cantidadCitas++] = c->id;
    
    if (d->cantidadCitas >= d->capacidadCitas) {
        int nuevaCap = d->capacidadCitas * 2;
        int* nuevo = new int[nuevaCap];
        for (int i = 0; i < d->cantidadCitas; i++) nuevo[i] = d->citasAgendadas[i];
        delete[] d->citasAgendadas;
        d->citasAgendadas = nuevo;
        d->capacidadCitas = nuevaCap;
    }
    d->citasAgendadas[d->cantidadCitas++] = c->id;
    
    hospital->cantidadCitas++;
    return c;
}

bool atenderCita(Hospital* hospital, int idCita, const char* diagnostico,
                 const char* tratamiento, const char* medicamentos) {
    Cita* c = NULL;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].id == idCita) {
            c = &hospital->citas[i];
            break;
        }
    }
    if (!c || strcmp(c->estado, "Agendada") != 0) {
        cout << "Error: Cita no encontrada o ya atendida.\n";
        return false;
    }
    
    
    HistorialMedico hist;
    hist.idConsulta = hospital->siguienteIdConsulta++;
    strcpy(hist.fecha, c->fecha);
    strcpy(hist.hora, c->hora);
    strcpy(hist.diagnostico, diagnostico);
    strcpy(hist.tratamiento, tratamiento);
    strcpy(hist.medicamentos, medicamentos);
    hist.idDoctor = c->idDoctor;
    
    Doctor* d = buscarDoctorPorId(hospital, c->idDoctor);
    hist.costo = d ? d->costoConsulta : 0.0f;
    
    Paciente* p = buscarPacientePorId(hospital, c->idPaciente);
    if (p) {
        agregarConsultaAlHistorial(p, hist);
        
        if (d) asignarPacienteADoctor(d, p->id);
    }
    
    strcpy(c->estado, "Atendida");
    c->atendida = true;
    return true;
}

void listarCitasPendientes(Hospital* hospital) {
    bool hay = false;
    cout << "\==============================================================================================================================\n";
    cout << "== ID  == PACIENTE     == DOCTOR     == FECHA      == MOTIVO                           ==\n";
    cout << "==============================================================================================================================\n";
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita* c = &hospital->citas[i];
        if (strcmp(c->estado, "Agendada") == 0) {
            hay = true;
            Paciente* p = buscarPacientePorId(hospital, c->idPaciente);
            Doctor* d = buscarDoctorPorId(hospital, c->idDoctor);
            cout << "==" << setw(3) << c->id
                 << "==" << setw(12) << (p ? p->nombre : "???")
                 << "==" << setw(10) << (d ? d->nombre : "???")
                 << "==" << setw(10) << c->fecha
                 << "==" << setw(32) << c->motivo << "==\n";
        }
    }
    if (!hay) cout << "==                        No hay citas pendientes.                              ==\n";
    cout << "==============================================================================================================================\n";
}



void menuPacientes(Hospital* hospital) {
    int opcion;
    do {
        cout << "==============================================================================================================================\n";
        cout << "==         GESTION DE PACIENTES         ==\n";
        cout << "==============================================================================================================================\n";
        cout << "== 1. Registrar nuevo paciente         ==\n";
        cout << "== 2. Buscar por cedula               ==\n";
        cout << "== 3. Buscar por nombre                ==\n";
        cout << "== 4. Ver historial medico             ==\n";
        cout << "== 5. Listar todos los pacientes      ==\n";
        cout << "== 6. Volver al menu principal       ==\n";
        cout << "==============================================================================================================================\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20];
                int edad;
                char sexo;
                cout << "Nombre: "; cin.getline(nombre, 50);
                cout << "Apellido: "; cin.getline(apellido, 50);
                cout << "Cedula: "; cin.getline(cedula, 20);
                cout << "Edad: "; cin >> edad;
                cout << "Sexo (M/F): "; cin >> sexo;
                cin.ignore();
                crearPaciente(hospital, nombre, apellido, cedula, edad, sexo);
                break;
            }
            case 2: {
                char cedula[20];
                cout << "Cedula: "; cin.getline(cedula, 20);
                Paciente* p = buscarPacientePorCedula(hospital, cedula);
                if (p) {
                    cout << "Paciente encontrado: " << p->nombre << " " << p->apellido << "\n";
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
            }
            case 3: {
                char nombre[50];
                cout << "Nombre (parcial): "; cin.getline(nombre, 50);
                int cant;
                Paciente** res = buscarPacientesPorNombre(hospital, nombre, &cant);
                if (res) {
                    cout << "Resultados (" << cant << "):\n";
                    for (int i = 0; i < cant; i++) {
                        cout << "- " << res[i]->nombre << " " << res[i]->apellido << "\n";
                    }
                    delete[] res;
                } else {
                    cout << "No se encontraron pacientes.\n";
                }
                break;
            }
            case 4: {
                int id;
                cout << "ID del paciente: "; cin >> id;
                Paciente* p = buscarPacientePorId(hospital, id);
                if (p) {
                    mostrarHistorialMedico(p);
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
            }
            case 5:
                listarPacientes(hospital);
                break;
            case 6:
                break;
            default:
                cout << "OpciÃ³n invÃ¡lida.\n";
        }
    } while (opcion != 6);
}

void menuDoctores(Hospital* hospital) {
    int opcion;
    do {
        cout << "==============================================================================================================================\n";
        cout << "==         GESTION DE DOCTORES          ==\n";
        cout << "==============================================================================================================================\n";
        cout << "== 1. Registrar nuevo doctor            ==\n";
        cout << "== 2. Buscar por ID                     ==\n";
        cout << "== 3. Buscar por especialidad           ==\n";
        cout << "== 4. Listar todos los doctores         ==\n";
        cout << "== 5. Volver al menu principal         ==\n";
        cout << "==============================================================================================================================\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20], especialidad[50];
                int exp;
                float costo;
                cout << "Nombre: "; cin.getline(nombre, 50);
                cout << "Apellido: "; cin.getline(apellido, 50);
                cout << "Cedula profesional: "; cin.getline(cedula, 20);
                cout << "Especialidad: "; cin.getline(especialidad, 50);
                cout << "Anios de experiencia: "; cin >> exp;
                cout << "Costo de consulta: "; cin >> costo;
                cin.ignore();
                crearDoctor(hospital, nombre, apellido, cedula, especialidad, exp, costo);
                break;
            }
            case 2: {
                int id;
                cout << "ID: "; cin >> id;
                Doctor* d = buscarDoctorPorId(hospital, id);
                if (d) {
                    cout << "Doctor: " << d->nombre << " " << d->apellido << " - " << d->especialidad << "\n";
                } else {
                    cout << "Doctor no encontrado.\n";
                }
                break;
            }
            case 3: {
                char esp[50];
                cout << "Especialidad: "; cin.getline(esp, 50);
                int cant;
                Doctor** res = buscarDoctoresPorEspecialidad(hospital, esp, &cant);
                if (res) {
                    cout << "Doctores (" << cant << "):\n";
                    for (int i = 0; i < cant; i++) {
                        cout << "- " << res[i]->nombre << " " << res[i]->apellido << "\n";
                    }
                    delete[] res;
                } else {
                    cout << "No hay doctores en esa especialidad.\n";
                }
                break;
            }
            case 4:
                listarDoctores(hospital);
                break;
            case 5:
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 5);
}

void menuCitas(Hospital* hospital) {
    int opcion;
    do {
        cout << "\==============================================================================================================================\n";
        cout << "==           GESTION DE CITAS           ==\n";
        cout << "===============================================================================================================================\n";
        cout << "== 1. Agendar nueva cita                ==\n";
        cout << "== 2. Atender cita                      ==\n";
        cout << "== 3. Ver citas pendientes              ==\n";
        cout << "== 4. Volver al menu principal         ==\n";
        cout << "================================================================================================================================\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                int idP, idD;
                char fecha[11], hora[6], motivo[150];
                cout << "ID Paciente: "; cin >> idP;
                cout << "ID Doctor: "; cin >> idD;
                cout << "Fecha (YYYY-MM-DD): "; cin.getline(fecha, 11); // buffer
                cin.getline(fecha, 11);
                cout << "Hora (HH:MM): "; cin.getline(hora, 6);
                cout << "Motivo: "; cin.getline(motivo, 150);
                agendarCita(hospital, idP, idD, fecha, hora, motivo);
                break;
            }
            case 2: {
                int id;
                char diag[200], trat[200], meds[150];
                cout << "ID Cita: "; cin >> id;
                cout << "Diagnostico: "; cin.ignore(); cin.getline(diag, 200);
                cout << "Tratamiento: "; cin.getline(trat, 200);
                cout << "Medicamentos: "; cin.getline(meds, 150);
                atenderCita(hospital, id, diag, trat, meds);
                break;
            }
            case 3:
                listarCitasPendientes(hospital);
                break;
            case 4:
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
}


int main() {
    Hospital* hospital = inicializarHospital("Hospital Central");
    
    int opcion;
    do {
        cout << "========================================================================================================================\n";
        cout << "==   SISTEMA DE GESTION HOSPITALARIA     ==\n";
        cout << "======================================================================================================================\n";
        cout << "1. Gestion de Pacientes\n";
        cout << "2. Gestion de Doctores\n";
        cout << "3. Gestion de Citas\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: menuPacientes(hospital); break;
            case 2: menuDoctores(hospital); break;
            case 3: menuCitas(hospital); break;
            case 4: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 4);
    
    destruirHospital(hospital);
    return 0;
}