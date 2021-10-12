#include <iostream>
#include <string>
#include"Estructuras/Stack/Stack.hpp"
#include"Estructuras/Queue/Queue.hpp"
#include"1.3/Registro.hpp"

using std::string;
using std::vector;

#pragma once
class ConexionesComputadora{
    protected:
        string ip;
        string nombre;
        Stack<Registro> * conexiones_entrantes;
        Queue<Registro> * conexiones_salientes;

    public:
        /* Constructores */
        ConexionesComputadora(){}
        ConexionesComputadora(string ip) : ip(ip) {}
        ConexionesComputadora(string ip, VectorRegistros &registros);

        /* Destructor */
        ~ConexionesComputadora();

        /* Getters, Setters */
        string getIP(){ return ip; }
        string getNombre(){ return nombre; }
        Stack<Registro> * getConexionesEntrantes(){ return conexiones_entrantes; }
        Queue<Registro> * getConexionesSalientes(){ return conexiones_salientes; }

        void setConexionesEntrantes(VectorRegistros &registros);
        void setConexionesEntrantes(Stack<Registro> * conexiones_entrantes);
        void setConexionesSalientes(VectorRegistros &registros);
        void setConexionesSalientes(Queue<Registro> * conexiones_salientes);

        /* Metodos */
        /* Agrega una conexion entrante a la lista. */
        void push_conexion_entrante(Registro conexion);

        /* Agrega una conexion saliente a la lista. */
        void push_conexion_saliente(Registro conexion);

        /* Regresa la ultima conexion saliente.*/
        Registro ultimaConexionSaliente();

        /* Regresa la ultima conexion entrante */
        Node<Registro> * ultimaConexionEntrante();

        /* Obtener numero de conexiones */
        int numeroConexionesEntrantes();
        /* Obtener numero de conexiones */
        int numeroConexionesSalientes();

        /* Regresa verdadero si la direccion de red de un nodo es interna */
        bool isInterna(Node<Registro> * last);

        /* Regresa verdadero si hay tres conexiones seguidas a un sitio WEB */
        bool tresSeguidos();

        /* Imprime todos lo registros que se hicieron hacia un sitio WEB */
        void printPuertosWEB();
};

/* Destructor */
ConexionesComputadora::~ConexionesComputadora(){
    /* El destructor llama a los destructores de el queue y el stack para liberar la memoria */
    delete conexiones_entrantes;
    delete conexiones_salientes;
}

/* Constructor que recibe el vector para construir todo el objeto */
ConexionesComputadora::ConexionesComputadora(string ip, VectorRegistros &registros){
    /* Inicializa la ip y el nombre que tiene esta ip */
    this->ip                   = registros.desifrarRedInterna() + "." + ip;
    this->nombre               = registros.buscarNombreConIP(this->ip);

    /* Se crean y se inicializn las listas de conexiones con el vector de registros dado. */
    this->conexiones_entrantes = new Stack<Registro>();
    this->conexiones_salientes = new Queue<Registro>();
    this->setConexionesEntrantes(registros);
    this->setConexionesSalientes(registros);
}

/* Establece toda la lista de conexiones entrantes. 
   Complejidad O(n)
*/
void ConexionesComputadora::setConexionesEntrantes(VectorRegistros &registros){
    /* Recorremos el vector de registros */
    for (int i = 0; i < registros.getSize(); i++){
        /* Comparamos si la ip se encuentra en las IP destino. */
        if (registros[i].getIpDestino() == this->ip){
            /* LLamamos al metodo para añadir el registro. */
            this->push_conexion_entrante(registros[i]);
        }   
    }
}

/* Establece toda la lista de conexiones entrantes */
void ConexionesComputadora::setConexionesEntrantes(Stack<Registro> * conexiones_entrantes){
    this->conexiones_entrantes = conexiones_entrantes;
}

/* Establece toda la lista de conexiones salientes. 
   Complejidad O(n) 
*/
void ConexionesComputadora::setConexionesSalientes(VectorRegistros &registros){
    /* Recorremos el vector de registros */
    for (int i = 0; i < registros.getSize(); i++){
        /* Comparamos si la ip se encuentra en las IP destino. */
        if (registros[i].getIpOrigen() == this->ip){
            /* Llamamos al metodo para añadir el registro. */
            this->push_conexion_saliente(registros[i]);
        }   
    }
}

/* Establece toda la lista de conexiones salientes */
void ConexionesComputadora::setConexionesSalientes(Queue<Registro> * conexiones_salientes){
    this->conexiones_salientes = conexiones_salientes;
}

/* Agrega una conexion entrante a la lista. */
void ConexionesComputadora::push_conexion_entrante(Registro conexion){
    this->conexiones_entrantes->push(conexion);
}

/* Agrega una conexion saliente a la lista. */
void ConexionesComputadora::push_conexion_saliente(Registro conexion){
    this->conexiones_salientes->enqueue(conexion);
}

/* Regresa la utima conexion saliente. */
Registro ConexionesComputadora::ultimaConexionSaliente(){
    return this->conexiones_salientes->last()->getInfo();
}

Node<Registro> * ConexionesComputadora::ultimaConexionEntrante(){
    Node<Registro> * last = this->conexiones_entrantes->top();
    return last;
}

/* Regresa el numero de conexiones entrantes que se realizaron. */
int ConexionesComputadora::numeroConexionesEntrantes(){
    return this->conexiones_entrantes->size();
}

/* Regresa el numero de conexiones salientes que se realizaron. */
int ConexionesComputadora::numeroConexionesSalientes(){
    return this->conexiones_salientes->size();
}

/* Regresa verdadero si hay tres conexiones seguidas a un sitio WEB */
bool ConexionesComputadora::tresSeguidos(){
    string actual_destino_par, actual_destino_non;
    int contador = 0;
    bool encontrado = false;

    /* Creamos un nodo temporal */
    Node<Registro> * registro_tmp;

    /* Hacemos dequeue a toda la lista de los nodos */
    for (int i = 0; i < this->conexiones_salientes->size(); i++){
        /* Nodo actual */
        registro_tmp = this->conexiones_salientes->dequeue();

        /* Comparamos si los puertos tienen protocolo http o https */
        if( registro_tmp->getInfo().getPuertoDestino() == "80" ||
            registro_tmp->getInfo().getPuertoDestino() == "443"  ){    
                
            /* Guardamos un par y un non para comparar de tres en tres */
            if( i%2 == 0)
                actual_destino_par = registro_tmp->getInfo().getIpDestino();   
            else 
                actual_destino_non = registro_tmp->getInfo().getIpDestino();
                   
            /* Comparamos si los registros son iguales */
            if( actual_destino_non == actual_destino_par && i != 0)
                contador++;
            else   
                contador = 0;

            /* Si el contador llega a tres es por que ha sido encontrado */
            if ( contador == 3)
                encontrado = true;
        }

        /* Volvemos a meter el nodo en la lista */
        this->conexiones_salientes->enqueue(registro_tmp);
    }
    
    return encontrado;
}

/* Regresa verdadero si la direccion de red de un nodo es interna */
bool ConexionesComputadora::isInterna(Node<Registro> * last){
    
    string lastIp = last->getInfo().getIpOrigen();

    if( lastIp.substr(0,2) ==  "10" || 
        lastIp.substr(0,3) ==  "172" || 
        lastIp.substr(0,3) ==  "192"){

        return true;
    }
    else{
        
        return false;
    }
}

/* Imprime todos lo registros que se hicieron hacia un sitio WEB */
void ConexionesComputadora::printPuertosWEB(){
    /* Nodo temporal */
    Node<Registro> * registro_tmp;

    /* Hacemos deque a los nodos */
    for (int i = 0; i < this->numeroConexionesSalientes(); i++){

        /* Guardamos el nodo en la varible declarada */
        registro_tmp = this->conexiones_salientes->dequeue();

        /* Comparamos si el puerto destino es http o https */
        if (registro_tmp->getInfo().getPuertoDestino() == "80" ||
            registro_tmp->getInfo().getPuertoDestino() == "443"){
            /* Imprimimos la informacion */
            std::cout << registro_tmp->getInfo();
        }
        
        /* Volvemos a insertar el nodo en las conexiones salientes */
        this->conexiones_salientes->enqueue(registro_tmp); 
    }
}