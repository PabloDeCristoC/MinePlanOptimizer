#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

// Limites maximos del sistema
#define MAX_EQUIPOS 100
#define MAX_RECURSOS 100
#define MAX_TAREAS 100
#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 100

// Estructura para cada equipo (excavadoras, camiones, etc)
struct Equipo {
    int id;                     // numero unico de identificacion
    char nombre[MAX_NOMBRE];    // nombre del equipo
    char tipo[MAX_NOMBRE];      // tipo: excavadora, camion, taladro
    int capacidad;              // capacidad o potencia del equipo
    bool disponible;            // true = disponible, false = ocupado
};

// Estructura para cada trabajador
struct RecursoHumano {
    int id;                     // numero unico de identificacion
    char nombre[MAX_NOMBRE];    // nombre completo del trabajador
    char rol[MAX_NOMBRE];       // rol: operador, supervisor, tecnico
    bool disponible;            // true = disponible, false = ocupado
};

// Estructura para cada tarea de trabajo
struct Tarea {
    int id;                           // numero unico de identificacion
    char descripcion[MAX_DESCRIPCION]; // descripcion de la tarea
    int duracionHoras;                // cuantas horas toma completarla
    int equiposNecesarios[10];        // lista de IDs de equipos que necesita
    int cantidadEquipos;              // cuantos equipos necesita en total
    int recursosNecesarios[10];       // lista de IDs de trabajadores que necesita
    int cantidadRecursos;             // cuantos trabajadores necesita en total
    bool completada;                  // true = terminada, false = pendiente
};

#endif
