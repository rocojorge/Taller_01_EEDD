#pragma once

#include "ColaPacientes.h"
#include "HistorialAtenciones.h"
#include "Servicio.h"

#include <string>

class Hospital {
private:
    class NodoServicio {
    public:
        Servicio servicio;
        NodoServicio* siguiente;

        explicit NodoServicio(const std::string& nombre)
            : servicio(nombre), siguiente(nullptr) {}
    };

    static const int CANTIDAD_SERVICIOS = 8;
    static const char* const NOMBRES_SERVICIOS[CANTIDAD_SERVICIOS];

    NodoServicio* primerServicio;
    NodoServicio* ultimoServicio;
    ColaPacientes espera;
    HistorialAtenciones historial;

    void crearServicios();
    Servicio* buscarServicio(const std::string& nombre);
    const Servicio* buscarServicio(const std::string& nombre) const;
    bool existePaciente(const std::string& id) const;

public:
    Hospital();
    ~Hospital();
    Hospital(const Hospital&) = delete;
    Hospital& operator=(const Hospital&) = delete;
	int totalPacientes() const;
    bool cargarPacientes(const std::string& ruta);
    void mostrarCola() const;
    void atenderPacientes(int cantidad);
    void mostrarServicios() const;
    void mostrarDepartamento(int opcion) const;
    void mostrarHistorial() const;
    void buscarPacientePorId(const std::string& id) const;
};
