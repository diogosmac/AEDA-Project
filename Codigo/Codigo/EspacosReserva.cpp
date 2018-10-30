#include "EspacosReserva.h"

//-----------------------------------------------------------Espaco------------------------------------------------------------//

size_t Espaco::getNumID() const {
	return numID;
}

//-----------------------------------------------------------Quarto------------------------------------------------------------//


Quarto::Quarto(bool QuartoDuplo, bool frente) {

	this->QuartoDuplo = QuartoDuplo;
	this->frente = frente;
}

double Quarto::getPrecoReservaDiario() const {

	return 50; //TO DO
}

bool Quarto::getQuartoDuplo() const {

	return this->QuartoDuplo;
}

//---------------------------------------------------------Sala Reunioes-------------------------------------------------------//

SalaDeReunioes::SalaDeReunioes(int capacidade, bool equipamentoVideo, bool equipamentoAudio) {

	this->capacidade = capacidade;
	this->equipamentoVideo = equipamentoVideo;
	this->equipamentoAudio = equipamentoAudio;
}


double SalaDeReunioes::getPrecoReservaDiario() const {

	return 50; // TO DO
}

int SalaDeReunioes::getCapacidade() const {

	return this->capacidade;
}

bool SalaDeReunioes::getEquipamentoVideo() const {

	return this->equipamentoVideo;
}

bool SalaDeReunioes::getEquipamentoAudio() const {
    
	return this->equipamentoAudio;
}