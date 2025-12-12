#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include "Paciente.hpp"
#include "Doctor.hpp"
#include "Cita.hpp"
#include "../historiales/HistorialMedico.hpp"
#include <vector>
#include <string>
#include <map>
#include <queue>

/**
 * @class Hospital
 * @brief Clase principal que gestiona todo el sistema hospitalario
 * 
 * Esta clase centraliza la gestión de pacientes, doctores, citas,
 * historiales médicos y todas las operaciones del sistema.
 */
class Hospital {
private:
    std::string nombre;                 ///< Nombre del hospital
    std::string direccion;              ///< Dirección del hospital
    std::string telefono;               ///< Teléfono de contacto
    int capacidadTotal;                 ///< Capacidad máxima de pacientes
    int proximoIDPaciente;              ///< Siguiente ID para pacientes
    int proximoIDDoctor;                ///< Siguiente ID para doctores
    int proximoIDCita;                  ///< Siguiente ID para citas
    int proximoIDHistorial;             ///< Siguiente ID para historiales
    
    // Contenedores principales
    std::vector<Paciente> pacientes;    ///< Lista de pacientes
    std::vector<Doctor> doctores;       ///< Lista de doctores
    std::vector<Cita> citas;            ///< Lista de citas
    std::vector<HistorialMedico> historiales; ///< Lista de historiales médicos
    
    // Índices para búsquedas rápidas
    std::map<int, int> indicePacientes;       ///< Mapa ID -> índice en vector pacientes
    std::map<int, int> indiceDoctores;        ///< Mapa ID -> índice en vector doctores
    std::map<int, int> indiceCitas;           ///< Mapa ID -> índice en vector citas
    std::map<int, int> indiceHistoriales;     ///< Mapa ID -> índice en vector historiales
    
    // Cola de espera para pacientes no atendidos
    std::queue<int> colaEspera;               ///< IDs de pacientes en espera

public:
    /**
     * @brief Constructor por defecto
     */
    Hospital();

    /**
     * @brief Constructor con parámetros básicos
     * @param nombre Nombre del hospital
     * @param direccion Dirección del hospital
     * @param telefono Teléfono de contacto
     * @param capacidad Capacidad máxima de pacientes
     */
    Hospital(const std::string& nombre, const std::string& direccion, 
             const std::string& telefono, int capacidad);

    // Métodos de configuración del hospital
    std::string getNombre() const;
    std::string getDireccion() const;
    std::string getTelefono() const;
    int getCapacidadTotal() const;
    int getOcupacionActual() const;
    int getProximoIDPaciente() const;
    int getProximoIDDoctor() const;
    int getProximoIDCita() const;
    int getProximoIDHistorial() const;
    
    void setNombre(const std::string& nombre);
    void setDireccion(const std::string& direccion);
    void setTelefono(const std::string& telefono);
    void setCapacidadTotal(int capacidad);

    // Métodos para generar nuevos IDs
    int generarNuevoIDPaciente();
    int generarNuevoIDDoctor();
    int generarNuevoIDCita();
    int generarNuevoIDHistorial();

    // Gestión de pacientes
    bool agregarPaciente(const Paciente& paciente);
    bool eliminarPaciente(int idPaciente);
    Paciente* buscarPaciente(int idPaciente);
    const Paciente* buscarPaciente(int idPaciente) const;
    std::vector<Paciente> buscarPacientesPorNombre(const std::string& nombre) const;
    std::vector<Paciente> getTodosPacientes() const;
    int getCantidadPacientes() const;
    bool existePaciente(int idPaciente) const;

    // Gestión de doctores
    bool agregarDoctor(const Doctor& doctor);
    bool eliminarDoctor(int idDoctor);
    Doctor* buscarDoctor(int idDoctor);
    const Doctor* buscarDoctor(int idDoctor) const;
    std::vector<Doctor> buscarDoctoresPorEspecialidad(const std::string& especialidad) const;
    std::vector<Doctor> getTodosDoctores() const;
    int getCantidadDoctores() const;
    bool existeDoctor(int idDoctor) const;

    // Gestión de citas
    bool agregarCita(const Cita& cita);
    bool eliminarCita(int idCita);
    Cita* buscarCita(int idCita);
    const Cita* buscarCita(int idCita) const;
    std::vector<Cita> buscarCitasPorPaciente(int idPaciente) const;
    std::vector<Cita> buscarCitasPorDoctor(int idDoctor) const;
    std::vector<Cita> buscarCitasPorFecha(std::time_t fecha) const;
    std::vector<Cita> getCitasHoy() const;
    std::vector<Cita> getCitasPendientes() const;
    std::vector<Cita> getTodasCitas() const;
    int getCantidadCitas() const;
    bool existeCita(int idCita) const;
    
    /**
     * @brief Verifica si hay conflicto de horarios para un doctor
     * @param idDoctor ID del doctor
     * @param fechaHora Fecha y hora propuesta
     * @param duracion Duración en minutos
     * @return true si hay conflicto, false si está disponible
     */
    bool tieneConflictoHorario(int idDoctor, std::time_t fechaHora, int duracion = 30) const;

    // Gestión de historiales médicos
    bool agregarHistorial(const HistorialMedico& historial);
    bool eliminarHistorial(int idHistorial);
    HistorialMedico* buscarHistorial(int idHistorial);
    const HistorialMedico* buscarHistorial(int idHistorial) const;
    std::vector<HistorialMedico> buscarHistorialesPorPaciente(int idPaciente) const;
    HistorialMedico* getUltimoHistorialPaciente(int idPaciente);
    std::vector<HistorialMedico> getTodosHistoriales() const;
    int getCantidadHistoriales() const;
    bool existeHistorial(int idHistorial) const;

    // Gestión de cola de espera
    void agregarAColaEspera(int idPaciente);
    int atenderSiguientePaciente();
    int getCantidadEnEspera() const;
    std::vector<int> getColaEspera() const;
    bool pacienteEnEspera(int idPaciente) const;
    void limpiarColaEspera();

    // Estadísticas y reportes
    struct EstadisticasHospital {
        int totalPacientes;
        int totalDoctores;
        int totalCitas;
        int totalHistoriales;
        int citasHoy;
        int citasPendientes;
        int pacientesEnEspera;
        float ocupacionPorcentaje;
        std::map<std::string, int> citasPorEspecialidad;
        std::map<int, int> pacientesPorEdad;
    };
    
    EstadisticasHospital obtenerEstadisticas() const;
    void mostrarEstadisticas() const;
    
    /**
     * @brief Genera un reporte detallado del hospital
     * @param incluirPacientes Incluir lista de pacientes
     * @param incluirDoctores Incluir lista de doctores
     * @param incluirCitas Incluir lista de citas
     * @return String con el reporte generado
     */
    std::string generarReporte(bool incluirPacientes = false, 
                               bool incluirDoctores = false, 
                               bool incluirCitas = false) const;

    // Métodos de persistencia
    bool guardarEnArchivo(const std::string& ruta) const;
    bool cargarDesdeArchivo(const std::string& ruta);
    
    /**
     * @brief Guarda el estado actual del hospital
     * @param datos Puntero a datos de salida
     * @param tamano Tamaño de los datos
     * @return true si se guardó correctamente
     */
    bool guardarEstado(void* datos, size_t& tamano) const;
    
    /**
     * @brief Carga el estado del hospital
     * @param datos Puntero a datos de entrada
     * @param tamano Tamaño de los datos
     * @return true si se cargó correctamente
     */
    bool cargarEstado(const void* datos, size_t tamano);

    // Métodos de utilidad
    void mostrarInformacion() const;
    bool estaLleno() const;
    void limpiarSistema();
    
    /**
     * @brief Verifica la consistencia de los datos internos
     * @return true si todos los datos son consistentes
     */
    bool verificarConsistencia() const;
};

#endif // HOSPITAL_HPP
