/**
 * @file ListaDeCarga.h
 * @brief Lista doblemente enlazada para almacenar los datos decodificados
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#ifndef LISTA_DE_CARGA_H
#define LISTA_DE_CARGA_H

/**
 * @brief Nodo para la lista doblemente enlazada de carga
 */
struct NodoCarga {
    char dato;
    NodoCarga* siguiente;
    NodoCarga* anterior;
    
    NodoCarga(char c);
};

/**
 * @class ListaDeCarga
 * @brief Lista doblemente enlazada para almacenar los datos decodificados
 * @details Almacena los caracteres decodificados en el orden correcto para formar el mensaje final
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;  ///< Puntero al primer nodo
    NodoCarga* cola;    ///< Puntero al último nodo
    int tamanio;        ///< Número de elementos en la lista
    
public:
    /**
     * @brief Constructor que inicializa una lista vacía
     */
    ListaDeCarga();
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~ListaDeCarga();
    
    /**
     * @brief Inserta un carácter al final de la lista
     * @param dato Carácter a insertar
     */
    void insertarAlFinal(char dato);
    
    /**
     * @brief Imprime el mensaje completo
     */
    void imprimirMensaje();
    
    /**
     * @brief Imprime el estado actual de la lista (para debugging)
     */
    void imprimirEstado();
    
    /**
     * @brief Obtiene el tamaño de la lista
     * @return Número de elementos en la lista
     */
    int getTamanio() const;
};

#endif // LISTA_DE_CARGA_H