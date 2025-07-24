#ifndef EQUIPOS_H
#define EQUIPOS_H

#include "estructuras.h"
#include "utilidades.h"
#include <cstring>

extern Equipo equipos[MAX_EQUIPOS];
extern int totalEquipos;

void mostrarEquipo(int indice);
void listarEquipos();
void crearEquipo();
void eliminarEquipo();
void menuEquipos();

void mostrarEquipo(int indice) {
    cout << "ID: " << equipos[indice].id 
         << " | Nombre: " << equipos[indice].nombre 
         << " | Tipo: " << equipos[indice].tipo
         << " | Capacidad: " << equipos[indice].capacidad
         << " | Disponible: " << (equipos[indice].disponible ? "Si" : "No") 
         << endl;
}

void listarEquipos() {
    limpiarPantalla();
    cout << "=== LISTA DE EQUIPOS ===" << endl;
    
    if (totalEquipos == 0) {
        cout << "No hay equipos registrados." << endl;
    } else {
        for (int i = 0; i < totalEquipos; i++) {
            mostrarEquipo(i);
        }
    }
    cout << "\nTotal de equipos: " << totalEquipos << endl;
    pausar();
}

void crearEquipo() {
    if (totalEquipos >= MAX_EQUIPOS) {
        cout << "Error: Maximo de equipos alcanzado." << endl;
        pausar();
        return;
    }
    
    limpiarPantalla();
    cout << "=== CREAR EQUIPO ===" << endl;
    
    equipos[totalEquipos].id = totalEquipos + 1;
    
    leerTexto("Nombre del equipo: ", equipos[totalEquipos].nombre, MAX_NOMBRE);
    leerTexto("Tipo de equipo: ", equipos[totalEquipos].tipo, MAX_NOMBRE);
    equipos[totalEquipos].capacidad = leerEntero("Capacidad: ");
    
    char disponible = leerSiNo("Esta disponible?");
    equipos[totalEquipos].disponible = (disponible == 's' || disponible == 'S');
    
    totalEquipos++;
    
    cout << "Equipo creado exitosamente!" << endl;
    pausar();
}

void eliminarEquipo() {
    if (totalEquipos == 0) {
        cout << "No hay equipos para eliminar." << endl;
        pausar();
        return;
    }
    
    limpiarPantalla();
    cout << "=== ELIMINAR EQUIPO ===" << endl;
    
    cout << "Equipos disponibles:" << endl;
    for (int i = 0; i < totalEquipos; i++) {
        mostrarEquipo(i);
    }
    
    int id = leerEntero("Ingresa el ID del equipo a eliminar: ");
    
    int indice = -1;
    for (int i = 0; i < totalEquipos; i++) {
        if (equipos[i].id == id) {
            indice = i;
            break;
        }
    }
    
    if (indice != -1) {
        for (int i = indice; i < totalEquipos - 1; i++) {
            equipos[i] = equipos[i + 1];
        }
        totalEquipos--;
        cout << "Equipo eliminado exitosamente." << endl;
    } else {
        cout << "No se encontro un equipo con ID: " << id << endl;
    }
    pausar();
}

void menuEquipos() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "=== GESTION DE EQUIPOS ===" << endl;
        cout << "1. Listar equipos" << endl;
        cout << "2. Crear equipo" << endl;
        cout << "3. Eliminar equipo" << endl;
        cout << "0. Volver al menu principal" << endl;
        cout << "=========================" << endl;
        
        opcion = leerEntero("Selecciona una opcion: ");
        
        switch (opcion) {
            case 1: listarEquipos(); break;
            case 2: crearEquipo(); break;
            case 3: eliminarEquipo(); break;
            case 0: break;
            default: 
                cout << "Opcion invalida." << endl;
                pausar();
        }
    } while (opcion != 0);
}

#endif