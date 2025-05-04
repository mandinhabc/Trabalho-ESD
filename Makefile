# Nome do executável
TARGET = music_system.exe

# Compilador
CXX = g++

# Flags do compilador (gera binário estático para rodar fora do MSYS2)
CXXFLAGS = -std=c++17 -Wall -static -static-libgcc -static-libstdc++

# Diretórios
SRC_DIR = src
STRUCTS_DIR = $(SRC_DIR)/structs

# Arquivos fonte
SOURCES = $(SRC_DIR)/main.cpp \
          $(SRC_DIR)/parser.cpp \
          $(STRUCTS_DIR)/linkedlist.cpp \
          $(STRUCTS_DIR)/avltree.cpp \
          $(STRUCTS_DIR)/hashtable.cpp

# Regra padrão
all: $(TARGET)

# Compila o executável
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Limpa os arquivos gerados
clean:
	del /f /q $(TARGET) 2>nul || true
