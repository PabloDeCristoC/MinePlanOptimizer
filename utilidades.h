#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iostream>
using namespace std;

void limpiarPantalla();
void pausar();

int leerEntero(const char* mensaje);
void leerTexto(const char* mensaje, char* destino, int tamano);
char leerSiNo(const char* mensaje);

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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

void leerTexto(const char* mensaje, char* destino, int tamano) {
    cout << mensaje;
    cin.getline(destino, tamano);
}

char leerSiNo(const char* mensaje) {
    char respuesta;
    cout << mensaje << " (s/n): ";
    cin >> respuesta;
    cin.ignore();
    return respuesta;
}

#endif