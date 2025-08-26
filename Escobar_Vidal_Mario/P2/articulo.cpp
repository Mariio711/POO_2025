#include "articulo.hpp"

/*------------CLASE ARTICULO------------*/

Articulo::Articulo(Cadena cod_ref, Cadena titulo, Fecha fecha, double precio, int stock)
    : referencia_(cod_ref), titulo_(titulo), f_publi_(fecha), precio_(precio), stock_(stock)
{
}

std::ostream &operator<<(std::ostream &os, const Articulo &A)
{
    if (os)
    {
        os.setf(std::ios::fixed); // notacion de punto fijo
        os.precision(2);          // dos decimales
        os << "[" << A.referencia() << "] " << "\"" << A.titulo() << "\", " << A.f_publi().anno() << ". " << A.precio() << " €";
    }
    return os;
}