#include "Hospital_.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>

const char* const Hospital::NOMBRES_SERVICIOS[Hospital::CANTIDAD_SERVICIOS] = {
    "Urgencias", "Medicina General", "Cardiologia", "Neurologia",
    "Traumatologia", "Cirugia", "Pediatria", "Hospitalizacion"
};

namespace {
    std::string limpiar(const std::string& texto) {
        const std::string espacios = " \t\r\n";
        const std::size_t inicio = texto.find_first_not_of(espacios);
        if (inicio == std::string::npos) return "";
        return texto.substr(inicio, texto.find_last_not_of(espacios) - inicio + 1);
    }

    std::string normalizarServicio(std::string servicio) {
        servicio = limpiar(servicio);
        for (char& caracter : servicio) {
            caracter = static_cast<char>(std::tolower(static_cast<unsigned char>(caracter)));
        }
        if (servicio == "cardiolog\xC3\xAD" "a") return "cardiologia";
        if (servicio == "neurolog\xC3\xAD" "a") return "neurologia";
        if (servicio == "traumatolog\xC3\xAD" "a") return "traumatologia";
        if (servicio == "cirug\xC3\xAD" "a") return "cirugia";
        if (servicio == "pediatr\xC3\xAD" "a") return "pediatria";
        if (servicio == "hospitalizaci\xC3\xB3" "n") return "hospitalizacion";
        return servicio;
    }

    bool convertirEdad(const std::string& texto, int& edad) {
        try {
            std::size_t procesados = 0;
            edad = std::stoi(limpiar(texto), &procesados);
            return procesados == limpiar(texto).size() && edad >= 0 && edad <= 130;
        }
        catch (...) {
            return false;
        }
    }
}

Hospital::Hospital() : primerServicio(nullptr), ultimoServicio(nullptr) { crearServicios(); }

Hospital::~Hospital() {
    while (primerServicio != nullptr) {
        NodoServicio* eliminado = primerServicio;
        primerServicio = primerServicio->siguiente;
        delete eliminado;
    }
    ultimoServicio = nullptr;
}

void Hospital::crearServicios() {
    // Los punteros recorren el catálogo fijo para construir la lista enlazada.
    const char* const* nombre = NOMBRES_SERVICIOS;
    const char* const* limite = NOMBRES_SERVICIOS + CANTIDAD_SERVICIOS;
    while (nombre != limite) {
        NodoServicio* nuevo = new NodoServicio(*nombre);
        if (ultimoServicio == nullptr) primerServicio = nuevo;
        else ultimoServicio->siguiente = nuevo;
        ultimoServicio = nuevo;
        ++nombre;
    }
}

Servicio* Hospital::buscarServicio(const std::string& nombreBuscado) {
    const std::string normalizado = normalizarServicio(nombreBuscado);
    NodoServicio* actual = primerServicio;
    const char* const* nombre = NOMBRES_SERVICIOS;
    while (actual != nullptr && nombre != NOMBRES_SERVICIOS + CANTIDAD_SERVICIOS) {
        if (normalizado == normalizarServicio(*nombre)) return &actual->servicio;
        actual = actual->siguiente;
        ++nombre;
    }
    return nullptr;
}

const Servicio* Hospital::buscarServicio(const std::string& nombreBuscado) const {
    const std::string normalizado = normalizarServicio(nombreBuscado);
    const NodoServicio* actual = primerServicio;
    const char* const* nombre = NOMBRES_SERVICIOS;
    while (actual != nullptr && nombre != NOMBRES_SERVICIOS + CANTIDAD_SERVICIOS) {
        if (normalizado == normalizarServicio(*nombre)) return &actual->servicio;
        actual = actual->siguiente;
        ++nombre;
    }
    return nullptr;
}

bool Hospital::existePaciente(const std::string& id) const {
    const NodoServicio* actual = primerServicio;
    while (actual != nullptr) {
        if (actual->servicio.contieneId(id)) return true;
        actual = actual->siguiente;
    }
    return false;
}

int Hospital::totalPacientes() const {
	int total = espera.size();
	const NodoServicio* actual = primerServicio;
	while (actual != nullptr) {
		total += actual->servicio.size();
		actual = actual->siguiente;
	}
	return total;
}

bool Hospital::cargarPacientes(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo) {
        std::cout << "No fue posible abrir el archivo: " << ruta << "\n";
        return false;
    }
    std::string linea;
    int numeroLinea = 0;
    int cargados = 0;
    while (std::getline(archivo, linea)) {
        ++numeroLinea;
        const std::size_t p1 = linea.find(';');
        const std::size_t p2 = p1 == std::string::npos ? p1 : linea.find(';', p1 + 1);
        const std::size_t p3 = p2 == std::string::npos ? p2 : linea.find(';', p2 + 1);
        if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos ||
            linea.find(';', p3 + 1) != std::string::npos) {
            if (!limpiar(linea).empty()) std::cout << "Linea " << numeroLinea << " ignorada: formato invalido.\n";
            continue;
        }
        const std::string id = limpiar(linea.substr(0, p1));
        const std::string nombre = limpiar(linea.substr(p1 + 1, p2 - p1 - 1));
        const std::string edadTexto = linea.substr(p2 + 1, p3 - p2 - 1);
        Servicio* servicio = buscarServicio(limpiar(linea.substr(p3 + 1)));
        int edad = 0;
        if (id.empty() || nombre.empty() || !convertirEdad(edadTexto, edad) || servicio == nullptr) {
            std::cout << "Linea " << numeroLinea << " ignorada: datos invalidos.\n";
            continue;
        }
        if (espera.contieneId(id) || existePaciente(id)) {
            std::cout << "Linea " << numeroLinea << " ignorada: ID duplicado (" << id << ").\n";
            continue;
        }
        espera.encolar(Paciente(id, nombre, edad, servicio->getNombre()));
        ++cargados;
    }
    std::cout << cargados << " paciente(s) incorporado(s) a la cola.\n";
    return true;
}

void Hospital::mostrarCola() const {
    std::cout << "\n=== PACIENTES EN ESPERA (" << espera.size() << ") ===\n";
    espera.mostrar();
}

void Hospital::atenderPacientes(int cantidad) {
    if (cantidad <= 0) {
        std::cout << "La cantidad debe ser mayor que cero.\n";
        return;
    }
    if (espera.estaVacia()) {
        std::cout << "No hay pacientes para atender.\n";
        return;
    }
    std::cout << "\n=== ATENDIENDO PACIENTES ===\n";
    int atendidos = 0;
    while (atendidos < cantidad && !espera.estaVacia()) {
        Paciente paciente("", "", 0, "");
        espera.desencolar(paciente);
        Servicio* servicio = buscarServicio(paciente.getServicio());
        if (servicio != nullptr) {
            servicio->agregarPaciente(paciente);
            historial.apilar(paciente);
            std::cout << paciente.resumen() << " -> enviado a " << servicio->getNombre() << ".\n";
        }
        ++atendidos;
    }
    if (atendidos < cantidad) std::cout << "La cola se terminó antes de completar la cantidad solicitada. :/ \n";
}

void Hospital::mostrarServicios() const {
    std::cout << "\n=== DEPARTAMENTOS / SERVICIOS ===\n";
    const NodoServicio* actual = primerServicio;
    int opcion = 1;
    while (actual != nullptr) {
        std::cout << opcion++ << ". " << actual->servicio.getNombre()
            << " (" << actual->servicio.size() << " paciente(s))\n";
        actual = actual->siguiente;
    }
}

void Hospital::mostrarDepartamento(int opcion) const {
    if (opcion < 1 || opcion > CANTIDAD_SERVICIOS) {
        std::cout << "Departamento no valido.\n";
        return;
    }
    const NodoServicio* actual = primerServicio;
    for (int i = 1; i < opcion; ++i) actual = actual->siguiente;
    actual->servicio.mostrarEstado();
}

void Hospital::mostrarHistorial() const { historial.mostrar(); }

void Hospital::buscarPacientePorId(const std::string& id) const {
    const Paciente* paciente = espera.buscarPorId(id);
    if (paciente != nullptr) {
        std::cout << "Paciente encontrado en la cola de espera: " << paciente->resumen() << "\n";
        return;
    }
    const NodoServicio* actual = primerServicio;
    while (actual != nullptr) {
        paciente = actual->servicio.buscarPorId(id);
        if (paciente != nullptr) {
            std::cout << "Paciente encontrado en " << actual->servicio.getNombre() << ": "
                << paciente->resumen() << "\n";
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "No existe un paciente con ID " << id << ".\n";
}
