#pragma once

#include <string>
#include "NodoAVL.h"

class AVL {
private:
    NodoAVL* raiz;

    static int altura(const NodoAVL* nodo);
    static int maximo(int a, int b);
    static int factorBalance(const NodoAVL* nodo);
    static void actualizarAltura(NodoAVL* nodo);
    static NodoAVL* rotacionIzquierda(NodoAVL* nodo);
    static NodoAVL* rotacionDerecha(NodoAVL* nodo);
    static NodoAVL* balancear(NodoAVL* nodo);
    static NodoAVL* insertar(NodoAVL* nodo, const Paciente& paciente, bool& insertado);
    static NodoAVL* eliminar(NodoAVL* nodo, const std::string& id, bool& eliminado);
    static NodoAVL* minimo(NodoAVL* nodo);
    static void liberar(NodoAVL* nodo);
    static const Paciente* buscarPorId(const NodoAVL* nodo, const std::string& id);
    static const Paciente* buscarPorNombre(const NodoAVL* nodo, const std::string& nombre);
    static void preOrden(const NodoAVL* nodo);
    static void inOrden(const NodoAVL* nodo);
    static void postOrden(const NodoAVL* nodo);

public:
    AVL();
    ~AVL();
    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    bool insertar(const Paciente& paciente);
    bool eliminar(const std::string& id);
    const Paciente* buscarPorId(const std::string& id) const;
    const Paciente* buscarPorNombre(const std::string& nombre) const;
    bool estaVacio() const;
    int getAltura() const;
    int getFactorBalance() const;
    void mostrarPreOrden() const;
    void mostrarInOrden() const;
    void mostrarPostOrden() const;
};

