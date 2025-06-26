#include "pantry.h"

Pantry::Pantry() {}

void Pantry::agregarIngrediente(const std::string& ingrediente) {
    // Convertir a minúsculas para evitar duplicados por capitalización
    std::string ing_lower = ingrediente;
    std::transform(ing_lower.begin(), ing_lower.end(), ing_lower.begin(), ::tolower);

    // Evitar duplicados
    bool encontrado = false;
    for (const std::string& actual : ingredientes_disponibles) {
        if (actual == ing_lower) {
            encontrado = true;
            break;
        }
    }
    if (!encontrado) {
        ingredientes_disponibles.push_back(ing_lower);
        std::cout << "Ingrediente '" << ingrediente << "' agregado al inventario." << std::endl;
    } else {
        std::cout << "El ingrediente '" << ingrediente << "' ya está en el inventario." << std::endl;
    }
}

void Pantry::eliminarIngrediente(const std::string& ingrediente) {
    std::string ing_lower_eliminar = ingrediente;
    std::transform(ing_lower_eliminar.begin(), ing_lower_eliminar.end(), ing_lower_eliminar.begin(), ::tolower);

    auto it = std::remove_if(ingredientes_disponibles.begin(), ingredientes_disponibles.end(),
                             [&](const std::string& actual) {
                                 std::string actual_lower = actual;
                                 std::transform(actual_lower.begin(), actual_lower.end(), actual_lower.begin(), ::tolower);
                                 return actual_lower == ing_lower_eliminar;
                             });

    if (it != ingredientes_disponibles.end()) {
        ingredientes_disponibles.erase(it, ingredientes_disponibles.end());
        std::cout << "Ingrediente '" << ingrediente << "' eliminado del inventario." << std::endl;
    } else {
        std::cout << "Ingrediente '" << ingrediente << "' no encontrado en el inventario." << std::endl;
    }
}

void Pantry::mostrarInventario() const {
    if (ingredientes_disponibles.empty()) {
        std::cout << "El inventario está vacío." << std::endl;
        return;
    }
    std::cout << "Inventario de ingredientes:" << std::endl;
    for (const std::string& ingrediente : ingredientes_disponibles) {
        std::cout << "- " << ingrediente << std::endl;
    }
}

const std::vector<std::string>& Pantry::obtenerIngredientes() const {
    return ingredientes_disponibles;
}

bool Pantry::tieneIngrediente(const std::string& ingrediente) const {
    std::string ing_lower_buscar = ingrediente;
    std::transform(ing_lower_buscar.begin(), ing_lower_buscar.end(), ing_lower_buscar.begin(), ::tolower);

    for (const std::string& disponible : ingredientes_disponibles) {
        if (disponible == ing_lower_buscar) {
            return true;
        }
    }
    return false;
}