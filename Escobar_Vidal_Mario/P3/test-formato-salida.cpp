#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include "usuario.hpp"
#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

using namespace std;

// Función auxiliar para las comprobaciones
void mostrar_operador_insercion(ostream& os, const Pedido_Articulo::Pedidos& pedidos) {
    // Mostrar directamente el contenido para verificar el orden natural del mapa
    os << "Verificación manual del orden:\n";
    for (const auto& p : pedidos) {
        os << "Pedido #" << p.first->numero() << " - " << p.second.cantidad() 
           << " unidades a " << fixed << setprecision(2) << p.second.precio_venta() << " €\n";
    }
    os << "\nOperador de inserción normal:\n";
    os << pedidos << endl;
}

int main() {
    // Crear artículos para las pruebas
    // Referencia [100] - debe aparecer primero por OrdenaArticulos
    Articulo articulo1("[100]", "Programación Orientada a Objetos", "01/03/2019", 35.20, 30);
    // Referencia [110] - debe aparecer segundo por OrdenaArticulos
    Articulo articulo2("[110]", "Fundamentos de C++", "09/07/2020", 29.95, 50);
    
    // Crear usuario y tarjeta para los pedidos
    Usuario usuario("u123", "Usuario Prueba", "Dir Prueba", "123456789");
    Numero num("1234567890123456");
    Tarjeta tarjeta(num, usuario, Fecha(31, 12, 2025));
    usuario.es_titular_de(tarjeta);
    
    // Añadir artículos al carrito
    usuario.compra(articulo1, 2);
    usuario.compra(articulo2, 1);
    
    // Crear pedido y asociaciones
    Usuario_Pedido usuario_pedido;
    Pedido_Articulo pedido_articulo;
    
    // Crear pedidos con diferentes números para comprobar orden
    // Este será el pedido #1
    Pedido pedido1(usuario.compra(), usuario, Fecha(10, 3, 2017), &tarjeta);
    // Añadir asociaciones
    usuario_pedido.asocia(usuario, pedido1);
    pedido_articulo.pedir(pedido1, articulo1, 35.20, 2);
    pedido_articulo.pedir(pedido1, articulo2, 29.95, 1);
    
    // Limpiar carrito y crear otro pedido
    usuario.compra(articulo1, 1);
    usuario.compra(articulo2, 2);
    // Este será el pedido #2
    Pedido pedido2(usuario.compra(), usuario, Fecha(20, 4, 2017), &tarjeta);
    // Añadir asociaciones
    usuario_pedido.asocia(usuario, pedido2);
    pedido_articulo.pedir(pedido2, articulo1, 35.20, 1);
    pedido_articulo.pedir(pedido2, articulo2, 29.95, 2);
    
    // === Pruebas del formato de salida ===
    cout << "\n=== PRUEBAS DE FORMATO DE SALIDA ===\n" << endl;
    
    // 1. Probar ItemsPedido - operador << para el detalle de un pedido
    cout << "DETALLE DEL PEDIDO #" << pedido1.numero() << endl;
    cout << "===============================" << endl;
    cout << pedido_articulo.detalle(pedido1) << endl;
    
    // 2. Probar Pedidos - operador << para las ventas de un artículo
    cout << "VENTAS DEL ARTÍCULO [" << articulo1.referencia() << "] \"" 
         << articulo1.titulo() << "\"" << endl;
    cout << "===============================" << endl;
    cout << pedido_articulo.ventas(articulo1) << endl;
    
    // 3. Verificar orden de los pedidos con la función auxiliar
    cout << "VERIFICACIÓN DEL ORDEN EN LAS VENTAS:" << endl;
    cout << "===============================" << endl;
    mostrar_operador_insercion(cout, pedido_articulo.ventas(articulo1));
    
    // 4. Probar mostrarVentasArticulos
    cout << "\nPRUEBA DE mostrarVentasArticulos():" << endl;
    cout << "===============================" << endl;
    pedido_articulo.mostrarVentasArticulos(cout);
    
    // 5. Probar mostrarDetallePedidos
    cout << "\nPRUEBA DE mostrarDetallePedidos():" << endl;
    cout << "===============================" << endl;
    pedido_articulo.mostrarDetallePedidos(cout);
    
    return 0;
}