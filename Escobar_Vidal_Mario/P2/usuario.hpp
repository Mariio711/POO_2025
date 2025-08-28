#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <unistd.h>
#include <random>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"
class Numero;
class Tarjeta;

class Clave
{
public:
    // enumeracion a nivel de la clase Clave (Clave::Razon)
    enum Razon
    {
        CORTA,
        ERROR_CRYPT
    };

    // clase Clave::Incorrecta
    class Incorrecta
    {
    public:
        Incorrecta(Razon r) : razon_(r) {}
        Razon razon() const { return razon_; }

    private:
        Razon razon_;
    };

    // constructor
    Clave(const char *cad);

    // metodo observador
    Cadena clave() const; // devuelve la contraseña cifrada (clave_)

    // metodo verificar
    bool verifica(const char *cad) const; // recibe la contraseña en claro y devuelve verdadero si corresponde con la contraseña

    friend const Cadena &cifrar(const char *cad);

private:
    Cadena clave_;                          // aloja la contraseña cifrada
    static const char caracteres_validos[]; // Conjunto de caracteres entre los que escoger la «sal» para encriptar las claves
};

class Usuario
{
public:
    typedef std::map<Numero, Tarjeta *> Tarjetas;
    typedef std::unordered_map<Articulo *, unsigned int> Articulos;

    // clase de error
    class Id_duplicado
    {
    public:
        Id_duplicado(Cadena idd) : idd_(idd) {}
        Cadena idd() const { return idd_; }

    private:
        Cadena idd_;
    };

    // constructor
    Usuario(Cadena id, Cadena nombre, Cadena apell, Cadena direc, Clave clave);

    // prohibir la copia
    Usuario(const Usuario &user) = delete;
    Usuario &operator=(const Usuario &user) = delete;

    //metodos observadores
    const Cadena id() const {return id_; };
    const Cadena nombre() const {return nombre_; };
    const Cadena apellidos() const {return apellidos_; };
    const Cadena direccion() const {return dir_; };
    const Tarjetas& tarjetas() const {return tarjetas_; };
    const Articulos& compra() const {return articulos_; };

    //asociacion con clase Tarjeta
    void es_titular_de (Tarjeta &t);
    void no_es_titular_de (Tarjeta &t);

    //asociacion con clase Articulo
    void compra(Articulo &art, unsigned int cantidad = 1);
    void vaciar_carro();
    size_t n_articulos() const;

    //sobrecarga de operador de insercion
    friend std::ostream &operator <<(std::ostream &os, const Usuario &usr);

    ~Usuario();
private:
    const Cadena id_, nombre_, apellidos_, dir_;
    Clave clave_;
    Tarjetas tarjetas_;
    Articulos articulos_;
    static std::unordered_set<Cadena> ids; // Conjunto de identificadores
};

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user);
#endif