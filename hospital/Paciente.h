#pragma once

#include "Persona.h"

#include <string>

class Paciente : public Persona {
private:
    std::string id;
    std::string servicio;
    float temperatura;
    float presionArterial;
    int dolor;
    std::string tipoDolor;
    bool trauma;
	bool sintomasNeurologicos;
	bool requiereCirugia;
	int diasHospitalizado;



public:
    Paciente();
    Paciente(const std::string& id, 
        const std::string& nombre, 
        int edad, float temperatura, 
        float presionArterial, int dolor, 
        const std::string& tipoDolor, 
        bool trauma, bool sintomasNeurologicos, 
        bool requiereCirugia, int diasHospitalizado);

    const std::string& getId() const;
    const std::string& getServicio() const;
    std::string resumen() const override;
	bool getTrauma() const;
	bool getSintomasNeurologicos() const;
	bool getRequiereCirugia() const;
	float getTemperatura() const;
	float getPresionArterial() const;
	int getDolor() const;
	const std::string& getTipoDolor() const;
	int getDiasHospitalizado() const;
    void setServicio(const std::string& nuevoServicio);
    void mostrarDetalle() const;

};
