#pragma once

#include <iostream>
#include "Funcionarios.h"
#include "EspacosReserva.h"
#include "Cliente.h"
#include "Reservas.h"
#include "Restaurante.h"
#include "BST.h"
#include <vector>
#include <string>
#include <fstream>
#include <unordered_set>


using namespace std;

struct clientesHotelHash
{
	int operator()(const Cliente &c1) const
	{
		return c1.getNome().at(0);
	}

	bool operator() (const Cliente &c1, const Cliente &c2) const
	{
		return c1 == c2;
	}
};

typedef unordered_set<Cliente, clientesHotelHash, clientesHotelHash> tabHClientes;

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

	/**
	*	Contem todos os funcionarios do hotel
	*/
	vector<Funcionario *> funcionarios;
	
	/**
	*	Contem todos os clientes do hotel
	*/
	//vector<Cliente *> clientesHotel;
	tabHClientes clientesHotel;
	
	/**
	*	Contem todas as reservas realizadas
	*/
	Reservas todasReservas;

	/**
	*	Arvore binaria de pesquisa com todos os restaurante perto do hotel ordenados (alfabeticamente) pelo tipo de comida que servem e por distancia ao hotel
	*/
	BST<Restaurante> restaurantesProximosHotel;

public:

	/**
	*	Construtor da classe Hotel vazio
	*	@param nome nome que vai ser dado ao hotel
	*/
	Hotel(string nome);

	/**
	*	Retorna o nome do Hotel.
	*/
	string getNomeHotel() const;

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
	*	Retorna um vetor com todos os espaços disponiveis para o intervalo entre as datas passadas como argumento
	*/
	vector<Espaco *> getEspacosDisponiveis(Date data1, Date data2) const;


	/**
	*	Retorna um set com todos os clientes do hotel
	*/
	tabHClientes getClientes() const;

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
	*	Retorna o apontador para o objeto cliente com o id que foi passado por parametro.
	*	Se nao encontrar dá erro, lança a exceção ClienteNaoEncontrado
	*/
	Cliente encontraCliente(size_t id);

	/**
	*	Verifica a idade do cliente. Caso este seja menor de 18 anos, lança a exceção ClienteDemasiadoNovoReserva.
	*	Verifica se o espaço se encontra no vetor de espacos do hotel. Caso isso não se verifique, lança a exceção EspacoNaoPertenceHotel
	*	Se for maior de idade e o espaco pretendido pertencer ao hotel, verifica a disponibilidade do espaço pretendido nas datas pretendidas.
	*	Se o espaco estiver disponivel nas datas pretendidas efetua a reserva, caso contrário lança a exceção EspacoNaoDisponivel.
	*	Retorna TRUE se tiver sucesso, e FALSE se isso não acontecer.
	*/
	bool efetuaReserva(Cliente* cliente, size_t idEspaco, Date inicio, Date fim);

	/**
	*	Efetua reserva de espaco; É utilizada na pela função efutuaReserva; Não faz verificações de disponibilidade;
	*/
	void reservaEspaco(size_t idEspaco, Reserva r1);

	/**
	*	Retorna o numero de reservas efetuadas no Hotel.
	*/
	size_t nReservas();

	/**
	*	Remove reserva do espaco
	*/
	bool removeReserva(size_t idEspaco, Reserva res);

	/**
	*	Distribui os supervisores pelos espaços do hotel
	*/
	void alocaSupervisores();

	/**
	*	Retorna o preco a pagar por uma dada reserva
	*/
	double getPrecoReserva(size_t idEspaco, Reserva res);

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
	*	Mostra na consola toda a informação relativa aos clientes do hotel 
	*/
	void showInfoClientes();

	/**
	*	Mostra na consola toda a informação relativa aos espaços do hotel 
	*/
	void showInfoEspacos();

	/**
	*	Mostra na consola toda a informação relativa as reservas do hotel 
	*/
	void showInfoReservas();

	/**
	*	Mostra na consola toda a informação relativa aos funcionarios do hotel 
	*/
	void showInfoFuncionarios();

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
	*	Importa de um ficheiro de texto um conjunto de Espaços, que são acrescentados ao Hotel
	*	Se conseguir, returna TRUE. Se não, retorna FALSE.
	*/
	bool importInfoEspacos();

	/**
	*	Exporta toda a informação relativa ao hotel, chamando as outras funções de exportação.
	*/
	void exportAllInfo();

	/**
	*	Mostra na consola toda a informação relativa ao hotel, chamando as outras funções de consulta
	*/
	void showAllInfo();

	/**
	*	Importa toda a informação relativa ao hotel, chamando as outras funções de importação.
	*/
	bool importAllInfo();

	/**
	*	Adiciona um resturante a arvore binaria de restaurantes proximos do hotel
	*/
	void addRestaurant(Restaurante r);

	/**
	*	Retorna um vetor com todos os restaurantes proximos do hotel do tipo de cozinha pretendido
	*/
	vector<Restaurante> getRestaurantesDoTipo(string tipoCozinha);

	/**
	*	Retorna um vetor com todos os restaurantes proximos do hotel a cerca de n metros (argumento) ou menos
	*/
	vector<Restaurante> getRestaurantesNMetros(double n);

	/**
	*	Exporta toda a informacao relativa aos restaurantes proximos do hotel
	*/
	void exportInfoRestaurantes();

	/**
	*	Importa toda a informacao relativa aos restaurantes proximos do hotel
	*/
	bool importInfoRestaurantes();
	
};
