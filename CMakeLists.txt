# Minimum CMake Version
cmake_minimum_required(VERSION 3.12)

# Project Definition
project(ArmProject)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

# Ensure all configurations (Debug, Release) respect these paths
foreach(OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG_UPPER)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG_UPPER} ${CMAKE_BINARY_DIR}/output)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG_UPPER} ${CMAKE_BINARY_DIR}/output)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG_UPPER} ${CMAKE_BINARY_DIR}/output)
endforeach()

# Enable STM32F429 definitions
add_definitions(-DSTM32F429xx)


# Define STM32 Microcontroller
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F429xx)

# CPU and FPU Parameters
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard)




# Startup and Linker Script Files
set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/startup/stm32F429_startup.c)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker/stm32F429_ls.ld)

# CMake Configuration
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Add CMSIS Headers
set(CMSIS_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/CMSIS/CMSIS/Core/Include
)

# Add STM32F429 Headers
set(STM32F429_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4/Include)

# Add CMSIS Source Files
set(CMSIS_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/STM32F4/Source/Templates/system_stm32f4xx.c 
)

# Source Directories
set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/App)
file(GLOB_RECURSE APP_SOURCES FOLLOW_SYMLINKS ${APP_DIR}/*.c)

# Define Executable
add_executable(${PROJECT_NAME}
    ${CMSIS_SOURCES}
    ${APP_SOURCES}
    ${STARTUP_SCRIPT})

# Include Directories
target_include_directories(${PROJECT_NAME} PRIVATE ${APP_DIR} ${CMSIS_INCLUDE_DIRS} ${STM32F429_INCLUDE_DIR})

# Compiler Flags
target_compile_options(${PROJECT_NAME} PRIVATE
    ${CPU_PARAMETERS}
    -Wall -Wextra -Wpedantic -Wno-unused-parameter
    )

# Linker Options
target_link_options(${PROJECT_NAME} PRIVATE
    -T${MCU_LINKER_SCRIPT} # Linker script
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_BINARY_DIR}/output/${PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc -lm -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)

# Generate Binary and Hex Files
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/output/${PROJECT_NAME}.hex 
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/output/${PROJECT_NAME}.bin)

