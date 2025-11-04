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

  cout << endl << "MostrandoListaAdyacencia" << endl;
  grafo->MostrarListaAdyacencia();

  //grafo->EliminarArista("B", "A");
  grafo->EliminarVertice("B");

  cout << endl << "MostrandoListaAdyacencia" << endl;
  grafo->MostrarListaAdyacencia();

  // 🔍 Buscar si existe una ruta entre dos centros
  cout << endl << "¿Existe ruta entre A y D?" << endl;
  if (grafo->ExisteRuta("A", "D"))
    cout << "✅ Sí existe una ruta entre A y D." << endl;
  else
    cout << "❌ No existe ruta entre A y D." << endl;

  return 0;
}

