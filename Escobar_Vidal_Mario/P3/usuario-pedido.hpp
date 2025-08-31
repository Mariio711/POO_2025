#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <map>
#include <set>
#include <iostream>
#include "usuario.hpp"
#include "pedido.hpp"

class Pedido;

class Usuario_Pedido
{
public:
    typedef std::set<Pedido*> Pedidos;

    //metodos de asociacion
    void asocia(Usuario &u, Pedido&p);
    void asocia(Pedido&p, Usuario &u);

    //metodos observadores
    Pedidos pedidos(const Usuario &u) const;
    const Usuario* cliente(const Pedido &p) const;

private:
    typedef std::map<Usuario*, Pedidos> Usr_Pedidos;
    typedef std::map<Pedido*, Usuario*> Pedido_usr;
    Usr_Pedidos Usr_Peds_;
    Pedido_usr Peds_Usr_;
};

#endif