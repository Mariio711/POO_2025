#include "tarjeta.hpp"

/*---------------CLASE NUMERO---------------*/

// algoritmo de luhn
bool luhn(const Cadena &numero)
{
    size_t n = numero.length();
    size_t suma = 0;
    bool alt = false;
    for (int i = n - 1; i > -1; --i)
    {
        n = numero[size_t(i)] - '0';
        if (alt)
        {
            n *= 2;
            if (n > 9)
                n = (n % 10) + 1;
        }
        alt = !alt;
        suma += n;
    }
    return !(suma % 10);
}

// constructor
Numero::Numero(const Cadena num)
{
    Cadena num_limpio;
    size_t i = 0;
    for (auto it = num.begin(); it != num.end(); ++it)
    {
        if (!isspace(*it))
        {
            if (!isdigit(*it))
            {
                throw Numero::Incorrecta(DIGITOS);
            }
            else
            {
                num_limpio += Cadena(1, *it);
            }
        }
    }

    if (num_limpio.length() < 13 || num_limpio.length() > 19)
    {
        throw Numero::Incorrecta(LONGITUD);
    }

    if (!luhn(num_limpio))
    {
        throw Numero::Incorrecta(NO_VALIDO);
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
std::unordered_set<Numero> Tarjeta::nums; // Conjunto de numeros de tarjetas almacenados

Tarjeta::Tarjeta(const Numero &num, Usuario &tit, const Fecha &f) : numero_(num), titular_(&tit), f_caducidad_(f), activa_(true)
{
    Fecha f_actual;
    if (f < f_actual)
    {
        throw Tarjeta::Caducada(f);
    }

    typedef std::unordered_set<Numero>::iterator tipoIt;
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

const Tarjeta::Tipo Tarjeta::tipo() const
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
    const_cast<Usuario *&>(titular_) = nullptr;
    activa_ = false;
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
        switch (tipo)
        {
        case Tarjeta::Tipo::AmericanExpress:
            os << "American Express" << std::endl;
            return os;
            break;
        case Tarjeta::Tipo::JCB:
            os << "JCB" << std::endl;
            return os;
            break;
        case Tarjeta::Tipo::Maestro:
            os << "Maestro" << std::endl;
            return os;
            break;
        case Tarjeta::Tipo::Mastercard:
            os << "Mastercard" << std::endl;
            return os;
            break;
        case Tarjeta::Tipo::VISA:
            os << "VISA" << std::endl;
            return os;
            break;
        case Tarjeta::Tipo::Otro:
            os << "Tipo indeterminado" << std::endl;
            return os;
            break;
        }
    }
}

std::ostream &operator<<(std::ostream &os, Tarjeta &tarj)
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