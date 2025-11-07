/**
 * @file SerialReader.cpp
 * @brief Implementación de la clase SerialReader
 * @author Arturo Rosales Velázquez
 * @date 2025
 */

#include "SerialReader.h"
#include <iostream>
#include <cstring>

SerialReader::SerialReader(const char* puerto, int baudRate) : conectado(false) {
#ifdef _WIN32
    // Configuración para Windows
    hSerial = CreateFileA(puerto,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          nullptr,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          nullptr);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cerr << "Error: No se pudo abrir el puerto " << puerto << std::endl;
        return;
    }
    
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al obtener estado del puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    dcbSerialParams.BaudRate = baudRate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        std::cerr << "Error al configurar puerto" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        std::cerr << "Error al configurar timeouts" << std::endl;
        CloseHandle(hSerial);
        return;
    }
    
    conectado = true;
    std::cout << "Puerto serial " << puerto << " abierto exitosamente (Windows)" << std::endl;

#else
    // Configuración para Linux
    fd = open(puerto, O_RDWR | O_NOCTTY | O_NONBLOCK);
    
    if (fd == -1) {
        std::cerr << "Error: No se pudo abrir el puerto " << puerto << std::endl;
        return;
    }
    
    struct termios options;
    tcgetattr(fd, &options);
    
    // Configurar velocidad
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    
    // Configurar formato: 8N1
    options.c_cflag &= ~PARENB;   // Sin paridad
    options.c_cflag &= ~CSTOPB;   // 1 bit de stop
    options.c_cflag &= ~CSIZE;    // Limpiar bits de tamaño
    options.c_cflag |= CS8;       // 8 bits de datos
    
    // Control local
    options.c_cflag |= CREAD | CLOCAL;
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    
    // Timeouts
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 1;
    
    tcsetattr(fd, TCSANOW, &options);
    
    conectado = true;
    std::cout << "Puerto serial " << puerto << " abierto exitosamente (Linux)" << std::endl;
#endif
}

SerialReader::~SerialReader() {
    if (conectado) {
#ifdef _WIN32
        CloseHandle(hSerial);
#else
        close(fd);
#endif
        std::cout << "Puerto serial cerrado" << std::endl;
    }
}

bool SerialReader::leerLinea(char* buffer, int maxLength) {
    if (!conectado) return false;
    
    int pos = 0;
    char c;
    
    while (pos < maxLength - 1) {
#ifdef _WIN32
        DWORD bytesRead;
        if (!ReadFile(hSerial, &c, 1, &bytesRead, nullptr)) {
            return false;
        }
        if (bytesRead == 0) continue;
#else
        int result = read(fd, &c, 1);
        if (result <= 0) continue;
#endif
        
        if (c == '\n') {
            buffer[pos] = '\0';
            return true;
        }
        
        if (c != '\r') {
            buffer[pos++] = c;
        }
    }
    
    buffer[pos] = '\0';
    return true;
}

bool SerialReader::estaConectado() const {
    return conectado;
}