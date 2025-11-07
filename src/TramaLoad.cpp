/**
 * @file TramaLoad.cpp
 * @brief Implementación de la clase TramaLoad
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#include "TramaLoad.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include <iostream>

/**
 * @brief Constructor que almacena el carácter de la trama
 * @param c Carácter a almacenar
 */
TramaLoad::TramaLoad(char c) : caracter(c) {
    std::cout << "Creada TramaLoad con carácter: '" << c << "'" << std::endl;
}

/**
 * @brief Procesa la trama LOAD: decodifica el carácter y lo agrega a la lista de carga
 * @param carga Lista donde se almacenan los datos decodificados
 * @param rotor Rotor para el mapeo de caracteres
 */
void TramaLoad::procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) {
    char caracterDecodificado = rotor->getMapeo(caracter);
    std::cout << "Procesando TramaLoad: '" << caracter << "' -> '" << caracterDecodificado << "'" << std::endl;
    carga->insertarAlFinal(caracterDecodificado);
    carga->imprimirEstado();
}