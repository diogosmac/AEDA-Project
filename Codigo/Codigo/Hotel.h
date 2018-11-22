#pragma once

#include <iostream>
#include "Funcionarios.h"
#include "EspacosReserva.h"
#include "Cliente.h"
#include "Reservas.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Hotel
{
	/**
	*	Contem o nome do hotel
	*/
	string nomeHotel;

	/**
	*	Contem todos os espacos que pertencem ao hotel
	*/
	vector<Espaco *> todosEspacos;

	//vector<Espaco *> espacosDisponiveis; // Contem todos os espacos que se encontram disponiveis
	
	/**
	*	Contem todos os funcionarios do hotel
	*/
	vector<Funcionario *> funcionarios;
	
	/**
	*	Contem todos os clientes do hotel
	*/
	vector<Cliente *> clientesHotel; // Contem todos os clientes do hotel
	
	/**
	*	Contem todas as reservas realizadas
	*/
	Reservas todasReservas;

public:

	/**
	*	Construtor da classe Hotel
	*	Retira a informação necessária à inicialização do objeto de um ficheiro
	*	@param nome nome que vai ser dado ao hotel
	*	@param ficheiro ficheiro de onde é retirada a informação
	*/
	Hotel(string nome, istream &ficheiro);

	/**
	*	Retorna o número de espaços que pertencem ao hotel
	*/
	size_t nEspacos() const;

	/**
	*	Retorna um vetor com todos os espaços que pertencem ao hotel
	*/
	vector<Espaco *> getTodosEspacos() const;

	/**
	*	Retorna um vetor com todos os espaços disponiveis para a data passada como argumento
	*/
	vector<Espaco *> getEspacosDisponiveis(Date data) const;

	/**
	*	Retorna um vetor com todos os clientes do hotel
	*/
	vector<Cliente *> getClientes() const;

	/**
	*	Retorna um vetor com todos os funcionarios (e supervisores) do hotel
	*/
	vector<Funcionario *> getFuncionarios() const;

	/**
	*	Retorna um objeto do tipo Reservas, com todas as reservas do hotel
	*/
	Reservas getReservas() const;


	/**
	*	Retorna o número de espaços disponíveis no hotel na data passada como argumento
	*/
	double nEspacosDisponiveis(Date data);

	/**
	*	Retorna a lotação do hotel (em percentagem) na data passada como argumento
	*/
	double lotacao(Date data);


	// void adicionaEspacoOcupado(Espaco * espaco); // Adiciona um espaco ao hotel (nao disponivel)


	/**
	*	Adiciona um espaço ao vetor de espaços do hotel
	*/
	void adicionaEspaco(Espaco * espaco);

	/**
	*	Adiciona um funcionario ao vetor de funcionarios que trabalham no hotel
	*/
	void adicionaFuncionario(Funcionario * func);

	/**
	*	Remove um espaço do vetor de espaços do hotel
	*/
	void removeEspaco(size_t numID);

	/**
	*	Remove um funcionario do vetor de funcionarios do hotel
	*/
	void removeFuncionario(size_t ID_Code);

	/**
	*	Retorna o numero de clintes do hotel
	*/
	size_t nClientes() const;

	/**
	*	Procura pelo cliente de nome e idade passados por argumento no vetor clientes. 
	*	Se o encontrar, retorna true, caso contrário, retorna false
	*/
	bool verificaCliente(string nome, size_t idade);

	/**
	*	Retorna o id do clinte
	*/
	int idCliente(string nome, size_t idade);

	/**
	*	Adiciona um cliente de nome e idade passados em argumento, caso este não exista no vetor clientes
	*/
	void adicionaCliente(string nome, size_t idade);

	/**
	*	Remove do vetor clientesHotel o cliente de nome e id passados por argumento.
	*	Caso este não seja encontrado, lança a exceção ClienteNaoEncontrado
	*/
	void removeCliente(string nome, size_t idCliente);

	/**
	*	Retorna o apontador para o objeto cliente com o nome que foi passado por parametro.
	*	Se nao encontrar dá erro, lança a exceção ClienteNaoEncontrado
	*/
	Cliente * encontraCliente(string nome);

	/**
	*	Verifica a idade do cliente. Caso este seja menor de 18 anos, lança a exceção ClienteDemasiadoNovoReserva.
	*	Verifica se o espaço se encontra no vetor de espacos do hotel. Caso isso não se verifique, lança a exceção EspacoNaoPertenceHotel
	*	Se for maior de idade e o espaco pretendido pertencer ao hotel, verifica a disponibilidade do espaço pretendido nas datas pretendidas.
	*	Se o espaco estiver disponivel nas datas pretendidas efetua a reserva, caso contrário lança a exceção EspacoNaoDisponivel.
	*/
	void efetuaReserva(Cliente* cliente, size_t idEspaco, Date inicio, Date fim);

	/**
	*	Efetua reserva de espaco; É utilizada na pela função efutuaReserva; Não faz verificações de disponibilidade;
	*/
	void reservaEspaco(size_t idEspaco, Reserva r1);

	/**
	*	Distribui os supervisores pelos espaços do hotel
	*/
	void alocaSupervisores();

	/**
	*	Exporta toda a informação relativa aos clientes do hotel para um ficheiro de texto
	*/
	void exportInfoClientes();

	/**
	*	Exporta toda a informação relativa aos espaços do hotel para um ficheiro de texto
	*/
	void exportInfoEspacos();

	/**
	*	Exporta toda a informação relativa as reservas do hotel para um ficheiro de texto
	*/
	void exportInfoReservas();

	/**
	*	Exporta toda a informação relativa aos funcionarios do hotel para um ficheiro de texto
	*/
	void exportInfoFuncionarios();

	/**
	*	Importa de um ficheiro de texto um conjunto de Clientes, que são adicionados ao Hotel
	*	Se conseguir, retorna TRUE. Se não, retorna FALSE.
	*/
	bool importInfoClientes();

	/**
	*	Importa de um ficheiro de texto um conjunto de Reservas, que são colocadas nos Espaços do Hotel
	*	Se conseguir, retorna TRUE. Se não, retorna FALSE.
	*/
	bool importInfoReservas();

	/**
	*	Importa de um ficheiro de texto um conjunto de Funcionários, que são distribuídos pelos Espaços do Hotel
	*	Se conseguir, retorna TRUE. Se não, retorna FALSE.
	*/
	bool importInfoFuncionarios();

	/**
	*	Exporta toda a informação relativa ao hotel, chamando as outras funções de exportação.
	*/
	void exportAllInfo();

	/**
	*	Importa toda a informação relativa ao hotel, chamando as outras funções de importação.
	*/
	void importAllInfo();
};
