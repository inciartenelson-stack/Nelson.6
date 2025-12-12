#include <iostream>
#include <cstdlib>
#include "hospital/Hospital.hpp"
#include "utilidades/Formatos.hpp"

using namespace std;

void mostrarMenuPrincipal() {
    cout << "\n========================================" << endl;
    cout << "   SISTEMA HOSPITALARIO - POO v3.0" << endl;
    cout << "   Universidad Rafael Urdaneta" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "MENU PRINCIPAL:" << endl;
    cout << "1. Informacion del Hospital" << endl;
    cout << "2. Estadisticas del Sistema" << endl;
    cout << "3. Gestion de Pacientes" << endl;
    cout << "4. Gestion de Doctores" << endl;
    cout << "5. Salir" << endl;
    cout << endl;
}

void menuPacientes(Hospital& hospital) {
    int opcion;
    
    do {
        Formatos::limpiarPantalla();
        
        cout << "=== GESTION DE PACIENTES ===" << endl;
        cout << "1. Registrar paciente" << endl;
        cout << "2. Ver total registrados" << endl;
        cout << "3. Volver al menu principal" << endl;
        cout << "\nOpcion: ";
        cin >> opcion;
        Formatos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                cout << "\n--- REGISTRAR PACIENTE ---" << endl;
                cout << "ID asignado: " << hospital.generarNuevoIDPaciente() << endl;
                hospital.incrementarPacientesRegistrados();
                cout << "Paciente registrado exitosamente!" << endl;
                Formatos::pausar();
                break;
                
            case 2:
                cout << "\n--- TOTAL PACIENTES ---" << endl;
                cout << "Pacientes registrados: " << hospital.getContadorPacientes() << endl;
                Formatos::pausar();
                break;
                
            case 3:
                cout << "Volviendo al menu principal..." << endl;
                break;
                
            default:
                cout << "Opcion no valida!" << endl;
                Formatos::pausar();
        }
        
    } while(opcion != 3);
}

void menuDoctores(Hospital& hospital) {
    int opcion;
    
    do {
        Formatos::limpiarPantalla();
        
        cout << "=== GESTION DE DOCTORES ===" << endl;
        cout << "1. Registrar doctor" << endl;
        cout << "2. Ver total registrados" << endl;
        cout << "3. Volver al menu principal" << endl;
        cout << "\nOpcion: ";
        cin >> opcion;
        Formatos::limpiarBuffer();
        
        switch(opcion) {
            case 1:
                cout << "\n--- REGISTRAR DOCTOR ---" << endl;
                cout << "ID asignado: " << hospital.generarNuevoIDDoctor() << endl;
                hospital.incrementarDoctoresRegistrados();
                cout << "Doctor registrado exitosamente!" << endl;
                Formatos::pausar();
                break;
                
            case 2:
                cout << "\n--- TOTAL DOCTORES ---" << endl;
                cout << "Doctores registrados: " << hospital.getContadorDoctores() << endl;
                Formatos::pausar();
                break;
                
            case 3:
                cout << "Volviendo al menu principal..." << endl;
                break;
                
            default:
                cout << "Opcion no valida!" << endl;
                Formatos::pausar();
        }
        
    } while(opcion != 3);
}

int main() {
    Hospital hospital("Hospital General URU", 
                     "Av. Universidad, Maracaibo", 
                     "0261-1234567");
    
    int opcionPrincipal;
    
    do {
        Formatos::limpiarPantalla();
        mostrarMenuPrincipal();
        
        cout << "Seleccione una opcion: ";
        cin >> opcionPrincipal;
        Formatos::limpiarBuffer();
        
        switch(opcionPrincipal) {
            case 1:
                Formatos::limpiarPantalla();
                cout << "=== INFORMACION DEL HOSPITAL ===" << endl;
                hospital.mostrarInformacion();
                Formatos::pausar();
                break;
                
            case 2:
                Formatos::limpiarPantalla();
                cout << "=== ESTADISTICAS DEL SISTEMA ===" << endl;
                hospital.mostrarEstadisticas();
                Formatos::pausar();
                break;
                
            case 3:
                menuPacientes(hospital);
                break;
                
            case 4:
                menuDoctores(hospital);
                break;
                
            case 5:
                cout << "\n========================================" << endl;
                cout << "   Gracias por usar el sistema" << endl;
                cout << "   ¡Hasta pronto!" << endl;
                cout << "========================================" << endl;
                break;
                
            default:
                cout << "\nOpcion no valida. Intente nuevamente." << endl;
                Formatos::pausar();
        }
        
    } while(opcionPrincipal != 5);
    
    return 0;
}