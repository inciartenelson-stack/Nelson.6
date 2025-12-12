#include "operacionesDoctores.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../utilidades/Validaciones.hpp"
#include "../utilidades/Formatos.hpp"
#include <iostream>
#include <cstring>

using namespace std;

void registrarDoctor(Hospital& hospital) {
    cout << "\n=== REGISTRAR NUEVO DOCTOR ===" << endl;
    
    Doctor doctor;
    
    // Generar ID único
    int nuevoID = hospital.generarNuevoIDDoctor();
    
    char buffer[100];
    
    // Solicitar datos
    cout << "Nombre: ";
    cin.getline(buffer, 100);
    doctor.setNombre(buffer);
    
    cout << "Apellido: ";
    cin.getline(buffer, 100);
    doctor.setApellido(buffer);
    
    cout << "Cédula: ";
    cin.getline(buffer, 100);
    doctor.setCedula(buffer);
    
    // Especialidad
    cout << "Especialidad (ej: Cardiología, Pediatría): ";
    cin.getline(buffer, 100);
    doctor.setEspecialidad(buffer);
    
    // Años de experiencia
    int aniosExp;
    do {
        cout << "Años de experiencia: ";
        cin >> aniosExp;
        cin.ignore();
        
        if (aniosExp < 0 || aniosExp > 60) {
            cout << "Años de experiencia deben estar entre 0 y 60." << endl;
        }
    } while (aniosExp < 0 || aniosExp > 60);
    doctor.setAniosExperiencia(aniosExp);
    
    cout << "Teléfono: ";
    cin.getline(buffer, 100);
    doctor.setTelefono(buffer);
    
    cout << "Cédula profesional: ";
    cin.getline(buffer, 100);
    doctor.setCedulaProfesional(buffer);
    
    // Costo de consulta
    double costo;
    do {
        cout << "Costo de consulta: $";
        cin >> costo;
        cin.ignore();
        
        if (costo < 0 || costo > 100000) {
            cout << "Costo debe estar entre 0 y 100,000." << endl;
        }
    } while (costo < 0 || costo > 100000);
    doctor.setCostoConsulta(costo);
    
    // Disponibilidad
    char disponibleChar;
    cout << "¿Está disponible? (S/N): ";
    cin >> disponibleChar;
    cin.ignore();
    doctor.setDisponible(toupper(disponibleChar) == 'S');
    
    cout << "Horario de trabajo (ej: Lunes-Viernes 8:00-16:00): ";
    cin.getline(buffer, 100);
    doctor.setHorarioTrabajo(buffer);
    
    // Validar datos completos
    if (doctor.validarDatos()) {
        // Guardar en archivo (esto es un ejemplo, implementa tu GestorArchivos)
        cout << "\n✓ Doctor registrado exitosamente con ID: " << nuevoID << endl;
        hospital.incrementarDoctoresRegistrados();
    } else {
        cout << "\n✗ Datos del doctor no válidos." << endl;
    }
    
    Formatos::pausar();
}

void buscarDoctorPorID() {
    cout << "\n=== BUSCAR DOCTOR POR ID ===" << endl;
    
    int idBuscado;
    cout << "ID del doctor: ";
    cin >> idBuscado;
    cin.ignore();
    
    cout << "Búsqueda por ID implementada aquí..." << endl;
    // Implementar búsqueda real con GestorArchivos
    
    Formatos::pausar();
}

void buscarDoctorPorCedula() {
    cout << "\n=== BUSCAR DOCTOR POR CÉDULA ===" << endl;
    
    char cedulaBuscada[20];
    cout << "Cédula del doctor: ";
    cin.getline(cedulaBuscada, 20);
    
    cout << "Búsqueda por cédula implementada aquí..." << endl;
    
    Formatos::pausar();
}

void listarTodosDoctores() {
    cout << "\n=== LISTADO DE TODOS LOS DOCTORES ===" << endl;
    
    // Implementar listado real con GestorArchivos
    cout << "Listado de doctores implementado aquí..." << endl;
    
    Formatos::pausar();
}

void listarDoctoresPorEspecialidad() {
    cout << "\n=== LISTAR DOCTORES POR ESPECIALIDAD ===" << endl;
    
    char especialidad[50];
    cout << "Especialidad a buscar: ";
    cin.getline(especialidad, 50);
    
    cout << "Listado por especialidad implementado aquí..." << endl;
    
    Formatos::pausar();
}

void modificarDoctor() {
    cout << "\n=== MODIFICAR DATOS DE DOCTOR ===" << endl;
    
    int idModificar;
    cout << "ID del doctor a modificar: ";
    cin >> idModificar;
    cin.ignore();
    
    cout << "Modificación de doctor implementada aquí..." << endl;
    
    Formatos::pausar();
}

void eliminarDoctor() {
    cout << "\n=== ELIMINAR DOCTOR ===" << endl;
    
    int idEliminar;
    cout << "ID del doctor a eliminar: ";
    cin >> idEliminar;
    cin.ignore();
    
    // Confirmar eliminación
    char confirmar;
    cout << "¿Está seguro de eliminar este doctor? (S/N): ";
    cin >> confirmar;
    cin.ignore();
    
    if (toupper(confirmar) == 'S') {
        cout << "Doctor eliminado (simulación)" << endl;
    } else {
        cout << "Eliminación cancelada" << endl;
    }
    
    Formatos::pausar();
}

void mostrarDisponibilidadDoctores() {
    cout << "\n=== DISPONIBILIDAD DE DOCTORES ===" << endl;
    
    // Implementar consulta de disponibilidad
    cout << "Consulta de disponibilidad implementada aquí..." << endl;
    
    Formatos::pausar();
}