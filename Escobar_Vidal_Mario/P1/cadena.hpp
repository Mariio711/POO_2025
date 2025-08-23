#ifndef CADENA_H_
#define CADENA_H_

#include <cstring>
#include <iostream>

class Cadena{
    public:
        //constructores
        explicit Cadena(size_t n = 0, char a = ' ');  //predeterminado
        Cadena(const char* cadena);        //de conversion
        Cadena(const Cadena& otra);                 //de copia

        //operador de aignación
        Cadena& operator=(const Cadena& otra);
        Cadena& operator=(const char* cadena);

        //destructor
        ~Cadena();

        //metodos observadores
        size_t length() const {return std::strlen(s_);}; //devuelve la longitud de la cadena c

        //operadores de comparación
        friend bool operator== (const Cadena& a, const Cadena& b);
        friend bool operator< (const Cadena& a, const Cadena& b);
        friend bool operator> (const Cadena& a, const Cadena& b);
        friend bool operator<= (const Cadena& a, const Cadena& b);
        friend bool operator>= (const Cadena& a, const Cadena& b);
        friend bool operator!= (const Cadena& a, const Cadena& b);

        //operadores aritmeticos
        Cadena& operator +=(const Cadena& b);                               //concatenación
        friend Cadena operator+(const Cadena& a, const Cadena& b);         //concatenaciôn sin

        //operador de indice
        char& operator[] (size_t i);
        const char& operator[] (size_t i) const;

        //conversion a cadena de bajo nivel
        //explicit operator const char*() const; // deja de ser necesario por el operador de inserción

        //operadores de insercion y extracción
        friend std::ostream& operator <<(std::ostream& os, const Cadena &c);
        friend std::istream& operator >>(std::istream& is, Cadena &c);


        //metodos
        char& at(size_t i);
        const char& at(size_t i) const;
        Cadena substr(unsigned int i, unsigned int tam) const;
    private:
        static char vacia[1];
        size_t tam_;
        char* s_;

};

#endif 