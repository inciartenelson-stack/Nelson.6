#include <iostream>
#include <cstring>
#include <ctime>
#include <iosmanip>
using namespace std;

paciente* pacientes = new Paciente[tamanio_pacientes];
doctor* doctores = new Doctor[tamanio_doctores];
cita* cita = new Cita[tamanio_citas];
HistorialMedico* historial = new HistorialMedico[tamanio_historial];

struct Hospital {
    char nombre_hospital[100];
    char direccion[150];
    char telefono[15];
    
    paciente* pacientes;
    int cantidad_Pacientes;
    int capacidad_Pacientes_total;
    
    Doctor* doctores;
    int cantidad_Doctoresr;
    int capacidad_tDoctores;
    
    Cita* citas;
    int cantidad_citasr;
    int capacidad_citastotal; 
    
    int siguienteIdPaciente;
    int siguienteIdDoctor;
    int siguienteIdCita;
    int siguienteIdConsulta;
};

struct Paciente {
    int id_paciente;
    char nombre_paciente[50];
    char apellido_paciente[50];
    char cedula_paciente[20];
    int edad_paciente;
    char sexo_paciente[10];
    char tipo_sangre[5];
    char telefono_Ppaciente[15];
    char direccion_casa[100];
    char email[50];
    
    HistorialMedico* historial;
    int cantidad_Consultas;
    int capacidad_HistorialTotal;
    
    int* citas_agendadas;
    int cantidad_citas;
    int capacidad_citas;
    
    char alergias[500];
    char observaciones[500];
    
    bool activo;
};

struct HistorialMedico {
    int id_Consulta;
    char fechad_consuta[11];
    char horad_consulta[6];
    char diagnostico_paciente[200];
    char tratamiento_designado[200];
    char medicamentos_asignados[150];
    int id_Doctor;
    float costo_total;
};

struct Doctor {
    int id;
    char nombre_doctor[50];
    char apellido_doctor[50];
    char cedula_doctor[20];
    char especialidad_doctor[50];
    int anios_experiencia;
    float costo_consulta;
    char horario_atencion[50];
    char telefono_doctor[15];
    char email_doctorP[50];
    
    int* pacientes_asignadosD;
    int cantidad_pacientesD;
    int capacidad_pacientesD;
    
    int* citas_agendadas;
    int cantidadd_citas;
    int capacidad_citas;
    
    bool disponible;
};

struct Cita {
    int id_cita;
    Paciente* pacientes;
    Doctor* doctores;
   char fecahd_consulta[11];
   char horad_consulta[6];
   char motivo[150];
   char estado_cita[20];
   char observacionesd_lacita[200];
   bool cita_terminada;
};

*Paciente agregar_paciente(Hospital* hospital, const char* nombre, const char* apellido, const char* cedula, int edad, const char* sexo, const char* tipo_sangre, const char* telefono, const char* direccion, const char* email) {
    if (hospital->cantidad_Pacientes >= hospital->capacidad_Pacientes_total) {
        cout << "Capacidad de pacientes alcanzada." << endl;
        return nullptr;
    }
    
    Paciente nuevo_paciente;
    nuevo_paciente.id_paciente = hospital->siguienteIdPaciente++;
    strncpy(nuevo_paciente.nombre_paciente, nombre, sizeof(nuevo_paciente.nombre_paciente));
    strncpy(nuevo_paciente.apellido_paciente, apellido, sizeof(nuevo_paciente.apellido_paciente));
    strncpy(nuevo_paciente.cedula_paciente, cedula, sizeof(nuevo_paciente.cedula_paciente));
    nuevo_paciente.edad_paciente = edad;
    strncpy(nuevo_paciente.sexo_paciente, sexo, sizeof(nuevo_paciente.sexo_paciente));
    strncpy(nuevo_paciente.tipo_sangre, tipo_sangre, sizeof(nuevo_paciente.tipo_sangre));
    strncpy(nuevo_paciente.telefono_Ppaciente, telefono, sizeof(nuevo_paciente.telefono_Ppaciente));
    strncpy(nuevo_paciente.direccion_casa, direccion, sizeof(nuevo_paciente.direccion_casa));
    strncpy(nuevo_paciente.email, email, sizeof(nuevo_paciente.email));
    
    nuevo_paciente.historial = new HistorialMedico[10];
    nuevo_paciente.cantidad_Consultas = 0;
    nuevo_paciente.capacidad_HistorialTotal = 10;
    
    nuevo_paciente.citas_agendadas = new int[10];
    nuevo_paciente.cantidad_citas = 0;
    nuevo_paciente.capacidad_citas = 10;
    
    nuevo_paciente.alergias[0] = '\0';
    nuevo_paciente.observaciones[0] = '\0';
    
    nuevo_paciente.activo = true;
    
    hospital->pacientes[hospital->cantidad_Pacientes++] = nuevo_paciente;
    
    return &hospital->pacientes[hospital->cantidad_Pacientes - 1];

    
}







int main() {
    Hospital hospital;
    hospital.siguienteIdPaciente = 1;
    hospital.cantidad_Pacientes = 0;
    hospital.capacidad_Pacientes_total = 100;
    hospital.pacientes = new Paciente[hospital.capacidad_Pacientes_total];
    



