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

int is_valid(Node* n) {
  int i, j;

  for (i = 0; i < 9; i++) {
    int fila[10] = {0};
    for (j = 0; j < 9; j++) {
      int num = n->sudo[i][j];
      if (num != 0) {
        if (fila[num]) return 0;
        fila[num] = 1;
      }
    }
  }
  for (j = 0; j < 9; j++) {
    int columna[10] = {0};
    for (i = 0; i < 9; i++) {
      int num = n->sudo[i][j];
      if (num != 0) {
        if (columna[num]) return 0;
        columna[num] = 1;
      }
    }
  }
  for (int k = 0; k < 3; k++) {
    for (int p = 0; p < 3; p++) {
      int submatriz[10] = {0};
      for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
          int fila = k * 3 + i;
          int col = p * 3 + j;
          int num = n->sudo[fila][col];
          if (num != 0) {
            if (submatriz[num]) return 0;
            submatriz[num] = 1;
          }
      }
    }
  }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();
  if (is_valid(n) != 1) return list;
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if (n->sudo[i][j] == 0){
        for(int a = 1; a <= 9; a++){
          Node* new_node = copy(n);
          new_node->sudo[i][j]= a;
          if (is_valid(new_node)) pushBack(list,new_node);
          else{
            free(new_node);
          }
        }
        return list;
      }
    }
  }
  return list;
}


int is_final(Node* n){
  int j,i;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if (n->sudo[i][j] == 0) return 0;
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* S = createStack();
  push(S, initial);
  Node* topNode = first(S);
  while ( topNode != NULL) {
    (*cont)++;
    Node* n = top(S);
    pop(S);
    if (is_final(n)) {
      return n;
    }

    List* adj = get_adj_nodes(n);
    Node* aux = first(adj);

    while (aux) {
      push(S, aux);
      aux = next(adj);
      }
      free(n);
      topNode = first(S);
    }
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