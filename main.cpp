#include <iostream>
#include <fstream>    // Para std::ifstream
#include <string>
#include "windows.h"

#include "classes/pantry.h"
#include "UI/menu.h"
#include "handlers/menuHandler.h"
#include "handlers/dataHandler.h"
#include "externalLibraries/json.hpp"

// Alias para el tipo JSON para facilitar su uso
using json = nlohmann::json;


int main() {
    //SetConsoleOutputCP(1252);
    SetConsoleOutputCP(CP_UTF8);
    Pantry miPantry;
    std::string nombre_archivo = "data/recetas.json";
    json recetas = cargarRecetas("recetas.json");

    if (recetas.is_null() || !recetas.is_array()) {
        std::cerr << "No se pudieron cargar las recetas o el formato es incorrecto. El programa terminará." << std::endl;
        return 1;
    }
    // std::cout << recetas.dump(4) << std::endl;


    int opcion;
    do {
        mostrarMenuPrincipal();
        std::cin >> opcion;

        // Validar entrada numérica
        if (std::cin.fail()) {
            std::cout << "Entrada no válida. Por favor, introduce un número." << std::endl;
            std::cin.clear(); // Limpiar flags de error
            opcion = 0; // Asignar un valor no válido para continuar el bucle
            continue;
        }

        switch (opcion) {
            case 1:
                opcionAgregarIngrediente(miPantry);
                break;
            case 2:
                opcionVerInventario(miPantry);
                break;
            case 3:
                opcionEliminarIngrediente(miPantry);
                break;
            case 4:
                opcionBuscarRecetas(miPantry, recetas);
                break;
            case 5:
                opcionAgregarRecetas(recetas, nombre_archivo);
                break;
            case 6:
                std::cout << "¡Hasta luego! Gracias por usar el recomendador de comidas." << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Inténtalo de nuevo." << std::endl;
        }
    } while (opcion != 6);

    return 0;
}