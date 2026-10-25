cmake_minimum_required(VERSION 3.16)
project(HospitalMarmajaTaller2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(hospital
    hospital/ArbolDecision.cpp
    hospital/AVL.cpp
    hospital/ColaPacientes.cpp
    hospital/HistorialAtenciones.cpp
    hospital/Hospital_.cpp
    hospital/NodoAVL.cpp
    hospital/Paciente.cpp
    hospital/Persona.cpp
    hospital/Servicio.cpp
    hospital/hospital.cpp
)

target_include_directories(hospital PRIVATE hospital)
