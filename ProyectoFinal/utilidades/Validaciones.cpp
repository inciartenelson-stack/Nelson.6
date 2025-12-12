#include "Validaciones.hpp"
#include <iostream>
#include <regex>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <ctime>
#include <vector>
#include <set>

// Valida email usando expresión regular
bool Validaciones::validarEmail(const std::string& email) {
    if (email.empty()) return false;
    
    // Expresión regular para validar email
    const std::regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return std::regex_match(email, pattern);
}

// Valida teléfono
bool Validaciones::validarTelefono(const std::string& telefono) {
    if (telefono.empty()) return false;
    
    // Eliminar espacios, guiones, paréntesis, etc.
    std::string numeros;
    for (char c : telefono) {
        if (std::isdigit(c)) {
            numeros += c;
        }
    }
    
    // Validar longitud (entre 7 y 15 dígitos para teléfonos internacionales)
    if (numeros.length() < 7 || numeros.length() > 15) {
        return false;
    }
    
    // Validar que todos los caracteres sean dígitos (ya lo hicimos)
    // y que no comience con 0 (en algunos países)
    if (numeros.length() > 0 && numeros[0] == '0') {
        // Aceptar que pueda comenzar con 0 (para números locales)
        // Podríamos hacer validaciones más específicas por país
    }
    
    return true;
}

// Valida cédula básica
bool Validaciones::validarCedula(const std::string& cedula) {
    if (cedula.empty()) return false;
    
    // Para cédulas genéricas: verificar que tenga al menos 5 dígitos
    // y que contenga solo dígitos y posiblemente guiones o puntos
    std::string numeros;
    for (char c : cedula) {
        if (std::isdigit(c)) {
            numeros += c;
        }
    }
    
    if (numeros.length() < 5) return false;
    
    // Verificar dígito verificador para algunos países
    // (implementación básica - se podría expandir)
    return true;
}

// Valida RUT chileno
bool Validaciones::validarRUTChileno(const std::string& rut) {
    if (rut.empty()) return false;
    
    std::string rutLimpio;
    for (char c : rut) {
        if (std::isdigit(c) || c == 'k' || c == 'K') {
            rutLimpio += std::toupper(c);
        }
    }
    
    if (rutLimpio.length() < 2) return false;
    
    // Separar número y dígito verificador
    std::string numeroStr = rutLimpio.substr(0, rutLimpio.length() - 1);
    char dv = rutLimpio[rutLimpio.length() - 1];
    
    // Convertir número a entero
    long long numero;
    try {
        numero = std::stoll(numeroStr);
    } catch (...) {
        return false;
    }
    
    // Calcular dígito verificador
    int m = 0, s = 1;
    for (; numero; numero /= 10) {
        s = (s + numero % 10 * (9 - m++ % 6)) % 11;
    }
    char dvCalculado = s ? s + 47 : 75; // '0'-'9' o 'K'
    
    return dv == dvCalculado;
}

// Valida DNI español
bool Validaciones::validarDNIEspanol(const std::string& dni) {
    if (dni.length() != 9) return false;
    
    std::string numeros = dni.substr(0, 8);
    char letra = std::toupper(dni[8]);
    
    if (!esSoloNumeros(numeros)) return false;
    
    // Tabla de correspondencia letra-número
    const std::string letras = "TRWAGMYFPDXBNJZSQVHLCKE";
    
    int numero;
    try {
        numero = std::stoi(numeros);
    } catch (...) {
        return false;
    }
    
    int indice = numero % 23;
    return letra == letras[indice];
}

// Valida fecha
bool Validaciones::validarFecha(int dia, int mes, int anio) {
    // Validar rango básico
    if (año < 1900 || anio > 2100) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > 31) return false;
    
    // Validar meses con 30 días
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) {
        return false;
    }
    
    // Validar febrero
    if (mes == 2) {
        // Verificar año bisiesto
        bool esBisiesto = (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
        if (esBisiesto && dia > 29) return false;
        if (!esBisiesto && dia > 28) return false;
    }
    
    return true;
}

// Valida fecha en formato string
bool Validaciones::validarFechaString(const std::string& fecha) {
    if (fecha.length() != 10) return false;
    if (fecha[2] != '/' || fecha[5] != '/') return false;
    
    try {
        int dia = std::stoi(fecha.substr(0, 2));
        int mes = std::stoi(fecha.substr(3, 2));
        int año = std::stoi(fecha.substr(6, 4));
        
        return validarFecha(dia, mes, año);
    } catch (...) {
        return false;
    }
}

// Valida hora
bool Validaciones::validarHora(int hora, int minuto, int segundo) {
    return (hora >= 0 && hora < 24) &&
           (minuto >= 0 && minuto < 60) &&
           (segundo >= 0 && segundo < 60);
}

// Valida nombre
bool Validaciones::validarNombre(const std::string& nombre) {
    if (nombre.empty()) return false;
    
    // Permitir letras, espacios, guiones y apóstrofes
    for (char c : nombre) {
        if (!std::isalpha(c) && c != ' ' && c != '-' && c != '\'' && c != '.' && c != ',') {
            return false;
        }
    }
    
    // Debe tener al menos una letra
    for (char c : nombre) {
        if (std::isalpha(c)) {
            return true;
        }
    }
    
    return false;
}

// Valida dirección
bool Validaciones::validarDireccion(const std::string& direccion) {
    if (direccion.empty()) return false;
    if (direccion.length() < 5) return false;
    
    // Debe contener al menos un número (para dirección postal)
    bool tieneNumero = false;
    for (char c : direccion) {
        if (std::isdigit(c)) {
            tieneNumero = true;
            break;
        }
    }
    
    if (!tieneNumero) return false;
    
    // Verificar caracteres válidos
    for (char c : direccion) {
        if (!std::isalnum(c) && c != ' ' && c != ',' && c != '.' && c != '#' && 
            c != '-' && c != '/' && c != 'º' && c != 'ª' && c != '°') {
            return false;
        }
    }
    
    return true;
}

// Valida habitación
bool Validaciones::validarHabitacion(int habitacion, int piso, int maxHabitacionesPorPiso) {
    if (habitacion <= 0) return false;
    
    if (piso > 0) {
        // Si se especifica piso, validar que la habitación corresponda
        int habitacionBase = piso * 100;
        if (habitacion < habitacionBase || habitacion >= habitacionBase + maxHabitacionesPorPiso) {
            return false;
        }
    }
    
    return true;
}

// Valida código de seguro
bool Validaciones::validarCodigoSeguro(const std::string& codigoSeguro) {
    if (codigoSeguro.empty()) return false;
    
    // Longitud típica de códigos de seguro
    if (codigoSeguro.length() < 6 || codigoSeguro.length() > 20) return false;
    
    // Debe contener letras y números
    return esAlfanumerico(codigoSeguro);
}

// Valida número de historia clínica
bool Validaciones::validarNumeroHistoriaClinica(const std::string& numeroHC) {
    if (numeroHC.empty()) return false;
    
    // Formato común: letras y números, generalmente con guiones
    for (char c : numeroHC) {
        if (!std::isalnum(c) && c != '-' && c != '/') {
            return false;
        }
    }
    
    return true;
}

// Valida especialidad médica
bool Validaciones::validarEspecialidadMedica(const std::string& especialidad) {
    if (especialidad.empty()) return false;
    
    // Lista de especialidades médicas válidas
    static const std::set<std::string> especialidadesValidas = {
        "Cardiología", "Pediatría", "Dermatología", "Neurología", 
        "Ginecología", "Obstetricia", "Oftalmología", "Ortopedia",
        "Psiquiatría", "Radiología", "Urología", "Endocrinología",
        "Gastroenterología", "Hematología", "Nefrología", "Neumología",
        "Oncología", "Reumatología", "Traumatología", "Medicina Interna",
        "Medicina Familiar", "Anestesiología", "Cirugía General",
        "Cirugía Plástica", "Dermatología", "Infectología"
    };
    
    // Convertir a mayúsculas para comparación case-insensitive
    std::string especialidadUpper = especialidad;
    std::transform(especialidadUpper.begin(), especialidadUpper.end(),
                  especialidadUpper.begin(), ::toupper);
    
    // Verificar si está en la lista
    for (const auto& esp : especialidadesValidas) {
        std::string espUpper = esp;
        std::transform(espUpper.begin(), espUpper.end(), espUpper.begin(), ::toupper);
        
        if (especialidadUpper == espUpper) {
            return true;
        }
    }
    
    return false;
}

// Valida código de medicamento
bool Validaciones::validarCodigoMedicamento(const std::string& codigoMedicamento) {
    if (codigoMedicamento.empty()) return false;
    
    // Códigos ATC tienen formato LNNNNNN donde L es letra y N es número
    // Ejemplo: N02BE01 (paracetamol)
    const std::regex atcPattern(R"(^[A-Z][0-9]{2}[A-Z][A-Z][0-9]{2}$)");
    
    return std::regex_match(codigoMedicamento, atcPattern);
}

// Valida dosis de medicamento
bool Validaciones::validarDosisMedicamento(double dosis, const std::string& unidad, double maxDosis) {
    if (dosis <= 0 || dosis > maxDosis) return false;
    
    // Validar unidad de medida
    static const std::set<std::string> unidadesValidas = {
        "mg", "g", "mcg", "ml", "L", "UI", "mmol", "mg/kg", "mg/m²"
    };
    
    std::string unidadLower = unidad;
    std::transform(unidadLower.begin(), unidadLower.end(), unidadLower.begin(), ::tolower);
    
    return unidadesValidas.find(unidadLower) != unidadesValidas.end();
}

// Valida grupo sanguíneo
bool Validaciones::validarGrupoSanguineo(const std::string& grupoSanguineo) {
    static const std::set<std::string> gruposValidos = {
        "A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"
    };
    
    std::string grupoUpper = grupoSanguineo;
    std::transform(grupoUpper.begin(), grupoUpper.end(), grupoUpper.begin(), ::toupper);
    
    return gruposValidos.find(grupoUpper) != gruposValidos.end();
}

// Valida altura
bool Validaciones::validarAltura(double altura) {
    return altura > 30 && altura < 250; // en cm
}

// Valida peso
bool Validaciones::validarPeso(double peso) {
    return peso > 0.5 && peso < 300; // en kg
}

// Valida temperatura
bool Validaciones::validarTemperatura(double temperatura) {
    return temperatura > 30 && temperatura < 45; // en °C
}

// Valida presión arterial
bool Validaciones::validarPresionArterial(int sistolica, int diastolica) {
    if (sistolica <= 0 || diastolica <= 0) return false;
    if (sistolica > 250 || diastolica > 150) return false;
    if (sistolica <= diastolica) return false; // La sistólica debe ser mayor
    
    return true;
}

// Valida frecuencia cardíaca
bool Validaciones::validarFrecuenciaCardiaca(int frecuencia) {
    return frecuencia >= 30 && frecuencia <= 200; // lpm
}

// Valida frecuencia respiratoria
bool Validaciones::validarFrecuenciaRespiratoria(int frecuencia) {
    return frecuencia >= 6 && frecuencia <= 60; // rpm
}

// Valida glucosa en sangre
bool Validaciones::validarGlucosaSangre(double glucosa) {
    return glucosa >= 20 && glucosa <= 600; // mg/dL
}

// Valida número de emergencia
bool Validaciones::validarNumeroEmergencia(const std::string& numeroEmergencia) {
    // Números de emergencia suelen ser cortos (911, 112, etc.)
    if (numeroEmergencia.empty()) return false;
    
    // Solo dígitos
    if (!esSoloNumeros(numeroEmergencia)) return false;
    
    // Longitud típica: 3-4 dígitos
    return numeroEmergencia.length() >= 2 && numeroEmergencia.length() <= 4;
}

// Valida código postal
bool Validaciones::validarCodigoPostal(const std::string& codigoPostal, const std::string& pais) {
    if (codigoPostal.empty()) return false;
    
    if (pais == "CL") { // Chile
        // Códigos postales chilenos: 7 dígitos
        if (codigoPostal.length() != 7) return false;
        return esSoloNumeros(codigoPostal);
    }
    else if (pais == "ES") { // España
        // Códigos postales españoles: 5 dígitos
        if (codigoPostal.length() != 5) return false;
        return esSoloNumeros(codigoPostal);
    }
    else if (pais == "MX") { // México
        // Códigos postales mexicanos: 5 dígitos
        if (codigoPostal.length() != 5) return false;
        return esSoloNumeros(codigoPostal);
    }
    else {
        // Validación genérica: entre 3 y 10 caracteres alfanuméricos
        return codigoPostal.length() >= 3 && codigoPostal.length() <= 10;
    }
}

// Valida NSS
bool Validaciones::validarNSS(const std::string& nss) {
    if (nss.empty()) return false;
    
    // Formato básico: 11 dígitos
    if (nss.length() != 11) return false;
    
    return esSoloNumeros(nss);
}

// Valida RFC mexicano
bool Validaciones::validarRFCMexicano(const std::string& rfc) {
    if (rfc.length() != 12 && rfc.length() != 13) return false;
    
    // Los primeros 4 caracteres deben ser letras
    for (int i = 0; i < 4; i++) {
        if (!std::isalpha(rfc[i])) return false;
    }
    
    // Los siguientes 6 deben ser números (fecha)
    for (int i = 4; i < 10; i++) {
        if (!std::isdigit(rfc[i])) return false;
    }
    
    // Los últimos pueden ser letras o números (homoclave)
    for (size_t i = 10; i < rfc.length(); i++) {
        if (!std::isalnum(rfc[i])) return false;
    }
    
    return true;
}

// Obtiene especialidades válidas
int Validaciones::obtenerEspecialidadesValidas(std::vector<std::string>& especialidades) {
    especialidades = {
        "Cardiología", "Pediatría", "Dermatología", "Neurología", 
        "Ginecología", "Obstetricia", "Oftalmología", "Ortopedia",
        "Psiquiatría", "Radiología", "Urología", "Endocrinología",
        "Gastroenterología", "Hematología", "Nefrología", "Neumología",
        "Oncología", "Reumatología", "Traumatología", "Medicina Interna",
        "Medicina Familiar", "Anestesiología", "Cirugía General",
        "Cirugía Plástica", "Dermatología", "Infectología"
    };
    
    return especialidades.size();
}

// Verifica si fecha está en el pasado
bool Validaciones::esFechaPasada(std::time_t fecha) {
    std::time_t ahora = std::time(nullptr);
    return fecha < ahora;
}

// Verifica si fecha está en el futuro
bool Validaciones::esFechaFutura(std::time_t fecha) {
    std::time_t ahora = std::time(nullptr);
    return fecha > ahora;
}

// Valida edad
bool Validaciones::validarEdad(int edad, int minEdad, int maxEdad) {
    return edad >= minEdad && edad <= maxEdad;
}

// Valida género
bool Validaciones::validarGenero(char genero) {
    char g = std::toupper(genero);
    return g == 'M' || g == 'F' || g == 'O'; // Masculino, Femenino, Otro
}

// Valida estado civil
bool Validaciones::validarEstadoCivil(const std::string& estadoCivil) {
    static const std::set<std::string> estadosValidos = {
        "Soltero", "Casado", "Divorciado", "Viudo", "Unión Libre", "Separado"
    };
    
    std::string estadoUpper = estadoCivil;
    std::transform(estadoUpper.begin(), estadoUpper.end(), estadoUpper.begin(), ::toupper);
    
    for (const auto& estado : estadosValidos) {
        std::string eUpper = estado;
        std::transform(eUpper.begin(), eUpper.end(), eUpper.begin(), ::toupper);
        
        if (estadoUpper == eUpper) {
            return true;
        }
    }
    
    return false;
}

// Valida nivel de urgencia
bool Validaciones::validarNivelUrgencia(int urgencia) {
    return urgencia >= 1 && urgencia <= 5; // Escala 1-5
}

// Valida código CIE-10
bool Validaciones::validarCodigoCIE10(const std::string& codigoCIE10) {
    if (codigoCIE10.empty()) return false;
    
    // Formato básico: letra seguida de 2-3 números, opcionalmente con punto y más números
    const std::regex ciePattern(R"(^[A-Z][0-9]{2}(\.[0-9]+)?$)");
    
    return std::regex_match(codigoCIE10, ciePattern);
}

// Valida licencia médica
bool Validaciones::validarLicenciaMedica(const std::string& licencia) {
    if (licencia.empty()) return false;
    
    // Generalmente alfanumérica, entre 6 y 15 caracteres
    if (licencia.length() < 6 || licencia.length() > 15) return false;
    
    return esAlfanumerico(licencia);
}

// Sanitiza entrada
std::string Validaciones::sanitizarEntrada(const std::string& entrada) {
    std::string sanitizada;
    
    for (char c : entrada) {
        // Permitir caracteres seguros
        if (std::isalnum(c) || c == ' ' || c == '.' || c == ',' || c == '-' || 
            c == '_' || c == '@' || c == '(' || c == ')' || c == '/' || c == '\\') {
            sanitizada += c;
        }
        // Escapar caracteres peligrosos
        else if (c == '\'' || c == '"' || c == ';' || c == '<' || c == '>') {
            sanitizada += '\\';
            sanitizada += c;
        }
    }
    
    return sanitizada;
}

// Verifica si string contiene solo números
bool Validaciones::esSoloNumeros(const std::string& str) {
    if (str.empty()) return false;
    
    for (char c : str) {
        if (!std::isdigit(c)) {
            return false;
        }
    }
    
    return true;
}

// Verifica si string contiene solo letras
bool Validaciones::esSoloLetras(const std::string& str) {
    if (str.empty()) return false;
    
    for (char c : str) {
        if (!std::isalpha(c) && c != ' ') {
            return false;
        }
    }
    
    return true;
}

// Verifica si string es alfanumérico
bool Validaciones::esAlfanumerico(const std::string& str) {
    if (str.empty()) return false;
    
    for (char c : str) {
        if (!std::isalnum(c)) {
            return false;
        }
    }
    
    return true;
}

// Verifica si string está vacío
bool Validaciones::estaVacio(const std::string& str) {
    for (char c : str) {
        if (!std::isspace(c)) {
            return false;
        }
    }
    
    return true;
}

// Valida dirección IP
bool Validaciones::validarIP(const std::string& ip) {
    const std::regex ipPattern(R"(^(\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3})$)");
    
    std::smatch match;
    if (!std::regex_match(ip, match, ipPattern)) {
        return false;
    }
    
    // Verificar que cada octeto esté entre 0 y 255
    for (int i = 1; i <= 4; i++) {
        int octeto = std::stoi(match[i]);
        if (octeto < 0 || octeto > 255) {
            return false;
        }
    }
    
    return true;
}

// Valida URL
bool Validaciones::validarURL(const std::string& url) {
    const std::regex urlPattern(R"(^(https?|ftp)://[^\s/$.?#].[^\s]*$)");
    return std::regex_match(url, urlPattern);
}