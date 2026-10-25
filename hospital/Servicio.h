#pragma once

#include <string>
#include "AVL.h"

class Servicio {
private:
    std::string nombre;
    AVL arbolPacientes;
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
    bool agregarPaciente(const Paciente& paciente);
    bool eliminarPaciente(const std::string& id);
    void mostrarEstado() const;
    bool contieneId(const std::string& id) const;
    const Paciente* buscarPorId(const std::string& id) const;
    const Paciente* buscarPorNombre(const std::string& nombre) const;
};

