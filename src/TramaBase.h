/**
 * @file TramaBase.h
 * @brief Clase base abstracta para todas las tramas del protocolo PRT-7
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#ifndef TRAMA_BASE_H
#define TRAMA_BASE_H

// Forward declarations para evitar dependencias circulares
class ListaDeCarga;
class RotorDeMapeo;

/**
 * @class TramaBase
 * @brief Clase base abstracta que define la interfaz para todas las tramas del protocolo PRT-7
 * @details Esta clase define la interfaz común para todos los tipos de tramas
 *          que se reciben del arduino. Implementa el patrón Template Method mediante polimorfismo.
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual obligatorio para polimorfismo
     * @details CRÍTICO: Debe ser virtual para permitir la limpieza correcta
     *          de memoria al eliminar objetos derivados mediante punteros base
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Método virtual puro para procesar la trama
     * @param carga Puntero a la lista de carga donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo que actúa como disco de cifrado
     * @details Este método debe ser implementado por todas las clases derivadas.
     *          Define el comportamiento específico de cada tipo de trama.
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

#endif // TRAMA_BASE_H