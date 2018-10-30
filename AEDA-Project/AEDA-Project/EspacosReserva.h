#pragma once

class espaco
{
	virtual double getPrecoReservaDiario() const;
};

class quarto : public espaco
{
	bool quartoDuplo;

public:

	quarto(bool quartoDuplo);
	double getPrecoReservaDiario() const;
	bool getQuartoDuplo()const;
};

class salaReunioes : public espaco
{
	int capacidade;
	bool equipamentoVideo;
	bool equipamentoAudio;

public:

	salaReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio);
	double getPrecoReservaDiario() const;
	int getCapacidade() const;
	bool getEquipamentoVideo() const;
	bool getEquipamentoAudio() const;
};