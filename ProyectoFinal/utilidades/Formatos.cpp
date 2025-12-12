#include "Formatos.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <regex>
#include <limits>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// Limpiar pantalla
void Formatos::limpiarPantalla(const std::string& sistemaOperativo) {
    std::string comando;
    
    if (sistemaOperativo == "windows" || 
        (sistemaOperativo == "auto" && 
         #ifdef _WIN32
         true
         #else
         false
         #endif
        )) {
        system("cls");
    } else {
        system("clear");
    }
}

// Pausar ejecución
void Formatos::pausar(const std::string& mensaje) {
    std::cout << "\n" << mensaje;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Mostrar mensajes con colores
void Formatos::mostrarError(const std::string& mensaje) {
    std::cout << colorizar("[ERROR] ", ROJO, NEGRITA) 
              << colorizar(mensaje, ROJO) << "\n";
}

void Formatos::mostrarExito(const std::string& mensaje) {
    std::cout << colorizar("[ÉXITO] ", VERDE, NEGRITA) 
              << colorizar(mensaje, VERDE) << "\n";
}

void Formatos::mostrarAdvertencia(const std::string& mensaje) {
    std::cout << colorizar("[ADVERTENCIA] ", AMARILLO, NEGRITA) 
              << colorizar(mensaje, AMARILLO) << "\n";
}

void Formatos::mostrarInfo(const std::string& mensaje) {
    std::cout << colorizar("[INFO] ", CYAN, NEGRITA) 
              << colorizar(mensaje, CYAN) << "\n";
}

// Encabezados y separadores
void Formatos::encabezado(const std::string& titulo, int ancho, char caracter) {
    std::cout << "\n";
    separador(ancho, caracter);
    std::cout << centrarTexto(titulo, ancho) << "\n";
    separador(ancho, caracter);
    std::cout << "\n";
}

void Formatos::piePagina(const std::string& mensaje, int ancho, char caracter) {
    std::cout << "\n";
    separador(ancho, caracter);
    std::cout << centrarTexto(mensaje, ancho) << "\n";
    separador(ancho, caracter);
}

void Formatos::separador(int ancho, char caracter) {
    std::cout << std::string(ancho, caracter) << "\n";
}

// Menús
int Formatos::mostrarMenu(const std::string& titulo, 
                         const std::vector<std::string>& opciones, 
                         bool incluirSalir) {
    encabezado(titulo);
    
    if (incluirSalir) {
        std::cout << "  0. " << colorizar("Salir", ROJO) << "\n";
    }
    
    for (size_t i = 0; i < opciones.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << opciones[i] << "\n";
    }
    
    separador();
    
    int opcion;
    while (true) {
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            mostrarError("Entrada inválida. Ingrese un número.");
            continue;
        }
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        int maxOpcion = opciones.size();
        if (incluirSalir) {
            if (opcion == 0) return 0;
            if (opcion >= 1 && opcion <= maxOpcion) return opcion;
        } else {
            if (opcion >= 1 && opcion <= maxOpcion) return opcion;
        }
        
        mostrarError("Opción fuera de rango. Intente nuevamente.");
    }
}

// Tablas
void Formatos::mostrarTabla(const std::string& titulo,
                           const std::vector<std::string>& encabezados,
                           const std::vector<std::vector<std::string>>& datos,
                           const std::vector<Alineacion>& alineaciones) {
    if (encabezados.empty()) return;
    
    // Calcular anchos de columnas
    std::vector<int> anchos(encabezados.size(), 0);
    
    for (size_t i = 0; i < encabezados.size(); ++i) {
        anchos[i] = std::max(anchos[i], static_cast<int>(encabezados[i].length()));
    }
    
    for (const auto& fila : datos) {
        for (size_t i = 0; i < std::min(fila.size(), anchos.size()); ++i) {
            anchos[i] = std::max(anchos[i], static_cast<int>(fila[i].length()));
        }
    }
    
    // Añadir padding
    for (auto& ancho : anchos) {
        ancho += 4;
    }
    
    // Mostrar título
    if (!titulo.empty()) {
        int anchoTotal = 0;
        for (int ancho : anchos) anchoTotal += ancho;
        anchoTotal += encabezados.size() + 1; // Bordes
        
        encabezado(titulo, anchoTotal);
    }
    
    // Mostrar encabezados
    std::cout << "┌";
    for (size_t i = 0; i < encabezados.size(); ++i) {
        std::cout << std::string(anchos[i], '─');
        if (i < encabezados.size() - 1) std::cout << "┬";
    }
    std::cout << "┐\n";
    
    std::cout << "│";
    for (size_t i = 0; i < encabezados.size(); ++i) {
        Alineacion alineacion = (i < alineaciones.size()) ? alineaciones[i] : IZQUIERDA;
        std::string encabezado = colorizar(encabezados[i], AZUL, NEGRITA);
        std::cout << alinearTexto(encabezado, anchos[i], alineacion) << "│";
    }
    std::cout << "\n";
    
    // Separador
    std::cout << "├";
    for (size_t i = 0; i < encabezados.size(); ++i) {
        std::cout << std::string(anchos[i], '─');
        if (i < encabezados.size() - 1) std::cout << "┼";
    }
    std::cout << "┤\n";
    
    // Mostrar datos
    for (const auto& fila : datos) {
        std::cout << "│";
        for (size_t i = 0; i < encabezados.size(); ++i) {
            Alineacion alineacion = (i < alineaciones.size()) ? alineaciones[i] : IZQUIERDA;
            std::string valor = (i < fila.size()) ? fila[i] : "";
            std::cout << alinearTexto(valor, anchos[i], alineacion) << "│";
        }
        std::cout << "\n";
    }
    
    // Cierre
    std::cout << "└";
    for (size_t i = 0; i < encabezados.size(); ++i) {
        std::cout << std::string(anchos[i], '─');
        if (i < encabezados.size() - 1) std::cout << "┴";
    }
    std::cout << "┘\n";
}

// Formateo de fechas
std::string Formatos::formatearFecha(std::time_t timestamp, const std::string& formato) {
    if (timestamp == 0) return "No asignada";
    
    std::tm* tiempo = std::localtime(&timestamp);
    std::stringstream ss;
    ss << std::put_time(tiempo, formato.c_str());
    return ss.str();
}

std::string Formatos::formatearDuracion(long segundos) {
    long horas = segundos / 3600;
    long minutos = (segundos % 3600) / 60;
    long segs = segundos % 60;
    
    std::stringstream ss;
    if (horas > 0) ss << horas << "h ";
    if (minutos > 0 || horas > 0) ss << minutos << "m ";
    ss << segs << "s";
    
    return ss.str();
}

// Formateo de números
std::string Formatos::formatearMoneda(double cantidad, const std::string& simbolo, int decimales) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(decimales) << cantidad;
    std::string numero = ss.str();
    
    // Agregar separadores de miles
    size_t punto = numero.find('.');
    std::string parteEntera = (punto != std::string::npos) ? numero.substr(0, punto) : numero;
    std::string parteDecimal = (punto != std::string::npos) ? numero.substr(punto) : "";
    
    std::string resultado;
    int contador = 0;
    for (int i = parteEntera.length() - 1; i >= 0; --i) {
        resultado = parteEntera[i] + resultado;
        ++contador;
        if (contador == 3 && i > 0 && (parteEntera[i-1] != '-')) {
            resultado = "," + resultado;
            contador = 0;
        }
    }
    
    return simbolo + resultado + parteDecimal;
}

std::string Formatos::formatearNumero(long long numero, char separadorCaracter) {
    std::string str = std::to_string(numero);
    std::string resultado;
    int contador = 0;
    
    for (int i = str.length() - 1; i >= 0; --i) {
        resultado = str[i] + resultado;
        ++contador;
        if (contador == 3 && i > 0 && str[i-1] != '-') {
            resultado = separadorCaracter + resultado;
            contador = 0;
        }
    }
    
    return resultado;
}

std::string Formatos::formatearPorcentaje(double valor, int decimales) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(decimales) << (valor * 100) << "%";
    return ss.str();
}

// Manipulación de texto
std::string Formatos::truncarTexto(const std::string& texto, size_t maxLongitud) {
    if (texto.length() <= maxLongitud) return texto;
    if (maxLongitud <= 3) return texto.substr(0, maxLongitud);
    return texto.substr(0, maxLongitud - 3) + "...";
}

std::string Formatos::centrarTexto(const std::string& texto, int ancho, char relleno) {
    return alinearTexto(texto, ancho, CENTRO, relleno);
}

std::string Formatos::alinearTexto(const std::string& texto, int ancho, 
                                  Alineacion alineacion, char relleno) {
    if (texto.length() >= ancho) return texto.substr(0, ancho);
    
    int espacios = ancho - texto.length();
    
    switch (alineacion) {
        case IZQUIERDA:
            return texto + std::string(espacios, relleno);
        case CENTRO:
            return std::string(espacios / 2, relleno) + texto + 
                   std::string(espacios - espacios / 2, relleno);
        case DERECHA:
            return std::string(espacios, relleno) + texto;
        default:
            return texto;
    }
}

// Colores (solo funciona en terminales que soportan ANSI)
std::string Formatos::colorizar(const std::string& texto, Color color, Estilo estilo) {
    #ifdef _WIN32
        // Windows necesita configuración especial para ANSI
        static bool windowsAnsiEnabled = false;
        if (!windowsAnsiEnabled) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD mode;
            GetConsoleMode(hConsole, &mode);
            SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            windowsAnsiEnabled = true;
        }
    #endif
    
    std::stringstream ss;
    ss << "\033[" << estilo << ";" << color << "m" << texto << "\033[0m";
    return ss.str();
}

// Solicitud de entrada con validación
std::string Formatos::solicitarTexto(const std::string& mensaje, 
                                    bool requerido,
                                    size_t minLongitud,
                                    size_t maxLongitud) {
    std::string entrada;
    
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, entrada);
        
        entrada = trim(entrada);
        
        if (entrada.empty() && requerido) {
            mostrarError("Este campo es obligatorio.");
            continue;
        }
        
        if (!entrada.empty()) {
            if (minLongitud > 0 && entrada.length() < minLongitud) {
                mostrarError("El texto debe tener al menos " + 
                           std::to_string(minLongitud) + " caracteres.");
                continue;
            }
            
            if (maxLongitud > 0 && entrada.length() > maxLongitud) {
                mostrarError("El texto no puede exceder " + 
                           std::to_string(maxLongitud) + " caracteres.");
                continue;
            }
        }
        
        break;
    }
    
    return entrada;
}

int Formatos::solicitarEntero(const std::string& mensaje, 
                             int min, 
                             int max,
                             int valorPorDefecto) {
    std::string entrada;
    int valor;
    
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, entrada);
        
        entrada = trim(entrada);
        
        if (entrada.empty()) {
            return valorPorDefecto;
        }
        
        try {
            valor = std::stoi(entrada);
        } catch (const std::exception&) {
            mostrarError("Por favor ingrese un número entero válido.");
            continue;
        }
        
        if (valor < min || valor > max) {
            mostrarError("El valor debe estar entre " + std::to_string(min) + 
                       " y " + std::to_string(max) + ".");
            continue;
        }
        
        break;
    }
    
    return valor;
}

double Formatos::solicitarDecimal(const std::string& mensaje,
                                 double min,
                                 double max,
                                 int decimales,
                                 double valorPorDefecto) {
    std::string entrada;
    double valor;
    
    while (true) {
        std::cout << mensaje;
        std::getline(std::cin, entrada);
        
        entrada = trim(entrada);
        
        if (entrada.empty()) {
            return valorPorDefecto;
        }
        
        try {
            valor = std::stod(entrada);
        } catch (const std::exception&) {
            mostrarError("Por favor ingrese un número decimal válido.");
            continue;
        }
        
        if (valor < min || valor > max) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(decimales);
            ss << "El valor debe estar entre " << min << " y " << max << ".";
            mostrarError(ss.str());
            continue;
        }
        
        break;
    }
    
    return valor;
}

std::time_t Formatos::solicitarFecha(const std::string& mensaje,
                                    bool permitirPasado,
                                    bool permitirFuturo) {
    std::time_t ahora = std::time(nullptr);
    
    std::cout << mensaje << " (Formato: DD/MM/AAAA HH:MM o Enter para ahora)\n";
    
    while (true) {
        std::string entrada = solicitarTexto("> ");
        
        if (entrada.empty()) {
            return ahora;
        }
        
        // Parsear fecha
        std::tm tm = {};
        std::stringstream ss(entrada);
        ss >> std::get_time(&tm, "%d/%m/%Y %H:%M");
        
        if (ss.fail()) {
            mostrarError("Formato de fecha inválido. Use DD/MM/AAAA HH:MM");
            continue;
        }
        
        std::time_t fecha = std::mktime(&tm);
        
        if (!permitirPasado && fecha < ahora) {
            mostrarError("No se permiten fechas en el pasado.");
            continue;
        }
        
        if (!permitirFuturo && fecha > ahora) {
            mostrarError("No se permiten fechas en el futuro.");
            continue;
        }
        
        return fecha;
    }
}

// Elementos de UI
void Formatos::mostrarProgreso(double progreso, int ancho, bool mostrarPorcentaje) {
    progreso = std::max(0.0, std::min(1.0, progreso));
    int completado = static_cast<int>(progreso * ancho);
    
    std::cout << "\r[";
    for (int i = 0; i < ancho; ++i) {
        if (i < completado) {
            std::cout << colorizar("█", VERDE);
        } else {
            std::cout << " ";
        }
    }
    std::cout << "]";
    
    if (mostrarPorcentaje) {
        std::cout << " " << std::fixed << std::setprecision(1) << (progreso * 100) << "%";
    }
    
    std::cout.flush();
    
    if (progreso >= 1.0) {
        std::cout << "\n";
    }
}

void Formatos::spinner(bool activo, const std::string& mensaje) {
    static int contador = 0;
    static const char spinners[] = {'|', '/', '-', '\\'};
    
    if (activo) {
        std::cout << "\r" << mensaje << " " << spinners[contador % 4] << " ";
        std::cout.flush();
        contador++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } else {
        std::cout << "\r" << std::string(mensaje.length() + 3, ' ') << "\r";
    }
}

bool Formatos::confirmar(const std::string& mensaje, bool valorPorDefecto) {
    std::string opciones = valorPorDefecto ? " (S/n)" : " (s/N)";
    
    while (true) {
        std::string entrada = solicitarTexto(mensaje + opciones + ": ");
        entrada = aMinusculas(trim(entrada));
        
        if (entrada.empty()) {
            return valorPorDefecto;
        }
        
        if (entrada == "s" || entrada == "si" || entrada == "sí" || entrada == "y" || entrada == "yes") {
            return true;
        }
        
        if (entrada == "n" || entrada == "no") {
            return false;
        }
        
        mostrarError("Por favor ingrese 's' para Sí o 'n' para No.");
    }
}

// Validaciones
bool Formatos::validarEmail(const std::string& email) {
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    return std::regex_match(email, pattern);
}

bool Formatos::validarTelefono(const std::string& telefono) {
    // Eliminar espacios, guiones, paréntesis
    std::string limpio;
    for (char c : telefono) {
        if (std::isdigit(c)) {
            limpio += c;
        }
    }
    
    // Validar longitud básica (entre 7 y 15 dígitos)
    return limpio.length() >= 7 && limpio.length() <= 15;
}

bool Formatos::validarCedula(const std::string& cedula, const std::string& pais) {
    if (cedula.empty()) return false;
    
    // Validación básica: solo dígitos y longitud mínima
    for (char c : cedula) {
        if (!std::isdigit(c) && c != '-' && c != '.') {
            return false;
        }
    }
    
    // Eliminar caracteres no numéricos
    std::string numeros;
    for (char c : cedula) {
        if (std::isdigit(c)) {
            numeros += c;
        }
    }
    
    if (numeros.length() < 5) return false;
    
    // Reglas específicas por país (ejemplo básico)
    if (pais == "cl") { // Chile - RUT
        if (numeros.length() < 7 || numeros.length() > 9) return false;
        // Aquí iría el algoritmo de verificación del dígito verificador
    }
    
    return true;
}

// Manipulación de strings
std::string Formatos::capitalizar(const std::string& texto) {
    if (texto.empty()) return texto;
    
    std::string resultado = texto;
    resultado[0] = std::toupper(resultado[0]);
    
    for (size_t i = 1; i < resultado.length(); ++i) {
        if (resultado[i-1] == ' ') {
            resultado[i] = std::toupper(resultado[i]);
        } else {
            resultado[i] = std::tolower(resultado[i]);
        }
    }
    
    return resultado;
}

std::string Formatos::aMinusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return resultado;
}

std::string Formatos::aMayusculas(const std::string& texto) {
    std::string resultado = texto;
    std::transform(resultado.begin(), resultado.end(), resultado.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return resultado;
}

std::string Formatos::trim(const std::string& texto) {
    size_t inicio = texto.find_first_not_of(" \t\n\r\f\v");
    if (inicio == std::string::npos) return "";
    
    size_t fin = texto.find_last_not_of(" \t\n\r\f\v");
    return texto.substr(inicio, fin - inicio + 1);
}

std::vector<std::string> Formatos::split(const std::string& texto, char delimitador) {
    std::vector<std::string> partes;
    std::stringstream ss(texto);
    std::string parte;
    
    while (std::getline(ss, parte, delimitador)) {
        partes.push_back(trim(parte));
    }
    
    return partes;
}

std::string Formatos::join(const std::vector<std::string>& partes, char delimitador) {
    std::stringstream ss;
    for (size_t i = 0; i < partes.size(); ++i) {
        if (i > 0) ss << delimitador;
        ss << partes[i];
    }
    return ss.str();
}