#include "HistorialMedico.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

// Constructor por defecto
HistorialMedico::HistorialMedico() 
    : id(0), idPaciente(0), idDoctor(0), idCita(0), 
      fechaCreacion(std::time(nullptr)), peso(0), altura(0), 
      temperatura(36.5), presionSistolica(120), presionDiastolica(80),
      frecuenciaCardiaca(72), frecuenciaRespiratoria(16) {}

// Constructor básico
HistorialMedico::HistorialMedico(int id, int idPaciente, int idDoctor, int idCita)
    : id(id), idPaciente(idPaciente), idDoctor(idDoctor), idCita(idCita),
      fechaCreacion(std::time(nullptr)), peso(0), altura(0), 
      temperatura(36.5), presionSistolica(120), presionDiastolica(80),
      frecuenciaCardiaca(72), frecuenciaRespiratoria(16) {}

// Constructor completo
HistorialMedico::HistorialMedico(int id, int idPaciente, int idDoctor, int idCita,
                                 const std::string& diagnostico, const std::string& tratamiento,
                                 std::time_t fechaCreacion)
    : id(id), idPaciente(idPaciente), idDoctor(idDoctor), idCita(idCita),
      fechaCreacion(fechaCreacion), diagnostico(diagnostico), tratamiento(tratamiento),
      peso(0), altura(0), temperatura(36.5), presionSistolica(120), 
      presionDiastolica(80), frecuenciaCardiaca(72), frecuenciaRespiratoria(16) {}

// Getters
int HistorialMedico::getId() const { return id; }
int HistorialMedico::getIdPaciente() const { return idPaciente; }
int HistorialMedico::getIdDoctor() const { return idDoctor; }
int HistorialMedico::getIdCita() const { return idCita; }
std::time_t HistorialMedico::getFechaCreacion() const { return fechaCreacion; }
std::string HistorialMedico::getDiagnostico() const { return diagnostico; }
std::string HistorialMedico::getTratamiento() const { return tratamiento; }
const std::vector<std::string>& HistorialMedico::getMedicamentos() const { return medicamentos; }
std::string HistorialMedico::getAlergias() const { return alergias; }
std::string HistorialMedico::getAntecedentes() const { return antecedentes; }
std::string HistorialMedico::getNotas() const { return notas; }
float HistorialMedico::getPeso() const { return peso; }
float HistorialMedico::getAltura() const { return altura; }
float HistorialMedico::getTemperatura() const { return temperatura; }
int HistorialMedico::getPresionSistolica() const { return presionSistolica; }
int HistorialMedico::getPresionDiastolica() const { return presionDiastolica; }
int HistorialMedico::getFrecuenciaCardiaca() const { return frecuenciaCardiaca; }
int HistorialMedico::getFrecuenciaRespiratoria() const { return frecuenciaRespiratoria; }

std::string HistorialMedico::getFechaCreacionStr() const {
    std::tm* tiempoLocal = std::localtime(&fechaCreacion);
    std::stringstream ss;
    ss << std::put_time(tiempoLocal, "%d/%m/%Y %H:%M");
    return ss.str();
}

float HistorialMedico::getIMC() const {
    if (altura <= 0) return 0.0f;
    return peso / (altura * altura);
}

std::string HistorialMedico::getPresionArterialStr() const {
    std::stringstream ss;
    ss << presionSistolica << "/" << presionDiastolica << " mmHg";
    return ss.str();
}

std::string HistorialMedico::getMedicamentosStr() const {
    if (medicamentos.empty()) return "Ninguno";
    
    std::stringstream ss;
    for (size_t i = 0; i < medicamentos.size(); ++i) {
        ss << medicamentos[i];
        if (i < medicamentos.size() - 1) ss << ", ";
    }
    return ss.str();
}

// Setters
void HistorialMedico::setId(int id) { this->id = id; }
void HistorialMedico::setIdPaciente(int idPaciente) { this->idPaciente = idPaciente; }
void HistorialMedico::setIdDoctor(int idDoctor) { this->idDoctor = idDoctor; }
void HistorialMedico::setIdCita(int idCita) { this->idCita = idCita; }
void HistorialMedico::setFechaCreacion(std::time_t fechaCreacion) { this->fechaCreacion = fechaCreacion; }
void HistorialMedico::setDiagnostico(const std::string& diagnostico) { this->diagnostico = diagnostico; }
void HistorialMedico::setTratamiento(const std::string& tratamiento) { this->tratamiento = tratamiento; }
void HistorialMedico::setAlergias(const std::string& alergias) { this->alergias = alergias; }
void HistorialMedico::setAntecedentes(const std::string& antecedentes) { this->antecedentes = antecedentes; }
void HistorialMedico::setNotas(const std::string& notas) { this->notas = notas; }
void HistorialMedico::setPeso(float peso) { this->peso = peso; }
void HistorialMedico::setAltura(float altura) { this->altura = altura; }
void HistorialMedico::setTemperatura(float temperatura) { this->temperatura = temperatura; }
void HistorialMedico::setPresionSistolica(int presionSistolica) { this->presionSistolica = presionSistolica; }
void HistorialMedico::setPresionDiastolica(int presionDiastolica) { this->presionDiastolica = presionDiastolica; }
void HistorialMedico::setFrecuenciaCardiaca(int frecuenciaCardiaca) { this->frecuenciaCardiaca = frecuenciaCardiaca; }
void HistorialMedico::setFrecuenciaRespiratoria(int frecuenciaRespiratoria) { this->frecuenciaRespiratoria = frecuenciaRespiratoria; }

// Métodos para gestionar medicamentos
void HistorialMedico::agregarMedicamento(const std::string& medicamento) {
    if (!medicamento.empty()) {
        medicamentos.push_back(medicamento);
    }
}

bool HistorialMedico::eliminarMedicamento(const std::string& medicamento) {
    auto it = std::find(medicamentos.begin(), medicamentos.end(), medicamento);
    if (it != medicamentos.end()) {
        medicamentos.erase(it);
        return true;
    }
    return false;
}

void HistorialMedico::limpiarMedicamentos() {
    medicamentos.clear();
}

bool HistorialMedico::contieneMedicamento(const std::string& medicamento) const {
    return std::find(medicamentos.begin(), medicamentos.end(), medicamento) != medicamentos.end();
}

bool HistorialMedico::validarDatos() const {
    // Validar IDs
    if (id <= 0) {
        std::cerr << "Error: ID de historial inválido (" << id << ").\n";
        return false;
    }
    
    if (idPaciente <= 0) {
        std::cerr << "Error: ID de paciente inválido (" << idPaciente << ").\n";
        return false;
    }
    
    if (idDoctor <= 0) {
        std::cerr << "Error: ID de doctor inválido (" << idDoctor << ").\n";
        return false;
    }
    
    // Validar diagnóstico
    if (diagnostico.empty()) {
        std::cerr << "Error: El diagnóstico no puede estar vacío.\n";
        return false;
    }
    
    // Validar valores fisiológicos
    if (peso < 0 || peso > 300) {
        std::cerr << "Error: Peso inválido (" << peso << " kg). Debe estar entre 0 y 300 kg.\n";
        return false;
    }
    
    if (altura < 0 || altura > 2.5) {
        std::cerr << "Error: Altura inválida (" << altura << " m). Debe estar entre 0 y 2.5 m.\n";
        return false;
    }
    
    if (temperatura < 30 || temperatura > 45) {
        std::cerr << "Error: Temperatura inválida (" << temperatura << " °C). Debe estar entre 30 y 45 °C.\n";
        return false;
    }
    
    if (presionSistolica < 50 || presionSistolica > 250) {
        std::cerr << "Error: Presión sistólica inválida (" << presionSistolica << "). Rango: 50-250 mmHg.\n";
        return false;
    }
    
    if (presionDiastolica < 30 || presionDiastolica > 150) {
        std::cerr << "Error: Presión diastólica inválida (" << presionDiastolica << "). Rango: 30-150 mmHg.\n";
        return false;
    }
    
    if (presionSistolica <= presionDiastolica) {
        std::cerr << "Error: Presión sistólica debe ser mayor que diastólica.\n";
        return false;
    }
    
    if (frecuenciaCardiaca < 30 || frecuenciaCardiaca > 200) {
        std::cerr << "Error: Frecuencia cardíaca inválida (" << frecuenciaCardiaca << " ppm). Rango: 30-200 ppm.\n";
        return false;
    }
    
    if (frecuenciaRespiratoria < 6 || frecuenciaRespiratoria > 60) {
        std::cerr << "Error: Frecuencia respiratoria inválida (" << frecuenciaRespiratoria << " rpm). Rango: 6-60 rpm.\n";
        return false;
    }
    
    return true;
}

bool HistorialMedico::signosVitalesNormales() const {
    return (temperatura >= 36.0 && temperatura <= 37.5) &&  // Temperatura normal
           (presionSistolica >= 90 && presionSistolica <= 120) &&  // Presión normal
           (presionDiastolica >= 60 && presionDiastolica <= 80) &&
           (frecuenciaCardiaca >= 60 && frecuenciaCardiaca <= 100) &&  // Frecuencia cardíaca normal
           (frecuenciaRespiratoria >= 12 && frecuenciaRespiratoria <= 20);  // Frecuencia respiratoria normal
}

std::string HistorialMedico::getClasificacionIMC() const {
    float imc = getIMC();
    
    if (imc <= 0) return "No calculable";
    if (imc < 18.5) return "Bajo peso";
    if (imc < 25.0) return "Peso normal";
    if (imc < 30.0) return "Sobrepeso";
    if (imc < 35.0) return "Obesidad grado I";
    if (imc < 40.0) return "Obesidad grado II";
    return "Obesidad grado III (mórbida)";
}

std::string HistorialMedico::generarResumen() const {
    std::stringstream ss;
    ss << "Historial #" << id << " - Paciente: " << idPaciente 
       << " - Fecha: " << getFechaCreacionStr() 
       << " - Diagnóstico: " << (diagnostico.length() > 50 ? diagnostico.substr(0, 47) + "..." : diagnostico);
    
    if (!signosVitalesNormales()) {
        ss << " [⚠️ SIGNOS VITALES ANORMALES]";
    }
    
    return ss.str();
}

void HistorialMedico::mostrarInformacion() const {
    std::cout << "\n=== HISTORIAL MÉDICO ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "ID Paciente: " << idPaciente << "\n";
    std::cout << "ID Doctor: " << idDoctor << "\n";
    std::cout << "ID Cita: " << (idCita > 0 ? std::to_string(idCita) : "N/A") << "\n";
    std::cout << "Fecha: " << getFechaCreacionStr() << "\n";
    std::cout << "------------------------------\n";
    
    // Signos vitales
    std::cout << "SIGNOS VITALES:\n";
    std::cout << "  Peso: " << peso << " kg\n";
    std::cout << "  Altura: " << altura << " m\n";
    if (altura > 0) {
        std::cout << "  IMC: " << std::fixed << std::setprecision(1) << getIMC() 
                  << " (" << getClasificacionIMC() << ")\n";
    }
    std::cout << "  Temperatura: " << temperatura << " °C\n";
    std::cout << "  Presión arterial: " << getPresionArterialStr() << "\n";
    std::cout << "  Frecuencia cardíaca: " << frecuenciaCardiaca << " ppm\n";
    std::cout << "  Frecuencia respiratoria: " << frecuenciaRespiratoria << " rpm\n";
    
    if (!signosVitalesNormales()) {
        std::cout << "  ⚠️  ALERTA: Signos vitales fuera de rango normal\n";
    }
    
    std::cout << "------------------------------\n";
    std::cout << "DIAGNÓSTICO:\n  " << diagnostico << "\n";
    std::cout << "TRATAMIENTO:\n  " << tratamiento << "\n";
    
    if (!medicamentos.empty()) {
        std::cout << "MEDICAMENTOS:\n";
        for (const auto& med : medicamentos) {
            std::cout << "  - " << med << "\n";
        }
    }
    
    if (!alergias.empty()) {
        std::cout << "ALERGIAS: " << alergias << "\n";
    }
    
    if (!antecedentes.empty()) {
        std::cout << "ANTECEDENTES: " << antecedentes << "\n";
    }
    
    if (!notas.empty()) {
        std::cout << "NOTAS ADICIONALES:\n  " << notas << "\n";
    }
    
    std::cout << "==============================\n";
}

void HistorialMedico::mostrarResumen() const {
    std::cout << generarResumen() << "\n";
}

std::string HistorialMedico::toString() const {
    std::stringstream ss;
    ss << id << "|" 
       << idPaciente << "|" 
       << idDoctor << "|" 
       << idCita << "|" 
       << fechaCreacion << "|" 
       << diagnostico << "|" 
       << tratamiento << "|";
    
    // Medicamentos separados por punto y coma
    for (size_t i = 0; i < medicamentos.size(); ++i) {
        ss << medicamentos[i];
        if (i < medicamentos.size() - 1) ss << ";";
    }
    ss << "|";
    
    ss << alergias << "|" 
       << antecedentes << "|" 
       << notas << "|" 
       << peso << "|" 
       << altura << "|" 
       << temperatura << "|" 
       << presionSistolica << "|" 
       << presionDiastolica << "|" 
       << frecuenciaCardiaca << "|" 
       << frecuenciaRespiratoria;
    
    return ss.str();
}

bool HistorialMedico::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;

    // Separar por pipe
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    // Debe tener exactamente 17 campos
    if (tokens.size() != 17) {
        std::cerr << "Error: Formato de datos inválido. Se esperaban 17 campos, se encontraron " 
                  << tokens.size() << ".\n";
        return false;
    }

    try {
        id = std::stoi(tokens[0]);
        idPaciente = std::stoi(tokens[1]);
        idDoctor = std::stoi(tokens[2]);
        idCita = std::stoi(tokens[3]);
        fechaCreacion = static_cast<std::time_t>(std::stoll(tokens[4]));
        diagnostico = tokens[5];
        tratamiento = tokens[6];
        
        // Medicamentos (separados por punto y coma)
        std::string medicamentosStr = tokens[7];
        if (!medicamentosStr.empty()) {
            std::stringstream medStream(medicamentosStr);
            std::string medicamento;
            while (std::getline(medStream, medicamento, ';')) {
                if (!medicamento.empty()) {
                    medicamentos.push_back(medicamento);
                }
            }
        }
        
        alergias = tokens[8];
        antecedentes = tokens[9];
        notas = tokens[10];
        peso = std::stof(tokens[11]);
        altura = std::stof(tokens[12]);
        temperatura = std::stof(tokens[13]);
        presionSistolica = std::stoi(tokens[14]);
        presionDiastolica = std::stoi(tokens[15]);
        frecuenciaCardiaca = std::stoi(tokens[16]);
        frecuenciaRespiratoria = std::stoi(tokens[17]);
        
        return validarDatos();
    } catch (const std::exception& e) {
        std::cerr << "Error al cargar historial médico desde string: " << e.what() << "\n";
        return false;
    }
}