#include "ArbolDecision.h"
#include <iostream>


ArbolDecision::ArbolDecision() : raiz(nullptr) {
    construirArbol();
}

ArbolDecision::~ArbolDecision() {
    liberar(raiz);
    raiz = nullptr;
}

void ArbolDecision::preOrden(const NodoDecision* nodo) const {
    if (nodo == nullptr) return;
    if (nodo->esHoja()) 
		std::cout << nodo->getServicio() << std::endl;
    else
		std::cout << nodo->getPregunta() << std::endl;
    preOrden(nodo->getSi());
	preOrden(nodo->getNo());    
}

void ArbolDecision::inOrden(const NodoDecision* nodo) const {
	if (nodo == nullptr) return;
	inOrden(nodo->getSi());
	if (nodo->esHoja())
		std::cout << nodo->getServicio() << std::endl;
	else
		std::cout << nodo->getPregunta() << std::endl;
	inOrden(nodo->getNo());
}

void ArbolDecision::postOrden(const NodoDecision* nodo) const {
    if (nodo == nullptr) return;
    postOrden(nodo->getSi());
    postOrden(nodo->getNo());
    if (nodo->esHoja()) {
        std::cout << nodo->getServicio() << std::endl;
    } else {
        std::cout << nodo->getPregunta() << std::endl;
    }
}

void ArbolDecision::liberar(NodoDecision* nodo) {
    if (nodo == nullptr) {
        return;
    }

    liberar(nodo->getSi());
    liberar(nodo->getNo());

    delete nodo;
}

void ArbolDecision::construirArbol() {
    liberar(raiz);
    raiz = nullptr;

    raiz = new NodoDecision(
        TipoPregunta::CASO_PRIORITARIO,
        "Caso prioritario?"
    );

    // Rama paciente prioritario.

    NodoDecision* traumaOCirugia = new NodoDecision(
        TipoPregunta::TRAUMA_O_CIRUGIA,
        "Trauma o requiere cirugia?"
    );

    raiz->setSi(traumaOCirugia);

    NodoDecision* requiereCirugia = new NodoDecision(
        TipoPregunta::REQUIERE_CIRUGIA,
        "Requiere cirugia?"
    );

    traumaOCirugia->setSi(requiereCirugia);
    requiereCirugia->setSi(new NodoDecision("Cirugia"));
    requiereCirugia->setNo(new NodoDecision("Traumatologia"));

    NodoDecision* sintomasNeurologicos = new NodoDecision(
        TipoPregunta::SINTOMAS_NEUROLOGICOS,
        "Sintomas neurologicos?"
    );

    traumaOCirugia->setNo(sintomasNeurologicos);
    sintomasNeurologicos->setSi(new NodoDecision("Neurologia"));

    NodoDecision* dolorPecho = new NodoDecision(
        TipoPregunta::DOLOR_PECHO,
        "Dolor en el pecho?"
    );

    sintomasNeurologicos->setNo(dolorPecho);
    dolorPecho->setSi(new NodoDecision("Cardiologia"));
    dolorPecho->setNo(new NodoDecision("Urgencias"));
    // Rama paciente rutinario.

    NodoDecision* esPediatrico = new NodoDecision(
        TipoPregunta::EDAD_MENOR_14,
        "Edad menor a 14?"
    );

    raiz->setNo(esPediatrico);
    esPediatrico->setSi(new NodoDecision("Pediatria"));

    NodoDecision* requiereHospitalizacion = new NodoDecision(
        TipoPregunta::REQUIERE_HOSPITALIZACION,
        "Dias hospitalizacion mayor o igual a 2?"
    );

    esPediatrico->setNo(requiereHospitalizacion);
    requiereHospitalizacion->setSi(
        new NodoDecision("Hospitalizacion")
    );
    requiereHospitalizacion->setNo(
        new NodoDecision("Medicina General")
    );
}

std::string ArbolDecision::clasificarPaciente(const Paciente& paciente, std::string* ruta) const {
    const NodoDecision* actual = raiz;
    if (ruta != nullptr) ruta->clear();

    while (actual != nullptr && !actual->esHoja()) {
        const bool respuesta = actual->evaluar(paciente);
        if (ruta != nullptr) {
            if (!ruta->empty()) *ruta += " -> ";
            *ruta += actual->getPregunta() + (respuesta ? " [Si]" : " [No]");
        }

        if (respuesta) {
            actual = actual->getSi();
        }
        else {
            actual = actual->getNo();
        }
    }

    if (actual == nullptr) {
        return "";
    }

    return actual->getServicio();
}

void ArbolDecision::mostrarPreOrden() const { preOrden(raiz); }
void ArbolDecision::mostrarInOrden() const { inOrden(raiz); }
void ArbolDecision::mostrarPostOrden() const { postOrden(raiz); }
