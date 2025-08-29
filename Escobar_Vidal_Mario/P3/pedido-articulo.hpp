#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <map>
#include <iostream>
#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido
{
public:
    // constructor
    explicit LineaPedido(double pv = 0.0, unsigned cant = 1) : precio_venta_(pv), cantidad_(cant) {}

    // Observadores
    double precio_venta() const noexcept { return precio_venta_; }
    unsigned cantidad() const noexcept { return cantidad_; }

private:
    double precio_venta_;
    unsigned cantidad_;
};

std::ostream &operator<<(std::ostream &os, LineaPedido &lp)
{
    if (os)
    {
        os.setf(std::ios::fixed); // notacion de punto fijo
        os.precision(2);          // dos decimales
        os << lp.precio_venta() << " €    " << lp.cantidad() << std::endl;
    }
}

class Pedido_Articulo
{
public:
    // clases de ordenacion para los diccionarios
    class OrdenaArticulos
    {
        bool operator()(const Articulo *art1, const Articulo *art2) const { return art1->referencia() < art2->referencia(); }
    };

    class OrdenaPedidos
    {
        bool operator()(const Pedido *ped1, const Pedido *ped2) const { return ped1->numero() < ped2->numero(); }
    };

    // diccionarios publicos
    typedef std::map<Articulo *, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido *, LineaPedido, OrdenaPedidos> Pedidos;

    // metodos de asociacion
    void pedir(Pedido &ped, Articulo &art, double precio, unsigned cantidad = 1);
    void pedir(Articulo &art, Pedido &ped, double precio, unsigned cantidad = 1);

    // metodos observadores
    const ItemsPedido &detalle(const Pedido &ped) const;
    const Pedidos &ventas(const Articulo &art) const;

    // metodos mostrar
    void mostarDetallePedidos(std::ostream &os);
    void mostarVentasArticulos(std::ostream &os);

private:
    typedef std::map<Pedido *, ItemsPedido, OrdenaPedidos> Ped_Art;
    typedef std::map<Articulo *, Pedidos, OrdenaArticulos> Art_Ped;
    Ped_Art Ped_Art_;
    Art_Ped Art_Ped_;
};

std::ostream &operator<<(std::ostream &os, Pedido_Articulo::ItemsPedido &Art_ped);
std::ostream &operator<<(std::ostream &os, Pedido_Articulo::Pedidos &Ped_art);

#endif