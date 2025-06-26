#ifndef MENUHANDLER_H
#define MENUHANDLER_H

#include <variant>

#include "../classes/pantry.h"
#include "../externalLibraries/json.hpp"

using json = nlohmann::json; //Alias

void opcionAgregarIngrediente(Pantry& pantry);
void opcionVerInventario(const Pantry& pantry);
void opcionEliminarIngrediente(Pantry& pantry);
void opcionBuscarRecetas(const Pantry& pantry, json& recetas);
void opcionAgregarRecetas(json& recetas, std::string& nombre_archivo);


#endif