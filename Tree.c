//
// Created by anton on 12/11/2024.
//

#include "Tree.h"
#include "loc.h"
#include "moves.h"
#include <stdio.h>
#include <stdlib.h>



t_node *createNode(int val, int nb_sons)
{
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->nbSons = nb_sons;
    if (nb_sons>0) {
        new_node->sons = (t_node **) malloc(nb_sons * sizeof(t_node *));
        for (int i = 0; i < nb_sons; i++) {
            new_node->sons[i] = NULL;
        }
    }
    else {
        new_node->sons =NULL;
    }
    return new_node;
}

t_tree createTree(int val,t_node *startnode){
    t_tree tree;
    tree.root = startnode;
    for(int i=0; i<val; i++){
        tree.root->sons[i] = createBranch(val-1);

    }
    return tree;

}

t_node *createBranch(int val){
    t_node *branch = createNode(10000, val);
    if (val>0){
        for(int i=0; i<val; i++){
            branch->sons[i] = createBranch(val-1);
        }

    }

    return branch;
}

int IsMvtAlreadyDone(int *list, int nbElt, int value){
    if (list == NULL) return 1;
    else {
        for (int i = 0; i < nbElt; i++){
            if (list[i] == value){
                return 0;
            }

        }
        return 1;
    }
}



 void fillTree(t_node *node,int **map, int y_max, int x_max, int *list,int depth,int maxDepth) {
     if (node == NULL) return;
     if (map[node->loc.pos.y][node->loc.pos.x] >= 10000) return;

     if (maxDepth<=depth) return;

     int i = 0;
     printf("coucou");


      if (IsMvtAlreadyDone(list, depth, 1)) {
      // Mouvement 1: Avancer de 10 m
          t_localisation forwardPos = translate(node->loc, F_10);

          if (isValidLocalisation(forwardPos.pos, y_max, x_max)) {
             node->sons[i]->value = map[forwardPos.pos.y][forwardPos.pos.x];
             node->sons[i]->loc = forwardPos;

             // Ajout du mvt dans la liste
             list[depth] = 1;
              printf("si sa montre 2 fois ce mesage je tue lucas");

             // Appel récursif pour les fils
             fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth);
             i++;
         }
      }

     printf("cENCU2");
      if (IsMvtAlreadyDone(list, depth, 2)) {
          // Mouvement 2: Quart de tour à gauche
          t_orientation leftOri = rotate(node->loc.ori, T_LEFT);
          printf("f");
          node->sons[i]->value = node->value;  // Orientation change seulement
          printf("d");
          node->sons[i]->loc.ori = leftOri;
          printf("p");

          // Ajout du mvt dans la liste
          list[depth] = 2;
          printf("n");
          // Appel récursif pour les fils
          fillTree(node->sons[1], map, y_max, x_max, list, depth + 1, maxDepth);
          i++;
      }
     printf("fdp");
      if (IsMvtAlreadyDone(list, depth, 3)) {
          // Mouvement 3: Quart de tour à droite
          t_orientation rightOri = rotate(node->loc.ori, T_RIGHT);
          node->sons[i]->value = node->value;  // Orientation change seulement
          node->sons[i]->loc.ori = rightOri;

          // Ajout du mvt dans la liste
          list[depth] = 3;

          // Appel récursif pour les fils
          fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth);
          i++;
      }

      if (IsMvtAlreadyDone(list, depth, 4)) {
          // Mouvement 4: Avancer de 20 m
          t_localisation forwardPos = translate(node->loc, F_10);
          if (isValidLocalisation(forwardPos.pos, y_max, x_max)  && map[node->loc.pos.y][node->loc.pos.x] <= 10000) {
              t_localisation forwardPos2 = translate(node->loc, F_20);
              if (isValidLocalisation(forwardPos2.pos, y_max, x_max)) {
                  node->sons[i]->value = map[forwardPos2.pos.y][forwardPos2.pos.x];
                  node->sons[i]->loc = forwardPos2;

                  // Ajout du mvt dans la liste
                  list[depth] = 4;


                  // Appel récursif pour les fils
                  fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth);
                  i++;
              }
          }

     }



      if (IsMvtAlreadyDone(list, depth, 5)) {
          // Mouvement 5: Reculer de 10 m
          t_localisation backwardPos = translate(node->loc, B_10);


          if (isValidLocalisation(backwardPos.pos, x_max, y_max)) {
              node->sons[i]->value = map[backwardPos.pos.y][backwardPos.pos.x];
              node->sons[i]->loc = backwardPos;

              // Ajout du mvt dans la liste
              list[depth] = 5;

              // Appel récursif pour les fils
              fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth);
              i++;
          }
      }

}

void displayTree(t_node *node){
    printf(" couche 0 : %d \n \n", node->value);
    printf(" couche 1 : ");
    for (int a=0; a<5; a++){
        printf("%d ",node->sons[a]->value);
    }
    printf(" \n \n couche 2 : ");
    for (int a=0; a<5; a++){
        for (int b=0; b<4; b++){
            printf("%d ",node->sons[a]->sons[b]->value);
        }
    }
    printf(" \n \n couche 3 : ");
    for (int a=0; a<5; a++){
        for (int b=0; b<4; b++){
            for (int c=0; c<3; c++) {
                printf("%d ", node->sons[a]->sons[b]->sons[c]->value);
            }
        }
    }
    printf(" \n \n couche 4 : ");
    for (int a=0; a<5; a++){
        for (int b=0; b<4; b++){
            for (int c=0; c<3; c++) {
                for (int d=0; d<2; d++) {
                    printf("%d ", node->sons[a]->sons[b]->sons[c]->sons[d]->value);
                }
            }
        }
    }
    printf(" \n \n couche 5 : ");
    for (int a=0; a<5; a++){
        for (int b=0; b<4; b++){
            for (int c=0; c<3; c++) {
                for (int d=0; d<2; d++) {
                    printf("%d ", node->sons[a]->sons[b]->sons[c]->sons[d]->sons[0]->value);

                }
            }
        }
    }

}

