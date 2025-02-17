@echo off
set BUILD_DIR=build
set BUILD_TYPE=Debug
for %%I in (.) do set "PROJECT_NAME=%%~nxI"

echo Select an option 
echo 1. Clean build
echo 2. Incremental build 
echo 3. Exit

set /p choice="Enter the number of your choice: "

if "%choice%"=="1" (
    echo Cleaning previous build...
    if exist %BUILD_DIR% (
        rmdir /s /q %BUILD_DIR%
    )

    echo Configuring CMake for STM32...
    cmake -G "MinGW Makefiles" -B %BUILD_DIR% -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DCMAKE_TOOLCHAIN_FILE=../stm32_toolchain.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

)  else if "%choice%"=="2" (
    echo Starting incremental build
)  else if "%choice%"=="3" (
    echo Terminated by user
    exit /b 0
    
)   else ( 
    echo Invalid choice.
    exit /b 1
)




echo Building the firmware...
cmake --build %BUILD_DIR% --config %BUILD_TYPE%

echo Checking for output files...
if not exist %BUILD_DIR%/output/%PROJECT_NAME%.bin (
    echo Error: Build failed! No %PROJECT_NAME%.bin found.
    exit /b 1
)

echo Build process completed successfully!
exit /b 0