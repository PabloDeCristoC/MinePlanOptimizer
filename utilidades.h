#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
using namespace std;

// Funciones basicas del sistema
void limpiarPantalla();
void pausar();

// Funciones para leer datos desde teclado
int leerEntero(const char* mensaje);
void leerTexto(const char* mensaje, char* destino, int tamaño);
char leerSiNo(const char* mensaje);

// Implementaciones
void limpiarPantalla() {
    system("clear");  // En Windows cambiar por "cls"
}

void pausar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore();
    cin.get();
}

int leerEntero(const char* mensaje) {
    int valor;
    cout << mensaje;
    cin >> valor;
    cin.ignore();
    return valor;
}

void leerTexto(const char* mensaje, char* destino, int tamaño) {
    cout << mensaje;
    cin.getline(destino, tamaño);
}

char leerSiNo(const char* mensaje) {
    char respuesta;
    cout << mensaje << " (s/n): ";
    cin >> respuesta;
    cin.ignore();
    return respuesta;
}

#endif