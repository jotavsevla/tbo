#include "Classes/Menu.h"
#include "Classes/Arquivo.h"
#define ARQUIVOFILME "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoI/arquivosTexto/filmes.txt"
#define ARQUIVOCINEMAS "/Users/jotavsevla/CLionProjects/tbo_2024_01/ProjetoI/arquivosTexto/cinemas.txt"

int main() {
    Arquivo filmes(ARQUIVOFILME, ARQUIVOCINEMAS);
    Menu menu(*filmes.lerArquivo());
    menu.principal();
    return 0;
}
