#include "EspacosReserva.h"

//----------------------------------------------------------Espaço-------------------------------------------------------------//


double espaco::getPrecoReservaDiario() const
{
	return 50; //TO DO
}

//-----------------------------------------------------------Quarto------------------------------------------------------------//


quarto::quarto(bool quartoDuplo)
{
	this->quartoDuplo = quartoDuplo;
}

double quarto::getPrecoReservaDiario() const
{
	return 50; //TO DO
}

bool quarto::getQuartoDuplo()const
{
	return this->quartoDuplo;
}

//---------------------------------------------------------Sala Reunioes-------------------------------------------------------//

salaReunioes::salaReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio)
{
	this->capacidade = capacidade;
	this->equipamentoVideo = equipamentoVideo;
	this->equipamentoAudio = equipamentoAudio;
}


double salaReunioes::getPrecoReservaDiario() const
{
	return 50; // TO DO
}

int salaReunioes::getCapacidade() const
{
	return this->capacidade;
}

bool salaReunioes::getEquipamentoVideo() const
{
	return this->equipamentoVideo;
}

bool salaReunioes::getEquipamentoAudio() const
{
	return this->equipamentoAudio;
}