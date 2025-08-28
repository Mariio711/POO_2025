#ifndef CADENA_H_
#define CADENA_H_

#include <cstring>
#include <iostream>
#include <iterator>
#include <string>

class Cadena
{
public:
    // constructores
    explicit Cadena(size_t n = 0, char a = ' '); // predeterminado
    Cadena(const char *cadena);                  // de conversion
    Cadena(const Cadena &otra);                  // de copia

    // constructor de movimiento
    Cadena(Cadena &&otra) noexcept;

    // operador de aignación
    Cadena &operator=(const Cadena &otra);
    Cadena &operator=(const char *cadena);

    // operador de asignacion por movimiento
    Cadena &operator=(Cadena &&otra) noexcept;

    // destructor
    ~Cadena();

    // metodos observadores
    size_t length() const { return std::strlen(s_); }; // devuelve la longitud de la cadena c

    // operadores de comparación
    friend bool operator==(const Cadena &a, const Cadena &b);
    friend bool operator<(const Cadena &a, const Cadena &b);
    friend bool operator>(const Cadena &a, const Cadena &b);
    friend bool operator<=(const Cadena &a, const Cadena &b);
    friend bool operator>=(const Cadena &a, const Cadena &b);
    friend bool operator!=(const Cadena &a, const Cadena &b);

    // operadores aritmeticos
    Cadena &operator+=(const Cadena &b);                       // concatenación
    friend Cadena operator+(const Cadena &a, const Cadena &b); // concatenaciôn sin

    // operador de indice
    char &operator[](size_t i);
    const char &operator[](size_t i) const;

    // conversion a cadena de bajo nivel
    explicit operator const char *() const; // deja de ser necesario por el operador de inserción

    // operadores de insercion y extracción
    friend std::ostream &operator<<(std::ostream &os, const Cadena &c);
    friend std::istream &operator>>(std::istream &is, Cadena &c);

    //-----------ITERADORES----------

    // Tipos de iteradores
    typedef char *iterator;
    typedef const char *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    // Funciones de iteradores directos
    iterator begin() { return s_; }
    iterator end() { return s_ + tam_; }
    const_iterator begin() const { return s_; }
    const_iterator end() const { return s_ + tam_; }
    const_iterator cbegin() const { return s_; }
    const_iterator cend() const { return s_ + tam_; }

    // Funciones de iteradores inversos
    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(begin()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
    const_reverse_iterator crbegin() const { return const_reverse_iterator(end()); }
    const_reverse_iterator crend() const { return const_reverse_iterator(begin()); }

    // metodos
    char &at(size_t i);
    const char &at(size_t i) const;
    Cadena substr(unsigned int i, unsigned int tam) const;

private:
    static char vacia[1];
    size_t tam_;
    char *s_;
};

// Para P2 y ss.
// Especialización de la plantilla std ::hash<Key> para definir la función hash
// a usar con contenedores asociativos desordenados con claves de tipo Cadena,
// unordered_[set|map|multiset|multimap].
namespace std
{               // Estaremos dentro del espacio de nombres std.
    template <> // Es una especialización de una plantilla para Cadena.
    struct hash<Cadena>
    {                                              // Es una clase con solo un operador público.
        size_t operator()(const Cadena &cad) const // El operador función.
        {
            hash<string> hs;             // Creamos un objeto hash de string.
            auto p{(const char *)(cad)}; // Convertimos cad a cadena de bajo nivel.
            string s{p};                 // Creamos un string desde la cadena de b. nivel .
            size_t res{hs(s)};           // El hash del string . Como hs.operator()(s);
            return res;                  // Devolvemos el hash del string.
            // En forma abreviada:
            // return hash<string>{}((const char*)(cad));
        }
    };
}

#endif