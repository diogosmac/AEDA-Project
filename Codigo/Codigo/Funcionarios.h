#pragma once

#include <string>
#include <vector>

#include "EspacosReserva.h"

using namespace std;

class Funcionario {
	
	static size_t nextID;
    string nome;
    size_t ID_Code;

public:

    Funcionario(string nome);
    string getNome() const;
    size_t getID_Code() const;

};

size_t Funcionario::nextID = 0;

class Supervisor : public Funcionario {

    vector<Espaco *> Espacos;

public:

    Supervisor(string nome);
    void AcrescentaEspaco(size_t idEspaco);
    void RemoveEspaco(size_t idEspaco);
	vector<Espaco *> getLocaisResponsavel() const;

};

class EspacoInexistente {   // exception for function RemoveEspaco
    size_t num_ID;
public:
    EspacoInexistente(size_t idEspaco) { num_ID = idEspaco; }
    int getNumID() { return num_ID; }
};