#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
using namespace std;

struct book
{
	int id;
	char title[255];
	char author[100];
	int releaseYear;
	char description[600];
	int sizeb;
	float rate;
	int rateSize;
};

book* aumentar(book *livros, int &tamanho)
{
	book *newB = new book[tamanho + 1];
	copy(livros, livros + tamanho, newB);
	delete[] livros;
	tamanho++;
	return newB;
}

book* diminuir(book *livros, int &tamanho)
{
	book *newB = new book[tamanho - 1];
	copy(livros, livros + (tamanho - 1), newB);
	delete[] livros;
	tamanho--;
	return newB;
}

book convertVetor(string vetor[])
{
	book codx;

	codx.id = int(stoi(vetor[0]));
	strcpy(codx.title, vetor[1].c_str());
	strcpy(codx.author, vetor[2].c_str());
	codx.releaseYear = int(stoi(vetor[3]));
	strcpy(codx.description, vetor[4].c_str());
	codx.sizeb = int(stoi(vetor[5]));
	codx.rate = float(stof(vetor[6]));
	codx.rateSize = int(stoi(vetor[7]));

	return codx;
}

book* Ler(book *livros, int &tamanho, ifstream &arquivo)
{
	int x = 0;
	string vetor[8];
	string coluna;
	string aux;
	book saved;
	while (getline(arquivo, aux))
	{
		stringstream linha(aux);

		for (int i = 0; i < 8; i++)
		{
			getline(linha, coluna, ',');
			if (coluna.front() == '"'
				and coluna.back() != '"')
			{
				string colunaTemp;
				while (coluna.back() != '"')
				{
					getline(linha, colunaTemp, ',');
					coluna += ',' + colunaTemp;
				}
			}

			vetor[i] = coluna;
		}

		saved = convertVetor(vetor);
		if (tamanho == x)
		{
			livros = aumentar(livros, tamanho);
		}

		livros[x] = saved;
		x++;
	}

	for (int h = 0; h < x; h++)
	{
		cout << "ID: " << livros[h].id << endl;
		cout << "Titulo: " << livros[h].title << endl;
		cout << "Autor: " << livros[h].author << endl;
		cout << "Ano de Lancamento: " << livros[h].releaseYear << endl;
		cout << "Descricao (Sinopse): " << livros[h].description << endl;
		cout << "Numero de Paginas " << livros[h].sizeb << endl;
		cout << "Avaliacao: " << livros[h].rate << endl;
		cout << "Quantidade de Avaliacao: " << livros[h].rateSize << endl;
		cout << "_______________________________________________________________" << endl;
	}

	return livros;
}

//ORGANIZA POR AVALIACAO:
int ParticionaRate(book v[], int c, int f)
{
	float pivo = v[c].rate;
	int i = c + 1, j = f;
	while (i <= j)
	{
		if (v[i].rate >= pivo) i++;
		else if (pivo >= v[j].rate) j--;
		else
		{
			swap(v[i], v[j]);
			i++;
			j--;
		}
	}

	v[c] = v[j];
	v[j].rate = pivo;
	return j;
}

void QuicksortRate(book a[], int pos_pivo, int fim)
{
	int pos_novo_pivo;
	if (pos_pivo < fim)
	{
		pos_novo_pivo = ParticionaRate(a, pos_pivo, fim);
		QuicksortRate(a, pos_pivo, pos_novo_pivo - 1);
		QuicksortRate(a, pos_novo_pivo + 1, fim);
	}
}

//ORGANIZA POR ID
int ParticionaID(book v[], int c, int f)
{
	int pivo = v[c].id;
	int i = c + 1, j = f;
	while (i <= j)
	{
		if (v[i].id <= pivo) i++;
		else if (pivo <= v[j].id) j--;
		else
		{
			swap(v[i], v[j]);
			i++;
			j--;
		}
	}

	v[c] = v[j];
	v[j].id = pivo;
	return j;
}

void QuicksortID(book a[], int pos_pivo, int fim)
{
	int pos_novo_pivo;
	if (pos_pivo < fim)
	{
		pos_novo_pivo = ParticionaID(a, pos_pivo, fim);
		QuicksortID(a, pos_pivo, pos_novo_pivo - 1);
		QuicksortID(a, pos_novo_pivo + 1, fim);
	}
}

//____________________________________________________________________________________________________-
void Selection_sortAutor(book vetor[], int tam)
{
	int menor;
	for (int indice = 0; indice < tam - 1; indice++)
	{
		menor = indice;
		for (int j = indice + 1; j < tam; j++)
		{
			if (strcmp(vetor[j].author, vetor[menor].author) < 0)
			{
				menor = j;
			}
		}

		swap(vetor[indice], vetor[menor]);
	}
}

void Selection_sortTitulo(book vetor[], int tam)
{
	int menor;
	for (int indice = 0; indice < tam - 1; indice++)
	{
		menor = indice;
		for (int j = indice + 1; j < tam; j++)
		{
			if (strcmp(vetor[j].title, vetor[menor].title) < 0)
			{
				menor = j;
			}
		}

		swap(vetor[indice], vetor[menor]);
	}
}

//_______________________________________________________________________________
int Busca_binaria(book *livros, int pos_inicial, int pos_final, int id)
{
	int meio = (pos_inicial + pos_final) / 2;
	if (id == livros[meio].id)
	{
		return meio;
	}
	else if (pos_inicial < pos_final)
	{
		if (livros[meio].id < id) return Busca_binaria(livros, meio + 1, pos_final, id);
		else return Busca_binaria(livros, pos_inicial, meio - 1, id);
	}
	else
	{
		return -1;
	}
}

void Listar(book *livros, int &tamanho, ifstream &arquivo)
{
	int idPesquisa;
	int escolhaListagem;
	cout << "| 1 - Todos Elementos | 2 - Um Item (ID) |" << endl;
	cin >> escolhaListagem;
	if (escolhaListagem == 1)
	{
		for (int h = 0; h < tamanho; h++)
		{
			cout << "ID: " << livros[h].id << endl;
			cout << "Titulo: " << livros[h].title << endl;
			cout << "Autor: " << livros[h].author << endl;
			cout << "Ano de Lancamento: " << livros[h].releaseYear << endl;
			cout << "Descricao (Sinopse): " << livros[h].description << endl;
			cout << "Numero de Paginas: " << livros[h].sizeb << endl;
			cout << "Avaliacao: " << livros[h].rate << endl;
			cout << "Quantidade de Avaliacao: " << livros[h].rateSize << endl;
			cout << "_______________________________________________________________" << endl;
		}
	}
	else if (escolhaListagem == 2)
	{
		cout << "Digite o ID do livro: ";
		cin >> idPesquisa;
		int posicao;
		posicao = Busca_binaria(livros, 0, tamanho - 1, idPesquisa);
		if (posicao != -1)
		{
			cout << "ID: " << livros[posicao].id << endl;
			cout << "Titulo: " << livros[posicao].title << endl;
			cout << "Autor: " << livros[posicao].author << endl;
			cout << "Ano de Lancamento: " << livros[posicao].releaseYear << endl;
			cout << "Descricao (Sinopse): " << livros[posicao].description << endl;
			cout << "Quantidade de Paginas: " << livros[posicao].sizeb << endl;
			cout << "Avaliacao: " << livros[posicao].rate << endl;
			cout << "Quantidade de Avaliacao: " << livros[posicao].rateSize << endl;
			cout << "_______________________________________________________________" << endl;
		}
		else
		{
			cout << "Nao encontrado :(" << endl;
		}
	}
}

book* Adicionar(book *livros, int &tamanho)
{
	book novo;
	livros = aumentar(livros, tamanho);
	tamanho--;
	novo.id = livros[tamanho - 1].id + 1;
	string aux;
	cout << "Insira o Titulo do Livro: ";
	cin.ignore();
	getline(cin, aux);
	strcpy(novo.title, aux.c_str());
	cout << "Insira o Nome do Autor: ";
	getline(cin, aux);
	strcpy(novo.author, aux.c_str());
	cout << "Ano de Lancamento: ";
	cin >> novo.releaseYear;
	cout << "Sinopse: ";
	cin.ignore();
	getline(cin, aux);
	strcpy(novo.description, aux.c_str());
	cout << "Tamanho do Livro (Paginas): ";
	cin >> novo.sizeb;
	cout << "Avaliacao: ";
	cin >> novo.rate;
	cout << "Quantidade de Avaliacoes: ";
	cin >> novo.rateSize;
	livros[tamanho] = novo;
	tamanho++;
	return livros;
}

book* Deletar(book *livros, int &tamanho)
{
	int idp;
	string aux;
	cout << "Deseja deletar o dado de qual ID?" << endl;
	cin >> idp;
	int posicao = Busca_binaria(livros, 0, tamanho - 1, idp);
	if (posicao != -1)
	{
		if (posicao == tamanho)
		{
			livros = diminuir(livros, tamanho);
			cout << "Livro excluido com Sucesso" << endl;
			return livros;
		}
		else
		{
			for (int h = posicao; h < (tamanho - 1); h++)
			{
				livros[h] = livros[h + 1];
			}

			livros = diminuir(livros, tamanho);
			cout << "Livro excluido com SUCESSO" << endl;
			return livros;
		}
	}
	else
	{
		cout << "Livro nao Encontrado Para Ser Deletado" << endl;
	}

	return 0;
}

book* Modificar(book *livros, int &tamanho)
{
	book novo;
	cout << "Digite o ID do item a ser modificado: " << endl;
	cin >> novo.id;
	int posicao = Busca_binaria(livros, 0, tamanho - 1, novo.id);
	if (posicao != -1)
	{
		string aux;
		cout << "NOVO titulo: ";
		cin.ignore();
		getline(cin, aux);
		strcpy(novo.title, aux.c_str());
		cout << "NOVO nome do autor: ";
		getline(cin, aux);
		strcpy(novo.author, aux.c_str());
		cout << "NOVO ano de lancamento: ";
		cin >> novo.releaseYear;
		cout << "NOVA sinopse: ";
		cin.ignore();
		getline(cin, aux);
		strcpy(novo.description, aux.c_str());
		cout << "NOVA quantidade de paginas: ";
		cin >> novo.sizeb;
		cout << "NOVA avaliacao: ";
		cin >> novo.rate;
		cout << "NOVA quantidade de avaliacao; ";
		cin >> novo.rateSize;
		livros[posicao] = novo;
		return livros;
	}
	else
	{
		cout << "Item nao encontrado :(" << endl;
	}

	return 0;
}

void Upload(book *livros, int &tamanho, string nome)
{
	cout << "Uploud de um BIN  para txt (para verificacao de funcionamento)";
	ofstream arqBin("NOVObooks.txt", ios::binary);
	arqBin.write(reinterpret_cast<const char*> (&livros), sizeof(book) *tamanho);
	arqBin.close();
	cout << "Arquivo BIN em txt Salvo com Sucesso!" << endl;
	cout << "__________________________________________________100%" << endl;
	cout << "Atualizacao de Arquivo CSV" << endl;
	ofstream arquivo(nome);
	for (int i = 0; i < tamanho; i++)
	{
		arquivo << livros[i].id << ',' <<
			livros[i].title << ',' <<
			livros[i].author << ',' <<
			livros[i].releaseYear << ',' <<
			livros[i].description << ',' <<
			livros[i].sizeb << ',' <<
			livros[i].rate << ',' <<
			livros[i].rateSize << endl;
	}

	cout << "Aquivo CSV atualizado com sucesso!" << endl;
}

void Menu(book *livros, int &tamanho, ifstream &arquivo, string nome)
{
	cout << "Criacao de Recursos Para Arquivo Binario (Por Enquanto Inativo Ate que uma Opcao que necessite Dele Seja Utilizada)" << endl << "_____________________________________" << endl;
	bool menu = true;
	int escolha;
	while (menu)
	{
		cout << "----Menu----" << endl << "Que operacao voce deseja fazer?\n| 1- Listar | 2- Adicionar um novo livro | 3- Editar um livro |\n| 4- Deletar um livro | 5- Upload arquivo | 6- Organizar (Ordenar) | 0 - SAIR |" << endl;
		cin >> escolha;
		if (escolha == 1)
		{
			Listar(livros, tamanho, arquivo);
		}
		else if (escolha == 2)
		{
			livros = Adicionar(livros, tamanho);
		}
		else if (escolha == 3)
		{
			livros = Modificar(livros, tamanho);
		}
		else if (escolha == 4)
		{
			livros = Deletar(livros, tamanho);
		}
		else if (escolha == 5)
		{
			Upload(livros, tamanho, nome);
		}
		else if (escolha == 6)
		{
			cout << "Deseja Organizar Por:\n| 1 - Avaliacoes | 2 - Autor | 3 - Titulo | 4 - ID |" << endl;
			int escolhaO;
			cin >> escolhaO;
			if (escolhaO == 1) QuicksortRate(livros, 0, tamanho - 1);
			else if (escolhaO == 2) Selection_sortAutor(livros, tamanho);
			else if (escolhaO == 3) Selection_sortTitulo(livros, tamanho);
			else if (escolhaO == 4) QuicksortID(livros,0,tamanho-1);
			else cout << "Voce deve ter se enganado..." << endl;
		}
		else if (escolha == 0)
		{
			cout << "_______Obrigado por utilizar o Hiper Mini Sistema de Controle de Arquivos CSV e Binarios________<3";
			menu = false;
		}
		else
		{
			cout << "Acho que voce se enganou, tente de novo >>" << endl;
		}
	}
}

int main()
{
	int tamanho = 1;
	book * livros;
	livros = new book[tamanho];
	bool verificacao = true;
	int escolhaArq = 0;
	string nome;
	while (verificacao)
	{
		cout << "Existem dois bancos de dados que voce pode utilizar, ambos na mesma formatacao" << endl << "| 1 - Organizado PT-BT | 2 - Maior Fluxo de Dados EN |" << endl;
		cin >> escolhaArq;
		if (escolhaArq == 1)
		{
			nome = "books.csv";
			verificacao = false;
		}
		else if (escolhaArq == 2)
		{
			nome = "altbooks.csv";
			verificacao = false;
		}
		else
		{
			cout << "Acho que voce se enganou...";
		}
	}

	ifstream arquivo(nome, ios::binary);
	if (!arquivo)
	{
		cout << "Arquivo CSV não existe" << endl;
	}
	else
	{
		//Realiza A leitura do arquivo dentro da main (assim não dá problema com mudança de valores do vetor)
		livros = Ler(livros, tamanho, arquivo);
		//terminou a leitura, agora vem o programa em sí
		Menu(livros, tamanho, arquivo, nome);
		arquivo.close();
		delete[] livros;
	}

	return 0;
}
