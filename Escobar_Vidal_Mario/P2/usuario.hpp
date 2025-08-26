#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unistd.h>
#include <random>
#include "cadena.hpp"

class Clave
{
public:
    // enumeracion a nivel de la clase Clave (Clave::Razon)
    enum Razon
    {
        CORTA,
        ERROR_CRYPT
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

    // constructor
    Clave(const char *cad);

    // metodo observador
    Cadena clave() const; // devuelve la contraseña cifrada (clave_)

    // metodo verificar
    bool verifica(const char *cad) const; // recibe la contraseña en claro y devuelve verdadero si corresponde con la contraseña

    friend const Cadena &cifrar(const char *cad);

private:
    Cadena clave_;                          // aloja la contraseña cifrada
    static const char caracteres_validos[]; // Conjunto de caracteres entre los que escoger la «sal» para encriptar las claves
};

#endif