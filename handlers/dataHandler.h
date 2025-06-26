#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>

#include "../externalLibraries/json.hpp"

using json = nlohmann::json; //Alias

bool guardarRecetas(const json &recetas, const std::string &nombre_archivo);
json cargarRecetas(const std::string& nombre_archivo);
std::vector<std::string> cargarIngredientes(const std::string& nombre_archivo);

#endif