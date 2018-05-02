// Declarações do programa de lista ligada simples
#include <iostream>
#include <Windows.h>
using namespace std;
// defines do programa
#define PAUSA							system("pause")
#define LIMPAR_TELA						system("cls")
// defines do menu
#define INCLUIR_PRODUTO					'I'
#define EXCLUIR_PRODUTO					'E'
#define LISTAR_PRODUTOS					'L'
#define MOSTRAR_PRODUTO					'M'
#define SAIR_DO_PROGRAMA				'S'
// struct do produto
typedef struct tagPRODUTO
{
	int nCodigo;											// codigo do produto
	char szDescricao[41];									// descrição do produto
	double dPrecoUnit;										// preço unitário
	tagPRODUTO *ptrProximo;									// ponteiro para o próximo produto
} PRODUTO;

class clProduto
{
	// atributos private da classe
private:
	PRODUTO *ptrPrimeiro,									// ponteiro para o primeiro produto da lista
		*ptrWork,											// ponteiro de trabalho
		stProduto;											// struct para conter um produto
public:
	// Método construtor da classe
	clProduto()
	{
		ptrPrimeiro = NULL;									// lista ligada vazia
	}
	// Método público que verifica se o produto já está na lista
	// Parâmetros:
	//	Entrada: int nCodigo - código do produto a ser pesquisado
	//			 PRODUTO *ptrStProduto - ponteiro de uma struct a receber os dados do
	//									produto se ele já existe
	//	Retorno: true - o produto já existe e seus dados estão na struct cujo o
	//									endereço foi passado
	//			 false - o produto não existe
	bool VerificaSeExiste(int nCodigo, PRODUTO *ptrStProduto)
	{
		// loop para varrer a lista ligada até o fim
		for (ptrWork = ptrPrimeiro;							// inicializa apontando para o primeiro
		ptrWork;										// false é nulo e true não é nulo
			ptrWork = ptrWork->ptrProximo)					// encadeia com o próximo da lista
		{	// ptrWork contém um produto da lista
			if (nCodigo == ptrWork->nCodigo)					// mesmo código de produto?
			{	// encontrou o produto
				memcpy_s(ptrStProduto, sizeof(PRODUTO), ptrWork, sizeof(PRODUTO));
				return true;								// indica que tem o produto
			}
			else if (ptrWork->nCodigo> nCodigo)			//Codigo maior do que o desejado?
			{//encontrou o codigo maior - portanto o produto nao existe 
				return false;								//avisa que nao existe 
			}
		} // for
		  // varreu a lista inteira e não encontrou o produto
		return false;										//avisa que nao encontrou 
	}
	//Método que lista os produtos da lista ligada
	bool ListagemProdutos()
	{
		char cWork[200];
		LIMPAR_TELA;
		cout << "\tListagem dos produtos" << endl <<			// cabeçalho da listagem
			"  Codigo  Descricao						    Preco" << endl;
		// loop para varrer a lista ligada até o fim
		for (ptrWork = ptrPrimeiro;							// inicializa apontando para o primeiro
		ptrWork;										// false é nulo e true não é nulo
			ptrWork = ptrWork->ptrProximo)					// encadeia com o próximo da lista
		{	// ptrWork contém um produto da lista
			sprintf_s(cWork, sizeof(cWork), " %7d  %-50s  %10.2f",
				ptrWork->nCodigo, ptrWork->szDescricao, ptrWork->dPrecoUnit);
			cout << cWork << endl;
		} // for
		cout << "\tFim da listagem!" << endl;
		PAUSA;
		return true;
	}
	// Método público para inserir um produto na lista ligada em ordem crescente de codigo 
	//	Parâmetros:
	//		Entrada: PRODUTO *ptrStProduto - ponteiro para uma struct do invocador do
	//										 método que contém os dados do produto
	//		Retorno: true - inserção foi OK
	//				 false - não tem memória para o novo produto da lista
	bool IsereNaLista(PRODUTO *ptrStProduto)
	{
		PRODUTO *ptrAnterior,								//ponteiro do produto anterior 
			*ptrSalva;										//para salvar ponteiros que serao destruidos pelo new
		bool flgPrimeiro = true;								//indica que nao percorremos a lista ainda 
		if (ptrPrimeiro == NULL)							//vai ser o primeiro da lista ?
		{//vai ser o primeiro
			ptrPrimeiro = new PRODUTO;						//aloca memoria para o produto
			if (ptrPrimeiro == NULL)						//nao tem memoria?
				return false;								//avisa que nao tem memoria 
			memcpy_s(ptrPrimeiro, sizeof(PRODUTO), ptrStProduto, sizeof(PRODUTO));
			ptrPrimeiro->ptrProximo = NULL;					//indica o ultimo da lista 
			return true;									//indica que a inclusao foi ok
		}
		//Nao é o primeiro da lista - varrer a lista procurando o espaço para a insercao
		for (ptrAnterior = ptrWork = ptrPrimeiro;			//inicializacao
		ptrWork;										//Null é falso e fim da lista 
			ptrWork = ptrWork->ptrProximo, flgPrimeiro = false)
		{//ptrWork aponta para o produto corrente 
			if (ptrWork->nCodigo > ptrStProduto->nCodigo)	//insere antes do corrente?
			{//vai inserir antes do corrente 
				if (flgPrimeiro)							//antes do primeiro  
				{	//insercao antes do primeiro - o inserido agora sera o primeiro 
					//e o primeiro sera o proximo do corrente
					ptrSalva = ptrPrimeiro;					//salva o ponteiro seguinte 
					ptrPrimeiro = new PRODUTO;				//aloca memoria 
					if (ptrPrimeiro == NULL)
					{	//nao tem memoria disponivel 
						ptrPrimeiro = ptrSalva;				//restaura a ligação da lista 
						return false;						// retorna em condicao de erro 
					}
					memcpy_s(ptrPrimeiro, sizeof(PRODUTO), ptrStProduto, sizeof(PRODUTO));
					ptrPrimeiro->ptrProximo = ptrSalva;		//liga com o proximo 
					return true;							//retorna indicando ok
				}
				else
				{	//é um produto a ser inserido  no meio da lista 
					// o aterior esta apontando para o seguinte deste produto
					ptrSalva = ptrAnterior->ptrProximo;		//salva o ponteiro do seguinte 
					ptrAnterior->ptrProximo = new PRODUTO;	//aloca memoria 
					if (ptrAnterior->ptrProximo == NULL)	//nao tem memoria?
					{	//nao tem memoria - restaurar a ligação da lista 
						ptrAnterior->ptrProximo = ptrSalva;	//restaura
						return false;						//indica que nao tem memoria 
					}
					memcpy_s(ptrAnterior->ptrProximo, sizeof(PRODUTO), ptrStProduto, sizeof(PRODUTO));
					ptrAnterior->ptrProximo->ptrProximo = ptrSalva; //liga com o seguinte 
					return true;							//indica tudo ok
				}

			}
			else //codigo do corrente é menor que vai inserir  
				ptrAnterior = ptrWork;						//o corrente é o anterior 
		}//for 
		 //percorremos a lista e nao inserimos - vamos inserir este como ultimo 
		ptrAnterior->ptrProximo = new PRODUTO;				//aloca memoria 
		if (ptrAnterior->ptrProximo == NULL)				//sem memoria?
			return false;									//retorna indicando erro 
		memcpy_s(ptrAnterior->ptrProximo, sizeof(PRODUTO), ptrStProduto, sizeof(PRODUTO));
		ptrAnterior->ptrProximo->ptrProximo = NULL;			//ultimo da lista 
		return true;										//indica tudo ok
	}
	// Método público que exclui um produto da lista
	//	Parâmetros:
	//		Entrada: int nCodigo - código do produto a ser excluido
	//		Retorno: bool - true - produto excluido com sucesso
	//						false - produto não existe
	bool ExcluirProduto(int nCodPro)
	{
		PRODUTO *ptrAnterior,					// para receber o endereço do produto anterior
			*ptrSalvaProximo;					// para salvar o ponteiro do próximo a ligar
												// com o anterior do corrente
		bool flgProximo;						// true - indica que já percorreu e não encontrou 
												// pelo menos um produto da lista ligada
		for (flgProximo = false, ptrAnterior = ptrWork = ptrPrimeiro;    // inicialização
		ptrWork;							// produto corrente e nulo é o último
			ptrWork = ptrWork->ptrProximo)		// o corrente será o próximo
		{
			if (nCodPro > ptrWork->nCodigo) // não é o desejado?
			{	// não é o desejado
				ptrAnterior = ptrWork;			// o corrente é o anterior do próximo
				flgProximo = true;				// indica que o corrente não o desejado
				continue;						// vai ver se o póximo é o desejado
			} // não o desejado
			if (nCodPro < ptrWork->nCodigo)	// não encontrou o desejado?
				return false;
			// encontramos o desejado
			// vamos salvar o endereço do próximo que está no corrente
			ptrSalvaProximo = ptrWork->ptrProximo;
			delete ptrWork;						// devolve a memória do cliente corrente que é excluido
			if (flgProximo)						// não é o primeiro
			{	// não é o primeiro da lista
				ptrAnterior->ptrProximo = ptrSalvaProximo;
			}
			else								// é o primeiro da lista
			{
				ptrPrimeiro = ptrSalvaProximo;
			}
			return true;
		}
		// não encontrou o desejado
		return false;							// indica que não encontrou
	}

};//fim da classe 
