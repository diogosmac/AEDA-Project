#include "Hotel.h"

Hotel::Hotel(istream &ficheiro) {

	cout << endl;

	string line;
	while (getline(ficheiro, line)) {
		size_t index = line.find_first_of(';');
		string tipoEspaco = line.substr(0, index);
		string dado1 = line.substr(index + 1, line.find(';', index + 1) - index - 1);
		index = line.find(';', index + 1) - index - 1;

		if (tipoEspaco == "Quarto") {
			string dado2 = line.substr(index + 1);

			bool duplo = true;
			bool frente = true;
			if (dado1.at(0) == '-') duplo = false;
			if (dado2.at(0) == '-') frente = false;
			Espaco* e = new Quarto(duplo, frente);
			todosEspacos.push_back(e);
			cout << "Quarto (numero " << e->getNumID() << ") adicionado.\n";
		}
		else if (tipoEspaco == "SalaDeReunioes") {
			string dado2 = line.substr(index + 1, line.find(';', index + 1) - index - 1);
			index = line.find(';', index + 1) - index - 1;
			string dado3 = line.substr(index + 1);

			bool video = true;
			bool audio = true;
			int cap = stoi(dado1);
			if (dado2.at(0) == '-') video = false;
			if (dado3.at(0) == '-') audio = false;
			Espaco* e = new SalaDeReunioes(cap, video, audio);
			todosEspacos.push_back(e);
			cout << "Sala de Reunioes (numero " << e->getNumID() << ") adicionada.\n";
		}
		else {
			cout << "Linha inválida, nenhum espaço foi adicionado.\n";
		}
	}

	cout << endl;
}

size_t Hotel::nEspacos() const {
	return this->todosEspacos.size();
}

vector<Espaco *> Hotel::getTodosEspacos() const
{
	return this->todosEspacos;
}

vector<Cliente *> Hotel::getClientes() const {
	return this->clientesHotel;
}

vector<Espaco *> Hotel::getEspacosDisponiveis(Date data) const
{
	vector<Espaco *> disp;
	for (size_t i = 0; i < todosEspacos.size(); i++) {
		if (!(this->todasReservas.verificaEspaco(todosEspacos[i]->getNumID(), data)))
			disp.push_back(todosEspacos[i]);
	}
	return disp;
}

vector<Funcionario *> Hotel::getFuncionarios() const
{
	return this->funcionarios;
}

double Hotel::nEspacosDisponiveis(Date data)
{
	double contador = 0;
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		if ( !( this->todasReservas.verificaEspaco(todosEspacos[i]->getNumID(), data) ) )
			contador++;
	}
	return contador;
}

double Hotel::lotacao(Date data)
{
	return (this->nEspacosDisponiveis(data) / this->todosEspacos.size()) * 100;
}

// void Hotel::adicionaEspacoOcupado(Espaco * espaco)
// {
// 	this->todosEspacos.push_back(espaco);
// }

void Hotel::adicionaEspaco(Espaco * espaco)
{
	this->todosEspacos.push_back(espaco);
	todasReservas.updateReservas(espaco);

}

void Hotel::adicionaFuncionario(Funcionario * func)
{
	this->funcionarios.push_back(func);
	/*if (func->isSupervisor())
		this->supervisores.push_back(func);*/
}


void Hotel::removeEspaco(size_t numID)
{
	bool encontrado = false;

	// Remove do vetor todosEspacos. Caso nao encontre, da erro.
	for (size_t i = 0; i < this->todosEspacos.size(); i++)
	{
		if (todosEspacos.at(i)->getNumID() == numID)
		{
			if (!(todasReservas.temReservas(numID)))
			{
				todosEspacos.erase(todosEspacos.begin() + i);
				encontrado = true;
				todasReservas.removeEspaco(numID);
				break;
			}
		}
	}

	if (!encontrado)
	{
		throw EspacoNaoPertenceHotel(numID);
	}
}

void Hotel::removeFuncionario(size_t ID_Code)
{
	bool encontrado = false;

	// Remove funcionario. Caso nao o encontre, d� erro.
	for (size_t i = 0; i < this->funcionarios.size(); i++)
	{
		if (funcionarios.at(i)->getID_Code() == ID_Code)
		{
			funcionarios.erase(funcionarios.begin() + i);
			encontrado = true;
			break;
		}
	}

	if (!encontrado)
	{
		throw FuncionarioNaoTrabalhaHotel(ID_Code);
	}
}

size_t Hotel::nClientes() const
{
	return this->clientesHotel.size();
}

void Hotel::removeCliente(string nome, size_t idCliente)
{
	bool encontrado = false;

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if ((this->clientesHotel.at(i)->getNome() == nome) && (this->clientesHotel.at(i)->getIDCliente() == idCliente))
		{
			encontrado = true;
			this->clientesHotel.erase(this->clientesHotel.begin() + i);
		}
	}

	if (!encontrado)
	{
		throw ClienteNaoEncontrado(nome);
	}
}

bool Hotel::verificaCliente(string nome, size_t idade)
{
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome && this->clientesHotel.at(i)->getIdade() == idade)
		{
			return true;
		}
	}

	return false;
}

int Hotel::idCliente(string nome, size_t idade) {

	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (this->clientesHotel.at(i)->getNome() == nome && this->clientesHotel.at(i)->getIdade() == idade)
		{
			return clientesHotel.at(i)->getIDCliente();
		}
	}

	return -1;
}

void Hotel::adicionaCliente(string nome, size_t idade)
{
	if (!verificaCliente(nome, idade))
	{
		Cliente *c1 = new Cliente(nome, idade);
		this->clientesHotel.push_back(c1);
	}
}

Cliente * Hotel::encontraCliente(string nome) {
	for (size_t i = 0; i < clientesHotel.size(); i++) {
		if (clientesHotel.at(i)->getNome() == nome) {
			return clientesHotel.at(i);
		}
	}
	throw ClienteNaoEncontrado(nome);
}

void Hotel::efetuaReserva(Cliente* cliente, size_t idEspaco, Date inicio, Date fim) {
	if (cliente->getIdade() < 18) {
		throw ClienteDemasiadoNovoReserva(cliente);
	}

	bool espacoExiste = false;
	for (size_t i = 0; i < todosEspacos.size(); i++) {
		if (todosEspacos[i]->getNumID() == idEspaco)
			espacoExiste = true;
	}
	if (!espacoExiste) {
		throw EspacoNaoPertenceHotel(idEspaco);
	}

	bool espacoDisponivel = true;
	Reserva res(cliente->getIDCliente(), inicio, fim);
	for (size_t i = 0; i < todasReservas.returnReservas().at(idEspaco).size(); i++) {
		if (res - todasReservas.returnReservas().at(idEspaco).at(i))
			espacoDisponivel = false;
	}
	if (!espacoDisponivel) {
		throw EspacoNaoDisponivel(idEspaco);
	}
	else {
		reservaEspaco(idEspaco, res);
	}
}

void Hotel::reservaEspaco(size_t idEspaco, Reserva res) {
	if (!todasReservas.adicionaReserva(idEspaco, res)) {
		cout << "Algo correu mal. A reserva não pôde ser efetuada.\n";
	}
	else {
		cout << "Reserva efetuada com sucesso!\n";
		cout << "Espaco reservado: " << idEspaco << '\t' << res << '\n';
	}
}

void Hotel::alocaSupervisores() {
	for (size_t i = 0; i < supervisores.size(); i++) {
		supervisores.at(i)->RemoveEspacos();
	}

	for (size_t i = 0, j = 0; i < todosEspacos.size(); i++, j++) {
		if (j == supervisores.size()) {
			j = 0;
		}
		supervisores.at(j)->AcrescentaEspaco(todosEspacos.at(i));
	}
}

void Hotel::exportInfo()
{
	ofstream ficheiro;

	string nomeFicheiro;

	cout << "Escreva o nome do ficheiro de texto onde pretende guardar os dados" << endl;
	cout << "Nota: Caso o ficheiro com nome inserido ja existir, o mesmo sera substituido pelo novo" << endl;


	cin >> nomeFicheiro;

	if (nomeFicheiro.length() < 4 || nomeFicheiro.substr(nomeFicheiro.length() - 4, 4) != ".txt") {
		nomeFicheiro += ".txt";
	}

	ficheiro.open(nomeFicheiro);

	cin.ignore(9999999, '\n');
	cin.clear();

	if (!ficheiro.is_open())
	{
		cerr << "Erro opening file!" << endl;
		return;
	}

	//Escreve todos os clientes
	for (size_t i = 0; i < this->clientesHotel.size(); i++)
	{
		if (i == this->clientesHotel.size() - 1)
		{
			ficheiro << clientesHotel.at(i);
			ficheiro << '\n';
			cout << "Toda a informacao relativa aos clientes foi guardada com sucesso!" << endl;
		}
		else
		{
			ficheiro << clientesHotel.at(i);
		}
	}

}
