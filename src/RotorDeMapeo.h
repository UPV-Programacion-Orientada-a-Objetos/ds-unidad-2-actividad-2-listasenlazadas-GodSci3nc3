/**
 * @file RotorDeMapeo.h
 * @brief Lista circular doblemente enlazada que actúa como disco de cifrado
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#ifndef ROTOR_DE_MAPEO_H
#define ROTOR_DE_MAPEO_H

/**
 * @brief Nodo para la lista circular doblemente enlazada del rotor
 */
struct NodoRotor {
    char dato;
    NodoRotor* siguiente;
    NodoRotor* anterior;
    
    NodoRotor(char c);
};

/**
 * @class RotorDeMapeo
 * @brief Lista circular doblemente enlazada que actúa como disco de cifrado
 * @details Contiene el alfabeto A-Z y puede rotar para cambiar el mapeo de caracteres
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza;  ///< Puntero al nodo actual de posición cero
    int tamanio;        ///< Tamaño de la lista circular
    
public:
    /**
     * @brief Constructor que inicializa el rotor con el alfabeto A-Z
     */
    RotorDeMapeo();
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~RotorDeMapeo();
    
    /**
     * @brief Inserta un carácter al final de la lista circular
     * @param c Carácter a insertar
     */
    void insertarCaracter(char c);
    
    /**
     * @brief Rota el rotor N posiciones
     * @param n Número de posiciones a rotar (positivo = horario, negativo = antihorario)
     */
    void rotar(int n);
    
    /**
     * @brief Obtiene el mapeo de un carácter según la rotación actual
     * @param entrada Carácter de entrada
     * @return Carácter mapeado según la posición actual del rotor
     */
    char getMapeo(char entrada);
    
    /**
     * @brief Imprime el estado actual del rotor (para debugging)
     */
    void imprimir();
};

#endif // ROTOR_DE_MAPEO_H