#include "Servicio.h"

#include <iostream>

Servicio::Servicio(const std::string& nombre)
    : nombre(nombre), primero(nullptr), ultimo(nullptr), cantidad(0) {}

Servicio::~Servicio() {
    while (primero != nullptr) {
        NodoPaciente* eliminado = primero;
        primero = primero->siguiente;
        delete eliminado;
    }
    ultimo = nullptr;
    cantidad = 0;
}

const std::string& Servicio::getNombre() const { return nombre; }
int Servicio::size() const { return cantidad; }

void Servicio::agregarPaciente(const Paciente& paciente) {
    NodoPaciente* nuevo = new NodoPaciente(paciente);
    if (ultimo == nullptr) primero = nuevo;
    else ultimo->siguiente = nuevo;
    ultimo = nuevo;
    ++cantidad;
}

void Servicio::mostrarEstado() const {
    std::cout << "\n=== ESTADO " << nombre << " ===\n";
    std::cout << "Pacientes en el departamento: " << cantidad << '\n';
    if (primero == nullptr) {
        std::cout << "Sin pacientes asignados.\n";
        return;
    }
    const NodoPaciente* actual = primero;
    while (actual != nullptr) {
        std::cout << "- " << actual->paciente.getNombre() << " ("
            << actual->paciente.getEdad() << ")\n";
        actual = actual->siguiente;
    }
}

bool Servicio::contieneId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

const Paciente* Servicio::buscarPorId(const std::string& id) const {
    const NodoPaciente* actual = primero;
    while (actual != nullptr) {
        if (actual->paciente.getId() == id) return &actual->paciente;
        actual = actual->siguiente;
    }
    return nullptr;
}
bool Servicio::estaVacio() const { 
    return primero == nullptr; 
}