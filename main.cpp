#include <iostream>
#include <vector>
#include "mining_models.h"

using namespace std;

// Función para mostrar equipo
void mostrarEquipo(const Equipo& e) {
    cout << "ID: " << e.id 
         << " | Nombre: " << e.nombre 
         << " | Tipo: " << e.tipo
         << " | Capacidad: " << e.capacidad
         << " | Disponible: " << (e.disponible ? "Sí" : "No") 
         << endl;
}

// Función para mostrar recurso humano
void mostrarRecursoHumano(const RecursoHumano& r) {
    cout << "ID: " << r.id 
         << " | Nombre: " << r.nombre 
         << " | Rol: " << r.rol
         << " | Disponible: " << (r.disponible ? "Sí" : "No") 
         << endl;
}

// Función para mostrar tarea
void mostrarTarea(const Tarea& t) {
    cout << "ID: " << t.id 
         << " | Descripción: " << t.descripcion
         << " | Duración (hrs): " << t.duracionHoras
         << " | Completada: " << (t.completada ? "Sí" : "No") 
         << endl;
}

int main() {
    // Vectores para almacenar objetos
    vector<Equipo> equipos;
    vector<RecursoHumano> recursos;
    vector<Tarea> tareas;

    // Crear algunos ejemplos
    equipos.push_back({1, "Excavadora CAT 320", "Excavadora", 100, true});
    recursos.push_back({1, "Juan Perez", "Operador", true});
    tareas.push_back({1, "Cargar material en camión", 5, {1}, {1}, false});

    // Mostrar datos
    cout << "\n=== EQUIPOS ===" << endl;
    for (const auto& e : equipos) mostrarEquipo(e);

    cout << "\n=== RECURSOS HUMANOS ===" << endl;
    for (const auto& r : recursos) mostrarRecursoHumano(r);

    cout << "\n=== TAREAS ===" << endl;
    for (const auto& t : tareas) mostrarTarea(t);

    return 0;
}