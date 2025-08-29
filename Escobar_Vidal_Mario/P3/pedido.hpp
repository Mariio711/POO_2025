#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "../P1/fecha.hpp"

class Pedido
{
public:
    // clase Pedido::Vacio
    class Vacio
    {
    public:
        // Constructor que recibe el usuario que intentó hacer el pedido vacío
        Vacio(Usuario *usuario) : u(usuario) {}

        // Método observador para devolver el usuario
        const Usuario *usuario() const { return u; }

    private:
        Usuario *u;
    };
    // clase Pedido::Impostor
    class Impostor
    {
    public:
        // Constructor que recibe el usuario que intentó hacer el pedido vacío
        Impostor(Usuario *usuario) : u(usuario) {}

        // Método observador para devolver el usuario
        const Usuario *usuario() const { return u; }

    private:
        Usuario *u;
    };
    // clase Pedido::SinStock
    class SinStock
    {
    public:
        // Constructor que recibe el usuario que intentó hacer el pedido vacío
        SinStock(Articulo *articulo) : a(articulo) {}

        // Método observador para devolver el usuario
        const Articulo *articulo() const { return a; }

    private:
        Articulo *a;
    };

    // constructor
    Pedido(Usuario_Pedido &U_ped, Pedido_Articulo &P_art, Usuario &u, Tarjeta &tarj, const Fecha &f_ped = Fecha());

private:
    const unsigned num_ped_;
    const Tarjeta *pago_;
    Fecha f_ped_;
    double total_;
    static unsigned num_pedidos_;
};

#endif