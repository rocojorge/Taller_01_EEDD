#include "AVL.h"

#include <iostream>

AVL::AVL() : raiz(nullptr) {}

AVL::~AVL() {
    liberar(raiz);
    raiz = nullptr;
}

int AVL::altura(const NodoAVL* nodo) {
    return nodo == nullptr ? 0 : nodo->getAltura();
}

int AVL::maximo(int a, int b) {
    return a > b ? a : b;
}

int AVL::factorBalance(const NodoAVL* nodo) {
    return nodo == nullptr ? 0 : altura(nodo->getIzquierda()) - altura(nodo->getDerecha());
}

void AVL::actualizarAltura(NodoAVL* nodo) {
    if (nodo != nullptr) {
        nodo->setAltura(1 + maximo(altura(nodo->getIzquierda()), altura(nodo->getDerecha())));
    }
}

NodoAVL* AVL::rotacionDerecha(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getIzquierda();
    NodoAVL* subarbolTransferido = nuevaRaiz->getDerecha();
    nuevaRaiz->setDerecha(nodo);
    nodo->setIzquierda(subarbolTransferido);
    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

NodoAVL* AVL::rotacionIzquierda(NodoAVL* nodo) {
    NodoAVL* nuevaRaiz = nodo->getDerecha();
    NodoAVL* subarbolTransferido = nuevaRaiz->getIzquierda();
    nuevaRaiz->setIzquierda(nodo);
    nodo->setDerecha(subarbolTransferido);
    actualizarAltura(nodo);
    actualizarAltura(nuevaRaiz);
    return nuevaRaiz;
}

NodoAVL* AVL::balancear(NodoAVL* nodo) {
    if (nodo == nullptr) return nullptr;
    actualizarAltura(nodo);
    const int factor = factorBalance(nodo);
    if (factor > 1) {
        if (factorBalance(nodo->getIzquierda()) < 0)
            nodo->setIzquierda(rotacionIzquierda(nodo->getIzquierda()));
        return rotacionDerecha(nodo);
    }
    if (factor < -1) {
        if (factorBalance(nodo->getDerecha()) > 0)
            nodo->setDerecha(rotacionDerecha(nodo->getDerecha()));
        return rotacionIzquierda(nodo);
    }
    return nodo;
}

NodoAVL* AVL::insertar(NodoAVL* nodo, const Paciente& paciente, bool& insertado) {
    if (nodo == nullptr) {
        insertado = true;
        return new NodoAVL(paciente);
    }

    if (paciente.getId() < nodo->getPaciente().getId())
        nodo->setIzquierda(insertar(nodo->getIzquierda(), paciente, insertado));
    else if (paciente.getId() > nodo->getPaciente().getId())
        nodo->setDerecha(insertar(nodo->getDerecha(), paciente, insertado));
    else
        return nodo;

    return balancear(nodo);
}

NodoAVL* AVL::minimo(NodoAVL* nodo) {
    while (nodo != nullptr && nodo->getIzquierda() != nullptr)
        nodo = nodo->getIzquierda();
    return nodo;
}

NodoAVL* AVL::eliminar(NodoAVL* nodo, const std::string& id, bool& eliminado) {
    if (nodo == nullptr) return nullptr;

    if (id < nodo->getPaciente().getId()) {
        nodo->setIzquierda(eliminar(nodo->getIzquierda(), id, eliminado));
    } else if (id > nodo->getPaciente().getId()) {
        nodo->setDerecha(eliminar(nodo->getDerecha(), id, eliminado));
    } else {
        eliminado = true;
        if (nodo->getIzquierda() == nullptr || nodo->getDerecha() == nullptr) {
            NodoAVL* hijo = nodo->getIzquierda() != nullptr ? nodo->getIzquierda() : nodo->getDerecha();
            delete nodo;
            return hijo;
        }
        NodoAVL* sucesor = minimo(nodo->getDerecha());
        nodo->setPaciente(sucesor->getPaciente());
        bool eliminadoSucesor = false;
        nodo->setDerecha(eliminar(nodo->getDerecha(), sucesor->getPaciente().getId(), eliminadoSucesor));
    }
    return balancear(nodo);
}

void AVL::liberar(NodoAVL* nodo) {
    if (nodo == nullptr) return;
    liberar(nodo->getIzquierda());
    liberar(nodo->getDerecha());
    delete nodo;
}

const Paciente* AVL::buscarPorId(const NodoAVL* nodo, const std::string& id) {
    while (nodo != nullptr) {
        if (id == nodo->getPaciente().getId()) return &nodo->getPaciente();
        nodo = id < nodo->getPaciente().getId() ? nodo->getIzquierda() : nodo->getDerecha();
    }
    return nullptr;
}

const Paciente* AVL::buscarPorNombre(const NodoAVL* nodo, const std::string& nombre) {
    if (nodo == nullptr) return nullptr;
    if (nodo->getPaciente().getNombre() == nombre) return &nodo->getPaciente();
    const Paciente* encontrado = buscarPorNombre(nodo->getIzquierda(), nombre);
    return encontrado != nullptr ? encontrado : buscarPorNombre(nodo->getDerecha(), nombre);
}

void AVL::preOrden(const NodoAVL* nodo) {
    if (nodo == nullptr) return;
    std::cout << nodo->getPaciente().resumen() << '\n';
    preOrden(nodo->getIzquierda());
    preOrden(nodo->getDerecha());
}

void AVL::inOrden(const NodoAVL* nodo) {
    if (nodo == nullptr) return;
    inOrden(nodo->getIzquierda());
    std::cout << nodo->getPaciente().resumen() << '\n';
    inOrden(nodo->getDerecha());
}

void AVL::postOrden(const NodoAVL* nodo) {
    if (nodo == nullptr) return;
    postOrden(nodo->getIzquierda());
    postOrden(nodo->getDerecha());
    std::cout << nodo->getPaciente().resumen() << '\n';
}

bool AVL::insertar(const Paciente& paciente) {
    bool insertado = false;
    raiz = insertar(raiz, paciente, insertado);
    return insertado;
}

bool AVL::eliminar(const std::string& id) {
    bool eliminado = false;
    raiz = eliminar(raiz, id, eliminado);
    return eliminado;
}

const Paciente* AVL::buscarPorId(const std::string& id) const {
    return buscarPorId(raiz, id);
}

const Paciente* AVL::buscarPorNombre(const std::string& nombre) const {
    return buscarPorNombre(raiz, nombre);
}

bool AVL::estaVacio() const { return raiz == nullptr; }
int AVL::getAltura() const { return altura(raiz); }
int AVL::getFactorBalance() const { return factorBalance(raiz); }
void AVL::mostrarPreOrden() const { preOrden(raiz); }
void AVL::mostrarInOrden() const { inOrden(raiz); }
void AVL::mostrarPostOrden() const { postOrden(raiz); }
