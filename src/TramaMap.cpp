/**
 * @file TramaMap.cpp
 * @brief Implementación de la clase TramaMap
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#include "TramaMap.h"
#include "RotorDeMapeo.h"
#include <iostream>

/**
 * @brief Constructor que almacena la cantidad de rotación
 * @param n Número de posiciones a rotar
 */
TramaMap::TramaMap(int n) : rotacion(n) {
    std::cout << "Creada TramaMap con rotación: " << n << std::endl;
}

/**
 * @brief Procesa la trama MAP: rota el disco de cifrado
 * @param carga Lista de carga (no se modifica por esta trama)
 * @param rotor Rotor a modificar
 */
void TramaMap::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    std::cout << "Procesando TramaMap: rotando " << rotacion << " posiciones" << std::endl;
    rotor->rotar(rotacion);
}