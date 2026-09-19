#pragma once
#include <string>

class Persona {
protected:
    std::string nombre;
    int edad;

public:
    Persona();
    Persona(const std::string& nombre, int edad);
    virtual ~Persona();

    const std::string& getNombre() const;
    int getEdad() const;
    virtual std::string resumen() const = 0;
};

