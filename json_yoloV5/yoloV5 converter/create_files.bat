 @echo off
REM Usage: create_empty_files.bat output_folder number_of_files [prefix] [padding]

set "OUTPUT_DIR=%~1"
set "NUM_FILES=%~2"
set "PREFIX=%~3"
set "PADDING=%~4"

if "%PREFIX%"=="" set "PREFIX=file"
if "%PADDING%"=="" set "PADDING=4"

REM Create the output folder if it doesn't exist
if not exist "%OUTPUT_DIR%" (
    mkdir "%OUTPUT_DIR%"
)

REM Enable delayed expansion
setlocal EnableDelayedExpansion

for /L %%i in (1,1,%NUM_FILES%) do (
    set "NUM=%%i"
    set "PADDED=0000000000!NUM!"

    REM Handle padding manually
    if "%PADDING%"=="1" set "FINALNAME=!PADDED:~-1!"
    if "%PADDING%"=="2" set "FINALNAME=!PADDED:~-2!"
    if "%PADDING%"=="3" set "FINALNAME=!PADDED:~-3!"
    if "%PADDING%"=="4" set "FINALNAME=!PADDED:~-4!"
    if "%PADDING%"=="5" set "FINALNAME=!PADDED:~-5!"
    if "%PADDING%"=="6" set "FINALNAME=!PADDED:~-6!"

    set "FILENAME=!PREFIX!_!FINALNAME!.txt"
    type nul > "!OUTPUT_DIR!\!FILENAME!"
)

echo Done. %NUM_FILES% empty files created in %OUTPUT_DIR%

