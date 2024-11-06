#include <stdio.h>
#include <time.h>

void carrinhoResg(int codigo, const char *nome, int quantidade_vendida, float preco, int estoque){
  FILE *arquivo = fopen("Carrinho.txt", "a");
  if (arquivo == NULL){
    printf("Carrinho vazio! :(\n");
    return;
  }
  

  fprintf(arquivo, "Código: %d\n", codigo);
  fprintf(arquivo, "Fruta: %s\n", nome);
  fprintf(arquivo, "Quantidade vendida: %d\n", quantidade_vendida);
  fprintf(arquivo, "Estoque: %d\n", estoque);
  fprintf(arquivo, "====================================\n");

      fclose(arquivo);
}
