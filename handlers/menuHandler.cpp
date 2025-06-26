#include "menuHandler.h"
#include "dataHandler.h"
#include "userInputHandler.h"
#include <iostream>
#include <algorithm> // Para std::transform




void opcionAgregarIngrediente(Pantry& pantry) {
    const std::string linea_ingredientes = pedirListaIngredientes();

    const std::vector<std::string> ingredientes = parsearIngredientesComando(linea_ingredientes);
    if (ingredientes.empty() && !linea_ingredientes.empty()){
         std::cout << "No se introdujeron ingredientes válidos. Asegúrate de separar por comas." << std::endl;
    } else if (ingredientes.empty()){
        std::cout << "No se introdujo ningún ingrediente." << std::endl;
    }

    for (const std::string& ing : ingredientes) {
        pantry.agregarIngrediente(ing);
    }
}

void opcionVerInventario(const Pantry& pantry) {
    pantry.mostrarInventario();
}

void opcionEliminarIngrediente(Pantry& pantry) {
    pantry.mostrarInventario();
    if (pantry.obtenerIngredientes().empty()){
        return; // No hacer nada si el inventario está vacío
    }
    const std::string ingrediente_a_eliminar = pedirUnicoIngrediente();

    pantry.eliminarIngrediente(ingrediente_a_eliminar);
}

void opcionBuscarRecetas(const Pantry& pantry, json& recetas) {
    std::cout << "\n--- Recetas que puedes preparar ---" << std::endl;
    bool alguna_receta_posible = false;

    if (pantry.obtenerIngredientes().empty()) {
        std::cout << "No tienes ingredientes en tu inventario. Agrega algunos primero." << std::endl;
        return;
    }

    for (const auto& receta_json : recetas) {
        std::string nombre_receta = receta_json["nombre"];
        std::vector<std::string> ingredientes_necesarios;
        ingredientes_necesarios = receta_json["ingredientes"].get<std::vector<std::string> >();
        bool se_puede_preparar = true;
        std::vector<std::string> ingredientes_faltantes;

        for (const std::string& ing_necesario : ingredientes_necesarios) {
            std::string ing_necesario_lower = ing_necesario;
            std::transform(ing_necesario_lower.begin(), ing_necesario_lower.end(), ing_necesario_lower.begin(), ::tolower);
            if (!pantry.tieneIngrediente(ing_necesario_lower)) {
                se_puede_preparar = false;
                ingredientes_faltantes.push_back(ing_necesario);
            }
        }

        if (se_puede_preparar) {
            std::cout << "-> " << nombre_receta << std::endl;
            alguna_receta_posible = true;
        } else {
            if (ingredientes_faltantes.size() <= 2) {
                std::cout << "Para " << nombre_receta << " te faltan: ";
                for(size_t i = 0; i < ingredientes_faltantes.size(); ++i) {
                    std::cout << ingredientes_faltantes[i] << (i == ingredientes_faltantes.size() - 1 ? "" : ", ") << std::endl;
                }
            }
        }
    }

    if (!alguna_receta_posible) {
        std::cout << "No puedes preparar ninguna receta completa con los ingredientes actuales." << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}

void opcionAgregarRecetas(json &recetas, std::string& nombre_archivo) {
    // if (0 == 0) {
    //     std::cout << "Lo sentimos, esta funcionalidad estará disponible en una siguiente actualización" << std::endl;
    //     return;
    // }

    //Inicializamos las variables necesarias
    std::string nombre_receta;
    std::string ingredientes_necesarios;

    // Ignora caracteres de salto de linea persistentes
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Le pedimos al usuario la data
    std::cout << "Introduce el nombre de la receta:" << std::endl;
    std::getline(std::cin, nombre_receta);

    // Validación de entrada
    if (nombre_receta.empty()) {
        std::cout << "El nombre de la receta no puede estar vacío. Operación cancelada." << std::endl;
        return;
    }

    std::cout << "Introduce los ingredientes que lleva la receta, separados por comas (ej: tomates, cebolla, ajo):" << std::endl;
    std::getline(std::cin, ingredientes_necesarios);

    // Validación de ingredientes
    if (ingredientes_necesarios.empty()) {
        std::cout << "La lista de ingredientes no puede estar vacía. Operación cancelada." << std::endl;
        return;
    }

    std::vector<std::string> ingredientes_a_agregar = parsearIngredientesComando(ingredientes_necesarios);

    // std::map<std::string, std::variant<std::string, std::vector<std::string>>> mapaAgregar = {
    //     {"nombre", nombre_receta},
    //     {"ingredientes", ingredientes_a_agregar}
    // };
    json nueva_receta;

    nueva_receta["nombre"] = nombre_receta;
    nueva_receta["ingredientes"] = ingredientes_a_agregar;
    recetas.push_back(nueva_receta);

    // agregarMapaAJson(mapaAgregar, recetas);
    guardarRecetas(recetas, nombre_archivo);

}
