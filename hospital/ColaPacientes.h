#pragma once

#include "Paciente.h"

class ColaPacientes {
private:
    class NodoCola { // Esto si es una Clase Nodo, con el struct no aplico lo visto en clase
    public:
        Paciente paciente;
        NodoCola* siguiente;

        explicit NodoCola(const Paciente& paciente)
            : paciente(paciente), siguiente(nullptr) {}
    };

    NodoCola* frente;
    NodoCola* final;
    int cantidad;

public:
    ColaPacientes();
    ~ColaPacientes();
    ColaPacientes(const ColaPacientes&) = delete;
    ColaPacientes& operator=(const ColaPacientes&) = delete;

    void encolar(const Paciente& paciente);
    bool desencolar(Paciente& paciente);
    bool estaVacia() const;
    int size() const;
    bool contieneId(const std::string& id) const;
    const Paciente* buscarPorId(const std::string& id) const;
    void mostrar() const;
};