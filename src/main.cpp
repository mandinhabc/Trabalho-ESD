#include <iostream>
#include "parser.hpp"
#include "structs/linkedlist.hpp"
#include <vector>

int main() {
    std::vector<Music> musicas = load_music_dataset("dataset/Top_spotify_songs.csv");

    std::cout << "Total de músicas carregadas: " << musicas.size() << std::endl;

    if (!musicas.empty()) {
        std::cout << "Exemplo: " << musicas[0].name
                  << " - " << musicas[0].artist
                  << " (País: " << musicas[0].country << ", Popularidade: " << musicas[0].popularity << ")"
                  << std::endl;
    }

    LinkedList lista;
    for (const auto& m : musicas) {
        lista.insert(m);
    }

    std::cout << "Músicas carregadas: " << musicas.size() << std::endl;
    std::cout << "Primeiras 5 músicas na lista encadeada:" << std::endl;
    lista.print_sample(5);

    std::string nome_busca = "Blinding Lights";
    Music* encontrada = lista.find_by_name(nome_busca);
    if (encontrada)
        std::cout << "Encontrada: " << encontrada->name << " - " << encontrada->artist << std::endl;
    else
        std::cout << nome_busca << " não encontrada." << std::endl;

    return 0;
}
