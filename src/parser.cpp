#include "parser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

std::vector<Music> load_music_dataset(const std::string& filename) {
    std::vector<Music> dataset;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return dataset;
    }

    std::string line;
    bool header_skipped = false;

    while (std::getline(file, line)) {
        if (!header_skipped) {
            header_skipped = true;
            continue; // pula o cabeçalho
        }

        std::stringstream ss(line);
        std::string token;
        Music music;

        // Lê e ignora as colunas que não vamos usar
        std::getline(ss, music.id, ',');
        std::getline(ss, music.name, ',');
        std::getline(ss, music.artist, ',');
        std::getline(ss, token, ','); // daily_rank
        std::getline(ss, token, ','); // daily_movement
        std::getline(ss, token, ','); // weekly_movement
        std::getline(ss, music.country, ',');
        std::getline(ss, token, ','); // snapshot_date
        std::getline(ss, token, ','); music.popularity = std::stoi(token);
        std::getline(ss, token, ','); // is_explicit
        std::getline(ss, token, ','); music.duration_ms = std::stoi(token);
        std::getline(ss, token, ','); // album_name
        std::getline(ss, token, ','); // album_release_date
        std::getline(ss, token, ','); music.danceability = std::stod(token);
        std::getline(ss, token, ','); music.energy = std::stod(token);
        std::getline(ss, token, ','); // key
        std::getline(ss, token, ','); // loudness
        std::getline(ss, token, ','); // mode
        std::getline(ss, token, ','); // speechiness
        std::getline(ss, token, ','); // acousticness
        std::getline(ss, token, ','); // instrumentalness
        std::getline(ss, token, ','); // liveness
        std::getline(ss, token, ','); // valence
        std::getline(ss, token, ','); music.tempo = std::stod(token);

        dataset.push_back(music);
    }

    file.close();
    return dataset;
}
