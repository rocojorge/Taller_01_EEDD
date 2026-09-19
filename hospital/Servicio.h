#pragma once

#include "Paciente.h"

#include <string>

class Servicio {
private:
    class NodoPaciente {
    public:
        Paciente paciente;
        NodoPaciente* siguiente;

        explicit NodoPaciente(const Paciente& paciente)
            : paciente(paciente), siguiente(nullptr) {}
    };

    std::string nombre;
    NodoPaciente* primero;
    NodoPaciente* ultimo;
    int cantidad;
    

public:
    explicit Servicio(const std::string& nombre);
    ~Servicio();
    Servicio(const Servicio&) = delete;
    Servicio& operator=(const Servicio&) = delete; //La idea es que con esto me blindo ante posibles cagadas que pueda tener, así
	// no se puede copiar ni asignar un objeto de la clase Servicio, lo que ayuda a prevenir errores y mantener la integridad de los datos
    bool estaVacio() const;
    const std::string& getNombre() const;
    int size() const;
    void agregarPaciente(const Paciente& paciente);
    void mostrarEstado() const;
    bool contieneId(const std::string& id) const;
    const Paciente* buscarPorId(const std::string& id) const;
};

