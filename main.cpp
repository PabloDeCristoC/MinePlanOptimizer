#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include "mining_models.h"
#include "file_manager.h"

using namespace std;

// Variables globales para almacenar datos
vector<Equipo> equipos;
vector<RecursoHumano> recursos;
vector<Tarea> tareas;

// Función para limpiar la pantalla (multiplataforma)
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Función para pausar y esperar input del usuario
void pausar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Función para obtener input entero seguro
int obtenerEntero(const string& mensaje) {
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

// Función para obtener string seguro
string obtenerString(const string& mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

// Función para obtener boolean
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

// ==================== FUNCIONES DE EQUIPOS ====================

void mostrarEquipo(const Equipo& e) {
    cout << "ID: " << e.id 
         << " | Nombre: " << e.nombre 
         << " | Tipo: " << e.tipo
         << " | Capacidad: " << e.capacidad
         << " | Disponible: " << (e.disponible ? "Sí" : "No") 
         << endl;
}

void listarEquipos() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                        LISTA DE EQUIPOS                        " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    if (equipos.empty()) {
        cout << "No hay equipos registrados." << endl;
    } else {
        for (const auto& e : equipos) {
            mostrarEquipo(e);
        }
    }
    cout << "\nTotal de equipos: " << equipos.size() << endl;
    pausar();
}

void crearEquipo() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                        CREAR EQUIPO                           " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    Equipo nuevoEquipo;
    
    // Generar ID automático
    nuevoEquipo.id = equipos.empty() ? 1 : equipos.back().id + 1;
    
    nuevoEquipo.nombre = obtenerString("Nombre del equipo: ");
    nuevoEquipo.tipo = obtenerString("Tipo de equipo (ej: Excavadora, Camión, Taladro): ");
    nuevoEquipo.capacidad = obtenerEntero("Capacidad/Potencia: ");
    nuevoEquipo.disponible = obtenerBoolean("¿Está disponible?");
    
    equipos.push_back(nuevoEquipo);
    
    cout << "\n✓ Equipo creado exitosamente con ID: " << nuevoEquipo.id << endl;
    pausar();
}

void eliminarEquipo() {
    limpiarPantalla();
    cout <<"════════════════════════════════════════════════════════════════" << endl;
    cout << "                       ELIMINAR EQUIPO                         " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    if (equipos.empty()) {
        cout << "No hay equipos para eliminar." << endl;
        pausar();
        return;
    }
    
    // Mostrar equipos disponibles
    cout << "Equipos disponibles:" << endl;
    for (const auto& e : equipos) {
        mostrarEquipo(e);
    }
    
    int id = obtenerEntero("\nIngresa el ID del equipo a eliminar: ");
    
    auto it = find_if(equipos.begin(), equipos.end(), 
                     [id](const Equipo& e) { return e.id == id; });
    
    if (it != equipos.end()) {
        cout << "Eliminando equipo: " << it->nombre << endl;
        equipos.erase(it);
        cout << "✓ Equipo eliminado exitosamente." << endl;
    } else {
        cout << "✗ No se encontró un equipo con ID: " << id << endl;
    }
    pausar();
}

// ==================== FUNCIONES DE RECURSOS HUMANOS ====================

void mostrarRecursoHumano(const RecursoHumano& r) {
    cout << "ID: " << r.id 
         << " | Nombre: " << r.nombre 
         << " | Rol: " << r.rol
         << " | Disponible: " << (r.disponible ? "Sí" : "No") 
         << endl;
}

void listarRecursos() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                     RECURSOS HUMANOS                          " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    if (recursos.empty()) {
        cout << "No hay recursos humanos registrados." << endl;
    } else {
        for (const auto& r : recursos) {
            mostrarRecursoHumano(r);
        }
    }
    cout << "\nTotal de recursos: " << recursos.size() << endl;
    pausar();
}

void crearRecurso() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                    CREAR RECURSO HUMANO                       " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    RecursoHumano nuevoRecurso;
    
    // Generar ID automático
    nuevoRecurso.id = recursos.empty() ? 1 : recursos.back().id + 1;
    
    nuevoRecurso.nombre = obtenerString("Nombre del trabajador: ");
    nuevoRecurso.rol = obtenerString("Rol (ej: Operador, Supervisor, Técnico): ");
    nuevoRecurso.disponible = obtenerBoolean("¿Está disponible?");
    
    recursos.push_back(nuevoRecurso);
    
    cout << "\n✓ Recurso humano creado exitosamente con ID: " << nuevoRecurso.id << endl;
    pausar();
}

void eliminarRecurso() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                   ELIMINAR RECURSO HUMANO                     " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    if (recursos.empty()) {
        cout << "No hay recursos humanos para eliminar." << endl;
        pausar();
        return;
    }
    
    // Mostrar recursos disponibles
    cout << "Recursos humanos disponibles:" << endl;
    for (const auto& r : recursos) {
        mostrarRecursoHumano(r);
    }
    
    int id = obtenerEntero("\nIngresa el ID del recurso a eliminar: ");
    
    auto it = find_if(recursos.begin(), recursos.end(), 
                     [id](const RecursoHumano& r) { return r.id == id; });
    
    if (it != recursos.end()) {
        cout << "Eliminando recurso: " << it->nombre << endl;
        recursos.erase(it);
        cout << "✓ Recurso eliminado exitosamente." << endl;
    } else {
        cout << "✗ No se encontró un recurso con ID: " << id << endl;
    }
    pausar();
}

// ==================== FUNCIONES DE TAREAS ====================

void mostrarTarea(const Tarea& t) {
    cout << "ID: " << t.id 
         << " | Descripción: " << t.descripcion
         << " | Duración (hrs): " << t.duracionHoras
         << " | Completada: " << (t.completada ? "Sí" : "No") << endl;
    
    cout << "   Equipos necesarios: ";
    if (t.equiposNecesarios.empty()) {
        cout << "Ninguno";
    } else {
        for (size_t i = 0; i < t.equiposNecesarios.size(); ++i) {
            cout << t.equiposNecesarios[i];
            if (i < t.equiposNecesarios.size() - 1) cout << ", ";
        }
    }
    
    cout << " | Recursos necesarios: ";
    if (t.recursosHumanosNecesarios.empty()) {
        cout << "Ninguno";
    } else {
        for (size_t i = 0; i < t.recursosHumanosNecesarios.size(); ++i) {
            cout << t.recursosHumanosNecesarios[i];
            if (i < t.recursosHumanosNecesarios.size() - 1) cout << ", ";
        }
    }
    cout << endl;
}

void listarTareas() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                        LISTA DE TAREAS                        " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    if (tareas.empty()) {
        cout << "No hay tareas registradas." << endl;
    } else {
        for (const auto& t : tareas) {
            mostrarTarea(t);
            cout << endl;
        }
    }
    cout << "Total de tareas: " << tareas.size() << endl;
    pausar();
}

vector<int> seleccionarRecursos(const string& tipo, bool esEquipo) {
    vector<int> seleccionados;
    
    if (esEquipo && equipos.empty()) {
        cout << "No hay equipos disponibles." << endl;
        return seleccionados;
    }
    if (!esEquipo && recursos.empty()) {
        cout << "No hay recursos humanos disponibles." << endl;
        return seleccionados;
    }
    
    cout << "\n" << tipo << " disponibles:" << endl;
    if (esEquipo) {
        for (const auto& e : equipos) {
            mostrarEquipo(e);
        }
    } else {
        for (const auto& r : recursos) {
            mostrarRecursoHumano(r);
        }
    }
    
    cout << "\nIngresa los IDs necesarios separados por espacios (0 para terminar): ";
    string linea;
    getline(cin, linea);
    
    if (!linea.empty()) {
        size_t pos = 0;
        string token;
        linea += " "; // Añadir espacio al final para procesar último token
        
        while ((pos = linea.find(' ')) != string::npos) {
            token = linea.substr(0, pos);
            if (!token.empty()) {
                try {
                    int id = stoi(token);
                    if (id != 0) {
                        seleccionados.push_back(id);
                    }
                } catch (const exception&) {
                    // Ignorar tokens inválidos
                }
            }
            linea.erase(0, pos + 1);
        }
    }
    
    return seleccionados;
}

void crearTarea() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                        CREAR TAREA                            " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    Tarea nuevaTarea;
    
    // Generar ID automático
    nuevaTarea.id = tareas.empty() ? 1 : tareas.back().id + 1;
    
    nuevaTarea.descripcion = obtenerString("Descripción de la tarea: ");
    nuevaTarea.duracionHoras = obtenerEntero("Duración estimada (horas): ");
    
    // Seleccionar equipos necesarios
    nuevaTarea.equiposNecesarios = seleccionarRecursos("Equipos", true);
    
    // Seleccionar recursos humanos necesarios
    nuevaTarea.recursosHumanosNecesarios = seleccionarRecursos("Recursos humanos", false);
    
    nuevaTarea.completada = false;
    
    tareas.push_back(nuevaTarea);
    
    cout << "\n✓ Tarea creada exitosamente con ID: " << nuevaTarea.id << endl;
    pausar();
}

void completarTarea() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                      COMPLETAR TAREA                          " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    if (tareas.empty()) {
        cout << "No hay tareas registradas." << endl;
        pausar();
        return;
    }
    
    // Mostrar tareas pendientes
    cout << "Tareas pendientes:" << endl;
    bool hayPendientes = false;
    for (const auto& t : tareas) {
        if (!t.completada) {
            mostrarTarea(t);
            cout << endl;
            hayPendientes = true;
        }
    }
    
    if (!hayPendientes) {
        cout << "No hay tareas pendientes." << endl;
        pausar();
        return;
    }
    
    int id = obtenerEntero("\nIngresa el ID de la tarea a completar: ");
    
    auto it = find_if(tareas.begin(), tareas.end(), 
                     [id](const Tarea& t) { return t.id == id; });
    
    if (it != tareas.end()) {
        if (!it->completada) {
            it->completada = true;
            cout << "✓ Tarea '" << it->descripcion << "' marcada como completada." << endl;
        } else {
            cout << "La tarea ya estaba completada." << endl;
        }
    } else {
        cout << "✗ No se encontró una tarea con ID: " << id << endl;
    }
    pausar();
}

// ==================== MENÚS ====================

void menuEquipos() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "                      GESTIÓN DE EQUIPOS                       " << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "1. Listar equipos" << endl;
        cout << "2. Crear equipo" << endl;
        cout << "3. Eliminar equipo" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        
        opcion = obtenerEntero("Selecciona una opción: ");
        
        switch (opcion) {
            case 1: listarEquipos(); break;
            case 2: crearEquipo(); break;
            case 3: eliminarEquipo(); break;
            case 0: break;
            default: 
                cout << "Opción inválida. Intenta nuevamente." << endl;
                pausar();
        }
    } while (opcion != 0);
}

void menuRecursos() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "                   GESTIÓN DE RECURSOS HUMANOS                 " << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "1. Listar recursos humanos" << endl;
        cout << "2. Crear recurso humano" << endl;
        cout << "3. Eliminar recurso humano" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        
        opcion = obtenerEntero("Selecciona una opción: ");
        
        switch (opcion) {
            case 1: listarRecursos(); break;
            case 2: crearRecurso(); break;
            case 3: eliminarRecurso(); break;
            case 0: break;
            default: 
                cout << "Opción inválida. Intenta nuevamente." << endl;
                pausar();
        }
    } while (opcion != 0);
}

void menuTareas() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "                      GESTIÓN DE TAREAS                        " << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "1. Listar tareas" << endl;
        cout << "2. Crear tarea" << endl;
        cout << "3. Completar tarea" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        
        opcion = obtenerEntero("Selecciona una opción: ");
        
        switch (opcion) {
            case 1: listarTareas(); break;
            case 2: crearTarea(); break;
            case 3: completarTarea(); break;
            case 0: break;
            default: 
                cout << "Opción inválida. Intenta nuevamente." << endl;
                pausar();
        }
    } while (opcion != 0);
}

void cargarDatosEjemplo() {
    // Limpiar datos existentes
    equipos.clear();
    recursos.clear();
    tareas.clear();
    
    // Agregar equipos de ejemplo
    equipos.push_back({1, "Excavadora CAT 320", "Excavadora", 100, true});
    equipos.push_back({2, "Camión Volvo FH16", "Camión", 40, true});
    equipos.push_back({3, "Taladro Atlas Copco", "Taladro", 200, false});
    
    // Agregar recursos humanos de ejemplo
    recursos.push_back({1, "Juan Pérez", "Operador", true});
    recursos.push_back({2, "María González", "Supervisor", true});
    recursos.push_back({3, "Carlos Rodríguez", "Técnico", false});
    
    // Agregar tareas de ejemplo
    tareas.push_back({1, "Cargar material en camión", 5, {1}, {1}, false});
    tareas.push_back({2, "Transporte de mineral", 3, {2}, {1}, false});
    tareas.push_back({3, "Perforación de túnel", 8, {3}, {1, 3}, false});
    
    cout << "✓ Datos de ejemplo cargados exitosamente." << endl;
    pausar();
}

// ==================== FUNCIONES DE ARCHIVOS ====================

void menuExportarCSV() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                      EXPORTAR A CSV                           " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    int opcion;
    cout << "1. Exportar Equipos" << endl;
    cout << "2. Exportar Recursos Humanos" << endl;
    cout << "3. Exportar Tareas" << endl;
    cout << "4. Exportar Todo (archivos separados)" << endl;
    cout << "0. Cancelar" << endl;
    
    opcion = obtenerEntero("Selecciona una opción: ");
    
    bool exito = false;
    string archivo;
    
    switch (opcion) {
        case 1:
            archivo = obtenerString("Nombre del archivo (default: equipos.csv): ");
            if (archivo.empty()) archivo = "equipos.csv";
            exito = FileManager::guardarEquiposCSV(equipos, archivo);
            break;
            
        case 2:
            archivo = obtenerString("Nombre del archivo (default: recursos.csv): ");
            if (archivo.empty()) archivo = "recursos.csv";
            exito = FileManager::guardarRecursosCSV(recursos, archivo);
            break;
            
        case 3:
            archivo = obtenerString("Nombre del archivo (default: tareas.csv): ");
            if (archivo.empty()) archivo = "tareas.csv";
            exito = FileManager::guardarTareasCSV(tareas, archivo);
            break;
            
        case 4:
            exito = FileManager::guardarEquiposCSV(equipos, "equipos.csv") &&
                   FileManager::guardarRecursosCSV(recursos, "recursos.csv") &&
                   FileManager::guardarTareasCSV(tareas, "tareas.csv");
            cout << "Archivos creados:" << endl;
            cout << "- equipos.csv" << endl;
            cout << "- recursos.csv" << endl;
            cout << "- tareas.csv" << endl;
            break;
            
        case 0:
            return;
            
        default:
            cout << "Opción no válida." << endl;
            pausar();
            return;
    }
    
    if (exito) {
        cout << "✓ Exportación exitosa." << endl;
    } else {
        cout << "✗ Error durante la exportación." << endl;
    }
    
    pausar();
}

void menuImportarCSV() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                      IMPORTAR DESDE CSV                       " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    cout << "ADVERTENCIA: Esta operación reemplazará los datos actuales." << endl;
    if (!obtenerBoolean("¿Deseas continuar?")) {
        return;
    }
    
    int opcion;
    cout << "\n1. Importar Equipos" << endl;
    cout << "2. Importar Recursos Humanos" << endl;
    cout << "3. Importar Tareas" << endl;
    cout << "4. Importar Todo (desde archivos separados)" << endl;
    cout << "0. Cancelar" << endl;
    
    opcion = obtenerEntero("Selecciona una opción: ");
    
    bool exito = false;
    string archivo;
    
    switch (opcion) {
        case 1:
            archivo = obtenerString("Nombre del archivo (default: equipos.csv): ");
            if (archivo.empty()) archivo = "equipos.csv";
            exito = FileManager::cargarEquiposCSV(equipos, archivo);
            break;
            
        case 2:
            archivo = obtenerString("Nombre del archivo (default: recursos.csv): ");
            if (archivo.empty()) archivo = "recursos.csv";
            exito = FileManager::cargarRecursosCSV(recursos, archivo);
            break;
            
        case 3:
            archivo = obtenerString("Nombre del archivo (default: tareas.csv): ");
            if (archivo.empty()) archivo = "tareas.csv";
            exito = FileManager::cargarTareasCSV(tareas, archivo);
            break;
            
        case 4:
            exito = FileManager::cargarEquiposCSV(equipos, "equipos.csv") &&
                   FileManager::cargarRecursosCSV(recursos, "recursos.csv") &&
                   FileManager::cargarTareasCSV(tareas, "tareas.csv");
            break;
            
        case 0:
            return;
            
        default:
            cout << "Opción no válida." << endl;
            pausar();
            return;
    }
    
    if (exito) {
        cout << "✓ Importación exitosa." << endl;
    } else {
        cout << "✗ Error durante la importación. Verifica que el archivo existe y tiene el formato correcto." << endl;
    }
    
    pausar();
}

void guardarProyectoJSON() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                    GUARDAR PROYECTO (JSON)                    " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    string archivo = obtenerString("Nombre del archivo (default: mine_data.json): ");
    if (archivo.empty()) archivo = "mine_data.json";
    
    if (FileManager::guardarTodosJSON(equipos, recursos, tareas, archivo)) {
        cout << "✓ Proyecto guardado exitosamente en: " << archivo << endl;
    } else {
        cout << "✗ Error al guardar el proyecto." << endl;
    }
    
    pausar();
}

void cargarProyectoJSON() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                    CARGAR PROYECTO (JSON)                     " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    cout << "ADVERTENCIA: Esta operación reemplazará todos los datos actuales." << endl;
    if (!obtenerBoolean("¿Deseas continuar?")) {
        return;
    }
    
    string archivo = obtenerString("Nombre del archivo (default: mine_data.json): ");
    if (archivo.empty()) archivo = "mine_data.json";
    
    if (FileManager::cargarTodosJSON(equipos, recursos, tareas, archivo)) {
        cout << "✓ Proyecto cargado exitosamente desde: " << archivo << endl;
        cout << "Datos cargados:" << endl;
        cout << "- Equipos: " << equipos.size() << endl;
        cout << "- Recursos: " << recursos.size() << endl;
        cout << "- Tareas: " << tareas.size() << endl;
    } else {
        cout << "✗ Error al cargar el proyecto. Verifica que el archivo existe y tiene el formato correcto." << endl;
    }
    
    pausar();
}

void crearRespaldoAuto() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                       CREAR RESPALDO                          " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    if (FileManager::crearRespaldo(equipos, recursos, tareas)) {
        cout << "✓ Respaldo creado exitosamente." << endl;
        cout << "El archivo se guardó con timestamp automático." << endl;
    } else {
        cout << "✗ Error al crear el respaldo." << endl;
    }
    
    pausar();
}

void restaurarRespaldo() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                      RESTAURAR RESPALDO                       " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    cout << "ADVERTENCIA: Esta operación reemplazará todos los datos actuales." << endl;
    if (!obtenerBoolean("¿Deseas continuar?")) {
        return;
    }
    
    if (FileManager::restaurarRespaldo(equipos, recursos, tareas)) {
        cout << "✓ Respaldo restaurado exitosamente." << endl;
        cout << "Datos restaurados:" << endl;
        cout << "- Equipos: " << equipos.size() << endl;
        cout << "- Recursos: " << recursos.size() << endl;
        cout << "- Tareas: " << tareas.size() << endl;
    } else {
        cout << "✗ Error al restaurar el respaldo." << endl;
    }
    
    pausar();
}

void menuArchivos() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "                    GESTIÓN DE ARCHIVOS                        " << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "           ---- FORMATO CSV (INDIVIDUAL) ----" << endl;
        cout << "1. Exportar a CSV" << endl;
        cout << "2. Importar desde CSV" << endl;
        cout << "           ---- FORMATO JSON (COMPLETO) ----" << endl;
        cout << "3. Guardar Proyecto (JSON)" << endl;
        cout << "4. Cargar Proyecto (JSON)" << endl;
        cout << "           ---- RESPALDOS AUTOMÁTICOS ----" << endl;
        cout << "5. Crear Respaldo" << endl;
        cout << "6. Restaurar Respaldo" << endl;
        cout << "0. Volver al menú principal" << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        
        opcion = obtenerEntero("Selecciona una opción: ");
        
        switch (opcion) {
            case 1: menuExportarCSV(); break;
            case 2: menuImportarCSV(); break;
            case 3: guardarProyectoJSON(); break;
            case 4: cargarProyectoJSON(); break;
            case 5: crearRespaldoAuto(); break;
            case 6: restaurarRespaldo(); break;
            case 0: break;
            default: 
                cout << "Opción inválida. Intenta nuevamente." << endl;
                pausar();
        }
    } while (opcion != 0);
}

void mostrarEstadisticas() {
    limpiarPantalla();
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "                      ESTADÍSTICAS GENERALES                   " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    
    // Estadísticas de equipos
    int equiposDisponibles = count_if(equipos.begin(), equipos.end(), 
                                     [](const Equipo& e) { return e.disponible; });
    cout << "EQUIPOS:" << endl;
    cout << "  Total: " << equipos.size() << endl;
    cout << "  Disponibles: " << equiposDisponibles << endl;
    cout << "  No disponibles: " << (equipos.size() - equiposDisponibles) << endl;
    
    // Estadísticas de recursos
    int recursosDisponibles = count_if(recursos.begin(), recursos.end(), 
                                      [](const RecursoHumano& r) { return r.disponible; });
    cout << "\nRECURSOS HUMANOS:" << endl;
    cout << "  Total: " << recursos.size() << endl;
    cout << "  Disponibles: " << recursosDisponibles << endl;
    cout << "  No disponibles: " << (recursos.size() - recursosDisponibles) << endl;
    
    // Estadísticas de tareas
    int tareasCompletadas = count_if(tareas.begin(), tareas.end(), 
                                    [](const Tarea& t) { return t.completada; });
    int horasTotales = 0;
    for (const auto& t : tareas) {
        horasTotales += t.duracionHoras;
    }
    
    cout << "\nTAREAS:" << endl;
    cout << "  Total: " << tareas.size() << endl;
    cout << "  Completadas: " << tareasCompletadas << endl;
    cout << "  Pendientes: " << (tareas.size() - tareasCompletadas) << endl;
    cout << "  Horas totales estimadas: " << horasTotales << endl;
    
    if (tareas.size() > 0) {
        double porcentajeCompletado = (double)tareasCompletadas / tareas.size() * 100;
        cout << "  Progreso: " << fixed << porcentajeCompletado << "%" << endl;
    }
    
    pausar();
}

int main() {
    int opcion;
    
    cout << "════════════════════════════════════════════════════════════════" << endl;
    cout << "              BIENVENIDO A MINE PLAN OPTIMIZER                  " << endl;
    cout << "        Sistema de Optimización de Operaciones Mineras          " << endl;
    cout << "════════════════════════════════════════════════════════════════" << endl;
    pausar();
    
    do {
        limpiarPantalla();
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "                         MENÚ PRINCIPAL                        " << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        cout << "1. Gestión de Equipos" << endl;
        cout << "2. Gestión de Recursos Humanos" << endl;
        cout << "3. Gestión de Tareas" << endl;
        cout << "4. Gestión de Archivos" << endl;
        cout << "5. Ver Estadísticas" << endl;
        cout << "6. Cargar Datos de Ejemplo" << endl;
        cout << "0. Salir" << endl;
        cout << "════════════════════════════════════════════════════════════════" << endl;
        
        opcion = obtenerEntero("Selecciona una opción: ");
        
        switch (opcion) {
            case 1: menuEquipos(); break;
            case 2: menuRecursos(); break;
            case 3: menuTareas(); break;
            case 4: menuArchivos(); break;
            case 5: mostrarEstadisticas(); break;
            case 6: cargarDatosEjemplo(); break;
            case 0: 
                cout << "\n¡Gracias por usar Mine Plan Optimizer!" << endl;
                cout << "Desarrollado por Pablo Emanuel de Cristo Cavieres Körn" << endl;
                break;
            default: 
                cout << "Opción inválida. Intenta nuevamente." << endl;
                pausar();
        }
    } while (opcion != 0);
    
    return 0;
}