#pragma once

#include <string>
#include "Paciente.h"

class ArbolDecision {
private:
    enum class TipoPregunta {
        CASO_PRIORITARIO,
        TRAUMA_O_CIRUGIA,
        REQUIERE_CIRUGIA,
        SINTOMAS_NEUROLOGICOS,
        DOLOR_PECHO,
        EDAD_MENOR_14,
        REQUIERE_HOSPITALIZACION,
        HOJA
    };

    class NodoDecision {
    private:
        TipoPregunta tipo;
        std::string pregunta;
        std::string servicio;
        NodoDecision* si;
        NodoDecision* no;

    public:
        // Constructor para nodos que hacen preguntas.
        NodoDecision(TipoPregunta tipo, const std::string& pregunta)
            : tipo(tipo), pregunta(pregunta), servicio(""),
              si(nullptr), no(nullptr) {}

        // Constructor para nodos hoja.
        NodoDecision(const std::string& servicio)
            : tipo(TipoPregunta::HOJA), pregunta(""),
              servicio(servicio), si(nullptr), no(nullptr) {}

        bool esHoja() const {
            return tipo == TipoPregunta::HOJA;
        }

        bool evaluar(const Paciente& paciente) const {
            switch (tipo) {
            case TipoPregunta::CASO_PRIORITARIO:
                return paciente.getTrauma() ||
                    paciente.getRequiereCirugia() ||
                    paciente.getSintomasNeurologicos() ||
                    paciente.getTipoDolor() == "pecho" ||
                    paciente.getTemperatura() >= 38.5 ||
                    paciente.getDolor() >= 8 ||
                    paciente.getPresionArterial() < 90 ||
                    paciente.getPresionArterial() > 180;

            case TipoPregunta::TRAUMA_O_CIRUGIA:
                return paciente.getTrauma() ||
                    paciente.getRequiereCirugia();

            case TipoPregunta::REQUIERE_CIRUGIA:
                return paciente.getRequiereCirugia();

            case TipoPregunta::SINTOMAS_NEUROLOGICOS:
                return paciente.getSintomasNeurologicos();

            case TipoPregunta::DOLOR_PECHO:
                return paciente.getTipoDolor() == "pecho";

            case TipoPregunta::EDAD_MENOR_14:
                return paciente.getEdad() < 14;

            case TipoPregunta::REQUIERE_HOSPITALIZACION:
                return paciente.getDiasHospitalizado() >= 2;

            default:
                return false;
            }
        }
        const std::string& getPregunta() const {
            return this->pregunta;
        }

        const std::string& getServicio() const {
            return this->servicio;
        }

        NodoDecision* getSi() const {
            return this->si;
        }

        NodoDecision* getNo() const {
            return this->no;
        }

        void setSi(NodoDecision* si) {
            this->si = si;
        }

        void setNo(NodoDecision* no) {
            this->no = no;
        }
    };

    NodoDecision* raiz;

    void liberar(NodoDecision* nodo);

public:
    ArbolDecision();
    ~ArbolDecision();

    ArbolDecision(const ArbolDecision&) = delete;
    ArbolDecision& operator=(const ArbolDecision&) = delete;

    void construirArbol();
    std::string clasificarPaciente(Paciente* paciente);

    NodoDecision* getRaiz() {
        return raiz;
    }
};