#include "file_manager.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

string FileManager::vectorIntToString(const vector<int>& vec) {
    if (vec.empty()) return "";
    
    stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i) {
        ss << vec[i];
        if (i < vec.size() - 1) ss << ";";
    }
    return ss.str();
}

vector<int> FileManager::stringToVectorInt(const string& str) {
    vector<int> result;
    if (str.empty()) return result;
    
    stringstream ss(str);
    string item;
    
    while (getline(ss, item, ';')) {
        if (!item.empty()) {
            try {
                result.push_back(stoi(item));
            } catch (const exception&) {
                
            }
        }
    }
    return result;
}

string FileManager::boolToString(bool value) {
    return value ? "true" : "false";
}

bool FileManager::stringToBool(const string& str) {
    return (str == "true" || str == "1" || str == "True" || str == "TRUE");
}


string escaparCSV(const string& str) {
    string result = str;

    size_t pos = 0;
    while ((pos = result.find("\"", pos)) != string::npos) {
        result.replace(pos, 1, "\"\"");
        pos += 2;
    }
    

    if (result.find(',') != string::npos || 
        result.find('\"') != string::npos || 
        result.find('\n') != string::npos) {
        result = "\"" + result + "\"";
    }
    
    return result;
}


string desescaparCSV(string str) {

    if (str.length() >= 2 && str.front() == '\"' && str.back() == '\"') {
        str = str.substr(1, str.length() - 2);

        size_t pos = 0;
        while ((pos = str.find("\"\"", pos)) != string::npos) {
            str.replace(pos, 2, "\"");
            pos += 1;
        }
    }
    return str;
}



bool FileManager::guardarEquiposCSV(const vector<Equipo>& equipos, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para escritura." << endl;
        return false;
    }
    

    file << "id,nombre,tipo,capacidad,disponible" << endl;
    

    for (const auto& equipo : equipos) {
        file << equipo.id << ","
             << escaparCSV(equipo.nombre) << ","
             << escaparCSV(equipo.tipo) << ","
             << equipo.capacidad << ","
             << boolToString(equipo.disponible) << endl;
    }
    
    file.close();
    return true;
}

bool FileManager::cargarEquiposCSV(vector<Equipo>& equipos, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para lectura." << endl;
        return false;
    }
    
    equipos.clear();
    string line;
    

    if (getline(file, line)) {

        while (getline(file, line)) {
            if (line.empty()) continue;
            
            stringstream ss(line);
            string item;
            vector<string> campos;
            

            bool dentroComillas = false;
            string campoActual = "";
            
            for (char c : line) {
                if (c == '\"') {
                    dentroComillas = !dentroComillas;
                    campoActual += c;
                } else if (c == ',' && !dentroComillas) {
                    campos.push_back(desescaparCSV(campoActual));
                    campoActual = "";
                } else {
                    campoActual += c;
                }
            }
            campos.push_back(desescaparCSV(campoActual));
            
            if (campos.size() >= 5) {
                Equipo equipo;
                try {
                    equipo.id = stoi(campos[0]);
                    equipo.nombre = campos[1];
                    equipo.tipo = campos[2];
                    equipo.capacidad = stoi(campos[3]);
                    equipo.disponible = stringToBool(campos[4]);
                    equipos.push_back(equipo);
                } catch (const exception& e) {
                    cerr << "Error procesando línea: " << line << endl;
                }
            }
        }
    }
    
    file.close();
    return true;
}


bool FileManager::guardarRecursosCSV(const vector<RecursoHumano>& recursos, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para escritura." << endl;
        return false;
    }
    

    file << "id,nombre,rol,disponible" << endl;
    

    for (const auto& recurso : recursos) {
        file << recurso.id << ","
             << escaparCSV(recurso.nombre) << ","
             << escaparCSV(recurso.rol) << ","
             << boolToString(recurso.disponible) << endl;
    }
    
    file.close();
    return true;
}

bool FileManager::cargarRecursosCSV(vector<RecursoHumano>& recursos, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para lectura." << endl;
        return false;
    }
    
    recursos.clear();
    string line;
    

    if (getline(file, line)) {

        while (getline(file, line)) {
            if (line.empty()) continue;
            
            vector<string> campos;
            bool dentroComillas = false;
            string campoActual = "";
            
            for (char c : line) {
                if (c == '\"') {
                    dentroComillas = !dentroComillas;
                    campoActual += c;
                } else if (c == ',' && !dentroComillas) {
                    campos.push_back(desescaparCSV(campoActual));
                    campoActual = "";
                } else {
                    campoActual += c;
                }
            }
            campos.push_back(desescaparCSV(campoActual));
            
            if (campos.size() >= 4) {
                RecursoHumano recurso;
                try {
                    recurso.id = stoi(campos[0]);
                    recurso.nombre = campos[1];
                    recurso.rol = campos[2];
                    recurso.disponible = stringToBool(campos[3]);
                    recursos.push_back(recurso);
                } catch (const exception& e) {
                    cerr << "Error procesando línea: " << line << endl;
                }
            }
        }
    }
    
    file.close();
    return true;
}


bool FileManager::guardarTareasCSV(const vector<Tarea>& tareas, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para escritura." << endl;
        return false;
    }
    
    file << "id,descripcion,duracion_horas,equipos_necesarios,recursos_necesarios,completada" << endl;
    
    for (const auto& tarea : tareas) {
        file << tarea.id << ","
             << escaparCSV(tarea.descripcion) << ","
             << tarea.duracionHoras << ","
             << escaparCSV(vectorIntToString(tarea.equiposNecesarios)) << ","
             << escaparCSV(vectorIntToString(tarea.recursosHumanosNecesarios)) << ","
             << boolToString(tarea.completada) << endl;
    }
    
    file.close();
    return true;
}

bool FileManager::cargarTareasCSV(vector<Tarea>& tareas, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para lectura." << endl;
        return false;
    }
    
    tareas.clear();
    string line;
    
    if (getline(file, line)) {
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            vector<string> campos;
            bool dentroComillas = false;
            string campoActual = "";
            
            for (char c : line) {
                if (c == '\"') {
                    dentroComillas = !dentroComillas;
                    campoActual += c;
                } else if (c == ',' && !dentroComillas) {
                    campos.push_back(desescaparCSV(campoActual));
                    campoActual = "";
                } else {
                    campoActual += c;
                }
            }
            campos.push_back(desescaparCSV(campoActual));
            
            if (campos.size() >= 6) {
                Tarea tarea;
                try {
                    tarea.id = stoi(campos[0]);
                    tarea.descripcion = campos[1];
                    tarea.duracionHoras = stoi(campos[2]);
                    tarea.equiposNecesarios = stringToVectorInt(campos[3]);
                    tarea.recursosHumanosNecesarios = stringToVectorInt(campos[4]);
                    tarea.completada = stringToBool(campos[5]);
                    tareas.push_back(tarea);
                } catch (const exception& e) {
                    cerr << "Error procesando línea: " << line << endl;
                }
            }
        }
    }
    
    file.close();
    return true;
}


bool FileManager::guardarTodosJSON(const vector<Equipo>& equipos, 
                                  const vector<RecursoHumano>& recursos, 
                                  const vector<Tarea>& tareas, 
                                  const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para escritura." << endl;
        return false;
    }
    
    file << "{" << endl;
    file << "  \"version\": \"1.0\"," << endl;
    file << "  \"timestamp\": \"" << time(nullptr) << "\"," << endl;
    

    file << "  \"equipos\": [" << endl;
    for (size_t i = 0; i < equipos.size(); ++i) {
        const auto& e = equipos[i];
        file << "    {" << endl;
        file << "      \"id\": " << e.id << "," << endl;
        file << "      \"nombre\": \"" << e.nombre << "\"," << endl;
        file << "      \"tipo\": \"" << e.tipo << "\"," << endl;
        file << "      \"capacidad\": " << e.capacidad << "," << endl;
        file << "      \"disponible\": " << boolToString(e.disponible) << endl;
        file << "    }";
        if (i < equipos.size() - 1) file << ",";
        file << endl;
    }
    file << "  ]," << endl;
    

    file << "  \"recursos\": [" << endl;
    for (size_t i = 0; i < recursos.size(); ++i) {
        const auto& r = recursos[i];
        file << "    {" << endl;
        file << "      \"id\": " << r.id << "," << endl;
        file << "      \"nombre\": \"" << r.nombre << "\"," << endl;
        file << "      \"rol\": \"" << r.rol << "\"," << endl;
        file << "      \"disponible\": " << boolToString(r.disponible) << endl;
        file << "    }";
        if (i < recursos.size() - 1) file << ",";
        file << endl;
    }
    file << "  ]," << endl;
    

    file << "  \"tareas\": [" << endl;
    for (size_t i = 0; i < tareas.size(); ++i) {
        const auto& t = tareas[i];
        file << "    {" << endl;
        file << "      \"id\": " << t.id << "," << endl;
        file << "      \"descripcion\": \"" << t.descripcion << "\"," << endl;
        file << "      \"duracion_horas\": " << t.duracionHoras << "," << endl;
        

        file << "      \"equipos_necesarios\": [";
        for (size_t j = 0; j < t.equiposNecesarios.size(); ++j) {
            file << t.equiposNecesarios[j];
            if (j < t.equiposNecesarios.size() - 1) file << ", ";
        }
        file << "]," << endl;
        

        file << "      \"recursos_necesarios\": [";
        for (size_t j = 0; j < t.recursosHumanosNecesarios.size(); ++j) {
            file << t.recursosHumanosNecesarios[j];
            if (j < t.recursosHumanosNecesarios.size() - 1) file << ", ";
        }
        file << "]," << endl;
        
        file << "      \"completada\": " << boolToString(t.completada) << endl;
        file << "    }";
        if (i < tareas.size() - 1) file << ",";
        file << endl;
    }
    file << "  ]" << endl;
    file << "}" << endl;
    
    file.close();
    return true;
}

string extraerValorJSON(const string& line, const string& key) {
    size_t keyPos = line.find("\"" + key + "\"");
    if (keyPos == string::npos) return "";
    
    size_t colonPos = line.find(":", keyPos);
    if (colonPos == string::npos) return "";
    
    size_t startPos = colonPos + 1;
    
    while (startPos < line.length() && (line[startPos] == ' ' || line[startPos] == '\t')) {
        startPos++;
    }
    
    if (startPos >= line.length()) return "";
    
    string valor;
    if (line[startPos] == '\"') {
        
        startPos++;
        size_t endPos = line.find('\"', startPos);
        if (endPos != string::npos) {
            valor = line.substr(startPos, endPos - startPos);
        }
    } else if (line[startPos] == '[') {
 
        size_t endPos = line.find(']', startPos);
        if (endPos != string::npos) {
            valor = line.substr(startPos + 1, endPos - startPos - 1);
        }
    } else {
        size_t endPos = startPos;
        while (endPos < line.length() && 
               line[endPos] != ',' && 
               line[endPos] != '}' && 
               line[endPos] != '\n') {
            endPos++;
        }
        valor = line.substr(startPos, endPos - startPos);
        
        while (!valor.empty() && (valor.back() == ' ' || valor.back() == '\t')) {
            valor.pop_back();
        }
    }
    
    return valor;
}

bool FileManager::cargarTodosJSON(vector<Equipo>& equipos, 
                                 vector<RecursoHumano>& recursos, 
                                 vector<Tarea>& tareas, 
                                 const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << filename << " para lectura." << endl;
        return false;
    }
    
    equipos.clear();
    recursos.clear();
    tareas.clear();
    
    string line;
    string seccionActual = "";
    
    while (getline(file, line)) {
        if (line.find("\"equipos\"") != string::npos) {
            seccionActual = "equipos";
            continue;
        } else if (line.find("\"recursos\"") != string::npos) {
            seccionActual = "recursos";
            continue;
        } else if (line.find("\"tareas\"") != string::npos) {
            seccionActual = "tareas";
            continue;
        }
        
        // Procesar objetos
        if (line.find("\"id\"") != string::npos) {
            if (seccionActual == "equipos") {
                Equipo equipo;
                equipo.id = stoi(extraerValorJSON(line, "id"));
                
                // Leer siguientes líneas del objeto
                if (getline(file, line)) equipo.nombre = extraerValorJSON(line, "nombre");
                if (getline(file, line)) equipo.tipo = extraerValorJSON(line, "tipo");
                if (getline(file, line)) equipo.capacidad = stoi(extraerValorJSON(line, "capacidad"));
                if (getline(file, line)) equipo.disponible = stringToBool(extraerValorJSON(line, "disponible"));
                
                equipos.push_back(equipo);
                
            } else if (seccionActual == "recursos") {
                RecursoHumano recurso;
                recurso.id = stoi(extraerValorJSON(line, "id"));
                
                if (getline(file, line)) recurso.nombre = extraerValorJSON(line, "nombre");
                if (getline(file, line)) recurso.rol = extraerValorJSON(line, "rol");
                if (getline(file, line)) recurso.disponible = stringToBool(extraerValorJSON(line, "disponible"));
                
                recursos.push_back(recurso);
                
            } else if (seccionActual == "tareas") {
                Tarea tarea;
                tarea.id = stoi(extraerValorJSON(line, "id"));
                
                if (getline(file, line)) tarea.descripcion = extraerValorJSON(line, "descripcion");
                if (getline(file, line)) tarea.duracionHoras = stoi(extraerValorJSON(line, "duracion_horas"));
                
                // Arrays
                if (getline(file, line)) {
                    string equiposStr = extraerValorJSON(line, "equipos_necesarios");
                    if (!equiposStr.empty()) {
                        stringstream ss(equiposStr);
                        string item;
                        while (getline(ss, item, ',')) {
                            // Limpiar espacios
                            item.erase(0, item.find_first_not_of(" \t"));
                            item.erase(item.find_last_not_of(" \t") + 1);
                            if (!item.empty()) {
                                tarea.equiposNecesarios.push_back(stoi(item));
                            }
                        }
                    }
                }
                
                if (getline(file, line)) {
                    string recursosStr = extraerValorJSON(line, "recursos_necesarios");
                    if (!recursosStr.empty()) {
                        stringstream ss(recursosStr);
                        string item;
                        while (getline(ss, item, ',')) {
                            item.erase(0, item.find_first_not_of(" \t"));
                            item.erase(item.find_last_not_of(" \t") + 1);
                            if (!item.empty()) {
                                tarea.recursosHumanosNecesarios.push_back(stoi(item));
                            }
                        }
                    }
                }
                
                if (getline(file, line)) tarea.completada = stringToBool(extraerValorJSON(line, "completada"));
                
                tareas.push_back(tarea);
            }
        }
    }
    
    file.close();
    return true;
}


bool FileManager::crearRespaldo(const vector<Equipo>& equipos, 
                               const vector<RecursoHumano>& recursos, 
                               const vector<Tarea>& tareas) {
    time_t now = time(0);
    string timestamp = to_string(now);
    string filename = "backup_" + timestamp + ".json";
    
    return guardarTodosJSON(equipos, recursos, tareas, filename);
}

bool FileManager::restaurarRespaldo(vector<Equipo>& equipos, 
                                   vector<RecursoHumano>& recursos, 
                                   vector<Tarea>& tareas) {
    // Buscar el respaldo más reciente
    // Esta es una implementación simple, en un caso real podrías listar archivos
    cout << "Introduce el nombre del archivo de respaldo (ej: backup_1234567890.json): ";
    string filename;
    getline(cin, filename);
    
    return cargarTodosJSON(equipos, recursos, tareas, filename);
}