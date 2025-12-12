#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <cstring>

class Hospital {
private:
    static const int MAX_NOMBRE = 100;
    static const int MAX_DIRECCION = 200;
    static const int MAX_TELEFONO = 20;
    
    char nombre[MAX_NOMBRE];
    char direccion[MAX_DIRECCION];
    char telefono[MAX_TELEFONO];
    
    int contadorPacientes;
    int contadorDoctores;
    int contadorCitas;
    int contadorConsultas;
    
    int proximoIDPaciente;
    int proximoIDDoctor;
    int proximoIDCita;
    int proximoIDConsulta;
    
public:
    // Constructores
    Hospital();
    Hospital(const char* nombre, const char* direccion, const char* telefono);
    
    // Getters
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const;
    int getContadorPacientes() const;
    int getContadorDoctores() const;
    int getContadorCitas() const;
    int getContadorConsultas() const;
    
    // Setters
    void setNombre(const char* nombre);
    void setDireccion(const char* direccion);
    void setTelefono(const char* telefono);
    
    // Generadores de ID
    int generarNuevoIDPaciente();
    int generarNuevoIDDoctor();
    int generarNuevoIDCita();
    int generarNuevoIDConsulta();
    
    // Incrementadores
    void incrementarPacientesRegistrados();
    void incrementarDoctoresRegistrados();
    void incrementarCitasRegistradas();
    void incrementarConsultasRegistradas();
    
    // Métodos de presentación
    void mostrarInformacion() const;
    void mostrarEstadisticas() const;
    
    // Validación
    bool validarDatos() const;
    
    // Método estático
    static size_t obtenerTamano();
};

#endif