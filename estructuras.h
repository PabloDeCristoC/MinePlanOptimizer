#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX_EQUIPOS 100
#define MAX_RECURSOS 100
#define MAX_TAREAS 100
#define MAX_NOMBRE 50
#define MAX_DESCRIPCION 100


struct Equipo {
    int id;                     
    char nombre[MAX_NOMBRE];    
    char tipo[MAX_NOMBRE];      
    int capacidad;              
    bool disponible;           
};


struct RecursoHumano {
    int id;                     
    char nombre[MAX_NOMBRE];    
    char rol[MAX_NOMBRE];       
    bool disponible;            
};


struct Tarea {
    int id;                           
    char descripcion[MAX_DESCRIPCION]; 
    int duracionHoras;                
    int equiposNecesarios[10];        
    int cantidadEquipos;              
    int recursosNecesarios[10];       
    int cantidadRecursos;             
    bool completada;                  
};

#endif
