#pragma once
#include <iostream>
using namespace std;

class Vertice;

class Arista {
  int distancia;
  string tipoRuta;
  bool activa;

  Arista* sig;
  Vertice* dest;

  friend class Grafo;

public:
  Arista(Vertice *_dest, int _distancia, string _tipoRuta, bool _activa);
};

Arista::Arista(Vertice* _dest, int _distancia, string _tipoRuta, bool _activa) {
  dest = _dest;
  distancia = _distancia;
  tipoRuta = _tipoRuta;
  activa = _activa;
  sig = NULL;
}

