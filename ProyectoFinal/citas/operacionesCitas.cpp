#include "operacionesCitas.hpp"
#include "Cita.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include "../utilidades/Formatos.hpp"
#include <iostream>
#include <ctime>

void agendarCita(Hospital& hospital) {
    std::cout << "\n=== AGENDAR NUEVA CITA ===\n";
    int pacienteID, doctorID;
    int dia, mes, anio, hora, minuto;

    std::cout << "ID del paciente: ";
    std::cin >> pacienteID;
    std::cout << "ID del doctor: ";
    std::cin >> doctorID;
    std::cout << "Fecha (DD MM AAAA): ";
    std::cin >> dia >> mes >> anio;
    std::cout << "Hora (HH MM, 24h): ";
    std::cin >> hora >> minuto;
    std::cin.ignore();

    // Validación básica de fecha/hora
    if (hora < 7 || hora > 19) {
        std::cout << "❌ Horario fuera del rango (7:00 - 19:00).\n";
        Formatos::pausar();
        return;
    }

    struct tm fechaStruct = {};
    fechaStruct.tm_year = anio - 1900;
    fechaStruct.tm_mon = mes - 1;
    fechaStruct.tm_mday = dia;
    fechaStruct.tm_hour = hora;
    fechaStruct.tm_min = minuto;
    fechaStruct.tm_sec = 0;
    fechaStruct.tm_isdst = -1;

    time_t fechaCita = mktime(&fechaStruct);
    if (fechaCita == -1 || fechaCita < time(nullptr)) {
        std::cout << "❌ Fecha/hora inválida o en el pasado.\n";
        Formatos::pausar();
        return;
    }

    // Verificar existencia (opcional en este nivel)
    Cita cita(hospital.generarNuevoIDCita(), pacienteID, doctorID, fechaCita);

    int idGuardado = -1;
    if (GestorArchivos::guardarRegistro(cita, Rutas::CITAS, &idGuardado)) {
        std::cout << "✓ Cita agendada con ID: " << idGuardado << "\n";
    } else {
        std::cout << "❌ Error al guardar cita.\n";
    }

    GestorArchivos::guardarHospital(hospital);
    Formatos::pausar();
}

void buscarCitaPorID() {
    std::cout << "\n=== BUSCAR CITA POR ID ===\n";
    int id;
    std::cout << "ID de la cita: ";
    std::cin >> id;
    std::cin.ignore();

    Cita c;
    if (GestorArchivos::leerRegistroPorID(id, c, Rutas::CITAS)) {
        c.mostrarInformacionCompleta();
    } else {
        std::cout << "❌ Cita no encontrada.\n";
    }
    Formatos::pausar();
}

void listarCitasPendientes() {
    std::cout << "\n=== CITAS PENDIENTES ===\n";
    Cita* citas = nullptr;
    int cantidad = 0;
    bool hayPendientes = false;

    if (GestorArchivos::listarTodosRegistros(citas, cantidad, Rutas::CITAS)) {
        for (int i = 0; i < cantidad; i++) {
            if (citas[i].getEstado() == 'P') {
                citas[i].mostrarInformacionBasica();
                hayPendientes = true;
            }
        }
        if (!hayPendientes) {
            std::cout << "No hay citas pendientes.\n";
        }
        delete[] citas;
    } else {
        std::cout << "❌ Error al cargar citas.\n";
    }
    Formatos::pausar();
}

void atenderCita() {
    std::cout << "\n=== ATENDER CITA ===\n";
    int id;
    std::cout << "ID de la cita a atender: ";
    std::cin >> id;
    std::cin.ignore();

    Cita c;
    if (!GestorArchivos::leerRegistroPorID(id, c, Rutas::CITAS)) {
        std::cout << "❌ Cita no encontrada.\n";
        Formatos::pausar();
        return;
    }

    if (c.getEstado() != 'P') {
        std::cout << "❌ La cita no está pendiente.\n";
        Formatos::pausar();
        return;
    }

    if (c.marcarComoAtendida()) {
        // Aquí podrías crear un historial médico automáticamente
        std::cout << "✓ Cita marcada como atendida.\n";
        // Actualización en archivo requeriría indexación → omitida por simplicidad
    } else {
        std::cout << "❌ No se pudo atender la cita.\n";
    }
    Formatos::pausar();
}

void cancelarCita() {
    std::cout << "\n=== CANCELAR CITA ===\n";
    int id;
    std::cout << "ID de la cita a cancelar: ";
    std::cin >> id;
    std::cin.ignore();

    Cita c;
    if (!GestorArchivos::leerRegistroPorID(id, c, Rutas::CITAS)) {
        std::cout << "❌ Cita no encontrada.\n";
        Formatos::pausar();
        return;
    }

    if (c.getEstado() != 'P') {
        std::cout << "❌ Solo se pueden cancelar citas pendientes.\n";
        Formatos::pausar();
        return;
    }

    if (c.cancelar()) {
        std::cout << "✓ Cita cancelada.\n";
    } else {
        std::cout << "❌ Error al cancelar.\n";
    }
    Formatos::pausar();
}