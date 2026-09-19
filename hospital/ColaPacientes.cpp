#include "ColaPacientes.h"

#include <iostream>

ColaPacientes::ColaPacientes() : frente(nullptr), final(nullptr), cantidad(0) {}

ColaPacientes::~ColaPacientes() {
    //Paciente paciente("", "", 0, "");
    while (frente != nullptr) {
		NodoCola* eliminado = frente;
		frente = frente->siguiente;
		delete eliminado;
		--cantidad;
    }
	final = nullptr;
}

void ColaPacientes::encolar(const Paciente& paciente) {
    NodoCola* nuevo = new NodoCola(paciente);
    if (final == nullptr) {
        frente = nuevo;
    }
    else {
        final->siguiente = nuevo;
    }
    final = nuevo;
    ++cantidad;
}

bool ColaPacientes::desencolar(Paciente& paciente) {
    if (frente == nullptr) return false;
    NodoCola* eliminado = frente;
    paciente = eliminado->paciente;
    frente = frente->siguiente;
    if (frente == nullptr) final = nullptr;
    delete eliminado;
    --cantidad;
    return true;
}

bool ColaPacientes::estaVacia() const { return frente == nullptr; }
int ColaPacientes::size() const { return cantidad; }

bool ColaPacientes::contieneId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

const Paciente* ColaPacientes::buscarPorId(const std::string& id) const {
    const NodoCola* actual = frente;
    while (actual != nullptr) {
        if (actual->paciente.getId() == id) return &actual->paciente;
        actual = actual->siguiente;
    }
    return nullptr;
}

void ColaPacientes::mostrar() const {
    if (estaVacia()) {
        std::cout << "No hay pacientes esperando. :D\n";
        return;
    }
    const NodoCola* actual = frente;
    int posicion = 1;
    while (actual != nullptr) {
        std::cout << posicion++ << ". " << actual->paciente.resumen() << '\n';
        actual = actual->siguiente;
    }
}
