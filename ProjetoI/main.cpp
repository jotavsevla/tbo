#include <iostream>
#include "Classes/Arquivo.h"
#define ARQUIVOFILMES "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoI/arquivosTexto/filmes.txt"
int main() {
    Arquivo filmes(ARQUIVOFILMES);
    filmes.lerArquivo();


    return 0;
}
