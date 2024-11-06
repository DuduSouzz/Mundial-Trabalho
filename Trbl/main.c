#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[40];
  int codigo, quantidade;
  float preco;
} Fruta;

// Estrutura de lista encadeada para armazenar as frutas
typedef struct Lista{
  Fruta fruta;
  struct Lista *prox;
} Lista;

// Função para verificação do nome da mesma
int verifFruta(Lista *iniciolista, Fruta novaFruta){
  Lista *atual = iniciolista;
  while (atual != NULL){
    if (atual->fruta.codigo == novaFruta.codigo){
      printf("\nOpps! Já existe uma fruta cadastrada\ncom esse código!\nTente outro\n", novaFruta.codigo);
      return 1;
    }
    if (strcmp(atual->fruta.nome, novaFruta.nome) == 0){
      printf("Opps! Essa fruta já foi cadastrada. Tente outra\n", novaFruta.nome);
      return 1;
    }
    atual = atual->prox;
  }
  return 0;
}

// Função para adicionar uma fruta ao final da lista
Lista *adicionar_fruta(Lista *iniciolista, Fruta novaFruta){
  if (verifFruta(iniciolista, novaFruta)){
    printf("Opps! Não é possível cadastrar essa fruta por já existir. \n");
    return iniciolista;
  }

  Lista *novoNo = (Lista *)malloc(sizeof(Lista));
  if (novoNo == NULL){
    printf("Ocorreu um erro ao alocar memória!\n");
    return iniciolista;
  }

  novoNo->fruta = novaFruta;
  novoNo->prox = NULL;

  if (iniciolista == NULL){
    return novoNo;
  } else{
    Lista *atual = iniciolista;
    while (atual->prox != NULL){
      atual = atual->prox;
    }
    atual->prox = novoNo;
    return iniciolista;
  }
}

// Função para listar as frutas cadastradas na lista
void listarFrutas(Lista *iniciolista){
  Lista *atual = iniciolista;
  if (atual == NULL){
    printf("A lista está vazia.\n");
  } else {
    printf("Frutas cadastradas:\n");
    while (atual != NULL){
      printf("Código: %d\n •Nome: %s\n •Quantidade: %d\n •Preço: R$%.2f\n\n",
             atual->fruta.codigo, atual->fruta.nome, atual->fruta.quantidade,
             atual->fruta.preco);
      atual = atual->prox;
    }
  }
}
void buscarfruta(Lista *iniciolista, int codigo){
  Lista *atual = iniciolista;
  while (atual != NULL){
    if (atual->fruta.codigo == codigo){
      printf("Sua fruta foi encontrada:\n");
      printf("Código: %d\n", atual->fruta.codigo);
      printf("Nome: %s\n", atual->fruta.nome);
      printf("Quantidade: %d\n", atual->fruta.quantidade);
      printf("Preço: %.2f\n\n", atual->fruta.preco);
      return;
    }
    atual = atual->prox;
  }
  printf("Código errado ou fruta não cadastrada!\n");
}
void alterarDados(Lista *iniciolista, int codigo){
  Lista *atual = iniciolista;
  while (atual != NULL){
    if (atual->fruta.codigo == codigo){
      printf("Sua fruta foi encontrada:\n");
      printf("Código: %d\n", atual->fruta.codigo);
      printf("Nome: %s\n", atual->fruta.nome);
      printf("Quantidade: %d\n", atual->fruta.quantidade);
      printf("Preço: %.2f\n", atual->fruta.preco);

      // Alterção dos dados
      printf("\nInsira os novos dados: \n");
      printf("Nome da fruta: ");
      scanf("%s", atual->fruta.nome);
      printf("Quantidade que deseja: ");
      scanf("%d", &atual->fruta.quantidade);
      printf("Novo preço: ");
      scanf("%f", &atual->fruta.preco);

      // Alteração feita

      printf("\nOs dados da fruta foram alterados!\n");

      // Fruta após a alteração
      printf("\nDados atualizados:\n");
      printf("Código: %d\n", atual->fruta.codigo);
      printf("Nome: %s\n", atual->fruta.nome);
      printf("Quantidade: %d\n", atual->fruta.quantidade);
      printf("Preço: R$ %.2f\n", atual->fruta.preco);

      return;
    }
    atual = atual->prox;
  }
  printf("Código errado ou fruta não cadastrada!\nLogo, não foi possível "
         "alterar os dados da fruta.\n");
}
void excluirFruta(Lista **iniciolista, int codigo){
  Lista *atual = *iniciolista;
  Lista *anterior = NULL;

  while (atual != NULL){
    if (atual->fruta.codigo == codigo){

      // Verifica a quantidade da fruta
      if (atual->fruta.quantidade > 0){
        printf("Não pode excluir a fruta, pois ainda há estoque!");
        return;
      }
      if (anterior == NULL){
        *iniciolista = atual->prox;
      } else{
        anterior->prox = atual->prox;
      }
      free(atual);
      printf("Essa fruta %d foi excluída!\n", codigo);
      return;
    }
    anterior = atual;
    atual = atual->prox;
  }
  printf("Código errado ou fruta não cadastrada!\n");
}
void vendasfrutas(Lista **iniciolista, int codigo, int vendas_quant, int *quantidade_vendas){
  Lista *atual = *iniciolista;
  while (atual != NULL){
    if(atual->fruta.codigo == codigo){
      
        //Verifica se a quantidade de estoque da fruta se é maior que a quantidade de vendas pedida
        if (atual->fruta.quantidade >= vendas_quant){
          atual->fruta.quantidade -= vendas_quant; 
          (*quantidade_vendas) += vendas_quant;
        printf("Sua venda foi realizada!\n");
        printf("Fruta: %s\n", atual->fruta.nome);
        printf("Código: %d\n", atual->fruta.codigo);
        printf("Quantidade vendida: %d\n", vendas_quant);
        printf("Estoque restante: %d\n", atual->fruta.quantidade);

        printf("Preço da unidade: R$ %.2f\n", atual->fruta.preco);
          if (atual->fruta.preco > 0){
            carrinhoResg(codigo, atual->fruta.nome, vendas_quant, atual->fruta.preco, atual->fruta.quantidade);
          }else{
            printf("Preço incorreto!\n");
          }
        }else{
          printf("Não temos estoque suficiente para a venda!\n");
        }
      return;
    }
    atual = atual->prox;
  }
  printf("Código errado ou fruta não cadastrada!\n");
}

// Liberando a memória da lista alocada
void liberandolista(Lista **iniciolista){
  Lista *atual = *iniciolista;
  Lista *lib;

  while(atual != NULL){
    lib = atual;
    atual = atual->prox;
    free(lib);
  }
  *iniciolista = NULL;
}

int main(){
  Lista *iniciolista = NULL;
  int opcao;
  int quantidade_vendas = 0;
  do{
      // Menu do switch
      printf("\n==     Mercado Mundial    ==\n");
      printf("\n       Seja bem-vindo!     \n");
      printf("\n1. Adicionar fruta\n");
      printf("2. Listar frutas\n");
      printf("3. Buscar fruta\n");
      printf("4. Alterar dados da fruta\n");
      printf("5. Excluir fruta\n");
      printf("6. Vender fruta\n");
      printf("7. Sair\n");
      printf("\n        Escolha uma opção: ");
      scanf("%d", &opcao);

      switch (opcao){
          case 1: {
              Fruta novaFruta;
              printf("Nome da fruta: ");
              scanf("%s", novaFruta.nome);
              printf("Código da fruta: ");
              scanf("%d", &novaFruta.codigo);
              printf("Quantidade da fruta: ");
              scanf("%d", &novaFruta.quantidade);
              printf("Preço da fruta: ");
              scanf("%f", &novaFruta.preco);
              iniciolista = adicionar_fruta(iniciolista, novaFruta);
              break;
          }
          case 2: {
              listarFrutas(iniciolista);
              break;
          }
          case 3: {
              int codigo_buscado;
              printf("Informe o código da fruta a ser buscada: ");
              scanf("%d", &codigo_buscado);
              buscarfruta(iniciolista, codigo_buscado);
              break;
          }
          case 4: {
              int codigo_alterar;
              printf("Informe o código da fruta a ser alterada: ");
              scanf("%d", &codigo_alterar);
              alterarDados(iniciolista, codigo_alterar);
              break;
          }
          case 5: {
              int codigo_excluir;
              printf("Informe o código da fruta a ser excluída: ");
              scanf("%d", &codigo_excluir);
              excluirFruta(&iniciolista, codigo_excluir);
              break;
          }
          case 6: {
              int venda_codigo;
              int vendas_quant; 
              printf("Insira o código da fruta que deseja vender: ");
              scanf("%d", &venda_codigo);
              printf("Insira a quantidade que deseja vender: ");
              scanf("%d", &vendas_quant);

              vendasfrutas(&iniciolista, venda_codigo, vendas_quant, &quantidade_vendas);
              break;
          }
        case 7: {
        printf("\n         Saindoo do mercado!\n");
        break;
        }
        default:
        printf("Opção não aceita. Tente novamente.\n");
      }
  }while (opcao != 7);

  liberandolista(&iniciolista);
  printf("\nRealizada a liberação de memória do programa!\n");
  return 0;
}