# Makefile para Mine Plan Optimizer
# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++11 -Wall -Wextra -O2

# Archivos fuente
SOURCES = main.cpp file_manager.cpp

# Archivos de encabezado
HEADERS = mining_models.h file_manager.h

# Nombre del ejecutable
TARGET = mine_optimizer

# Archivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Regla principal
all: $(TARGET)

# Compilar el ejecutable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ Compilación exitosa! Ejecutable: $(TARGET)"

# Compilar archivos objeto
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos temporales
clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ Archivos temporales eliminados"

# Limpiar archivos de datos
clean-data:
	rm -f *.csv *.json backup_*.json
	@echo "✓ Archivos de datos eliminados"

# Ejecutar el programa
run: $(TARGET)
	./$(TARGET)

# Ejecutar con datos de ejemplo
run-demo: $(TARGET)
	@echo "Ejecutando con datos de ejemplo..."
	./$(TARGET)

# Instalar (copiar a /usr/local/bin)
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/
	@echo "✓ Instalado en /usr/local/bin/"

# Desinstalar
uninstall:
	rm -f /usr/local/bin/$(TARGET)
	@echo "✓ Desinstalado"

# Crear paquete de distribución
package: clean
	tar -czf mine_optimizer.tar.gz *.cpp *.h Makefile README.md
	@echo "✓ Paquete creado: mine_optimizer.tar.gz"

# Verificar sintaxis sin compilar
check:
	$(CXX) $(CXXFLAGS) -fsyntax-only $(SOURCES)
	@echo "✓ Sintaxis verificada"

# Crear estructura de directorio para desarrollo
setup:
	mkdir -p data backups docs
	@echo "✓ Estructura de directorios creada"

# Reglas que no son archivos
.PHONY: all clean clean-data run run-demo install uninstall package check setup

# Información de ayuda
help:
	@echo "Mine Plan Optimizer - Makefile"
	@echo "=============================="
	@echo ""
	@echo "Targets disponibles:"
	@echo "  all        - Compilar el proyecto (default)"
	@echo "  clean      - Limpiar archivos temporales"
	@echo "  clean-data - Limpiar archivos de datos (CSV/JSON)"
	@echo "  run        - Compilar y ejecutar"
	@echo "  run-demo   - Ejecutar con datos de ejemplo"
	@echo "  check      - Verificar sintaxis sin compilar"
	@echo "  install    - Instalar en sistema (/usr/local/bin)"
	@echo "  uninstall  - Desinstalar del sistema"
	@echo "  package    - Crear paquete de distribución"
	@echo "  setup      - Crear estructura de directorios"
	@echo "  help       - Mostrar esta ayuda"
	@echo ""
	@echo "Ejemplo de uso:"
	@echo "  make           # Compilar"
	@echo "  make run       # Compilar y ejecutar"
	@echo "  make clean     # Limpiar archivos temporales"