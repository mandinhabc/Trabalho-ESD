# Nome do executável
TARGET = music_system

# Diretórios
SRC_DIR = src
STRUCTS_DIR = $(SRC_DIR)/structs

# Encontra todos os .cpp do src e src/structs
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(STRUCTS_DIR)/*.cpp)

# Comando de compilação
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Regra padrão
all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# Limpa o executável
clean:
	rm -f $(TARGET)
