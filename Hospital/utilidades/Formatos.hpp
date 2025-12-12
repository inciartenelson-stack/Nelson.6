#ifndef FORMATOS_HPP
#define FORMATOS_HPP

class Formatos {
public:
    // Constructor y destructor
    Formatos();
    ~Formatos();
    
    // Métodos estáticos
    static void pausar(const char* mensaje = nullptr);
    static void limpiarBuffer();
    static void limpiarPantalla();
    
    // Nuevos métodos útiles
    static void mostrarSeparador();
    static void mostrarTitulo(const char* titulo);
};

#endif