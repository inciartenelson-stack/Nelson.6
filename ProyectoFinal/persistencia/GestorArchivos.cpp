#include "GestorArchivos.hpp"
#include <iostream>
#include <cstdlib>
#include <cstring>

long GestorArchivos::calcularPosicion(int indice, size_t tamanoRegistro) {
    return sizeof(ArchivoHeader) + (indice * tamanoRegistro);
}

bool GestorArchivos::inicializarArchivo(const char* ruta, const char* tipo) {
    std::ofstream archivo(ruta, std::ios::binary);
    if (!archivo.is_open()) return false;

    ArchivoHeader header = {0, 1, 0, 3};
    archivo.write(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    archivo.close();
    std::cout << "✓ Archivo " << tipo << " inicializado: " << ruta << "\n";
    return true;
}

bool GestorArchivos::inicializarSistemaArchivos() {
    system("mkdir datos 2>nul");
    bool ok = true;
    ok &= inicializarArchivo(Rutas::HOSPITAL, "Hospital");
    ok &= inicializarArchivo(Rutas::PACIENTES, "Pacientes");
    ok &= inicializarArchivo(Rutas::DOCTORES, "Doctores");
    ok &= inicializarArchivo(Rutas::CITAS, "Citas");
    ok &= inicializarArchivo(Rutas::HISTORIALES, "Historiales");
    return ok;
}

bool GestorArchivos::guardarHospital(const void* hospital, size_t tamano) {
    std::ofstream archivo(Rutas::HOSPITAL, std::ios::binary);
    if (!archivo.is_open()) return false;
    archivo.write(static_cast<const char*>(hospital), tamano);
    archivo.close();
    return true;
}

bool GestorArchivos::cargarHospital(void* hospital, size_t tamano) {
    std::ifstream archivo(Rutas::HOSPITAL, std::ios::binary);
    if (!archivo.is_open()) return false;
    archivo.read(static_cast<char*>(hospital), tamano);
    archivo.close();
    return true;
}

bool GestorArchivos::guardarRegistro(const void* registro, size_t tamano, const char* archivo, int* nuevoID) {
    std::fstream f(archivo, std::ios::binary | std::ios::in | std::ios::out);
    if (!f.is_open()) return false;

    ArchivoHeader header;
    f.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    f.seekp(0, std::ios::end);
    f.write(static_cast<const char*>(registro), tamano);
    header.cantidadRegistros++;
    header.registrosActivos++;
    if (nuevoID) *nuevoID = header.proximoID;
    header.proximoID++;
    f.seekp(0);
    f.write(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    f.close();
    return true;
}

bool GestorArchivos::leerRegistroPorIndice(int indice, void* registro, size_t tamano, const char* archivo) {
    std::ifstream f(archivo, std::ios::binary);
    if (!f.is_open()) return false;
    ArchivoHeader header;
    f.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    if (indice < 0 || indice >= header.cantidadRegistros) { f.close(); return false; }
    f.seekg(calcularPosicion(indice, tamano));
    f.read(static_cast<char*>(registro), tamano);
    f.close();
    return true;
}

bool GestorArchivos::leerRegistroPorID(int id, void* registro, size_t tamano, const char* archivo) {
    std::ifstream f(archivo, std::ios::binary);
    if (!f.is_open()) return false;
    ArchivoHeader header;
    f.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    char* buffer = new char[tamano];
    for (int i = 0; i < header.cantidadRegistros; ++i) {
        f.seekg(calcularPosicion(i, tamano));
        f.read(buffer, tamano);
        // Suponemos que el primer campo de TODAS las entidades es un int "id"
        int registroID = *reinterpret_cast<int*>(buffer);
        if (registroID == id) {
            memcpy(registro, buffer, tamano);
            delete[] buffer;
            f.close();
            return true;
        }
    }
    delete[] buffer;
    f.close();
    return false;
}

bool GestorArchivos::listarTodosRegistros(void*& registros, int& cantidad, size_t tamano, const char* archivo) {
    std::ifstream f(archivo, std::ios::binary);
    if (!f.is_open()) { cantidad = 0; registros = nullptr; return false; }
    ArchivoHeader header;
    f.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    cantidad = header.cantidadRegistros;
    if (cantidad == 0) { registros = nullptr; f.close(); return true; }
    registros = new char[cantidad * tamano];
    for (int i = 0; i < cantidad; ++i) {
        f.seekg(calcularPosicion(i, tamano));
        f.read(static_cast<char*>(registros) + (i * tamano), tamano);
    }
    f.close();
    return true;
}