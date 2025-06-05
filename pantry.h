#ifndef PANTRY_H
#define PANTRY_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Pantry {
private:
    std::vector<std::string> ingredientes_disponibles;

public:
    Pantry();
    void agregarIngrediente(const std::string& ingrediente);
    void eliminarIngrediente(const std::string& ingrediente);
    void mostrarInventario() const;
    const std::vector<std::string>& obtenerIngredientes() const;
    bool tieneIngrediente(const std::string& ingrediente) const;
};

#endif