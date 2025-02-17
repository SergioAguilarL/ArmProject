# Minimum CMake Version
cmake_minimum_required(VERSION 3.12)

# CMake Configuration
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Project Definition
project(ArmProject)

##################################################################################################################################
################################################### MCU DEFINITIONS ##############################################################
##################################################################################################################################

# Enable STM32F429 definitions
add_definitions(-DSTM32F429xx)

# Define STM32 Microcontroller
set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F429xx)

##################################################################################################################################
################################################ CPU and FPU Parameters ##########################################################
##################################################################################################################################

set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
    )


##################################################################################################################################
################################################ Setting output directories ######################################################
##################################################################################################################################

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

##################################################################################################################################
########################################### Startup and Linker Script Files ######################################################
##################################################################################################################################

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32F4/Source/Templates/gcc/startup_stm32f429xx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker/stm32F429_ls.ld)

##################################################################################################################################
##################################### Setting Include Directories for the Project ################################################
##################################################################################################################################

# Add HAL Headers
set(STM32F4XX_HAL_INC_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32fxx_HAL/Inc

)

# Add STM32F429 BSP Headers
set(STM32F4XX_BSP_INC_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32F429_BSP

)

# Add Driver APP Headers

set(APP_INC_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/App/Inc

)

# Add Utils Headers 
set(UTILS_INC_DIRS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/utils/Inc

)

# Add CMSIS Headers
set(CMSIS_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/CMSIS/CMSIS/Core/Include
)

# Add STM32F429 Headers
set(STM32F429_INCLUDE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32F4/Include)



##################################################################################################################################
##################################### Setting Source Directories for the Project #################################################
##################################################################################################################################

# Add STM32FF429 Source Files
set(STM32FF429_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32F4/Source/Templates/system_stm32f4xx.c 
)

# App Directories
set(APP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/App)
file(GLOB_RECURSE APP_SOURCES FOLLOW_SYMLINKS ${APP_DIR}/*.c)

# Utils Directories
set(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Driver/utils)
file(GLOB_RECURSE UTILS_SOURCES FOLLOW_SYMLINKS ${UTILS_DIR}/*.c)

# HAL Source Directories
set(STM32F4XX_HAL_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32fxx_HAL/Src)
file(GLOB_RECURSE STM32F4XX_HAL_SRC_DIR FOLLOW_SYMLINKS ${STM32F4XX_HAL_SRC_DIR}/*.c)

# HAL FILTER template files that fail the build
list( FILTER STM32F4XX_HAL_SRC_DIR EXCLUDE REGEX ".*(stm32f4xx_hal_timebase_rtc_alarm_template\\.c|stm32f4xx_hal_timebase_rtc_wakeup_template\\.c|stm32f4xx_hal_timebase_tim_template\\.c)$")

#BSP Source Directories 
set(STM32F4XX_BSP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Driver/STM32F429_BSP)
file(GLOB_RECURSE STM32F4XX_BSP_SRC_DIR FOLLOW_SYMLINKS ${STM32F4XX_BSP_SRC_DIR}/*.c)
# BSP FILTER gryo driver no available for STM32F429i
list( FILTER STM32F4XX_BSP_SRC_DIR EXCLUDE REGEX ".*(stm32f429i_discovery_gyroscope\\.c)$")

##################################################################################################################################
################################################## Executable Definition  ########################################################
##################################################################################################################################

# Define Executable
add_executable(${PROJECT_NAME}
    ${STM32FF429_SOURCES}
    ${APP_SOURCES}
    ${UTILS_SOURCES}
    ${STM32F4XX_HAL_SRC_DIR}
    ${STM32F4XX_BSP_SRC_DIR}
    ${STARTUP_SCRIPT})


##################################################################################################################################
##################################################  Include Directories  #########################################################
##################################################################################################################################

target_include_directories(${PROJECT_NAME} PRIVATE ${APP_DIR} ${CMSIS_INCLUDE_DIRS} ${STM32F429_INCLUDE_DIR} ${STM32F4XX_HAL_INC_DIRS} ${APP_INC_DIRS} ${STM32F4XX_BSP_INC_DIRS} ${UTILS_INC_DIRS})


##################################################################################################################################
####################################################  Compiler Flags  ############################################################
##################################################################################################################################

target_compile_options(${PROJECT_NAME} PRIVATE
    ${CPU_PARAMETERS}
    -Wall -Wextra -Wpedantic -Wno-unused-parameter
    )


##################################################################################################################################
####################################################  Linker Options  ############################################################
##################################################################################################################################

target_link_options(${PROJECT_NAME} PRIVATE
    -T${MCU_LINKER_SCRIPT} # Linker script
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_BINARY_DIR}/output/${PROJECT_NAME}.map
    --specs=nosys.specs
    -Wl,--start-group
    -lc -lm -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)


##################################################################################################################################
#########################################  Generate Binary and Hex Files  ########################################################
##################################################################################################################################
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/output/${PROJECT_NAME}.hex 
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_BINARY_DIR}/output/${PROJECT_NAME}.bin)

