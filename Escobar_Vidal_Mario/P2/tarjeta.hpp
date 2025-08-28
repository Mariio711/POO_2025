#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <cctype>
#include <cstddef>
#include <iostream>
#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

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

    // constructor
    Numero(const Cadena num);

    // operador a cadena de bajo nivel
    explicit operator const char *() const;

    // operador menor-que
    friend bool operator<(const Numero &a, const Numero &b);

private:
    Cadena numero_;
};

class Tarjeta
{
public:
    enum Tipo
    {
        Otro,
        VISA,
        MasterCard,
        Maestro,
        JCB,
        AmericanExpress
    };

    // clase de error fecha caducada
    class Caducada
    {
    public:
        Caducada(Fecha &r) : f_cad_(r) {}
        Fecha cuando() const { return f_cad_; }

    private:
        Fecha f_cad_;
    };

    // clase de error numero duplicado
    class Num_duplicado
    {
    public:
        Num_duplicado(Numero &r) : num_(r) {}
        Numero que() const { return num_; }

    private:
        Numero num_;
    };

    // constructor unico
    Tarjeta(Numero num, Usuario tit, Fecha f);

    // prohibir la copia
    Tarjeta(const Tarjeta &t) = delete;
    Tarjeta &operator=(const Tarjeta &t) = delete;

    // metodos observadores
    const Numero numero() const { return numero_; };
    const Usuario *titular() const { return titular_; };
    const Fecha caducidad() const { return f_caducidad_; };
    const bool activa() const { return activa_; };
    const Tipo tipo() const;

    // metodos modificadores
    bool activa(const bool nuevo); // activar o desactivar tarjeta
    void anula_titular();          // desvincula del usuario titular y desactiva tarjeta

    //sobrecarga del operador de insercion
    friend std::ostream &operator<<(std::ostream &os, Tarjeta &tarj);

    //operador menor-que
    friend bool operator<(Tarjeta &tarj_a, Tarjeta &tarj_b);

    //destructor
    ~Tarjeta();

private:
    const Numero numero_;
    const Usuario *titular_;
    const Fecha f_caducidad_;
    bool activa_;
};
#endif