#ifndef MINING_MODELS_H
#define MINING_MODELS_H

#include <string>
#include <vector>

using namespace std;

struct Equipo {
    int id;
    string nombre;
    string tipo;      // Ejemplo: "Excavadora", "Camión"
    int capacidad;    // Capacidad o potencia, según corresponda
    bool disponible;
};

struct RecursoHumano {
    int id;
    string nombre;
    string rol;       // Ejemplo: "Operador", "Supervisor"
    bool disponible;
};

struct Tarea {
    int id;
    string descripcion;
    int duracionHoras;
    vector<int> equiposNecesarios;
    vector<int> recursosHumanosNecesarios;
    bool completada;
};

#endif // MINING_MODELS_H