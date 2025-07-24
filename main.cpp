#include <iostream>
#include <cstring>
#include "estructuras.h"
#include "utilidades.h"
#include "equipos.h"
#include "recursos.h"

using namespace std;

Equipo equipos[MAX_EQUIPOS];
RecursoHumano recursos[MAX_RECURSOS];
Tarea tareas[MAX_TAREAS];

int totalEquipos = 0;
int totalRecursos = 0;
int totalTareas = 0;

void cargarDatosEjemplo() {
    totalEquipos = 0;
    totalRecursos = 0;
    totalTareas = 0;
    
    strcpy(equipos[0].nombre, "Excavadora CAT 320");
    strcpy(equipos[0].tipo, "Excavadora");
    equipos[0].id = 1;
    equipos[0].capacidad = 100;
    equipos[0].disponible = true;
    
    strcpy(equipos[1].nombre, "Camion Volvo");
    strcpy(equipos[1].tipo, "Camion");
    equipos[1].id = 2;
    equipos[1].capacidad = 40;
    equipos[1].disponible = true;
    
    totalEquipos = 2;
    
    strcpy(recursos[0].nombre, "Juan Perez");
    strcpy(recursos[0].rol, "Operador");
    recursos[0].id = 1;
    recursos[0].disponible = true;
    
    strcpy(recursos[1].nombre, "Maria Gonzalez");
    strcpy(recursos[1].rol, "Supervisor");
    recursos[1].id = 2;
    recursos[1].disponible = true;
    
    totalRecursos = 2;
    
    cout << "Datos de ejemplo cargados!" << endl;
    pausar();
}

void mostrarEstadisticas() {
    limpiarPantalla();
    cout << "=== ESTADISTICAS GENERALES ===" << endl;
    
    int equiposDisponibles = 0;
    for (int i = 0; i < totalEquipos; i++) {
        if (equipos[i].disponible) {
            equiposDisponibles++;
        }
    }
    
    int recursosDisponibles = 0;
    for (int i = 0; i < totalRecursos; i++) {
        if (recursos[i].disponible) {
            recursosDisponibles++;
        }
    }
    
    cout << "EQUIPOS:" << endl;
    cout << "  Total: " << totalEquipos << endl;
    cout << "  Disponibles: " << equiposDisponibles << endl;
    cout << "  No disponibles: " << (totalEquipos - equiposDisponibles) << endl;
    
    cout << "\nRECURSOS HUMANOS:" << endl;
    cout << "  Total: " << totalRecursos << endl;
    cout << "  Disponibles: " << recursosDisponibles << endl;
    cout << "  No disponibles: " << (totalRecursos - recursosDisponibles) << endl;
    
    pausar();
}

int main() {
    int opcion;
    
    cout << "=== BIENVENIDO A MINE PLAN OPTIMIZER ===" << endl;
    cout << "Sistema de Gestion Minera / Desarrollado por: Pablo Emanuel De Cristo Cavieres Körn" << endl;
    pausar();
    
    do {
        limpiarPantalla();
        cout << "=== MENU PRINCIPAL ===" << endl;
        cout << "1. Gestion de Equipos" << endl;
        cout << "2. Gestion de Recursos Humanos" << endl;
        cout << "3. Ver Estadisticas" << endl;
        cout << "4. Cargar Datos de Ejemplo" << endl;
        cout << "0. Salir" << endl;
        cout << "=====================" << endl;
        
        opcion = leerEntero("Selecciona una opcion: ");
        
        switch (opcion) {
            case 1: menuEquipos(); break;
            case 2: menuRecursos(); break;
            case 3: mostrarEstadisticas(); break;
            case 4: cargarDatosEjemplo(); break;
            case 0: 
                cout <<"\nGracias por usar Mine Plan Optimizer!"<< endl;
                cout <<"\nDesarrollado por: Pablo Emanuel De Cristo Cavieres Körn"<< endl;
                break;
            default: 
                cout << "Opcion invalida." << endl;
                pausar();
        }
    } while (opcion != 0);
    
    return 0;
}