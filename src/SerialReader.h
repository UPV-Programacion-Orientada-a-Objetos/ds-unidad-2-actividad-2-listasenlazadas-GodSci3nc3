/**
 * @file SerialReader.h
 * @brief Declaración de la clase SerialReader para lectura del puerto serial
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#ifndef SERIAL_READER_H
#define SERIAL_READER_H

#ifdef _WIN32
    #include <windows.h>
#else
    #include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>
#endif

/**
 * @class SerialReader
 * @brief Maneja la comunicación serial con el dispositivo Arduino
 * @details Implementa lectura del puerto COM/ttyUSB compatible con
 *          Windows y Linux usando APIs nativas
 */
class SerialReader {
private:
#ifdef _WIN32
    HANDLE hSerial; ///< Handle del puerto serial en Windows
#else
    int fd; ///< File descriptor del puerto serial en Linux
#endif
    bool conectado; ///< Estado de la conexión
    
public:
    /**
     * @brief Constructor
     * @param puerto Nombre del puerto (ej: "COM3" o "/dev/ttyUSB0")
     * @param baudRate Velocidad de comunicación (default: 9600)
     */
    SerialReader(const char* puerto, int baudRate = 9600);
    
    /**
     * @brief Destructor
     * @details Cierra el puerto serial si está abierto
     */
    ~SerialReader();
    
    /**
     * @brief Lee una línea completa del puerto serial
     * @param buffer Buffer donde se almacenará la línea leída
     * @param maxLength Tamaño máximo del buffer
     * @return true si se leyó correctamente, false en caso de error
     * @details Lee hasta encontrar '\n' o alcanzar maxLength
     */
    bool leerLinea(char* buffer, int maxLength);
    
    /**
     * @brief Verifica si la conexión está establecida
     * @return true si está conectado, false en caso contrario
     */
    bool estaConectado() const;
};

#endif // SERIAL_READER_H