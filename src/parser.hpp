#pragma once
#include <string>
#include <vector>

struct Music {
    std::string id;
    std::string name;
    std::string artist;
    std::string country;
    std::string is_explicit;
    int popularity;
    int duration_ms;
    double danceability;
    double energy;
    double tempo;
};

// Função que carrega o dataset
std::vector<Music> load_music_dataset(const std::string& filename);
