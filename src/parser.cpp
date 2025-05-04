#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

// Divide uma linha CSV considerando campos entre aspas
std::vector<std::string> split_csv_line(const std::string& line) {
    std::vector<std::string> result;
    std::string current;
    bool inside_quotes = false;

    for (char ch : line) {
        if (ch == '"') {
            inside_quotes = !inside_quotes;
        } else if (ch == ',' && !inside_quotes) {
            result.push_back(current);
            current.clear();
        } else {
            current += ch;
        }
    }
    result.push_back(current);
    return result;
}

// Lê e processa o arquivo CSV
std::vector<Music> load_music_dataset(const std::string& filename) {
    std::vector<Music> dataset;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return dataset;
    }

    std::string line;
    bool header_skipped = false;
    int linha = 1;

    while (std::getline(file, line)) {
        if (!header_skipped) {
            header_skipped = true;
            continue;
        }

        std::vector<std::string> campos = split_csv_line(line);

        try {
            if (campos.size() < 24) throw std::runtime_error("Colunas insuficientes");

            Music m;
            m.id = campos[0];
            m.name = campos[1];
            m.artist = campos[2];
            m.country = campos[6];
            m.popularity = std::stoi(campos[8]);
            m.is_explicit = campos[9];
            m.duration_ms = std::stoi(campos[10]);
            m.danceability = std::stod(campos[13]);
            m.energy = std::stod(campos[14]);
            m.tempo = std::stod(campos[22]);

            dataset.push_back(m);
        } catch (...) {
            std::cerr << "⚠️ Erro ao processar linha " << linha << ": " << line << "\n";
        }

        linha++;
    }

    file.close();
    return dataset;
}
