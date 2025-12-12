#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include <string>

/**
 * @class Paciente
 * @brief Clase que representa a un paciente en el sistema hospitalario
 * 
 * Esta clase almacena toda la información personal y médica de un paciente,
 * incluyendo datos de contacto, identificación y validación de información.
 */
class Paciente {
private:
    int id;                     ///< Identificador único del paciente
    std::string nombre;         ///< Nombre del paciente
    std::string apellido;       ///< Apellido del paciente
    std::string cedula;         ///< Número de cédula/identificación
    int edad;                   ///< Edad del paciente
    char genero;                ///< Género del paciente (M/F/O)
    std::string telefono;       ///< Número de teléfono
    std::string email;          ///< Dirección de correo electrónico

public:
    /**
     * @brief Constructor por defecto
     */
    Paciente();

 
     
    Paciente(int id, const std::string& nombre, const std::string& apellido, const std::string& cedula);

    
     
    Paciente(int id, const std::string& nombre, const std::string& apellido, 
             const std::string& cedula, int edad, char genero, 
             const std::string& telefono, const std::string& email);

    // Getters
    int getId() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getNombreCompleto() const;
    std::string getCedula() const;
    int getEdad() const;
    char getGenero() const;
    std::string getTelefono() const;
    std::string getEmail() const;

    // Setters
    void setId(int id);
    void setNombre(const std::string& nombre);
    void setApellido(const std::string& apellido);
    void setCedula(const std::string& cedula);
    void setEdad(int edad);
    void setGenero(char genero);
    void setTelefono(const std::string& telefono);
    void setEmail(const std::string& email);


     
    bool validarDatos() const;

    /**
     * @brief Muestra la información del paciente en consola
     */
    void mostrarInformacion() const;

    /**
     * @brief Serializa el paciente a string para almacenamiento
     * @return String con los datos del paciente en formato CSV
     */
    std::string toString() const;

    /**
     * @brief Carga un paciente desde un string serializado
     * @param data String con los datos en formato CSV
     * @return true si se cargó correctamente, false en caso contrario
     */
    bool fromString(const std::string& data);
};

#endif // PACIENTE_HPP