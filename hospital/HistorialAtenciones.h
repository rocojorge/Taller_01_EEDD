#pragma once

#include "Paciente.h"

class HistorialAtenciones {
private:
    class NodoHistorial {
    public:
        Paciente paciente;
        NodoHistorial* siguiente;

        explicit NodoHistorial(const Paciente& paciente)
            : paciente(paciente), siguiente(nullptr) {}
    };

    NodoHistorial* cima;
    int cantidad;

public:
    HistorialAtenciones();
    ~HistorialAtenciones();
    HistorialAtenciones(const HistorialAtenciones&) = delete;
    HistorialAtenciones& operator=(const HistorialAtenciones&) = delete;

    void apilar(const Paciente& paciente);
	bool desapilar(Paciente& paciente);
	const Paciente* verUltimo() const;
    bool estaVacio() const;
    int size() const;
    void mostrar() const;
};


