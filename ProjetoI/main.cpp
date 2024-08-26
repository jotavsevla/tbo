#include "Classes/Menu.h"
#include "Classes/Arquivo.h"
#define ARQUIVOFILME "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoI/arquivosTexto/filmes.txt"
#define ARQUIVOCINEMAS "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoI/arquivosTexto/cinemas.txt"

int main() {
    Arquivo dataLoader(ARQUIVOFILME, ARQUIVOCINEMAS);
    Menu menu(*dataLoader.lerArquivo());
    menu.principal();
    dataLoader.filmes.clear();
    dataLoader.cinemas.clear();
    dataLoader.clearAll();
    return 0;
}
