#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <vector>
#include <string>
#include "mining_models.h"

using namespace std;

class FileManager{
public:
    // Funciones para CSV
    static bool guardarEquiposCSV(const vector<Equipo>& equipos, const string& filename = "equipos.csv");
    static bool cargarEquiposCSV(vector<Equipo>& equipos, const string& filename = "equipos.csv");
    
    static bool guardarRecursosCSV(const vector<RecursoHumano>& recursos, const string& filename = "recursos.csv");
    static bool cargarRecursosCSV(vector<RecursoHumano>& recursos, const string& filename = "recursos.csv");
    
    static bool guardarTareasCSV(const vector<Tarea>& tareas, const string& filename = "tareas.csv");
    static bool cargarTareasCSV(vector<Tarea>& tareas, const string& filename = "tareas.csv");

    // Funciones para JSON
    static bool guardarTodosJSON(const vector<Equipo>& equipos, 
                                const vector<RecursoHumano>& recursos, 
                                const vector<Tarea>& tareas, 
                                const string& filename = "mine_data.json");
    
    static bool cargarTodosJSON(vector<Equipo>& equipos, 
                               vector<RecursoHumano>& recursos, 
                               vector<Tarea>& tareas, 
                               const string& filename = "mine_data.json");