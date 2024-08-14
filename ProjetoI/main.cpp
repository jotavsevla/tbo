#include <iostream>
#include "Classes/Menu.h"
#include "Classes/Arquivo.h"
#define ARQUIVOFILMES "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoI/arquivosTexto/filmes.txt"
int main() {
    Arquivo filmes(ARQUIVOFILMES);
    filmes.lerArquivo();
    Menu menu;
    vector<int> codeIds = menu.menuPrincipal();

    for (int i = 0; i < codeIds.size(); i++) filmes.getFilmePorId(codeIds[i]);


    return 0;
}
