#ifndef FUNCIONES_PACIENTE_HPP
#define FUNCIONES_PACIENTE_HPP

#include "Paciente.hpp"
#include "../persistencia/GestorArchivos.hpp"
#include "../persistencia/Constantes.hpp"
#include <iostream>

/**
 * @brief Registra un nuevo paciente en el sistema del hospital
 * 
 * Esta función solicita al usuario los datos del paciente, valida la información
 * y guarda el registro tanto del paciente como del estado actualizado del hospital.
 * 
 * @param hospital Referencia al objeto Hospital donde se registrará el paciente
 */
void registrarPaciente(Hospital& hospital);

#endif // FUNCIONES_PACIENTE_HPP