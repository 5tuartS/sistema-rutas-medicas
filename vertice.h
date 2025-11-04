#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Arista;

class Vertice {
  string id;
  string nombre;
  string tipo;
  string direccion;
  vector<string> especialidades;
  string horario;

  Vertice* sig;
  Arista* ari;

  friend class Grafo;

public:
  Vertice(string _id, string _nombre, string _tipo, string _direccion);
};

Vertice::Vertice(string _id, string _nombre, string _tipo, string _direccion) {
  id = _id;
  nombre = _nombre;
  tipo = _tipo;
  direccion = _direccion;
  sig = NULL;
  ari = NULL;
}
