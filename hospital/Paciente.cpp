#include "Paciente.h"
#include <string>
#include <iostream>


Paciente::Paciente() : Persona(), id(""), servicio(""), temperatura(0), presionArterial(0), dolor(0), tipoDolor(""), trauma(false), sintomasNeurologicos(false), requiereCirugia(false), diasHospitalizado(0) {}
Paciente::Paciente(const std::string& id, 
    const std::string& nombre, 
    int edad, 
    float temperatura, 
    float presionArterial, 
    int dolor, 
    const std::string& tipoDolor, 
    bool trauma,
    bool sintomasNeurologicos, 
    bool requiereCirugia, 
    int diasHospitalizado) : Persona(nombre, edad), 
    id(id),
    servicio(""),
    temperatura(temperatura), 
    presionArterial(presionArterial), 
    dolor(dolor), 
    tipoDolor(tipoDolor), 
    trauma(trauma), 
    sintomasNeurologicos(sintomasNeurologicos), 
    requiereCirugia(requiereCirugia), 
    diasHospitalizado(diasHospitalizado) {}


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

void Paciente::setServicio(const std::string& nuevoServicio)
{
    servicio = nuevoServicio;
}

void Paciente::mostrarDetalle() const
{
    std::cout << "ID: " << id << "\n"
        << "Nombre: " << getNombre() << "\n"
        << "Edad: " << getEdad() << "\n"
        << "Temperatura: " << temperatura << "\n"
        << "Presion arterial: " << presionArterial << "\n"
        << "Dolor (0-10): " << dolor << "\n"
        << "Tipo de dolor: " << tipoDolor << "\n"
        << "Trauma: " << (trauma ? "Si" : "No") << "\n"
        << "Sintomas neurologicos: " << (sintomasNeurologicos ? "Si" : "No") << "\n"
        << "Requiere cirugia: " << (requiereCirugia ? "Si" : "No") << "\n"
        << "Dias hospitalizado: " << diasHospitalizado << "\n"
        << "Servicio: " << (servicio.empty() ? "Pendiente" : servicio) << "\n";
}
