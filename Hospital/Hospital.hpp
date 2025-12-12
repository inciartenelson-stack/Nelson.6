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
    // ============ CONSTRUCTORES ============
    Hospital();
    Hospital(const char* nombre, const char* direccion, const char* telefono);
    Hospital(const Hospital& otro);
    ~Hospital();
    
    // ============ GETTERS ============
    const char* getNombre() const;
    const char* getDireccion() const;
    const char* getTelefono() const;
    int getContadorPacientes() const;
    int getContadorDoctores() const;
    int getContadorCitas() const;
    int getContadorConsultas() const;
    
    // ============ SETTERS ============
    void setNombre(const char* nombre);
    void setDireccion(const char* direccion);
    void setTelefono(const char* telefono);
    
    // ============ GENERADORES DE ID ============
    int generarNuevoIDPaciente();
    int generarNuevoIDDoctor();
    int generarNuevoIDCita();
    int generarNuevoIDConsulta();
    
    // ============ INCREMENTADORES ============
    void incrementarPacientesRegistrados();
    void incrementarDoctoresRegistrados();
    void incrementarCitasRegistradas();
    void incrementarConsultasRegistradas();
    
    void decrementarPacientesRegistrados();
    void decrementarDoctoresRegistrados();
    void decrementarCitasRegistradas();
    void decrementarConsultasRegistradas();
    
    // ============ MÉTODOS DE PRESENTACIÓN ============
    void mostrarInformacion() const;
    void mostrarEstadisticas() const;
    
    // ============ MÉTODOS DE VALIDACIÓN ============
    bool validarDatos() const;
    
    // ============ MÉTODO ESTÁTICO ============
    static size_t obtenerTamano();
};

#endif