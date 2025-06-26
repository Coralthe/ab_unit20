#include "menu.h"

void mostrarMenuPrincipal() {
    std::cout << "\n===== Menú Principal =====\n"
    << "1. Menú ingredientes\n"
    << "2. Menú Recetas\n"
    << "3. Salir\n"
    << "Seleccione una opción: " << std::endl;
}

void mostrarMenuIngredientes() {
    std::cout << "\n===== Menú Ingredientes =====\n"
<< "1. Introducir ingredientes\n"
<< "2. Ver inventario\n"
<< "3. Eliminar ingrediente del inventario\n"
<< "4. Cargar ingredientes preestablecidos\n"
<< "5. Volver al menú principal\n"
<< "Seleccione una opción: " << std::endl;
}

void mostrarMenuRecetas() {
    std::cout << "\n===== Menú Recetas =====\n"
<< "1. Buscar recetas posibles\n"
<< "2. Agregar recetas personalizadas\n"
<< "3. Ver todas las recetas\n"
<< "4. Volver al menú principal\n"
<< "Seleccione una opción: " << std::endl;
}