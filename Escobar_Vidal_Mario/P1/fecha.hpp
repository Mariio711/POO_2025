#ifndef FECHA_H_
#define FECHA_H_

#include <ctime>
#include <iostream>

class Fecha{
    public:
        //constantes año max y año min
        static const int AnnoMinimo = 1902, AnnoMaximo = 2037;

        //Metodos observadores
        int dia() const {return dia_;};
        int mes() const {return mes_;};
        int anno() const {return anno_;};

        //Constructores
        explicit Fecha(int d = 0, int m = 0, int a = 0); //con tres parámetros
        Fecha(const char * f);

        //sobrecarga de operadores de comparación 
        friend bool operator== (const Fecha& a, const Fecha& b);
        friend bool operator< (const Fecha& a, const Fecha& b);
        friend bool operator> (const Fecha& a, const Fecha& b);
        friend bool operator<= (const Fecha& a, const Fecha& b);
        friend bool operator>= (const Fecha& a, const Fecha& b);
        friend bool operator!= (const Fecha& a, const Fecha& b);

        //sobrecarga de operadores aritmeticos
        Fecha& operator+=(int n);
        Fecha& operator-=(int n);
        Fecha operator+(int n) const;
        Fecha operator-(int n) const;

        //sobrecraga operadores de incremento
        Fecha operator++(int);   //sufijo
        Fecha& operator++();        //prefijo
        Fecha operator--(int);   //sufijo
        Fecha& operator--();        //prefijo

        //conversión a const char*
        operator const char*() const;

        //clase fecha::invalida
        class Invalida{
            public:
                Invalida(const char* error): error_(error) {}
                const char* por_que() const {return error_;}
            private:
            const char* error_;
        };

    private:
        int dia_, mes_, anno_;
        mutable char crep[40] {};
        bool valida() const;
        mutable bool actual = false;
        
};

#endif