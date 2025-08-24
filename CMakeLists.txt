cmake_minimum_required(VERSION 3.16)
project(atedot C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Default to Release build if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Add include directory
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files in src (recursively)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Split out main.c from library sources
list(FILTER SRC_FILES EXCLUDE REGEX "src/main.c$")

# Build library from src (everything except main.c)
add_library(atedot_lib ${SRC_FILES})

# Build main executable (depends on library)
add_executable(atedot src/main.c)
target_link_libraries(atedot PRIVATE atedot_lib m)

# Build all examples (one executable per .c file)
file(GLOB EXAMPLES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/examples/*.c)
foreach(EX ${EXAMPLES})
    get_filename_component(EX_NAME ${EX} NAME_WE)
    add_executable(${EX_NAME} ${EX})
    target_link_libraries(${EX_NAME} PRIVATE atedot_lib m)
endforeach()

# --- Install paths ---
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(WIN32)
        # Default to local AppData/bin for Windows
        set(CMAKE_INSTALL_PREFIX "$ENV{LOCALAPPDATA}/atedot" CACHE PATH "default install path" FORCE)
    else()
        # Default to ~/.local for Linux/macOS
        set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.local" CACHE PATH "default install path" FORCE)
    endif()
endif()

install(TARGETS atedot DESTINATION bin)
