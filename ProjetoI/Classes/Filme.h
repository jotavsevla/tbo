//
// Created by João on 18/07/24.
//

#ifndef TBO_2024_01_FILME_H
#define TBO_2024_01_FILME_H

#include "string"
#include "vector"
#include "utility"
#include "string"
#include "iostream"
#define INICIAL 7917520 // primeiro filme AKA base da hash
using namespace std;

class Filme {
private:
int codeId, startYear, endYear, runTimeMinutes, typeMask;
string tipo, namePrimary, nameOriginal;
vector<string> genres;
bool itsAdult;

public:
Filme(string t_const, string tipo, string namePrimary,
      string nameOriginal, bool itsAdult, int startYear,
      int endYear, int runTimeMinutes, vector<string> genres)
        : tipo(tipo), namePrimary(namePrimary),
          nameOriginal(nameOriginal), itsAdult(itsAdult),
          startYear(startYear), endYear(endYear),
          runTimeMinutes(runTimeMinutes), genres(genres), codeId(hashFilme(t_const)){}
int getCodeId() const { return codeId; }
string getTipo() const { return tipo; }
string getNamePrimary() const { return namePrimary; }
string getNameOriginal() const { return nameOriginal; }
bool isAdult() const { return itsAdult; }
int getStartYear() const { return startYear; }
int getEndYear() const { return endYear; }
int getRunTimeMinutes() const { return runTimeMinutes; }
int hashFilme(string t_const) {
    // Supondo que o código de identidade do filme comece com "tt", vamos extrair o número após "tt"
    string numero_str = t_const.substr(2);  // Remove os dois primeiros caracteres "tt"
    int index = stoi(numero_str);  // Converte a parte numérica para inteiro
    // Calcular o índice sequencial com base na diferença em relação ao primeiro filme
    index = (index - INICIAL) / 2;  // Calcula o índice sequencial conforme a fórmula
    return index;
}
};


#endif //TBO_2024_01_FILME_H
