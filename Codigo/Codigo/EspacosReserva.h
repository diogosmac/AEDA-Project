#pragma once

class Espaco 
{
	
    size_t numID;

public:
	Espaco();
    size_t getNumID() const;
	virtual double getPrecoReservaDiario() const = 0;

private:
	static size_t nextSpaceID;

};

class Quarto : public Espaco 
{

	bool duplo;
	bool frente;

public:

	Quarto(bool QuartoDuplo, bool frente);
	double getPrecoReservaDiario() const;
	bool isDuplo() const;
	bool isFrente() const;
};

class SalaDeReunioes : public Espaco 
{

	int capacidade;
	bool equipamentoVideo;
	bool equipamentoAudio;

public:

	SalaDeReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio);
	double getPrecoReservaDiario() const;
	int getCapacidade() const;
	bool getEquipamentoVideo() const;
	bool getEquipamentoAudio() const;
};
