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
