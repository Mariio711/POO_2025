#include "pedido.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

int Pedido::num_pedidos_ = 0;

Pedido::Pedido(Usuario_Pedido &U_ped, Pedido_Articulo &P_art, Usuario &u, const Tarjeta &tarj, const Fecha &f_ped)
    : num_ped_(num_pedidos_ + 1), pago_(&tarj), f_ped_(f_ped), total_(0.0)
{
    // si no hay articulos en el carrito, lanza excepcion
    if (u.n_articulos() == 0)
    {
        throw Vacio(&u);
    }

    // si la tarjeta no pertenece al usuario, lanza excepcion
    if (&u != tarj.titular())
    {
        throw Impostor(&u);
    }

    // si no hay stock de algun articulo, vacia carro y lanza excepcion
    for (auto it : u.compra())
    {
        if (it.first->stock() < it.second)
        {
            u.vaciar_carro();
            throw SinStock(it.first);
        }
    }

    // si la tarjeta esta caducada
    if (tarj.caducidad() < f_ped_)
    {
        throw Tarjeta::Caducada(tarj.caducidad());
    }

    // si la tarjeta esta desactivada
    if (!tarj.activa())
    {
        throw Tarjeta::Desactivada();
    }

    // actualizar pedido
    for (auto &[articulo, cantidad] : u.compra())
    {
        P_art.pedir(*this, *articulo, articulo->precio(), cantidad);

        articulo->stock() -= cantidad;
        total_ = total_ + articulo->precio() * cantidad;
    }

    U_ped.asocia(u, *this);

    u.vaciar_carro();

    ++num_pedidos_;
}
 
std::ostream &operator<<(std::ostream &os, const Pedido &ped)
{
    if (os)
    {
        os.setf(std::ios::fixed); // notacion de punto fijo
        os.precision(2);          // dos decimales
        os << "Núm. pedido: " << ped.numero() << std::endl;
        os << "Fecha:       " << ped.fecha() << std::endl;
        os << "Pagado con:  " << ped.tarjeta()->tipo() << " n.º: " << ped.tarjeta()->numero() << std::endl;
        os << "Importe:     " << ped.total() << " €" << std::endl;
    }
    return os;
}