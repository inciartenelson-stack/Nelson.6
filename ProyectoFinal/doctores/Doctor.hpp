#ifndef DOCTOR_HPP
#define DOCTOR_HPP

#include <ctime>

/**
 * @class Doctor
 * @brief Clase que representa a un médico en el sistema hospitalario
 * 
 * Esta clase almacena toda la información profesional de un doctor,
 * incluyendo datos personales, especialidad, disponibilidad y
 * relación con pacientes.
 */
class Doctor {
private:
    int id;                     ///< Identificador único del doctor
    char nombre[100];           ///< Nombre del doctor
    char apellido[100];         ///< Apellido del doctor
    char cedula[20];            ///< Cédula profesional
    char especialidad[50];      ///< Especialidad médica
    char telefono[30];          ///< Número de teléfono
    char email[100];            ///< Dirección de correo electrónico
    float costoConsulta;        ///< Costo de la consulta
    bool disponible;            ///< Estado de disponibilidad
    int pacienteIDs[100];       ///< IDs de pacientes atendidos
    int cantidadPacientes;      ///< Cantidad de pacientes atendidos
    std::time_t fechaCreacion;  ///< Fecha de creación del registro
    std::time_t fechaModificacion; ///< Fecha de última modificación

public:
    /**
     * @brief Constructor por defecto
     */
    Doctor();

    /**
     * @brief Constructor con parámetros básicos
     * @param id Identificador único
     * @param nombre Nombre del doctor
     * @param apellido Apellido del doctor
     * @param cedula Cédula profesional
     * @param especialidad Especialidad médica
     */
    Doctor(int id, const char* nombre, const char* apellido, 
           const char* cedula, const char* especialidad);

    /**
     * @brief Constructor de copia
     * @param otro Otro objeto Doctor a copiar
     */
    Doctor(const Doctor& otro);

    /**
     * @brief Destructor
     */
    ~Doctor();

    // Getters
    int getId() const { return id; }
    const char* getNombre() const { return nombre; }
    const char* getApellido() const { return apellido; }
    const char* getCedula() const { return cedula; }
    const char* getEspecialidad() const { return especialidad; }
    const char* getTelefono() const { return telefono; }
    const char* getEmail() const { return email; }
    float getCostoConsulta() const { return costoConsulta; }
    bool getDisponible() const { return disponible; }
    int getCantidadPacientes() const { return cantidadPacientes; }
    const int* getPacienteIDs() const { return pacienteIDs; }
    std::time_t getFechaCreacion() const { return fechaCreacion; }
    std::time_t getFechaModificacion() const { return fechaModificacion; }

    // Método para obtener nombre completo
    char* getNombreCompleto(char* buffer, size_t tamano) const;

    // Setters
    void setNombre(const char* nuevoNombre);
    void setApellido(const char* nuevoApellido);
    void setCedula(const char* nuevaCedula);
    void setEspecialidad(const char* nuevaEspecialidad);
    void setTelefono(const char* nuevoTelefono);
    void setEmail(const char* nuevoEmail);
    void setCostoConsulta(float nuevoCosto);
    void setDisponible(bool estado);

    // Métodos de validación
    bool especialidadEsValida() const;
    bool cedulaProfesionalValida() const;
    bool costoConsultaValido() const;
    bool validarDatos() const;

    // Métodos para gestión de pacientes
    bool agregarPacienteID(int pacienteID);
    bool eliminarPacienteID(int pacienteID);
    bool tienePacienteID(int pacienteID) const;
    void limpiarPacientes();

    // Métodos de información
    void mostrarInformacionBasica() const;
    void mostrarInformacionCompleta() const;
    void mostrarPacientesAtendidos() const;

    /**
     * @brief Verifica si el doctor está disponible en una fecha específica
     * @param fechaTimestamp Timestamp de la fecha a verificar
     * @return true si está disponible, false en caso contrario
     */
    bool estaDisponibleFecha(std::time_t fechaTimestamp) const;

    /**
     * @brief Obtiene la experiencia del doctor en años
     * @return Años de experiencia (calculado desde fechaCreacion)
     */
    int getExperienciaAnios() const;

    /**
     * @brief Serializa el doctor a string para almacenamiento
     * @param buffer Buffer de salida
     * @param tamano Tamaño del buffer
     * @return true si se serializó correctamente
     */
    bool toString(char* buffer, size_t tamano) const;

    /**
     * @brief Carga un doctor desde un string serializado
     * @param data String con los datos serializados
     * @return true si se cargó correctamente
     */
    bool fromString(const char* data);

    // Sobrecarga de operadores
    Doctor& operator=(const Doctor& otro);
    bool operator==(const Doctor& otro) const;
    bool operator!=(const Doctor& otro) const;
    bool operator<(const Doctor& otro) const; ///< Ordenar por apellido

    // Métodos estáticos
    static bool validarEspecialidad(const char* especialidad);
    static const char** obtenerEspecialidadesValidas(int& cantidad);
    static float obtenerCostoPromedioEspecialidad(const char* especialidad);
};

#endif // DOCTOR_HPP