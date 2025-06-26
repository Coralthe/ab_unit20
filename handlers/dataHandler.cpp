#include "dataHandler.h"

#include <iostream>

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

int modificarArchivoRecetas(const json& recetas, std::string& nombre_archivo) {
    // Definir ruta del archivo
    // const std::string nombreArchivo = "../data/recetas.json";

    // Abribos el archivo y verificamos que está abierto
    std::ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        std::cerr << "Error opening file " << nombre_archivo << std::endl;
        return 0;
    }

    // Escribimos el json de recetas en el archivo y lo cerramos
    archivo << recetas.dump(4);
    archivo.close();
    return 1;
}
