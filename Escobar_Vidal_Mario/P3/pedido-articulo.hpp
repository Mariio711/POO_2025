#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <map>
#include <iostream>
#include <iomanip>
#include "articulo.hpp"

// Forward declarations
class Pedido;

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

std::ostream &operator<<(std::ostream &os, const LineaPedido &lp);

class Pedido_Articulo
{
public:
    // clases de ordenacion para los diccionarios
    class OrdenaArticulos
    {
    public:
        bool operator()(const Articulo *art1, const Articulo *art2) const;
    };

    class OrdenaPedidos
    {
    public:
        // Declaración del operador - implementación en pedido-articulo.cpp
        bool operator()(const Pedido *ped1, const Pedido *ped2) const;
    };

    // diccionarios publicos
    typedef std::map<Articulo *, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido *, LineaPedido, OrdenaPedidos> Pedidos;

    // metodos de asociacion
    void pedir(Pedido &ped, Articulo &art, double precio, unsigned cantidad = 1);
    void pedir(Articulo &art, Pedido &ped, double precio, unsigned cantidad = 1);

    // metodos observadores
    ItemsPedido detalle(const Pedido &ped) const;
    Pedidos ventas(const Articulo &art) const;

    // metodos mostrar
    void mostrarDetallePedidos(std::ostream &os) const noexcept;
    void mostrarVentasArticulos(std::ostream &os) const noexcept;

private:
    typedef std::map<Pedido *, ItemsPedido, OrdenaPedidos> Ped_Art;
    typedef std::map<Articulo *, Pedidos, OrdenaArticulos> Art_Ped;
    Ped_Art Ped_Art_;
    Art_Ped Art_Ped_;
};

std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::ItemsPedido &Art_ped);
std::ostream &operator<<(std::ostream &os, const Pedido_Articulo::Pedidos &Ped_art);

#endif