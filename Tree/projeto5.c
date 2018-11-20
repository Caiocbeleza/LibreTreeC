#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct elemento {
  int info;
  struct elemento* esq;
  struct elemento* dir;
} El;

int getHeight(El *raiz);
void preencher_matriz(int **matrizNum,char **matriz,El *raiz,int altura,int nivel,int coluna);
void coloca_galhos(char **matriz,int height, int *inicio, int *fim);

El* criaArv(){
    El* r = (El *) malloc(sizeof(El));
    r = NULL;
    return r;
}

void insereArv(El** r, int valor){
    if(*r == NULL){
        *r = (El *) malloc(sizeof(El));
        (*r)->esq = NULL;
        (*r)->dir = NULL;
        (*r)->info = valor;
    }
    else{
        if(valor < (*r)->info){
            insereArv(&(*r)->esq, valor);
        }
        if(valor > (*r)->info){
            insereArv(&(*r)->dir, valor);
        }
    }
}

int isFULL(El *raiz){
  if (raiz == NULL){
     printf("Arvore esta vazia\n");
     return ;
   }
   if (raiz != NULL){
     if ((raiz->esq == NULL && raiz->dir != NULL) || (raiz->esq != NULL && raiz->dir == NULL)){
       return 0;
     }

     else{
       return isFULL(raiz->esq) * isFULL(raiz->dir);
     }
   }
   return 1;
 }

int getHeight(El *raiz){
    int u, v;

    if (raiz == NULL)
        return 0;

    u = getHeight(raiz->esq);
    v = getHeight(raiz->dir);

    if (u > v)
        return u+1;

    return v+1;
}

void printInOrder(El* r){
    if(r != NULL){
        printInOrder(r->esq);
        printf(" %d", r->info);
        printInOrder(r->dir);
    }
}

void printPreOrder(El* r){
    if(r != NULL){
        printf(" %d", r->info);
        printPreOrder(r->esq);
        printPreOrder(r->dir);
    }
}

void printPosOrder(El* r){
    if(r != NULL){
        printPosOrder(r->esq);
        printPosOrder(r->dir);
        printf(" %d", r->info);
    }
}

void showTree(El *raiz){
  if (raiz == NULL){
    return;
  }

  int height = getHeight(raiz);
  int inicio = 0;
  int fim = (pow(2,height)-1)/2;
  int **matrizNum = (int **) calloc (height,sizeof(int*));

  if(matrizNum == NULL){
     puts("Alocação Falhou!");
     exit(1);
  }

  for (int i = 0; i < (height); i++){
     *(matrizNum+i) = (int*)calloc(pow(2,height)-1,sizeof(int));

     if(*(matrizNum+i) == NULL){
        puts("Alocação Falhou!");
        exit(1);
     }
  }

  char **matriz = (char **) calloc (height-1,sizeof(char*));

  if(matriz == NULL){
     puts("Alocação Falhou!");
     exit(1);
  }

  for (int i = 0; i < (height-1); i++){
     *(matriz+i) = (char*)calloc(pow(2,height)-1,sizeof(char));

     if(*(matriz+i) == NULL){
        puts("Alocação Falhou!");
        exit(1);
     }
  }

  for (int i = 0; i < height-1; i++){
    for (int j = 0; j < pow(2,height)-1; j++){
      matriz[i][j] = ' ';
    }
  }

  preencher_matriz(matrizNum,matriz,raiz,height,0,(pow(2,height)-1)/2);

  coloca_galhos(matriz, height, &inicio, &fim);

  for (int j = inicio; j <= fim; j++){
    if (j != (int)(pow(2,height)-1)/2){
      printf(" ");
    }

    else{
      printf("%d",matrizNum[0][j]);
    }
  }

  printf("\n");

  for (int i = 0; i < height-1; i++){
    for (int j = inicio; j <= fim; j++){
      if (matriz[i][j] == '/' || matriz[i][j] == '\\'){
        for(int aux = matrizNum[i+1][j]/10; aux != 0; aux = aux/10){
          printf(" ");
        }
        printf("%c",matriz[i][j]);
      }

      else{
        printf(" ");
      }
    }
    printf("\n");

    for (int j = inicio; j <= fim; j++){
      if (matriz[i][j] == '/' || matriz[i][j] == '\\'){
        printf("%d",matrizNum[i+1][j]);
      }

      else{
        printf("%c",matriz[i][j]);
      }
    }
    printf("\n");
  }
  puts("");

   for(int i=0; i < height; i++){
      free(*(matrizNum+i));
   }

   free(matrizNum);

   for(int i=0; i < height-1; i++){
      free(*(matriz+i));
   }

   free(matriz);

}

void preencher_matriz(int **matrizNum,char **matriz,El *raiz,int altura,int linha,int coluna){
  int aux = pow(2,altura-2-linha);
  * (*(matrizNum+linha)+coluna) = raiz->info;

  if (raiz->esq != NULL){
    * (*(matriz+linha)+coluna-aux) = '/';
    preencher_matriz(matrizNum,matriz,raiz->esq,altura,linha+1,coluna-aux);
  }

  if (raiz->dir != NULL){
    * (*(matriz+linha)+coluna+aux) = '\\';
    preencher_matriz(matrizNum,matriz,raiz->dir,altura,linha+1,coluna+aux);
  }
}

void coloca_galhos(char **matriz,int height, int *inicio, int *fim){
  for (int j = 0; j < pow(2,height)-1; j++){
    for (int i = 0; i < height-1; i++){
      if (matriz[i][j] == '/' || matriz[i][j] == '\\'){
        if (! *inicio) {
          *inicio = j;
        }

        if (*fim < j) {
          *fim = j;
        }
      }
    }
  }
}

int main(){
    // L� o arquivo do diret�rio indicado por nomeArq[]
    FILE *fp;
    char nomeArq[] = "/home/caio/Projeto 5/BSTs/bst2.txt"; // Mudar o diret�rio dos arquivos aqui!!
    fp = fopen(nomeArq, "r");
    if(fp == NULL){
        printf("Falha ao abrir o arquivo.\n");
        exit(1);
    }

    // Imprime o vetor
    int num[10];
    int i, v;
    printf("Vetor: ");
    for(i = 0; i < 10; i++){
        fscanf(fp, "%d", &num[i]);
        printf(" %d", num[i]);
    }   printf("\n");

    // Cria uma �rvore vazia
    El* raiz = criaArv();

    // Insere todos os elementos na arvore
    for(i = 0; i < 10; i++){
        insereArv(&raiz, num[i]);
    }

    int continuar=1;

    do
    {

        printf("\n\n");
        printf("1. Mostrar árvore\n");
        printf("2. Mostrar inOrder\n");
        printf("3. Mostrar preOrder\n");
        printf("4. Mostrar PostOrder\n");
        printf("5. Mostrar tamanho\n");
        printf("6. isFULL\n");
        printf("0. Sair\n");

        scanf("%d", &continuar);
        system("cls || clear");

        switch(continuar)
        {
            case 1:
                system("clear");
                printf("Arvore: \n");
                showTree(raiz);
                break;

            case 2:
                system("clear");
                printf("InOrder:" );
                printInOrder(raiz);
                break;

            case 3:
                system("clear");
                printf("PreOrder:" );
                printPreOrder(raiz);
                break;

            case 4:
                system("clear");
                printf("PosOrder:" );
                printPosOrder(raiz);
                break;
            case 5:
                system("clear");
                printf("Altura da arvore: %d\n",getHeight(raiz));
                break;

            case 0:
                exit(1);
                break;

            default:
                printf("Digite uma opcao valida\n");
        }
    } while(continuar);

    return 0;
}
