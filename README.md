# Sistema de Rutas Médicas en Perú

Sistema de gestión de rutas entre centros médicos implementado con estructuras de grafos en C++ utilizando listas enlazadas.

## Descripción del Proyecto

Este sistema permite a una clínica en Perú visualizar y gestionar las rutas médicas entre diferentes centros de atención (consultorios, hospitales, laboratorios, etc). Cada centro está conectado con otros mediante rutas que representan distancias.

## ⚙︎ Adaptaciones del Código Original

### 1. **Modificaciones en la Clase Arista**

**Código Original:**
class Arista {
int weight;
Arista *next;
Vertice *dest;
};

**Código Adaptado:**
class Arista {
int distancia; // Tiempo en minutos entre centros
string tipoRuta; // vehicular, peatonal, ambulancia
bool activa; // Estado de la ruta (activa/inactiva)
Arista *sig;
Vertice *dest;
};

**Justificación:** Se agregaron atributos específicos para el contexto médico: `tipoRuta` permite clasificar las rutas según el medio de transporte, y `activa` permite gestionar el estado operativo de cada ruta.

### 2. **Modificaciones en la Clase Vertice**

**Código Original:**
class Vertice {
std::string name;
float capital;
Vertice *next;
Arista *ari;
};

**Código Adaptado:**
class Vertice {
string id; // ID único del centro
string nombre; // Nombre del centro médico
string tipo; // consultorio, hospital, laboratorio
string direccion; // Dirección del centro
vectorstd::string especialidades; // Especialidades médicas
string horario; // Horario de atención
Vertice *sig;
Arista *ari;
};

**Justificación:** Se eliminó el atributo genérico `capital` y se agregaron campos específicos del dominio médico: `id` (identificador único), `tipo` (clasificación del centro), `direccion`, `especialidades` y `horario` de atención.

### 3. **Modificaciones en la Clase Grafo**

**Funciones Agregadas:**
- `MostrarCentrosConectados(string id)`: Visualiza todos los centros médicos directamente conectados a uno específico.
- `ExisteRuta(string origin, string dest)`: Verifica si existe una ruta (directa o indirecta) entre dos centros usando BFS.

**Funciones Modificadas:**
- `InsertaVertice()`: Ahora acepta múltiples parámetros para crear un centro médico completo.
- `InsertaArista()`: Incluye parámetros adicionales para tipo de ruta y estado.
- `MostrarListaAdyacencia()`: Formateada para mostrar información médica relevante.

**Justificación:** Las nuevas funciones satisfacen los requisitos específicos de la actividad: visualizar conexiones, buscar rutas, y gestionar información médica contextualizada.

### 4. **Funciones repartidas entre los Integrantes**

## Visualizar los centros conectados a uno específico. = Yhamir Laura
## Buscar si existe una ruta entre dos centros. = Johao Avila
## Agregar y eliminar rutas entre centros (aristas). = Lennin Medrano
## Agregar y eliminar centros médicos (vertices). = Bruno Herrera

## 📊 Análisis de Complejidad Computacional (Big-O)

### 1. Inserción de Vértice
**Complejidad: O(n)**

**Análisis:**
- Búsqueda de duplicados: O(n) - debe recorrer la lista de vértices
- Llegada al final para inserción: O(n) - recorre todos los vértices
- Creación del nuevo nodo: O(1)

**Desglose:**
T(n) = T_buscar(n) + T_insertar(n)
T(n) = O(n) + O(n) = O(n)

En el peor caso, si tenemos n centros médicos, debemos recorrer toda la lista para verificar que el ID no exista y luego recorrer nuevamente para insertar al final.

### 2. Eliminación de Nodo
**Complejidad: O(n × m)**

**Análisis:**
- Búsqueda del nodo: O(n)
- Eliminación de aristas salientes: O(m) donde m = número de aristas del nodo
- Eliminación de aristas entrantes: O(n × m) - revisar todos los vértices y sus aristas

**Desglose:**
T(n,m) = T_buscar(n) + T_aristas_salientes(m) + T_aristas_entrantes(n × m)
T(n,m) = O(n) + O(m) + O(n × m) = O(n × m)

El término dominante es O(n × m) porque debemos revisar cada vértice (n) y cada una de sus aristas (m) para eliminar referencias al nodo eliminado.

### 3. Inserción de Arista
**Complejidad: O(n + m)**

**Análisis:**
- Búsqueda del vértice origen: O(n)
- Búsqueda del vértice destino: O(n)
- Recorrido de aristas hasta el final: O(m)
- Inserción de la nueva arista: O(1)

**Desglose:**
T(n,m) = T_buscar_origen(n) + T_buscar_destino(n) + T_recorrer_aristas(m)
T(n,m) = O(n) + O(n) + O(m) = O(n + m)

Donde n es el número de centros médicos y m es el número de aristas del centro origen.

### 4. Eliminación de Arista
**Complejidad: O(n + m)**

**Análisis:**
- Búsqueda del vértice origen: O(n)
- Búsqueda del vértice destino: O(n)
- Búsqueda de la arista específica: O(m)
- Eliminación: O(1)

**Desglose:**
T(n,m) = T_buscar_origen(n) + T_buscar_destino(n) + T_buscar_arista(m)
T(n,m) = O(n) + O(n) + O(m) = O(n + m)

Similar a la inserción, el costo está dominado por la búsqueda de vértices y el recorrido de aristas.