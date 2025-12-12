#include "Formatos.hpp"
#include <iostream>
#include <cstdlib>  // Para system()

using namespace std;

// Versión CORREGIDA - sin errores
void Formatos::pausar(const char* mensaje) {
    if (mensaje != nullptr) {
        cout << mensaje;
    } else {
        cout << "\nPresione ENTER para continuar...";
    }
    
    // Limpiar buffer y esperar Enter
    cin.clear();
    cin.ignore(10000, '\n');
}

void Formatos::limpiarBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

void Formatos::limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}