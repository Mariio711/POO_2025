#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>
#include "tarjeta.hpp"
#include "articulo.hpp"
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
        // Constructor que recibe el artículo sin stock
        SinStock(Articulo *articulo) : a(articulo) {}

        // Método observador para devolver el artículo
        const Articulo *articulo() const { return a; }

    private:
        Articulo *a;
    };

    // constructor
    Pedido(Usuario_Pedido &U_ped, Pedido_Articulo &P_art, Usuario &u, const Tarjeta &tarj, const Fecha &f_ped = Fecha());

    //Métodos observadores
    int numero() const{return num_ped_;}
    const Tarjeta* tarjeta() const{return pago_;}
    const Fecha& fecha() const {return f_ped_;}
    double total() const{return total_;}
    static int n_total_pedidos(){return num_pedidos_;}

private:
    const unsigned num_ped_;
    const Tarjeta *pago_;
    Fecha f_ped_;
    double total_;
    static unsigned num_pedidos_;
};

inline unsigned Pedido::num_pedidos_ = 1;
std::ostream& operator <<(std::ostream& os, const Pedido& ped);


#endif