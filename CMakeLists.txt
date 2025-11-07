cmake_minimum_required(VERSION 3.10)

# Información del proyecto
project(PRT7_Decoder_Arturo VERSION 1.0 LANGUAGES CXX)

# Estándar de C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Archivos fuente
set(SOURCES
    src/main.cpp
    src/TramaLoad.cpp
    src/TramaMap.cpp
    src/RotorDeMapeo.cpp
    src/ListaDeCarga.cpp
    src/SerialReader.cpp
)

# Archivos de encabezado
set(HEADERS
    src/TramaBase.h
    src/TramaLoad.h
    src/TramaMap.h
    src/RotorDeMapeo.h
    src/ListaDeCarga.h
    src/SerialReader.h
)

# Ejecutable
add_executable(prt7_decoder ${SOURCES} ${HEADERS})

# Incluir directorio de headers
target_include_directories(prt7_decoder PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Configuración específica para Windows
if(WIN32)
    target_compile_definitions(prt7_decoder PRIVATE _WIN32)
endif()

# Instalación
install(TARGETS prt7_decoder DESTINATION bin)

# Información de compilación
message(STATUS "Configurando PRT-7 Decoder Arturo v${PROJECT_VERSION}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")