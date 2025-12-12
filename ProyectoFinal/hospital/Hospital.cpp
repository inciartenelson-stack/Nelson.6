#include "Hospital.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>
#include <cstring>
#include "../historiales/HistorialMedico.hpp"

// Constructor por defecto
Hospital::Hospital() 
    : nombre("Hospital General"), direccion("Av. Principal 123"), 
      telefono("+1-234-567-8900"), capacidadTotal(100),
      proximoIDPaciente(1), proximoIDDoctor(1), 
      proximoIDCita(1), proximoIDHistorial(1) {}

// Constructor con parámetros básicos
Hospital::Hospital(const std::string& nombre, const std::string& direccion, 
                   const std::string& telefono, int capacidad)
    : nombre(nombre), direccion(direccion), telefono(telefono), 
      capacidadTotal(capacidad), proximoIDPaciente(1), proximoIDDoctor(1),
      proximoIDCita(1), proximoIDHistorial(1) {}

// Métodos de configuración del hospital
std::string Hospital::getNombre() const { return nombre; }
std::string Hospital::getDireccion() const { return direccion; }
std::string Hospital::getTelefono() const { return telefono; }
int Hospital::getCapacidadTotal() const { return capacidadTotal; }
int Hospital::getOcupacionActual() const { return pacientes.size(); }
int Hospital::getProximoIDPaciente() const { return proximoIDPaciente; }
int Hospital::getProximoIDDoctor() const { return proximoIDDoctor; }
int Hospital::getProximoIDCita() const { return proximoIDCita; }
int Hospital::getProximoIDHistorial() const { return proximoIDHistorial; }

void Hospital::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Hospital::setDireccion(const std::string& direccion) { this->direccion = direccion; }
void Hospital::setTelefono(const std::string& telefono) { this->telefono = telefono; }
void Hospital::setCapacidadTotal(int capacidad) { this->capacidadTotal = capacidad; }

// Métodos para generar nuevos IDs
int Hospital::generarNuevoIDPaciente() { return proximoIDPaciente++; }
int Hospital::generarNuevoIDDoctor() { return proximoIDDoctor++; }
int Hospital::generarNuevoIDCita() { return proximoIDCita++; }
int Hospital::generarNuevoIDHistorial() { return proximoIDHistorial++; }

// Gestión de pacientes
bool Hospital::agregarPaciente(const Paciente& paciente) {
    if (estaLleno()) {
        std::cerr << "Error: Hospital ha alcanzado su capacidad máxima.\n";
        return false;
    }
    
    if (existePaciente(paciente.getId())) {
        std::cerr << "Error: Ya existe un paciente con ID " << paciente.getId() << ".\n";
        return false;
    }
    
    if (!paciente.validarDatos()) {
        std::cerr << "Error: Datos del paciente no válidos.\n";
        return false;
    }
    
    pacientes.push_back(paciente);
    indicePacientes[paciente.getId()] = pacientes.size() - 1;
    
    // Actualizar próximo ID si es necesario
    if (paciente.getId() >= proximoIDPaciente) {
        proximoIDPaciente = paciente.getId() + 1;
    }
    
    return true;
}

bool Hospital::eliminarPaciente(int idPaciente) {
    auto it = indicePacientes.find(idPaciente);
    if (it == indicePacientes.end()) {
        std::cerr << "Error: No existe paciente con ID " << idPaciente << ".\n";
        return false;
    }
    
    int index = it->second;
    
    // Eliminar citas asociadas
    auto citasIt = citas.begin();
    while (citasIt != citas.end()) {
        if (citasIt->getIdPaciente() == idPaciente) {
            int idCita = citasIt->getId();
            indiceCitas.erase(idCita);
            citasIt = citas.erase(citasIt);
        } else {
            ++citasIt;
        }
    }
    
    // Eliminar historiales asociados
    auto historialesIt = historiales.begin();
    while (historialesIt != historiales.end()) {
        if (historialesIt->getIdPaciente() == idPaciente) {
            int idHistorial = historialesIt->getId();
            indiceHistoriales.erase(idHistorial);
            historialesIt = historiales.erase(historialesIt);
        } else {
            ++historialesIt;
        }
    }
    
    // Eliminar de cola de espera
    std::queue<int> nuevaCola;
    while (!colaEspera.empty()) {
        int id = colaEspera.front();
        colaEspera.pop();
        if (id != idPaciente) {
            nuevaCola.push(id);
        }
    }
    colaEspera = nuevaCola;
    
    // Eliminar paciente
    pacientes.erase(pacientes.begin() + index);
    indicePacientes.erase(it);
    
    // Reindexar
    for (auto& pair : indicePacientes) {
        if (pair.second > index) {
            pair.second--;
        }
    }
    
    return true;
}

Paciente* Hospital::buscarPaciente(int idPaciente) {
    auto it = indicePacientes.find(idPaciente);
    if (it != indicePacientes.end() && it->second < pacientes.size()) {
        return &pacientes[it->second];
    }
    return nullptr;
}

const Paciente* Hospital::buscarPaciente(int idPaciente) const {
    auto it = indicePacientes.find(idPaciente);
    if (it != indicePacientes.end() && it->second < pacientes.size()) {
        return &pacientes[it->second];
    }
    return nullptr;
}

std::vector<Paciente> Hospital::buscarPacientesPorNombre(const std::string& nombre) const {
    std::vector<Paciente> resultados;
    std::string nombreLower = nombre;
    std::transform(nombreLower.begin(), nombreLower.end(), nombreLower.begin(), ::tolower);
    
    for (const auto& paciente : pacientes) {
        std::string nombreCompleto = paciente.getNombre() + " " + paciente.getApellido();
        std::transform(nombreCompleto.begin(), nombreCompleto.end(), nombreCompleto.begin(), ::tolower);
        
        if (nombreCompleto.find(nombreLower) != std::string::npos) {
            resultados.push_back(paciente);
        }
    }
    
    return resultados;
}

std::vector<Paciente> Hospital::getTodosPacientes() const {
    return pacientes;
}

int Hospital::getCantidadPacientes() const {
    return pacientes.size();
}

bool Hospital::existePaciente(int idPaciente) const {
    return indicePacientes.find(idPaciente) != indicePacientes.end();
}

// Gestión de doctores (implementaciones similares a pacientes)
bool Hospital::agregarDoctor(const Doctor& doctor) {
    if (existeDoctor(doctor.getId())) {
        std::cerr << "Error: Ya existe un doctor con ID " << doctor.getId() << ".\n";
        return false;
    }
    
    if (!doctor.validarDatos()) {
        std::cerr << "Error: Datos del doctor no válidos.\n";
        return false;
    }
    
    doctores.push_back(doctor);
    indiceDoctores[doctor.getId()] = doctores.size() - 1;
    
    if (doctor.getId() >= proximoIDDoctor) {
        proximoIDDoctor = doctor.getId() + 1;
    }
    
    return true;
}

bool Hospital::eliminarDoctor(int idDoctor) {
    auto it = indiceDoctores.find(idDoctor);
    if (it == indiceDoctores.end()) {
        std::cerr << "Error: No existe doctor con ID " << idDoctor << ".\n";
        return false;
    }
    
    int index = it->second;
    
    // Eliminar citas asociadas
    auto citasIt = citas.begin();
    while (citasIt != citas.end()) {
        if (citasIt->getIdDoctor() == idDoctor) {
            int idCita = citasIt->getId();
            indiceCitas.erase(idCita);
            citasIt = citas.erase(citasIt);
        } else {
            ++citasIt;
        }
    }
    
    // Eliminar historiales asociados
    auto historialesIt = historiales.begin();
    while (historialesIt != historiales.end()) {
        if (historialesIt->getIdDoctor() == idDoctor) {
            int idHistorial = historialesIt->getId();
            indiceHistoriales.erase(idHistorial);
            historialesIt = historiales.erase(historialesIt);
        } else {
            ++historialesIt;
        }
    }
    
    doctores.erase(doctores.begin() + index);
    indiceDoctores.erase(it);
    
    // Reindexar
    for (auto& pair : indiceDoctores) {
        if (pair.second > index) {
            pair.second--;
        }
    }
    
    return true;
}

Doctor* Hospital::buscarDoctor(int idDoctor) {
    auto it = indiceDoctores.find(idDoctor);
    if (it != indiceDoctores.end() && it->second < doctores.size()) {
        return &doctores[it->second];
    }
    return nullptr;
}

const Doctor* Hospital::buscarDoctor(int idDoctor) const {
    auto it = indiceDoctores.find(idDoctor);
    if (it != indiceDoctores.end() && it->second < doctores.size()) {
        return &doctores[it->second];
    }
    return nullptr;
}

std::vector<Doctor> Hospital::buscarDoctoresPorEspecialidad(const std::string& especialidad) const {
    std::vector<Doctor> resultados;
    std::string especialidadLower = especialidad;
    std::transform(especialidadLower.begin(), especialidadLower.end(), especialidadLower.begin(), ::tolower);
    
    for (const auto& doctor : doctores) {
        std::string espDoctor = doctor.getEspecialidad();
        std::transform(espDoctor.begin(), espDoctor.end(), espDoctor.begin(), ::tolower);
        
        if (espDoctor.find(especialidadLower) != std::string::npos) {
            resultados.push_back(doctor);
        }
    }
    
    return resultados;
}

std::vector<Doctor> Hospital::getTodosDoctores() const {
    return doctores;
}

int Hospital::getCantidadDoctores() const {
    return doctores.size();
}

bool Hospital::existeDoctor(int idDoctor) const {
    return indiceDoctores.find(idDoctor) != indiceDoctores.end();
}

// Gestión de citas
bool Hospital::agregarCita(const Cita& cita) {
    if (existeCita(cita.getId())) {
        std::cerr << "Error: Ya existe una cita con ID " << cita.getId() << ".\n";
        return false;
    }
    
    if (!cita.validarDatos()) {
        std::cerr << "Error: Datos de la cita no válidos.\n";
        return false;
    }
    
    if (!existePaciente(cita.getIdPaciente())) {
        std::cerr << "Error: No existe paciente con ID " << cita.getIdPaciente() << ".\n";
        return false;
    }
    
    if (!existeDoctor(cita.getIdDoctor())) {
        std::cerr << "Error: No existe doctor con ID " << cita.getIdDoctor() << ".\n";
        return false;
    }
    
    if (tieneConflictoHorario(cita.getIdDoctor(), cita.getFechaHora(), cita.getDuracion())) {
        std::cerr << "Error: Conflicto de horario para el doctor.\n";
        return false;
    }
    
    citas.push_back(cita);
    indiceCitas[cita.getId()] = citas.size() - 1;
    
    if (cita.getId() >= proximoIDCita) {
        proximoIDCita = cita.getId() + 1;
    }
    
    return true;
}

bool Hospital::eliminarCita(int idCita) {
    auto it = indiceCitas.find(idCita);
    if (it == indiceCitas.end()) {
        std::cerr << "Error: No existe cita con ID " << idCita << ".\n";
        return false;
    }
    
    int index = it->second;
    citas.erase(citas.begin() + index);
    indiceCitas.erase(it);
    
    // Reindexar
    for (auto& pair : indiceCitas) {
        if (pair.second > index) {
            pair.second--;
        }
    }
    
    return true;
}

Cita* Hospital::buscarCita(int idCita) {
    auto it = indiceCitas.find(idCita);
    if (it != indiceCitas.end() && it->second < citas.size()) {
        return &citas[it->second];
    }
    return nullptr;
}

const Cita* Hospital::buscarCita(int idCita) const {
    auto it = indiceCitas.find(idCita);
    if (it != indiceCitas.end() && it->second < citas.size()) {
        return &citas[it->second];
    }
    return nullptr;
}

std::vector<Cita> Hospital::buscarCitasPorPaciente(int idPaciente) const {
    std::vector<Cita> resultados;
    for (const auto& cita : citas) {
        if (cita.getIdPaciente() == idPaciente) {
            resultados.push_back(cita);
        }
    }
    return resultados;
}

std::vector<Cita> Hospital::buscarCitasPorDoctor(int idDoctor) const {
    std::vector<Cita> resultados;
    for (const auto& cita : citas) {
        if (cita.getIdDoctor() == idDoctor) {
            resultados.push_back(cita);
        }
    }
    return resultados;
}

std::vector<Cita> Hospital::buscarCitasPorFecha(std::time_t fecha) const {
    std::vector<Cita> resultados;
    std::tm* fechaBuscada = std::localtime(&fecha);
    
    for (const auto& cita : citas) {
        std::time_t fechaCita = cita.getFechaHora();
        std::tm* fechaCitaTm = std::localtime(&fechaCita);
        
        if (fechaBuscada->tm_year == fechaCitaTm->tm_year &&
            fechaBuscada->tm_mon == fechaCitaTm->tm_mon &&
            fechaBuscada->tm_mday == fechaCitaTm->tm_mday) {
            resultados.push_back(cita);
        }
    }
    
    return resultados;
}

std::vector<Cita> Hospital::getCitasHoy() const {
    std::time_t ahora = std::time(nullptr);
    std::tm* hoy = std::localtime(&ahora);
    
    std::vector<Cita> resultados;
    for (const auto& cita : citas) {
        std::time_t fechaCita = cita.getFechaHora();
        std::tm* fechaCitaTm = std::localtime(&fechaCita);
        
        if (hoy->tm_year == fechaCitaTm->tm_year &&
            hoy->tm_mon == fechaCitaTm->tm_mon &&
            hoy->tm_mday == fechaCitaTm->tm_mday) {
            resultados.push_back(cita);
        }
    }
    
    return resultados;
}

std::vector<Cita> Hospital::getCitasPendientes() const {
    std::vector<Cita> resultados;
    for (const auto& cita : citas) {
        if (cita.estaActiva()) {
            resultados.push_back(cita);
        }
    }
    return resultados;
}

std::vector<Cita> Hospital::getTodasCitas() const {
    return citas;
}

int Hospital::getCantidadCitas() const {
    return citas.size();
}

bool Hospital::existeCita(int idCita) const {
    return indiceCitas.find(idCita) != indiceCitas.end();
}

bool Hospital::tieneConflictoHorario(int idDoctor, std::time_t fechaHora, int duracion) const {
    std::time_t inicio = fechaHora;
    std::time_t fin = fechaHora + (duracion * 60); // Convertir minutos a segundos
    
    for (const auto& cita : citas) {
        if (cita.getIdDoctor() == idDoctor && cita.estaActiva()) {
            std::time_t inicioCita = cita.getFechaHora();
            std::time_t finCita = inicioCita + (cita.getDuracion() * 60);
            
            // Verificar superposición
            if ((inicio >= inicioCita && inicio < finCita) ||
                (fin > inicioCita && fin <= finCita) ||
                (inicio <= inicioCita && fin >= finCita)) {
                return true; // Hay conflicto
            }
        }
    }
    
    return false; // No hay conflicto
}

// Gestión de historiales médicos (implementaciones similares)
bool Hospital::agregarHistorial(const HistorialMedico& historial) {
    if (existeHistorial(historial.getId())) {
        std::cerr << "Error: Ya existe un historial con ID " << historial.getId() << ".\n";
        return false;
    }
    
    if (!historial.validarDatos()) {
        std::cerr << "Error: Datos del historial no válidos.\n";
        return false;
    }
    
    if (!existePaciente(historial.getIdPaciente())) {
        std::cerr << "Error: No existe paciente con ID " << historial.getIdPaciente() << ".\n";
        return false;
    }
    
    if (!existeDoctor(historial.getIdDoctor())) {
        std::cerr << "Error: No existe doctor con ID " << historial.getIdDoctor() << ".\n";
        return false;
    }
    
    historiales.push_back(historial);
    indiceHistoriales[historial.getId()] = historiales.size() - 1;
    
    if (historial.getId() >= proximoIDHistorial) {
        proximoIDHistorial = historial.getId() + 1;
    }
    
    return true;
}

bool Hospital::eliminarHistorial(int idHistorial) {
    auto it = indiceHistoriales.find(idHistorial);
    if (it == indiceHistoriales.end()) {
        std::cerr << "Error: No existe historial con ID " << idHistorial << ".\n";
        return false;
    }
    
    int index = it->second;
    historiales.erase(historiales.begin() + index);
    indiceHistoriales.erase(it);
    
    // Reindexar
    for (auto& pair : indiceHistoriales) {
        if (pair.second > index) {
            pair.second--;
        }
    }
    
    return true;
}

HistorialMedico* Hospital::buscarHistorial(int idHistorial) {
    auto it = indiceHistoriales.find(idHistorial);
    if (it != indiceHistoriales.end() && it->second < historiales.size()) {
        return &historiales[it->second];
    }
    return nullptr;
}

const HistorialMedico* Hospital::buscarHistorial(int idHistorial) const {
    auto it = indiceHistoriales.find(idHistorial);
    if (it != indiceHistoriales.end() && it->second < historiales.size()) {
        return &historiales[it->second];
    }
    return nullptr;
}

std::vector<HistorialMedico> Hospital::buscarHistorialesPorPaciente(int idPaciente) const {
    std::vector<HistorialMedico> resultados;
    for (const auto& historial : historiales) {
        if (historial.getIdPaciente() == idPaciente) {
            resultados.push_back(historial);
        }
    }
    return resultados;
}

HistorialMedico* Hospital::getUltimoHistorialPaciente(int idPaciente) {
    HistorialMedico* ultimo = nullptr;
    std::time_t ultimaFecha = 0;
    
    for (auto& historial : historiales) {
        if (historial.getIdPaciente() == idPaciente && 
            historial.getFechaCreacion() > ultimaFecha) {
            ultimo = &historial;
            ultimaFecha = historial.getFechaCreacion();
        }
    }
    
    return ultimo;
}

std::vector<HistorialMedico> Hospital::getTodosHistoriales() const {
    return historiales;
}

int Hospital::getCantidadHistoriales() const {
    return historiales.size();
}

bool Hospital::existeHistorial(int idHistorial) const {
    return indiceHistoriales.find(idHistorial) != indiceHistoriales.end();
}

// Gestión de cola de espera
void Hospital::agregarAColaEspera(int idPaciente) {
    if (existePaciente(idPaciente) && !pacienteEnEspera(idPaciente)) {
        colaEspera.push(idPaciente);
    }
}

int Hospital::atenderSiguientePaciente() {
    if (colaEspera.empty()) {
        return -1; // No hay pacientes en espera
    }
    
    int idPaciente = colaEspera.front();
    colaEspera.pop();
    return idPaciente;
}

int Hospital::getCantidadEnEspera() const {
    return colaEspera.size();
}

std::vector<int> Hospital::getColaEspera() const {
    std::vector<int> resultado;
    std::queue<int> temp = colaEspera;
    
    while (!temp.empty()) {
        resultado.push_back(temp.front());
        temp.pop();
    }
    
    return resultado;
}

bool Hospital::pacienteEnEspera(int idPaciente) const {
    std::queue<int> temp = colaEspera;
    while (!temp.empty()) {
        if (temp.front() == idPaciente) {
            return true;
        }
        temp.pop();
    }
    return false;
}

void Hospital::limpiarColaEspera() {
    while (!colaEspera.empty()) {
        colaEspera.pop();
    }
}

// Estadísticas y reportes
Hospital::EstadisticasHospital Hospital::obtenerEstadisticas() const {
    EstadisticasHospital stats;
    
    stats.totalPacientes = pacientes.size();
    stats.totalDoctores = doctores.size();
    stats.totalCitas = citas.size();
    stats.totalHistoriales = historiales.size();
    stats.citasHoy = getCitasHoy().size();
    stats.citasPendientes = getCitasPendientes().size();
    stats.pacientesEnEspera = colaEspera.size();
    stats.ocupacionPorcentaje = capacidadTotal > 0 ? 
        (static_cast<float>(pacientes.size()) / capacidadTotal) * 100.0f : 0.0f;
    
    // Citas por especialidad
    for (const auto& doctor : doctores) {
        std::string especialidad = doctor.getEspecialidad();
        int citasDoctor = buscarCitasPorDoctor(doctor.getId()).size();
        stats.citasPorEspecialidad[especialidad] += citasDoctor;
    }
    
    // Pacientes por grupo de edad
    for (const auto& paciente : pacientes) {
        int edad = paciente.getEdad();
        int grupo = (edad / 10) * 10; // Grupo por década
        stats.pacientesPorEdad[grupo]++;
    }
    
    return stats;
}

void Hospital::mostrarEstadisticas() const {
    EstadisticasHospital stats = obtenerEstadisticas();
    
    std::cout << "\n=== ESTADÍSTICAS DEL HOSPITAL ===\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Ocupación: " << stats.totalPacientes << "/" << capacidadTotal 
              << " (" << std::fixed << std::setprecision(1) << stats.ocupacionPorcentaje << "%)\n";
    std::cout << "\nTOTALES:\n";
    std::cout << "  Pacientes: " << stats.totalPacientes << "\n";
    std::cout << "  Doctores: " << stats.totalDoctores << "\n";
    std::cout << "  Citas: " << stats.totalCitas << "\n";
    std::cout << "  Historiales: " << stats.totalHistoriales << "\n";
    std::cout << "\nCITAS:\n";
    std::cout << "  Hoy: " << stats.citasHoy << "\n";
    std::cout << "  Pendientes: " << stats.citasPendientes << "\n";
    std::cout << "  Pacientes en espera: " << stats.pacientesEnEspera << "\n";
    
    if (!stats.citasPorEspecialidad.empty()) {
        std::cout << "\nCITAS POR ESPECIALIDAD:\n";
        for (const auto& pair : stats.citasPorEspecialidad) {
            std::cout << "  " << pair.first << ": " << pair.second << "\n";
        }
    }
    
    if (!stats.pacientesPorEdad.empty()) {
        std::cout << "\nPACIENTES POR EDAD:\n";
        for (const auto& pair : stats.pacientesPorEdad) {
            std::cout << "  " << pair.first << "-" << (pair.first + 9) << " años: " 
                      << pair.second << "\n";
        }
    }
    
    std::cout << "================================\n";
}

std::string Hospital::generarReporte(bool incluirPacientes, bool incluirDoctores, bool incluirCitas) const {
    std::stringstream reporte;
    
    reporte << "REPORTE DEL HOSPITAL: " << nombre << "\n";
    reporte << "Fecha: " << std::put_time(std::localtime(&std::time(nullptr)), "%d/%m/%Y %H:%M") << "\n";
    reporte << "========================================\n\n";
    
    EstadisticasHospital stats = obtenerEstadisticas();
    reporte << "RESUMEN GENERAL:\n";
    reporte << "  Pacientes registrados: " << stats.totalPacientes << "\n";
    reporte << "  Doctores activos: " << stats.totalDoctores << "\n";
    reporte << "  Citas totales: " << stats.totalCitas << "\n";
    reporte << "  Historiales médicos: " << stats.totalHistoriales << "\n";
    reporte << "  Ocupación: " << stats.ocupacionPorcentaje << "%\n\n";
    
    if (incluirPacientes && !pacientes.empty()) {
        reporte << "LISTA DE PACIENTES:\n";
        reporte << "====================\n";
        for (const auto& paciente : pacientes) {
            reporte << "ID: " << paciente.getId() 
                    << " | Nombre: " << paciente.getNombreCompleto()
                    << " | Edad: " << paciente.getEdad()
                    << " | Tel: " << paciente.getTelefono() << "\n";
        }
        reporte << "\n";
    }
    
    if (incluirDoctores && !doctores.empty()) {
        reporte << "LISTA DE DOCTORES:\n";
        reporte << "==================\n";
        for (const auto& doctor : doctores) {
            reporte << "ID: " << doctor.getId() 
                    << " | Nombre: " << doctor.getNombreCompleto()
                    << " | Especialidad: " << doctor.getEspecialidad()
                    << " | Tel: " << doctor.getTelefono() << "\n";
        }
        reporte << "\n";
    }
    
    if (incluirCitas && !citas.empty()) {
        reporte << "CITAS PROGRAMADAS:\n";
        reporte << "==================\n";
        for (const auto& cita : citas) {
            if (cita.estaActiva()) {
                reporte << "ID: " << cita.getId()
                        << " | Paciente: " << cita.getIdPaciente()
                        << " | Doctor: " << cita.getIdDoctor()
                        << " | Fecha: " << cita.getFechaHoraStr()
                        << " | Estado: " << cita.getEstadoStr() << "\n";
            }
        }
    }
    
    return reporte.str();
}

// Métodos de persistencia
bool Hospital::guardarEnArchivo(const std::string& ruta) const {
    std::ofstream archivo(ruta, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error: No se pudo abrir el archivo para guardar.\n";
        return false;
    }
    
    // Guardar metadatos del hospital
    size_t nombreLen = nombre.length();
    archivo.write(reinterpret_cast<const char*>(&nombreLen), sizeof(size_t));
    archivo.write(nombre.c_str(), nombreLen);
    
    size_t direccionLen = direccion.length();
    archivo.write(reinterpret_cast<const char*>(&direccionLen), sizeof(size_t));
    archivo.write(direccion.c_str(), direccionLen);
    
    size_t telefonoLen = telefono.length();
    archivo.write(reinterpret_cast<const char*>(&telefonoLen), sizeof(size_t));
    archivo.write(telefono.c_str(), telefonoLen);
    
    archivo.write(reinterpret_cast<const char*>(&capacidadTotal), sizeof(int));
    archivo.write(reinterpret_cast<const char*>(&proximoIDPaciente), sizeof(int));
    archivo.write(reinterpret_cast<const char*>(&proximoIDDoctor), sizeof(int));
    archivo.write(reinterpret_cast<const char*>(&proximoIDCita), sizeof(int));
    archivo.write(reinterpret_cast<const char*>(&proximoIDHistorial), sizeof(int));
    
    // Guardar pacientes
    size_t numPacientes = pacientes.size();
    archivo.write(reinterpret_cast<const char*>(&numPacientes), sizeof(size_t));
    for (const auto& paciente : pacientes) {
        std::string datos = paciente.toString();
        size_t len = datos.length();
        archivo.write(reinterpret_cast<const char*>(&len), sizeof(size_t));
        archivo.write(datos.c_str(), len);
    }
    
    // Guardar doctores (similar a pacientes)
    // Guardar citas (similar)
    // Guardar historiales (similar)
    
    // Guardar cola de espera
    std::vector<int> cola = getColaEspera();
    size_t colaSize = cola.size();
    archivo.write(reinterpret_cast<const char*>(&colaSize), sizeof(size_t));
    for (int id : cola) {
        archivo.write(reinterpret_cast<const char*>(&id), sizeof(int));
    }
    
    archivo.close();
    return archivo.good();
}

bool Hospital::cargarDesdeArchivo(const std::string& ruta) {
    std::ifstream archivo(ruta, std::ios::binary);
    if (!archivo) {
        std::cerr << "Error: No se pudo abrir el archivo para cargar.\n";
        return false;
    }
    
    limpiarSistema();
    
    // Cargar metadatos del hospital
    size_t nombreLen;
    archivo.read(reinterpret_cast<char*>(&nombreLen), sizeof(size_t));
    char* nombreBuffer = new char[nombreLen + 1];
    archivo.read(nombreBuffer, nombreLen);
    nombreBuffer[nombreLen] = '\0';
    nombre = nombreBuffer;
    delete[] nombreBuffer;
    
    // Similar para direccion y telefono...
    
    archivo.read(reinterpret_cast<char*>(&capacidadTotal), sizeof(int));
    archivo.read(reinterpret_cast<char*>(&proximoIDPaciente), sizeof(int));
    archivo.read(reinterpret_cast<char*>(&proximoIDDoctor), sizeof(int));
    archivo.read(reinterpret_cast<char*>(&proximoIDCita), sizeof(int));
    archivo.read(reinterpret_cast<char*>(&proximoIDHistorial), sizeof(int));
    
    // Cargar pacientes
    size_t numPacientes;
    archivo.read(reinterpret_cast<char*>(&numPacientes), sizeof(size_t));
    for (size_t i = 0; i < numPacientes; ++i) {
        size_t datosLen;
        archivo.read(reinterpret_cast<char*>(&datosLen), sizeof(size_t));
        char* datosBuffer = new char[datosLen + 1];
        archivo.read(datosBuffer, datosLen);
        datosBuffer[datosLen] = '\0';
        
        Paciente paciente;
        if (paciente.fromString(datosBuffer)) {
            agregarPaciente(paciente);
        }
        delete[] datosBuffer;
    }
    
    // Cargar otros datos similares...
    
    archivo.close();
    return archivo.good() && verificarConsistencia();
}

// Métodos de utilidad
void Hospital::mostrarInformacion() const {
    std::cout << "\n=== INFORMACIÓN DEL HOSPITAL ===\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Dirección: " << direccion << "\n";
    std::cout << "Teléfono: " << telefono << "\n";
    std::cout << "Capacidad: " << capacidadTotal << " pacientes\n";
    std::cout << "Ocupación: " << getOcupacionActual() << " pacientes\n";
    std::cout << "Próximos IDs:\n";
    std::cout << "  Pacientes: " << proximoIDPaciente << "\n";
    std::cout << "  Doctores: " << proximoIDDoctor << "\n";
    std::cout << "  Citas: " << proximoIDCita << "\n";
    std::cout << "  Historiales: " << proximoIDHistorial << "\n";
    std::cout << "===============================\n";
}

bool Hospital::estaLleno() const {
    return pacientes.size() >= capacidadTotal;
}

void Hospital::limpiarSistema() {
    pacientes.clear();
    doctores.clear();
    citas.clear();
    historiales.clear();
    indicePacientes.clear();
    indiceDoctores.clear();
    indiceCitas.clear();
    indiceHistoriales.clear();
    
    while (!colaEspera.empty()) {
        colaEspera.pop();
    }
    
    proximoIDPaciente = 1;
    proximoIDDoctor = 1;
    proximoIDCita = 1;
    proximoIDHistorial = 1;
}

bool Hospital::verificarConsistencia() const {
    // Verificar que todos los índices apunten a elementos válidos
    for (const auto& pair : indicePacientes) {
        if (pair.second >= pacientes.size()) {
            std::cerr << "Error: Índice de paciente inválido.\n";
            return false;
        }
        if (pacientes[pair.second].getId() != pair.first) {
            std::cerr << "Error: Inconsistencia en ID de paciente.\n";
            return false;
        }
    }
    
    // Verificar referencias en citas
    for (const auto& cita : citas) {
        if (!existePaciente(cita.getIdPaciente())) {
            std::cerr << "Error: Cita referencia paciente inexistente.\n";
            return false;
        }
        if (!existeDoctor(cita.getIdDoctor())) {
            std::cerr << "Error: Cita referencia doctor inexistente.\n";
            return false;
        }
    }
    
    // Verificar referencias en historiales
    for (const auto& historial : historiales) {
        if (!existePaciente(historial.getIdPaciente())) {
            std::cerr << "Error: Historial referencia paciente inexistente.\n";
            return false;
        }
        if (!existeDoctor(historial.getIdDoctor())) {
            std::cerr << "Error: Historial referencia doctor inexistente.\n";
            return false;
        }
    }
    
    return true;
}