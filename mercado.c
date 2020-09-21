#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
//#include <unistd.h> "Para quem usa Linux/Mac"

typedef struct {
	int codigo;
	char nome[30];
	float preco;

} Produto;

typedef struct {
	Produto produto;
	int quantidade;
} Carrinho;

void infoProduto(Produto prod);
void menu();
void cadastrarProduto();
void comprarProduto();
void listarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();


static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[100];
static Produto produtos[100];

int main(){
	menu();
	return 0;
}

void infoProduto(Produto prod){
	printf("Código do Produto: %d \nNome: %s \nPreço: %.2f \n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}

void  menu(){
	printf("==================================================================\n");
	printf("===========================BEM-VINDO(a)===========================\n");
	printf("=========================SISTEMA MERCADO==========================\n");
	printf("==================================================================\n");

	printf("Selecione uma opção a baixo: \n");
	printf("1 - Cadastrar produto\n");
	printf("2 - Listar produtos\n");
	printf("3 - Comprar produto\n");
	printf("4 - Visualizar carrinho\n");
	printf("5 - Fechar pedido\n");
	printf("6 - Sair do sistema\n");

	int opcao;
	scanf("%d", &opcao);
	getchar(); //para não pular e não bugar quando seleciona

	switch (opcao){
	case 1:
		cadastrarProdut0();
		break;
	case 2:
		listarProdutos();
		break;
	case 3:
		comprarProduto();
		break;
	case 4:
			visualizarCarrinho();
			break;
	case 5:
			fecharPedido();
			break;
	case 6:
		printf("Volte Sempre!  \n");
		Sleep(2); //sleep com S minusculo para Linux e MAC
		exit(0);
	default:
		printf("Digite uma opção válida!!!");
		Sleep(2);
		menu();
		break;
	}
}

void cadastrarProduto(){
	printf("Cadastro de Produto\n");
	printf("===================");

	printf("Informe o nome do produto: \n");
	fgets(produtos[contador_produto].nome, 30, stdin);

	printf("Informe o preco do produto: \n");
	scanf("$f", &produtos[contador_produto].preco);

	printf("O Produto %s foi cadastrado com sucesso./n", strtok(produtos[contador_produto].nome,  "\n"));

	produtos[contador_produto].codigo = (contador_produto +  1);
	contador_produto++; //IMPORTANTE PARA NÃO CADASTRAR OUTRO PRODUTO EM CIMA DO ANTERIOR
}

void listarProduto(){
	if(contador_produto > 0){
		printf("Listagem de Produtos.\n");
		printf("=====================\n");
		for (int i = 0; i < contador_produto; i++){  //LISTAR OS PRODUTOS
			infoProduto(produtos[i]);
			printf("-----------------\n");
			Sleep(1);
		}
	}else{
		printf("Não temos produtos cadastrados. \n");
	}
}

void comprarProduto(){
	//
}

void visualizarCarrinho(){
	//
}

Produto pegarProdutoPorCodigo(int codigo){
	//
}

int * temNoCarrinho(int codigo){
	//
}

void fecharPedido(){
	//
}
