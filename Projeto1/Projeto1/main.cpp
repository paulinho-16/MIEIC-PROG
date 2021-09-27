#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

struct Agency
{
	std::string nome, morada, url, nif, ficheiro_pacotes, ficheiro_clientes;
};

struct Client
{
	std::string nome, nif, n_familiares, morada;
	std::vector<std::string> pacotes;
};

struct Date
{
	std::string ano, mes, dia;
};

struct TravelPack
{
	std::string identificador,data_inicio,data_fim,preco,n_maximo,n_vendidos,locais;
	Date dat_inicio, dat_fim;
};

struct Adress
{
	std::string rua, porta, andar, codigo_postal, localidade;
};

bool Ficheiro_existe(std::string ficheiro)		// Verifica se o ficheiro existe
{
	std::ifstream ler_ficheiro(ficheiro);
	if (!ler_ficheiro.good())
		return false;
	return true;
}	

Agency Ler_Agency(std::string ficheiro)		// Armazena informacoes do ficheiro da agencia
{
	Agency Agencia;
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	std::getline(ler_ficheiro, Agencia.nome);
	getline(ler_ficheiro, Agencia.nif);
	std::getline(ler_ficheiro, Agencia.url);
	std::getline(ler_ficheiro, Agencia.morada);
	std::getline(ler_ficheiro, Agencia.ficheiro_clientes);
	std::getline(ler_ficheiro, Agencia.ficheiro_pacotes);
	ler_ficheiro.close();
	return Agencia;
}

std::vector<Client> Ler_Clientes(std::string ficheiro)	// Armazena informacoes do ficheiro dos clientes
{
	std::vector<Client> Clientes;
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	while (!ler_ficheiro.eof())
	{
		Client novo_cliente;
		std::string s_pacotes;
		getline(ler_ficheiro, novo_cliente.nome);
		getline(ler_ficheiro, novo_cliente.nif);
		getline(ler_ficheiro, novo_cliente.n_familiares);
		getline(ler_ficheiro, novo_cliente.morada);
		getline(ler_ficheiro, s_pacotes);
		std::string pacote = "";
		for (size_t i = 0; i < s_pacotes.length(); i++)
		{
			if (s_pacotes[i] == ';')
			{
				pacote = std::to_string(stoi(pacote));
				novo_cliente.pacotes.push_back(pacote);
				pacote = "";
				continue;
			}
			pacote += s_pacotes[i];
			if (i == s_pacotes.length() - 1)
			{
				pacote = std::to_string(stoi(pacote));
				novo_cliente.pacotes.push_back(pacote);
			}
		}
		std::string separacao;
		std::getline(ler_ficheiro, separacao);
		if (novo_cliente.nome == "" && novo_cliente.nif == "")
			continue;
		Clientes.push_back(novo_cliente);
	}
	ler_ficheiro.close();
	return Clientes;
}

std::string Ler_Pacotes(std::string ficheiro,std::vector<TravelPack> &Pacotes)		// Armazena informacoes do ficheiro dos pacotes
{
	Pacotes.resize(0);
	std::ifstream ler_ficheiro;
	std::string ultimo_pacote_criado,nova_string = "";
	std::vector<std::string> adicionar;
	ler_ficheiro.open(ficheiro);
	getline(ler_ficheiro, ultimo_pacote_criado);
	while (!ler_ficheiro.eof())
	{
		TravelPack novo_pacote;
		getline(ler_ficheiro, novo_pacote.identificador);
		getline(ler_ficheiro, novo_pacote.locais);
		getline(ler_ficheiro, novo_pacote.data_inicio);
		getline(ler_ficheiro, novo_pacote.data_fim);
		getline(ler_ficheiro, novo_pacote.preco);
		getline(ler_ficheiro, novo_pacote.n_maximo);
		getline(ler_ficheiro, novo_pacote.n_vendidos);
		std::string separacao;
		getline(ler_ficheiro, separacao);
		Pacotes.push_back(novo_pacote);
	}
	ler_ficheiro.close();
	return ultimo_pacote_criado;
}

bool Sair_Programa()		// Permite que o Cliente decida se quer sair ou nao do programa
{
	bool certo = true;
	std::string opcao;
	while (certo)
	{
		std::cout << "\nDeseja sair do programa? (S/N) R: ";
		getline(std::cin, opcao);
		if (opcao == "S" || opcao == "s")
			return true;
		else if (opcao == "N" || opcao == "n")
			return false;
		else
		{
			std::cout << "\nOpcao Invalida!\n";
		}
	}
}

void Normalizar_Nome(std::string &nome)		// Normaliza os nomes
{
	nome = nome.substr(nome.find_first_not_of(' '));
	nome = nome.substr(0, nome.find_last_not_of(' ') + 1);
	nome += " ";
	std::vector<std::string> nomes;
	while (nome.length() != 0)
	{
		nome.erase(0, nome.find_first_not_of(' '));
		std::string n = nome.substr(nome.find_first_not_of(' '), nome.find_first_of(' ') + 1);
		n[0] = toupper(n[0]);
		for (unsigned int j = 1; j < n.length(); j++)
			n[j] = tolower(n[j]);
		nomes.push_back(n);
		nome.erase(0, nome.find_first_of(' ') + 1);
	}
	nome = "";
	for (unsigned int i = 0; i < nomes.size(); i++)
		nome += nomes[i];
	nome = nome.substr(0, nome.length() - 1);
}

Adress Adicionar_Morada()		// Cria uma Morada
{
	Adress morada;
	std::cout << "\nIntroduza o nome da rua do cliente: ";
	getline(std::cin, morada.rua);
	std::cout << "\nIntroduza o numero da porta do cliente: ";
	getline(std::cin, morada.porta);
	std::cout << "\nIntroduza o numero do andar do cliente, introduzir o caracter '-' se nao aplicavel: ";
	getline(std::cin, morada.andar);
	std::cout << "\nIntroduza o codigo-postal do cliente: ";
	getline(std::cin, morada.codigo_postal);
	std::cout << "\nIntroduza a localidade do cliente:  ";
	getline(std::cin, morada.localidade);
	return morada;
}

void Escrever_Ficheiro_Clientes(std::string ficheiro,const std::vector<Client> &clientes)		// Atualiza os dados do ficheiro dos clientes
{
	std::ofstream escrever_ficheiro;
	//std::ifstream ler_ficheiro;
	//ler_ficheiro.open(ficheiro);
	//if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	//{
	//	std::cout << "\nNao existem clientes disponiveis!\n";
	//	return;
	//}
	//ler_ficheiro.close();
	escrever_ficheiro.open(ficheiro, std::ofstream::out | std::ofstream::trunc);
	for (size_t i = 0; i < clientes.size(); i++)
	{
		if (i != 0)
			escrever_ficheiro << "\n::::::::::\n";
		escrever_ficheiro << clientes[i].nome << '\n' << clientes[i].nif << '\n' << clientes[i].n_familiares << '\n' << clientes[i].morada << '\n';
		for (size_t j = 0; j < clientes[i].pacotes.size(); j++)
		{
			if (j == clientes[i].pacotes.size() - 1)
				escrever_ficheiro << clientes[i].pacotes[j];
			else
				escrever_ficheiro << clientes[i].pacotes[j] << " ; ";
		}
	}
	escrever_ficheiro.close();
}

void Escrever_Ficheiro_Pacotes(std::string ficheiro, std::string ultimo, std::vector<TravelPack> &pacotes)		// Atualiza os dados do ficheiro dos pacotes
{
	std::ofstream escrever_ficheiro;
	escrever_ficheiro.open(ficheiro, std::ofstream::out | std::ofstream::trunc);
	escrever_ficheiro << ultimo << std::endl;
	for (size_t i = 0; i < pacotes.size(); i++)
	{
		if (i != 0)
			escrever_ficheiro << "\n::::::::::\n";
		escrever_ficheiro << pacotes[i].identificador << '\n' << pacotes[i].locais << '\n' << pacotes[i].data_inicio << '\n' << pacotes[i].data_fim << '\n' << pacotes[i].preco << '\n' << pacotes[i].n_maximo << '\n' << pacotes[i].n_vendidos;
	}
	escrever_ficheiro.close();
}

void Adicionar_Cliente(std::string ficheiro, std::vector<Client> &clientes)      // Adicionar Novo Cliente
{	
	system("CLS");
	std::cout << "\n\t\t\t\t\t\tAdicionar Cliente";
	Client Cliente;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "\n\nIntroduza o nome do cliente: ";
	getline(std::cin, Cliente.nome);
	Normalizar_Nome(Cliente.nome);
	std::cout << "\nIntroduza o nif do cliente: ";
	getline(std::cin, Cliente.nif);
	std::cout << "\nIntroduza o numero de familiares do cliente: ";
	getline(std::cin, Cliente.n_familiares);
	Adress Morada = Adicionar_Morada();
	Cliente.morada = Morada.rua + " / " + Morada.porta + " / " + Morada.andar + " / " + Morada.codigo_postal + " / " + Morada.localidade;
	Cliente.pacotes.push_back("0");
	clientes.push_back(Cliente);
	Escrever_Ficheiro_Clientes(ficheiro, clientes);
}

void Alterar_Cliente(std::string ficheiro,std::vector<Client> &clientes)		// Alterar os dados de um determinado cliente
{
	system("CLS");
	std::cout << "\n\t\t\t\t\t\tAlterar Cliente";
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	bool encontrar = true;
	int indice = -1;
	std::cout << "\nClientes: \n\n";
	for (size_t l = 0; l < clientes.size(); l++)
		std::cout << clientes[l].nome << std::endl;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	while (encontrar)
	{
		indice = -1;
		std::string nome;
		std::cout << "\nIntroduza o nome do cliente a alterar: ";
		getline(std::cin, nome);
		Normalizar_Nome(nome);
		for (size_t j = 0; j < clientes.size(); j++)
		{
			if (clientes[j].nome == nome)
			{
				indice = j;
				break;
			}
		}
		if (indice == -1)
			std::cout << "\nNome do Cliente nao encontrado!\n";
		else
			encontrar = false;
	}
	bool alterar = true;
	while (alterar)
	{
		std::string alteracao;
		std::cout << "\nO que deseja alterar (nome,nif,familiares,morada): ";
		std::cin >> alteracao;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		if (alteracao == "nome")
		{
			std::cout << "\nIntroduza o novo nome do Cliente: ";
			getline(std::cin, clientes[indice].nome);
			Normalizar_Nome(clientes[indice].nome);
			alterar = false;
		}
		else if (alteracao == "nif")
		{
			std::cout << "\nIntroduza o novo nif do Cliente: ";
			getline(std::cin, clientes[indice].nif);
			alterar = false;
		}
		else if (alteracao == "familiares")
		{
			std::cout << "\nIntroduza o novo numero de familiares do Cliente: ";
			getline(std::cin, clientes[indice].n_familiares);
			alterar = false;
		}
		else if (alteracao == "morada")
		{
			Adress a_morada;
			a_morada = Adicionar_Morada();
			clientes[indice].morada = a_morada.rua + " / " + a_morada.porta + " / " + a_morada.andar + " / " + a_morada.codigo_postal + " / " + a_morada.localidade;
			alterar = false;
		}
		else
		{
			std::cout << "\nOpcao Invalida!\n";
		}
	}
	ler_ficheiro.close();
	Escrever_Ficheiro_Clientes(ficheiro, clientes);
	std::cout << "\nAlteracao Efetuada!\n";
}

void Remover_Cliente(std::string ficheiro, std::vector<Client> &clientes)		// Remover Cliente
{
	system("CLS");
	std::cout << "\n\t\t\t\t\t\tRemover Cliente";
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	std::string nome;
	bool encontrar = true;
	int indice = -1;
	std::cout << "\nClientes: \n\n";
	for (size_t l = 0; l < clientes.size(); l++)
		std::cout << clientes[l].nome << std::endl;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	while (encontrar)
	{
		std::cout << "\nIntroduza o nome do cliente a remover: ";
		getline(std::cin, nome);
		Normalizar_Nome(nome);
		indice = -1;
		for (size_t k = 0; k < clientes.size(); k++)
		{
			if (clientes[k].nome == nome)
			{
				indice = k;
				break;
			}
		}
		if (indice == -1)
			std::cout << "\nNome do Cliente nao encontrado!\n";
		else
			encontrar = false;
	}
	clientes.erase(clientes.begin() + indice);
	Escrever_Ficheiro_Clientes(ficheiro, clientes);
	std::cout << "\nCliente Removido!\n";
}

void Adicionar_Pacote(std::string ficheiro,std::string ultimo,std::vector<TravelPack> &Pacotes)		// Adicionar Novo Pacote
{
	system("CLS");
	std::cout << "\n\t\t\t\t\t\tAdicionar Pacote";
	TravelPack pacote;
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
		ultimo = "1";
	else
		ultimo = std::to_string(abs(stoi(ultimo))+1);
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "\n\nIntroduza o principal local turistico de destino (pode ser seguido de um hifen com os principais locais a visitar):\n";
	getline(std::cin, pacote.locais);
	std::cout << "\nIntroduza a data de inicio da viagem (AAAA/MM/DD): ";
	getline(std::cin, pacote.data_inicio);
	std::cout << "\nIntroduza a data de fim da viagem (AAAA/MM/DD): ";
	getline(std::cin, pacote.data_fim);
	std::cout << "\nIntroduza o preco por pessoa: ";
	getline(std::cin, pacote.preco);
	std::cout << "\nIntroduza o numero de lugares inicialmente disponiveis no pacote: ";
	getline(std::cin, pacote.n_maximo);
	pacote.n_vendidos = "0";
	pacote.identificador = ultimo;
	Pacotes.push_back(pacote);
	Escrever_Ficheiro_Pacotes(ficheiro, ultimo, Pacotes);
	ler_ficheiro.close();
}

void Alterar_Pacote(std::string ficheiro,std::string ultimo, std::vector<TravelPack> &pacotes)		//Alterar os dados de um determinado pacote
{
	system("CLS");
	std::cout << "\n\t\t\t\t\t\tAlterar Pacote";
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem pacotes disponiveis!\n";
		return;
	}
	bool encontrar = true;
	int indice = -1;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "\n\nPacotes Disponiveis: \n\n";
	for (size_t k = 0; k < pacotes.size(); k++)
		std::cout << "(" << pacotes[k].identificador << ")" << " --> " << pacotes[k].locais << std::endl;
	while (encontrar)
	{
		std::string identificador;
		std::cout << "\nIntroduza o identificador do pacote a alterar: ";
		getline(std::cin, identificador);
		indice = -1;
		for (size_t j = 0; j < pacotes.size(); j++)
		{
			if (pacotes[j].identificador == identificador)
			{
				indice = j;
				break;
			}
		}
		if (indice == -1)
			std::cout << "\nIdentificador do pacote nao encontrado!\n";
		else
			encontrar = false;
	}
	bool alterar = true;
	while (alterar)
	{
		std::string alteracao;
		std::cout << "\nO que deseja alterar (destino, data inicial, data final, preco, pacotes disponiveis): ";
		getline(std::cin, alteracao);
		if (alteracao == "destino")
		{
			std::cout << "\nIntroduza o principal local turistico de destino (pode ser seguido de um hifen com os principais locais a visitar):\n";
			getline(std::cin, pacotes[indice].locais);
			alterar = false;
		}
		else if (alteracao == "data inicial")
		{
			std::cout << "\nIntroduza a nova data de inicio da viagem (AAAA/MM/DD): ";
			getline(std::cin, pacotes[indice].data_inicio);
			alterar = false;
		}
		else if (alteracao == "data final")
		{
			std::cout << "\nIntroduza a nova data de fim da viagem (AAAA/MM/DD): ";
			getline(std::cin, pacotes[indice].data_fim);
			alterar = false;
		}
		else if (alteracao == "preco")
		{
			std::cout << "\nIntroduza o novo preco por pessoa: ";
			getline(std::cin, pacotes[indice].preco);
			alterar = false;
		}
		else if (alteracao == "pacotes disponiveis")
		{
			std::cout << "\nIntroduza o novo numero de pacotes disponiveis: ";
			getline(std::cin, pacotes[indice].n_maximo);
			alterar = false;
		}
		else
		{
			std::cout << "\nOpcao Invalida!\n";
		}
	}
	ler_ficheiro.close();
	Escrever_Ficheiro_Pacotes(ficheiro, ultimo, pacotes);
	std::cout << "\nAlteracao Efetuada!\n";
}

void Remover_Pacote(std::string ficheiro_pacotes, std::string ultimo, std::vector<TravelPack> &pacotes,std::vector<Client> &clientes,std::string ficheiro_clientes)		// Remover Pacote
{
	system("CLS");
	std::cout << "\n\t\t\t\t\t\tRemover Pacote";
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro_pacotes);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem pacotes disponiveis!\n";
		return;
	}
	bool encontrar = true;
	int indice = -1;
	std::cout << "\n\nPacotes Disponiveis: \n\n";
	for (size_t k = 0; k < pacotes.size(); k++)
		std::cout << "(" << pacotes[k].identificador << ")" << " --> " << pacotes[k].locais << std::endl;
	while (encontrar)
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::string identificador;
		std::cout << "\nIntroduza o identificador do pacote a remover: ";
		getline(std::cin, identificador);
		indice = -1;
		for (size_t j = 0; j < pacotes.size(); j++)
		{
			if (abs(stoi(pacotes[j].identificador)) == abs(stoi(identificador)))
			{
				indice = j;
				break;
			}
		}
		if (indice == -1)
			std::cout << "\nIdentificador do pacote nao encontrado!\n";
		else
			encontrar = false;
	}
	for (size_t l = 0; l < clientes.size(); l++)
	{
		for (size_t m = 0; m < clientes[l].pacotes.size(); m++)
		{
			if (abs(stoi(clientes[l].pacotes[m])) == abs(stoi(pacotes[indice].identificador)))
				clientes[l].pacotes.erase(clientes[l].pacotes.begin() + m);
			if (clientes[l].pacotes.size() == 0)
				clientes[l].pacotes.push_back("0");
		}
	}
	for (size_t k = indice + 1; k < pacotes.size(); k++)
	{
		if (stoi(pacotes[k].identificador) > 0)
			pacotes[k].identificador = std::to_string(stoi(pacotes[k].identificador) - 1);
		else
			pacotes[k].identificador = std::to_string(-(abs(stoi(pacotes[k].identificador)) - 1));
	}
	pacotes.erase(pacotes.begin() + indice);
	std::string ultimo_pacote = pacotes[pacotes.size() - 1].identificador;
	Escrever_Ficheiro_Pacotes(ficheiro_pacotes, ultimo_pacote, pacotes);
	Escrever_Ficheiro_Clientes(ficheiro_clientes, clientes);
	ler_ficheiro.close();
	std::cout << "\nPacote Removido!\n";
}

void Visualizar_Cliente(std::string ficheiro, const std::vector<Client> &clientes)		// Visualizar informacao de um unico cliente
{
	system("CLS");
	std::cout << "\n\t\t\t\tVisualizar Informacao de um unico cliente";
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	bool encontrar = true;
	std::string nome;
	int indice = -1;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "\nClientes: \n\n";
	for (size_t l = 0; l < clientes.size(); l++)
		std::cout << clientes[l].nome << std::endl;
	while (encontrar)
	{
		std::cout << "\nIntroduza o nome do cliente a analisar: ";
		getline(std::cin, nome);
		Normalizar_Nome(nome);
		for (size_t k = 0; k < clientes.size(); k++)
		{
			if (clientes[k].nome == nome)
			{
				indice = k;
				break;
			}
		}
		if (indice == -1)
			std::cout << "\nNome do Cliente nao encontrado!\n";
		else
			encontrar = false;
	}
	std::cout << "\nInformacao do cliente:\n\n";
	std::cout << "Nome: " << clientes[indice].nome << "\nNIF: " << clientes[indice].nif << "\nNumero de Familiares: " << clientes[indice].n_familiares << "\nMorada: " << clientes[indice].morada << "\nPacotes Adquiridos: ";
	for (size_t i = 0; i < clientes[indice].pacotes.size(); i++)
	{
		if (i == clientes[indice].pacotes.size() - 1)
			std::cout << clientes[indice].pacotes[i] << std::endl;
		else
			std::cout << clientes[indice].pacotes[i] << ", ";
	}
}

void Visualizar_Todos_Clientes(std::string ficheiro, const std::vector<Client> &clientes)		// Visualizar informacao de todos os clientes
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	system("CLS");
	std::cout << "\n\t\t\t\tInformacao de todos os clientes\n\n";
	for (size_t j = 0; j < clientes.size(); j++)
	{
		std::cout << "Nome: " << clientes[j].nome << "\nNIF: " << clientes[j].nif << "\nNumero de Familiares: " << clientes[j].n_familiares << "\nMorada: " << clientes[j].morada << "\nPacotes Adquiridos: ";
		for (size_t i = 0; i < clientes[j].pacotes.size(); i++)
		{
			if (i == clientes[j].pacotes.size() - 1)
				std::cout << clientes[j].pacotes[i] << std::endl << std::endl;
			else
				std::cout << clientes[j].pacotes[i] << ", ";
		}
	}
}

void Visualizar_Todos_Pacotes(std::string ficheiro, const std::vector<TravelPack> &pacotes)		// Visualizar informacao de todos os pacotes
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem pacotes disponiveis!\n";
		return;
	}
	system("CLS");
	std::cout << "\n\t\t\t\tInformacao de todos os pacotes disponiveis\n\n";
	for (size_t i = 0; i < pacotes.size(); i++)
	{
		std::cout << "Identificador: " << pacotes[i].identificador << "\nLocais: " << pacotes[i].locais << "\nData de inicio: " << pacotes[i].data_inicio << "\nData de fim: " << pacotes[i].data_fim << "\nPreco por pessoa: " << pacotes[i].preco << "\nNumero de lugares disponiveis: " << pacotes[i].n_maximo << "\nNumero de lugares vendidos: " << pacotes[i].n_vendidos << std::endl << std::endl;
	}
	ler_ficheiro.close();
}

void Visualizar_Pacotes_Destino(std::string ficheiro, const std::vector<TravelPack> &pacotes)		// Visualizar informacao de um pacote com determinado destino  
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem pacotes disponiveis!\n";
		return;
	}
	bool encontrar = true;
	std::vector<TravelPack> disponiveis;
	std::string nome,local,locais;
	int idx;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	system("CLS");
	std::cout << "\n\t\t\t\tInformacao dos pacotes disponiveis de um dado destino\n\n";
	std::cout << "\n\nPacotes Disponiveis: \n\n";
	for (size_t k = 0; k < pacotes.size(); k++)
		std::cout << "(" << pacotes[k].identificador << ")" << " --> " << pacotes[k].locais << std::endl;
	while (encontrar)
	{
		std::cout << "\nIntroduza o nome do destino desejado (nome antes do -): ";
		getline(std::cin, nome);
		for (size_t k = 0; k < pacotes.size(); k++)
		{
			locais = pacotes[k].locais;
			idx = locais.find_first_of('-');
			if (idx == std::string::npos)
				local = locais;
			else
				local = locais.substr(0, idx - 1);
			if (local == nome)
			{
				disponiveis.push_back(pacotes[k]);
			}
		}
		if (disponiveis.size() == 0)
			std::cout << "\nNao existem pacotes turisticos disponiveis desse local!\n";
		else
			encontrar = false;
	}
	std::cout << "\nPacotes disponiveis do local pedido:\n\n";
	for (size_t i = 0; i < disponiveis.size(); i++)
	{
		std::cout << "Identificador: " << disponiveis[i].identificador << "\nLocais: " << disponiveis[i].locais << "\nData de inicio: " << disponiveis[i].data_inicio << "\nData de fim: " << disponiveis[i].data_fim << "\nPreco por pessoa: " << disponiveis[i].preco << "\nNumero de lugares disponiveis: " << disponiveis[i].n_maximo << "\nNumero de lugares vendidos: " << disponiveis[i].n_vendidos << std::endl << std::endl;
	}
	ler_ficheiro.close();
}

void Visualizar_Pacotes_Datas(std::string ficheiro, const std::vector<TravelPack> &pacotes)		// Visualizar Pacotes Disponiveis entre duas datas
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem pacotes disponiveis!\n";
		return;
	}
	system("CLS");
	std::cout << "\n\t\t\t\tInformacao dos pacotes disponiveis entre duas datas\n\n";
	std::string data_inicial, data_final,nova_string = "";
	Date Data_Inicial,Data_Final;
	std::vector<std::string> adicionar;
	std::cout << "\nIntroduza uma data limite de inicio(AAAA/MM/DD): ";
	std::cin >> data_inicial;
	std::cout << "\nIntroduza uma data limite de fim(AAAA/MM/DD): ";
	std::cin >> data_final;
	std::vector<TravelPack> disponiveis;
	for (size_t k = 0; k < pacotes.size(); k++)
	{
		if (((data_inicial >= pacotes[k].data_inicio) && (data_final <= pacotes[k].data_fim)) || ((data_inicial <= pacotes[k].data_inicio) && (data_final >= pacotes[k].data_fim)))
		{
			disponiveis.push_back(pacotes[k]);
		}
	}
	if (disponiveis.size() == 0)
		std::cout << "\nNao ha nenhum pacote disponivel entre as duas datas inseridas!\n\n";
	else
	{
		std::cout << "\nPacotes disponiveis entre as duas datas inseridas:\n\n";
		for (size_t l = 0; l < disponiveis.size(); l++)
		{
			std::cout << "Identificador: " << disponiveis[l].identificador << "\nLocais: " << disponiveis[l].locais << "\nData de inicio: " << disponiveis[l].data_inicio << "\nData de fim: " << disponiveis[l].data_fim << "\nPreco por pessoa: " << disponiveis[l].preco << "\nNumero de lugares disponiveis: " << disponiveis[l].n_maximo << "\nNumero de lugares vendidos: " << disponiveis[l].n_vendidos << std::endl << std::endl;
		}
	}
	ler_ficheiro.close();
}

void Visualizar_Pacotes_Destino_Datas(std::string ficheiro, std::vector<TravelPack> &pacotes)		// Visualizar os pacotes disponiveis entre duas datas, para um determinado destino
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem pacotes disponiveis!\n";
		return;
	}
	system("CLS");
	std::cout << "\n\t\t\tInformacao dos pacotes disponiveis de um dado destino, entre duas datas\n\n";
	std::cout << "\n\nPacotes Disponiveis: \n\n";
	for (size_t k = 0; k < pacotes.size(); k++)
		std::cout << "(" << pacotes[k].identificador << ")" << " --> " << pacotes[k].locais << std::endl;
	bool encontrar = true;
	std::vector<TravelPack> disponiveis1,disponiveis2,disponiveis;
	std::string nome, local, locais;
	int idx;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "\nIntroduza o nome do destino desejado: ";
	getline(std::cin, nome);
	for (size_t k = 0; k < pacotes.size(); k++)
	{
		locais = pacotes[k].locais;
		idx = locais.find_first_of('-');
		if (idx == std::string::npos)
			local = locais;
		else
			local = locais.substr(0, idx - 1);
		if (local == nome)
		{
			disponiveis1.push_back(pacotes[k]);
		}
	}
	std::string data_inicial, data_final;
	std::cout << "\nIntroduza uma data limite de inicio(AAAA/MM/DD): ";
	std::cin >> data_inicial;
	std::cout << "\nIntroduza uma data limite de fim(AAAA/MM/DD): ";
	std::cin >> data_final;
	for (size_t i = 0; i < pacotes.size(); i++)
	{
		if ((data_inicial <= pacotes[i].data_inicio) && (data_final >= pacotes[i].data_fim))
		{
			disponiveis2.push_back(pacotes[i]);
		}
	}
	for (size_t j = 0; j < disponiveis1.size(); j++)
	{
		for (size_t m = 0; m < disponiveis2.size(); m++)
		{
			if (disponiveis1[j].identificador == disponiveis2[m].identificador)
				disponiveis.push_back(disponiveis1[j]);
		}
	}
	if (disponiveis.size() == 0)
		std::cout << "\nNao ha nenhum pacote disponivel para o destino inserido, entre as duas datas inseridas!\n\n";
	else
	{
		std::cout << "\nPacotes disponiveis do local inserido, entre as duas datas inseridas:\n\n";
		for (size_t l = 0; l < disponiveis.size(); l++)
		{
			std::cout << "Identificador: " << disponiveis[l].identificador << "\nLocais: " << disponiveis[l].locais << "\nData de inicio: " << disponiveis[l].data_inicio << "\nData de fim: " << disponiveis[l].data_fim << "\nPreco por pessoa: " << disponiveis[l].preco << "\nNumero de lugares disponiveis: " << disponiveis[l].n_maximo << "\nNumero de lugares vendidos: " << disponiveis[l].n_vendidos << std::endl << std::endl;
		}
	}
	ler_ficheiro.close();
}

void Visualizar_Pacotes_Vendidos_Cliente(std::string ficheiro, std::vector<Client> &clientes)		// Visualizar Pacotes Vendidos a um determinado cliente
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	bool encontrar = true;
	std::string nome;
	int indice = -1;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	system("CLS");
	std::cout << "\n\t\t\tInformacao dos pacotes vendidos a um determinado cliente\n\n";
	std::cout << "\nClientes: \n\n";
	for (size_t l = 0; l < clientes.size(); l++)
		std::cout << clientes[l].nome << std::endl;
	while (encontrar)
	{
		std::cout << "\nIntroduza o nome do cliente a analisar: ";
		getline(std::cin, nome);
		Normalizar_Nome(nome);
		for (size_t k = 0; k < clientes.size(); k++)
		{
			if (clientes[k].nome == nome)
			{
				indice = k;
				break;
			}
		}
		if (indice == -1)
			std::cout << "\nNome do Cliente nao encontrado!\n";
		else
			encontrar = false;
	}
	std::cout << "\nIdentificadores dos Pacotes vendidos ao cliente introduzido: ";
	for (size_t i = 0; i < clientes[indice].pacotes.size(); i++)
	{
		if (i == clientes[indice].pacotes.size()-1)
			std::cout << clientes[indice].pacotes[i] << std::endl;
		else
			std::cout << clientes[indice].pacotes[i] << ", ";
	}
}

void Visualizar_Pacotes_Vendidos_Clientes(std::string ficheiro, std::vector<Client> &clientes)		// Visualizar Pacotes Vendidos a todos os clientes
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	ler_ficheiro.close();
	system("CLS");
	std::cout << "\n\t\t\tInformacao dos pacotes vendidos a todos os clientes\n\n";
	for (size_t i = 0; i < clientes.size(); i++)
	{
		std::cout << "\n Identificadores dos Pacotes vendidos ao cliente " << clientes[i].nome << ": ";
		for (size_t j = 0; j < clientes[i].pacotes.size(); j++)
		{
			if (j == clientes[i].pacotes.size() - 1)
				std::cout << clientes[i].pacotes[j] << std::endl;
			else
				std::cout << clientes[i].pacotes[j] << ", ";
		}
	}
}

void Comprar_Pacote(std::vector<Client> &clientes,std::vector<TravelPack> &pacotes, std::string ficheiro_pacotes, std::string ultimo, const std::string ficheiro_clientes)		// Comprar Pacote
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro_pacotes);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem pacotes disponiveis!\n";
		return;
	}
	ler_ficheiro.close();
	ler_ficheiro.open(ficheiro_clientes);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	ler_ficheiro.close();
	system("CLS");
	std::cout << "\n\t\t\t\t\tComprar Pacote\n\n";
	bool encontrar = true, procurar = true, valido = true;
	std::string nome,identificador;
	int indice = -1, idx = -1;
	std::cin.clear();
	std::cin.ignore(1000, '\n');
	std::cout << "\nClientes: \n\n";
	for (size_t l = 0;l<clientes.size();l++)
		std::cout << clientes[l].nome << std::endl;
	while (encontrar)
	{
		indice = -1;
		std::cout << "\nIntroduza o nome do cliente que deseja comprar um pacote: ";
		getline(std::cin, nome);
		Normalizar_Nome(nome);
		for (size_t j = 0; j < clientes.size(); j++)
		{
			if (clientes[j].nome == nome)
			{
				indice = j;
				break;
			}
		}
		if (indice == -1)
			std::cout << "\nNome do Cliente nao encontrado!\n";
		else
			encontrar = false;
	}
	std::cout << "\nPacotes Disponiveis: \n\n";
	for (size_t k = 0; k < pacotes.size(); k++)
		std::cout << "(" << pacotes[k].identificador << ")" << " --> " << pacotes[k].locais << std::endl;
	while (procurar)
	{
		idx = -1;
		std::cout << "\nIntroduza o identificador do pacote turistico a comprar: ";
		getline(std::cin, identificador);
		for (size_t i = 0; i < pacotes.size(); i++)
		{
			if (abs(stoi(pacotes[i].identificador)) == abs(stoi(identificador)))
			{
				idx = i;
				break;
			}
		}
		if (idx == -1)
			std::cout << "\nIdentificador do Pacote Invalido!\n";
		else
		{
			if (pacotes[idx].n_vendidos >= pacotes[idx].n_maximo)
			{
				if (stoi(pacotes[idx].identificador) > 0)
					pacotes[idx].identificador = std::to_string(-stoi(pacotes[idx].identificador));
				std::cout << "\nPacote Turistico Esgotado!\n";
			}
			else
				procurar = false;
		}
	}
	if (clientes[indice].pacotes[0] == "0")
		clientes[indice].pacotes.clear();
	clientes[indice].pacotes.push_back(pacotes[idx].identificador);
	pacotes[idx].n_vendidos = std::to_string(stoi(pacotes[idx].n_vendidos) + 1);
	Escrever_Ficheiro_Pacotes(ficheiro_pacotes, ultimo, pacotes);
	std::cout << "\nPacote Comprado!\n";
}

void Visualizar_Total_Pacotes_Vendidos(std::string ficheiro, std::vector<Client> &clientes, std::vector<TravelPack> &pacotes)		// Visualizar Total de Pacotes Vendidos pela Agencia
{
	std::ifstream ler_ficheiro;
	ler_ficheiro.open(ficheiro);
	if (ler_ficheiro.peek() == std::ifstream::traits_type::eof())
	{
		std::cout << "\nNao existem clientes disponiveis!\n";
		return;
	}
	system("CLS");
	std::cout << "\n\t\t\tInformacao de todos os pacotes vendidos pela agencia\n\n";
	ler_ficheiro.close();
	int contador,total_pacotes = 0,numero_familiares = 0;
	double lucro,soma = 0;
	std::cout << "   _________" << " \t\t ___________________________" << " \t\t _________________";
	std::cout << "\n  | Pacotes |" << "\t\t| Numero de Pacotes Vendidos|" << "\t\t| Lucro do Pacote |";
	std::cout << "\n  -----------" << " \t\t-----------------------------" << " \t\t-------------------";
	for (size_t i = 0; i < pacotes.size(); i++)
	{
		contador = 0;
		std::cout << std::endl << "  |" << std::setw(5) << pacotes[i].identificador << "    |";
		for (size_t j = 0; j < clientes.size(); j++)
		{
			for (size_t k = 0; k < clientes[j].pacotes.size(); k++)
			{
				if (clientes[j].pacotes[k] == std::to_string(abs(stoi(pacotes[i].identificador))))
				{
					contador++;
					numero_familiares += stoi(clientes[j].n_familiares);
				}
			}
		}
		lucro = numero_familiares * stod(pacotes[i].preco);
		total_pacotes += contador;
		soma += lucro;
		std::cout << "\t\t|\t      " << std::setw(2) << contador << "\t    |\t\t|     " << std::setw(5) << lucro << "\t  |";
		numero_familiares = 0;
	}
	std::cout << "\n  -----------" << " \t\t-----------------------------" << " \t\t-------------------";
	std::cout << "\n\nNumero total de Pacotes Vendidos: " << total_pacotes;
	std::cout << "\n\nLucro total da Agencia: " << soma << " euros\n";
}

int main()
{
	std::string ficheiro_agencia;
	std::cout << "Introduza o nome do ficheiro da agencia: ";
	std::cin >> ficheiro_agencia;
	if (!Ficheiro_existe(ficheiro_agencia))		// Verificar se o ficheiro da agencia existe
	{
		std::cout << "\nNome do ficheiro da agencia invalido!\n\n";
		system("pause");
		return 1;
	}
	Agency Agencia = Ler_Agency(ficheiro_agencia);
	if (!Ficheiro_existe(Agencia.ficheiro_clientes))	// Verificar se o ficheiro dos clientes existe
	{
		std::cout << "Nome do ficheiro dos clientes invalido!\n\n";
		system("pause");
		return 1;
	}
	if (!Ficheiro_existe(Agencia.ficheiro_pacotes))		// Verificar se o ficheiro dos pacotes existe
	{
		std::cout << "Nome do ficheiro dos pacotes invalido!\n\n";
		system("pause");
		return 1;
	}
	std::vector <Client> Clientes; //APAGAR
	//std::vector<Client> Clientes = Ler_Clientes(Agencia.ficheiro_clientes);		//	Leitura dos Dados
	std::vector<TravelPack> Pacotes;
	char opcao,opcao2,opcao3;
	bool repetir = true,repetir2 = true,repetir3,sair;
	while (repetir)		// Apresentacao dos Menus
	{
		system("CLS");
		std::cout << "\n\n\t\t\t\t\t\tAgencia NiceHolidays!\n\n\tMenu Principal\n\n";
		std::cout << "[0] Gestao de Clientes\n[1] Gestao de Pacotes\n[2] Visualizar Informacao\n[3] Comprar Pacote Turistico\n[4] Sair do Programa\n\n";
		std::cout << "O que deseja fazer ? R: ";
		std::cin >> opcao;
		repetir2 = true;
		switch (opcao)
		{
			case '0':		// Menu de Gestao de Clientes
			{
				while(repetir2)
				{
					system("CLS");
					std::cout << "\n\n\t\t\t\t\t\tAgencia NiceHolidays!\n\n\tMenu de Gestao de Clientes\n\n";
					std::cout << "[0] Adicionar Cliente\n[1] Alterar Dados de Cliente\n[2] Remover Cliente\n[3] Sair para o Menu Principal\n\n";
					std::cout << "O que deseja fazer ? R: ";
					std::cin >> opcao2;
					switch (opcao2)
					{
						case '0':		// Adicionar Cliente
						{
							Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
							Adicionar_Cliente(Agencia.ficheiro_clientes, Clientes);
							std::cout << "\nCliente Adicionado!\n";
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '1':		// Alterar Dados do Cliente
						{
							Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
							Alterar_Cliente(Agencia.ficheiro_clientes, Clientes);
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '2':		// Remover Cliente
						{
							Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
							Remover_Cliente(Agencia.ficheiro_clientes, Clientes);
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '3':		// Sair para o Menu Principal
						{
							repetir2 = false;
							repetir = true;
							system("CLS");
							break;
						}
						default:		// Input Invalido
						{
							repetir2 = true;
							std::cout << "\n\nOpcao Invalida!\n\nO que deseja fazer ? R: ";
							break;
						}
					}
				}
				break;
			}
			case '1':		// Menu de Gestao de Pacotes Turisticos
			{
				while (repetir2)
				{
					system("CLS");
					std::cout << "\n\n\t\t\t\t\t\tAgencia NiceHolidays!\n\n\tMenu de Gestao de Pacotes\n\n";
					std::cout << "[0] Adicionar Pacote\n[1] Alterar Dados de Pacote\n[2] Remover Pacote\n[3] Sair para o Menu Principal\n\n";
					std::cout << "O que deseja fazer ? R: ";
					std::cin >> opcao2;
					switch (opcao2)
					{
						case '0':		// Adicionar Pacote
						{
							std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
							Adicionar_Pacote(Agencia.ficheiro_pacotes, ultimo_pacote_criado, Pacotes);
							std::cout << "\nPacote Adicionado!\n";
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '1':		// Alterar Dados de Pacote
						{
							std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
							Alterar_Pacote(Agencia.ficheiro_pacotes, ultimo_pacote_criado, Pacotes);
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '2':		// Remover Pacote
						{
							Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
							std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
							Remover_Pacote(Agencia.ficheiro_pacotes, ultimo_pacote_criado, Pacotes, Clientes, Agencia.ficheiro_clientes);
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '3':		// Sair para o Menu Principal
						{
							repetir2 = false;
							repetir = true;
							system("CLS");
							break;
						}
						default:		// Input Invalido
						{
							repetir2 = true;
							std::cout << "\n\nOpcao Invalida!\n\nO que deseja fazer ? R: ";
							break;
						}
					}
				}
				break;
			}
			case '2':		// Menu de Visualizacao de Informacoes
			{
				repetir2 = true;

				while (repetir2)
				{
					system("CLS");
					std::cout << "\n\n\t\t\t\t\t\tAgencia NiceHolidays!\n\n\tMenu de Visualizacao de Informacao\n\n";
					std::cout << "[0] Visualizar informacao de um unico cliente\n[1] Visualizar informacao de todos os clientes\n[2] Visualizar informacao dos pacotes turisticos disponiveis\n[3] Visualizar informacao dos pacotes turisticos vendidos\n[4] Sair para o Menu Principal\n\n";
					std::cout << "O que deseja fazer ? R: ";
					std::cin >> opcao2;
					switch (opcao2)
					{
						case '0':		// Visualizar Informacao de um unico cliente
						{
							Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
							Visualizar_Cliente(Agencia.ficheiro_clientes, Clientes);
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '1':		// Visualizar Informacao de todos os clientes
						{
							Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
							Visualizar_Todos_Clientes(Agencia.ficheiro_clientes, Clientes);
							std::cin.clear();
							std::cin.ignore(1000, '\n');
							sair = Sair_Programa();
							if (sair)
							{
								std::cout << "\nObrigado!\n\n";
								system("pause");
								return 0;
							}
							repetir2 = false;
							break;
						}
						case '2':		// Visualizar Informacoes sobre pacotes disponiveis
						{
							system("CLS");
							std::cout << "\n\n\t\t\t\t\t\tAgencia NiceHolidays!\n\n\tMenu de Visualizacao de Pacotes Disponiveis\n\n";
							std::cout << "[0] Visualizar todos os pacotes disponiveis\n[1] Visualizar os pacotes disponiveis de um destino especifico\n[2] Visualizar os pacotes disponiveis entre duas datas\n[3] Visualizar os pacotes disponiveis de um destino especifico e entre duas datas\n[4] Sair para o Menu de Visualizacao de Informacao\n\n";
							std::cout << "O que deseja fazer ? R: ";
							repetir3 = true;
							repetir2 = false;
							while (repetir3)
							{
								std::cin >> opcao3;
								switch (opcao3)
								{
									case '0':		// Visualizar Todos os Pacotes Disponiveis
									{
										std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
										Visualizar_Todos_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
										std::cin.clear();
										std::cin.ignore(1000, '\n');
										sair = Sair_Programa();
										if (sair)
										{
											std::cout << "\nObrigado!\n\n";
											system("pause");
											return 0;
										}
										repetir3 = false;
										repetir2 = false;
										break;
									}
									case '1':		// Visualizar os Pacotes Disponiveis para um determinado destino
									{
										std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
										Visualizar_Pacotes_Destino(Agencia.ficheiro_pacotes, Pacotes);
										sair = Sair_Programa();
										if (sair)
										{
											std::cout << "\nObrigado!\n\n";
											system("pause");
											return 0;
										}
										repetir3 = false;
										repetir2 = false;
										break;
									}
									case '2':		// Visualizar os Pacotes Disponiveis entre duas determinadas datas
									{
										std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
										Visualizar_Pacotes_Datas(Agencia.ficheiro_pacotes, Pacotes);
										std::cin.clear();
										std::cin.ignore(1000, '\n');
										sair = Sair_Programa();
										if (sair)
										{
											std::cout << "\nObrigado!\n\n";
											system("pause");
											return 0;
										}
										repetir3 = false;
										repetir2 = false;
										break;
									}
									case '3':		// Visualizar os Pacotes Disponiveis para um determinado destino, entre duas determinadas datas
									{
										std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
										Visualizar_Pacotes_Destino_Datas(Agencia.ficheiro_pacotes, Pacotes);
										std::cin.clear();
										std::cin.ignore(1000, '\n');
										sair = Sair_Programa();
										if (sair)
										{
											std::cout << "\nObrigado!\n\n";
											system("pause");
											return 0;
										}
										repetir3 = false;
										repetir2 = false;
										break;
									}
									case '4':		// Sair para o Menu de Visualizacao de Informacao
									{
										repetir3 = false;
										repetir2 = true;
										break;
									}
								}
							}
							break;
						}
						case '3':		// Visualizar Informacoes sobre os Pacotes Turisticos Vendidos
						{
							system("CLS");
							std::cout << "\n\n\t\t\t\t\t\tAgencia NiceHolidays!\n\n\tMenu de Visualizacao de Pacotes Vendidos\n\n";
							std::cout << "[0] Visualizar os pacotes vendidos a um unico cliente\n[1] Visualizar todos os pacotes vendidos\n[2] Visualizar o total de pacotes vendidos pela agencia\n[3] Sair para o Menu de Visualizacao de Informacao\n\n";
							std::cout << "O que deseja fazer ? R: ";
							repetir3 = true;
							repetir2 = false;
							while (repetir3)
							{
								std::cin >> opcao3;
								switch (opcao3)
								{
									case '0':		// Visualizar os Pacotes Vendidos a um determinado Cliente
									{
										Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
										Visualizar_Pacotes_Vendidos_Cliente(Agencia.ficheiro_clientes, Clientes);
										sair = Sair_Programa();
										if (sair)
										{
											std::cout << "\nObrigado!\n\n";
											system("pause");
											return 0;
										}
										repetir3 = false;
										repetir2 = false;
										break;
									}
									case '1':		// Visualizar os Pacotes Vendidos a todos os Clientes
									{
										Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
										Visualizar_Pacotes_Vendidos_Clientes(Agencia.ficheiro_clientes, Clientes);
										std::cin.clear();
										std::cin.ignore(1000, '\n');
										sair = Sair_Programa();
										if (sair)
										{
											std::cout << "\nObrigado!\n\n";
											system("pause");
											return 0;
										}
										repetir3 = false;
										repetir2 = false;
										break;
									}
									case '2':		// Visualizar todos os Pacotes Vendidos pela Agencia
									{
										Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
										std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
										Visualizar_Total_Pacotes_Vendidos(Agencia.ficheiro_clientes, Clientes, Pacotes);
										std::cin.clear();
										std::cin.ignore(1000, '\n');
										sair = Sair_Programa();
										if (sair)
										{
											std::cout << "\nObrigado!\n\n";
											system("pause");
											return 0;
										}
										repetir3 = false;
										repetir2 = false;
										break;
									}
									case '3':		// Sair para o Menu de Visualizacao de Informacao
									{
										repetir3 = false;
										repetir2 = true;
										break;
									}
									default:		// Input Invalido
									{
										std::cout << "\nOpcao Invalida!\n";
										break;
									}
								}
							}
							break;
						}
						case '4':		// Sair para o Menu Principal
						{
							repetir2 = false;
							repetir = true;
							system("CLS");
							break;
						}
						default:		// Input Invalido
						{
							repetir2 = true;
							std::cout << "\n\nOpcao Invalida!\n\nO que deseja fazer ? R: ";
							break;
						}
					}
				}
				break;
			}
			case '3':		// Comprar Pacote Turistico
			{
				Clientes = Ler_Clientes(Agencia.ficheiro_clientes);
				std::string ultimo_pacote_criado = Ler_Pacotes(Agencia.ficheiro_pacotes, Pacotes);
				Comprar_Pacote(Clientes, Pacotes,Agencia.ficheiro_pacotes,ultimo_pacote_criado,Agencia.ficheiro_clientes);
				Escrever_Ficheiro_Clientes(Agencia.ficheiro_clientes, Clientes);
				sair = Sair_Programa();
				if (sair)
				{
					std::cout << "\nObrigado!\n\n";
					system("pause");
					return 0;
				}
				break;
			}
			case '4':		//Sair do Programa
			{
				std::cout << "\nObrigado!\n\n";
				system("pause");
				return 0;
			}
			default:		// Input Invalido
			{
				repetir = true;
				std::cout << "\n\nOpcao Invalida!\n\nO que deseja fazer ? R: ";
				break;
			}
		}
	}
	std::cout << std::endl;
	system("pause");
	return 0;
}