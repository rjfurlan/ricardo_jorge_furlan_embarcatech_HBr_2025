# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# set(CMAKE_BUILD_TYPE "Debug")
# set(PICO_DEOPTIMIZED_DEBUG 1)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(lab-01-galton-board C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(lab-01-galton-board
        app/ball.c
        app/balls.c
        app/bell.c
        app/gb_speed.c
        app/gb_structure.c
        app/histogram_bars.c
        app/histogram_bell.c
        app/histogram_data.c
        app/input.c
        app/main.c
        app/menu.c
        app/menu_structure_histogram.c
        app/menu_structure_main.c
        app/menu_structure_play.c
        app/play.c
        lib_bitdoglab/ads/ads.c
        lib_bitdoglab/buttons/buttons.c
        lib_bitdoglab/oled/i2c.c
        lib_bitdoglab/oled/display.c
        lib_ext/ssd1306_i2c.c
        )

pico_set_program_name(lab-01-galton-board "lab-01-galton-board")
pico_set_program_version(lab-01-galton-board "0.1")

# no_flash means the target is to run from RAM
pico_set_binary_type(lab-01-galton-board no_flash)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(lab-01-galton-board 1)
pico_enable_stdio_usb(lab-01-galton-board 1)

# Add the standard library to the build
target_link_libraries(lab-01-galton-board
        pico_stdlib
        pico_rand
        hardware_adc
        hardware_i2c
        )

# Add the standard include files to the build
target_include_directories(lab-01-galton-board PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

# Add any user requested libraries
target_link_libraries(lab-01-galton-board 
        
        )

pico_add_extra_outputs(lab-01-galton-board)




# === GENERATE AUTOMATIC DOCUMENTATION (OPTIONAL) ===

# Creates an option for the user to decide whether to generate documentation
# option(GENERATE_DOCUMENTATION "Generate project documentation using Doxygen" OFF)
option(GENERATE_DOCUMENTATION "Generate project documentation using Doxygen" ON)

# Try to find Doxygen installed
find_package(Doxygen)

if (DOXYGEN_FOUND AND GENERATE_DOCUMENTATION)
    message(STATUS "Doxygen found. Configuring documentation generation...")

    # Defines the configuration files
    set(DOXYGEN_IN  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    # Creates the documentation target
    add_custom_target(doc_doxygen
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating documentation with Doxygen..."
        VERBATIM
    )
    
    # Makes the documentation be generated only after compiling the project
    add_dependencies(lab-01-galton-board doc_doxygen)
else()
    if(GENERATE_DOCUMENTATION)
        message(WARNING "Doxygen not found! Documentation will not be generated")
    endif()
endif()
