// historial/operacionesHistorial.cpp
#include "operacionesHistorial.hpp"
#include "HistorialMedico.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include "../utilidades/Formatos.hpp"
#include <iostream>

void crearHistorialMedico() {
    std::cout << "\n=== CREAR HISTORIAL ===\n";
    int pac, doc, cit;
    char diag[500], trat[500];

    std::cout << "ID Paciente: "; std::cin >> pac;
    std::cout << "ID Doctor: "; std::cin >> doc;
    std::cout << "ID Cita: "; std::cin >> cit;
    std::cin.ignore();
    std::cout << "Diagnóstico: "; std::cin.getline(diag, 499);
    std::cout << "Tratamiento: "; std::cin.getline(trat, 499);

    // Obtener próximo ID desde archivo
    std::ifstream f(Rutas::HISTORIALES, std::ios::binary);
    ArchivoHeader header;
    f.read(reinterpret_cast<char*>(&header), sizeof(ArchivoHeader));
    f.close();
    int id = header.proximoID;

    HistorialMedico h(id, pac, doc, cit);
    h.setDiagnostico(diag);
    h.setTratamiento(trat);

    if (GestorArchivos::guardarRegistro(&h, sizeof(HistorialMedico), Rutas::HISTORIALES)) {
        std::cout << "✓ Historial creado con ID: " << id << "\n";
    }
    Formatos::pausar();
}

void verHistorialPorID() {}
void listarHistorialPaciente() {}