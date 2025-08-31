#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Usuario &u, Pedido &p)
{
    Usr_Peds_[&u].insert(&p);
    Peds_Usr_[&p] = &u;
}

void Usuario_Pedido::asocia(Pedido &p, Usuario &u)
{
    asocia(u, p); // Reutiliza el método anterior para mantener consistencia
}

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(const Usuario &u) const
{
    auto it = Usr_Peds_.find(const_cast<Usuario *>(&u));
    if (it != Usr_Peds_.end())
    {
        return it->second;
    }
    else
    {
        return Usuario_Pedido::Pedidos();
    }
}

const Usuario *Usuario_Pedido::cliente(const Pedido &p) const
{
    auto it = Peds_Usr_.find(const_cast<Pedido *> (&p));
    if (it != Peds_Usr_.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}