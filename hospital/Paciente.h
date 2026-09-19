#pragma once

#include "Persona.h"

#include <string>

class Paciente : public Persona {
private:
    std::string id;
    std::string servicio;

public:
    Paciente(const std::string& id, const std::string& nombre, int edad,
        const std::string& servicio);

    const std::string& getId() const;
    const std::string& getServicio() const;
    std::string resumen() const override;
};

#endif
