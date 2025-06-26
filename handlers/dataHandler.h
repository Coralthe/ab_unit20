#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <variant>
#include <string>
#include <vector>
#include <fstream>

#include "../externalLibraries/json.hpp"

using json = nlohmann::json; //Alias

std::vector<std::string> parsearIngredientesComando(const std::string& linea_comando);
int guardarRecetas(const json& recetas, const std::string& nombre_archivo);
json cargarRecetas(const std::string& nombre_archivo);

// template<typename ValueType>
// void agregarMapaAJson(std::map<std::string, ValueType>& mapToAdd, json& jsonObj) {
//     for (const auto& par : mapToAdd) {
//         // En lugar de la asignación directa...
//         // ...usamos std::visit para desempaquetar el variant (par.second)
//         std::visit([&jsonObj, &par](const auto& value) {
//             // 'value' aquí será o un std::string o un std::vector<std::string>.
//             // La librería json SÍ sabe cómo manejar estos tipos directamente.
//             jsonObj[par.first] = value;
//         }, par.second);
//     }
// };
#endif