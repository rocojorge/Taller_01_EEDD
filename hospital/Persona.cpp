#include "Persona.h"
#include <string>

class Persona {
private:
    std::string nombre;
    int edad;

public:
    Persona(const std::string& nombre, int edad);
    virtual ~Persona();

    const std::string& getNombre() const;
    int getEdad() const;
    virtual std::string resumen() const = 0;
};
