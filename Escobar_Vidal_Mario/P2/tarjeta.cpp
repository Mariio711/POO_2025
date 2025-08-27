#include "tarjeta.hpp"

/*---------------CLASE NUMERO---------------*/

//algoritmo de luhn
bool luhn(const Cadena& numero)
{
  size_t n = numero.length();
  size_t suma = 0;
  bool alt = false;
  for (int i = n - 1; i > -1; --i) {
    n = numero[size_t(i)] - '0';
    if (alt) {
      n *= 2;
      if (n > 9)
	n = (n % 10) + 1;
    }
    alt = !alt;
    suma += n;
  }
  return !(suma % 10);
}

//constructor
Numero::Numero(const Cadena num)
{
    Cadena num_limpio;
    size_t i = 0;
    for(auto it = num.begin(); it != num.end(); ++it)
    {
        if(!isspace(*it))
        {
            if(!isdigit(*it))
            {
                throw Numero::Incorrecta(DIGITOS);
            }
            else
            {
                num_limpio += Cadena(1, *it);
            }
            
        }
    }

    if(num_limpio.length() < 13 || num_limpio.length() > 19)
    {
        throw Numero::Incorrecta(LONGITUD);
    }

    if(!luhn(num_limpio))
    {
        throw Numero::Incorrecta(NO_VALIDO);
    }

    numero_ = num_limpio;
}

//operador de conversion a const char*
Numero::operator const char *() const
{
    return numero_.operator const char *();
}

//operador menor-que
bool operator<(const Numero &a, const Numero &b)
{
    return a.numero_ < b.numero_;
}