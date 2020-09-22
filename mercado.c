#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // No Linux/Mac
//#include <windows.h>

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
void listarProdutos();
void comprarProduto();
void visualizarCarrinho();
Produto pegarProdutoPorCodigo(int codigo);
int * temNoCarrinho(int codigo);
void fecharPedido();

static int contador_produto = 0;
static int contador_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];


int main(){
	menu();
	return 0;
}

void infoProduto(Produto prod){
	printf("Código: %d \nNome: %s \nPreço: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}

void menu(){
	printf("=========================================\n");
	printf("================ Bem-vindo(a) ===========\n");
	printf("================  Geek Shop   ===========\n");
	printf("=========================================\n");

	printf("Selecione uma opção abaixo: \n");
	printf("1 - Cadastrar produto\n");
	printf("2 - Listar produtos\n");
	printf("3 - Comprar produto\n");
	printf("4 - Visualizar carrinho\n");
	printf("5 - Fechar pedido\n");
	printf("6 - Sair do sistema\n");

	int opcao;
	scanf("%d", &opcao);
	getchar();

	switch (opcao) {
		case 1:
			cadastrarProduto();
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
			printf("Volte sempre!\n");
			sleep(2); //Sleep(2)
			exit(0);
		default:
			printf("Opção inválida.\n");
			sleep(2);
			menu();
			break;
	}
}

void cadastrarProduto(){
	printf("Cadastro de Produto\n");
	printf("====================\n");

	printf("Informe o nome do produto: \n");
	fgets(produtos[contador_produto].nome, 30, stdin);

	printf("Informe o preço do produto: \n");
	scanf("%f", &produtos[contador_produto].preco);

	printf("O produto %s foi cadastrado com sucesso.\n", strtok(produtos[contador_produto].nome, "\n"));

	produtos[contador_produto].codigo = (contador_produto + 1);
	contador_produto++;

	sleep(2);
	menu();
}

void listarProdutos(){
	if(contador_produto > 0){
		printf("Listagem de produtos.\n");
		printf("---------------------\n");
		for(int i = 0; i < contador_produto; i++){
			infoProduto(produtos[i]);
			printf("------------------\n");
			sleep(1);
		}
		sleep(2);
		menu();
	}else{
		printf("Não temos ainda produtos cadastrados.\n");
		sleep(2);
		menu();
	}
}

void comprarProduto(){
	if(contador_produto > 0){
		printf("Informe o código do produto que deseja adicionar ao carrinho.\n");

		printf("========== Produtos Disponíveis ===========\n");
		for(int i = 0; i < contador_produto; i++){
			infoProduto(produtos[i]);
			printf("---------------------\n");
			sleep(1);
		}
		int codigo;
		scanf("%d", &codigo);
		getchar();

		int tem_mercado = 0;
		for(int i = 0; i < contador_produto; i++){
			if(produtos[i].codigo == codigo){
				tem_mercado = 1;

				if(contador_carrinho > 0){
					int * retorno = temNoCarrinho(codigo);

					if(retorno[0] == 1){
						carrinho[retorno[1]].quantidade++;
						printf("Aumentei a quantidade do produto %s já existente no carrinho.\n",
								strtok(carrinho[retorno[1]].produto.nome, "\n"));
						sleep(2);
						menu();
					}else{
						Produto p = pegarProdutoPorCodigo(codigo);
						carrinho[contador_carrinho].produto = p;
						carrinho[contador_carrinho].quantidade = 1;
						contador_carrinho++;
						printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
						sleep(2);
						menu();
					}
				}else{
					Produto p = pegarProdutoPorCodigo(codigo);
					carrinho[contador_carrinho].produto = p;
					carrinho[contador_carrinho].quantidade = 1;
					contador_carrinho++;
					printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
					sleep(2);
					menu();
				}
			}
		}
		if(tem_mercado < 1){
			printf("Não foi encontrado o produto com código %d.\n", codigo);
			sleep(2);
			menu();
		}
	}else{
		printf("Ainda não existem produtos para vender.\n");
		sleep(2);
		menu();
	}
}

void visualizarCarrinho(){
	if(contador_carrinho > 0){
		printf("Produtos do Carrinho\n");
		printf("--------------------\n");
		for(int i = 0; i < contador_carrinho; i++){
			infoProduto(carrinho[i].produto);
			printf("Quantidade: %d\n", carrinho[i].quantidade);
			printf("-----------------\n");
			sleep(1);
		}
		sleep(2);
		menu();
	}else{
		printf("Não temos ainda produtos no carrinho.\n");
		sleep(2);
		menu();
	}
}

Produto pegarProdutoPorCodigo(int codigo){
	Produto p;
	for(int i = 0; i < contador_produto; i++){
		if(produtos[i].codigo == codigo){
			p = produtos[i];
		}
	}
	return p;
}

int * temNoCarrinho(int codigo){
	int static retorno[] = {0, 0};
	for(int i = 0; i < contador_carrinho; i++){
		if(carrinho[i].produto.codigo == codigo){
			retorno[0] = 1; //tem o produto com este código no carrinho
			retorno[1] = i; //o índice do produto no carrinho
		}
	}
	return retorno;
}

void fecharPedido(){
	if(contador_carrinho > 0){
		float valorTotal = 0.0;
		printf("Produtos do Carrinho\n");
		printf("--------------------\n");
		for(int i = 0; i < contador_carrinho; i++){
			Produto p = carrinho[i].produto;
			int quantidade = carrinho[i].quantidade;
			valorTotal += p.preco * quantidade;
			infoProduto(p);
			printf("Quantidade: %d\n", quantidade);
			printf("---------------\n");
			sleep(1);
		}
		printf("Sua fatura é R$ %.2f\n", valorTotal);

		//limpar carrinho
		contador_carrinho = 0;
		printf("Obrigado pela preferência.\n");
		sleep(5);
		menu();
	}else{
		printf("Você não tem nenhum produto no carrinho ainda.\n");
		sleep(3);
		menu();
	}
}
