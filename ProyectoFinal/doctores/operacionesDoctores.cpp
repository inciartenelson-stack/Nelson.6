#include "operacionesDoctores.hpp"
#include "../hospital/Hospital.hpp"
#include "Doctor.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include "../utilidades/Validaciones.hpp"
#include "../utilidades/Formatos.hpp"
#include <iostream>
#include <cstring>

void registrarDoctor(Hospital& hospital) {
    std::cout << "\n=== REGISTRAR NUEVO DOCTOR ===\n";
    
    char nombre[100], apellido[100], cedula[20], especialidad[50], telefono[30], email[100];
    float costo;
    char disponibleChar;

    std::cout << "Nombre: ";
    std::cin.getline(nombre, 99);
    std::cout << "Apellido: ";
    std::cin.getline(apellido, 99);
    std::cout << "Cédula profesional: ";
    std::cin.getline(cedula, 19);
    std::cout << "Especialidad (Cardiología, Pediatría, Dermatología, Neurología, Ginecología): ";
    std::cin.getline(especialidad, 49);
    std::cout << "Teléfono: ";
    std::cin.getline(telefono, 29);
    std::cout << "Email: ";
    std::cin.getline(email, 99);
    std::cout << "Costo de consulta ($): ";
    std::cin >> costo;
    std::cin.ignore();
    std::cout << "¿Disponible? (S/N): ";
    std::cin >> disponibleChar;
    bool disponible = (disponibleChar == 'S' || disponibleChar == 's');

    if (!Validaciones::validarCedula(cedula)) {
        std::cout << "❌ Cédula inválida.\n";
        Formatos::pausar();
        return;
    }
    if (!Validaciones::validarTelefono(telefono)) {
        std::cout << "❌ Teléfono inválido.\n";
        Formatos::pausar();
        return;
    }
    if (!Validaciones::validarEmail(email)) {
        std::cout << "❌ Email inválido.\n";
        Formatos::pausar();
        return;
    }

    int nuevoID = hospital.generarNuevoIDDoctor();
    Doctor d(nuevoID, nombre, apellido, cedula, especialidad);
    d.setTelefono(telefono);
    d.setEmail(email);
    d.setCostoConsulta(costo);
    d.setDisponible(disponible);

    if (!d.validarDatos()) {
        std::cout << "❌ Datos del doctor incompletos o inválidos.\n";
        Formatos::pausar();
        return;
    }

    int idGuardado = -1;
    if (GestorArchivos::guardarRegistro(d, Rutas::DOCTORES, &idGuardado)) {
        std::cout << "✓ Doctor registrado con ID: " << idGuardado << "\n";
    } else {
        std::cout << "❌ Error al guardar doctor.\n";
    }

    GestorArchivos::guardarHospital(hospital);
    Formatos::pausar();
}

void buscarDoctorPorID() {
    std::cout << "\n=== BUSCAR DOCTOR POR ID ===\n";
    int id;
    std::cout << "Ingrese ID del doctor: ";
    std::cin >> id;
    std::cin.ignore();

    Doctor d;
    if (GestorArchivos::leerRegistroPorID(id, d, Rutas::DOCTORES)) {
        d.mostrarInformacionCompleta();
    } else {
        std::cout << "❌ Doctor no encontrado.\n";
    }
    Formatos::pausar();
}

void listarTodosDoctores() {
    std::cout << "\n=== LISTA DE TODOS LOS DOCTORES ===\n";
    Doctor* doctores = nullptr;
    int cantidad = 0;

    if (GestorArchivos::listarTodosRegistros(doctores, cantidad, Rutas::DOCTORES)) {
        if (cantidad == 0) {
            std::cout << "No hay doctores registrados.\n";
        } else {
            for (int i = 0; i < cantidad; i++) {
                std::cout << "\n--- Doctor " << (i + 1) << " ---\n";
                doctores[i].mostrarInformacionBasica();
            }
        }
        delete[] doctores;
    } else {
        std::cout << "❌ Error al cargar doctores.\n";
    }
    Formatos::pausar();
}

void listarDoctoresPorEspecialidad() {
    std::cout << "\n=== LISTAR DOCTORES POR ESPECIALIDAD ===\n";
    char especialidad[50];
    std::cout << "Especialidad: ";
    std::cin.getline(especialidad, 49);

    Doctor* doctores = nullptr;
    int cantidad = 0;
    bool encontrado = false;

    if (GestorArchivos::listarTodosRegistros(doctores, cantidad, Rutas::DOCTORES)) {
        for (int i = 0; i < cantidad; i++) {
            if (strcmp(doctores[i].getEspecialidad(), especialidad) == 0) {
                doctores[i].mostrarInformacionBasica();
                encontrado = true;
            }
        }
        if (!encontrado) {
            std::cout << "No hay doctores en esa especialidad.\n";
        }
        delete[] doctores;
    } else {
        std::cout << "❌ Error al cargar doctores.\n";
    }
    Formatos::pausar();
}

void modificarDoctor() {
    std::cout << "\n=== MODIFICAR DATOS DE DOCTOR ===\n";
    int id;
    std::cout << "ID del doctor a modificar: ";
    std::cin >> id;
    std::cin.ignore();

    Doctor d;
    if (!GestorArchivos::leerRegistroPorID(id, d, Rutas::DOCTORES)) {
        std::cout << "❌ Doctor no encontrado.\n";
        Formatos::pausar();
        return;
    }

    d.mostrarInformacionCompleta();
    std::cout << "\n--- Nuevos datos (dejar vacío para no cambiar) ---\n";

    char telefono[30], email[100];
    float costo = -1.0f;
    char dispChar = ' ';

    std::cout << "Nuevo teléfono: ";
    std::cin.getline(telefono, 29);
    if (strlen(telefono) > 0) d.setTelefono(telefono);

    std::cout << "Nuevo email: ";
    std::cin.getline(email, 99);
    if (strlen(email) > 0) d.setEmail(email);

    std::cout << "Nuevo costo de consulta ($): ";
    std::cin >> costo;
    std::cin.ignore();
    if (costo >= 0) d.setCostoConsulta(costo);

    std::cout << "¿Disponible? (S/N): ";
    std::cin >> dispChar;
    std::cin.ignore();
    if (dispChar != ' ') d.setDisponible(dispChar == 'S' || dispChar == 's');

    if (GestorArchivos::actualizarRegistro( /* índice debe buscarse */ )) {
        std::cout << "⚠️ Actualización por índice no implementada en este modelo (usar reescritura o ID-based update en versión avanzada).\n";
    }
    // En este diseño simple, la actualización se omite por simplicidad.
    // Alternativa: eliminar y reinsertar, o implementar búsqueda por índice.
    std::cout << "✅ Datos modificados en memoria. (Persistencia completa requiere indexación más avanzada).\n";
    Formatos::pausar();
}

void eliminarDoctor() {
    std::cout << "\n=== ELIMINAR DOCTOR ===\n";
    int id;
    std::cout << "ID del doctor a eliminar: ";
    std::cin >> id;
    std::cin.ignore();
    std::cout << "⚠️ Eliminación lógica no implementada. Esta operación es solo de demostración.\n";
    Formatos::pausar();
}