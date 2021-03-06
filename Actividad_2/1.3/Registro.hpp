#pragma once
#include"Fecha.hpp"
#include<iostream>
using std::string;

class Registro{
    protected:
        Fecha fecha;
        string hora, 
               ip_origen, puerto_origen, nombre_origen,
               ip_destino, puerto_destino, nombre_destino;  

    public:
        //Constructor
        Registro(){}
        Registro(Fecha fecha, string hora, 
                 string ip_origen, string puerto_origen, string nombre_origen,
                 string ip_destino, string puerto_destino, string nombre_destino) :
                 fecha(fecha), hora(hora), ip_origen(ip_origen), puerto_origen(puerto_origen),
                 nombre_origen(nombre_origen), ip_destino(ip_destino), puerto_destino(puerto_destino),
                 nombre_destino(nombre_destino){}

        /*Pasar los datos de la fecha y el objeto lo crea el constructor*/
        Registro(int dia, int mes, int año, string hora, 
                 string ip_origen, string puerto_origen, string nombre_origen,
                 string ip_destino, string puerto_destino, string nombre_destino) :
                 fecha(Fecha(dia,mes,año)), hora(hora), ip_origen(ip_origen), puerto_origen(puerto_origen),
                 nombre_origen(nombre_origen), ip_destino(ip_destino), puerto_destino(puerto_destino),
                 nombre_destino(nombre_destino){}
        
        //Getters
        Fecha getFecha()          { return fecha; }
        string getNombreOrigen()  { return nombre_origen; }
        string getNombreDestino() { return nombre_destino; }
        string getPuertoDestino() { return puerto_destino; }
        string getIpOrigen()      { return ip_origen; }
        string getIpDestino()      { return ip_destino; }

        //Metodos
        /* Comparados registros con la fecha */
        static bool comparaFecha_asc(Registro, Registro);
        static bool comparaFecha_desc(Registro, Registro);

        //Sobrecarga de operadores
        friend std::ostream & operator<<(std::ostream & os, const Registro & registro);
        bool operator==(const Registro & r1);
        bool operator!=(const Registro & r1);

};


bool Registro::comparaFecha_asc(Registro a, Registro b){
    return (a.fecha < b.fecha);
}

bool Registro::comparaFecha_desc(Registro a, Registro b){
    return (a.fecha > b.fecha);
}

std::ostream & operator<<(std::ostream & os, const Registro & registro){
    os << registro.fecha << " | ";
    os << registro.hora << " | ";
    os << registro.ip_origen << " | ";
    os << registro.puerto_origen << " | ";
    os << registro.nombre_origen << " | ";
    os << registro.ip_destino << " | ";
    os << registro.puerto_destino << " | ";
    os << registro.nombre_destino;
    os << std::endl;
    
    return os;
}

bool Registro::operator==(const Registro & r1) {
    bool igual = false;

    if( 
        this->fecha          ==  r1.fecha           &&
        this->hora           ==  r1.hora            &&
        this->ip_origen      ==  r1.ip_origen       &&
        this->puerto_origen  ==  r1.puerto_origen   &&
        this->nombre_origen  ==  r1.nombre_origen   &&
        this->ip_destino     ==  r1.ip_destino      &&
        this->puerto_destino ==  r1.puerto_destino  &&
        this->nombre_destino ==  r1.nombre_destino
    ){ 
        igual = true;
    }

    return igual;
}

bool Registro::operator!=(const Registro & r1) {
    bool not_igual = true;

    if( 
        this->fecha          ==  r1.fecha           &&
        this->hora           ==  r1.hora            &&
        this->ip_origen      ==  r1.ip_origen       &&
        this->puerto_origen  ==  r1.puerto_origen   &&
        this->nombre_origen  ==  r1.nombre_origen   &&
        this->ip_destino     ==  r1.ip_destino      &&
        this->puerto_destino ==  r1.puerto_destino  &&
        this->nombre_destino ==  r1.nombre_destino
    ){ 
        not_igual = false;
    }

    return not_igual;
    
}



