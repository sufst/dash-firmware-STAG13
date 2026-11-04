# CMakeLists.txt

# --- CMake configuration for the Dash project -------------------

cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME Dash)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM, C and C++ languages
enable_language(C CXX ASM)

# --- TinyUSB ----------------------------------------------------

include(FetchContent)
FetchContent_Declare(
    tinyusb
    GIT_REPOSITORY https://github.com/hathach/tinyusb.git
    GIT_TAG        0.17.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(tinyusb)

# Add the tinyusb library to the project
set(TINYUSB_SRC
    ${tinyusb_SOURCE_DIR}/src/tusb.c
    ${tinyusb_SOURCE_DIR}/src/common/tusb_fifo.c
    ${tinyusb_SOURCE_DIR}/src/device/usbd.c
    ${tinyusb_SOURCE_DIR}/src/device/usbd_control.c
    ${tinyusb_SOURCE_DIR}/src/class/cdc/cdc_device.c
    ${tinyusb_SOURCE_DIR}/src/class/msc/msc_device.c
    ${tinyusb_SOURCE_DIR}/src/portable/synopsys/dwc2/dcd_dwc2.c
    )

set(TINYUSB_INC
    ${tinyusb_SOURCE_DIR}/src
    ${tinyusb_SOURCE_DIR}/src/common
    ${tinyusb_SOURCE_DIR}/src/device
    ${tinyusb_SOURCE_DIR}/src/class/cdc
    ${tinyusb_SOURCE_DIR}/src/class/msc
)

# --- End TinyUSB ------------------------------------------------

# --- Project Setup ----------------------------------------------

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/SUFST/Inc/lv_conf.h CACHE STRING "" FORCE)
add_subdirectory(SUFST/Middlewares/lvgl)
target_link_libraries(lvgl PUBLIC stm32cubemx)

set_target_properties(lvgl_examples lvgl_demos PROPERTIES EXCLUDE_FROM_ALL TRUE)

# EEZ Studio generates one source file per font/image, so pick up whatever is there
file(GLOB EEZ_UI_SRC CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/eez-Stag12/src/ui/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/eez-Stag12/src/ui/*.cpp
)

# Source directories
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    SUFST/Src/bsp_sd_override.c
    SUFST/Middlewares/can-defs/out/can_t.c
    SUFST/Middlewares/can-defs/out/can_s.c
    Middlewares/TinyUSB/Src/usb_descriptors.c
    Middlewares/TinyUSB/Src/msc_diskio_bridge.c
    Middlewares/TinyUSB/Src/usb_irq.c
    Middlewares/TinyUSB/Src/usb_init.c
    ${TINYUSB_SRC}
    ${EEZ_UI_SRC}
    SUFST/Src/can_rx_handlers.c
    SUFST/Src/uptime.c
    SUFST/Src/dash_diag.c
    SUFST/Src/screen_select.c
    SUFST/Src/warning_levels.cpp
)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    SUFST/Inc
    SUFST/Middlewares
    SUFST/Middlewares/can-defs/out
    Middlewares/TinyUSB/Inc
    ${TINYUSB_INC}
    eez-Stag12/src/ui
)

# Colour theme the dash starts in (themes are defined in the EEZ Studio project)
set(DASH_THEME "dash-white-bg" CACHE STRING "Dash colour theme: dash-white-bg or dash-black-bg")
set_property(CACHE DASH_THEME PROPERTY STRINGS dash-white-bg dash-black-bg)
message("Dash theme: " ${DASH_THEME})

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined compile definitions
    CFG_TUSB_MCU=OPT_MCU_STM32F7
    DASH_THEME="${DASH_THEME}"
)

set_source_files_properties(eez-Stag12/src/ui/screens.c PROPERTIES
    COMPILE_OPTIONS "-include${CMAKE_CURRENT_SOURCE_DIR}/SUFST/Inc/eez_compat.h"
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx
    lvgl
)

# `cmake --build <dir> --target flash`
# builds first if stale, then programs the ELF directly over ST-Link via OpenOCD (program + verify + reset + run)
add_custom_target(flash
    COMMAND openocd -f interface/stlink.cfg -f target/stm32f7x.cfg
            -c "program $<TARGET_FILE:${CMAKE_PROJECT_NAME}> verify reset exit"
    DEPENDS ${CMAKE_PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Flashing ${CMAKE_PROJECT_NAME} via OpenOCD/ST-Link"
    USES_TERMINAL
)
