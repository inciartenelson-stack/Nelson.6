#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
using namespace std;

// ======================================================================
// 1. DEFINICIÓN DE ESTRUCTURAS (según Requerimientos.md, Apéndice 11)
// ======================================================================

struct HistorialMedico {
    int idConsulta;
    char fecha[11];         // YYYY-MM-DD
    char hora[6];           // HH:MM
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
    char estado[20];        // "Agendada", "Atendida", "Cancelada"
    char observaciones[200];
    bool atendida;
    int consultaID;
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
    // Verifica que el origen no sea nulo
    if (!origen) return nullptr;
    
    // Calcula la longitud de la cadena (sin contar el terminador \0)
    size_t len = strlen(origen);
    
    // Reserva memoria exacta para la nueva cadena (+1 para \0)
    char* copia = new char[len + 1];
    
    // Copia la cadena usando strcpy
    strcpy(copia, origen);
    
    // Retorna el puntero a la nueva cadena
    return copia;
}


bool validarFecha(const char* fecha) {
    // Verifica que la fecha no sea nula y tenga exactamente 10 caracteres
    if (!fecha || strlen(fecha) != 10) return false;
    
    // Verifica que los separadores sean '-'
    if (fecha[4] != '-' || fecha[7] != '-') return false;
    
    // Verifica que todos los caracteres excepto los separadores sean dígitos
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (fecha[i] < '0' || fecha[i] > '9') return false;
    }
    
    // Extrae año, mes y día como enteros
    int anio = (fecha[0]-'0')*1000 + (fecha[1]-'0')*100 + (fecha[2]-'0')*10 + (fecha[3]-'0');
    int mes = (fecha[5]-'0')*10 + (fecha[6]-'0');
    int dia = (fecha[8]-'0')*10 + (fecha[9]-'0');
    
    // Valida mes (1-12)
    if (mes < 1 || mes > 12) return false;
    
    // Valida día (1-31)
    if (dia < 1 || dia > 31) return false;
    
    // Valida días por mes (abril, junio, septiembre, noviembre tienen 30 días)
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 30) return false;
    }
    
    // Valida febrero (28 o 29 días)
    if (mes == 2) {
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (esBisiesto) {
            if (dia > 29) return false;
        } else {
            if (dia > 28) return false;
        }
    }
    
    // Si pasa todas las validaciones, la fecha es válida
    return true;
}


bool validarHora(const char* hora) {
    // Verifica que la hora no sea nula y tenga exactamente 5 caracteres
    if (!hora || strlen(hora) != 5) return false;
    
    // Verifica que el separador sea ':'
    if (hora[2] != ':') return false;
    
    // Verifica que todos los caracteres excepto el separador sean dígitos
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (hora[i] < '0' || hora[i] > '9') return false;
    }
    
    // Extrae hora y minutos como enteros
    int h = (hora[0]-'0')*10 + (hora[1]-'0');
    int m = (hora[3]-'0')*10 + (hora[4]-'0');
    
    // Valida hora (0-23) y minutos (0-59)
    return (h >= 0 && h <= 23) && (m >= 0 && m <= 59);
}


int compararFechas(const char* fecha1, const char* fecha2) {
    // Extrae año, mes, día de ambas fechas
    int anio1, mes1, dia1, anio2, mes2, dia2;
    sscanf(fecha1, "%d-%d-%d", &anio1, &mes1, &dia1);
    sscanf(fecha2, "%d-%d-%d", &anio2, &mes2, &dia2);
    
    // Compara año
    if (anio1 < anio2) return -1;
    if (anio1 > anio2) return 1;
    
    // Compara mes
    if (mes1 < mes2) return -1;
    if (mes1 > mes2) return 1;
    
    // Compara día
    if (dia1 < dia2) return -1;
    if (dia1 > dia2) return 1;
    
    // Son iguales
    return 0;
}


bool validarCedula(const char* cedula) {
    // Verifica que no sea nula y tenga entre 1 y 20 caracteres
    return cedula && strlen(cedula) > 0 && strlen(cedula) <= 20;
}


bool validarEmail(const char* email) {
    // Verifica que no sea nulo
    if (!email) return false;
    
    // Verifica que contenga '@'
    if (!strchr(email, '@')) return false;
    
    // Verifica que contenga '.'
    if (!strchr(email, '.')) return false;
    
    // Verifica que '@' venga antes de '.'
    char* arroba = strchr(email, '@');
    char* punto = strchr(email, '.');
    if (arroba > punto) return false;
    
    return true;
}


Paciente* copiarPaciente(Paciente* original) {
    // Verifica que el original no sea nulo
    if (!original) return nullptr;
    
    // Crea un nuevo paciente en memoria dinámica
    Paciente* copia = new Paciente;
    
    // Copia todos los datos primitivos y arrays estáticos
    copia->id = original->id;
    strcpy(copia->nombre, original->nombre);
    strcpy(copia->apellido, original->apellido);
    strcpy(copia->cedula, original->cedula);
    copia->edad = original->edad;
    copia->sexo = original->sexo;
    strcpy(copia->tipoSangre, original->tipoSangre);
    strcpy(copia->telefono, original->telefono);
    strcpy(copia->direccion, original->direccion);
    strcpy(copia->email, original->email);
    strcpy(copia->alergias, original->alergias);
    strcpy(copia->observaciones, original->observaciones);
    copia->activo = original->activo;
    
    // Copia el array dinámico de historial
    copia->cantidadConsultas = original->cantidadConsultas;
    copia->capacidadHistorial = original->capacidadHistorial;
    if (original->historial) {
        copia->historial = new HistorialMedico[copia->capacidadHistorial];
        for (int i = 0; i < copia->cantidadConsultas; i++) {
            copia->historial[i] = original->historial[i];
        }
    } else {
        copia->historial = nullptr;
    }
    
    // Copia el array dinámico de citas agendadas
    copia->cantidadCitas = original->cantidadCitas;
    copia->capacidadCitas = original->capacidadCitas;
    if (original->citasAgendadas) {
        copia->citasAgendadas = new int[copia->capacidadCitas];
        for (int i = 0; i < copia->cantidadCitas; i++) {
            copia->citasAgendadas[i] = original->citasAgendadas[i];
        }
    } else {
        copia->citasAgendadas = nullptr;
    }
    
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
    return strstr(cad, sub) != nullptr;
}


Hospital* inicializarHospital(const char* nombre, int capacidadInicial = 10) {
    // Crea el hospital en memoria dinámica
    Hospital* h = new Hospital;
    
    // Copia el nombre del hospital
    strcpy(h->nombre, nombre);
    h->direccion[0] = '\0';
    h->telefono[0] = '\0';
    
    // Inicializa arrays de pacientes con capacidad inicial
    h->pacientes = new Paciente[capacidadInicial];
    h->capacidadPacientes = capacidadInicial;
    h->cantidadPacientes = 0;
    
    // Inicializa arrays de doctores con capacidad inicial
    h->doctores = new Doctor[capacidadInicial];
    h->capacidadDoctores = capacidadInicial;
    h->cantidadDoctores = 0;
    
    // Inicializa arrays de citas con capacidad doble (20)
    h->citas = new Cita[capacidadInicial * 2];
    h->capacidadCitas = capacidadInicial * 2;
    h->cantidadCitas = 0;
    
    // Inicializa contadores de IDs en 1
    h->siguienteIdPaciente = 1;
    h->siguienteIdDoctor = 1;
    h->siguienteIdCita = 1;
    h->siguienteIdConsulta = 1;
    
    return h;
}


void destruirHospital(Hospital* hospital) {
    // Verifica que el hospital no sea nulo
    if (!hospital) return;
    
    // Libera memoria de pacientes (primer nivel)
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        // Libera el historial médico de cada paciente (segundo nivel)
        delete[] hospital->pacientes[i].historial;
        // Libera las citas agendadas de cada paciente (segundo nivel)
        delete[] hospital->pacientes[i].citasAgendadas;
    }
    // Libera el array principal de pacientes
    delete[] hospital->pacientes;
    
    // Libera memoria de doctores (primer nivel)
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        // Libera los pacientes asignados de cada doctor (segundo nivel)
        delete[] hospital->doctores[i].pacientesAsignados;
        // Libera las citas agendadas de cada doctor (segundo nivel)
        delete[] hospital->doctores[i].citasAgendadas;
    }
    // Libera el array principal de doctores
    delete[] hospital->doctores;
    
    // Libera el array principal de citas
    delete[] hospital->citas;
    
    // Libera la estructura principal del hospital
    delete hospital;
}


void redimensionarArrayPacientes(Hospital* hospital) {
    // Calcula la nueva capacidad (doble de la actual)
    int nuevaCapacidad = hospital->capacidadPacientes * 2;
    
    // Crea un nuevo array con la nueva capacidad
    Paciente* nuevoArray = new Paciente[nuevaCapacidad];
    
    // Copia todos los pacientes existentes al nuevo array
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        nuevoArray[i] = hospital->pacientes[i];
    }
    
    // Libera la memoria del array antiguo
    delete[] hospital->pacientes;
    
    // Actualiza el puntero del hospital para que apunte al nuevo array
    hospital->pacientes = nuevoArray;
    
    // Actualiza la capacidad del array
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


Paciente* crearPaciente(Hospital* hospital, const char* nombre, 
                        const char* apellido, const char* cedula, 
                        int edad, char sexo) {
    // Validaciones de entrada
    if (!validarCedula(cedula)) {
        cout << "Error: Cédula inválida.\n";
        return nullptr;
    }
    if (edad < 0 || edad > 120) {
        cout << "Error: Edad debe estar entre 0 y 120.\n";
        return nullptr;
    }
    if (sexo != 'M' && sexo != 'F') {
        cout << "Error: Sexo debe ser 'M' o 'F'.\n";
        return nullptr;
    }
    
    // Verifica que la cédula no exista previamente (búsqueda case-insensitive)
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (strEqualsIgnoreCase(hospital->pacientes[i].cedula, cedula)) {
            cout << "Error: Cédula ya registrada.\n";
            return nullptr;
        }
    }
    
    // Redimensiona el array si está lleno
    if (hospital->cantidadPacientes >= hospital->capacidadPacientes) {
        redimensionarArrayPacientes(hospital);
    }
    
    // Crea el paciente en la siguiente posición disponible
    Paciente* p = &hospital->pacientes[hospital->cantidadPacientes];
    
    // Asigna ID único y datos básicos
    p->id = hospital->siguienteIdPaciente++;
    strcpy(p->nombre, nombre);
    strcpy(p->apellido, apellido);
    strcpy(p->cedula, cedula);
    p->edad = edad;
    p->sexo = sexo;
    p->tipoSangre[0] = '\0'; // Inicializa como cadena vacía
    p->telefono[0] = '\0';
    p->direccion[0] = '\0';
    p->email[0] = '\0';
    p->alergias[0] = '\0';
    p->observaciones[0] = '\0';
    p->activo = true;
    
    // Inicializa el array dinámico de historial médico
    p->historial = new HistorialMedico[5]; // Capacidad inicial = 5
    p->capacidadHistorial = 5;
    p->cantidadConsultas = 0;
    
    // Inicializa el array dinámico de citas agendadas
    p->citasAgendadas = new int[5]; // Capacidad inicial = 5
    p->capacidadCitas = 5;
    p->cantidadCitas = 0;
    
    // Incrementa el contador de pacientes
    hospital->cantidadPacientes++;
    
    return p;
}


Paciente* buscarPacientePorCedula(Hospital* hospital, const char* cedula) {
    // Recorre todos los pacientes registrados
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        // Compara cédulas sin importar mayúsculas/minúsculas
        if (strEqualsIgnoreCase(hospital->pacientes[i].cedula, cedula)) {
            return &hospital->pacientes[i];
        }
    }
    // Si no se encuentra, retorna nullptr
    return nullptr;
}



Paciente* buscarPacientePorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            return &hospital->pacientes[i];
        }
    }
    return nullptr;
}


Paciente** buscarPacientesPorNombre(Hospital* hospital, 
                                    const char* nombre, int* cantidad) {
    // Verifica que los parámetros no sean nulos
    if (!hospital || !nombre || !cantidad) {
        if (cantidad) *cantidad = 0;
        return nullptr;
    }
    
    // Paso 1: Contar cuántos pacientes coinciden con la búsqueda
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        // Crea el nombre completo del paciente
        char nombreCompleto[101];
        strcpy(nombreCompleto, hospital->pacientes[i].nombre);
        strcat(nombreCompleto, " ");
        strcat(nombreCompleto, hospital->pacientes[i].apellido);
        
        // Verifica si el nombre completo contiene la cadena de búsqueda
        if (contiene(nombreCompleto, nombre)) {
            (*cantidad)++;
        }
    }
    
    // Si no hay coincidencias, retorna nullptr
    if (*cantidad == 0) return nullptr;
    
    // Paso 2: Crear el array dinámico de punteros
    Paciente** resultados = new Paciente*[*cantidad];
    
    // Paso 3: Llenar el array con punteros a los pacientes encontrados
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


bool actualizarPaciente(Hospital* hospital, int id) {
    // Busca el paciente por ID
    Paciente* p = buscarPacientePorId(hospital, id);
    if (!p) {
        cout << "Error: Paciente no encontrado.\n";
        return false;
    }
    
    // Menú para actualizar campos específicos
    int opcion;
    cout << "\nActualizar datos de " << p->nombre << " " << p->apellido << ":\n";
    cout << "1. Teléfono\n2. Dirección\n3. Email\n4. Alergias\n5. Observaciones\nOpción: ";
    cin >> opcion;
    cin.ignore(); // Limpia el buffer
    
    char nuevoValor[500];
    switch (opcion) {
        case 1:
            cout << "Nuevo teléfono: "; cin.getline(nuevoValor, 15);
            strcpy(p->telefono, nuevoValor);
            break;
        case 2:
            cout << "Nueva dirección: "; cin.getline(nuevoValor, 100);
            strcpy(p->direccion, nuevoValor);
            break;
        case 3:
            cout << "Nuevo email: "; cin.getline(nuevoValor, 50);
            if (validarEmail(nuevoValor)) {
                strcpy(p->email, nuevoValor);
            } else {
                cout << "Email inválido.\n";
                return false;
            }
            break;
        case 4:
            cout << "Nuevas alergias: "; cin.getline(nuevoValor, 500);
            strcpy(p->alergias, nuevoValor);
            break;
        case 5:
            cout << "Nuevas observaciones: "; cin.getline(nuevoValor, 500);
            strcpy(p->observaciones, nuevoValor);
            break;
        default:
            cout << "Opción inválida.\n";
            return false;
    }
    
    cout << "Datos actualizados correctamente.\n";
    return true;
}


bool eliminarPaciente(Hospital* hospital, int id) {
    // Busca el paciente por ID
    int indice = -1;
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        if (hospital->pacientes[i].id == id) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        cout << "Error: Paciente no encontrado.\n";
        return false;
    }
    
    Paciente* p = &hospital->pacientes[indice];
    
    // Cancelar todas las citas del paciente
    for (int i = 0; i < p->cantidadCitas; i++) {
        int idCita = p->citasAgendadas[i];
        // Buscar la cita y marcarla como cancelada
        for (int j = 0; j < hospital->cantidadCitas; j++) {
            if (hospital->citas[j].id == idCita) {
                strcpy(hospital->citas[j].estado, "Cancelada");
                break;
            }
        }
    }
    
    //  Remover el paciente de las listas de doctores asignados
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        Doctor* d = &hospital->doctores[i];
        // Buscar el paciente en la lista del doctor
        for (int j = 0; j < d->cantidadPacientes; j++) {
            if (d->pacientesAsignados[j] == id) {
                // Compactar el array (mover elementos hacia adelante)
                for (int k = j; k < d->cantidadPacientes - 1; k++) {
                    d->pacientesAsignados[k] = d->pacientesAsignados[k + 1];
                }
                d->cantidadPacientes--;
                break;
            }
        }
    }
    
    //  Liberar la memoria del paciente
    delete[] p->historial;
    delete[] p->citasAgendadas;
    
    //  Compactar el array de pacientes (mover elementos hacia adelante)
    for (int i = indice; i < hospital->cantidadPacientes - 1; i++) {
        hospital->pacientes[i] = hospital->pacientes[i + 1];
    }
    
    // Decrementar el contador de pacientes
    hospital->cantidadPacientes--;
    
    cout << "Paciente eliminado correctamente.\n";
    return true;
}


void listarPacientes(Hospital* hospital) {
    if (hospital->cantidadPacientes == 0) {
        cout << "No hay pacientes registrados.\n";
        return;
    }
    
    // Encabezado del formato tabular
    cout << "\n+------------------------------------------------------------+\n";
    cout << "¦ ID  ¦ NOMBRE COMPLETO     ¦ CÉDULA       ¦ EDAD ¦ CONSULTAS¦\n";
    cout << "¦-----+---------------------+--------------+------+----------¦\n";
    
    // Lista cada paciente
    for (int i = 0; i < hospital->cantidadPacientes; i++) {
        Paciente* p = &hospital->pacientes[i];
        cout << "¦ " << setw(3) << p->id
             << " ¦ " << setw(19) << (string(p->nombre) + " " + p->apellido).c_str()
             << " ¦ " << setw(12) << p->cedula
             << " ¦ " << setw(4) << p->edad
             << " ¦ " << setw(8) << p->cantidadConsultas << " ¦\n";
    }
    
    // Pie de tabla
    cout << "+------------------------------------------------------------+\n";
}

// -------------------------------------------------------------------------
// 2.2.d obtenerUltimaConsulta: Retorna la última consulta del paciente
// Propósito: Acceder rápidamente a la consulta más reciente
// Parámetros: Paciente* paciente ? puntero al paciente
// Retorna: HistorialMedico* ? puntero a la última consulta, o nullptr si no hay
// -------------------------------------------------------------------------
HistorialMedico* obtenerUltimaConsulta(Paciente* paciente) {
    if (paciente->cantidadConsultas == 0) {
        return nullptr;
    }
    return &paciente->historial[paciente->cantidadConsultas - 1];
}

// ======================================================================
// 5. MÓDULO DE GESTIÓN DE DOCTORES (Módulo 3)
// ======================================================================

// -------------------------------------------------------------------------
// 3.1.a crearDoctor: Registra un nuevo doctor en el sistema
// Propósito: Agregar un doctor con validación de unicidad de cédula
// Parámetros: Hospital* hospital ? puntero al hospital
//             const char* nombre, apellido, cedula, especialidad ? datos personales
//             int aniosExperiencia ? años de experiencia
//             float costoConsulta ? costo de la consulta
// Retorna: Doctor* ? puntero al doctor creado, o nullptr si falla
// -------------------------------------------------------------------------
Doctor* crearDoctor(Hospital* hospital, const char* nombre, 
                    const char* apellido, const char* cedula,
                    const char* especialidad, int aniosExperiencia, 
                    float costoConsulta) {
    // Validaciones de entrada
    if (!validarCedula(cedula)) {
        cout << "Error: Cédula profesional inválida.\n";
        return nullptr;
    }
    if (aniosExperiencia < 0) {
        cout << "Error: Años de experiencia no pueden ser negativos.\n";
        return nullptr;
    }
    if (costoConsulta <= 0) {
        cout << "Error: El costo de consulta debe ser positivo.\n";
        return nullptr;
    }
    
    // Verifica que la cédula no exista previamente
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (strEqualsIgnoreCase(hospital->doctores[i].cedula, cedula)) {
            cout << "Error: Cédula profesional ya registrada.\n";
            return nullptr;
        }
    }
    
    // Redimensiona el array si está lleno
    if (hospital->cantidadDoctores >= hospital->capacidadDoctores) {
        redimensionarArrayDoctores(hospital);
    }
    
    // Crea el doctor en la siguiente posición disponible
    Doctor* d = &hospital->doctores[hospital->cantidadDoctores];
    
    // Asigna ID único y datos básicos
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
    
    // Inicializa el array dinámico de pacientes asignados
    d->pacientesAsignados = new int[5]; // Capacidad inicial = 5
    d->capacidadPacientes = 5;
    d->cantidadPacientes = 0;
    
    // Inicializa el array dinámico de citas agendadas
    d->citasAgendadas = new int[10]; // Capacidad inicial = 10
    d->capacidadCitas = 10;
    d->cantidadCitas = 0;
    
    // Incrementa el contador de doctores
    hospital->cantidadDoctores++;
    
    return d;
}

// -------------------------------------------------------------------------
// 3.1.b buscarDoctorPorId: Busca un doctor por su ID
// Propósito: Acceder rápidamente a un doctor por su identificador único
// Parámetros: Hospital* hospital ? puntero al hospital
//             int id ? ID del doctor a buscar
// Retorna: Doctor* ? puntero al doctor encontrado, o nullptr si no existe
// -------------------------------------------------------------------------
Doctor* buscarDoctorPorId(Hospital* hospital, int id) {
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id) {
            return &hospital->doctores[i];
        }
    }
    return nullptr;
}

// -------------------------------------------------------------------------
// 3.1.c buscarDoctoresPorEspecialidad: Busca doctores por especialidad
// Propósito: Implementar búsqueda por especialidad médica
// Parámetros: Hospital* hospital ? puntero al hospital
//             const char* especialidad ? especialidad a buscar
//             int* cantidad ? puntero para retornar la cantidad de resultados
// Retorna: Doctor** ? array dinámico de punteros a doctores encontrados
//         El usuario debe liberar este array (solo el array, no los doctores)
// -------------------------------------------------------------------------
Doctor** buscarDoctoresPorEspecialidad(Hospital* hospital, 
                                       const char* especialidad, 
                                       int* cantidad) {
    if (!hospital || !especialidad || !cantidad) {
        if (cantidad) *cantidad = 0;
        return nullptr;
    }
    
    // Paso 1: Contar coincidencias
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (strEqualsIgnoreCase(hospital->doctores[i].especialidad, especialidad)) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    // Paso 2: Crear array dinámico
    Doctor** resultados = new Doctor*[*cantidad];
    
    // Paso 3: Llenar array
    int idx = 0;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (strEqualsIgnoreCase(hospital->doctores[i].especialidad, especialidad)) {
            resultados[idx++] = &hospital->doctores[i];
        }
    }
    
    return resultados;
}

// -------------------------------------------------------------------------
// 3.1.d asignarPacienteADoctor: Asigna un paciente a un doctor
// Propósito: Establecer relación entre paciente y doctor
// Parámetros: Doctor* doctor ? puntero al doctor
//             int idPaciente ? ID del paciente a asignar
// Retorna: bool ? true si se asignó correctamente, false en caso contrario
// -------------------------------------------------------------------------
bool asignarPacienteADoctor(Doctor* doctor, int idPaciente) {
    // Verifica que el paciente no esté ya asignado (evitar duplicados)
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        if (doctor->pacientesAsignados[i] == idPaciente) {
            return false; // Ya está asignado
        }
    }
    
    // Redimensiona el array si está lleno
    if (doctor->cantidadPacientes >= doctor->capacidadPacientes) {
        int nuevaCapacidad = doctor->capacidadPacientes * 2;
        int* nuevo = new int[nuevaCapacidad];
        for (int i = 0; i < doctor->cantidadPacientes; i++) {
            nuevo[i] = doctor->pacientesAsignados[i];
        }
        delete[] doctor->pacientesAsignados;
        doctor->pacientesAsignados = nuevo;
        doctor->capacidadPacientes = nuevaCapacidad;
    }
    
    // Agrega el ID del paciente al array
    doctor->pacientesAsignados[doctor->cantidadPacientes] = idPaciente;
    
    // Incrementa el contador
    doctor->cantidadPacientes++;
    
    return true;
}

// -------------------------------------------------------------------------
// 3.1.e removerPacienteDeDoctor: Remueve un paciente de un doctor
// Propósito: Eliminar relación entre paciente y doctor
// Parámetros: Doctor* doctor ? puntero al doctor
//             int idPaciente ? ID del paciente a remover
// Retorna: bool ? true si se removió correctamente, false en caso contrario
// -------------------------------------------------------------------------
bool removerPacienteDeDoctor(Doctor* doctor, int idPaciente) {
    // Busca el ID del paciente en el array
    int indice = -1;
    for (int i = 0; i < doctor->cantidadPacientes; i++) {
        if (doctor->pacientesAsignados[i] == idPaciente) {
            indice = i;
            break;
        }
    }
    if (indice == -1) return false; // No encontrado
    
    // Compacta el array (mover elementos hacia adelante)
    for (int i = indice; i < doctor->cantidadPacientes - 1; i++) {
        doctor->pacientesAsignados[i] = doctor->pacientesAsignados[i + 1];
    }
    
    // Decrementa el contador
    doctor->cantidadPacientes--;
    
    return true;
}

// -------------------------------------------------------------------------
// 3.1.f listarPacientesDeDoctor: Muestra los pacientes de un doctor
// Propósito: Presentar información de los pacientes asignados a un doctor
// Parámetros: Hospital* hospital ? puntero al hospital
//             int idDoctor ? ID del doctor
// Retorna: void
// -------------------------------------------------------------------------
void listarPacientesDeDoctor(Hospital* hospital, int idDoctor) {
    Doctor* d = buscarDoctorPorId(hospital, idDoctor);
    if (!d) {
        cout << "Doctor no encontrado.\n";
        return;
    }
    
    if (d->cantidadPacientes == 0) {
        cout << "No hay pacientes asignados.\n";
        return;
    }
    
    // Encabezado
    cout << "\n+-------------------------------------------------+\n";
    cout << "¦ ID  ¦ NOMBRE COMPLETO     ¦ CÉDULA       ¦ EDAD ¦\n";
    cout << "¦-----+---------------------+--------------+------¦\n";
    
    // Lista cada paciente asignado
    for (int i = 0; i < d->cantidadPacientes; i++) {
        int idPaciente = d->pacientesAsignados[i];
        Paciente* p = buscarPacientePorId(hospital, idPaciente);
        if (p) {
            cout << "¦ " << setw(3) << p->id
                 << " ¦ " << setw(19) << (string(p->nombre) + " " + p->apellido).c_str()
                 << " ¦ " << setw(12) << p->cedula
                 << " ¦ " << setw(4) << p->edad << " ¦\n";
        }
    }
    
    // Pie de tabla
    cout << "+-------------------------------------------------+\n";
}

// -------------------------------------------------------------------------
// 3.1.g listarDoctores: Muestra todos los doctores en formato tabular
// Propósito: Presentar información clave de todos los doctores registrados
// Parámetros: Hospital* hospital ? puntero al hospital
// Retorna: void
// -------------------------------------------------------------------------
void listarDoctores(Hospital* hospital) {
    if (hospital->cantidadDoctores == 0) {
        cout << "No hay doctores registrados.\n";
        return;
    }
    
    // Encabezado
    cout << "\n+-------------------------------------------------------------------+\n";
    cout << "¦ ID  ¦ NOMBRE COMPLETO     ¦ ESPECIALIDAD       ¦ COSTO CONSULTA   ¦\n";
    cout << "¦-----+---------------------+--------------------+------------------¦\n";
    
    // Lista cada doctor
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        Doctor* d = &hospital->doctores[i];
        cout << "¦ " << setw(3) << d->id
             << " ¦ " << setw(19) << (string(d->nombre) + " " + d->apellido).c_str()
             << " ¦ " << setw(18) << d->especialidad
             << " ¦ $" << setw(14) << fixed << setprecision(2) << d->costoConsulta << " ¦\n";
    }
    
    // Pie de tabla
    cout << "+-------------------------------------------------------------------+\n";
}

// -------------------------------------------------------------------------
// 3.1.h eliminarDoctor: Elimina un doctor del sistema
// Propósito: Liberar toda la memoria asociada y mantener la integridad del sistema
// Parámetros: Hospital* hospital ? puntero al hospital
//             int id ? ID del doctor a eliminar
// Retorna: bool ? true si se eliminó correctamente, false en caso contrario
// -------------------------------------------------------------------------
bool eliminarDoctor(Hospital* hospital, int id) {
    // Busca el doctor por ID
    int indice = -1;
    for (int i = 0; i < hospital->cantidadDoctores; i++) {
        if (hospital->doctores[i].id == id) {
            indice = i;
            break;
        }
    }
    if (indice == -1) {
        cout << "Error: Doctor no encontrado.\n";
        return false;
    }
    
    Doctor* d = &hospital->doctores[indice];
    
    // Paso 1: Cancelar todas las citas del doctor
    for (int i = 0; i < d->cantidadCitas; i++) {
        int idCita = d->citasAgendadas[i];
        // Buscar la cita y marcarla como cancelada
        for (int j = 0; j < hospital->cantidadCitas; j++) {
            if (hospital->citas[j].id == idCita) {
                strcpy(hospital->citas[j].estado, "Cancelada");
                break;
            }
        }
    }
    
    // Paso 2: Liberar la memoria del doctor
    delete[] d->pacientesAsignados;
    delete[] d->citasAgendadas;
    
    // Paso 3: Compactar el array de doctores
    for (int i = indice; i < hospital->cantidadDoctores - 1; i++) {
        hospital->doctores[i] = hospital->doctores[i + 1];
    }
    
    // Paso 4: Decrementar el contador de doctores
    hospital->cantidadDoctores--;
    
    cout << "Doctor eliminado correctamente.\n";
    return true;
}

// ======================================================================
// 6. MÓDULO DE GESTIÓN DE CITAS (Módulo 4)
// ======================================================================

// -------------------------------------------------------------------------
// 5.2.c verificarDisponibilidad: Verifica si un doctor está disponible
// Propósito: Evitar conflictos de horario al agendar citas
// Parámetros: Hospital* hospital ? puntero al hospital
//             int idDoctor ? ID del doctor
//             const char* fecha, hora ? fecha y hora a verificar
// Retorna: bool ? true si está disponible, false en caso contrario
// -------------------------------------------------------------------------
bool verificarDisponibilidad(Hospital* hospital, int idDoctor,
                             const char* fecha, const char* hora) {
    // Recorre todas las citas registradas
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita* c = &hospital->citas[i];
        // Verifica si es del mismo doctor, fecha y hora, y está agendada
        if (c->idDoctor == idDoctor && 
            strcmp(c->fecha, fecha) == 0 && 
            strcmp(c->hora, hora) == 0 &&
            strcmp(c->estado, "Agendada") == 0) {
            return false; // No disponible
        }
    }
    return true; // Disponible
}

// -------------------------------------------------------------------------
// 4.1.a agendarCita: Registra una nueva cita médica
// Propósito: Crear una cita con validación de disponibilidad
// Parámetros: Hospital* hospital ? puntero al hospital
//             int idPaciente, idDoctor ? IDs del paciente y doctor
//             const char* fecha, hora, motivo ? detalles de la cita
// Retorna: Cita* ? puntero a la cita creada, o nullptr si falla
// -------------------------------------------------------------------------
Cita* agendarCita(Hospital* hospital, int idPaciente, int idDoctor,
                  const char* fecha, const char* hora, const char* motivo) {
    // Verifica que el paciente y doctor existan
    Paciente* p = buscarPacientePorId(hospital, idPaciente);
    Doctor* d = buscarDoctorPorId(hospital, idDoctor);
    if (!p || !d) {
        cout << "Error: Paciente o doctor no encontrado.\n";
        return nullptr;
    }
    
    // Valida formato de fecha y hora
    if (!validarFecha(fecha) || !validarHora(hora)) {
        cout << "Error: Fecha u hora inválida.\n";
        return nullptr;
    }
    
    // Verifica disponibilidad del doctor
    if (!verificarDisponibilidad(hospital, idDoctor, fecha, hora)) {
        cout << "Error: El doctor no está disponible en esa fecha/hora.\n";
        return nullptr;
    }
    
    // Redimensiona el array si está lleno
    if (hospital->cantidadCitas >= hospital->capacidadCitas) {
        redimensionarArrayCitas(hospital);
    }
    
    // Crea la cita en la siguiente posición disponible
    Cita* c = &hospital->citas[hospital->cantidadCitas];
    
    // Asigna ID único y datos básicos
    c->id = hospital->siguienteIdCita++;
    c->idPaciente = idPaciente;
    c->idDoctor = idDoctor;
    strcpy(c->fecha, fecha);
    strcpy(c->hora, hora);
    strcpy(c->motivo, motivo);
    strcpy(c->estado, "Agendada");
    c->observaciones[0] = '\0';
    c->atendida = false;
    
    // Agrega el ID de la cita al array del paciente
    if (p->cantidadCitas >= p->capacidadCitas) {
        int nuevaCap = p->capacidadCitas * 2;
        int* nuevo = new int[nuevaCap];
        for (int i = 0; i < p->cantidadCitas; i++) {
            nuevo[i] = p->citasAgendadas[i];
        }
        delete[] p->citasAgendadas;
        p->citasAgendadas = nuevo;
        p->capacidadCitas = nuevaCap;
    }
    p->citasAgendadas[p->cantidadCitas] = c->id;
    p->cantidadCitas++;
    
    // Agrega el ID de la cita al array del doctor
    if (d->cantidadCitas >= d->capacidadCitas) {
        int nuevaCap = d->capacidadCitas * 2;
        int* nuevo = new int[nuevaCap];
        for (int i = 0; i < d->cantidadCitas; i++) {
            nuevo[i] = d->citasAgendadas[i];
        }
        delete[] d->citasAgendadas;
        d->citasAgendadas = nuevo;
        d->capacidadCitas = nuevaCap;
    }
    d->citasAgendadas[d->cantidadCitas] = c->id;
    d->cantidadCitas++;
    
    // Incrementa el contador de citas
    hospital->cantidadCitas++;
    
    return c;
}

// -------------------------------------------------------------------------
// 4.1.b cancelarCita: Cancela una cita existente
// Propósito: Cambiar el estado de una cita a "Cancelada"
// Parámetros: Hospital* hospital ? puntero al hospital
//             int idCita ? ID de la cita a cancelar
// Retorna: bool ? true si se canceló correctamente, false en caso contrario
// -------------------------------------------------------------------------
bool cancelarCita(Hospital* hospital, int idCita) {
    // Busca la cita por ID
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].id == idCita) {
            // Verifica que no esté ya cancelada o atendida
            if (strcmp(hospital->citas[i].estado, "Agendada") == 0) {
                strcpy(hospital->citas[i].estado, "Cancelada");
                return true;
            } else {
                cout << "Error: La cita ya fue atendida o cancelada.\n";
                return false;
            }
        }
    }
    cout << "Error: Cita no encontrada.\n";
    return false;
}

// -------------------------------------------------------------------------
// 4.1.c atenderCita: Atiende una cita y crea entrada en historial médico
// Propósito: Completar el ciclo de una cita y generar registro clínico
// Parámetros: Hospital* hospital ? puntero al hospital
//             int idCita ? ID de la cita a atender
//             const char* diagnostico, tratamiento, medicamentos ? datos clínicos
// Retorna: bool ? true si se atendió correctamente, false en caso contrario
// -------------------------------------------------------------------------
bool atenderCita(Hospital* hospital, int idCita, const char* diagnostico,
                 const char* tratamiento, const char* medicamentos) {
    // Busca la cita por ID
    Cita* c = nullptr;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].id == idCita) {
            c = &hospital->citas[i];
            break;
        }
    }
    if (!c) {
        cout << "Error: Cita no encontrada.\n";
        return false;
    }
    
    // Verifica que esté en estado "Agendada"
    if (strcmp(c->estado, "Agendada") != 0) {
        cout << "Error: La cita ya fue atendida o cancelada.\n";
        return false;
    }
    
    // Obtiene datos del paciente y doctor
    Paciente* p = buscarPacientePorId(hospital, c->idPaciente);
    Doctor* d = buscarDoctorPorId(hospital, c->idDoctor);
    if (!p || !d) {
        cout << "Error: Paciente o doctor no encontrado.\n";
        return false;
    }
    
    // Crea la estructura de historial médico
    HistorialMedico hist;
    hist.idConsulta = hospital->siguienteIdConsulta++;
    strcpy(hist.fecha, c->fecha);
    strcpy(hist.hora, c->hora);
    strcpy(hist.diagnostico, diagnostico);
    strcpy(hist.tratamiento, tratamiento);
    strcpy(hist.medicamentos, medicamentos);
    hist.idDoctor = d->id;
    hist.costo = d->costoConsulta;
    
    // Agrega la consulta al historial del paciente
    agregarConsultaAlHistorial(p, hist);
    
    // Asigna el paciente al doctor si no está asignado
    asignarPacienteADoctor(d, p->id);
    
    // Actualiza el estado de la cita
    strcpy(c->estado, "Atendida");
    c->atendida = true;
    c->consultaID = hist.idConsulta; // Campo adicional para referencia
    
    cout << "Cita atendida correctamente. ID de consulta: " << hist.idConsulta << "\n";
    return true;
}

// -------------------------------------------------------------------------
// 4.1.d obtenerCitasDePaciente: Retorna las citas de un paciente
// Propósito: Proporcionar acceso a las citas de un paciente específico
// Parámetros: Hospital* hospital ? puntero al hospital
//             int idPaciente ? ID del paciente
//             int* cantidad ? puntero para retornar la cantidad de citas
// Retorna: Cita** ? array dinámico de punteros a citas
//         El usuario debe liberar este array (solo el array, no las citas)
// -------------------------------------------------------------------------
Cita** obtenerCitasDePaciente(Hospital* hospital, int idPaciente, int* cantidad) {
    if (!hospital || !cantidad) {
        if (cantidad) *cantidad = 0;
        return nullptr;
    }
    
    // Contar citas del paciente
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == idPaciente) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    // Crear array dinámico
    Cita** resultados = new Cita*[*cantidad];
    
    // Llenar array
    int idx = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idPaciente == idPaciente) {
            resultados[idx++] = &hospital->citas[i];
        }
    }
    
    return resultados;
}

// -------------------------------------------------------------------------
// 4.1.e obtenerCitasDeDoctor: Retorna las citas de un doctor
// Propósito: Proporcionar acceso a las citas de un doctor específico
// Parámetros: Hospital* hospital ? puntero al hospital
//             int idDoctor ? ID del doctor
//             int* cantidad ? puntero para retornar la cantidad de citas
// Retorna: Cita** ? array dinámico de punteros a citas
//         El usuario debe liberar este array (solo el array, no las citas)
// -------------------------------------------------------------------------
Cita** obtenerCitasDeDoctor(Hospital* hospital, int idDoctor, int* cantidad) {
    if (!hospital || !cantidad) {
        if (cantidad) *cantidad = 0;
        return nullptr;
    }
    
    // Contar citas del doctor
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    // Crear array dinámico
    Cita** resultados = new Cita*[*cantidad];
    
    // Llenar array
    int idx = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (hospital->citas[i].idDoctor == idDoctor) {
            resultados[idx++] = &hospital->citas[i];
        }
    }
    
    return resultados;
}

// -------------------------------------------------------------------------
// 4.1.f obtenerCitasPorFecha: Retorna las citas de una fecha específica
// Propósito: Proporcionar acceso a las citas de una fecha determinada
// Parámetros: Hospital* hospital ? puntero al hospital
//             const char* fecha ? fecha a buscar
//             int* cantidad ? puntero para retornar la cantidad de citas
// Retorna: Cita** ? array dinámico de punteros a citas
//         El usuario debe liberar este array (solo el array, no las citas)
// -------------------------------------------------------------------------
Cita** obtenerCitasPorFecha(Hospital* hospital, const char* fecha, int* cantidad) {
    if (!hospital || !fecha || !cantidad) {
        if (cantidad) *cantidad = 0;
        return nullptr;
    }
    
    // Contar citas de la fecha
    *cantidad = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].fecha, fecha) == 0) {
            (*cantidad)++;
        }
    }
    
    if (*cantidad == 0) return nullptr;
    
    // Crear array dinámico
    Cita** resultados = new Cita*[*cantidad];
    
    // Llenar array
    int idx = 0;
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        if (strcmp(hospital->citas[i].fecha, fecha) == 0) {
            resultados[idx++] = &hospital->citas[i];
        }
    }
    
    return resultados;
}

// -------------------------------------------------------------------------
// 4.1.g listarCitasPendientes: Muestra citas con estado "Agendada"
// Propósito: Presentar citas pendientes de atención
// Parámetros: Hospital* hospital ? puntero al hospital
// Retorna: void
// -------------------------------------------------------------------------
void listarCitasPendientes(Hospital* hospital) {
    bool hay = false;
    cout << "\n+-------------------------------------------------------------------------------+\n";
    cout << "¦ ID  ¦ PACIENTE     ¦ DOCTOR     ¦ FECHA      ¦ MOTIVO                           ¦\n";
    cout << "¦-----+--------------+------------+------------+----------------------------------¦\n";
    for (int i = 0; i < hospital->cantidadCitas; i++) {
        Cita* c = &hospital->citas[i];
        if (strcmp(c->estado, "Agendada") == 0) {
            hay = true;
            Paciente* p = buscarPacientePorId(hospital, c->idPaciente);
            Doctor* d = buscarDoctorPorId(hospital, c->idDoctor);
            cout << "¦ " << setw(3) << c->id
                 << " ¦ " << setw(12) << (p ? p->nombre : "???")
                 << " ¦ " << setw(10) << (d ? d->nombre : "???")
                 << " ¦ " << setw(10) << c->fecha
                 << " ¦ " << setw(32) << c->motivo << " ¦\n";
        }
    }
    if (!hay) cout << "¦                        No hay citas pendientes.                              ¦\n";
    cout << "+---------------------------------------------------------------------------------+\n";
}

// ======================================================================
// 7. INTERFAZ DE USUARIO (Módulo 6)
// ======================================================================

// -------------------------------------------------------------------------
// Menú de Pacientes (Módulo 6.2)
// -------------------------------------------------------------------------
void menuPacientes(Hospital* hospital) {
    int opcion;
    do {
        cout << "\n+----------------------------------------+\n";
        cout << "¦         GESTIÓN DE PACIENTES           ¦\n";
        cout << "¦----------------------------------------¦\n";
        cout << "¦ 1. Registrar nuevo paciente            ¦\n";
        cout << "¦ 2. Buscar por cédula                   ¦\n";
        cout << "¦ 3. Buscar por nombre                   ¦\n";
        cout << "¦ 4. Ver historial médico                ¦\n";
        cout << "¦ 5. Actualizar datos del paciente       ¦\n";
        cout << "¦ 6. Listar todos los pacientes          ¦\n";
        cout << "¦ 7. Eliminar paciente                   ¦\n";
        cout << "¦ 8. Volver al menú principal            ¦\n";
        cout << "+----------------------------------------+\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20];
                int edad;
                char sexo;
                cout << "Nombre: "; cin.getline(nombre, 50);
                cout << "Apellido: "; cin.getline(apellido, 50);
                cout << "Cédula: "; cin.getline(cedula, 20);
                cout << "Edad: "; cin >> edad;
                cout << "Sexo (M/F): "; cin >> sexo;
                cin.ignore();
                crearPaciente(hospital, nombre, apellido, cedula, edad, sexo);
                break;
            }
            case 2: {
                char cedula[20];
                cout << "Cédula: "; cin.getline(cedula, 20);
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
                    delete[] res; // Libera el array de punteros
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
            case 5: {
                int id;
                cout << "ID del paciente: "; cin >> id;
                actualizarPaciente(hospital, id);
                break;
            }
            case 6:
                listarPacientes(hospital);
                break;
            case 7: {
                int id;
                cout << "ID del paciente: "; cin >> id;
                eliminarPaciente(hospital, id);
                break;
            }
            case 8:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 8);
}

// -------------------------------------------------------------------------
// Menú de Doctores (Módulo 6.2)
// -------------------------------------------------------------------------
void menuDoctores(Hospital* hospital) {
    int opcion;
    do {
        cout << "\n+----------------------------------------+\n";
        cout << "¦         GESTIÓN DE DOCTORES            ¦\n";
        cout << "¦----------------------------------------¦\n";
        cout << "¦ 1. Registrar nuevo doctor              ¦\n";
        cout << "¦ 2. Buscar doctor por ID                ¦\n";
        cout << "¦ 3. Buscar por especialidad             ¦\n";
        cout << "¦ 4. Asignar paciente a doctor           ¦\n";
        cout << "¦ 5. Ver pacientes asignados             ¦\n";
        cout << "¦ 6. Listar todos los doctores           ¦\n";
        cout << "¦ 7. Eliminar doctor                     ¦\n";
        cout << "¦ 8. Volver al menú principal            ¦\n";
        cout << "+----------------------------------------+\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                char nombre[50], apellido[50], cedula[20], especialidad[50];
                int exp;
                float costo;
                cout << "Nombre: "; cin.getline(nombre, 50);
                cout << "Apellido: "; cin.getline(apellido, 50);
                cout << "Cédula profesional: "; cin.getline(cedula, 20);
                cout << "Especialidad: "; cin.getline(especialidad, 50);
                cout << "Años de experiencia: "; cin >> exp;
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
                    delete[] res; // Libera el array de punteros
                } else {
                    cout << "No hay doctores en esa especialidad.\n";
                }
                break;
            }
            case 4: {
                int idDoc, idPac;
                cout << "ID Doctor: "; cin >> idDoc;
                cout << "ID Paciente: "; cin >> idPac;
                Doctor* d = buscarDoctorPorId(hospital, idDoc);
                if (d) {
                    if (asignarPacienteADoctor(d, idPac)) {
                        cout << "Paciente asignado correctamente.\n";
                    } else {
                        cout << "Error: Paciente ya asignado o no encontrado.\n";
                    }
                } else {
                    cout << "Doctor no encontrado.\n";
                }
                break;
            }
            case 5: {
                int id;
                cout << "ID Doctor: "; cin >> id;
                listarPacientesDeDoctor(hospital, id);
                break;
            }
            case 6:
                listarDoctores(hospital);
                break;
            case 7: {
                int id;
                cout << "ID del doctor: "; cin >> id;
                eliminarDoctor(hospital, id);
                break;
            }
            case 8:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 8);
}

// -------------------------------------------------------------------------
// Menú de Citas (Módulo 6.2)
// -------------------------------------------------------------------------
void menuCitas(Hospital* hospital) {
    int opcion;
    do {
        cout << "\n+----------------------------------------+\n";
        cout << "¦           GESTIÓN DE CITAS             ¦\n";
        cout << "¦----------------------------------------¦\n";
        cout << "¦ 1. Agendar nueva cita                  ¦\n";
        cout << "¦ 2. Cancelar cita                       ¦\n";
        cout << "¦ 3. Atender cita                        ¦\n";
        cout << "¦ 4. Ver citas de un paciente            ¦\n";
        cout << "¦ 5. Ver citas de un doctor              ¦\n";
        cout << "¦ 6. Ver citas de una fecha              ¦\n";
        cout << "¦ 7. Ver citas pendientes                ¦\n";
        cout << "¦ 8. Volver al menú principal            ¦\n";
        cout << "+----------------------------------------+\n";
        cout << "Opción: ";
        cin >> opcion;
        cin.ignore();
        
        switch (opcion) {
            case 1: {
                int idP, idD;
                char fecha[11], hora[6], motivo[150];
                cout << "ID Paciente: "; cin >> idP;
                cout << "ID Doctor: "; cin >> idD;
                cout << "Fecha (YYYY-MM-DD): "; cin.ignore(); cin.getline(fecha, 11);
                cout << "Hora (HH:MM): "; cin.getline(hora, 6);
                cout << "Motivo: "; cin.getline(motivo, 150);
                agendarCita(hospital, idP, idD, fecha, hora, motivo);
                break;
            }
            case 2: {
                int id;
                cout << "ID Cita: "; cin >> id;
                cancelarCita(hospital, id);
                break;
            }
            case 3: {
                int id;
                char diag[200], trat[200], meds[150];
                cout << "ID Cita: "; cin >> id;
                cout << "Diagnóstico: "; cin.ignore(); cin.getline(diag, 200);
                cout << "Tratamiento: "; cin.getline(trat, 200);
                cout << "Medicamentos: "; cin.getline(meds, 150);
                atenderCita(hospital, id, diag, trat, meds);
                break;
            }
            case 4: {
                int id;
                cout << "ID Paciente: "; cin >> id;
                int cant;
                Cita** citas = obtenerCitasDePaciente(hospital, id, &cant);
                if (citas) {
                    cout << "Citas del paciente (" << cant << "):\n";
                    for (int i = 0; i < cant; i++) {
                        cout << "- " << citas[i]->fecha << " " << citas[i]->hora 
                             << " con Dr. " << citas[i]->idDoctor << "\n";
                    }
                    delete[] citas;
                } else {
                    cout << "No hay citas para este paciente.\n";
                }
                break;
            }
            case 5: {
                int id;
                cout << "ID Doctor: "; cin >> id;
                int cant;
                Cita** citas = obtenerCitasDeDoctor(hospital, id, &cant);
                if (citas) {
                    cout << "Citas del doctor (" << cant << "):\n";
                    for (int i = 0; i < cant; i++) {
                        cout << "- " << citas[i]->fecha << " " << citas[i]->hora 
                             << " Paciente ID: " << citas[i]->idPaciente << "\n";
                    }
                    delete[] citas;
                } else {
                    cout << "No hay citas para este doctor.\n";
                }
                break;
            }
            case 6: {
                char fecha[11];
                cout << "Fecha (YYYY-MM-DD): "; cin.getline(fecha, 11);
                int cant;
                Cita** citas = obtenerCitasPorFecha(hospital, fecha, &cant);
                if (citas) {
                    cout << "Citas del día (" << cant << "):\n";
                    for (int i = 0; i < cant; i++) {
                        cout << "- " << citas[i]->hora << " Paciente ID: " << citas[i]->idPaciente 
                             << " Doctor ID: " << citas[i]->idDoctor << "\n";
                    }
                    delete[] citas;
                } else {
                    cout << "No hay citas en esa fecha.\n";
                }
                break;
            }
            case 7:
                listarCitasPendientes(hospital);
                break;
            case 8:
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 8);
}

// ======================================================================
// 8. FUNCIÓN PRINCIPAL (MAIN)
// ======================================================================

int main() {
    // Inicializa el sistema con el nombre del hospital
    Hospital* hospital = inicializarHospital("Hospital Central Urdaneta");
    
    int opcion;
    do {
        cout << "\n+----------------------------------------+\n";
        cout << "¦   SISTEMA DE GESTIÓN HOSPITALARIA     ¦\n";
        cout << "+----------------------------------------+\n";
        cout << "1. Gestión de Pacientes\n";
        cout << "2. Gestión de Doctores\n";
        cout << "3. Gestión de Citas\n";
        cout << "4. Salir\n";
        cout << "Opción: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1: menuPacientes(hospital); break;
            case 2: menuDoctores(hospital); break;
            case 3: menuCitas(hospital); break;
            case 4: cout << "Saliendo del sistema...\n"; break;
            default: cout << "Opción inválida.\n";
        }
    } while (opcion != 4);
    
    // Realiza cleanup completo al salir
    destruirHospital(hospital);
    
    return 0;
}
