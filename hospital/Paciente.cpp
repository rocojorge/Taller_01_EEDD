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

bool Paciente::getTrauma() const
{
    return this->trauma;
}

bool Paciente::getSintomasNeurologicos() const
{
    return this->sintomasNeurologicos;
}

bool Paciente::getRequiereCirugia() const
{
    return this->requiereCirugia;
}

float Paciente::getTemperatura() const
{
    return this->temperatura;
}

float Paciente::getPresionArterial() const
{
    return this->presionArterial;
}

int Paciente::getDolor() const
{
    return this->dolor;
}

const std::string& Paciente::getTipoDolor() const
{
    return this->tipoDolor;
}

int Paciente::getDiasHospitalizado() const
{
    return this->diasHospitalizado;
}
