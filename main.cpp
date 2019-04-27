#include <iostream>
#include <cstdlib> 
#include <cctype>

#include "arbolbinarioordenadoenlazado.hpp"
#include "operadornodo.hpp"
#include "persona.hpp"
#include "macros.hpp"
#include "generarpersona.hpp"

using namespace ed;

void Mostrar(ArbolBinarioOrdenadoEnlazado<Persona> a);
void Buscar(ArbolBinarioOrdenadoEnlazado<Persona> a);
void Borrar(ArbolBinarioOrdenadoEnlazado<Persona> a);

int main(){
	srand(time(0));
	ArbolBinarioOrdenadoEnlazado<Persona> a;
	int np;
	int opt;

	std::cout << BGREEN;
  	std::cout<<"Introduzca el número de personas que quiere generar: ";
  	std::cout << RESET;
  	std::cin>>np;

  	for(int i= 0; i < np ; i++){
  		a.insertar(generarDatosPersonales());
  	}
  	std::cout << BIBLUE;
  	std::cout<<np<<" personas introducidas correctamente en el ábol"<<endl;
  	std::cout << RESET;

  	do{

  	system("clear");


  	std::cout << BGREEN;
  	std::cout<<"-----Introduzca una opción-----"<<std::endl;
  	std::cout << RESET;

  	std::cout << BYELLOW;
  	std::cout<<"	1. Buscar en el árbol"<<std::endl;
  	std::cout<<"	2. Mostrar Árbol"<<std::endl;
  	std::cout<<"	3. Borrar datos de un nodo"<<std::endl;
  	std::cout<<"	4. Borar árbol"<<std::endl;
  	std::cout<<"	0. Salir"<<std::endl;
  	std::cout << RESET;
  	std::cin>> opt;

  	switch (opt)
      {
        case 1:
          Buscar(a);
          std::cin.ignore();
          break;
        case 2:
          Mostrar(a);
          std::cin.ignore();
          break;
        case 3:
          Borrar(a);
          std::cin.ignore();
          break;
        case 4:
          a.borrarArbol();
          std::cout << BIBLUE;
  		  std::cout<<"Arbol borrado correctamente"<<endl;
  		  std::cout << RESET;
          std::cin.ignore();
          break;
      }

  }while(opt != 0);

return 0;
  	
}


void Mostrar(ArbolBinarioOrdenadoEnlazado<Persona> a){

	if(a.estaVacio()){
		std::cout << BYELLOW;
  		std::cout<<"El árbol esta vacío"<<std::endl;
  		std::cout << RESET;
  		std::cin.ignore();
  		return ;
	}

	system("clear");
	int opt;
	EscribirNodo<Persona> op;

	std::cout << BGREEN;
  	std::cout<<"-----Introduzca una opción de visualización -----"<<std::endl;
  	std::cout << RESET;

  	std::cout << BYELLOW;
  	std::cout<<"	1. Recorrido preOrden"<<std::endl;
  	std::cout<<"	2. Recorrido postOrden"<<std::endl;
  	std::cout<<"	3. Recorrido inOrden"<<std::endl;
  	std::cout << RESET;
  	cin>>opt;

  	system("clear");
  	switch (opt)
      {
        case 1:
            a.recorridoPreOrden(op);
            break;
        case 2:
            a.recorridoPostOrden(op);
            break;
        case 3:
        	a.recorridoInOrden(op);
            break;
        default:
        	std::cout << BRED;
  	  		std::cout<<"Opción no válida"<<std::endl;
  	  		std::cout << RESET;

      }
    std::cout << BGREEN;
  	std::cout<<"Pulse ENTER para continuar"<<std::endl;
  	std::cout << RESET;
    std::cin.ignore();
}
void Buscar(ArbolBinarioOrdenadoEnlazado<Persona> a){
	system("clear");
	Persona p;
	std::cout << BGREEN;
  	std::cout<<"-----Introduzca la persona que quiere buscar-----"<<std::endl;
  	std::cout << RESET;
  	cin>>p;

  	if(a.buscar(p)){
  		std::cout << BIBLUE;
  		std::cout<<"Encontrado"<<endl;
  		std::cout << RESET;
  	}
  	else{
  		std::cout << BRED;
  		std::cout<<"No encontrado"<<endl;
  		std::cout << RESET;
  	}
  	std::cin.ignore();
}

void Borrar(ArbolBinarioOrdenadoEnlazado<Persona> a){
	system("clear");
	Persona p;
	std::cout << BGREEN;
  	std::cout<<"-----Introduzca la persona que quiere buscar-----"<<std::endl;
  	std::cout << RESET;
  	cin>>p;

  	if(a.buscar(p)){
  		std::cout << BIBLUE;
  		std::cout<<"Encontrado, se procedera a borrar el elemento "<<endl;
  		std::cout << RESET;
  		a.borrar();
  		std::cout << BIBLUE;
  		std::cout<<"Elemento borado"<<endl;
  		std::cout << RESET;
  	}
  	else{
  		std::cout << BRED;
  		std::cout<<"No encontrado"<<endl;
  		std::cout << RESET;
  	}
  	std::cin.ignore();
}
