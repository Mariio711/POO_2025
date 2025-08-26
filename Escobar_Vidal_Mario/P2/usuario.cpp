#include "usuario.hpp"

/*---------------CLASE CLAVE---------------*/
const char Clave::caracteres_validos[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};

const Cadena &cifrar(const char *cad)
{
    static std ::random_device rd;                                     // Para obtener una semilla aleatoria para el GNA.
    static std ::mt19937 gna{rd()};                                    // Usamos un buen GNA, el de Matsumoto y Nishimura, por ejemplo, inicializado con el valor rd().
    static const std::size_t n{sizeof(Clave::caracteres_validos) - 1}; // n = 64
    std ::uniform_int_distribution<std::size_t> uniforme(0, n - 1);    // Genera números pseudoaleatorios equiprobables en el intervalo [0, 63].
    const char sal[3] = {Clave::caracteres_validos[uniforme(gna)],
                         Clave::caracteres_validos[uniforme(gna)], '\0'}; // 2 aleatorios de caracteres_validos y el terminador.

    char* encrypt;
    if(encrypt = crypt())
}

Clave::Clave(const char *cad)
{
    if (strlen(cad) < 5)
    {
        throw Incorrecta(CORTA);
    }
}