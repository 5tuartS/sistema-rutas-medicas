#include <iostream>
#include "grafo.h"

using namespace std;

int main() {

  Grafo *grafo = new Grafo();
  //int opc = 0;

  grafo->InsertaVertice("A");
  grafo->InsertaVertice("B");
  grafo->InsertaVertice("C");
  grafo->InsertaVertice("D");

  grafo->InsertaArista("A", "B", 7);
  grafo->InsertaArista("B", "A", 5);
  grafo->InsertaArista("A", "D", 9);
  grafo->InsertaArista("D", "A", 8);
  grafo->InsertaArista("C", "A", 7);
  grafo->InsertaArista("A", "C", 6);
  grafo->InsertaArista("B", "D", 8);
  grafo->InsertaArista("D", "B", 9);

  cout<<endl<<"MostrandoListaAdyacencia"<<endl;
  grafo->MostrarListaAdyacencia();

  //grafo->EliminarArista("B", "A");
  grafo->EliminarVertice("B");

  cout<<endl<<"MostrandoListaAdyacencia"<<endl;
  grafo->MostrarListaAdyacencia();

  return 0;
}
