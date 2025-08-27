#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <cctype>
#include <cstddef>
#include "cadena.hpp"

class Numero
{
public:
    // enumeracion a nivel de la clase Numero (Numero::Razon)
    enum Razon
    {
        LONGITUD,
        DIGITOS,
        NO_VALIDO
    };

    // clase Clave::Incorrecta
    class Incorrecta
    {
    public:
        Incorrecta(Razon r) : razon_(r) {}
        Razon razon() const { return razon_; }

    private:
        Razon razon_;
    };

    //constructor
    Numero(const Cadena num);

    //operador a cadena de bajo nivel
    explicit operator const char*() const;

    //operador menor-que
    friend bool operator<(const Numero &a, const Numero &b);


private:
    Cadena numero_;

};

#endif