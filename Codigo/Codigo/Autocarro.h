#pragma once

#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Autocarro
{
	/**
	*	Numero que identifica o autocarro
	*/
	size_t id;

	/**
	*	Lotação máxima do autocarro
	*/
	size_t nLugares;

	/**
	*	Contem por cada lugar, o nome da pessoa a que o mesmo foi atribuido
	*/
	vector<string> lugares;

	/**
	*	Numero de lugares que seja se encontram ocupados por alguem neste autocarro
	*/
	size_t nLugaresOcupados;

public:

	/**
	* Construtor da class Autocarro
	*/
	Autocarro(size_t id, size_t nLugares);

	/**
	*	Retorna o numero de lugares livres no autocarro
	*/
	size_t getNLugaresLivres() const;

	/**
	*	Retorna o id do autocarro
	*/
	size_t getID() const;

	/**
	*	Retorna o numero de lugares que o autocarro tem (no total)
	*/
	size_t getCapacidade();

	/**
	*	Incrementa o numnero de lugares ocupados
	*/
	void incNLugaresOcupados();

	/**
	*	Retorna o numero de lugares livres
	*/
	size_t getNLugaresOcupados()const;

	/**
	*	Tenta adicionar n pessoas (e respetivos nomes), se conseguir retorna true, caso contrario, retorna false
	*/
	bool adicionaNPessoas(size_t n);

	/**
	*	Operador usado para as filas de prioridade
	*/
	bool operator < (const Autocarro &a) const;

	/**
	*	Operador usado para exportar as informacoes do autocarro para um ficheiro de texto
	*/
	friend ostream& operator << (ostream& ofs, Autocarro a);

	/**
	*	Altera o numero de lugares para o valor passado por argumento. Usado para importar info de ficheiros de texto.
	*/
	void setNLugares(size_t n);

	/**
	*	Altera o valor de id para o passado por argumento. Usado para importar info de ficheiros de texto.
	*/
	void setId(size_t newID);

	/**
	*	Altera o nome da pessoa no lugar de indice index para aquele passado por argumento.
	*/
	void setNameAt(size_t posicaoLugar, string nome);

	/**
	*	Apaga todos os nomes que se encontravam nos lugares do autocarro. Esvazia o autocarro.
	*/
	void clearLugares();
};
