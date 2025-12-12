#include "Paciente.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

// Constructor por defecto
Paciente::Paciente() : id(0), edad(0), genero(' ') {}

// Constructor con parámetros básicos
Paciente::Paciente(int id, const std::string& nombre, const std::string& apellido, const std::string& cedula)
    : id(id), nombre(nombre), apellido(apellido), cedula(cedula), edad(0), genero(' ') {}

// Constructor completo
Paciente::Paciente(int id, const std::string& nombre, const std::string& apellido, 
                   const std::string& cedula, int edad, char genero, 
                   const std::string& telefono, const std::string& email)
    : id(id), nombre(nombre), apellido(apellido), cedula(cedula), 
      edad(edad), genero(genero), telefono(telefono), email(email) {}

// Getters
int Paciente::getId() const { return id; }
std::string Paciente::getNombre() const { return nombre; }
std::string Paciente::getApellido() const { return apellido; }
std::string Paciente::getNombreCompleto() const { return nombre + " " + apellido; }
std::string Paciente::getCedula() const { return cedula; }
int Paciente::getEdad() const { return edad; }
char Paciente::getGenero() const { return genero; }
std::string Paciente::getTelefono() const { return telefono; }
std::string Paciente::getEmail() const { return email; }

// Setters
void Paciente::setId(int id) { this->id = id; }
void Paciente::setNombre(const std::string& nombre) { this->nombre = nombre; }
void Paciente::setApellido(const std::string& apellido) { this->apellido = apellido; }
void Paciente::setCedula(const std::string& cedula) { this->cedula = cedula; }
void Paciente::setEdad(int edad) { this->edad = edad; }
void Paciente::setGenero(char genero) { this->genero = genero; }
void Paciente::setTelefono(const std::string& telefono) { this->telefono = telefono; }
void Paciente::setEmail(const std::string& email) { this->email = email; }

bool Paciente::validarDatos() const {
    // Validar edad
    if (edad < 0 || edad > 120) {
        std::cerr << "Error: Edad inválida (" << edad << "). Debe estar entre 0 y 120 años.\n";
        return false;
    }

    // Validar género
    char gen = std::toupper(genero);
    if (gen != 'M' && gen != 'F' && gen != 'O') {
        std::cerr << "Error: Género inválido (" << genero << "). Use M, F u O.\n";
        return false;
    }

    // Validar cédula
    if (cedula.empty()) {
        std::cerr << "Error: La cédula no puede estar vacía.\n";
        return false;
    }

    // Validar email básico
    if (!email.empty()) {
        size_t atPos = email.find('@');
        size_t dotPos = email.find('.', atPos);
        
        if (atPos == std::string::npos || dotPos == std::string::npos || 
            atPos == 0 || dotPos - atPos < 2 || dotPos == email.length() - 1) {
            std::cerr << "Error: Email inválido (" << email << ").\n";
            return false;
        }
    }

    // Validar nombre y apellido
    if (nombre.empty() || apellido.empty()) {
        std::cerr << "Error: Nombre y apellido no pueden estar vacíos.\n";
        return false;
    }

    return true;
}

void Paciente::mostrarInformacion() const {
    std::cout << "\n=== INFORMACIÓN DEL PACIENTE ===\n";
    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << getNombreCompleto() << "\n";
    std::cout << "Cédula: " << cedula << "\n";
    std::cout << "Edad: " << edad << "\n";
    std::cout << "Género: " << genero << "\n";
    std::cout << "Teléfono: " << telefono << "\n";
    std::cout << "Email: " << email << "\n";
    std::cout << "=================================\n";
}

std::string Paciente::toString() const {
    std::stringstream ss;
    ss << id << "|" 
       << nombre << "|" 
       << apellido << "|" 
       << cedula << "|" 
       << edad << "|" 
       << genero << "|" 
       << telefono << "|" 
       << email;
    return ss.str();
}

bool Paciente::fromString(const std::string& data) {
    std::stringstream ss(data);
    std::string token;
    std::vector<std::string> tokens;

    // Separar por pipe
    while (std::getline(ss, token, '|')) {
        tokens.push_back(token);
    }

    // Debe tener exactamente 8 campos
    if (tokens.size() != 8) {
        return false;
    }

    try {
        id = std::stoi(tokens[0]);
        nombre = tokens[1];
        apellido = tokens[2];
        cedula = tokens[3];
        edad = std::stoi(tokens[4]);
        genero = tokens[5][0]; // Tomar primer carácter
        telefono = tokens[6];
        email = tokens[7];
        
        return validarDatos();
    } catch (const std::exception& e) {
        std::cerr << "Error al cargar paciente desde string: " << e.what() << "\n";
        return false;
    }
}