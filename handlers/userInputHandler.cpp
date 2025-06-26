#include "userInputHandler.h"

#include <iostream>
#include <sstream>

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

std::string pedirListaIngredientes() {
    std::cout << "Introduce los ingredientes que tienes, separados por comas (ej: tomates, cebolla, ajo):" << std::endl;
    std::string ingredientes;
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, ingredientes);
    return ingredientes;
}

std::string pedirUnicoIngrediente() {
    std::cout << "Introduce el nombre exacto del ingrediente a eliminar: ";
    std::string ingrediente;
    // Consumir el newline pendiente del menú anterior si es necesario
    if (std::cin.peek() == '\n') {
        std::cin.ignore();
    }
    std::getline(std::cin, ingrediente);
    return ingrediente;
}