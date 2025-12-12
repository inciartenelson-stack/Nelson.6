@echo off
title Sistema Hospitalario con Mantenimiento
color 0A
cls

:menu_principal
echo.
echo ╔══════════════════════════════════════════╗
echo ║   SISTEMA HOSPITALARIO COMPLETO          ║
echo ║   (Funciones de Visualización Activas)   ║
╚══════════════════════════════════════════╝
echo.
echo ═══════════════════════════════════════════
echo.
echo 1. Guardar Nuevo Doctor
echo 2. Guardar Nuevo Paciente
echo 3. Ver Doctores Registrados
echo 4. Ver Pacientes Registrados
echo 5. Historial Medico
echo 6. Citas y Agenda
echo 7. Mantenimiento del Sistema
echo 8. Salir del sistema
echo.
echo ═══════════════════════════════════════════
echo.
set /p opcion="Seleccione opcion (1-8): "

if "%opcion%"=="1" goto guardar_doctor
if "%opcion%"=="2" goto guardar_paciente
if "%opcion%"=="3" goto ver_doctores
if "%opcion%"=="4" goto ver_pacientes
if "%opcion%"=="5" goto historial_medico
if "%opcion%"=="6" goto citas_agenda
if "%opcion%"=="7" goto menu_mantenimiento
if "%opcion%"=="8" goto salir
echo Opcion no valida!
timeout /t 2 >nul
goto menu_principal

:historial_medico
cls
echo.
echo ═══════════════════════════════════════════
echo HISTORIAL MEDICO Y CLINICO
echo ═══════════════════════════════════════════
echo.
echo Modulo para consulta y gestion de historiales medicos.
echo.
pause
goto menu_principal

:citas_agenda
cls
echo.
echo ═══════════════════════════════════════════
echo CITAS Y GESTION DE AGENDA
echo ═══════════════════════════════════════════
echo.
echo Modulo para creacion, modificacion y consulta de citas.
echo.
pause
goto menu_principal

:guardar_doctor
cls
echo.
echo ═══════════════════════════════════════════
echo REGISTRAR NUEVO DOCTOR
echo ═══════════════════════════════════════════
echo.
echo Complete los datos del doctor:
echo.

set /p id_doctor="ID del doctor (obligatorio): "
if "%id_doctor%"=="" (
    echo ERROR: El ID es obligatorio
    timeout /t 2 >nul
    goto guardar_doctor
)

set /p nombre="Nombre (obligatorio): "
if "%nombre%"=="" (
    echo ERROR: El nombre es obligatorio
    timeout /t 2 >nul
    goto guardar_doctor
)

set /p apellido="Apellido (obligatorio): "
if "%apellido%"=="" (
    echo ERROR: El apellido es obligatorio
    timeout /t 2 >nul
    goto guardar_doctor
)

set /p especialidad="Especialidad: "
set /p telefono="Telefono: "
set /p email="Email: "

REM Crear directorio para datos si no existe
if not exist "datos" mkdir "datos"

REM Guardar en archivo
echo %id_doctor%,%nombre%,%apellido%,%especialidad%,%telefono%,%email%,%date%,%time% >> datos\doctores.csv

echo.
echo ═══════════════════════════════════════════
echo ¡DOCTOR GUARDADO EXITOSAMENTE!
echo ═══════════════════════════════════════════
echo.
echo Resumen:
echo    ID: %id_doctor%
echo    Nombre: %nombre% %apellido%
echo    Especialidad: %especialidad%
echo    Telefono: %telefono%
echo    Email: %email%
echo    Fecha: %date% %time%
echo.
echo Datos guardados en: datos\doctores.csv
echo.
pause
goto menu_principal

:ver_doctores
cls
echo.
echo ═══════════════════════════════════════════
echo LISTA DE DOCTORES REGISTRADOS
echo ═══════════════════════════════════════════
echo.

if exist "datos\doctores.csv" (
    echo ID   | Nombre         | Apellido       | Especialidad
    echo -----------------------------------------------------------
    setlocal enabledelayedexpansion
    for /f "tokens=1-4 delims=," %%a in ('type "datos\doctores.csv"') do (
        echo %%a | %%b           | %%c         | %%d
    )
    endlocal
) else (
    echo ✗ No se encontraron datos de doctores (datos\doctores.csv).
    echo   Por favor, registre al menos un doctor (Opción 1).
)

echo.
pause
goto menu_principal

:guardar_paciente
cls
echo.
echo ═══════════════════════════════════════════
echo REGISTRAR NUEVO PACIENTE
echo ═══════════════════════════════════════════
echo.
echo Complete los datos del paciente:
echo.

set /p id_paciente="ID del paciente (obligatorio): "
if "%id_paciente%"=="" (
    echo ERROR: El ID es obligatorio
    timeout /t 2 >nul
    goto guardar_paciente
)

set /p nombre="Nombre (obligatorio): "
if "%nombre%"=="" (
    echo ERROR: El nombre es obligatorio
    timeout /t 2 >nul
    goto guardar_paciente
)

set /p apellido="Apellido (obligatorio): "
if "%apellido%"=="" (
    echo ERROR: El apellido es obligatorio
    timeout /t 2 >nul
    goto guardar_paciente
)

set /p edad="Edad: "
set /p genero="Genero (M/F/O): "
set /p telefono="Telefono: "
set /p email="Email: "
set /p direccion="Direccion: "

REM Crear directorio para datos si no existe
if not exist "datos" mkdir "datos"

REM Guardar en archivo
echo %id_paciente%,%nombre%,%apellido%,%edad%,%genero%,%telefono%,%email%,%direccion%,%date%,%time% >> datos\pacientes.csv

echo.
echo ═══════════════════════════════════════════
echo ¡PACIENTE GUARDADO EXITOSAMENTE!
echo ═══════════════════════════════════════════
echo.
echo Resumen:
echo    ID: %id_paciente%
echo    Nombre: %nombre% %apellido%
echo    Edad: %edad%
echo    Genero: %genero%
echo    Telefono: %telefono%
echo    Email: %email%
echo    Direccion: %direccion%
echo    Fecha: %date% %time%
echo.
echo Datos guardados en: datos\pacientes.csv
echo.
pause
goto menu_principal

:ver_pacientes
cls
echo.
echo ═══════════════════════════════════════════
echo LISTA DE PACIENTES REGISTRADOS
echo ═══════════════════════════════════════════
echo.

if exist "datos\pacientes.csv" (
    echo ID   | Nombre         | Apellido       | Edad | Genero
    echo -----------------------------------------------------------
    setlocal enabledelayedexpansion
    for /f "tokens=1-5 delims=," %%a in ('type "datos\pacientes.csv"') do (
        echo %%a | %%b           | %%c         | %%d  | %%e
    )
    endlocal
) else (
    echo ✗ No se encontraron datos de pacientes (datos\pacientes.csv).
    echo   Por favor, registre al menos un paciente (Opción 2).
)

echo.
pause
goto menu_principal


:menu_mantenimiento
cls
echo.
echo ╔══════════════════════════════════════════╗
echo ║    MANTENIMIENTO DEL SISTEMA             ║
╚══════════════════════════════════════════╝
echo.
echo ═══════════════════════════════════════════
echo.
echo 1. Verificar estado del sistema
echo 2. Limpiar datos temporales
echo 3. Crear copia de seguridad
echo 4. Restaurar copia de seguridad
echo 5. Ver estadisticas
echo 6. Comprobar archivos del sistema
echo 7. Ver registros de actividad
echo 8. Volver al menu principal
echo.
echo ═══════════════════════════════════════════
echo.
set /p op_mantenimiento="Seleccione opcion (1-8): "

if "%op_mantenimiento%"=="1" goto verificar_estado
if "%op_mantenimiento%"=="2" goto limpiar_temporales
if "%op_mantenimiento%"=="3" goto crear_backup
if "%op_mantenimiento%"=="4" goto restaurar_backup
if "%op_mantenimiento%"=="5" goto ver_estadisticas
if "%op_mantenimiento%"=="6" goto comprobar_archivos
if "%op_mantenimiento%"=="7" goto ver_registros
if "%op_mantenimiento%"=="8" goto menu_principal
echo Opcion no valida!
timeout /t 2 >nul
goto menu_mantenimiento

:verificar_estado
cls
echo.
echo ═══════════════════════════════════════════
echo VERIFICACION DEL ESTADO DEL SISTEMA
echo ═══════════════════════════════════════════
echo.
echo Verificando componentes del sistema...
echo.
timeout /t 1 >nul

REM Verificar si existe directorio de datos
if exist "datos" (
    echo ✓ Directorio 'datos' encontrado
) else (
    echo ✗ Directorio 'datos' no existe
    echo   Se creara automaticamente al guardar datos
)

REM Verificar archivos de doctores
if exist "datos\doctores.csv" (
    for /f %%i in ('type "datos\doctores.csv" ^| find /c /v ""') do set num_doctores=%%i
    echo ✓ Archivo 'doctores.csv' encontrado (%num_doctores% registros)
) else (
    echo ✗ Archivo 'doctores.csv' no existe
)

REM Verificar archivos de pacientes
if exist "datos\pacientes.csv" (
    for /f %%i in ('type "datos\pacientes.csv" ^| find /c /v ""') do set num_pacientes=%%i
    echo ✓ Archivo 'pacientes.csv' encontrado (%num_pacientes% registros)
) else (
    echo ✗ Archivo 'pacientes.csv' no existe
)

REM Verificar espacio en disco
echo.
echo Espacio en disco disponible:
for /f "tokens=3" %%a in ('dir /-c . 2^>nul ^| find "bytes libres"') do (
    set bytes_libres=%%a
    set /a mb_libres=bytes_libres/1048576
    echo   %mb_libres% MB disponibles
)

echo.
echo Estado del sistema: OPERATIVO
echo.
pause
goto menu_mantenimiento

:limpiar_temporales
cls
echo.
echo ═══════════════════════════════════════════
echo LIMPIAR DATOS TEMPORALES
echo ═══════════════════════════════════════════
echo.
echo ADVERTENCIA: Esta accion eliminara archivos temporales.
echo ¿Esta seguro de continuar?
echo.
set /p confirmar="Escriba 'SI' para continuar: "

if /i not "%confirmar%"=="SI" (
    echo Operacion cancelada.
    timeout /t 2 >nul
    goto menu_mantenimiento
)

echo.
echo Limpiando archivos temporales...
echo.

REM Eliminar archivos .tmp, .temp, .bak
del /q *.tmp 2>nul
del /q *.temp 2>nul
del /q *.bak 2>nul

REM Eliminar archivos de backup antiguos (más de 30 días)
if exist "backup" (
    echo Eliminando backups antiguos...
    forfiles /p "backup" /s /m *.* /d -30 /c "cmd /c del @path"
)

REM Limpiar archivos de log
if exist "*.log" (
    echo Eliminando archivos de log...
    del /q *.log 2>nul
)

echo.
echo ✓ Limpieza completada exitosamente.
echo.
pause
goto menu_mantenimiento

:crear_backup
cls
echo.
echo ═══════════════════════════════════════════
echo CREAR COPIA DE SEGURIDAD
echo ═══════════════════════════════════════════
echo.
echo Creando copia de seguridad del sistema...
echo.

REM Crear directorio de backup si no existe
if not exist "backup" mkdir "backup"

set timestamp=%date:/=-%_%time::=-%
set timestamp=%timestamp: =_%

REM Crear backup de doctores
if exist "datos\doctores.csv" (
    copy "datos\doctores.csv" "backup\doctores_backup_%timestamp%.csv" >nul
    echo ✓ Backup de doctores creado
) else (
    echo ✗ No hay datos de doctores para respaldar
)

REM Crear backup de pacientes
if exist "datos\pacientes.csv" (
    copy "datos\pacientes.csv" "backup\pacientes_backup_%timestamp%.csv" >nul
    echo ✓ Backup de pacientes creado
) else (
    echo ✗ No hay datos de pacientes para respaldar
)

REM Crear archivo de información del backup
echo === INFORMACION DE BACKUP === > "backup\info_%timestamp%.txt"
echo Fecha: %date% %time% >> "backup\info_%timestamp%.txt"
echo Sistema: Hospitalario v1.0 >> "backup\info_%timestamp%.txt"
echo. >> "backup\info_%timestamp%.txt"

if exist "datos\doctores.csv" (
    for /f %%i in ('type "datos\doctores.csv" ^| find /c /v ""') do (
        echo Doctores respaldados: %%i >> "backup\info_%timestamp%.txt"
    )
)

if exist "datos\pacientes.csv" (
    for /f %%i in ('type "datos\pacientes.csv" ^| find /c /v ""') do (
        echo Pacientes respaldados: %%i >> "backup\info_%timestamp%.txt"
    )
)

echo.
echo ═══════════════════════════════════════════
echo ¡COPIA DE SEGURIDAD COMPLETADA!
echo ═══════════════════════════════════════════
echo.
echo Archivos creados en carpeta 'backup':
dir backup\*%timestamp%* /b
echo.
echo Total de backups disponibles:
dir backup\*.csv /b | find /c /v ""
echo.
pause
goto menu_mantenimiento

:restaurar_backup
cls
echo.
echo ═══════════════════════════════════════════
echo RESTAURAR COPIA DE SEGURIDAD
echo ═══════════════════════════════════════════
echo.
echo ADVERTENCIA: Esta accion sobrescribira los datos actuales.
echo ¿Esta seguro de continuar?
echo.
set /p confirmar="Escriba 'RESTAURAR' para continuar: "

if /i not "%confirmar%"=="RESTAURAR" (
    echo Operacion cancelada.
    timeout /t 2 >nul
    goto menu_mantenimiento
)

echo.
echo Listando copias de seguridad disponibles...
echo.

if not exist "backup" (
    echo ✗ No hay carpeta de backup
    echo   Cree primero una copia de seguridad
    pause
    goto menu_mantenimiento
)

echo Copias disponibles:
echo ───────────────────
set count=0
setlocal enabledelayedexpansion
for /f "delims=" %%f in ('dir backup\*.csv /b /o-d') do (
    set /a count+=1
    echo [!count!] %%f
)
endlocal & set count=%count%

if %count%==0 (
    echo No hay copias de seguridad disponibles
    pause
    goto menu_mantenimiento
)

echo.
set /p seleccion="Seleccione numero de backup a restaurar (1-%count%): "

setlocal enabledelayedexpansion
set index=0
set backup_file=
for /f "delims=" %%f in ('dir backup\*.csv /b /o-d') do (
    set /a index+=1
    if !index!==%seleccion% (
        set backup_file=%%f
        goto restaurar_archivo
    )
)

:restaurar_archivo
if "%backup_file%"=="" (
    echo Seleccion no valida.
    pause
    goto menu_mantenimiento
)

echo.
echo Restaurando backup: %backup_file%
echo.

REM Hacer backup de los datos actuales antes de restaurar
if exist "datos\doctores.csv" (
    copy "datos\doctores.csv" "datos\doctores_backup_antes_de_restauracion.csv" >nul
)

if exist "datos\pacientes.csv" (
    copy "datos\pacientes.csv" "datos\pacientes_backup_antes_de_restauracion.csv" >nul
)

REM Restaurar según el tipo de archivo
if "%backup_file:~0,8%"=="doctores" (
    copy "backup\%backup_file%" "datos\doctores.csv" >nul
    echo ✓ Doctores restaurados desde: %backup_file%
) else if "%backup_file:~0,9%"=="pacientes" (
    copy "backup\%backup_file%" "datos\pacientes.csv" >nul
    echo ✓ Pacientes restaurados desde: %backup_file%
) else (
    echo ✗ Tipo de backup no reconocido
)

echo.
echo ✓ Restauracion completada exitosamente.
echo.
pause
endlocal
goto menu_mantenimiento

:ver_estadisticas
cls
echo.
echo ═══════════════════════════════════════════
echo ESTADISTICAS DEL SISTEMA
echo ═══════════════════════════════════════════
echo.
echo Informacion general del sistema:
echo.

REM Obtener fecha y hora del sistema
echo Fecha del sistema: %date%
echo Hora del sistema:  %time%
echo.

setlocal enabledelayedexpansion

REM Contar doctores
set doctores=0
if exist "datos\doctores.csv" (
    for /f %%i in ('type "datos\doctores.csv" ^| find /c /v ""') do set doctores=%%i
)

REM Contar pacientes
set pacientes=0
if exist "datos\pacientes.csv" (
    for /f %%i in ('type "datos\pacientes.csv" ^| find /c /v ""') do set pacientes=%%i
)

REM Contar backups
set backups=0
if exist "backup" (
    for /f %%i in ('dir backup\*.csv /b ^| find /c /v ""') do set backups=%%i
)

echo ┌─────────────────────┬──────────────┐
echo │ Tipo de Datos       │ Cantidad     │
echo ├─────────────────────┼──────────────┤
echo │ Doctores            │ !doctores!            │
echo │ Pacientes           │ !pacientes!            │
echo │ Copias de seguridad │ !backups!            │
echo └─────────────────────┴──────────────┘
echo.

REM Mostrar tamaño de archivos
echo Tamaño de archivos:
echo ───────────────────
if exist "datos\doctores.csv" (
    for %%F in ("datos\doctores.csv") do (
        set /a kb=%%~zF/1024
        echo   Doctores.csv: !kb! KB
    )
)

if exist "datos\pacientes.csv" (
    for %%F in ("datos\pacientes.csv") do (
        set /a kb=%%~zF/1024
        echo   Pacientes.csv: !kb! KB
    )
)

echo.
echo Última actividad:
echo ─────────────────
if exist "datos\doctores.csv" (
    set ult_doctor=No disponible
    for /f "tokens=7,8 delims=," %%a in ('type "datos\doctores.csv"') do (
        set ult_doctor=%%a %%b
    )
    echo   Último doctor: !ult_doctor!
) else (
    echo   Último doctor: No disponible
)


if exist "datos\pacientes.csv" (
    set ult_paciente=No disponible
    for /f "tokens=9,10 delims=," %%a in ('type "datos\pacientes.csv"') do (
        set ult_paciente=%%a %%b
    )
    echo   Último paciente: !ult_paciente!
) else (
    echo   Último paciente: No disponible
)
endlocal

echo.
pause
goto menu_mantenimiento

:comprobar_archivos
cls
echo.
echo ═══════════════════════════════════════════
echo COMPROBACION DE ARCHIVOS DEL SISTEMA
echo ═══════════════════════════════════════════
echo.
echo Verificando integridad de archivos...
echo.

echo Archivos requeridos:
echo ───────────────────
echo [✓] sistema_hospitalario.bat (este archivo)
echo.

if exist "datos\" (
    echo [✓] Directorio 'datos/'
) else (
    echo [✗] Directorio 'datos/' (no existe)
)

if exist "datos\doctores.csv" (
    echo [✓] Archivo 'datos/doctores.csv'
    
    REM Verificar formato del archivo (simplificado)
    setlocal enabledelayedexpansion
    set format_ok=true
    for /f "tokens=1-3 delims=," %%a in ('type "datos\doctores.csv" 2^>nul') do (
        if "%%a"=="" set format_ok=false
        if "%%b"=="" set format_ok=false
        if "%%c"=="" set format_ok=false
    )
    if "!format_ok!"=="true" (
        echo   [✓] Formato CSV valido (estructura basica)
    ) else (
        echo   [✗] Formato CSV invalido (estructura basica no cumplida)
    )
    endlocal
) else (
    echo [✗] Archivo 'datos/doctores.csv' (no existe)
)

if exist "datos\pacientes.csv" (
    echo [✓] Archivo 'datos/pacientes.csv'
    
    REM Verificar formato del archivo (simplificado)
    setlocal enabledelayedexpansion
    set format_ok=true
    for /f "tokens=1-3 delims=," %%a in ('type "datos\pacientes.csv" 2^>nul') do (
        if "%%a"=="" set format_ok=false
        if "%%b"=="" set format_ok=false
        if "%%c"=="" set format_ok=false
    )
    if "!format_ok!"=="true" (
        echo   [✓] Formato CSV valido (estructura basica)
    ) else (
        echo   [✗] Formato CSV invalido (estructura basica no cumplida)
    )
    endlocal
) else (
    echo [✗] Archivo 'datos/pacientes.csv' (no existe)
)

if exist "backup\" (
    echo [✓] Directorio 'backup/'
    setlocal enabledelayedexpansion
    for /f %%i in ('dir backup\*.csv /b ^| find /c /v ""') do (
        echo   Contiene backups: %%i
    )
    endlocal
) else (
    echo [✗] Directorio 'backup/' (no existe)
)

echo.
echo Verificando permisos de escritura...
echo.
REM Intentar crear archivo de prueba
echo prueba > test_permissions.txt 2>nul
if exist "test_permissions.txt" (
    echo [✓] Permisos de escritura OK
    del test_permissions.txt >nul
) else (
    echo [✗] Error de permisos de escritura
)

echo.
echo ✓ Comprobacion completada.
echo.
pause
goto menu_mantenimiento

:ver_registros
cls
echo.
echo ═══════════════════════════════════════════
echo REGISTROS DE ACTIVIDAD
echo ═══════════════════════════════════════════
echo.
echo Mostrando ultimas actividades del sistema...
echo.

echo Actividad reciente de Doctores:
echo ───────────────────────────────
if exist "datos\doctores.csv" (
    echo Ultimos 5 doctores registrados:
    echo.
    REM Usa 'more' para simular 'tail -n 5' si no está disponible, mostrando las últimas líneas
    setlocal enabledelayedexpansion
    set doctores=0
    for /f %%i in ('type "datos\doctores.csv" ^| find /c /v ""') do set doctores=%%i
    set /a skip_lines=!doctores!-5
    if !skip_lines! lss 0 set skip_lines=0
    
    type "datos\doctores.csv" | more +!skip_lines! 2>nul
    endlocal
) else (
    echo No hay registros de doctores
)

echo.
echo Actividad reciente de Pacientes:
echo ────────────────────────────────
if exist "datos\pacientes.csv" (
    echo Ultimos 5 pacientes registrados:
    echo.
    REM Usa 'more' para simular 'tail -n 5' si no está disponible, mostrando las últimas líneas
    setlocal enabledelayedexpansion
    set pacientes=0
    for /f %%i in ('type "datos\pacientes.csv" ^| find /c /v ""') do set pacientes=%%i
    set /a skip_lines=!pacientes!-5
    if !skip_lines! lss 0 set skip_lines=0
    
    type "datos\pacientes.csv" | more +!skip_lines! 2>nul
    endlocal
) else (
    echo No hay registros de pacientes
)

echo.
echo Registros del sistema:
echo ─────────────────────
REM Mostrar archivos de log si existen
if exist "*.log" (
    echo Archivos de log encontrados:
    dir *.log /b
    echo.
    echo Ultimas lineas del log principal:
    type sistema.log | tail -n 10 2>nul || echo No hay log disponible
) else (
    echo No hay archivos de log disponibles
)

echo.
pause
goto menu_mantenimiento

:salir
cls
echo.
echo ═══════════════════════════════════════════
echo SALIENDO DEL SISTEMA
echo ═══════════════════════════════════════════
echo.
echo Gracias por usar el Sistema Hospitalario.
echo.
echo Resumen de la sesion:
echo.
if not exist "datos" (
    echo No se crearon datos en esta sesion.
) else (
    if exist "datos\doctores.csv" (
        for /f %%i in ('type "datos\doctores.csv" ^| find /c /v ""') do (
            echo ✓ Doctores registrados: %%i
        )
    )
    if exist "datos\pacientes.csv" (
        for /f %%i in ('type "datos\pacientes.csv" ^| find /c /v ""') do (
            echo ✓ Pacientes registrados: %%i
        )
    )
)
echo.
echo Presione cualquier tecla para salir...
pause >nul
exit