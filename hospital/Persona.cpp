#include "Persona.h"

Persona::Persona() : nombre(""), edad(0) {}

Persona::Persona(const std::string& nombre, int edad) : nombre(nombre), edad(edad) {}
Persona::~Persona() = default;

const std::string& Persona::getNombre() const { return nombre; }
int Persona::getEdad() const { return edad; }
