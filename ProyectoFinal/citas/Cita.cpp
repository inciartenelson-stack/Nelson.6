#include "Cita.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

// Constructor por defecto
Cita::Cita() : id(0), idPaciente(0), idDoctor(0), fechaHora(0), 
               duracion(30), estado(PENDIENTE) {}

// Constructor básico
Cita::Cita(int id, int idPaciente, int idDoctor, time_t fechaHora)
    : id(id), idPaciente(idPaciente), idDoctor(idDoctor), 
      fechaHora(fechaHora), duracion(30), estado(PENDIENTE) {}

// Constructor completo
Cita::Cita(int id, int idPaciente, int idDoctor, time_t fechaHora,
           const string& motivo, const string& notas,
           int duracion, EstadoCita estado)
    : id(id), idPaciente(idPaciente), idDoctor(idDoctor), 
      fechaHora(fechaHora), motivo(motivo), notas(notas),
      duracion(duracion), estado(estado) {}

// Getters
int Cita::getId() const { return id; }
int Cita::getIdPaciente() const { return idPaciente; }
int Cita::getIdDoctor() const { return idDoctor; }
time_t Cita::getFechaHora() const { return fechaHora; }
EstadoCita Cita::getEstado() const { return estado; }
string Cita::getMotivo() const { return motivo; }
string Cita::getNotas() const { return notas; }
int Cita::getDuracion() const { return duracion; }

string Cita::getFechaHoraStr() const {
    if (fechaHora == 0) return "No asignada";
    
    tm* tiempoLocal = localtime(&fechaHora);
    stringstream ss;
    ss << put_time(tiempoLocal, "%d/%m/%Y %H:%M");
    return ss.str();
}

string Cita::getEstadoStr() const {
    switch(estado) {
        case PENDIENTE: return "Pendiente";
        case CONFIRMADA: return "Confirmada";
        case COMPLETADA: return "Completada";
        case CANCELADA: return "Cancelada";
        case REPROGRAMADA: return "Reprogramada";
        default: return "Desconocido";
    }
}

// Setters
void Cita::setId(int id) { this->id = id; }
void Cita::setIdPaciente(int idPaciente) { this->idPaciente = idPaciente; }
void Cita::setIdDoctor(int idDoctor) { this->idDoctor = idDoctor; }
void Cita::setFechaHora(time_t fechaHora) { this->fechaHora = fechaHora; }
void Cita::setEstado(EstadoCita estado) { this->estado = estado; }
void Cita::setMotivo(const string& motivo) { this->motivo = motivo; }
void Cita::setNotas(const string& notas) { this->notas = notas; }

// Método setDuracion faltante en el .hpp - agregado aquí
void Cita::setDuracion(int duracion) { 
    this->duracion = duracion; 
}

bool Cita::validarDatos() const {
    // Validar IDs
    if (id <= 0) {
        cerr << "Error: ID de cita inválido (" << id << ").\n";
        return false;
    }
    
    if (idPaciente <= 0) {
        cerr << "Error: ID de paciente inválido (" << idPaciente << ").\n";
        return false;
    }
    
    if (idDoctor <= 0) {
        cerr << "Error: ID de doctor inválido (" << idDoctor << ").\n";
        return false;
    }
    
    // Validar fecha/hora (no puede ser 0)
    if (fechaHora == 0) {
        cerr << "Error: Fecha y hora no asignadas.\n";
        return false;
    }
    
    // Validar duración
    if (duracion <= 0 || duracion > 480) { // Máximo 8 horas
        cerr << "Error: Duración inválida (" << duracion 
                  << " minutos). Debe ser entre 1 y 480 minutos.\n";
        return false;
    }
    
    // Validar motivo
    if (motivo.empty()) {
        cerr << "Error: Motivo de la consulta no puede estar vacío.\n";
        return false;
    }
    
    // Validar que la fecha no esté en el pasado para citas futuras
    if (estado == PENDIENTE || estado == CONFIRMADA) {
        time_t ahora = time(nullptr);
        if (fechaHora < ahora) {
            cerr << "Error: La cita no puede estar en el pasado para estado " 
                      << getEstadoStr() << ".\n";
            return false;
        }
    }
    
    return true;
}

bool Cita::estaActiva() const {
    return (estado == PENDIENTE || estado == CONFIRMADA || estado == REPROGRAMADA);
}

bool Cita::esParaHoy() const {
    if (fechaHora == 0) return false;
    
    time_t ahora = time(nullptr);
    tm* hoy = localtime(&ahora);
    tm* fechaCita = localtime(&fechaHora);
    
    return (hoy->tm_year == fechaCita->tm_year &&
            hoy->tm_mon == fechaCita->tm_mon &&
            hoy->tm_mday == fechaCita->tm_mday);
}

bool Cita::estaVencida() const {
    if (fechaHora == 0) return false;
    
    time_t ahora = time(nullptr);
    return fechaHora < ahora;
}

bool Cita::reprogramar(time_t nuevaFechaHora) {
    if (nuevaFechaHora == 0) {
        cerr << "Error: Nueva fecha/hora no válida.\n";
        return false;
    }
    
    if (estado == CANCELADA || estado == COMPLETADA) {
        cerr << "Error: No se puede reprogramar una cita " 
                  << getEstadoStr() << ".\n";
        return false;
    }
    
    // Validar que la nueva fecha no esté en el pasado
    time_t ahora = time(nullptr);
    if (nuevaFechaHora < ahora) {
        cerr << "Error: No se puede reprogramar al pasado.\n";
        return false;
    }
    
    fechaHora = nuevaFechaHora;
    estado = REPROGRAMADA;
    
    // Agregar nota sobre la reprogramación
    stringstream ss;
    ss << " [Reprogramada el " << getFechaHoraStr() << "]";
    notas += ss.str();
    
    return true;
}

bool Cita::cancelar(const string& motivoCancelacion) {
    if (estado == CANCELADA) {
        cerr << "Error: La cita ya está cancelada.\n";
        return false;
    }
    
    if (estado == COMPLETADA) {
        cerr << "Error: No se puede cancelar una cita completada.\n";
        return false;
    }
    
    estado = CANCELADA;
    if (!motivoCancelacion.empty()) {
        notas += " [Cancelada: " + motivoCancelacion + "]";
    } else {
        notas += " [Cancelada]";
    }
    
    return true;
}

bool Cita::completar(const string& notasFinales) {
    if (estado == CANCELADA) {
        cerr << "Error: No se puede completar una cita cancelada.\n";
        return false;
    }
    
    if (estado == COMPLETADA) {
        cerr << "Error: La cita ya está completada.\n";
        return false;
    }
    
    estado = COMPLETADA;
    if (!notasFinales.empty()) {
        notas += " [Completada: " + notasFinales + "]";
    } else {
        notas += " [Completada]";
    }
    
    return true;
}

void Cita::mostrarInformacion() const {
    cout << "\n=== INFORMACIÓN DE LA CITA ===\n";
    cout << "ID: " << id << "\n";
    cout << "ID Paciente: " << idPaciente << "\n";
    cout << "ID Doctor: " << idDoctor << "\n";
    cout << "Fecha y Hora: " << getFechaHoraStr() << "\n";
    cout << "Duración: " << duracion << " minutos\n";
    cout << "Estado: " << getEstadoStr() << "\n";
    cout << "Motivo: " << motivo << "\n";
    
    if (!notas.empty()) {
        cout << "Notas: " << notas << "\n";
    }
    
    // Indicadores de estado especial
    if (estaVencida() && estaActiva()) {
        cout << "⚠️  CITA VENCIDA\n";
    }
    
    if (esParaHoy() && estaActiva()) {
        cout << "📅 CITA PARA HOY\n";
    }
    
    cout << "===============================\n";
}

string Cita::toString() const {
    stringstream ss;
    ss << id << "|" 
       << idPaciente << "|" 
       << idDoctor << "|" 
       << fechaHora << "|" 
       << static_cast<int>(estado) << "|" 
       << motivo << "|" 
       << notas << "|" 
       << duracion;
    return ss.str();
}

bool Cita::fromString(const string& data) {
    stringstream ss(data);
    string token;
    vector<string> tokens;

    // Separar por pipe
    while (getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    // Debe tener exactamente 8 campos
    if (tokens.size() != 8) {
        cerr << "Error: Formato de datos inválido. Se esperaban 8 campos, se encontraron " 
                  << tokens.size() << ".\n";
        return false;
    }

    try {
        id = stoi(tokens[0]);
        idPaciente = stoi(tokens[1]);
        idDoctor = stoi(tokens[2]);
        fechaHora = static_cast<time_t>(stoll(tokens[3]));
        
        int estadoInt = stoi(tokens[4]);
        if (estadoInt >= 0 && estadoInt <= 4) {
            estado = static_cast<EstadoCita>(estadoInt);
        } else {
            estado = PENDIENTE;
        }
        
        motivo = tokens[5];
        notas = tokens[6];
        duracion = stoi(tokens[7]);
        
        return validarDatos();
    } catch (const exception& e) {
        cerr << "Error al cargar cita desde string: " << e.what() << "\n";
        return false;
    }
}

// Métodos adicionales útiles (no declarados en .hpp pero útiles)

/**
 * @brief Verifica si la cita está en conflicto con otra cita
 * @param otra Otra cita a comparar
 * @return true si hay conflicto de horario, false en caso contrario
 */
bool Cita::hayConflicto(const Cita& otra) const {
    if (idDoctor != otra.idDoctor && idPaciente != otra.idPaciente) {
        return false; // No hay conflicto si son diferentes doctores y pacientes
    }
    
    // Calcular tiempos de inicio y fin
    time_t inicio1 = fechaHora;
    time_t fin1 = fechaHora + (duracion * 60);
    
    time_t inicio2 = otra.fechaHora;
    time_t fin2 = otra.fechaHora + (otra.duracion * 60);
    
    // Verificar superposición
    bool conflictoDoctor = (idDoctor == otra.idDoctor) && 
                          ((inicio1 >= inicio2 && inicio1 < fin2) ||
                           (fin1 > inicio2 && fin1 <= fin2) ||
                           (inicio1 <= inicio2 && fin1 >= fin2));
    
    bool conflictoPaciente = (idPaciente == otra.idPaciente) && 
                            ((inicio1 >= inicio2 && inicio1 < fin2) ||
                             (fin1 > inicio2 && fin1 <= fin2) ||
                             (inicio1 <= inicio2 && fin1 >= fin2));
    
    return conflictoDoctor || conflictoPaciente;
}

/**
 * @brief Obtiene la fecha de la cita en formato corto
 * @return String con la fecha en formato DD/MM/AAAA
 */
string Cita::getFechaStr() const {
    if (fechaHora == 0) return "No asignada";
    
    tm* tiempoLocal = localtime(&fechaHora);
    stringstream ss;
    ss << put_time(tiempoLocal, "%d/%m/%Y");
    return ss.str();
}

/**
 * @brief Obtiene la hora de la cita en formato corto
 * @return String con la hora en formato HH:MM
 */
string Cita::getHoraStr() const {
    if (fechaHora == 0) return "No asignada";
    
    tm* tiempoLocal = localtime(&fechaHora);
    stringstream ss;
    ss << put_time(tiempoLocal, "%H:%M");
    return ss.str();
}

/**
 * @brief Confirma la cita (cambia estado de PENDIENTE a CONFIRMADA)
 * @return true si se pudo confirmar, false en caso contrario
 */
bool Cita::confirmar() {
    if (estado != PENDIENTE && estado != REPROGRAMADA) {
        cerr << "Error: Solo se pueden confirmar citas pendientes o reprogramadas.\n";
        return false;
    }
    
    estado = CONFIRMADA;
    notas += " [Confirmada]";
    return true;
}

/**
 * @brief Verifica si la cita está próxima (en las próximas 2 horas)
 * @return true si la cita está próxima, false en caso contrario
 */
bool Cita::estaProxima() const {
    if (fechaHora == 0) return false;
    if (!estaActiva()) return false;
    
    time_t ahora = time(nullptr);
    time_t dosHoras = 2 * 60 * 60; // 2 horas en segundos
    
    return (fechaHora > ahora && fechaHora <= (ahora + dosHoras));
}

/**
 * @brief Obtiene el tiempo restante para la cita
 * @return String con el tiempo restante formateado
 */
string Cita::getTiempoRestanteStr() const {
    if (fechaHora == 0) return "Fecha no asignada";
    if (!estaActiva()) return "Cita no activa";
    
    time_t ahora = time(nullptr);
    
    if (fechaHora <= ahora) {
        return "Cita vencida";
    }
    
    time_t diferencia = fechaHora - ahora;
    
    if (diferencia < 60) { // Menos de 1 minuto
        return "Menos de 1 minuto";
    } else if (diferencia < 3600) { // Menos de 1 hora
        long minutos = diferencia / 60;
        return to_string(minutos) + " minutos";
    } else if (diferencia < 86400) { // Menos de 1 día
        long horas = diferencia / 3600;
        long minutos = (diferencia % 3600) / 60;
        return to_string(horas) + "h " + to_string(minutos) + "m";
    } else { // Más de 1 día
        long dias = diferencia / 86400;
        return to_string(dias) + " días";
    }
}
