#pragma once
#include "NodoAVL.h"

class AVL{
private:
	NodoAVL* raiz;
	NodoAVL* insertar(NodoAVL* nodo, Paciente* paciente);
	int altura(NodoAVL* nodo);
	int balance(NodoAVL* nodo);
	NodoAVL* rotacionIzquierda(NodoAVL* nodo);
	NodoAVL* rotacionDerecha(NodoAVL* nodo);
public:
	AVL() : raiz(nullptr) {}
	~AVL();
	void insertar(Paciente* paciente);
	void preOrden(NodoAVL* nodo) const;
	void inOrden(NodoAVL* nodo) const;
	void postOrden(NodoAVL* nodo) const;
	NodoAVL* getRaiz() const { return raiz; }

};

