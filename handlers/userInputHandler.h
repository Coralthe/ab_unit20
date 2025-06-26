#pragma once

#include <string>
#include <vector>

std::vector<std::string> parsearIngredientesComando(const std::string& linea_comando);
std::string pedirListaIngredientes();
std::string pedirUnicoIngrediente();