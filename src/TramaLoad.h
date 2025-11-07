/**
 * @file TramaLoad.h
 * @brief Trama de tipo LOAD que contiene un fragmento de dato (un carácter)
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#ifndef TRAMA_LOAD_H
#define TRAMA_LOAD_H

#include "TramaBase.h"

/**
 * @class TramaLoad
 * @brief Trama de tipo LOAD que contiene un fragmento de dato (un carácter)
 * @details Representa una trama L,X (ejemplo: L,A) que almacena un carácter para ser decodificado
 */
class TramaLoad : public TramaBase {
private:
    char caracter;  ///< Carácter almacenado en la trama
    
public:
    /**
     * @brief Constructor que almacena el carácter de la trama
     * @param c Carácter a almacenar
     */
    TramaLoad(char c);
    
    /**
     * @brief Procesa la trama LOAD: decodifica el carácter y lo agrega a la lista de carga
     * @param carga Lista donde se almacenan los datos decodificados
     * @param rotor Rotor para el mapeo de caracteres
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override;
};

#endif // TRAMA_LOAD_H