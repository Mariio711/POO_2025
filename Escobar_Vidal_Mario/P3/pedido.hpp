#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>
#include "tarjeta.hpp"
#include "articulo.hpp"
#include "../P1/fecha.hpp"

class Usuario_Pedido;
class Pedido_Articulo;

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
        const Usuario &usuario() const noexcept { return *u; }

    private:
        Usuario *u;
    };
    // clase Pedido::Impostor
    class Impostor
    {
    public:
        // Constructor que recibe el usuario que intentó usar una tarjeta ajena
        Impostor(Usuario *usuario) : u(usuario) {}

        // Método observador para devolver el usuario
        const Usuario &usuario() const noexcept { return *u; }

    private:
        Usuario *u;
    };
    // clase Pedido::SinStock
    class SinStock
    {
    public:
        // Constructor que recibe el artículo sin stock
        SinStock(Articulo *articulo) : a(articulo) {}

        // Método observador para devolver el artículo
        const Articulo &articulo() const noexcept { return *a; }

    private:
        Articulo *a; // Aquí era un objeto, debe ser un puntero
    };

    // constructor
    Pedido(Usuario_Pedido &U_ped, Pedido_Articulo &P_art, Usuario &u, const Tarjeta &tarj, const Fecha &f_ped = Fecha());

    // Métodos observadores
    unsigned numero() const noexcept { return num_ped_; }
    const Tarjeta *tarjeta() const noexcept { return pago_; }
    const Fecha &fecha() const noexcept { return f_ped_; }
    double total() const noexcept { return total_; }
    static int n_total_pedidos() noexcept { return num_pedidos_; }

private:
    const unsigned num_ped_;
    const Tarjeta *const pago_;
    const Fecha f_ped_;
    double total_;
    static unsigned num_pedidos_;
};

std::ostream &operator<<(std::ostream &os, const Pedido &ped);

#endif