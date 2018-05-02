// Programa de lista ligada simples com insercao de codigo
// FATEC-MC - EPT -LSP - 11/08/2016 - Versão 0.0
#include "Lista.h"
// Função que pede um código de produto ou zero para cancelar a ação
// Parâmetros:
//		Entrada: int *ptrCodigo - ponteiro de uma inteira que receberá o código do produto
//				 char *ptrTransacao - legenda da transação sendo executada
//		Retorno: true - um código foi informado
//				 false - zero foi digitado para cancelar a transação
bool PedeCodigo(int *ptrCodigo, char *ptrTransacao)
{
	cout << "\n\t" << ptrTransacao << endl;			// exibe a legenda da transação
	cout << "Informe o codigo ou zero para cancelar a transacao: ";
	cin >> *ptrCodigo;								// informa o código
	if (*ptrCodigo == 0)								// cancelou a transação?
		return false;								// avisa que cancelou
	return true;									// avisa que tem um código
}
// entry point do programa
void main(void)
{
	PRODUTO stProduto;								// struct para conter os dados de um produto
	char cOpcao;									// recebe a opção do operador
	setlocale(LC_ALL, "portuguese_brazil");			// aceita acentuação brasileira
													// instancia a classe produto e cria o objeto
	clProduto objProduto;							// cria o objeto
	while (true)										// loop infinito do programa
	{
		LIMPAR_TELA;
		cout << "\n\tPrograma de lista ligada simples" << endl;
		cout << INCLUIR_PRODUTO << " - Inclusao de um novo produto" << endl;
		cout << EXCLUIR_PRODUTO << " - Exclusao de um produto existente" << endl;
		cout << LISTAR_PRODUTOS << " - Listagem dos produtos da lista" << endl;
		cout << MOSTRAR_PRODUTO << " - Mostrar os dados de um produto" << endl;
		cout << SAIR_DO_PROGRAMA << " - Sair do programa" << endl;
		cout << "\tSelecione: ";
		cin >> cOpcao;						// opção do operador
		cOpcao = toupper(cOpcao);			// converte para maiúscula
		switch (cOpcao)						// avaliar a opção escolhida
		{
		case INCLUIR_PRODUTO:
			if (!PedeCodigo(&stProduto.nCodigo, "Incluir produto")) // cancelou?
				break;					// retorna ao menu
										// verificar se o produto já está na lista
			if (objProduto.VerificaSeExiste(stProduto.nCodigo, &stProduto)) // já existe?
			{	// produto já existe
				cout << "\nCodigo: " << stProduto.nCodigo << " Descricao: "
					<< stProduto.szDescricao << endl
					<< "Preco Unitario: " << stProduto.dPrecoUnit
					<< " ja existe!" << endl;
				PAUSA;
				break;					// retorna ao menu
			}
			cin.ignore(1, EOF);			// ignorar a tecla Enter do código do produto
			cout << "Descricao: ";
			cin.getline(stProduto.szDescricao, 40, '\n'); // recebe a descrição
			cout << "Preco Unitario: ";
			cin >> stProduto.dPrecoUnit;		// recebe preço unitário
												// fazer a inserção
			if (!objProduto.IsereNaLista(&stProduto)) // inserção com problema?
			{
				cout << "Nao tem memoria disponivel!" << endl;
				PAUSA;
			}
			break;						// retorna ao menu
		case EXCLUIR_PRODUTO:
			if (!PedeCodigo(&stProduto.nCodigo, "Incluir produto")) // cancelou?
				break;					// retorna ao menu
										// verificar se o produto já está na lista
			if (objProduto.VerificaSeExiste(stProduto.nCodigo, &stProduto)) // já existe?
			{	// produto já existe
				cout << "\nCodigo: " << stProduto.nCodigo << " Descricao: "
					<< stProduto.szDescricao << endl
					<< "Preco Unitario: " << stProduto.dPrecoUnit
					<< "\nDeseja realmente excluir este produto? (S ou N):"<<endl;
				cin >> cOpcao;
				if (cOpcao == 'S' || cOpcao == 's')//deseja realmente excluir o produto
				{//ta exluindo
					if (!objProduto.ExcluirProduto(stProduto.nCodigo))	// exclusão com problema?
					{
						cout << "Problema na exclusão do cliente " << stProduto.nCodigo << endl;
						PAUSA;
						break;
					}
				}
			}
			else						// produto não existe		
			{
				cout << "Cliente: " << stProduto.nCodigo << " não existe!" << endl;
				PAUSA;
			}
			break;
		case LISTAR_PRODUTOS:
			objProduto.ListagemProdutos();
			break;						// retorna ao menu
		case MOSTRAR_PRODUTO:
			if (!PedeCodigo(&stProduto.nCodigo, "Mostrar produto"))
				break;					// retorna ao menu
			if (objProduto.VerificaSeExiste(stProduto.nCodigo, &stProduto))
			{	// produto existe
				cout << "\nCodigo: " << stProduto.nCodigo << " Descricao: "
					<< stProduto.szDescricao << endl
					<< "Preco Unitario: " << stProduto.dPrecoUnit << endl;
			}
			else
			{	// produto não existe
				cout << "\nProduto não existe!" << endl;
			}
			PAUSA;
			break;						// retorna ao menu
		case SAIR_DO_PROGRAMA:
			cout << "Sair realmente? (S ou N): ";
			cin >> cOpcao;
			if (cOpcao == 's' || cOpcao == 'S')	// sair realmente?
				return;					// volta ao sistema operacional
			break;						// retorna ao menu
		default:
			cout << "\nOpção invalida!" << endl;
			PAUSA;
		} // switch
	} // while
} // main