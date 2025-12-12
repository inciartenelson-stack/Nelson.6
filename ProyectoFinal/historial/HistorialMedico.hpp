#ifndef HISTORIALMEDICO_HPP
#define HISTORIALMEDICO_HPP

#include <string>
#include <vector>
#include <ctime>


class HistorialMedico {
private:
    int id;                     ///< Identificador único del historial
    int idPaciente;            ///< ID del paciente
    int idDoctor;              ///< ID del doctor que creó el registro
    int idCita;                ///< ID de la cita asociada (opcional)
    std::time_t fechaCreacion; ///< Fecha de creación del registro
    std::string diagnostico;   ///< Diagnóstico médico
    std::string tratamiento;   ///< Tratamiento prescrito
    std::vector<std::string> medicamentos; ///< Lista de medicamentos
    std::string alergias;      ///< Alergias conocidas
    std::string antecedentes;  ///< Antecedentes médicos familiares
    std::string notas;         ///< Notas adicionales
    float peso;                ///< Peso del paciente (kg)
    float altura;              ///< Altura del paciente (m)
    float temperatura;         ///< Temperatura corporal (°C)
    int presionSistolica;      ///< Presión arterial sistólica
    int presionDiastolica;     ///< Presión arterial diastólica
    int frecuenciaCardiaca;    ///< Frecuencia cardíaca (ppm)
    int frecuenciaRespiratoria; ///< Frecuencia respiratoria (rpm)

public:
    /**
     * @brief Constructor por defecto
     */
    HistorialMedico();

    /**
     * @brief Constructor básico
     * @param id Identificador único
     * @param idPaciente ID del paciente
     * @param idDoctor ID del doctor
     * @param idCita ID de la cita asociada
     */
    HistorialMedico(int id, int idPaciente, int idDoctor, int idCita);

    /**
     * @brief Constructor completo
     * @param id Identificador único
     * @param idPaciente ID del paciente
     * @param idDoctor ID del doctor
     * @param idCita ID de la cita asociada
     * @param diagnostico Diagnóstico médico
     * @param tratamiento Tratamiento prescrito
     * @param fechaCreacion Fecha de creación (timestamp)
     */
    HistorialMedico(int id, int idPaciente, int idDoctor, int idCita,
                    const std::string& diagnostico, const std::string& tratamiento,
                    std::time_t fechaCreacion = std::time(nullptr));

    // Getters
    int getId() const;
    int getIdPaciente() const;
    int getIdDoctor() const;
    int getIdCita() const;
    std::time_t getFechaCreacion() const;
    std::string getDiagnostico() const;
    std::string getTratamiento() const;
    const std::vector<std::string>& getMedicamentos() const;
    std::string getAlergias() const;
    std::string getAntecedentes() const;
    std::string getNotas() const;
    float getPeso() const;
    float getAltura() const;
    float getTemperatura() const;
    int getPresionSistolica() const;
    int getPresionDiastolica() const;
    int getFrecuenciaCardiaca() const;
    int getFrecuenciaRespiratoria() const;
    
    // Métodos para obtener información formateada
    std::string getFechaCreacionStr() const;
    float getIMC() const; ///< Índice de Masa Corporal
    std::string getPresionArterialStr() const;
    std::string getMedicamentosStr() const;

    // Setters
    void setId(int id);
    void setIdPaciente(int idPaciente);
    void setIdDoctor(int idDoctor);
    void setIdCita(int idCita);
    void setFechaCreacion(std::time_t fechaCreacion);
    void setDiagnostico(const std::string& diagnostico);
    void setTratamiento(const std::string& tratamiento);
    void setAlergias(const std::string& alergias);
    void setAntecedentes(const std::string& antecedentes);
    void setNotas(const std::string& notas);
    void setPeso(float peso);
    void setAltura(float altura);
    void setTemperatura(float temperatura);
    void setPresionSistolica(int presionSistolica);
    void setPresionDiastolica(int presionDiastolica);
    void setFrecuenciaCardiaca(int frecuenciaCardiaca);
    void setFrecuenciaRespiratoria(int frecuenciaRespiratoria);

    // Métodos para gestionar medicamentos
    void agregarMedicamento(const std::string& medicamento);
    bool eliminarMedicamento(const std::string& medicamento);
    void limpiarMedicamentos();
    bool contieneMedicamento(const std::string& medicamento) const;

    /**
     * @brief Valida los datos del historial médico
     * @return true si los datos son válidos, false en caso contrario
     * 
     * Realiza validaciones como:
     * - IDs positivos
     * - Valores fisiológicos en rangos razonables
     * - Diagnóstico no vacío
     */
    bool validarDatos() const;

    /**
     * @brief Verifica si los signos vitales están en rangos normales
     * @return true si todos los signos vitales están dentro de rangos normales
     */
    bool signosVitalesNormales() const;

    /**
     * @brief Obtiene una evaluación del IMC
     * @return String con la clasificación del IMC (Bajo peso, Normal, etc.)
     */
    std::string getClasificacionIMC() const;

    /**
     * @brief Genera un resumen del historial médico
     * @return String con un resumen conciso
     */
    std::string generarResumen() const;

    /**
     * @brief Muestra la información completa del historial en consola
     */
    void mostrarInformacion() const;

    /**
     * @brief Muestra un resumen compacto del historial
     */
    void mostrarResumen() const;

    /**
     * @brief Serializa el historial a string para almacenamiento
     * @return String con los datos en formato CSV
     */
    std::string toString() const;

    /**
     * @brief Carga un historial desde un string serializado
     * @param data String con los datos en formato CSV
     * @return true si se cargó correctamente, false en caso contrario
     */
    bool fromString(const std::string& data);
};

#endif // HISTORIALMEDICO_HPP