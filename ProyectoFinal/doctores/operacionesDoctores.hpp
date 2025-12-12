#ifndef OPERACIONES_DOCTORES_HPP
#define OPERACIONES_DOCTORES_HPP

#include "../hospital/Hospital.hpp"
#include "Doctor.hpp"

/**
 * @file operacionesDoctores.hpp
 * @brief Funciones para la gestión de doctores en el sistema hospitalario
 * 
 * Este archivo contiene las declaraciones de las funciones que permiten
 * realizar operaciones CRUD (Crear, Leer, Actualizar, Eliminar) sobre
 * los doctores del sistema.
 */

/**
 * @brief Registra un nuevo doctor en el sistema
 * 
 * Solicita al usuario todos los datos necesarios para registrar un nuevo doctor,
 * valida la información y guarda el registro en el sistema. También actualiza
 * el estado del hospital.
 * 
 * @param hospital Referencia al objeto Hospital donde se registrará el doctor
 * 
 * @note Valida cédula profesional, teléfono, email y datos básicos
 * @note Genera un ID automático para el doctor
 * @note Guarda el registro en el archivo de doctores
 */
void registrarDoctor(Hospital& hospital);

/**
 * @brief Busca un doctor por su ID único
 * 
 * Solicita al usuario un ID de doctor y muestra toda la información
 * del doctor correspondiente si existe en el sistema.
 * 
 * @note Muestra información completa del doctor
 * @note Informa si el doctor no fue encontrado
 */
void buscarDoctorPorID();

/**
 * @brief Lista todos los doctores registrados en el sistema
 * 
 * Muestra una lista con información básica de todos los doctores
 * registrados en el sistema hospitalario.
 * 
 * @note Muestra información básica de cada doctor
 * @note Informa si no hay doctores registrados
 */
void listarTodosDoctores();

/**
 * @brief Lista doctores filtrados por especialidad
 * 
 * Solicita al usuario una especialidad médica y muestra todos los
 * doctores que tienen esa especialidad.
 * 
 * @note Permite filtrar por especialidad específica
 * @note Muestra información básica de los doctores encontrados
 */
void listarDoctoresPorEspecialidad();

/**
 * @brief Modifica los datos de un doctor existente
 * 
 * Permite actualizar los datos de un doctor existente en el sistema.
 * El usuario puede cambiar teléfono, email, costo de consulta y 
 * disponibilidad, manteniendo los datos que no se modifican.
 * 
 * @note Busca el doctor por ID
 * @note Permite modificar solo campos específicos
 * @note Valida los nuevos datos antes de actualizar
 */
void modificarDoctor();

/**
 * @brief Elimina un doctor del sistema (eliminación lógica)
 * 
 * Permite eliminar un doctor del sistema. En la implementación actual
 * esta función es de demostración y requiere implementación completa
 * de eliminación lógica o física.
 * 
 * @note Actualmente es una función de demostración
 * @warning Requiere implementación completa para producción
 */
void eliminarDoctor();

#endif // OPERACIONES_DOCTORES_HPP