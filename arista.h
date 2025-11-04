#pragma once
#include <iostream>

class Vertice;

class Arista
{
  int peso;
  Arista* sig;
  Vertice* dest;

  friend class Grafo;

public:
  Arista(Vertice* _dest, int peso);
};

Arista::Arista(Vertice* _dest, int _peso)
{
  dest = _dest;
  peso = _peso;
  sig = NULL;
}
