#ifndef OPERACIONES_DOCTORES_HPP
#define OPERACIONES_DOCTORES_HPP

#include "../hospital/Hospital.hpp"
#include "Doctor.hpp"

// Declaraciones de funciones de operaciones con doctores
void registrarDoctor(Hospital& hospital);
void buscarDoctorPorID();
void buscarDoctorPorCedula();
void listarTodosDoctores();
void listarDoctoresPorEspecialidad();
void modificarDoctor();
void eliminarDoctor();
void mostrarDisponibilidadDoctores();

#endif