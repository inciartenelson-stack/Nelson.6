#ifndef FORMATOS_HPP
#define FORMATOS_HPP

#include <string>
#include <vector>
#include <ctime>


class Formatos {
public:
    // Colores para consola (ANSI escape codes)
    enum Color {
        RESET = 0,
        NEGRO = 30,
        ROJO = 31,
        VERDE = 32,
        AMARILLO = 33,
        AZUL = 34,
        MAGENTA = 35,
        CYAN = 36,
        BLANCO = 37,
        FONDO_ROJO = 41,
        FONDO_VERDE = 42,
        FONDO_AMARILLO = 43,
        FONDO_AZUL = 44,
        FONDO_MAGENTA = 45,
        FONDO_CYAN = 46,
        FONDO_BLANCO = 47
    };
    
    // Estilos de texto
    enum Estilo {
        NORMAL = 0,
        NEGRITA = 1,
        TENUE = 2,
        CURSIVA = 3,
        SUBRAYADO = 4
    };
    
    // Alineación para texto
    enum Alineacion {
        IZQUIERDA,
        CENTRO,
        DERECHA
    };

    /**
     * @brief Limpia la pantalla de la consola
     * @param sistemaOperativo SO para usar el comando correcto (windows/linux/macos)
     */
    static void limpiarPantalla(const std::string& sistemaOperativo = "auto");
    
    /**
     * @brief Pausa la ejecución hasta que el usuario presione una tecla
     * @param mensaje Mensaje opcional a mostrar
     */
    static void pausar(const std::string& mensaje = "Presione Enter para continuar...");
    
    /**
     * @brief Muestra un mensaje de error formateado
     * @param mensaje Mensaje de error a mostrar
     */
    static void mostrarError(const std::string& mensaje);
    
    /**
     * @brief Muestra un mensaje de éxito formateado
     * @param mensaje Mensaje de éxito a mostrar
     */
    static void mostrarExito(const std::string& mensaje);
    
    /**
     * @brief Muestra un mensaje de advertencia formateado
     * @param mensaje Mensaje de advertencia a mostrar
     */
    static void mostrarAdvertencia(const std::string& mensaje);
    
    /**
     * @brief Muestra un mensaje informativo formateado
     * @param mensaje Mensaje informativo a mostrar
     */
    static void mostrarInfo(const std::string& mensaje);
    
    /**
     * @brief Crea un encabezado centrado
     * @param titulo Título del encabezado
     * @param ancho Ancho total del encabezado
     * @param caracter Carácter para el borde
     */
    static void encabezado(const std::string& titulo, int ancho = 60, char caracter = '=');
    
    /**
     * @brief Crea un pie de página centrado
     * @param mensaje Mensaje del pie de página
     * @param ancho Ancho total del pie
     * @param caracter Carácter para el borde
     */
    static void piePagina(const std::string& mensaje, int ancho = 60, char caracter = '-');
    
    /**
     * @brief Crea una línea separadora
     * @param ancho Longitud de la línea
     * @param caracter Carácter a usar para la línea
     */
    static void separador(int ancho = 60, char caracter = '-');
    
    /**
     * @brief Muestra un menú de opciones numeradas
     * @param titulo Título del menú
     * @param opciones Vector de strings con las opciones
     * @param incluirSalir Si se debe incluir opción "0. Salir"
     * @return Opción seleccionada por el usuario
     */
    static int mostrarMenu(const std::string& titulo, 
                          const std::vector<std::string>& opciones, 
                          bool incluirSalir = true);
    
    /**
     * @brief Muestra una tabla de datos
     * @param titulo Título de la tabla
     * @param encabezados Vector con los encabezados de las columnas
     * @param datos Vector de vectores con los datos de cada fila
     * @param alineaciones Vector con alineación para cada columna
     */
    static void mostrarTabla(const std::string& titulo,
                            const std::vector<std::string>& encabezados,
                            const std::vector<std::vector<std::string>>& datos,
                            const std::vector<Alineacion>& alineaciones = {});
    
    /**
     * @brief Formatea una fecha/hora a string legible
     * @param timestamp Timestamp a formatear
     * @param formato Formato de salida (ver std::put_time)
     * @return String con la fecha formateada
     */
    static std::string formatearFecha(std::time_t timestamp, 
                                     const std::string& formato = "%d/%m/%Y %H:%M");
    
    /**
     * @brief Formatea una duración en segundos a string legible
     * @param segundos Duración en segundos
     * @return String formateado (ej: "2h 30m 15s")
     */
    static std::string formatearDuracion(long segundos);
    
    /**
     * @brief Formatea un número como moneda
     * @param cantidad Cantidad a formatear
     * @param simbolo Símbolo monetario (ej: "$")
     * @param decimales Número de decimales a mostrar
     * @return String con la cantidad formateada
     */
    static std::string formatearMoneda(double cantidad, 
                                       const std::string& simbolo = "$", 
                                       int decimales = 2);
    
    /**
     * @brief Formatea un número grande con separadores de miles
     * @param numero Número a formatear
     * @param separadorCaracter Carácter separador de miles
     * @return String con el número formateado
     */
    static std::string formatearNumero(long long numero, char separadorCaracter = ',');
    
    /**
     * @brief Formatea un porcentaje
     * @param valor Valor decimal (ej: 0.25 para 25%)
     * @param decimales Número de decimales a mostrar
     * @return String con el porcentaje formateado
     */
    static std::string formatearPorcentaje(double valor, int decimales = 1);
    
    /**
     * @brief Trunca un texto y agrega puntos suspensivos si es muy largo
     * @param texto Texto a truncar
     * @param maxLongitud Longitud máxima permitida
     * @return Texto truncado si es necesario
     */
    static std::string truncarTexto(const std::string& texto, size_t maxLongitud = 50);
    
    /**
     * @brief Centra un texto dentro de un ancho especificado
     * @param texto Texto a centrar
     * @param ancho Ancho total deseado
     * @param relleno Carácter de relleno
     * @return Texto centrado
     */
    static std::string centrarTexto(const std::string& texto, int ancho, char relleno = ' ');
    
    /**
     * @brief Alinea un texto a la izquierda, centro o derecha
     * @param texto Texto a alinear
     * @param ancho Ancho total deseado
     * @param alineacion Tipo de alineación
     * @param relleno Carácter de relleno
     * @return Texto alineado
     */
    static std::string alinearTexto(const std::string& texto, int ancho, 
                                   Alineacion alineacion, char relleno = ' ');
    
    /**
     * @brief Aplica color al texto en consola (si está soportado)
     * @param texto Texto a colorear
     * @param color Color del texto
     * @param estilo Estilo del texto
     * @return Texto con códigos ANSI (o sin ellos si no hay soporte)
     */
    static std::string colorizar(const std::string& texto, Color color = BLANCO, 
                                Estilo estilo = NORMAL);
    
    /**
     * @brief Solicita entrada de texto con validación
     * @param mensaje Mensaje a mostrar al usuario
     * @param requerido Si el campo es obligatorio
     * @param minLongitud Longitud mínima permitida (0 para no validar)
     * @param maxLongitud Longitud máxima permitida (0 para no validar)
     * @return Texto ingresado por el usuario
     */
    static std::string solicitarTexto(const std::string& mensaje, 
                                     bool requerido = false,
                                     size_t minLongitud = 0,
                                     size_t maxLongitud = 0);
    
    /**
     * @brief Solicita entrada de número entero con validación
     * @param mensaje Mensaje a mostrar al usuario
     * @param min Valor mínimo permitido
     * @param max Valor máximo permitido
     * @param valorPorDefecto Valor por defecto si se ingresa vacío
     * @return Número ingresado por el usuario
     */
    static int solicitarEntero(const std::string& mensaje, 
                              int min = INT_MIN, 
                              int max = INT_MAX,
                              int valorPorDefecto = 0);
    
    /**
     * @brief Solicita entrada de número decimal con validación
     * @param mensaje Mensaje a mostrar al usuario
     * @param min Valor mínimo permitido
     * @param max Valor máximo permitido
     * @param decimales Número de decimales a permitir
     * @param valorPorDefecto Valor por defecto si se ingresa vacío
     * @return Número ingresado por el usuario
     */
    static double solicitarDecimal(const std::string& mensaje,
                                  double min = -DBL_MAX,
                                  double max = DBL_MAX,
                                  int decimales = 2,
                                  double valorPorDefecto = 0.0);
    
    /**
     * @brief Solicita entrada de fecha con validación
     * @param mensaje Mensaje a mostrar al usuario
     * @param permitirPasado Si se permiten fechas en el pasado
     * @param permitirFuturo Si se permiten fechas en el futuro
     * @return Timestamp de la fecha ingresada
     */
    static std::time_t solicitarFecha(const std::string& mensaje,
                                     bool permitirPasado = true,
                                     bool permitirFuturo = true);
    
    /**
     * @brief Muestra una barra de progreso en consola
     * @param progreso Progreso actual (0.0 a 1.0)
     * @param ancho Ancho de la barra en caracteres
     * @param mostrarPorcentaje Si se debe mostrar el porcentaje
     */
    static void mostrarProgreso(double progreso, int ancho = 50, 
                               bool mostrarPorcentaje = true);
    
    /**
     * @brief Crea un spinner animado (útil para operaciones en curso)
     * @param activo Si el spinner está activo (llamar en bucle)
     * @param mensaje Mensaje a mostrar junto al spinner
     */
    static void spinner(bool activo, const std::string& mensaje = "Procesando");
    
    /**
     * @brief Muestra una confirmación (Sí/No) al usuario
     * @param mensaje Mensaje de confirmación
     * @param valorPorDefecto Valor por defecto (true=Sí, false=No)
     * @return true si el usuario seleccionó Sí, false si seleccionó No
     */
    static bool confirmar(const std::string& mensaje, bool valorPorDefecto = true);
    
    /**
     * @brief Valida un email con formato básico
     * @param email Email a validar
     * @return true si el email tiene formato válido
     */
    static bool validarEmail(const std::string& email);
    
    /**
     * @brief Valida un número de teléfono
     * @param telefono Número de teléfono a validar
     * @return true si el teléfono tiene formato válido
     */
    static bool validarTelefono(const std::string& telefono);
    
    /**
     * @brief Valida una cédula/RUT/DNI según el país
     * @param cedula Número de identificación a validar
     * @param pais Código de país para reglas específicas
     * @return true si la cédula es válida
     */
    static bool validarCedula(const std::string& cedula, const std::string& pais = "general");
    
    /**
     * @brief Capitaliza un string (primera letra en mayúscula)
     * @param texto Texto a capitalizar
     * @return Texto capitalizado
     */
    static std::string capitalizar(const std::string& texto);
    
    /**
     * @brief Convierte un string a minúsculas
     * @param texto Texto a convertir
     * @return Texto en minúsculas
     */
    static std::string aMinusculas(const std::string& texto);
    
    /**
     * @brief Convierte un string a mayúsculas
     * @param texto Texto a convertir
     * @return Texto en mayúsculas
     */
    static std::string aMayusculas(const std::string& texto);
    
    /**
     * @brief Elimina espacios en blanco al inicio y final
     * @param texto Texto a limpiar
     * @return Texto sin espacios al inicio/final
     */
    static std::string trim(const std::string& texto);
    
    /**
     * @brief Divide un string por un delimitador
     * @param texto Texto a dividir
     * @param delimitador Carácter delimitador
     * @return Vector de strings resultantes
     */
    static std::vector<std::string> split(const std::string& texto, char delimitador);
    
    /**
     * @brief Une un vector de strings con un delimitador
     * @param partes Vector de strings a unir
     * @param delimitador Carácter delimitador
     * @return String resultante
     */
    static std::string join(const std::vector<std::string>& partes, char delimitador);
};

#endif 