#ifndef RECURSOS_H
#define RECURSOS_H

#include "estructuras.h"
#include "utilidades.h"
#include <cstring>


extern RecursoHumano recursos[MAX_RECURSOS];
extern int totalRecursos;


void mostrarRecurso(int indice);
void listarRecursos();
void crearRecurso();
void menuRecursos();


void mostrarRecurso(int indice) {
    cout << "ID: " << recursos[indice].id 
         << " | Nombre: " << recursos[indice].nombre 
         << " | Rol: " << recursos[indice].rol
         << " | Disponible: " << (recursos[indice].disponible ? "Sí" : "No") 
         << endl;
}

void listarRecursos() {
    limpiarPantalla();
    cout << "=== RECURSOS HUMANOS ===" << endl;
    
    if (totalRecursos == 0) {
        cout << "No hay recursos humanos registrados." << endl;
    } else {
        for (int i = 0; i < totalRecursos; i++) {
            mostrarRecurso(i);
        }
    }
    cout << "\nTotal de recursos: " << totalRecursos << endl;
    pausar();
}

void crearRecurso() {
    if (totalRecursos >= MAX_RECURSOS) {
        cout << "Error: Máximo de recursos alcanzado." << endl;
        pausar();
        return;
    }
    
    limpiarPantalla();
    cout << "=== CREAR RECURSO HUMANO ===" << endl;
    
    recursos[totalRecursos].id = totalRecursos + 1;
    
    leerTexto("Nombre del trabajador: ", recursos[totalRecursos].nombre, MAX_NOMBRE);
    leerTexto("Rol (Operador, Supervisor, etc.): ", recursos[totalRecursos].rol, MAX_NOMBRE);
    
    char disponible = leerSiNo("¿Está disponible?");
    recursos[totalRecursos].disponible = (disponible == 's' || disponible == 'S');
    
    totalRecursos++;
    
    cout << "✓ Recurso humano creado exitosamente!" << endl;
    pausar();
}

void menuRecursos() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "=== GESTIÓN DE RECURSOS HUMANOS ===" << endl;
        cout << "1. Listar recursos humanos" << endl;
        cout << "2. Crear recurso humano" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "==================================" << endl;
        
        opcion = leerEntero("Selecciona una opción: ");
        
        switch (opcion) {
            case 1: listarRecursos(); break;
            case 2: crearRecurso(); break;
            case 0: break;
            default: 
                cout << "Opción inválida." << endl;
                pausar();
        }
    } while (opcion != 0);
}

#endif