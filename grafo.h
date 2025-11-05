#pragma once
#include "vertice.h"
#include "arista.h"
#include <queue>
#include <unordered_set> // Se agregó para usar BFS en ExisteRuta

using namespace std;

class Grafo {
  Vertice* primero;
  int tamano;

public:
  Grafo();
  bool EstaVacio();
  int ObtenerTamano();
  Vertice* ObtenerVertice(string id);
  void InsertaVertice(string id, string nombre, string tipo, string direccion,
                      vector<string> especialidades = {}, string horario = "");
  void InsertaArista(string ori, string dest, int distancia, string tipoRuta, bool activo);
  void MostrarListaAdyacencia();
  void MostrarCentrosConectados(string id);
  void EliminarVertice(string id);
  void EliminarArista(string ori, string dest);
  void EliminarTodo();
  void EliminarAristas(Vertice* vertice);
  void EliminarAristasDestino(string dest);
  bool ExisteRuta(string origen, string destino); // Nueva función agregada
};

Grafo::Grafo() {
  primero = NULL;
  tamano = 0;
}

bool Grafo::EstaVacio() {
  return tamano == 0;
}

int Grafo::ObtenerTamano() {
  return tamano;
}

// Buscar centro médico por ID = Complejidad O(n)
Vertice* Grafo::ObtenerVertice(string id) {
  Vertice* i = primero;
  while (i != NULL) {
    if (i->id == id) return i;
    i = i->sig;
  }
  return NULL;
}

// Insertar nuevo centro médico = Complejidad O(n)
void Grafo::InsertaVertice(string id, string nombre, string tipo, string direccion, 
                           vector<string> especialidades, string horario) {
  if (ObtenerVertice(id) == NULL) {
    Vertice* nuevo = new Vertice(id, nombre, tipo, direccion, especialidades, horario);

    if (EstaVacio()) {
      primero = nuevo;
    } else {
      Vertice* i = primero;
      while (i->sig != NULL) {
        i = i->sig;
      } 
      i->sig = nuevo;
    }
    tamano++;
    cout << "Centro médico '" << nombre << "' agregado exitosamente." << endl;
  } else {
    cout << "Error: Ya existe un centro médico con el ID '" << id << "'." << endl;
  }
}

// Insertar ruta entre centros = Complejidad O(n + m)
void Grafo::InsertaArista(string ori, string dest, int distancia, string tipoRuta, bool activo) {
  Vertice* vori = ObtenerVertice(ori);
  Vertice* vdest = ObtenerVertice(dest);

  if (vori == NULL) {
    cout << "Error: El centro origen '" << ori << "' no existe." << endl;
    return;
  }

  if (vdest == NULL) {
    cout << "Error: El centro destino '" << dest << "' no existe." << endl;
    return;
  }

  Arista *j = vori->ari;
  while (j != NULL) {
    if (j->dest == vdest) {
      cout << "Ya existe una ruta entre '" << vori->nombre << "' y '" << vdest->nombre << "'." << endl;
      return;
    }
    j = j->sig;
  }

  Arista *nueva = new Arista(vdest, distancia, tipoRuta, activo);

  if (vori->ari == NULL) {
    vori->ari = nueva;
  } else {
    Arista *j = vori->ari;
    while (j->sig != NULL) {
      j = j->sig;
    }
    j->sig = nueva;
  }
}

// Mostrar lista de adyacencia
void Grafo::MostrarListaAdyacencia() {
  if (EstaVacio()) {
    cout << "No hay centros médicos registrados." << endl;
    return;
  }

  Vertice* i = primero;
  while (i != NULL) {
    Arista *j = i->ari;
    cout << "\n" << i->nombre << " [" << i->id << "] (" << i->tipo << "):" << endl;

    if (j == NULL) {
      cout << "  Sin conexiones" << endl;
    } else {
      while (j != NULL) {
        cout << "  -> " << j->dest->nombre << " [" << j->dest->id << "]"
             << " | " << j->distancia << " min"
             << " | " << j->tipoRuta
             << " | " << (j->activa ? "Activa" : "Inactiva") << endl;
        j = j->sig;
      }
    }
    i = i->sig;
  }
}

// Mostrar centros conectados a uno específico
void Grafo::MostrarCentrosConectados(string id) {
  Vertice *centro = ObtenerVertice(id);

  if (centro == NULL) {
    cout << "Error: El centro '" << id << "' no existe." << endl;
    return;
  }

  Arista *j = centro->ari;

  if (j == NULL) {
    cout << "No hay centros conectados directamente." << endl;
  } else {
    int count = 1;
    while (j != NULL) {
      cout << count++ << ". " << j->dest->nombre
           << " (" << j->dest->tipo << ")"
           << " - " << j->distancia << " min"
           << " - Ruta " << j->tipoRuta << endl;
      j = j->sig;
    }
  }
}

// Eliminar todas las aristas de un vértice = Complejidad O(m)
void Grafo::EliminarAristas(Vertice* vertice) {
  if (vertice == NULL) return;
  
  Arista* i = vertice->ari;
  while (vertice->ari != NULL) {
    i = vertice->ari;
    vertice->ari = vertice->ari->sig;
    cout << "Arista " << vertice->id << "->" << i->dest->id << " eliminada" << endl;
    delete(i);
  }
}

// Eliminar aristas que apuntan a un destino = Complejidad O(n * m)
void Grafo::EliminarAristasDestino(string dest) {
  Vertice* i = primero;

  while (i != NULL) {
    if (i->id == dest || i->ari == NULL) {
      i = i->sig;
      continue;
    }

    if (i->ari->dest->id == dest) {
      Arista* j = i->ari;
      i->ari = i->ari->sig;
      cout << "Arista " << i->id << "->" << dest << " eliminada" << endl;
      delete(j);
    } else {
      Arista* x = i->ari;
      Arista* y = x->sig;

      while (y != NULL) {
        if (y->dest->id == dest) {
          x->sig = y->sig;
          cout << "Arista " << i->id << "->" << dest << " eliminada" << endl;
          delete(y);
        }

        x = x->sig;
        if (x == NULL) {
          y = NULL;
        } else {
          y = x->sig;
        }
      }
    }
    i = i->sig;
  }
}

// Eliminar centro médico = Complejidad O(n * m)
void Grafo::EliminarVertice(string id) {
  if (EstaVacio()) {
    cout << "El grafo está vacío." << endl;
    return;
  }

  if (primero->id == id){
    Vertice* i = primero;
    primero = primero->sig;
    EliminarAristas(i);
    EliminarAristasDestino(i->id);
    cout << "Vertice " << i->id << " fue eliminado" << endl;
    delete(i);
    tamano--;
  } else {
    Vertice* i = primero;
    Vertice* j = i->sig;
    bool existe = false;

    while (j != NULL) {
      if (j->id == id) {
        i->sig = j->sig;
        EliminarAristas(j);
        EliminarAristasDestino(j->id);
        cout << "Vertice " << j->id << " fue eliminado" << endl;
        delete(j);
        tamano--;
        existe = true;
        break;
      }
      i = j;
      j = j->sig;
    }

    if (!existe) cout << "El vertice especificado no existe" << endl;
  }
}

// Eliminar ruta específica = Complejidad O(n + m)
void Grafo::EliminarArista(string ori, string dest) {
  Vertice* vori = ObtenerVertice(ori);
  Vertice* vdest = ObtenerVertice(dest);

  if (vori == NULL) {
    cout << "Error: El centro origen no existe." << endl;
    return;
  }

  if (vdest == NULL) {
    cout << "Error: El centro destino no existe." << endl;
    return;
  }

  if (vori->ari == NULL) {
    cout << "No existe ruta entre estos centros." << endl;
    return;
  }

  if (vori->ari->dest == vdest) {
    Arista *i = vori->ari;
    vori->ari = vori->ari->sig;
    cout << "Arista " << ori << "->" << dest << " eliminada" << endl;
    delete (i);
  } else {
    Arista *i = vori->ari;
    Arista *j = i->sig;

    while (j != NULL) {
      if (j->dest == vdest) {
        i->sig = j->sig;
        cout << "Arista " << ori << "->" << dest << " eliminada" << endl;
        delete (j);
        break;
      }
      i = j;
      j = j->sig;
    }
  }
}

void Grafo::EliminarTodo() {
  Vertice* i = primero;

  while (primero != NULL) {
    i = primero;
    primero = primero->sig;
    EliminarAristas(i);
    EliminarAristasDestino(i->id);
    cout << "Vertice " << i->id << " eliminado" << endl;
    delete(i);
    tamano--;
  }
}

// Verificar si existe ruta entre dos centros usando BFS = Complejidad O(V + E)
bool Grafo::ExisteRuta(string origen, string destino) {
  Vertice* vori = ObtenerVertice(origen);
  Vertice* vdest = ObtenerVertice(destino);

  if (vori == NULL || vdest == NULL) {
    cout << "Error: Uno o ambos centros no existen." << endl;
    return false;
  }

  if (vori == vdest) {
    cout << "El origen y destino son el mismo centro." << endl;
    return true;
  }

  queue<Vertice*> cola;
  unordered_set<string> visitados;

  cola.push(vori);
  visitados.insert(vori->id);

  while (!cola.empty()) {
    Vertice* actual = cola.front();
    cola.pop();

    Arista* arista = actual->ari;
    while (arista != NULL) {
      if (arista->dest == vdest) {
        cout << "\nExiste una ruta desde '" << vori->nombre << "' hasta '" << vdest->nombre << "'." << endl;
        return true;
      }

      string vecino = arista->dest->id;
      if (visitados.find(vecino) == visitados.end()) {
        cola.push(arista->dest);
        visitados.insert(vecino);
      }
      arista = arista->sig;
    }
  }

  return false;
}
