/**
 * @file ListaDeCarga.cpp
 * @brief Implementación de la clase ListaDeCarga
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#include "ListaDeCarga.h"
#include <iostream>

/**
 * @brief Constructor del nodo
 * @param c Carácter a almacenar en el nodo
 */
NodoCarga::NodoCarga(char c) : dato(c), siguiente(nullptr), anterior(nullptr) {}

/**
 * @brief Constructor que inicializa una lista vacía
 */
ListaDeCarga::ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamanio(0) {
    std::cout << "ListaDeCarga inicializada (vacía)" << std::endl;
}

/**
 * @brief Destructor que libera toda la memoria
 */
ListaDeCarga::~ListaDeCarga() {
    while (cabeza != nullptr) {
        NodoCarga* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

/**
 * @brief Inserta un carácter al final de la lista
 * @param dato Carácter a insertar
 */
void ListaDeCarga::insertarAlFinal(char dato) {
    NodoCarga* nuevo = new NodoCarga(dato);
    
    if (cabeza == nullptr) {
        // Lista vacía
        cabeza = cola = nuevo;
    } else {
        // Agregar al final
        cola->siguiente = nuevo;
        nuevo->anterior = cola;
        cola = nuevo;
    }
    tamanio++;
}

/**
 * @brief Imprime el mensaje completo
 */
void ListaDeCarga::imprimirMensaje() {
    std::cout << "\n=== MENSAJE OCULTO ENSAMBLADO ===" << std::endl;
    if (cabeza == nullptr) {
        std::cout << "(mensaje vacío)" << std::endl;
        return;
    }
    
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato;
        actual = actual->siguiente;
    }
    std::cout << std::endl;
    std::cout << "=== FIN DEL MENSAJE ===" << std::endl;
}

/**
 * @brief Imprime el estado actual de la lista (para debugging)
 */
void ListaDeCarga::imprimirEstado() {
    std::cout << "Lista de carga (tamaño=" << tamanio << "): [";
    NodoCarga* actual = cabeza;
    while (actual != nullptr) {
        std::cout << actual->dato;
        if (actual->siguiente != nullptr) std::cout << "][";
        actual = actual->siguiente;
    }
    std::cout << "]" << std::endl;
}

/**
 * @brief Obtiene el tamaño de la lista
 * @return Número de elementos en la lista
 */
int ListaDeCarga::getTamanio() const {
    return tamanio;
}