#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <variant>

#include "../classes/pantry.h"
#include "../externalLibraries/json.hpp"

using json = nlohmann::json; //Alias

void opcionMenuIngredientes(Pantry& miPantry);
void opcionMenuRecetas(Pantry& miPantry, json& recetas, const std::string& nombre_archivo);
void opcionAgregarIngrediente(Pantry& pantry);
void opcionVerInventario(const Pantry& pantry);
void opcionEliminarIngrediente(Pantry& pantry);
void opcionBuscarRecetas(const Pantry& pantry, json& recetas);
void opcionAgregarRecetas(json& recetas, const std::string& nombre_archivo);
void opcionVerTodasRecetas(json& recetas);


#endif