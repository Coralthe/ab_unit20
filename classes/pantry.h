#ifndef PANTRY_H
#define PANTRY_H

#include <vector>
#include <string>
#include <algorithm> // Para std::transform
#include <iostream>
#include <fstream>

class Pantry {
private:
    std::vector<std::string> ingredientes_disponibles;

public:
    Pantry();
    void agregarIngrediente(const std::string& ingrediente);
    void cargarIngredientesDesdeArchivo(const std::string& rutaArchivo);
    void eliminarIngrediente(const std::string& ingrediente);
    void mostrarInventario() const;
    const std::vector<std::string>& obtenerIngredientes() const;
    bool tieneIngrediente(const std::string& ingrediente) const;
};

#endif