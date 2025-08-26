#include<unistd.h>
#include "usuario.hpp"


/*---------------CLASE CLAVE---------------*/
const char Clave::caracteres_validos[] = {"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./"};

Clave::Clave(const char* cad)
{
    if (strlen(cad) < 5)
    {
        throw Incorrecta(CORTA);
    }
}