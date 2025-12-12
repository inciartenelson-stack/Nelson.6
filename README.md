Este proyecto implementa un sistema de gestión hospitalaria en C++ siguiendo los principios de Programación Orientada a Objetos (POO) y una arquitectura modular por dominios, tal como se exige en el Proyecto 3: POO y Modularización.

El sistema permite gestionar:

🧑‍⚕️ Pacientes (con nombre, cédula, edad, género, correo electrónico y número de teléfono)
👨‍⚕️ Doctores (con especialidad, costo de consulta, disponibilidad, correo y teléfono)
📅 Citas médicas (con fecha/hora, estado y vinculación a paciente/doctores)
📋 Historial médico (diagnóstico, tratamiento, lista enlazada de consultas)
Todos los datos se persisten en archivos binarios dentro de la carpeta datos/, asegurando integridad y rendimiento mediante acceso aleatorio (seekg/seekp).

🗂️ Estructura del Proyecto
El código está organizado en módulos por dominio de responsabilidad:

ProyectoHospital_v3/
│
├── hospital/                   
├── pacientes/                 
├── doctores/                  
├── citas/                      
├── historial/                  
├── persistencia/              
├── utilidades/                 
│
├── main.cpp                    
├── compilar.bat               
└── datos/                     

✅ Cada módulo es autocontenido: todo lo relacionado con pacientes está en pacientes/, lo mismo para doctores, citas, etc.

 Principios de POO Aplicados
1. Encapsulamiento
Todos los atributos de las clases (Paciente, Doctor, etc.) son private.
Acceso controlado mediante getters (const) y setters con validación.
Ejemplo:
void Paciente::setEdad(int nuevaEdad) {
    if (Validaciones::validarRango(nuevaEdad, 0, 120)) {
        edad = nuevaEdad;
        fechaModificacion = time(nullptr);
    }
}

2. Abstracción
   
La lógica compleja está oculta dentro de los métodos.
El usuario de la clase solo ve una interfaz clara:
paciente.agregarCitaID(150); // Internamente: valida, actualiza contador, marca modificación

3. Responsabilidad Única
Persistencia: Archivos Binarios
Características:
Formato binario: eficiencia en lectura/escritura.
Header por archivo: almacena metadatos (cantidadRegistros, proximoID, etc.).
Acceso aleatorio: permite leer/modificar un registro sin cargar todo el archivo.
IDs únicos: generados por Hospital y persistidos entre ejecuciones.
Archivos generados en datos/:
hospital.bin
pacientes.bin
doctores.bin
citas.bin
historiales.bin
Métodos genéricos en GestorArchivos (Sección 6.6 del enunciado):
// Funciona para CUALQUIER entidad (Paciente, Doctor, Cita...)
bool guardarRegistro(void* registro, size_t tamano, const char* archivo);
bool leerRegistroPorID(int id, void* registro, size_t tamano, const char* archivo);

🖥️ Compilación y Ejecución
Compilador: g++ (parte de MinGW, MSYS2, etc.)
El compilador debe estar en el PATH
Pasos:
Clonar o descomprimir el proyecto.
Abrir una terminal en la carpeta raíz (ProyectoHospital_v3).
Ejecutar: compilar.bat

El script:
Compila todos los módulos con -std=c++17 -Wall -Wextra
Genera sistema_hospitalario.exe
Ejecuta el programa automáticamente si no hay errores
🔸 Nota: No se usa Makefile porque el enunciado permite adaptar la compilación a Windows mediante .bat.

🧪 Funcionalidades Implementadas
Gestión de Pacientes
Registrar nuevo paciente (con validación de cédula, email, teléfono)
Buscar por ID o cédula
Modificar datos
Listar todos
Ver historial médico
Gestión de Doctores
Registrar nuevo doctor (con especialidad válida)
Buscar por ID
Listar por especialidad
Actualizar disponibilidad y costo
Gestión de Citas
Agendar cita (con validación de fecha/hora laboral)
Marcar como atendida o cancelar
Listar citas pendientes
Historial Médico
Crear nuevo historial tras una cita
Consultar historial por paciente o ID

📏 Uso de Memoria
RAM: Solo se cargan en memoria los objetos necesarios en cada operación (ej: al buscar un paciente, se carga uno; al listar, se carga un array temporal).
Disco: Los archivos .bin crecen con el uso, pero el diseño evita carga innecesaria.
Tamaño promedio por registro:
Paciente: ~580 bytes
Doctor: ~550 bytes
Cita: ~50 bytes
HistorialMedico: ~1100 bytes
⚠️ No es un sistema multiusuario: no hay control de concurrencia. Diseñado para uso local.

📚 Referencias
Basado en el documento oficial: requerimientos_3.md
Estándar de C++: C++17
Compilador: g++
