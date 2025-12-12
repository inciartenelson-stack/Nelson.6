#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <cstring>
#include <ctime>

class Doctor {
private:
    static const int MAX_NOMBRE = 50;
    static const int MAX_APELLIDO = 50;
    static const int MAX_CEDULA = 15;
    static const int MAX_ESPECIALIDAD = 50;
    static const int MAX_TELEFONO = 20;
    static const int MAX_CEDULA_PROFESIONAL = 20;
    static const int MAX_PACIENTES = 100;
    static const int MAX_CITAS = 100;
    
    int id;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    char cedula[MAX_CEDULA];
    char especialidad[MAX_ESPECIALIDAD];
    int aniosExperiencia;
    char telefono[MAX_TELEFONO];
    char cedulaProfesional[MAX_CEDULA_PROFESIONAL];
    double costoConsulta;
    
    bool disponible;
    char horarioTrabajo[100]; // Ej: "Lunes-Viernes 8:00-16:00"
    
    int cantidadPacientes;
    int pacientesIDs[MAX_PACIENTES];
    
    int cantidadCitas;
    int citasIDs[MAX_CITAS];
    
    time_t fechaCreacion;
    time_t fechaUltimaModificacion;
    
public:
    // ============ CONSTRUCTORES ============
    Doctor();
    Doctor(int id, const char* nombre, const char* apellido, const char* cedula, 
           const char* especialidad);
    Doctor(const Doctor& otro);
    ~Doctor();
    
    // ============ GETTERS ============
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedula() const;
    const char* getEspecialidad() const;
    int getAniosExperiencia() const;
    const char* getTelefono() const;
    const char* getCedulaProfesional() const;
    double getCostoConsulta() const;
    bool getDisponible() const;
    const char* getHorarioTrabajo() const;
    int getCantidadPacientes() const;
    const int* getPacientesIDs() const;
    int getCantidadCitas() const;
    const int* getCitasIDs() const;
    time_t getFechaCreacion() const;
    time_t getFechaUltimaModificacion() const;
    
    // ============ SETTERS ============
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setCedula(const char* cedula);
    void setEspecialidad(const char* especialidad);
    void setAniosExperiencia(int anios);
    void setTelefono(const char* telefono);
    void setCedulaProfesional(const char* cedula);
    void setCostoConsulta(double costo);
    void setDisponible(bool disponible);
    void setHorarioTrabajo(const char* horario);
    
    // ============ MÉTODOS DE VALIDACIÓN ============
    bool validarDatos() const;
    bool especialidadEsValida() const;
    bool cedulaProfesionalValida() const;
    bool costoConsultaValido() const;
    bool estaDisponible() const;
    
    // ============ MÉTODOS DE GESTIÓN DE RELACIONES ============
    bool agregarPacienteID(int pacienteID);
    bool eliminarPacienteID(int pacienteID);
    bool agregarCitaID(int citaID);
    bool eliminarCitaID(int citaID);
    bool pacienteExiste(int pacienteID) const;
    bool citaExiste(int citaID) const;
    
    // ============ MÉTODOS DE PRESENTACIÓN ============
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;
    void mostrarPacientes() const;
    void mostrarCitas() const;
    
    // ============ MÉTODOS AUXILIARES ============
    void actualizarFechaModificacion();
    void inicializarFechas();
    
    // ============ MÉTODO ESTÁTICO ============
    static size_t obtenerTamano();
};

#endif