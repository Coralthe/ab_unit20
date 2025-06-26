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

int guardarRecetas(const json& recetas, const std::string& nombre_archivo) {
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
