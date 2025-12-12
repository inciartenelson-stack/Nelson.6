@echo off
echo Compilando sistema hospitalario (Proyecto 3 - POO y Modularización)...

REM Crear carpeta de datos si no existe (no es obligatorio, pero evita errores)
if not exist "datos" mkdir datos

REM Compilar todos los archivos .cpp en sus respectivas carpetas
g++ -Wall -Wextra -std=c++17 ^
hospital/Hospital.cpp ^
pacientes/Paciente.cpp pacientes/operacionesPacientes.cpp ^
doctores/Doctor.cpp doctores/operacionesDoctores.cpp ^
citas/Cita.cpp citas/operacionesCitas.cpp ^
historial/HistorialMedico.cpp historial/operacionesHistorial.cpp ^
persistencia/GestorArchivos.cpp ^
utilidades/Validaciones.cpp utilidades/Formatos.cpp ^
main.cpp ^
-o sistema_hospitalario.exe

REM Verificar resultado de compilación
if %errorlevel% equ 0 (
    echo.
    echo ✓ Compilación exitosa.
    echo Ejecutando...
    echo.
    sistema_hospitalario.exe
) else (
    echo.
    echo ❌ Error de compilación. Revise los mensajes anteriores.
    echo Asegúrese de que:
    echo   - Todos los archivos .hpp y .cpp existen
    echo   - Las rutas coinciden con la estructura del proyecto
    echo   - No hay errores de sintaxis o inclusiones faltantes
    pause
)