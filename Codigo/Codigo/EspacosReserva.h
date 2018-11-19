#pragma once

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Date
{
	size_t day;
	size_t month;
	size_t year;

public:

	Date(size_t d, size_t m, size_t y);
	size_t getDay() const { return day; }
	size_t getMonth() const { return month; }
	size_t getYear() const { return year; }
	string getDate() const;
};


class Espaco 
{
	
    size_t numID;

public:
	Espaco();
    size_t getNumID() const;
	virtual double getPrecoReservaDiario() const = 0;
	virtual ostream& operator >> (ostream& ofs);

private:
	static size_t nextSpaceID;
};

class Quarto : public Espaco 
{
	//Preço normal (por dia): 40€
	bool duplo; //Duplica o preço normal
	bool frente; //Acrescimo de 30% ao custo diario

public:

	Quarto(bool QuartoDuplo, bool frente);
	double getPrecoReservaDiario() const;
	bool isDuplo() const;
	bool isFrente() const;
	ostream& operator >> (ostream& ofs);
};


class SalaDeReunioes : public Espaco 
{

	int capacidade;
	bool equipamentoVideo; 
	bool equipamentoAudio;

public:

	/**
		Construtor da class SalaDeReunioes
	*/
	SalaDeReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio);


	/**
		Retorna o preco diario para aluguer da sala de reunioes em questao

		Se capacidade < 30 preco diario (base) = 20€
		Se capacidade < 50 preco diario (base) = 35€
		Se capacidade < 80 preco diario (base) = 50€
		Se capacidade < 120 preco diario (base) = 85€
		Se capacidade < 200 preco diario (base) = 140€
		Se capacidade < 500 preco diario (base) = 250€
		Se capacidade > 500 preco diario (base) = 480€
		Se tiver equipamento de video, o custo é aumentado em 20%
		Se tiver equipamento de audio, o custo é aumentado em 10%
	*/
	double getPrecoReservaDiario() const;

	/**
		Retorna a capacidade da sala de reunioes
	*/
	int getCapacidade() const;

	/**
		Retorna se a sala de reunioes tem ou não equipamento de video
	*/
	bool getEquipamentoVideo() const;

	/**
		Retorna se a sala de reunioes tem ou não equipamento de audio
	*/
	bool getEquipamentoAudio() const;

	/**
		Usado para exportar toda a informação da sala de reunioes para ficheiros
	*/
	ostream& operator >> (ostream& ofs);
};
