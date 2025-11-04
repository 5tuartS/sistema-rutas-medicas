//#pragma once
#include "vertice.h"
#include "arista.h"
//#include <queue>
//#include <list>
//#include <stack>
//#include <map>
//#include <unordered_set>

using namespace std;

class Grafo
{
  Vertice* primero;
  int tamano;

public:
  Grafo();
  bool EstaVacio(); // Retorna true si el grafo está vacío
  int ObtenerTamano(); // Retorna el número de vertices en el grafo
  Vertice* ObtenerVertice(string nombre); // Retornar el vertice que tenga el nombre especificado
  void InsertaVertice(string nombre); // Inserta un vertice al grafo
  void InsertaArista(string ori, string dest, int peso); // Inserta arista entre los dos vertices especificados con el peso especificado
  void MostrarListaAdyacencia(); // Mostrar todos los vertices con sus aristas y pesos
  void EliminarVertice(string nombre); // Elimina el vertice con el nombre especificado
  void EliminarArista(string ori, string dest); // Elimina la arista entre los dos vertices especificados
  void EliminarTodo(); // Elimina todos los vertices y aristas del grafo
  void EliminarAristas(Vertice* vertice); // Elimina las aristas del vertice especificado
  void EliminarAristasDestino(string dest); // Elimina las aristas que tienen como destino el vertice especificado
  void RecorridoAnchura(string origen); // Recorre el grafo con el algoritmo de anchura
  void RecorridoProfundidad(string origen); // Recorre el grafo con el algoritmo de profundidad
  void PrimeroEnAnchura(string origen, string destino); // Despliega la ruta entre los dos vertices especificados con el algoritmo de primero en anchura
  void PrimeroEnProfundidad(string origen, string destino); // Despliega la ruta entre los dos vertices especificados con el algoritmo de primero en profundidad
  void PrimeroElMejor(string origen, string destino); // Despliega la ruta entre los dos vertices especificados con el algoritmo de primero el mejor
  //void MostrarRutaEncontrada(stack<pair<Vertice*, Vertice*>> pilaPar, Vertice* vdest); // Despliega la ruta encontrada
  //void Dijkstra(string origen); // Despliega la ruta más corta entre el origen y los demás vertices
  //void Kruskal(); // Genera el arbol recubridor minimo con el algoritmo de kruskal
  //void Prim(string origen);// Genera el arbol recubridor minimo con el algoritmo de Prim
};

Grafo::Grafo()
{
  primero = NULL;
  tamano = 0;
}

bool Grafo::EstaVacio()
{
  return tamano == 0;
}

int Grafo::ObtenerTamano()
{
  return tamano;
}

Vertice* Grafo::ObtenerVertice(string nombre)
{
  Vertice* i = primero;

  while (i != NULL)
  {
    if (i->nombre == nombre)
      return i;

    i = i->sig;
  }

  return NULL;
}

void Grafo::InsertaVertice(string nombre)
{
  if (ObtenerVertice(nombre) == NULL)
  {
    Vertice* nuevo = new Vertice(nombre);

    if (EstaVacio())
      primero = nuevo;
    else
    {
      Vertice *i = primero;

      while (i->sig != NULL)
        i = i->sig;

      i->sig = nuevo;
    }

    tamano++;
  }
  else
    cout << "Ese vertice ya existe en el grafo" << endl;
}

void Grafo::InsertaArista(string ori, string dest, int peso)
{
  Vertice* vori = ObtenerVertice(ori);
  Vertice* vdest = ObtenerVertice(dest);

  if (vori == NULL)
    cout << "El vertice origen no existe" << endl;

  if (vdest == NULL)
    cout << "El vertice destino no existe" << endl;

  if (vori != NULL && vdest != NULL)
  {
    Arista* nueva = new Arista(vdest, peso);

    if (vori->ari == NULL)
      vori->ari = nueva;
    else
    {
      Arista* j = vori->ari;

      while (j->sig != NULL)
        j = j->sig;

      j->sig = nueva;
    }
  }
}


void Grafo::MostrarListaAdyacencia()
{
  Vertice* i = primero;

  while (i != NULL)
  {
    Arista* j = i->ari;
    cout << i->nombre << " = ";

    while (j != NULL)
    {
      cout << i->nombre << "->" << j->peso << "->" << j->dest->nombre << ",";
      j = j->sig;
    }

    cout << endl;
    i = i->sig;
  }
}

void Grafo::EliminarAristas(Vertice* vertice)
{
  if (vertice == NULL)
    return;

  Arista* i = vertice->ari;

  while (vertice->ari != NULL)
  {
    i = vertice->ari;
    vertice->ari = vertice->ari->sig;
    cout << "Arista " << vertice->nombre << "->" << i->dest->nombre << " eliminada" << endl;
    delete(i);
  }
}

void Grafo::EliminarAristasDestino(string dest)
{
  Vertice* i = primero;

  while (i != NULL)
  {
    if (i->nombre == dest || i->ari == NULL)
    {
      i = i->sig;
      continue;
    }

    if (i->ari->dest->nombre == dest)
    {
      Arista* j = i->ari;
      i->ari = i->ari->sig;
      cout << "Arista " << i->nombre << "->" << dest << " eliminada" << endl;
      delete(j);
    }
    else
    {
      Arista* x = i->ari;
      Arista* y = x->sig;

      while (y != NULL)
      {
        if (y->dest->nombre == dest)
        {
          x->sig = y->sig;
          cout << "Arista " << i->nombre << "->" << dest << " eliminada" << endl;
          delete(y);
        }

        x = x->sig;
        if(x==NULL)
          y=NULL;
        else
          y=x->sig;
      }
    }

    i = i->sig;
  }
}

void Grafo::EliminarVertice(string nombre)
{
  if (primero->nombre == nombre)
  {
    Vertice* i = primero;
    primero = primero->sig;
    EliminarAristas(i);
    EliminarAristasDestino(i->nombre);
    cout << "Vertice " << nombre << " fue eliminado" << endl;
    delete(i);
    tamano--;
  }
  else
  {
    Vertice* i = primero;
    Vertice* j = i->sig;
    bool existe = false;

    while (j != NULL)
    {
      if (j->nombre == nombre)
      {
        i->sig = j->sig;
        EliminarAristas(j);
        EliminarAristasDestino(j->nombre);
        cout << "Vertice " << nombre << " fue eliminado" << endl;
        delete(j);
        tamano--;
        existe = true;
        break;
      }

      i = j;
      j = j->sig;
    }

    if (!existe)
      cout << "El vertice especificado no existe" << endl;
  }
}

void Grafo::EliminarArista(string ori, string dest)
{
  Vertice* vori = ObtenerVertice(ori);
  Vertice* vdest = ObtenerVertice(dest);

  if (vori == NULL)
    cout << "El vertice origen no existe" << endl;

  if (vdest == NULL)
    cout << "El vertice destino no existe" << endl;

  if (vori != NULL && vdest != NULL)
  {
    if (vori->ari->dest == vdest)
    {
      Arista* i = vori->ari;
      vori->ari = vori->ari->sig;
      cout << "Arista " << ori << "->" << dest << " eliminada" << endl;
      delete(i);
    }
    else
    {
      Arista* i = vori->ari;
      Arista* j = i->sig;

      while (j != NULL)
      {
        if (j->dest == vdest)
        {
          i->sig = j->sig;
          cout << "Arista " << ori << "->" << dest << " eliminada" << endl;
          delete(j);
          break;
        }

        i = j;
        j = j->sig;
      }
    }
  }
}

void Grafo::EliminarTodo()
{
  Vertice* i = primero;

  while (primero != NULL)
  {
    i = primero;
    primero = primero->sig;
    EliminarAristas(i);
    EliminarAristasDestino(i->nombre);
    cout << "Vertice " << i->nombre << " eliminado" << endl;
    delete(i);
    tamano--;
  }
}

