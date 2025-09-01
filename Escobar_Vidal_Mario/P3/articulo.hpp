#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include <iostream>

class Articulo
{
public:
    // constructor unico
    Articulo(Cadena cod_ref, Cadena titulo, Fecha fecha, double precio, int stock = 0);

    // metodos observadores
    const Cadena referencia() const { return referencia_; }; // const no puede modificar
    const Cadena titulo() const { return titulo_; };         // const no puede modificar
    const Fecha f_publi() const { return f_publi_; };        // const no puede modificar
    double precio() const { return precio_; };               // const no puede modificar
    double &precio() { return precio_; };                    // no-const puede modificar
    unsigned stock() const { return stock_; };               // const no puede modificar
    unsigned &stock() { return stock_; };                    // no-const puede modificar

private:
    const Cadena referencia_, titulo_;
    const Fecha f_publi_;
    double precio_;
    unsigned stock_;
};

// operador de insercion en flujo de salida
std::ostream &operator<<(std::ostream &os, const Articulo &A);
#endif