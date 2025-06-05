#ifndef MENU_H
#define MENU_H

#include "../pantry.h"
#include "../json.hpp" // Para nlohmann/json
#include <string>
#include <vector>

using json = nlohmann::json; //Alias

void mostrarMenuPrincipal();
void opcionAgregarIngrediente(Pantry& pantry);
void opcionVerInventario(const Pantry& pantry);
void opcionEliminarIngrediente(Pantry& pantry);
void opcionBuscarRecetas(const Pantry& pantry, const json& recetas);
std::vector<std::string> parsearIngredientesComando(const std::string& linea_comando);

#endif