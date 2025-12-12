#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <cstring>
#include <ctime>

class Paciente {
private:
    static const int MAX_NOMBRE = 50;
    static const int MAX_APELLIDO = 50;
    static const int MAX_CEDULA = 15;
    static const int MAX_TELEFONO = 20;
    static const int MAX_DIRECCION = 200;
    static const int MAX_EMAIL = 100;
    static const int MAX_CONTACTO_EMERGENCIA = 100;
    static const int MAX_CITAS = 100;
    
    int id;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
    char cedula[MAX_CEDULA];
    int edad;
    char genero; // 'M' o 'F'
    char telefono[MAX_TELEFONO];
    char direccion[MAX_DIRECCION];
    char email[MAX_EMAIL];
    char contactoEmergencia[MAX_CONTACTO_EMERGENCIA];
    char telefonoEmergencia[MAX_TELEFONO];
    char tipoSangre[4]; // "A+", "O-", etc.
    
    int cantidadCitas;
    int citasIDs[MAX_CITAS];
    
    time_t fechaCreacion;
    time_t fechaUltimaModificacion;
    
public:
    // ============ CONSTRUCTORES ============
    Paciente();
    Paciente(int id, const char* nombre, const char* apellido, const char* cedula);
    Paciente(const Paciente& otro);
    ~Paciente();
    
    // ============ GETTERS ============
    int getId() const;
    const char* getNombre() const;
    const char* getApellido() const;
    const char* getCedula() const;
    int getEdad() const;
    char getGenero() const;
    const char* getTelefono() const;
    const char* getDireccion() const;
    const char* getEmail() const;
    const char* getContactoEmergencia() const;
    const char* getTelefonoEmergencia() const;
    const char* getTipoSangre() const;
    int getCantidadCitas() const;
    const int* getCitasIDs() const;
    time_t getFechaCreacion() const;
    time_t getFechaUltimaModificacion() const;
    
    // ============ SETTERS ============
    void setNombre(const char* nombre);
    void setApellido(const char* apellido);
    void setCedula(const char* cedula);
    void setEdad(int edad);
    void setGenero(char genero);
    void setTelefono(const char* telefono);
    void setDireccion(const char* direccion);
    void setEmail(const char* email);
    void setContactoEmergencia(const char* contacto);
    void setTelefonoEmergencia(const char* telefono);
    void setTipoSangre(const char* tipoSangre);
    
    // ============ MÉTODOS DE VALIDACIÓN ============
    bool validarDatos() const;
    bool esMayorDeEdad() const;
    bool cedulaEsValida() const;
    bool tieneContactoEmergencia() const;
    
    // ============ MÉTODOS DE GESTIÓN DE RELACIONES ============
    bool agregarCitaID(int citaID);
    bool eliminarCitaID(int citaID);
    bool tieneCitas() const;
    bool citaExiste(int citaID) const;
    
    // ============ MÉTODOS DE PRESENTACIÓN ============
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;
    void mostrarCitas() const;
    
    // ============ MÉTODOS AUXILIARES ============
    void actualizarFechaModificacion();
    void inicializarFechas();
    
    // ============ MÉTODO ESTÁTICO ============
    static size_t obtenerTamano();
};

#endif