#ifndef CITA_HPP
#define CITA_HPP

#include <string>
#include <ctime>

enum EstadoCita {
    PENDIENTE,      ///< Cita programada pero aún no atendida
    CONFIRMADA,     ///< Cita confirmada por el paciente
    COMPLETADA,     ///< Cita atendida y finalizada
    CANCELADA,      ///< Cita cancelada
    REPROGRAMADA    ///< Cita cambiada a otra fecha/hora
};


class Cita {
private:
    int id;                     ///< Identificador único de la cita
    int idPaciente;            ///< ID del paciente
    int idDoctor;              ///< ID del doctor/medico
    std::time_t fechaHora;     ///< Fecha y hora de la cita (timestamp)
    EstadoCita estado;         ///< Estado actual de la cita
    std::string motivo;        ///< Motivo de la consulta
    std::string notas;         ///< Notas adicionales
    int duracion;              ///< Duración estimada en minutos

public:
    /**
     * @brief Constructor por defecto
     */
    Cita();


     
    Cita(int id, int idPaciente, int idDoctor, std::time_t fechaHora);

   
     
    Cita(int id, int idPaciente, int idDoctor, std::time_t fechaHora,
         const std::string& motivo, const std::string& notas = "",
         int duracion = 30, EstadoCita estado = PENDIENTE);

    // Getters
    int getId() const;
    int getIdPaciente() const;
    int getIdDoctor() const;
    std::time_t getFechaHora() const;
    EstadoCita getEstado() const;
    std::string getMotivo() const;
    std::string getNotas() const;
    int getDuracion() const;
    
    // Métodos para obtener información formateada
    std::string getFechaHoraStr() const;
    std::string getEstadoStr() const;

    // Setters
    void setId(int id);
    void setIdPaciente(int idPaciente);
    void setIdDoctor(int idDoctor);
    void setFechaHora(std::time_t fechaHora);
    void setEstado(EstadoCita estado);
    void setMotivo(const std::string& motivo);
    void setNotas(const std::string& notas);

     
    bool validarDatos() const;

    /**
     * @brief Verifica si la cita está activa (no cancelada ni completada)
     * @return true si la cita está pendiente, confirmada o reprogramada
     */
    bool estaActiva() const;

    /**
     * @brief Verifica si la cita es para hoy
     * @return true si la cita es para el día actual
     */
    bool esParaHoy() const;

    /**
     * @brief Verifica si la cita está en el pasado
     * @return true si la fecha/hora de la cita ya pasó
     */
    bool estaVencida() const;

    /**
     * @brief Reprograma la cita a una nueva fecha/hora
     * @param nuevaFechaHora Nueva fecha y hora
     * @return true si se reprogramó exitosamente
     */
    bool reprogramar(std::time_t nuevaFechaHora);

   

    bool cancelar(const std::string& motivoCancelacion = "");

    
    bool completar(const std::string& notasFinales = "");

    /**
     * @brief Muestra la información de la cita en consola
     */
    void mostrarInformacion() const;

    /**
     * @brief Serializa la cita a string para almacenamiento
     * @return String con los datos de la cita en formato CSV
     */
    std::string toString() const;

    
    bool fromString(const std::string& data);
};

#endif // CITA_HPP