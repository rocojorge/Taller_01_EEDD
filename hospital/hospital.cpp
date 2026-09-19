#include "Hospital_.h"

#include <iostream>
#include <limits>
#include <string>

namespace {
    bool leerEntero(const std::string& mensaje, int& valor) {
        std::cout << mensaje;
        if (std::cin >> valor) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada no valida.\n";
        return false;
    }
}

int main(int argc, char* argv[]) {
    std::string ruta;
    if (argc >= 2) ruta = argv[1];
    else {
        std::cout << "Ruta del archivo de pacientes: ";
        std::getline(std::cin, ruta);
    }

    Hospital hospital;
    if (!hospital.cargarPacientes(ruta)) return 1;

    int opcion = 0;
    do {
        std::cout << "\n=== HOSPITAL MARMAJA ===\n"
            << "1. Ver y atender pacientes\n"
            << "2. Ver departamento\n"
            << "3. Revisar historial de atencion\n"
            << "4. Buscar paciente por ID\n"
            << "5. Salir\n";
        if (!leerEntero("Seleccionar opcion: ", opcion)) continue;

        if (opcion == 1) {
            hospital.mostrarCola();
            int cantidad;
            if (leerEntero("Cantidad de pacientes a atender: ", cantidad)) hospital.atenderPacientes(cantidad);
        }
        else if (opcion == 2) {
            hospital.mostrarServicios();
            int departamento;
            if (leerEntero("Seleccionar departamento: ", departamento)) hospital.mostrarDepartamento(departamento);
        }
        else if (opcion == 3) {
            hospital.mostrarHistorial();
        }
        else if (opcion == 4) {
            std::string id;
            std::cout << "ID del paciente: ";
            std::getline(std::cin, id);
            hospital.buscarPacientePorId(id);
        }
        else if (opcion != 5) {
            std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);

    std::cout << "Hasta luego. Memoria liberada correctamente al cerrar el programa.\n";
    return 0;
}
