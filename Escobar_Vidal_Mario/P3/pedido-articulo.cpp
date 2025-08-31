#include "pedido-articulo.hpp"
#include "pedido.hpp" // Ahora sí podemos incluir pedido.hpp

// Implementación del operador de comparación de OrdenaPedidos
bool Pedido_Articulo::OrdenaPedidos::operator()(const Pedido *ped1, const Pedido *ped2) const
{
    return ped1->numero() < ped2->numero();
}

std::ostream &operator<<(std::ostream &os, const LineaPedido &lp)
{
    if (os)
    {
        os.setf(std::ios::fixed); // notacion de punto fijo
        os.precision(2);          // dos decimales
        os << lp.precio_venta() << " €" << std::setw(4) << lp.cantidad();
    }
    return os;
}

void Pedido_Articulo::pedir(Pedido &ped, Articulo &art, double precio, unsigned cantidad)
{
    Ped_Art_[&ped].insert(std::make_pair(&art, LineaPedido(precio, cantidad)));
    Art_Ped_[&art].insert(std::make_pair(&ped, LineaPedido(precio, cantidad)));
}

void Pedido_Articulo::pedir(Articulo &art, Pedido &ped, double precio, unsigned cantidad)
{
    pedir(ped, art, precio, cantidad);
}

// Métodos observadores
Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(const Pedido &ped) const
{
    auto it = Ped_Art_.find(const_cast<Pedido *>(&ped)); // Buscamos pedido
    if (it != Ped_Art_.end())
    { // Si lo hemos encontrado
        return it->second;
    }
    else
        return ItemsPedido{}; // Devuelve map vacío
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(const Articulo &art) const
{
    auto it = Art_Ped_.find(const_cast<Articulo *>(&art)); // Buscamos artículo
    if (it != Art_Ped_.end())                              // Existe
        return it->second;
    else
        return Pedidos{}; // Devuelve map vacío
}

/* Métodos ostream */
std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::ItemsPedido &ped)
{
    double total = 0;
    int nejemplar = 0;

    os << std::setfill(' ') << std::setw(10) << "PVP" << std::setw(16) << "Cantidad" << std::setw(20) << "Artículo" << std::endl;
    os << std::setfill('=') << std::setw(65) << "" << std::endl;

    for (auto const &it : ped)
    {
        // Definimos nombres para más claridad
        const Articulo &a = *it.first;
        const LineaPedido &lp = it.second;

        total += lp.precio_venta() * lp.cantidad(); // Para el precio total
        nejemplar += lp.cantidad();

        os << std::setfill(' ') << lp.precio_venta() << std::setw(10) << " €"
           << std::setw(16) << lp.cantidad()
           << "[" << a.referencia() << "] " << a.titulo() << std::endl;
    }
    os << std::setfill('=') << std::setw(65) << "" << std::endl;
    os << std::setfill(' ') << std::setw(10) << "Total:" << total << std::setw(10) << " €" << std::setw(8) << nejemplar << std::endl;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::Pedidos &art)
{
    double total = 0.0;
    int nejemplar = 0;

    os << " [Pedidos: " << art.size() << "]" << std::endl;
    os << std::setfill('=') << std::setw(65) << " " << std::endl;
    os << std::setfill(' ') << std::setw(10) << " PVP" << std::setw(16) << "Cantidad" << std::setw(20) << "Fecha de venta" << std::endl;
    os << std::setfill('=') << std::setw(65) << " " << std::endl;
    for (auto const &it : art)
    {
        const Pedido &p = *it.first;
        const LineaPedido &l = it.second;

        total += l.precio_venta() * l.cantidad();
        nejemplar += l.cantidad();

        os << l << std::setw(20) << p.fecha() << std::endl;
    }

    os << std::setfill('=') << std::setw(65) << " " << std::endl;
    os << std::setfill(' ') << " " << total << " €" << "\t" << nejemplar << std::endl;
    return os;
}

// Métodos mostrar
void Pedido_Articulo::mostrarDetallePedidos(std::ostream &os) const noexcept
{
    double total = 0.0;

    for (auto &it : Ped_Art_)
    {
        const Pedido &p = *it.first;
        const ItemsPedido &ip = it.second;

        total += p.total();
        os << "Pedido num. " << p.numero() << std::endl;
        os << "Cliente: " << p.tarjeta()->titular()->nombre() << "\t"
           << "Fecha: " << p.fecha() << std::endl;

        os << detalle(p) << std::endl;
    }
    os << std::setw(20) << "TOTAL VENTAS" << "\t" << total << " €" << std::endl;
}

void Pedido_Articulo::mostrarVentasArticulos(std::ostream &os) const noexcept
{
    for (auto &it : Art_Ped_)
    {
        os << "Venta de [" << it.first->referencia() << "] " << it.first->titulo() << std::endl;
        os << ventas(*it.first) << std::endl;
    }
}