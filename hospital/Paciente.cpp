#include "Paciente.h"
#include <string>


Paciente::Paciente() : Persona(), id(""), servicio("") {}
Paciente::Paciente(const std::string& id, const std::string& nombre, int edad,
    const std::string& servicio)
    : Persona(nombre, edad), id(id), servicio(servicio) {}

const std::string& Paciente::getId() const { return id; }
const std::string& Paciente::getServicio() const { return servicio; }

std::string Paciente::resumen() const {
    return id + " - " + getNombre() + " (" + std::to_string(getEdad()) + ")";
}
