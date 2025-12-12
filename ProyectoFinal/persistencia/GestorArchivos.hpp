#ifndef GESTOR_ARCHIVOS_HPP
#define GESTOR_ARCHIVOS_HPP

#include "Constantes.hpp"  // ← Solo esto
#include <cstddef>         // para size_t
#include <fstream>

class GestorArchivos {
private:
    static long calcularPosicion(int indice, size_t tamanoRegistro);

public:
    // Inicialización
    static bool inicializarSistemaArchivos();
    static bool inicializarArchivo(const char* ruta, const char* tipo);

    // Hospital (único registro)
    static bool guardarHospital(const void* hospital, size_t tamano);
    static bool cargarHospital(void* hospital, size_t tamano);

    // Métodos GENÉRICOS (requisito 6.6)
    static bool guardarRegistro(const void* registro, size_t tamano, const char* archivo, int* idGenerado = nullptr);
    static bool leerRegistroPorIndice(int indice, void* registro, size_t tamano, const char* archivo);
    static bool leerRegistroPorID(int id, void* registro, size_t tamano, const char* archivo);
    static bool listarTodosRegistros(void*& registros, int& cantidad, size_t tamano, const char* archivo);
};

#endif