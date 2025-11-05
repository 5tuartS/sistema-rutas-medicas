#include <iostream>
#include "grafo.h"

using namespace std;

void cargarDatosPrueba(Grafo &sistema) {
  cout << "\n=== Cargando datos de prueba ===" << endl;

  sistema.InsertaVertice("HOS001", "Hospital Nacional Rebagliati", "hospital",
                        "Av. Rebagliati 490, Jesús María, Lima",
                        {"Cardiología", "Neurología", "Oncología", "Pediatría"},
                        "24 horas");

  sistema.InsertaVertice("HOS002", "Hospital Edgardo Rebagliati Martins", "hospital",
                        "Av. Edgardo Rebagliati 490, Jesús María, Lima",
                        {"Emergencias", "Cirugía", "Medicina Interna"},
                        "24 horas");

  sistema.InsertaVertice("CLI001", "Clínica San Pablo", "clínica",
                        "Av. El Polo 789, Surco, Lima",
                        {"Traumatología", "Oftalmología", "Dermatología"},
                        "Lun-Dom 7:00-22:00");

  sistema.InsertaVertice("LAB001", "Laboratorio ROE", "laboratorio",
                        "Av. Benavides 1555, Miraflores, Lima",
                        {"Análisis clínicos", "Imagenología"},
                        "Lun-Sab 6:00-20:00");

  sistema.InsertaVertice("CON001", "Consultorio Dr. Pérez", "consultorio",
                        "Jr. Las Flores 234, San Isidro, Lima",
                        {"Medicina General"},
                        "Lun-Vie 9:00-18:00");

  sistema.InsertaVertice("HOS003", "Hospital Dos de Mayo", "hospital",
                        "Av. Miguel Grau cuadra 13, Cercado de Lima",
                        {"Emergencias", "Pediatría", "Ginecología"},
                        "24 horas");

  sistema.InsertaArista("HOS001", "HOS002", 15, "vehicular", true);
  sistema.InsertaArista("HOS001", "CLI001", 25, "ambulancia", true);
  sistema.InsertaArista("HOS001", "LAB001", 20, "vehicular", true);
  sistema.InsertaArista("HOS002", "CON001", 18, "vehicular", true);
  sistema.InsertaArista("HOS002", "HOS003", 30, "ambulancia", true);
  sistema.InsertaArista("CLI001", "LAB001", 10, "vehicular", true);
  sistema.InsertaArista("CLI001", "CON001", 12, "peatonal", true);
  sistema.InsertaArista("LAB001", "CON001", 8, "peatonal", true);
  sistema.InsertaArista("CON001", "HOS003", 35, "vehicular", true);
  sistema.InsertaArista("HOS003", "LAB001", 40, "ambulancia", true);

  cout << "\nDatos de prueba cargados: 6 centros médicos y 10 rutas" << endl;
}

int main()
{
  Grafo sistema;
  cargarDatosPrueba(sistema);

  cout << "\n=== Mostrando Lista de Adyacencia ===" << endl;
  sistema.MostrarListaAdyacencia();

  cout << "\n=== Mostrar Centros Conectados a 'HOS001' ===" << endl;
  sistema.MostrarCentrosConectados("HOS001");

  cout << "\n=== Verificar si existe una ruta entre 'HOS001' y 'HOS003' ===" << endl;
  if (sistema.ExisteRuta("HOS001", "HOS003"))
    cout << "✅ Sí existe una ruta entre HOS001 y HOS003." << endl;
  else
    cout << "❌ No existe ruta entre HOS001 y HOS003." << endl;

  cout << "\n=== Eliminando un Centro Médico (HOS002) ===" << endl;
  sistema.EliminarVertice("HOS002");

  cout << "\n=== Lista de Adyacencia Actualizada ===" << endl;
  sistema.MostrarListaAdyacencia();

  cout << "\n=== Eliminando una Ruta (CLI001 -> CON001) ===" << endl;
  sistema.EliminarArista("CLI001", "CON001");

  cout << "\n=== Lista de Adyacencia Final ===" << endl;
  sistema.MostrarListaAdyacencia();

  cout << "\n=== Verificar Ruta entre 'CLI001' y 'HOS003' ===" << endl;
  if (sistema.ExisteRuta("CLI001", "HOS003"))
    cout << "✅ Sí existe una ruta entre CLI001 y HOS003." << endl;
  else
    cout << "❌ No existe ruta entre CLI001 y HOS003." << endl;

  return 0;
}