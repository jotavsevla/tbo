//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <string>
//#include <vector>

using namespace std;

class Menu {

private:
    int escolha;

public:
    void menuPrincipal(){
        cout << "### FILTROS ###";
        cout << endl << endl;
        cout << "1 - Filmes" << endl;
        cout << "2 - Cinemas" << endl << endl;
        cout << "Escolha: ";
        cin >> this->escolha;

        //if(this->escolha == 1) menuFilme();
        //else if(this->escolha) menuCinema();
        //else menuPrincipal();
    }



    //return 0;
};
