#include "Validaciones.hpp"

// Versión mínima para compilar
bool Validaciones::validarTextoNoVacio(const char* texto) {
    if (texto == nullptr) return false;
    return texto[0] != '\0';
}