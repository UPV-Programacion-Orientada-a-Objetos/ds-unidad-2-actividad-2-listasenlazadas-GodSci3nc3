/**
 * @file RotorDeMapeo.cpp
 * @brief Implementación de la clase RotorDeMapeo
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#include "RotorDeMapeo.h"
#include <iostream>

/**
 * @brief Constructor del nodo
 * @param c Carácter a almacenar en el nodo
 */
NodoRotor::NodoRotor(char c) : dato(c), siguiente(nullptr), anterior(nullptr) {}

/**
 * @brief Constructor que inicializa el rotor con el alfabeto A-Z
 */
RotorDeMapeo::RotorDeMapeo() : cabeza(nullptr), tamanio(0) {
    for (char c = 'A'; c <= 'Z'; c++) {
        insertarCaracter(c);
    }
    std::cout << "RotorDeMapeo inicializado con alfabeto A-Z. Posición inicial: A" << std::endl;
}

/**
 * @brief Destructor que libera toda la memoria
 */
RotorDeMapeo::~RotorDeMapeo() {
    if (cabeza == nullptr) return;
    
    NodoRotor* actual = cabeza;
    do {
        NodoRotor* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    } while (actual != cabeza);
}

/**
 * @brief Inserta un carácter al final de la lista circular
 * @param c Carácter a insertar
 */
void RotorDeMapeo::insertarCaracter(char c) {
    NodoRotor* nuevo = new NodoRotor(c);
    
    if (cabeza == nullptr) {
        cabeza = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        NodoRotor* ultimo = cabeza->anterior;
        nuevo->siguiente = cabeza;
        nuevo->anterior = ultimo;
        ultimo->siguiente = nuevo;
        cabeza->anterior = nuevo;
    }
    tamanio++;
}

/**
 * @brief Rota el rotor N posiciones
 * @param n Número de posiciones a rotar (positivo = horario, negativo = antihorario)
 */
void RotorDeMapeo::rotar(int n) {
    if (cabeza == nullptr) return;
    
    std::cout << "Rotando rotor " << n << " posiciones. ";
    
    n = n % tamanio;
    if (n < 0) n += tamanio;
    
    for (int i = 0; i < n; i++) {
        cabeza = cabeza->siguiente;
    }
    
    std::cout << "Nueva posición cero: '" << cabeza->dato << "'" << std::endl;
}

/**
 * @brief Obtiene el mapeo de un carácter según la rotación actual
 * @param entrada Carácter de entrada
 * @return Carácter mapeado según la posición actual del rotor
 */
char RotorDeMapeo::getMapeo(char entrada) {
    if (cabeza == nullptr) return entrada;
    
    if (entrada < 'A' || entrada > 'Z') {
        return entrada;
    }
    
    int posicionOriginal = entrada - 'A';
    
    NodoRotor* actual = cabeza;
    for (int i = 0; i < posicionOriginal; i++) {
        actual = actual->siguiente;
    }
    
    return actual->dato;
}

/**
 * @brief Imprime el estado actual del rotor (para debugging)
 */
void RotorDeMapeo::imprimir() {
    if (cabeza == nullptr) {
        std::cout << "Rotor vacío" << std::endl;
        return;
    }
    
    std::cout << "Rotor (posición cero='" << cabeza->dato << "'): ";
    NodoRotor* actual = cabeza;
    do {
        std::cout << actual->dato;
        if (actual == cabeza) std::cout << "*"; 
        std::cout << " ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << std::endl;
}