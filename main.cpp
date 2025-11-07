#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

/**
 * @file main.cpp
 * @brief Decodificador de Protocolo Industrial PRT-7
 * @author Arturo Rosales Velázquez
 * @version 1.0
 * @date 2025
 */

class ListaDeCarga;
class RotorDeMapeo;

/**
 * @brief Nodo para la lista circular doblemente enlazada del rotor
 */
struct NodoRotor {
    char dato;
    NodoRotor* siguiente;
    NodoRotor* anterior;
    
    NodoRotor(char c) : dato(c), siguiente(nullptr), anterior(nullptr) {}
};

/**
 * @brief Lista circular doblemente enlazada que actúa como disco de cifrado
 * 
 * Contiene el alfabeto A-Z y puede rotar para cambiar el mapeo de caracteres
 */
class RotorDeMapeo {
private:
    NodoRotor* cabeza;  
    int tamanio;    
    
public:
    /**
     * @brief Constructor que inicializa el rotor con el alfabeto A-Z
     */
    RotorDeMapeo() : cabeza(nullptr), tamanio(0) {
        for (char c = 'A'; c <= 'Z'; c++) {
            insertarCaracter(c);
        }
        std::cout << "RotorDeMapeo inicializado con alfabeto A-Z. Posición inicial: A" << std::endl;
    }
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~RotorDeMapeo() {
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
    void insertarCaracter(char c) {
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
    void rotar(int n) {
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
    char getMapeo(char entrada) {
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
    void imprimir() {
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
};

/**
 * @brief Nodo para la lista doblemente enlazada de carga
 */
struct NodoCarga {
    char dato;
    NodoCarga* siguiente;
    NodoCarga* anterior;
    
    NodoCarga(char c) : dato(c), siguiente(nullptr), anterior(nullptr) {}
};

/**
 * @brief Lista doblemente enlazada para almacenar los datos decodificados
 * 
 * Almacena los caracteres decodificados en el orden correcto para formar el mensaje final
 */
class ListaDeCarga {
private:
    NodoCarga* cabeza;  
    NodoCarga* cola;    
    int tamanio;         
    
public:
    /**
     * @brief Constructor que inicializa una lista vacía
     */
    ListaDeCarga() : cabeza(nullptr), cola(nullptr), tamanio(0) {
        std::cout << "ListaDeCarga inicializada (vacía)" << std::endl;
    }
    
    /**
     * @brief Destructor que libera toda la memoria
     */
    ~ListaDeCarga() {
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
    void insertarAlFinal(char dato) {
        NodoCarga* nuevo = new NodoCarga(dato);
        
        if (cabeza == nullptr) {
        
            cabeza = cola = nuevo;
        } else {
            
            cola->siguiente = nuevo;
            nuevo->anterior = cola;
            cola = nuevo;
        }
        tamanio++;
    }
    
    /**
     * @brief Imprime el mensaje completo
     */
    void imprimirMensaje() {
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
    void imprimirEstado() {
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
    int getTamanio() const {
        return tamanio;
    }
};

/**
 * @brief Clase base abstracta para que todas las tramas del protocolo PRT-7
 * 
 * Esta clase define la interfaz común para todos los tipos de tramas
 * que se reciben del arduino
 */
class TramaBase {
public:
    /**
     * @brief Destructor virtual obligatorio para polimorfismo
     */
    virtual ~TramaBase() {}
    
    /**
     * @brief Método virtual puro para procesar la trama
     * @param carga Puntero a la lista de carga donde se almacenan los datos decodificados
     * @param rotor Puntero al rotor de mapeo que actúa como disco de cifrado
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) = 0;
};

/**
 * @brief Trama de tipo LOAD que contiene un fragmento de dato (un carácter)
 * 
 * Representa una trama L,X (ejemplo: L,A) que almacena un carácter para ser decodificado
 */
class TramaLoad : public TramaBase {
private:
    char caracter;  
    
public:
    /**
     * @brief Constructor que almacena el carácter de la trama
     * @param c Carácter a almacenar
     */
    TramaLoad(char c) : caracter(c) {
        std::cout << "Creada TramaLoad con carácter: '" << c << "'" << std::endl;
    }
    
    /**
     * @brief Procesa la trama LOAD: decodifica el carácter y lo agrega a la lista de carga
     * @param carga Lista donde se almacenan los datos decodificados
     * @param rotor Rotor para el mapeo de caracteres
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        char caracterDecodificado = rotor->getMapeo(caracter);
        std::cout << "Procesando TramaLoad: '" << caracter << "' -> '" << caracterDecodificado << "'" << std::endl;
        carga->insertarAlFinal(caracterDecodificado);
        carga->imprimirEstado();
    }
};

/**
 * @brief Trama de tipo MAP que contiene instrucciones para rotar el disco de cifrado
 * 
 * Representa una trama M,N (ejemplo: M,5 o M,-3) que modifica la posición del rotor
 */
class TramaMap : public TramaBase {
private:
    int rotacion;  
    
public:
    /**
     * @brief Constructor que almacena la cantidad de rotación
     * @param n Número de posiciones a rotar
     */
    TramaMap(int n) : rotacion(n) {
        std::cout << "Creada TramaMap con rotación: " << n << std::endl;
    }
    
    /**
     * @brief Procesa la trama MAP: rota el disco de cifrado
     * @param carga Lista de carga (no se modifica por esta trama)
     * @param rotor Rotor a modificar
     */
    virtual void procesar(ListaDeCarga* carga, RotorDeMapeo* rotor) override {
        std::cout << "Procesando TramaMap: rotando " << rotacion << " posiciones" << std::endl;
        rotor->rotar(rotacion);
    }
};

/**
 * @brief Parsea una cadena de trama y crea el objeto correspondiente
 * @param linea Cadena a parsear (ej. "L,H" o "M,2")
 * @return Puntero a la trama creada, o nullptr si hay error
 */
TramaBase* parsearTrama(const char* linea) {
    if (linea == nullptr || strlen(linea) < 3) {
        std::cout << "Error: Línea inválida o muy corta: " << (linea ? linea : "null") << std::endl;
        return nullptr;
    }
    
    if (linea[1] != ',') {
        std::cout << "Error: Formato inválido (falta coma): " << linea << std::endl;
        return nullptr;
    }
    
    char tipo = linea[0]; 
    const char* parametro = &linea[2]; 
    
    if (tipo == 'L' || tipo == 'l') {
        if (strlen(parametro) != 1) {
            std::cout << "Error: TramaLoad debe tener exactamente un carácter: " << linea << std::endl;
            return nullptr;
        }
        char caracter = parametro[0];
        std::cout << "Parseando: [" << linea << "] -> TramaLoad('" << caracter << "')" << std::endl;
        return new TramaLoad(caracter);
        
    } else if (tipo == 'M' || tipo == 'm') {
        int rotacion = atoi(parametro);
        std::cout << "Parseando: [" << linea << "] -> TramaMap(" << rotacion << ")" << std::endl;
        return new TramaMap(rotacion);
        
    } else {
        std::cout << "Error: Tipo de trama desconocido: " << tipo << std::endl;
        return nullptr;
    }
}

/**
 * @brief Procesa una secuencia de tramas desde un array de strings
 * @param tramas Array de strings con las tramas
 * @param cantidad Número de elementos en el array
 * @param carga Lista de carga donde almacenar los resultados
 * @param rotor Rotor para el mapeo
 */
void procesarSecuencia(const char* tramas[], int cantidad, ListaDeCarga* carga, RotorDeMapeo* rotor) {
    std::cout << "\n=== Procesando secuencia de " << cantidad << " tramas ===" << std::endl;
    
    for (int i = 0; i < cantidad; i++) {
        std::cout << "\n--- Trama " << (i+1) << "/" << cantidad << " ---" << std::endl;
        
        TramaBase* trama = parsearTrama(tramas[i]);
        if (trama != nullptr) {
            trama->procesar(carga, rotor);
            delete trama;
        } else {
            std::cout << "ERROR: No se pudo procesar la trama: " << tramas[i] << std::endl;
        }
    }
    
    std::cout << "\n=== Secuencia completada ===" << std::endl;
}

/**
 * @brief Función principal del programa
 */
int main() {
    std::cout << "=== Decodificador de Protocolo Industrial PRT-7 ===" << std::endl;
    std::cout << "Iniciando sistema..." << std::endl;
    
    RotorDeMapeo rotor;
    ListaDeCarga carga;
    
    const char* secuenciaEjemplo[] = {
        "L,H",
        "L,O", 
        "L,L",
        "M,2",
        "L,A",
        "L, ",    
        "L,W",
        "M,-2",
        "L,O",
        "L,R",
        "L,L", 
        "L,D"
    };
    
    int cantidadTramas = sizeof(secuenciaEjemplo) / sizeof(secuenciaEjemplo[0]);
    
    procesarSecuencia(secuenciaEjemplo, cantidadTramas, &carga, &rotor);
    
    carga.imprimirMensaje();
    
    std::cout << "\n--- Probando parser con casos de error ---" << std::endl;
    TramaBase* tramaError1 = parsearTrama("X,A");      
    TramaBase* tramaError2 = parsearTrama("L");        
    TramaBase* tramaError3 = parsearTrama("L;A");      
    TramaBase* tramaError4 = parsearTrama("M,abc");   
    
    if (tramaError1) delete tramaError1;
    if (tramaError2) delete tramaError2;
    if (tramaError3) delete tramaError3;
    if (tramaError4) delete tramaError4;
    
    std::cout << "\n--- Sistema finalizado ---" << std::endl;
    return 0;
}