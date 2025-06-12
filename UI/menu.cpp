#include "menu.h"
#include <iostream>
#include <limits> // Para std::numeric_limits
#include <sstream> // Para std::stringstream
#include <algorithm> // Para std::transform

// Función auxiliar para limpiar el buffer de entrada
void limpiarBufferEntrada() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void mostrarMenuPrincipal() {
    std::cout << "\n===== Menú Principal =====\n"
    << "2. Ver inventario\n"
    << "1. Introducir ingredientes\n"
    << "3. Eliminar ingrediente del inventario\n"
    << "4. Buscar recetas posibles\n"
    << "5. Salir\n"
    << "Seleccione una opción: " << std::endl;
}

std::vector<std::string> parsearIngredientesComando(const std::string& linea_comando) {
    std::vector<std::string> ingredientes;
    std::stringstream ss(linea_comando);
    std::string ingrediente;
    // Leer ingredientes separados por coma, y quitar espacios extra
    while (std::getline(ss, ingrediente, ',')) {
        // Eliminar espacios al inicio
        ingrediente.erase(0, ingrediente.find_first_not_of(" \t\n\r\f\v"));
        // Eliminar espacios al final
        ingrediente.erase(ingrediente.find_last_not_of(" \t\n\r\f\v") + 1);
        if (!ingrediente.empty()) {
            ingredientes.push_back(ingrediente);
        }
    }
    return ingredientes;
}

void opcionAgregarIngrediente(Pantry& pantry) {
    std::string linea_ingredientes;
    std::cout << "Introduce los ingredientes que tienes, separados por comas (ej: tomates, cebolla, ajo):" << std::endl;
    // Consumir el newline pendiente del menú anterior si es necesario
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, linea_ingredientes);

    std::vector<std::string> ingredientes = parsearIngredientesComando(linea_ingredientes);
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
    std::string ingrediente_a_eliminar;
    pantry.mostrarInventario();
    if (pantry.obtenerIngredientes().empty()){
        return; // No hacer nada si el inventario está vacío
    }
    std::cout << "Introduce el nombre exacto del ingrediente a eliminar: ";
    // Consumir el newline pendiente del menú anterior si es necesario
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, ingrediente_a_eliminar);
    pantry.eliminarIngrediente(ingrediente_a_eliminar);
}

void opcionBuscarRecetas(const Pantry& pantry, const json& recetas) {
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
            // TODO: Mostrar qué falta para otras recetas
            // std::cout << "Para " << nombre_receta << " te faltan: ";
            // for(size_t i = 0; i < ingredientes_faltantes.size(); ++i) {
            //     std::cout << ingredientes_faltantes[i] << (i == ingredientes_faltantes.size() - 1 ? "" : ", ");
            // }
            // std::cout << std::endl;
        }
    }

    if (!alguna_receta_posible) {
        std::cout << "No puedes preparar ninguna receta completa con los ingredientes actuales." << std::endl;
    }
    std::cout << "---------------------------------" << std::endl;
}
