#include "cadena.hpp"
#include <stdexcept>

// Inicialización del atributo de clase
char Cadena::vacia[1] = {'\0'};

// Constructor predeterminado
Cadena::Cadena(size_t n, char a) : tam_(n), s_(n > 0 ? new char[n + 1] : vacia) {
    if (n > 0) {
        std::memset(s_, a, n);
        s_[n] = '\0';
    }
}

// Constructor de conversión explícito
Cadena::Cadena(const char* cadena) : tam_(std::strlen(cadena)), s_(tam_ > 0 ? new char[tam_ + 1] : vacia) {
    if (tam_ > 0) {
        std::strcpy(s_, cadena);
    }
}

// Constructor de copia
Cadena::Cadena(const Cadena& otra) : Cadena(otra.s_) {}

// Operador de asignación
Cadena& Cadena::operator=(const Cadena& otra) {
    if (this != &otra) {
        *this = otra.s_; // Delegamos en el operador de asignación desde const char*
    }
    return *this;
}

// Operador de asignación para cadenas de bajo nivel
Cadena& Cadena::operator=(const char* cadena) {
    if (cadena == s_) {
        return *this; // Evitar autoasignación
    }
    size_t nueva_tam = std::strlen(cadena);
    char* nueva_s = nueva_tam > 0 ? new char[nueva_tam + 1] : vacia;
    if (nueva_tam > 0) {
        std::strcpy(nueva_s, cadena);
    }
    if (tam_ > 0) {
        delete[] s_; // Liberar la memoria existente
    }
    tam_ = nueva_tam;
    s_ = nueva_s;
    return *this;
}

// Destructor
Cadena::~Cadena() {
    if (tam_ > 0) {
        delete[] s_;
    }
}

//operadores de comparacion
bool operator==(const Cadena& a, const Cadena& b){
    return std::strcmp(a.s_, b.s_) == 0;
}

bool operator<(const Cadena& a, const Cadena& b) {
    return std::strcmp(a.s_, b.s_) < 0;
}

bool operator>(const Cadena& a, const Cadena& b) {
    return std::strcmp(a.s_, b.s_) > 0;
}

bool operator<=(const Cadena& a, const Cadena& b) {
    return std::strcmp(a.s_, b.s_) <= 0;
}

bool operator>=(const Cadena& a, const Cadena& b) {
    return std::strcmp(a.s_, b.s_) >= 0;
}

bool operator!=(const Cadena& a, const Cadena& b) {
    return std::strcmp(a.s_, b.s_) != 0;
}

// Operador de suma con asignación
Cadena& Cadena::operator+=(const Cadena& b) {
    size_t nueva_tam = tam_ + b.tam_;
    char* nueva_s = nueva_tam > 0 ? new char[nueva_tam + 1] : vacia;
    if (nueva_tam > 0) {
        std::strcpy(nueva_s, s_);
        std::strcat(nueva_s, b.s_);
    }
    if (tam_ > 0) {
        delete[] s_; // Liberar la memoria existente
    }
    tam_ = nueva_tam;
    s_ = nueva_s;
    return *this;
}

// Operador de suma
Cadena operator+(const Cadena& a, const Cadena& b) {
    size_t nueva_tam = a.tam_ + b.tam_;
    char* nueva_s = nueva_tam > 0 ? new char[nueva_tam + 1] : Cadena::vacia;
    if (nueva_tam > 0) {
        std::strcpy(nueva_s, a.s_);
        std::strcat(nueva_s, b.s_);
    }
    Cadena temp(nueva_s);
    if (nueva_tam > 0) {
        delete[] nueva_s;
    }
    return temp;
}

//operaodres de indice
//no const
char& Cadena::operator[](size_t i){
    return s_[i];
}

//const
const char& Cadena::operator[](size_t i) const{
    return s_[i];
}

//conversion a cadena de bajo nivel
Cadena::operator const char*() const{
    return s_;
}

/*-----------------METODOS------------------*/
//funcion que devuleve el caracter del indice comprobando si este esta o no fuera de rango
//no const
char& Cadena::at(size_t i){
    if (i >= length()){
        throw std::out_of_range("Indice fuera de rango");
    }
    return s_[i];
}

//const
const char& Cadena::at(size_t i) const {
    if (i >= length()) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return s_[i];
}

//funcion que devuelve una cadena formada por los caracteres desde el indice i hasta los caracteres tam.
Cadena Cadena::substr(unsigned int i, unsigned int tam) const{
    if (i >= length() || (length() - i) < tam){
        throw std::out_of_range("Indice fuera de rango o tamaño de la cadena supera los caracteres desde el indice");
    }
    char* subs = new char[tam + 1];
    std::strncpy(subs, s_ +i, tam);
    subs[tam] = '\0';
    Cadena res(subs);
    delete[] subs;
    return res;
}


