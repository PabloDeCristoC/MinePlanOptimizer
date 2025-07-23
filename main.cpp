#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "mining_models.h"

using namespace std;

vector<Equipo> equipos;
vector<RecursoHumano> recursos;
vector<Tarea> tareas;

void limpiarPantalla(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pausar(){
    cout << "\nPresione Enter para continuar..";
    cin.ignore();
    cin.get();
}

int obtenerEntero(const string& mensaje){
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(); // Limpiar buffer
            return valor;
        } else {
            cout << "Error: Ingresa un número válido.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string obtenerString(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

void mostrarEquipo(const Equipo& e){
    cout << "ID: " << e.id 
         << " | Nombre: " << e.nombre 
         << " | Tipo: " << e.tipo
         << " | Capacidad: " << e.capacidad
         << " | Disponible: " << (e.disponible ? "Sí" : "No") 
         << endl;
}

bool obtenerBoolean(const string& mensaje) {
    char respuesta;
    while (true) {
        cout << mensaje << " (s/n): ";
        cin >> respuesta;
        cin.ignore();
        if (respuesta == 's' || respuesta == 'S') return true;
        if (respuesta == 'n' || respuesta == 'N') return false;
        cout << "Error: Ingresa 's' para sí o 'n' para no.\n";
    }
}


---------------------




void mostrarRecursoHumano(const RecursoHumano& r){
    cout << "ID: " << r.id 
         << " | Nombre: " << r.nombre 
         << " | Rol: " << r.rol
         << " | Disponible: " << (r.disponible ? "Sí" : "No") 
         << endl;
}


void mostrarTarea(const Tarea& t){
    cout << "ID: " << t.id 
         << " | Descripción: " << t.descripcion
         << " | Duración (hrs): " << t.duracionHoras
         << " | Completada: " << (t.completada ? "Sí" : "No") 
         << endl;
}

int main() {
    
    vector<Equipo> equipos;
    vector<RecursoHumano> recursos;
    vector<Tarea> tareas;

    
    equipos.push_back({1, "Excavadora CAT 320", "Excavadora", 100, true});
    recursos.push_back({1, "Juan Perez", "Operador", true});
    tareas.push_back({1, "Cargar material en camión", 5, {1}, {1}, false});

    
    cout << "\n=== EQUIPOS ===" << endl;
    for (const auto& e : equipos) mostrarEquipo(e);

    cout << "\n=== RECURSOS HUMANOS ===" << endl;
    for (const auto& r : recursos) mostrarRecursoHumano(r);

    cout << "\n=== TAREAS ===" << endl;
    for (const auto& t : tareas) mostrarTarea(t);

    return 0;
}