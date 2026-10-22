#pragma once
#include <string>
#include <iostream>
#include "Paciente.h"

class NodoDecision {
private:
	std::string pregunta;
	std::string servicio;
	NodoDecision* si;
	NodoDecision* no;
public:
	NodoDecision(std::string pregunta) { //Me permite añadir las preguntas al arbol
		this->pregunta = pregunta;
		this->servicio = "";
		this->si = nullptr;
		this->no = nullptr;

	}
	NodoDecision(std::string servicio, bool hoja) {
		this->pregunta = "";
		this->servicio = servicio;
		this->si = nullptr;
		this->no = nullptr;
	}
	bool esHoja() {
		if (this->servicio != "") return true;
	}
	std::string getPregunta() {
		return this->pregunta;
	}
	std::string getServicio() {
		return this->servicio;
	}
	NodoDecision* getSi() {
		return this->si;
	}
	NodoDecision* getNo() {
		return this->no;
	}
	void setSi(NodoDecision* si) {
		this->si = si;
	}
	void setNo(NodoDecision* no) {
		this->no = no;
	}
};

class ArbolDecision
{
private:
	NodoDecision* raiz;

public:
	ArbolDecision() {
		construirArbol();
	}
	void construirArbol();
	std::string clasificarPaciente(Paciente* paciente);
	NodoDecision* getRaiz() {
		return this->raiz;
	}
};

