#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }
  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i,j;
    for(i=0;i<9;i++){
      int filas[10] = {0};
      int columnas[10] = {0};
      for(j=0;j<9;j++){
        if (n->sudo[i][j] != 0) {
          if (n->sudo[i][j] == 1) return 0;
          filas[n->sudo[i][j]] = 1;
        }
        if (n->sudo[i][j] != 0){
          if(columnas[n->sudo[i][j]] == 1) return 0;
          columnas[n->sudo[i][j]] = 1;
          }
        }
       }
  for (i = 0; i < 9; i++) {
    int submatriz[10] = {0};
    int fila_inicio = (i / 3) * 3;
    int col_inicio = (i % 3) * 3;
    for (j = 0; j < 9; j++) {
      int fila = fila_inicio + j / 3;
      int col = col_inicio + j % 3;
      if (n->sudo[fila][col] != 0) {
        if (submatriz[n->sudo[fila][col]] == 1) {
          return 0; 
        }
        submatriz[n->sudo[fila][col]] = 1;
        }
      }
    }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  if (is_valid(n) == 1) return list;
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if (n->sudo[i][j] == 0){
        for(int a = 1; a <= 9; a++){
          Node* new_node = copy(n);
          new_node->sudo[i][j]= a;
          pushBack(list,new_node);
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/