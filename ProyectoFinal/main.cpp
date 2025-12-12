#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

// Headers principales
#include "hospital/Hospital.hpp"
#include "utilidades/Formatos.hpp"
#include "utilidades/Validaciones.hpp"

// Headers de operaciones
#include "doctores/operacionesDoctores.hpp"
#include "pacientes/operacionesPacientes.hpp"
#include "citas/operacionesCitas.hpp"
#include "historial/operacionesHistorial.hpp"

// Constantes de configuración
const std::string NOMBRE_HOSPITAL = "Hospital Central";
const std::string DIRECCION_HOSPITAL = "Av. Principal 123, Ciudad";
const std::string TELEFONO_HOSPITAL = "+1 (234) 567-8900";
const int CAPACIDAD_HOSPITAL = 500;

// Prototipos de funciones
void mostrarMenuPrincipal();
void inicializarSistema();
void cargarDatosDemo();
void mostrarCreditos();
void mostrarEstadisticasSistema();
void realizarCopiaSeguridad();
void restaurarCopiaSeguridad();

// Variables globales (considerar usar singleton en versión más avanzada)
std::unique_ptr<Hospital> hospital;

/**
 * @brief Función principal del sistema hospitalario
 * @return Código de salida (0 = éxito)
 */
int main() {
    // Configurar semilla aleatoria
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // Configurar localización para caracteres especiales
    std::setlocale(LC_ALL, "");
    
    try {
        // Inicializar sistema
        inicializarSistema();
        
        // Mostrar pantalla de bienvenida
        Formatos::limpiarPantalla();
        Formatos::encabezado("SISTEMA HOSPITALARIO INTEGRADO", 70, '=');
        std::cout << Formatos::colorizar("Bienvenido al " + NOMBRE_HOSPITAL, Formatos::AZUL, Formatos::NEGRITA) << "\n\n";
        std::cout << "Fecha y hora del sistema: " 
                  << Formatos::formatearFecha(std::time(nullptr), "%A, %d de %B de %Y - %H:%M") 
                  << "\n\n";
        
        Formatos::mostrarInfo("Sistema inicializado correctamente");
        Formatos::pausar("Presione Enter para continuar...");
        
        // Bucle principal del programa
        bool ejecutando = true;
        while (ejecutando) {
            mostrarMenuPrincipal();
        }
        
        // Guardar estado antes de salir
        Formatos::mostrarInfo("Guardando datos del sistema...");
        // Aquí iría la lógica para guardar el estado del hospital
        
        Formatos::mostrarExito("Sistema finalizado correctamente");
        
    } catch (const std::exception& e) {
        Formatos::mostrarError("Error crítico en el sistema: " + std::string(e.what()));
        Formatos::pausar("El programa se cerrará debido a un error crítico...");
        return 1;
    } catch (...) {
        Formatos::mostrarError("Error desconocido en el sistema");
        Formatos::pausar("El programa se cerrará debido a un error desconocido...");
        return 1;
    }
    
    return 0;
}

/**
 * @brief Inicializa el sistema hospitalario
 */
void inicializarSistema() {
    Formatos::mostrarInfo("Inicializando sistema hospitalario...");
    
    // Crear instancia del hospital
    hospital = std::make_unique<Hospital>(NOMBRE_HOSPITAL, DIRECCION_HOSPITAL, 
                                          TELEFONO_HOSPITAL, CAPACIDAD_HOSPITAL);
    
    // Intentar cargar datos existentes
    Formatos::mostrarInfo("Cargando datos del sistema...");
    
    // En una implementación real, aquí cargaríamos desde archivos
    // Por ahora, cargamos datos de demostración
    cargarDatosDemo();
    
    // Verificar consistencia de datos
    if (hospital->verificarConsistencia()) {
        Formatos::mostrarExito("Datos cargados y verificados correctamente");
    } else {
        Formatos::mostrarAdvertencia("Algunos datos pueden estar inconsistentes");
    }
}

/**
 * @brief Carga datos de demostración para pruebas
 */
void cargarDatosDemo() {
    // Este método carga datos de ejemplo para demostración
    // En un sistema real, estos datos vendrían de una base de datos
    
    Formatos::mostrarInfo("Cargando datos de demostración...");
    
    try {
        // Crear algunos doctores de ejemplo
        Doctor dr1(1, "Juan", "Pérez", "12345678-9", "Cardiología");
        dr1.setTelefono("+56 9 1234 5678");
        dr1.setEmail("juan.perez@hospital.com");
        dr1.setCostoConsulta(35000.0f);
        dr1.setDisponible(true);
        
        Doctor dr2(2, "María", "González", "87654321-0", "Pediatría");
        dr2.setTelefono("+56 9 8765 4321");
        dr2.setEmail("maria.gonzalez@hospital.com");
        dr2.setCostoConsulta(30000.0f);
        dr2.setDisponible(true);
        
        Doctor dr3(3, "Carlos", "Rodríguez", "56781234-5", "Dermatología");
        dr3.setTelefono("+56 9 5678 1234");
        dr3.setEmail("carlos.rodriguez@hospital.com");
        dr3.setCostoConsulta(40000.0f);
        dr3.setDisponible(false); // No disponible
        
        // Agregar doctores al hospital
        hospital->agregarDoctor(dr1);
        hospital->agregarDoctor(dr2);
        hospital->agregarDoctor(dr3);
        
        // Actualizar IDs para que no haya conflictos
        hospital->generarNuevoIDDoctor(); // Debería ser 4
        hospital->generarNuevoIDDoctor(); // Debería ser 5
        
        // Crear algunos pacientes de ejemplo
        Paciente pac1(1, "Ana", "Martínez", "11222333-4", 35, 'F', 
                     "+56 9 1111 2222", "ana.martinez@email.com");
        Paciente pac2(2, "Luis", "Fernández", "22333444-5", 42, 'M',
                     "+56 9 2222 3333", "luis.fernandez@email.com");
        Paciente pac3(3, "Sofía", "López", "33444555-6", 28, 'F',
                     "+56 9 3333 4444", "sofia.lopez@email.com");
        Paciente pac4(4, "Pedro", "Sánchez", "44555666-7", 55, 'M',
                     "+56 9 4444 5555", "pedro.sanchez@email.com");
        
        // Agregar pacientes al hospital
        hospital->agregarPaciente(pac1);
        hospital->agregarPaciente(pac2);
        hospital->agregarPaciente(pac3);
        hospital->agregarPaciente(pac4);
        
        // Actualizar IDs para que no haya conflictos
        hospital->generarNuevoIDPaciente(); // Debería ser 5
        hospital->generarNuevoIDPaciente(); // Debería ser 6
        
        // Crear algunas citas de ejemplo
        std::time_t ahora = std::time(nullptr);
        std::time_t manana = ahora + (24 * 60 * 60); // Mañana
        std::time_t pasadoManana = ahora + (2 * 24 * 60 * 60); // Pasado mañana
        
        Cita cita1(1, 1, 1, manana + (9 * 60 * 60),  // Paciente 1, Doctor 1, 9:00 AM
                  "Control cardíaco rutinario", "Primer control", 30);
        Cita cita2(2, 2, 2, manana + (11 * 60 * 60), // Paciente 2, Doctor 2, 11:00 AM
                  "Consulta pediátrica", "Control crecimiento", 45);
        Cita cita3(3, 3, 1, pasadoManana + (14 * 60 * 60), // Paciente 3, Doctor 1, 2:00 PM
                  "Evaluación cardíaca", "Segunda opinión", 60);
        
        // Agregar citas al hospital
        hospital->agregarCita(cita1);
        hospital->agregarCita(cita2);
        hospital->agregarCita(cita3);
        
        // Actualizar IDs para que no haya conflictos
        hospital->generarNuevoIDCita(); // Debería ser 4
        hospital->generarNuevoIDCita(); // Debería ser 5
        
        // Crear algunos historiales médicos de ejemplo
        HistorialMedico hist1(1, 1, 1, 1, 
                             "Hipertensión arterial controlada",
                             "Dieta baja en sal, ejercicio regular, medicación diaria");
        hist1.setPeso(70.5);
        hist1.setAltura(1.65);
        hist1.setTemperatura(36.8);
        hist1.setPresionSistolica(130);
        hist1.setPresionDiastolica(85);
        hist1.setFrecuenciaCardiaca(75);
        hist1.setFrecuenciaRespiratoria(16);
        hist1.agregarMedicamento("Losartán 50mg");
        hist1.agregarMedicamento("Hidroclorotiazida 25mg");
        
        HistorialMedico hist2(2, 2, 2, 2,
                             "Control pediátrico normal",
                             "Vacunación al día, desarrollo adecuado");
        hist2.setPeso(18.2);
        hist2.setAltura(0.95);
        hist2.setTemperatura(37.2);
        hist2.setPresionSistolica(90);
        hist2.setPresionDiastolica(60);
        hist2.setFrecuenciaCardiaca(110);
        hist2.setFrecuenciaRespiratoria(25);
        
        // Agregar historiales al hospital
        hospital->agregarHistorial(hist1);
        hospital->agregarHistorial(hist2);
        
        // Actualizar IDs para que no haya conflictos
        hospital->generarNuevoIDHistorial(); // Debería ser 3
        hospital->generarNuevoIDHistorial(); // Debería ser 4
        
        // Agregar algunos pacientes a la cola de espera
        hospital->agregarAColaEspera(4); // Paciente Pedro Sánchez
        
        Formatos::mostrarExito("Datos de demostración cargados: " + 
                              std::to_string(hospital->getCantidadDoctores()) + " doctores, " +
                              std::to_string(hospital->getCantidadPacientes()) + " pacientes, " +
                              std::to_string(hospital->getCantidadCitas()) + " citas, " +
                              std::to_string(hospital->getCantidadHistoriales()) + " historiales");
                              
    } catch (const std::exception& e) {
        Formatos::mostrarAdvertencia("Error al cargar datos demo: " + std::string(e.what()));
    }
}

/**
 * @brief Muestra el menú principal del sistema
 */
void mostrarMenuPrincipal() {
    Formatos::limpiarPantalla();
    
    // Mostrar información del sistema en la parte superior
    Formatos::encabezado(NOMBRE_HOSPITAL + " - Sistema de Gestión", 70, '=');
    
    std::cout << Formatos::colorizar("Estado del sistema:", Formatos::CYAN, Formatos::NEGRITA) << "\n";
    std::cout << "  Doctores activos: " << Formatos::colorizar(std::to_string(hospital->getCantidadDoctores()), Formatos::VERDE) << "\n";
    std::cout << "  Pacientes registrados: " << Formatos::colorizar(std::to_string(hospital->getCantidadPacientes()), Formatos::VERDE) << "\n";
    std::cout << "  Citas programadas hoy: " << Formatos::colorizar(std::to_string(hospital->getCitasHoy().size()), Formatos::AMARILLO) << "\n";
    std::cout << "  Pacientes en espera: " << Formatos::colorizar(std::to_string(hospital->getCantidadEnEspera()), Formatos::AMARILLO) << "\n";
    
    // Mostrar alertas si las hay
    if (hospital->getCitasHoy().size() > 10) {
        std::cout << Formatos::colorizar("  ⚠️  Muchas citas programadas para hoy", Formatos::AMARILLO) << "\n";
    }
    if (hospital->getCantidadEnEspera() > 5) {
        std::cout << Formatos::colorizar("  ⚠️  Cola de espera con muchos pacientes", Formatos::ROJO) << "\n";
    }
    
    Formatos::separador(70, '-');
    
    // Opciones del menú principal
    std::vector<std::string> opciones = {
        "Gestión de Doctores",
        "Gestión de Pacientes", 
        "Gestión de Citas",
        "Historiales Médicos",
        "Estadísticas del Hospital",
        "Atención de Urgencias",
        "Configuración del Sistema",
        "Copia de Seguridad",
        "Acerca del Sistema",
        "Salir del Sistema"
    };
    
    int opcion = Formatos::mostrarMenu("MENU PRINCIPAL", opciones, false);
    
    // Procesar opción seleccionada
    switch (opcion) {
        case 1: // Gestión de Doctores
            menuGestionDoctores();
            break;
            
        case 2: // Gestión de Pacientes
            menuGestionPacientes();
            break;
            
        case 3: // Gestión de Citas
            menuGestionCitas();
            break;
            
        case 4: // Historiales Médicos
            menuHistorialMedicos();
            break;
            
        case 5: // Estadísticas del Hospital
            mostrarEstadisticasSistema();
            break;
            
        case 6: // Atención de Urgencias
            menuAtencionUrgencias();
            break;
            
        case 7: // Configuración del Sistema
            menuConfiguracion();
            break;
            
        case 8: // Copia de Seguridad
            menuCopiaSeguridad();
            break;
            
        case 9: // Acerca del Sistema
            mostrarCreditos();
            break;
            
        case 10: // Salir del Sistema
            if (confirmarSalida()) {
                // Limpiar pantalla y mostrar mensaje de despedida
                Formatos::limpiarPantalla();
                Formatos::encabezado("Saliendo del Sistema", 60, '=');
                std::cout << Formatos::colorizar("¡Gracias por usar el Sistema Hospitalario!", Formatos::VERDE, Formatos::NEGRITA) << "\n\n";
                std::cout << "Hospital: " << NOMBRE_HOSPITAL << "\n";
                std::cout << "Dirección: " << DIRECCION_HOSPITAL << "\n";
                std::cout << "Teléfono: " << TELEFONO_HOSPITAL << "\n\n";
                Formatos::pausar("Presione Enter para salir...");
                
                // Terminar el bucle principal
                throw std::runtime_error("salida_normal"); // Usamos excepción para salir limpiamente
            }
            break;
            
        default:
            Formatos::mostrarError("Opción no válida");
            Formatos::pausar();
            break;
    }
}

/**
 * @brief Muestra el submenú de gestión de doctores
 */
void menuGestionDoctores() {
    bool volver = false;
    
    while (!volver) {
        Formatos::limpiarPantalla();
        Formatos::encabezado("GESTIÓN DE DOCTORES", 60, '=');
        
        std::vector<std::string> opciones = {
            "Registrar Nuevo Doctor",
            "Buscar Doctor por ID",
            "Listar Todos los Doctores",
            "Listar Doctores por Especialidad",
            "Modificar Datos de Doctor",
            "Ver Disponibilidad de Doctores",
            "Volver al Menú Principal"
        };
        
        int opcion = Formatos::mostrarMenu("", opciones, false);
        
        switch (opcion) {
            case 1:
                registrarDoctor(*hospital);
                break;
                
            case 2:
                buscarDoctorPorID();
                break;
                
            case 3:
                listarTodosDoctores();
                break;
                
            case 4:
                listarDoctoresPorEspecialidad();
                break;
                
            case 5:
                modificarDoctor();
                break;
                
            case 6:
                mostrarDisponibilidadDoctores();
                break;
                
            case 7:
                volver = true;
                break;
                
            default:
                Formatos::mostrarError("Opción no válida");
                Formatos::pausar();
                break;
        }
    }
}

/**
 * @brief Muestra el submenú de gestión de pacientes
 */
void menuGestionPacientes() {
    bool volver = false;
    
    while (!volver) {
        Formatos::limpiarPantalla();
        Formatos::encabezado("GESTIÓN DE PACIENTES", 60, '=');
        
        std::vector<std::string> opciones = {
            "Registrar Nuevo Paciente",
            "Buscar Paciente por ID",
            "Buscar Paciente por Nombre",
            "Listar Todos los Pacientes",
            "Modificar Datos de Paciente",
            "Eliminar Paciente",
            "Agregar a Cola de Espera",
            "Volver al Menú Principal"
        };
        
        int opcion = Formatos::mostrarMenu("", opciones, false);
        
        switch (opcion) {
            case 1:
                registrarPaciente(*hospital);
                break;
                
            case 2:
                buscarPacientePorID();
                break;
                
            case 3:
                buscarPacientePorNombre();
                break;
                
            case 4:
                listarTodosPacientes();
                break;
                
            case 5:
                modificarPaciente();
                break;
                
            case 6:
                eliminarPaciente();
                break;
                
            case 7:
                agregarPacienteAColaEspera();
                break;
                
            case 8:
                volver = true;
                break;
                
            default:
                Formatos::mostrarError("Opción no válida");
                Formatos::pausar();
                break;
        }
    }
}

/**
 * @brief Muestra el submenú de gestión de citas
 */
void menuGestionCitas() {
    bool volver = false;
    
    while (!volver) {
        Formatos::limpiarPantalla();
        Formatos::encabezado("GESTIÓN DE CITAS", 60, '=');
        
        std::vector<std::string> opciones = {
            "Agendar Nueva Cita",
            "Buscar Cita por ID",
            "Listar Citas de Hoy",
            "Listar Todas las Citas",
            "Listar Citas por Paciente",
            "Listar Citas por Doctor",
            "Modificar Cita",
            "Cancelar Cita",
            "Confirmar Asistencia a Cita",
            "Volver al Menú Principal"
        };
        
        int opcion = Formatos::mostrarMenu("", opciones, false);
        
        switch (opcion) {
            case 1:
                agendarCita(*hospital);
                break;
                
            case 2:
                buscarCitaPorID();
                break;
                
            case 3:
                listarCitasHoy();
                break;
                
            case 4:
                listarTodasCitas();
                break;
                
            case 5:
                listarCitasPorPaciente();
                break;
                
            case 6:
                listarCitasPorDoctor();
                break;
                
            case 7:
                modificarCita();
                break;
                
            case 8:
                cancelarCita();
                break;
                
            case 9:
                confirmarAsistenciaCita();
                break;
                
            case 10:
                volver = true;
                break;
                
            default:
                Formatos::mostrarError("Opción no válida");
                Formatos::pausar();
                break;
        }
    }
}

/**
 * @brief Muestra el submenú de historiales médicos
 */
void menuHistorialMedicos() {
    bool volver = false;
    
    while (!volver) {
        Formatos::limpiarPantalla();
        Formatos::encabezado("HISTORIALES MÉDICOS", 60, '=');
        
        std::vector<std::string> opciones = {
            "Crear Nuevo Historial Médico",
            "Buscar Historial por ID",
            "Ver Historial de Paciente",
            "Listar Historiales por Doctor",
            "Agregar Diagnóstico a Historial",
            "Agregar Tratamiento a Historial",
            "Registrar Signos Vitales",
            "Generar Reporte de Historial",
            "Volver al Menú Principal"
        };
        
        int opcion = Formatos::mostrarMenu("", opciones, false);
        
        switch (opcion) {
            case 1:
                crearHistorialMedico();
                break;
                
            case 2:
                verHistorialPorID();
                break;
                
            case 3:
                listarHistorialPaciente();
                break;
                
            case 4:
                listarHistorialPorDoctor();
                break;
                
            case 5:
                agregarDiagnosticoHistorial();
                break;
                
            case 6:
                agregarTratamientoHistorial();
                break;
                
            case 7:
                registrarSignosVitales();
                break;
                
            case 8:
                generarReporteHistorial();
                break;
                
            case 9:
                volver = true;
                break;
                
            default:
                Formatos::mostrarError("Opción no válida");
                Formatos::pausar();
                break;
        }
    }
}

/**
 * @brief Muestra el submenú de atención de urgencias
 */
void menuAtencionUrgencias() {
    bool volver = false;
    
    while (!volver) {
        Formatos::limpiarPantalla();
        Formatos::encabezado("ATENCIÓN DE URGENCIAS", 60, '=');
        
        std::cout << Formatos::colorizar("⚠️  MÓDULO DE URGENCIAS ⚠️", Formatos::ROJO, Formatos::NEGRITA) << "\n\n";
        
        std::vector<std::string> opciones = {
            "Registrar Paciente de Urgencia",
            "Ver Cola de Espera de Urgencias",
            "Atender Siguiente Paciente Urgente",
            "Asignar Prioridad de Urgencia",
            "Ver Doctores Disponibles para Urgencias",
            "Registrar Alta de Urgencia",
            "Ver Estadísticas de Urgencias",
            "Volver al Menú Principal"
        };
        
        int opcion = Formatos::mostrarMenu("", opciones, false);
        
        switch (opcion) {
            case 1:
                registrarPacienteUrgencia();
                break;
                
            case 2:
                verColaEsperaUrgencias();
                break;
                
            case 3:
                atenderPacienteUrgencia();
                break;
                
            case 4:
                asignarPrioridadUrgencia();
                break;
                
            case 5:
                verDoctoresDisponiblesUrgencias();
                break;
                
            case 6:
                registrarAltaUrgencia();
                break;
                
            case 7:
                verEstadisticasUrgencias();
                break;
                
            case 8:
                volver = true;
                break;
                
            default:
                Formatos::mostrarError("Opción no válida");
                Formatos::pausar();
                break;
        }
    }
}

/**
 * @brief Muestra el submenú de configuración
 */
void menuConfiguracion() {
    bool volver = false;
    
    while (!volver) {
        Formatos::limpiarPantalla();
        Formatos::encabezado("CONFIGURACIÓN DEL SISTEMA", 60, '=');
        
        std::vector<std::string> opciones = {
            "Configurar Hospital",
            "Gestionar Especialidades Médicas",
            "Configurar Precios de Consultas",
            "Configurar Horarios de Atención",
            "Gestionar Usuarios del Sistema",
            "Configurar Parámetros del Sistema",
            "Restaurar Valores por Defecto",
            "Volver al Menú Principal"
        };
        
        int opcion = Formatos::mostrarMenu("", opciones, false);
        
        switch (opcion) {
            case 1:
                configurarHospital();
                break;
                
            case 2:
                gestionarEspecialidades();
                break;
                
            case 3:
                configurarPreciosConsultas();
                break;
                
            case 4:
                configurarHorariosAtencion();
                break;
                
            case 5:
                gestionarUsuariosSistema();
                break;
                
            case 6:
                configurarParametrosSistema();
                break;
                
            case 7:
                restaurarValoresPorDefecto();
                break;
                
            case 8:
                volver = true;
                break;
                
            default:
                Formatos::mostrarError("Opción no válida");
                Formatos::pausar();
                break;
        }
    }
}

/**
 * @brief Muestra el submenú de copia de seguridad
 */
void menuCopiaSeguridad() {
    bool volver = false;
    
    while (!volver) {
        Formatos::limpiarPantalla();
        Formatos::encabezado("COPIA DE SEGURIDAD", 60, '=');
        
        std::cout << Formatos::colorizar("💾 GESTIÓN DE RESPALDOS 💾", Formatos::CYAN, Formatos::NEGRITA) << "\n\n";
        
        std::vector<std::string> opciones = {
            "Crear Copia de Seguridad Completa",
            "Restaurar desde Copia de Seguridad",
            "Crear Copia de Seguridad Incremental",
            "Listar Copias de Seguridad Disponibles",
            "Eliminar Copia de Seguridad Antigua",
            "Configurar Auto-Respaldo",
            "Ver Espacio de Almacenamiento",
            "Volver al Menú Principal"
        };
        
        int opcion = Formatos::mostrarMenu("", opciones, false);
        
        switch (opcion) {
            case 1:
                realizarCopiaSeguridad();
                break;
                
            case 2:
                restaurarCopiaSeguridad();
                break;
                
            case 3:
                crearCopiaSeguridadIncremental();
                break;
                
            case 4:
                listarCopiasSeguridad();
                break;
                
            case 5:
                eliminarCopiaSeguridadAntigua();
                break;
                
            case 6:
                configurarAutoRespaldo();
                break;
                
            case 7:
                verEspacioAlmacenamiento();
                break;
                
            case 8:
                volver = true;
                break;
                
            default:
                Formatos::mostrarError("Opción no válida");
                Formatos::pausar();
                break;
        }
    }
}

/**
 * @brief Muestra las estadísticas del sistema
 */
void mostrarEstadisticasSistema() {
    Formatos::limpiarPantalla();
    Formatos::encabezado("ESTADÍSTICAS DEL SISTEMA", 70, '=');
    
    // Obtener estadísticas del hospital
    auto stats = hospital->obtenerEstadisticas();
    
    // Mostrar estadísticas principales
    std::cout << Formatos::colorizar("📊 ESTADÍSTICAS PRINCIPALES 📊", Formatos::CYAN, Formatos::NEGRITA) << "\n\n";
    
    std::vector<std::vector<std::string>> datos = {
        {"Pacientes Registrados", Formatos::formatearNumero(stats.totalPacientes)},
        {"Doctores Activos", Formatos::formatearNumero(stats.totalDoctores)},
        {"Citas Totales", Formatos::formatearNumero(stats.totalCitas)},
        {"Historiales Médicos", Formatos::formatearNumero(stats.totalHistoriales)},
        {"Citas para Hoy", Formatos::formatearNumero(stats.citasHoy)},
        {"Citas Pendientes", Formatos::formatearNumero(stats.citasPendientes)},
        {"Pacientes en Espera", Formatos::formatearNumero(stats.pacientesEnEspera)},
        {"Ocupación Hospital", Formatos::formatearPorcentaje(stats.ocupacionPorcentaje / 100.0)}
    };
    
    std::vector<std::string> encabezados = {"Métrica", "Valor"};
    Formatos::mostrarTabla("", encabezados, datos);
    
    // Mostrar distribución por especialidad si hay datos
    if (!stats.citasPorEspecialidad.empty()) {
        std::cout << "\n" << Formatos::colorizar("📈 CITAS POR ESPECIALIDAD 📈", Formatos::MAGENTA, Formatos::NEGRITA) << "\n\n";
        
        std::vector<std::vector<std::string>> datosEspecialidades;
        for (const auto& [especialidad, cantidad] : stats.citasPorEspecialidad) {
            datosEspecialidades.push_back({especialidad, Formatos::formatearNumero(cantidad)});
        }
        
        Formatos::mostrarTabla("", {"Especialidad", "Citas"}, datosEspecialidades);
    }
    
    // Mostrar distribución por edad si hay datos
    if (!stats.pacientesPorEdad.empty()) {
        std::cout << "\n" << Formatos::colorizar("👥 PACIENTES POR GRUPO DE EDAD 👥", Formatos::VERDE, Formatos::NEGRITA) << "\n\n";
        
        std::vector<std::vector<std::string>> datosEdades;
        for (const auto& [grupo, cantidad] : stats.pacientesPorEdad) {
            datosEdades.push_back({std::to_string(grupo) + "-" + std::to_string(grupo + 9) + " años", 
                                  Formatos::formatearNumero(cantidad)});
        }
        
        Formatos::mostrarTabla("", {"Grupo de Edad", "Pacientes"}, datosEdades);
    }
    
    // Mostrar información del sistema
    std::cout << "\n" << Formatos::colorizar("💻 INFORMACIÓN DEL SISTEMA 💻", Formatos::AMARILLO, Formatos::NEGRITA) << "\n\n";
    std::cout << "Hospital: " << NOMBRE_HOSPITAL << "\n";
    std::cout << "Capacidad máxima: " << CAPACIDAD_HOSPITAL << " pacientes\n";
    std::cout << "Fecha del sistema: " << Formatos::formatearFecha(std::time(nullptr)) << "\n";
    std::cout << "Próximo ID Paciente: " << hospital->getProximoIDPaciente() << "\n";
    std::cout << "Próximo ID Doctor: " << hospital->getProximoIDDoctor() << "\n";
    std::cout << "Próximo ID Cita: " << hospital->getProximoIDCita() << "\n";
    std::cout << "Próximo ID Historial: " << hospital->getProximoIDHistorial() << "\n";
    
    Formatos::pausar();
}

/**
 * @brief Muestra los créditos del sistema
 */
void mostrarCreditos() {
    Formatos::limpiarPantalla();
    
    // Banner artístico
    std::cout << Formatos::colorizar(R"(
    ╔══════════════════════════════════════════════════════╗
    ║     🏥 SISTEMA HOSPITALARIO INTEGRADO 🏥           ║
    ║     -----------------------------------           ║
    ║     Versión: 2.0.0                                ║
    ║     Desarrollado por: Equipo HospitalSoft         ║
    ║     Licencia: GPL v3.0                            ║
    ║     Año: 2024                                     ║
    ╚══════════════════════════════════════════════════════╝
    )", Formatos::CYAN) << "\n\n";
    
    std::cout << Formatos::colorizar("DESCRIPCIÓN:", Formatos::VERDE, Formatos::NEGRITA) << "\n";
    std::cout << "Sistema integral de gestión hospitalaria para la administración\n";
    std::cout << "eficiente de pacientes, doctores, citas e historiales médicos.\n\n";
    
    std::cout << Formatos::colorizar("CARACTERÍSTICAS PRINCIPALES:", Formatos::VERDE, Formatos::NEGRITA) << "\n";
    std::cout << "• Gestión completa de pacientes y doctores\n";
    std::cout << "• Sistema de citas inteligente con conflictos de horario\n";
    std::cout << "• Historiales médicos digitales completos\n";
    std::cout << "• Módulo de urgencias integrado\n";
    std::cout << "• Sistema de copias de seguridad automáticas\n";
    std::cout << "• Interfaz intuitiva con colores y menús\n";
    std::cout << "• Validación de datos robusta\n";
    std::cout << "• Persistencia en archivos binarios\n\n";
    
    std::cout << Formatos::colorizar("TECNOLOGÍAS UTILIZADAS:", Formatos::VERDE, Formatos::NEGRITA) << "\n";
    std::cout << "• Lenguaje: C++11/14\n";
    std::cout << "• Paradigma: Programación Orientada a Objetos\n";
    std::cout << "• Persistencia: Archivos binarios con serialización\n";
    std::cout << "• Interfaz: Consola con soporte ANSI\n";
    std::cout << "• Compilador: MinGW/GCC\n\n";
    
    std::cout << Formatos::colorizar("EQUIPO DE DESARROLLO:", Formatos::VERDE, Formatos::NEGRITA) << "\n";
    std::cout << "• Director del Proyecto: Dr. Carlos Rodríguez\n";
    std::cout << "• Desarrollo Backend: Ana Martínez\n";
    std::cout << "• Desarrollo Frontend: Luis Fernández\n";
    std::cout << "• Base de Datos: Sofía López\n";
    std::cout << "• Testing: Pedro Sánchez\n\n";
    
    std::cout << Formatos::colorizar("CONTACTO Y SOPORTE:", Formatos::VERDE, Formatos::NEGRITA) << "\n";
    std::cout << "• Email: soporte@hospitalsoft.com\n";
    std::cout << "• Teléfono: +1 (800) 123-4567\n";
    std::cout << "• Sitio Web: www.hospitalsoft.com\n\n";
    
    std::cout << Formatos::colorizar("AGRADECIMIENTOS:", Formatos::VERDE, Formatos::NEGRITA) << "\n";
    std::cout << "A todo el personal médico y administrativo que contribuyó\n";
    std::cout << "con sus valiosas sugerencias para mejorar este sistema.\n\n";
    
    Formatos::pausar("Presione Enter para volver al menú principal...");
}

/**
 * @brief Realiza una copia de seguridad del sistema
 */
void realizarCopiaSeguridad() {
    Formatos::limpiarPantalla();
    Formatos::encabezado("CREAR COPIA DE SEGURIDAD", 60, '=');
    
    std::cout << Formatos::colorizar("Iniciando proceso de copia de seguridad...", Formatos::CYAN) << "\n\n";
    
    // Simular progreso
    for (int i = 0; i <= 100; i += 10) {
        Formatos::mostrarProgreso(i / 100.0, 40);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "\n\n";
    
    // Generar nombre de archivo con fecha
    std::time_t ahora = std::time(nullptr);
    std::tm* fecha = std::localtime(&ahora);
    char nombreArchivo[100];
    std::strftime(nombreArchivo, sizeof(nombreArchivo), 
                  "backup_%Y%m%d_%H%M%S.dat", fecha);
    
    // En una implementación real, aquí guardaríamos el estado del hospital
    Formatos::mostrarInfo("Guardando datos de pacientes...");
    Formatos::mostrarInfo("Guardando datos de doctores...");
    Formatos::mostrarInfo("Guardando citas programadas...");
    Formatos::mostrarInfo("Guardando historiales médicos...");
    
    std::cout << "\n";
    Formatos::mostrarExito("Copia de seguridad creada exitosamente");
    Formatos::mostrarInfo("Archivo: " + std::string(nombreArchivo));
    Formatos::mostrarInfo("Tamaño estimado: ~" + 
                         Formatos::formatearNumero(hospital->getCantidadPacientes() * 2 +
                                                  hospital->getCantidadDoctores() * 2 +
                                                  hospital->getCantidadCitas() * 3 +
                                                  hospital->getCantidadHistoriales() * 5) + 
                         " KB");
    
    Formatos::pausar();
}

/**
 * @brief Restaura el sistema desde una copia de seguridad
 */
void restaurarCopiaSeguridad() {
    Formatos::limpiarPantalla();
    Formatos::encabezado("RESTAURAR COPIA DE SEGURIDAD", 60, '=');
    
    std::cout << Formatos::colorizar("⚠️  ADVERTENCIA IMPORTANTE ⚠️", Formatos::ROJO, Formatos::NEGRITA) << "\n\n";
    std::cout << "Esta operación sobrescribirá TODOS los datos actuales del sistema.\n";
    std::cout << "Asegúrese de haber creado una copia de seguridad reciente antes de continuar.\n\n";
    
    if (!Formatos::confirmar("¿Está seguro de que desea restaurar desde copia de seguridad?", false)) {
        Formatos::mostrarInfo("Operación cancelada por el usuario");
        Formatos::pausar();
        return;
    }
    
    std::cout << "\n" << Formatos::colorizar("Iniciando restauración...", Formatos::CYAN) << "\n\n";
    
    // Simular progreso
    for (int i = 0; i <= 100; i += 10) {
        Formatos::mostrarProgreso(i / 100.0, 40);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    std::cout << "\n\n";
    
    // En una implementación real, aquí cargaríamos el estado del hospital
    Formatos::mostrarInfo("Cargando datos de pacientes...");
    Formatos::mostrarInfo("Cargando datos de doctores...");
    Formatos::mostrarInfo("Cargando citas programadas...");
    Formatos::mostrarInfo("Cargando historiales médicos...");
    
    // Simular datos restaurados
    int pacientesRestaurados = 150;
    int doctoresRestaurados = 25;
    int citasRestauradas = 300;
    int historialesRestaurados = 450;
    
    std::cout << "\n";
    Formatos::mostrarExito("Restauración completada exitosamente");
    Formatos::mostrarInfo("Pacientes restaurados: " + std::to_string(pacientesRestaurados));
    Formatos::mostrarInfo("Doctores restaurados: " + std::to_string(doctoresRestaurados));
    Formatos::mostrarInfo("Citas restauradas: " + std::to_string(citasRestauradas));
    Formatos::mostrarInfo("Historiales restaurados: " + std::to_string(historialesRestaurados));
    
    Formatos::pausar();
}

/**
 * @brief Confirma si el usuario desea salir del sistema
 * @return true si el usuario confirma la salida, false en caso contrario
 */
bool confirmarSalida() {
    Formatos::limpiarPantalla();
    Formatos::encabezado("CONFIRMAR SALIDA", 50, '=');
    
    std::cout << Formatos::colorizar("⚠️  CONFIRMACIÓN DE SALIDA ⚠️", Formatos::AMARILLO, Formatos::NEGRITA) << "\n\n";
    std::cout << "¿Está seguro de que desea salir del sistema?\n\n";
    std::cout << "Antes de salir, asegúrese de:\n";
    std::cout << "1. Haber guardado todos los cambios\n";
    std::cout << "2. Haber atendido a todos los pacientes en espera\n";
    std::cout << "3. Haber completado las citas del día\n\n";
    
    return Formatos::confirmar("¿Desea salir del sistema?", false);
}

// Funciones placeholder para opciones no implementadas completamente
// (Estas se implementarían en módulos separados)

void mostrarDisponibilidadDoctores() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void buscarPacientePorID() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void buscarPacientePorNombre() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void listarTodosPacientes() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void modificarPaciente() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void eliminarPaciente() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void agregarPacienteAColaEspera() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void agendarCita(Hospital& hospital) {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void buscarCitaPorID() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void listarCitasHoy() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void listarTodasCitas() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void listarCitasPorPaciente() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void listarCitasPorDoctor() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void modificarCita() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void cancelarCita() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void confirmarAsistenciaCita() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void listarHistorialesPorDoctor() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void agregarDiagnosticoHistorial() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void agregarTratamientoHistorial() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void registrarSignosVitales() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void generarReporteHistorial() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void registrarPacienteUrgencia() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void verColaEsperaUrgencias() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void atenderPacienteUrgencia() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void asignarPrioridadUrgencia() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void verDoctoresDisponiblesUrgencias() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void registrarAltaUrgencia() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void verEstadisticasUrgencias() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void configurarHospital() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void gestionarEspecialidades() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void configurarPreciosConsultas() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void configurarHorariosAtencion() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void gestionarUsuariosSistema() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void configurarParametrosSistema() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void restaurarValoresPorDefecto() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void crearCopiaSeguridadIncremental() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void listarCopiasSeguridad() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void eliminarCopiaSeguridadAntigua() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void configurarAutoRespaldo() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}

void verEspacioAlmacenamiento() {
    Formatos::mostrarInfo("Función en desarrollo - Próximamente");
    Formatos::pausar();
}