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

// Función para cargar recetas desde el archivo JSON
json cargarRecetas(const std::string& nombre_archivo) {
    std::ifstream archivo_json(nombre_archivo);
    json j;
    if (archivo_json.is_open()) {
        try {
            archivo_json >> j;
        } catch (json::parse_error& e) {
            std::cerr << "Error al parsear el archivo JSON: " << e.what() << std::endl;
            return nullptr; // Devuelve un json nulo en caso de error
        }
    } else {
        std::cerr << "Error: No se pudo abrir el archivo de recetas '" << nombre_archivo << "'" << std::endl;
        return nullptr; // Devuelve un json nulo si no se puede abrir
    }
    archivo_json.close();
    return j;
}

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