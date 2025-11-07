/**
 * @file TramaMap.h
 * @brief Trama de tipo MAP que contiene instrucciones para rotar el disco de cifrado
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#ifndef TRAMA_MAP_H
#define TRAMA_MAP_H

#include "TramaBase.h"

/**
 * @class TramaMap
 * @brief Trama de tipo MAP que contiene instrucciones para rotar el disco de cifrado
 * @details Representa una trama M,N (ejemplo: M,5 o M,-3) que modifica la posición del rotor
 */
class TramaMap : public TramaBase {
private:
    int rotacion;  ///< Número de posiciones a rotar
    
public:
    /**
     * @brief Constructor que almacena la cantidad de rotación
     * @param n Número de posiciones a rotar
     */
    TramaMap(int n);
    
    /**
     * @brief Procesa la trama MAP: rota el disco de cifrado
     * @param carga Lista de carga (no se modifica por esta trama)
     * @param rotor Rotor a modificar
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_MAP_H