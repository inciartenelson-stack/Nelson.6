#ifndef VALIDACIONES_HPP
#define VALIDACIONES_HPP

#include <string>
#include <ctime>
#include <vector>
#include <set>

/**
 * @class Validaciones
 * @brief Clase utilitaria para validar datos en el sistema hospitalario
 * 
 * Esta clase proporciona métodos estáticos para validar diferentes tipos
 * de datos comunes en el sistema, como emails, teléfonos, fechas, números
 * de identificación, y otros datos relacionados con la gestión hospitalaria.
 */
class Validaciones {
public:
    /**
     * @brief Valida una dirección de email
     * @param email Email a validar
     * @return true si el email tiene formato válido, false en caso contrario
     * 
     * Valida que el email tenga el formato correcto (usuario@dominio.extension)
     * y que contenga caracteres válidos.
     */
    static bool validarEmail(const std::string& email);
    
    /**
     * @brief Valida un número de teléfono
     * @param telefono Teléfono a validar
     * @return true si el teléfono tiene formato válido, false en caso contrario
     * 
     * Valida números telefónicos nacionales e internacionales. Acepta formatos
     * con y sin código de país, espacios, guiones y paréntesis.
     */
    static bool validarTelefono(const std::string& telefono);
    
    /**
     * @brief Valida una cédula de identidad
     * @param cedula Cédula a validar
     * @return true si la cédula tiene formato válido, false en caso contrario
     * 
     * Valida el formato básico de cédulas. Para implementaciones específicas
     * por país, se deberían añadir métodos adicionales.
     */
    static bool validarCedula(const std::string& cedula);
    
    /**
     * @brief Valida un RUT chileno
     * @param rut RUT a validar
     * @return true si el RUT es válido, false en caso contrario
     * 
     * Valida el formato y dígito verificador de un RUT chileno.
     * Acepta formatos con y sin puntos ni guión.
     */
    static bool validarRUTChileno(const std::string& rut);
    
    /**
     * @brief Valida un DNI español
     * @param dni DNI a validar
     * @return true si el DNI es válido, false en caso contrario
     * 
     * Valida el formato y letra de un DNI español.
     */
    static bool validarDNIEspanol(const std::string& dni);
    
    /**
     * @brief Valida una fecha
     * @param dia Día del mes (1-31)
     * @param mes Mes del año (1-12)
     * @param año Año (ej: 2024)
     * @return true si la fecha es válida, false en caso contrario
     * 
     * Valida que la fecha sea real (considera meses de 28, 30 o 31 días
     * y años bisiestos).
     */
   static bool validarFecha(int dia, int mes, int anio);
    
    
    static bool validarFechaString(const std::string& fecha);
    
    /**
     * @brief Valida una hora
     * @param hora Hora (0-23)
     * @param minuto Minuto (0-59)
     * @param segundo Segundo (0-59, opcional)
     * @return true si la hora es válida, false en caso contrario
     */
    static bool validarHora(int hora, int minuto, int segundo = 0);
    
    /**
     * @brief Valida un nombre propio
     * @param nombre Nombre a validar
     * @return true si el nombre es válido, false en caso contrario
     * 
     * Valida que el nombre contenga solo letras, espacios y algunos
     * caracteres especiales comunes en nombres (guiones, apóstrofes).
     */
    static bool validarNombre(const std::string& nombre);
    
    /**
     * @brief Valida una dirección física
     * @param direccion Dirección a validar
     * @return true si la dirección tiene formato válido, false en caso contrario
     * 
     * Valida formatos básicos de direcciones postales.
     */
    static bool validarDireccion(const std::string& direccion);
    
    /**
     * @brief Valida un número de habitación
     * @param habitacion Número de habitación
     * @param piso Piso (opcional)
     * @param maxHabitacionesPorPiso Máximo de habitaciones por piso
     * @return true si la habitación es válida, false en caso contrario
     */
    static bool validarHabitacion(int habitacion, int piso = 0, int maxHabitacionesPorPiso = 20);
    
    /**
     * @brief Valida un código de seguro médico
     * @param codigoSeguro Código a validar
     * @return true si el código es válido, false en caso contrario
     * 
     * Valida formatos comunes de códigos de seguros médicos.
     */
    static bool validarCodigoSeguro(const std::string& codigoSeguro);
    
    /**
     * @brief Valida un número de historia clínica
     * @param numeroHC Número de historia clínica
     * @return true si el número es válido, false en caso contrario
     */
    static bool validarNumeroHistoriaClinica(const std::string& numeroHC);
    
    /**
     * @brief Valida una especialidad médica
     * @param especialidad Especialidad a validar
     * @return true si la especialidad es válida, false en caso contrario
     * 
     * Valida contra una lista predefinida de especialidades médicas válidas.
     */
    static bool validarEspecialidadMedica(const std::string& especialidad);
    
    /**
     * @brief Valida un código de medicamento
     * @param codigoMedicamento Código a validar
     * @return true si el código es válido, false en caso contrario
     * 
     * Valida códigos de medicamentos según sistemas comunes (ATC, etc.).
     */
    static bool validarCodigoMedicamento(const std::string& codigoMedicamento);
    
    /**
     * @brief Valida una dosis de medicamento
     * @param dosis Dosis a validar
     * @param unidad Unidad de medida (mg, ml, etc.)
     * @param maxDosis Dosis máxima permitida
     * @return true si la dosis es válida, false en caso contrario
     */
    static bool validarDosisMedicamento(double dosis, const std::string& unidad, double maxDosis = 10000.0);
    
    /**
     * @brief Valida un grupo sanguíneo
     * @param grupoSanguineo Grupo sanguíneo a validar
     * @return true si el grupo es válido, false en caso contrario
     * 
     * Valida grupos sanguíneos del sistema ABO y factor Rh.
     */
    static bool validarGrupoSanguineo(const std::string& grupoSanguineo);
    
    /**
     * @brief Valida una talla (altura) de persona
     * @param altura Altura en centímetros
     * @return true si la altura es válida, false en caso contrario
     */
    static bool validarAltura(double altura);
    
    /**
     * @brief Valida un peso corporal
     * @param peso Peso en kilogramos
     * @return true si el peso es válido, false en caso contrario
     */
    static bool validarPeso(double peso);
    
    /**
     * @brief Valida una temperatura corporal
     * @param temperatura Temperatura en grados Celsius
     * @return true si la temperatura es válida, false en caso contrario
     */
    static bool validarTemperatura(double temperatura);
    
    /**
     * @brief Valida presión arterial
     * @param sistolica Presión sistólica
     * @param diastolica Presión diastólica
     * @return true si las presiones son válidas, false en caso contrario
     */
    static bool validarPresionArterial(int sistolica, int diastolica);
    
    /**
     * @brief Valida frecuencia cardíaca
     * @param frecuencia Frecuencia en latidos por minuto
     * @return true si la frecuencia es válida, false en caso contrario
     */
    static bool validarFrecuenciaCardiaca(int frecuencia);
    
    /**
     * @brief Valida frecuencia respiratoria
     * @param frecuencia Frecuencia en respiraciones por minuto
     * @return true si la frecuencia es válida, false en caso contrario
     */
    static bool validarFrecuenciaRespiratoria(int frecuencia);
    
    /**
     * @brief Valida un nivel de glucosa en sangre
     * @param glucosa Nivel de glucosa en mg/dL
     * @return true si el nivel es válido, false en caso contrario
     */
    static bool validarGlucosaSangre(double glucosa);
    
    /**
     * @brief Valida un número de emergencia
     * @param numeroEmergencia Número a validar
     * @return true si el número es válido, false en caso contrario
     */
    static bool validarNumeroEmergencia(const std::string& numeroEmergencia);
    
    /**
     * @brief Valida un código postal
     * @param codigoPostal Código postal a validar
     * @param pais País para validación específica
     * @return true si el código postal es válido, false en caso contrario
     */
    static bool validarCodigoPostal(const std::string& codigoPostal, const std::string& pais = "general");
    
    /**
     * @brief Valida un NSS (Número de Seguridad Social)
     * @param nss Número a validar
     * @return true si el NSS es válido, false en caso contrario
     */
    static bool validarNSS(const std::string& nss);
    
    /**
     * @brief Valida un RFC mexicano
     * @param rfc RFC a validar
     * @return true si el RFC es válido, false en caso contrario
     */
    static bool validarRFCMexicano(const std::string& rfc);
    
    /**
     * @brief Obtiene la lista de especialidades médicas válidas
     * @param especialidades Vector donde se almacenarán las especialidades
     * @return Número de especialidades en la lista
     */
   static int obtenerEspecialidadesValidas(std::vector<std::string>& especialidades);
    
    /**
     * @brief Verifica si una fecha está en el pasado
     * @param fecha Fecha a verificar (timestamp)
     * @return true si la fecha está en el pasado, false en caso contrario
     */
    static bool esFechaPasada(std::time_t fecha);
    
    /**
     * @brief Verifica si una fecha está en el futuro
     * @param fecha Fecha a verificar (timestamp)
     * @return true si la fecha está en el futuro, false en caso contrario
     */
    static bool esFechaFutura(std::time_t fecha);
    
    /**
     * @brief Valida un rango de edades
     * @param edad Edad a validar
     * @param minEdad Edad mínima permitida
     * @param maxEdad Edad máxima permitida
     * @return true si la edad está en el rango válido, false en caso contrario
     */
    static bool validarEdad(int edad, int minEdad = 0, int maxEdad = 120);
    
    /**
     * @brief Valida un género
     * @param genero Género a validar (M, F, O)
     * @return true si el género es válido, false en caso contrario
     */
    static bool validarGenero(char genero);
    
    /**
     * @brief Valida un estado civil
     * @param estadoCivil Estado civil a validar
     * @return true si el estado civil es válido, false en caso contrario
     */
    static bool validarEstadoCivil(const std::string& estadoCivil);
    
    /**
     * @brief Valida un nivel de urgencia
     * @param urgencia Nivel de urgencia (1-5)
     * @return true si el nivel es válido, false en caso contrario
     */
    static bool validarNivelUrgencia(int urgencia);
    
    /**
     * @brief Valida un código de diagnóstico (CIE-10)
     * @param codigoCIE10 Código de diagnóstico
     * @return true si el código es válido, false en caso contrario
     */
    static bool validarCodigoCIE10(const std::string& codigoCIE10);
    
    /**
     * @brief Valida un número de licencia médica
     * @param licencia Número de licencia
     * @return true si la licencia es válida, false en caso contrario
     */
    static bool validarLicenciaMedica(const std::string& licencia);
    
    /**
     * @brief Sanitiza un string para entrada segura
     * @param entrada String a sanitizar
     * @return String sanitizado
     * 
     * Elimina caracteres peligrosos para prevenir inyecciones SQL y XSS.
     */
    static std::string sanitizarEntrada(const std::string& entrada);
    
    /**
     * @brief Verifica si un string contiene solo números
     * @param str String a verificar
     * @return true si contiene solo números, false en caso contrario
     */
    static bool esSoloNumeros(const std::string& str);
    
    /**
     * @brief Verifica si un string contiene solo letras
     * @param str String a verificar
     * @return true si contiene solo letras, false en caso contrario
     */
    static bool esSoloLetras(const std::string& str);
    
    /**
     * @brief Verifica si un string contiene solo letras y números
     * @param str String a verificar
     * @return true si contiene solo letras y números, false en caso contrario
     */
    static bool esAlfanumerico(const std::string& str);
    
    /**
     * @brief Verifica si una cadena está vacía o contiene solo espacios
     * @param str String a verificar
     * @return true si está vacía o contiene solo espacios, false en caso contrario
     */
    static bool estaVacio(const std::string& str);
    
    /**
     * @brief Verifica si una dirección IP es válida
     * @param ip Dirección IP a validar
     * @return true si la IP es válida, false en caso contrario
     */
    static bool validarIP(const std::string& ip);
    
    /**
     * @brief Verifica si una URL es válida
     * @param url URL a validar
     * @return true si la URL es válida, false en caso contrario
     */
    static bool validarURL(const std::string& url);
};

#endif // VALIDACIONES_HPP