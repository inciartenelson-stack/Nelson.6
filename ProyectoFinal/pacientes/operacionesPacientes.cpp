// pacientes/operacionesPacientes.cpp
#include "Paciente.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"  // ← solo para Rutas::

void registrarPaciente(Hospital& hospital) {
    // ... (entrada de datos)

    int nuevoID = hospital.generarNuevoIDPaciente();
    Paciente p(nuevoID, nombre, apellido, cedula);
    p.setEdad(edad);
    p.setGenero(genero);
    p.setTelefono(telefono);
    p.setEmail(email);

    if (!p.validarDatos()) {
        // error
        return;
    }

    int idGuardado;
    if (GestorArchivos::guardarRegistro(&p, sizeof(Paciente), Rutas::PACIENTES, &idGuardado)) {
        std::cout << "✓ Paciente registrado con ID: " << idGuardado << "\n";
    }

    GestorArchivos::guardarHospital(&hospital, sizeof(Hospital));
}