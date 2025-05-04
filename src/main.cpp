#include <iostream>
#include <limits>
#include <sstream>
#include <fstream>
#include "parser.hpp"
#include "structs/linkedlist.hpp"
#include "structs/avltree.hpp"
#include "structs/hashtable.hpp"

void mostrarMenu() {
    std::cout << "\n========= MENU =========\n"
              << "1. Mostrar 5 músicas da lista encadeada\n"
              << "2. Mostrar músicas ordenadas pela popularidade (AVL)\n"
              << "3. Buscar por nome (Hash Table)\n"
              << "4. Buscar por popularidade (AVL)\n"
              << "5. Inserir nova música\n"
              << "6. Remover música por nome\n"
              << "7. Sair\n"
              << "Escolha uma opção: " << std::flush; // <- aqui
}



Music novaMusicaManual() {
    Music m;
    std::string input;

    std::cout << "ID: ";
    std::getline(std::cin, m.id);

    std::cout << "Nome: ";
    std::getline(std::cin, m.name);

    std::cout << "Artista: ";
    std::getline(std::cin, m.artist);

    std::cout << "País: ";
    std::getline(std::cin, m.country);

    std::cout << "Popularidade (0 a 100): ";
    std::getline(std::cin, input);
    m.popularity = std::stoi(input);

    std::cout << "Duração em ms: ";
    std::getline(std::cin, input);
    m.duration_ms = std::stoi(input);

    std::cout << "Danceability (0 a 1): ";
    std::getline(std::cin, input);
    m.danceability = std::stod(input);

    std::cout << "Energy (0 a 1): ";
    std::getline(std::cin, input);
    m.energy = std::stod(input);

    std::cout << "Tempo (BPM): ";
    std::getline(std::cin, input);
    m.tempo = std::stod(input);

    return m;
}

int main() {
    std::cout << "Iniciando o programa...\n";

    std::vector<Music> musicas = load_music_dataset("dataset/Top_spotify_songs.csv");

    std::cout << "Total de músicas carregadas: " << musicas.size() << "\n";

    if (musicas.empty()) {
        std::cerr << "Erro: Nenhuma música carregada.\n";
        return 1;
    }

    LinkedList lista;
    AVLTree avl;
    HashTable tabela;

    for (const auto& m : musicas) {
        lista.insert(new Music(m));
        avl.insert(m);
        tabela.insert(new Music(m));

    }

    int opcao= 0;
    do {
        mostrarMenu();
        std::cout << "[DEBUG] Menu impresso, aguardando entrada...\n" << std::flush;

        std::string input;
        std::getline(std::cin, input);
        std::stringstream ss(input);
        std::cout << "[DEBUG] Entrada lida: \"" << input << "\"\n";

        if (!(ss >> opcao)) {
            opcao = -1;  // valor inválido
        }

        switch (opcao) {
            case 1:
                lista.print_sample(5);
                break;

            case 2:
                avl.printInOrder();
                break;

            case 3: {
                std::string nome;
                std::cout << "Digite o nome da música: ";
                std::getline(std::cin, nome);
                Music* m = tabela.search(nome);
                if (m)
                    std::cout << "Encontrada: " << m->name << " - " << m->artist << "\n";
                else
                    std::cout << "⚠️ Música não encontrada.\n";
                break;
            }

            case 4: {
                int pop;
                std::cout << "Digite a popularidade da música: ";
                std::cin >> pop;
                std::cin.ignore();
                Music query;
                query.popularity = pop; // você deve ter `int pop;` vindo de input
                query.name = "";        // ou algum nome, se quiser buscar por nome também
                Music* m = avl.search(query);

                if (m)
                    std::cout << "Encontrada: " << m->name << " - " << m->artist << "\n";
                else
                    std::cout << "⚠️ Nenhuma música com essa popularidade.\n";
                break;
            }

            case 5: {
                std::cout << "\n--- Inserção Manual ---\n";
                Music nova = novaMusicaManual();
                lista.insert(new Music(nova));
                avl.insert(nova);
                tabela.insert(new Music(nova));
                std::cout << "✅ Música inserida com sucesso!\n";
                break;
            }

            case 6: {
                std::string nome;
                std::cout << "Digite o nome da música a remover: ";
                std::getline(std::cin, nome);
                Music* m = tabela.search(nome);
                if (m && lista.remove_by_id(m->id)) {
                    std::cout << "✅ Música removida da lista. (AVL e Hash não implementam remoção neste exemplo)\n";
                } else {
                    std::cout << "⚠️ Música não encontrada ou erro ao remover.\n";
                }
                break;
            }

            case 7:
                std::cout << "Encerrando...\n";
                break;

            default:
                std::cout << "Opção inválida!\n";
                break;
        }

    } while (opcao != 7);

    return 0;
}
