#include "Servicio.h"

#include <iostream>

Servicio::Servicio(const std::string& nombre) : nombre(nombre), cantidad(0) {}
Servicio::~Servicio() = default;

const std::string& Servicio::getNombre() const { return nombre; }
int Servicio::size() const { return cantidad; }

bool Servicio::agregarPaciente(const Paciente& paciente) {
    if (!arbolPacientes.insertar(paciente)) return false;
    ++cantidad;
    return true;
}

bool Servicio::eliminarPaciente(const std::string& id) {
    if (!arbolPacientes.eliminar(id)) return false;
    --cantidad;
    return true;
}

void Servicio::mostrarEstado() const {
    std::cout << "\n=== ESTADO " << nombre << " ===\n";
    std::cout << "Pacientes en el departamento: " << cantidad << '\n';
    if (arbolPacientes.estaVacio()) {
        std::cout << "Sin pacientes asignados.\n";
        return;
    }
    std::cout << "Altura del AVL: " << this->getAltura()
        << " | Factor de balance de la raiz: " << this->getFactorBalance() << "\n";
    std::cout << "\nInorden (ordenado por ID):\n";
    this->mostrarInOrden();
    std::cout << "\nPreorden:\n";
    this->mostrarPreOrden();
    std::cout << "\nPostorden:\n";
    this->mostrarPostOrden();
}

bool Servicio::contieneId(const std::string& id) const {
    return buscarPorId(id) != nullptr;
}

const Paciente* Servicio::buscarPorId(const std::string& id) const {
    return arbolPacientes.buscarPorId(id);
}
const Paciente* Servicio::buscarPorNombre(const std::string& nombre) const {
    return arbolPacientes.buscarPorNombre(nombre);
}
bool Servicio::estaVacio() const { return arbolPacientes.estaVacio(); }
