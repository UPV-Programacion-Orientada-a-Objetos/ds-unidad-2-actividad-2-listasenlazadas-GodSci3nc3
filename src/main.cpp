/**
 * @file main.cpp
 * @brief Programa principal del Decodificador PRT-7
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "TramaBase.h"
#include "TramaLoad.h"
#include "TramaMap.h"
#include "ListaDeCarga.h"
#include "RotorDeMapeo.h"
#include "SerialReader.h"

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
    std::cout << "Autor: Arturo Rosales Velázquez" << std::endl;
    std::cout << "Iniciando sistema..." << std::endl;
    
    RotorDeMapeo rotor;
    ListaDeCarga carga;
    
    // Secuencia de ejemplo con tus datos originales
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
    
    // Procesar la secuencia de ejemplo
    procesarSecuencia(secuenciaEjemplo, cantidadTramas, &carga, &rotor);
    
    // Mostrar el mensaje final
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
    
    std::cout << "\n--- Probando comunicación serial (comentado por seguridad) ---" << std::endl;
    /*
    // Código para comunicación serial real (descomentado cuando se conecte Arduino)
    const char* puerto = "/dev/ttyUSB0";  // Cambiar según el sistema
    SerialReader serial(puerto, 9600);
    
    if (serial.estaConectado()) {
        std::cout << "Esperando tramas del Arduino..." << std::endl;
        char buffer[256];
        bool transmisionActiva = true;
        
        while (transmisionActiva) {
            if (serial.leerLinea(buffer, sizeof(buffer))) {
                if (strcmp(buffer, "END") == 0) {
                    transmisionActiva = false;
                    continue;
                }
                
                TramaBase* trama = parsearTrama(buffer);
                if (trama) {
                    trama->procesar(&carga, &rotor);
                    delete trama;
                }
            }
        }
        
        carga.imprimirMensaje();
    } else {
        std::cout << "No se pudo conectar al puerto serial." << std::endl;
    }
    */
    
    std::cout << "\n--- Sistema finalizado ---" << std::endl;
    return 0;
}