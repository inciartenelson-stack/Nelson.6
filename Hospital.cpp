#include <iostream>
#include <cstring>
#include <ctime>
#include <iosmanip>
using namespace std;


struct HospitalMedico {
    int idConsulta;
    char fecha[11];
    char hora[6];
    char diagnostico[200];
    char tratamiento[200];
    char medicamentos[150];
    int idDoctor;
    float costo;

};

struct paciente {
    int id;
    char nombre[50];
    char apellido[50];
    char cedula[20];
    int edad;
    char sexo[10];
    char tipoSangre[5];
    char telefono[15];
    char direccion[100];
    char email[50];
    
    HistorialMedico* historial;
    int cantidadConsultas;
    int capacidadHistorial;
    
    int citasAgendadas;
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
    char horario[50];
    char telefono[15];
    char email[50];
    
    int* pacientesAsignadosD;
    int cantidadPacientesD;
    int capacidadPacientesD;
    
    int* citasAgendadas;
    int cantidadCitas;
    int capacidadCitas;
    
    bool disponible;
};

struct cita {
    int id;
    int idPpaciente;
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
    char direccion[200];
    char telefono[15];

    Paciente* pacientes;
    int cantidadPacientes;
    int capacidadPacientes;

    Doctor* doctores;
    int cantidadDoctores;
    int capacidadDoctores;

    Citas* citas;
    int cantidadCitas;
    int capacidadCitas;

    int siguienteIDPaciente;
    int siguienteIDDoctor;
    int SiguienteIDCita;
    int siguienteIDConsulta;
    };


    char* copiarString(const char* origen)  {
        if (!origen) return nullptr;
        size_t len = strlen (origen);
        char* copia = new char [len + 1];
        strcpy (copia, origen);
        return copia;
    }
    
void toLower (char*str){
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;
    }
}
    bool strEqualsIgnorease(const char* a, const char* b) {
        if (a! || !b ) return false;
        char aLow[200] , blow[200];
        strcpy (aLow, a);
        strcpy (bLow, b);
        toLower (aLow);
        toLower (bLow);
        return strcmp (aLow, bLow) == 0;

    }

    bool contiene(const char* cadena,const char* subcadena){
        if (!cadena || !subcadena) return false;
        char cad[200], sub[200];
        strcpy (cad, cadena);
        strcpy (sub, subcadena);
        toLower (cad);
        toLower (sub);
        return strstr (cad, sub) != nullptr;
    }

    
}






    



