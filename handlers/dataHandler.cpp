#include "dataHandler.h"

#include <iostream>
#include <fstream>

bool guardarRecetas(const json &recetas, const std::string &nombre_archivo) {
    // Definir ruta del archivo
    // const std::string nombreArchivo = "../data/recetas.json";

    // Abribos el archivo y verificamos que está abierto
    std::ofstream archivo(nombre_archivo);
    if (!archivo.is_open()) {
        std::cerr << "Error opening file " << nombre_archivo << std::endl;
        return false;
    }

    // Escribimos el json de recetas en el archivo y lo cerramos
    archivo << recetas.dump(4);
    archivo.close();
    return true;
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

std::vector<std::string> cargarIngredientes(const std::string& nombre_archivo) {
    std::vector<std::string> ingredientes;
    std::ifstream archivo_txt(nombre_archivo);
    std::string linea;

    if (!archivo_txt.is_open()) {
        std::cerr << "Error al abrir el archivo de ingredientes" << std::endl;
    }
    while (std::getline(archivo_txt, linea)) {
        ingredientes.push_back(linea);
    }

    archivo_txt.close();
    return ingredientes;
}
