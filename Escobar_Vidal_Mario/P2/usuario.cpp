#include "usuario.hpp"

/*---------------CLASE CLAVE---------------*/
const char Clave::caracteres_validos[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};

const Cadena cifrar(const char *cad)
{
    static std ::random_device rd;                                     // Para obtener una semilla aleatoria para el GNA.
    static std ::mt19937 gna{rd()};                                    // Usamos un buen GNA, el de Matsumoto y Nishimura, por ejemplo, inicializado con el valor rd().
    static const std::size_t n{sizeof(Clave::caracteres_validos) - 1}; // n = 64
    std ::uniform_int_distribution<std::size_t> uniforme(0, n - 1);    // Genera números pseudoaleatorios equiprobables en el intervalo [0, 63].
    const char sal[3] = {Clave::caracteres_validos[uniforme(gna)],
                         Clave::caracteres_validos[uniforme(gna)], '\0'}; // 2 aleatorios de caracteres_validos y el terminador.

    char *encrypt;
    if (!(encrypt = crypt(cad, sal)))
    {
        throw Clave::Incorrecta(Clave::ERROR_CRYPT);
    }

    return encrypt;
}

Clave::Clave(const char *cad)
{
    if (strlen(cad) < 5)
    {
        throw Incorrecta(CORTA);
    }

    clave_ = cifrar(cad);
}

Cadena Clave::clave() const
{
    return clave_;
}

bool Clave::verifica(const char *cad) const
{
    const char *clave = crypt(cad, (const char*)clave_);

    return clave && clave_ == clave;
}

/*---------------CLASE USUARIO---------------*/
std::unordered_set<Cadena> Usuario::ids; // Conjunto de identificadores


// constructor
Usuario::Usuario(Cadena id, Cadena nombre, Cadena apell, Cadena direc, Clave clave)
    : id_(id), nombre_(nombre), apellidos_(apell), dir_(direc), clave_(clave)
{

    typedef std::unordered_set<Cadena>::iterator tipoIt;
    std::pair<tipoIt, bool> res = ids.insert(id); // Insertar el identificador id
    if (!res.second)                              // Inserción fallida
    {
        throw Usuario::Id_duplicado(id_);
    }
}

// asocia una tarjeta al usuario
void Usuario::es_titular_de(Tarjeta &tarj)
{
    tarjetas_.insert(std::make_pair(tarj.numero(), &tarj));
}

// desliga una tarjeta del usuario
void Usuario::no_es_titular_de(Tarjeta &tarj)
{
    tarjetas_.erase(tarj.numero());
}

// asociacion con clase articulo (añadir articulo al carrito)

void Usuario::compra(Articulo &art, unsigned int cantidad)
{
    // primero debemos comprobar si el articulo ya está en el carrito (ya asociado)
    auto it = articulos_.find(&art);
    if (it == articulos_.end()) // si no está
    {
        if (cantidad > 0)
        {
            articulos_.insert(std::make_pair(&art, cantidad));
        }
    }
    else // si ya esta en el carrito
    {
        if (cantidad == 0) // se borra
        {
            articulos_.erase(&art);
        }
        else // se actualiza la cantidad
        {
            it->second = cantidad;
        }
    }
}

// elimina todos los articulos en el carrito
void Usuario::vaciar_carro()
{
    articulos_.clear();
}

// devuelve la cantidad de articulos diferentes en el carrito
size_t Usuario::n_articulos() const
{
    return articulos_.size();
}

std::ostream &operator<<(std::ostream &os, const Usuario &usr)
{
    if (os)
    {
        os << usr.id() << " [" << usr.clave_.clave() << "] " << usr.nombre() << " " << usr.apellidos() << std::endl;
        os << usr.direccion() << std::endl;
        os << "Tarjetas:" << std::endl;
        if (!usr.tarjetas().empty())
        {
            for (auto it : usr.tarjetas())
            {
                os << *it.second << std::endl;
            }
        }
    }
    return os;
}

std::ostream& mostrar_carro(std::ostream& os, const Usuario& user)
{
    if(os)
    {
        os << "Carrito de compra de " << user.id() << "[Articulos: " << user.n_articulos() << "]" << std::endl;
        os << " Cant. Artículo" << std::endl;
        os << "===========================================================" << std::endl;

        for(auto it : user.compra())
        {
            os << it.second << it.first << std::endl;
        }
    }

    return os;
}

Usuario::~Usuario()
{
    for(auto& it: tarjetas_)
    {
        it.second->anula_titular();
    }
    ids.erase(id_);
}