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
  Vertice(string _id, string _nombre, string _tipo, string _direccion,
          vector<string> _especialidades = {}, string _horario = "");
};

Vertice::Vertice(string _id, string _nombre, string _tipo, string _direccion, 
                 vector<string> _especialidades, string _horario) {
  id = _id;
  nombre = _nombre;
  tipo = _tipo;
  direccion = _direccion;
  especialidades = _especialidades;
  horario = _horario;
  sig = NULL;
  ari = NULL;
}
