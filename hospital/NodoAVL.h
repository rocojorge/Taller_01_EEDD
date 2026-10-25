#pragma once
#include "Paciente.h"
class NodoAVL {
	Paciente paciente;
	NodoAVL* izquierda;
	NodoAVL* derecha;
	int altura;
public:
	NodoAVL(const Paciente& paciente)
		: paciente(paciente), izquierda(nullptr), derecha(nullptr), altura(1) {}
	Paciente& getPaciente() { return paciente; }
	const Paciente& getPaciente() const { return paciente; }
	void setPaciente(const Paciente& nuevoPaciente) { paciente = nuevoPaciente; }
	NodoAVL* getIzquierda() const { return izquierda; }
	NodoAVL* getDerecha() const { return derecha; }
	int getAltura() const { return altura; }
	void setIzquierda(NodoAVL* nodo) { izquierda = nodo; }
	void setDerecha(NodoAVL* nodo) { derecha = nodo; }
	void setAltura(int h) { altura = h; }

};
