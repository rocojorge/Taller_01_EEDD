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

    bool convertirEntero(const std::string& texto, int minimo, int maximo, int& valor) {
        try {
            const std::string limpio = limpiar(texto);
            std::size_t procesados = 0;
            valor = std::stoi(limpio, &procesados);
            return procesados == limpio.size() && valor >= minimo && valor <= maximo;
        }
        catch (...) {
            return false;
        }
    }

    bool convertirReal(const std::string& texto, float minimo, float maximo, float& valor) {
        try {
            const std::string limpio = limpiar(texto);
            std::size_t procesados = 0;
            valor = std::stof(limpio, &procesados);
            return procesados == limpio.size() && valor >= minimo && valor <= maximo;
        }
        catch (...) {
            return false;
        }
    }

    bool convertirBandera(const std::string& texto, bool& valor) {
        const std::string limpio = limpiar(texto);
        if (limpio == "1") { valor = true; return true; }
        if (limpio == "0") { valor = false; return true; }
        return false;
    }

    bool separarCampos(const std::string& linea, std::string campos[11]) {
        std::size_t inicio = 0;
        for (int i = 0; i < 10; ++i) {
            const std::size_t separador = linea.find(';', inicio);
            if (separador == std::string::npos) return false;
            campos[i] = limpiar(linea.substr(inicio, separador - inicio));
            inicio = separador + 1;
        }
        if (linea.find(';', inicio) != std::string::npos) return false;
        campos[10] = limpiar(linea.substr(inicio));
        return true;
    }

    bool tipoDolorValido(const std::string& tipo) {
        return tipo == "pecho" || tipo == "cabeza" || tipo == "abdomen" ||
            tipo == "extremidad" || tipo == "otro";
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
    int ignorados = 0;
    while (std::getline(archivo, linea)) {
        ++numeroLinea;
        if (limpiar(linea).empty()) continue;

        std::string campos[11];
        if (!separarCampos(linea, campos)) {
            std::cout << "Linea " << numeroLinea << " ignorada: se esperaban 11 campos separados por ';'.\n";
            ++ignorados;
            continue;
        }

        int edad = 0, dolor = 0, diasHospitalizado = 0;
        float temperatura = 0, presion = 0;
        bool trauma = false, neurologicos = false, requiereCirugia = false;
        const std::string tipoDolor = normalizarServicio(campos[6]);
        if (campos[0].empty() || campos[1].empty() ||
            !convertirEntero(campos[2], 0, 130, edad) ||
            !convertirReal(campos[3], 30.0f, 45.0f, temperatura) ||
            !convertirReal(campos[4], 40.0f, 250.0f, presion) ||
            !convertirEntero(campos[5], 0, 10, dolor) ||
            !tipoDolorValido(tipoDolor) ||
            !convertirBandera(campos[7], trauma) ||
            !convertirBandera(campos[8], neurologicos) ||
            !convertirBandera(campos[9], requiereCirugia) ||
            !convertirEntero(campos[10], 0, 365, diasHospitalizado)) {
            std::cout << "Linea " << numeroLinea << " ignorada: datos fuera de rango o no validos.\n";
            ++ignorados;
            continue;
        }
        if (espera.contieneId(campos[0]) || existePaciente(campos[0])) {
            std::cout << "Linea " << numeroLinea << " ignorada: ID duplicado (" << campos[0] << ").\n";
            ++ignorados;
            continue;
        }
        espera.encolar(Paciente(campos[0], campos[1], edad, temperatura, presion, dolor,
            tipoDolor, trauma, neurologicos, requiereCirugia, diasHospitalizado));
        ++cargados;
    }
    std::cout << cargados << " paciente(s) incorporado(s) a la cola";
    if (ignorados > 0) std::cout << " | " << ignorados << " linea(s) ignorada(s)";
    std::cout << ".\n";
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
        Paciente paciente;
        espera.desencolar(paciente);
        std::string ruta;
        const std::string nombreServicio = arbolDecision.clasificarPaciente(paciente, &ruta);
        Servicio* servicio = buscarServicio(nombreServicio);
        if (servicio != nullptr) {
            paciente.setServicio(servicio->getNombre());
            if (!servicio->agregarPaciente(paciente)) {
                std::cout << "No se pudo insertar " << paciente.getId() << ": ID duplicado en el AVL.\n";
                ++atendidos;
                continue;
            }
            historial.apilar(paciente);
            std::cout << paciente.resumen() << " -> " << servicio->getNombre() << ".\n"
                << "  Ruta: " << ruta << '\n';
        } else {
            std::cout << "No se pudo clasificar " << paciente.getId() << ".\n";
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
	std::cout << opcion << ". Volver al menu principal\n";
}

void Hospital::mostrarDepartamento(int opcion) const {
	if (opcion == CANTIDAD_SERVICIOS + 1) return; // Opción para volver al menú principal
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
    if (paciente == nullptr) paciente = espera.buscarPorNombre(id);
    if (paciente != nullptr) {
        std::cout << "Paciente encontrado en la cola de espera: " << paciente->resumen() << "\n";
        return;
    }
    const NodoServicio* actual = primerServicio;
    while (actual != nullptr) {
        paciente = actual->servicio.buscarPorId(id);
        if (paciente == nullptr) paciente = actual->servicio.buscarPorNombre(id);
        if (paciente != nullptr) {
            std::cout << "Paciente encontrado en " << actual->servicio.getNombre() << ": "
                << paciente->resumen() << "\n";
            return;
        }
        actual = actual->siguiente;
    }
    std::cout << "No existe un paciente con ID " << id << ".\n";
}

void Hospital::buscarPacientePorNombre(const std::string& nombre) const{
	NodoServicio* actual = primerServicio;
	while (actual != nullptr) {
		const Paciente* paciente = actual->servicio.buscarPorNombre(nombre);
		if (paciente != nullptr) {
			std::cout << "Paciente encontrado en " << actual->servicio.getNombre() << ": "
				<< paciente->resumen() << "\n";
			return;
		}
		actual = actual->siguiente;
	}
	std::cout << "No existe un paciente con nombre " << nombre << ".\n";
}

void Hospital::buscarPaciente(const std::string& dato) const{
	if (isdigit(dato[0])) {
		buscarPacientePorId(dato);
	}
	else {
		buscarPacientePorNombre(dato);
	}
}
