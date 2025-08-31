#include "tarjeta.hpp"


/*---------------CLASE NUMERO---------------*/

// constructor
Numero::Numero(const Cadena num)
{
    Cadena num_limpio = num;
    auto end_it = std::remove_if(num_limpio.begin(), num_limpio.end(), EsBlanco());

    // Si encuentra algún caracter que no sea dígito entre aux.begin() y end_it
    if (std::find_if(num_limpio.begin(), end_it, std::not_fn(EsDigito())) != end_it)
    {
        throw Numero::Incorrecto(DIGITOS);
    }


    if (num_limpio.length() < 13 || num_limpio.length() > 19)
    {
        throw Numero::Incorrecto(LONGITUD);
    }

    if (!luhn(num_limpio))
    {
        throw Numero::Incorrecto(NO_VALIDO);
    }

    numero_ = num_limpio;
}

// operador de conversion a const char*
Numero::operator const char *() const
{
    return numero_.operator const char *();
}

// operador menor-que
bool operator<(const Numero &a, const Numero &b)
{
    return a.numero_ < b.numero_;
}

/*---------------CLASE TARJETA---------------*/
std::set<Numero> Tarjeta::nums; // Conjunto de numeros de tarjetas almacenados

Tarjeta::Tarjeta(const Numero &num, Usuario &tit, const Fecha &f) : numero_(num), titular_(&tit), f_caducidad_(f), activa_(true)
{
    Fecha f_actual;
    if (f < f_actual)
    {
        throw Tarjeta::Caducada(f);
    }

    typedef std::set<Numero>::iterator tipoIt;
    std::pair<tipoIt, bool> res = nums.insert(num); // Insertar el identificador id
    if (!res.second)                                // Inserción fallida
    {
        throw Tarjeta::Num_duplicado(num);
    }
    else
    {
        tit.es_titular_de(*this); // asociar tarjeta con el titular (usuario)
    }
}

Tarjeta::Tipo Tarjeta::tipo() const
{
    const Cadena &num = (const char *)numero_;
    // Verificar los primeros dígitos
    if (num[0] == '3')
    {
        if (num[1] == '4' || num[1] == '7')
            return Tipo::AmericanExpress;
        else
            return Tipo::JCB;
    }
    else if (num[0] == '4')
        return Tipo::VISA;
    else if (num[0] == '5')
        return Tipo::Mastercard;
    else if (num[0] == '6')
        return Tipo::Maestro;
    else
        return Tipo::Otro;
}

bool Tarjeta::activa(const bool nuevo)
{
    this->activa_ = nuevo;
    return this->activa_;
}

void Tarjeta::anula_titular()
{
    // Solo procede si hay un titular
    if (titular_)
    {
        // El usuario dejará de tener esta tarjeta
        const_cast<Usuario *>(titular_)->no_es_titular_de(*this);
        // Elimina la referencia al usuario y desactiva la tarjeta
        const_cast<Usuario *&>(titular_) = nullptr;
        activa_ = false;
    }
}

Tarjeta::~Tarjeta()
{
    // 1. Si todavía hay un titular, desasociar la tarjeta
    if (titular_)
    {
        const_cast<Usuario *>(titular_)->no_es_titular_de(*this);
        const_cast<Usuario *&>(titular_) = nullptr;
    }

    // 2. Eliminar el número de la tarjeta del conjunto de números
    nums.erase(numero_);
}

bool operator<(const Tarjeta &tarj1, const Tarjeta &tarj2)
{
    return tarj1.numero() < tarj2.numero();
}

std::ostream &operator<<(std::ostream &os, const Tarjeta::Tipo &tipo)
{
    if (os)
    {
        if (tipo == Tarjeta::Tipo::AmericanExpress)
        {
            os << "American Express" << std::endl;
        }
        else if (tipo == Tarjeta::Tipo::JCB)
        {
            os << "JCB" << std::endl;
        }
        else if (tipo == Tarjeta::Tipo::Maestro)
        {
            os << "Maestro" << std::endl;
        }
        else if (tipo == Tarjeta::Tipo::Mastercard)
        {
            os << "Mastercard" << std::endl;
        }
        else if (tipo == Tarjeta::Tipo::VISA)
        {
            os << "VISA" << std::endl;
        }
        else // Tarjeta::Tipo::Otro
        {
            os << "Tipo indeterminado" << std::endl;
        }
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, const Tarjeta &tarj)
{
    if (os)
    {

        os << tarj.tipo() << tarj.numero() << std::endl;
        Cadena aux = tarj.titular()->nombre() + " " + tarj.titular()->apellidos();
        for (Cadena::iterator it = aux.begin(); it != aux.end(); it++)
        {
            *it = toupper(*it);
        }

        os << aux << std::endl;
        os << "Caduca:  " << std::setfill('0') << std::setw(2) << tarj.caducidad().mes() << "/" << tarj.caducidad().anno() % 100 << std::endl;
    }
    return os;
}