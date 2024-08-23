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
int codeId, startYear, endYear, runTimeMinutes;
string type, namePrimary, nameOriginal;
string genres;
bool itsAdult;

public:
Filme(int codeId,string type,string namePrimary,string nameOriginal,bool itsAdult,int startYear,int endYear,int runTimeMinutes,string genres){
        this->type = type;
        this->namePrimary = namePrimary;
        this->nameOriginal = nameOriginal;
        this->itsAdult = itsAdult;
        this->startYear = startYear;
        this->endYear = endYear;
        this->runTimeMinutes = runTimeMinutes;
        this->genres = genres;
        this->codeId = codeId;
}
int getCodeId()  { return codeId; }
string getType()  { return type; }
string getGenres() { return genres;}
string getNamePrimary()  { return namePrimary; }
string getNameOriginal()  { return nameOriginal; }
bool isAdult() { return itsAdult; }
int getStartYear() { return startYear; }
int getEndYear() { return endYear; }
int getRunTimeMinutes() { return runTimeMinutes; }
void setCodeId(int codeId){
    this->codeId = codeId;
}
};


#endif //TBO_2024_01_FILME_H
