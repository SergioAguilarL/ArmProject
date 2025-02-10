@echo off

for %%I in (.) do set "BINARY_NAME=%%~nxI"


echo Choose an option
echo 1. Flash Binary for %BINARY_NAME%
echo 2. Cancel
set /p choice="Enter the number of your choice: "

if "%choice%"=="1" (
    
    cd build/output
    openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program %BINARY_NAME%.bin verify reset exit 0x08000000"
    cd../..
    
)  else if "%choice%"=="2" (

    
    exit /b 1

)  else  (
    exit /b 1
)