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
	Date();
	Date(size_t d, size_t m, size_t y);
	Date(string yearMonthDay);
	size_t getDay() const { return day; }
	size_t getMonth() const { return month; }
	size_t getYear() const { return year; }
	string getDate() const;
	void increaseDay();
	size_t numDaysOfMonth();
	size_t dayOfWeek();
	bool operator < (Date date2);
	bool operator > (Date date2);
	bool operator == (Date date2);
	bool validDate ();
	bool bissexto();
	bool isWeekend();
	bool isEpocaAlta();
};


class Espaco 
{
	
    size_t numID;

public:
	Espaco();

	/**
	*	Retorna id do espaço
	*/
    size_t getNumID() const;

	/**
	*	Retorna PrecoReservaDiario = 0€ (Alterado nas classes derivadas)
	*/
	virtual double getPrecoReservaDiario(Date data) const = 0;

	virtual string getOutputString();

	/**
	*	Usado para exportar toda a informação do espaco para ficheiros
	*	Objeto >> ostream
	*/
	friend ostream& operator << (ostream& ofs, Espaco* espaco);

private:
	static size_t nextSpaceID;
};

class Quarto : public Espaco 
{
	bool duplo;
	bool frente;

public:

	/**
	*	Construtor da class Quarto
	*/
	Quarto(bool QuartoDuplo, bool frente);

	/**
	*	Preço normal (por dia): 40€
	*	Se for quarto duplo: Duplica o preço normal
	*	Se for quarto voltado para o lado da frente do hotel: Acrescimo de 30% ao custo diario
	*   Se a reserva for durante a época alta (Maio a Setembro) o valor do custo sobe 20%
	*   Se a reserva for durante o fim de semana o valor do custo aumenta 5%
	*/
	double getPrecoReservaDiario(Date data) const;

	/**
	*	Retorna se o quarto é duplo ou não
	*/
	bool isDuplo() const;

	/**
	*	Retorna se o quarto é voltado para a frente do hotel ou nao
	*/	
	bool isFrente() const;

	/**
	*	Usado para exportar toda a informação do quarto para ficheiros
	*	Objeto >> ostream
	*/
	string getOutputString();

};


class SalaDeReunioes : public Espaco 
{

	int capacidade;
	bool equipamentoVideo; 
	bool equipamentoAudio;

public:

	/**
	*	Construtor da class SalaDeReunioes
	*/
	SalaDeReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio);


	/**
	*	Retorna o preco diario para aluguer da sala de reunioes em questao
	*
	*	Se capacidade < 30 preco diario (base) = 20€
	*	Se capacidade < 50 preco diario (base) = 35€
	*	Se capacidade < 80 preco diario (base) = 50€
	*	Se capacidade < 120 preco diario (base) = 85€
	*	Se capacidade < 200 preco diario (base) = 140€
	*	Se capacidade < 500 preco diario (base) = 250€
	*	Se capacidade > 500 preco diario (base) = 480€
	*	Se tiver equipamento de video, o custo é aumentado em 20%
	*	Se tiver equipamento de audio, o custo é aumentado em 10%
	*   Se a reserva for durante a época alta (Maio a Setembro) o valor do custo sobe 20%
	*   Se a reserva for durante o fim de semana o valor do custo aumenta 5%
	*/
	double getPrecoReservaDiario(Date data) const;

	/**
	*	Retorna a capacidade da sala de reunioes
	*/
	int getCapacidade() const;

	/**
	*	Retorna se a sala de reunioes tem ou não equipamento de video
	*/
	bool getEquipamentoVideo() const;

	/**
	*	Retorna se a sala de reunioes tem ou não equipamento de audio
	*/
	bool getEquipamentoAudio() const;

	/**
	*	Usado para exportar toda a informação da sala de reunioes para ficheiros
	*	Objeto >> ostream
	*/
	string getOutputString();

};
