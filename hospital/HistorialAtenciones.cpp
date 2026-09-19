#include "HistorialAtenciones.h"

#include <iostream>

HistorialAtenciones::HistorialAtenciones() : cima(nullptr), cantidad(0) {}

HistorialAtenciones::~HistorialAtenciones() {
    while (cima != nullptr) {
        NodoHistorial* eliminado = cima;
        cima = cima->siguiente;
        delete eliminado;
        cantidad--;
    }
	if(cantidad!=0) cantidad = 0;
}

void HistorialAtenciones::apilar(const Paciente& paciente) {
    NodoHistorial* nuevo = new NodoHistorial(paciente);
    nuevo->siguiente = cima;
    cima = nuevo;
    ++cantidad;
}

bool HistorialAtenciones::desapilar(Paciente& paciente) {
    if (cima == nullptr) return false;
    NodoHistorial* eliminado = cima;
    paciente = eliminado->paciente;
    cima = cima->siguiente;
    delete eliminado;
    --cantidad;
    return true;
}
const Paciente* HistorialAtenciones::verUltimo() const {
	if (cima == nullptr) return nullptr;
	return &cima->paciente;
}


bool HistorialAtenciones::estaVacio() const { return cima == nullptr; }
int HistorialAtenciones::size() const { return cantidad; }

void HistorialAtenciones::mostrar() const {
    std::cout << "\n=== HISTORIAL DE ULTIMAS ATENCIONES ===\n";
	std::cout << "Cantidad de atenciones registradas: " << cantidad << '\n';
    if (estaVacio()) {
        std::cout << "Aun no se han registrado atenciones.\n";
        return;
    }
    const NodoHistorial* actual = cima;
    while (actual != nullptr) {
        std::cout << "Nombre: " << actual->paciente.getNombre()
            << " | Edad: " << actual->paciente.getEdad()
            << " | Departamento: " << actual->paciente.getServicio() << '\n';
        actual = actual->siguiente;
    }
}
