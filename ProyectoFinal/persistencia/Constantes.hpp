// persistencia/Constantes.hpp
#ifndef CONSTANTES_HPP
#define CONSTANTES_HPP

struct ArchivoHeader {
    int cantidadRegistros;
    int proximoID;
    int registrosActivos;
    int version;
};

namespace Rutas {
    constexpr const char* HOSPITAL = "datos/hospital.bin";
    constexpr const char* PACIENTES = "datos/pacientes.bin";
    constexpr const char* DOCTORES = "datos/doctores.bin";
    constexpr const char* CITAS = "datos/citas.bin";
    constexpr const char* HISTORIALES = "datos/historiales.bin";
}

#endif