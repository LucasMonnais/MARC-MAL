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
    new_node->loc.nbREG = 0;
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

t_tree createTree(int val,t_node *startnode,int nb_poss_minus_maxdepth){
    t_tree tree;
    tree.root = startnode;
    for(int i=0; i<val; i++){
        tree.root->sons[i] = createBranch(val-1,nb_poss_minus_maxdepth);

    }
    return tree;

}

t_node *createBranch(int val, int maxdepth){
    t_node *branch = createNode(10000, val);
    if (val>maxdepth){
        for(int i=0; i<val; i++){
            branch->sons[i] = createBranch(val-1, maxdepth);
        }

    }
    else {
        for(int i=0; i<val; i++){
            branch->sons[i] = NULL;
        }
    }

    return branch;
}


int IsMvtAlreadyDone(int *list, int nbElt, t_move move, t_move *ls_mouvement_tot) {
    for (int a = 0; a < 9; a++) {
        // Check si le mvt fait partie de ceux à faire
        if (ls_mouvement_tot[a] == move) {
            // Vérification si l'indice du mvt a déjà été utilisé
            int trouve = 0;
            for (int i = 0; i < nbElt; i++) {
                if (list[i] == a) {
                    trouve  = 1;
                    break;
                }
            }

            // Si l'indice n'a pas été utilisé, on le retourne
            if (!trouve) {
                return a;
            }
        }
    }

    // Pour le reste on sort
    return -1;
}


void fillTree(t_node *node,t_map map, int y_max, int x_max, int *list,int depth,int maxDepth, t_move *ls_mvt) {
    if (node == NULL) return;
    if (map.costs[node->loc.pos.y][node->loc.pos.x] >= 10000) return;

    if (maxDepth<=depth) return;

    int i = 0;
    int a = -1;

    a =IsMvtAlreadyDone(list, depth, F_10,ls_mvt);
    if ( a >-1) {
        // Mouvement 1: Avancer de 10 m
        t_localisation forwardPos = moveTypeGround(node->loc, map,  F_10);

        if (isValidLocalisation(forwardPos.pos, x_max, y_max)) {
            node->sons[i]->value = map.costs[forwardPos.pos.y][forwardPos.pos.x];

            node->sons[i]->loc = forwardPos;

            list[depth] = a;


            // Appel récursif pour les fils
            fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth, ls_mvt);

        }
        i++;
    }

    a =IsMvtAlreadyDone(list, depth, T_LEFT,ls_mvt);
    if (a>-1) {
        // Mouvement 2: Quart de tour à gauche
        t_localisation leftOri = moveTypeGround(node->loc, map,  T_LEFT);;

        node->sons[i]->value = node->value;  // Orientation change seulement

        node->sons[i]->loc = leftOri;


        // Ajout du mvt dans la liste
        list[depth] = a;

        // Appel récursif pour les fils
        fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth, ls_mvt);
        i++;
    }

    a =IsMvtAlreadyDone(list, depth, T_RIGHT,ls_mvt);
    if (a>-1) {
        // Mouvement 3: Quart de tour à droite
        t_localisation rightOri = moveTypeGround(node->loc, map,  T_RIGHT);;

        node->sons[i]->value = node->value;  // Orientation change seulement

        node->sons[i]->loc = rightOri;


        // Ajout du mvt dans la liste
        list[depth] = a;


        // Appel récursif pour les fils
        fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth,ls_mvt);
        i++;
    }

    a =IsMvtAlreadyDone(list, depth, U_TURN,ls_mvt);
    if (a>-1) {
        // Mouvement 4: Demi-tour
        t_localisation rightOri = moveTypeGround(node->loc, map,  U_TURN);


        node->sons[i]->value = node->value;  // Orientation change seulement
        node->sons[i]->loc = rightOri;
        //problème résolu ici mtn il est ligne 268 (pour le B_10)

        // Ajout du mvt dans la liste
        list[depth] = a;


        // Appel récursif pour les fils
        fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth, ls_mvt);
        i++;
    }

    a =IsMvtAlreadyDone(list, depth, F_20,ls_mvt);
    if (a>-1) {
        // Mouvement 5: Avancer de 20 m

        t_localisation forwardPos = translate(node->loc, F_10);
        if (isValidLocalisation(forwardPos.pos, x_max, y_max)  && map.costs[forwardPos.pos.y][forwardPos.pos.x] < 10000) {
            t_localisation forwardPos2 = moveTypeGround(node->loc, map, F_20);
            if (isValidLocalisation(forwardPos2.pos, x_max, y_max)) {

                node->sons[i]->value = map.costs[forwardPos2.pos.y][forwardPos2.pos.x];

                node->sons[i]->loc = forwardPos2;

                // Ajout du mvt dans la liste
                list[depth] = a;


                // Appel récursif pour les fils
                fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth, ls_mvt);

            }
        }
        i++;

    }

    a =IsMvtAlreadyDone(list, depth, F_30,ls_mvt);
    if (a>-1) {
        // Mouvement 6: Avancer de 30 m

        t_localisation forwardPos = translate(node->loc, F_10);
        if (isValidLocalisation(forwardPos.pos, x_max, y_max)  && map.costs[forwardPos.pos.y][forwardPos.pos.x] < 10000) {
            t_localisation forwardPos2 = translate(node->loc, F_20);
            if (isValidLocalisation(forwardPos2.pos, x_max, y_max) && map.costs[forwardPos2.pos.y][forwardPos2.pos.x] < 10000){
                t_localisation forwardPos3 = moveTypeGround(node->loc, map, F_30);
                if (isValidLocalisation(forwardPos3.pos, x_max, y_max)){

                    node->sons[i]->value = map.costs[forwardPos3.pos.y][forwardPos3.pos.x];

                    node->sons[i]->loc = forwardPos3;

                    // Ajout du mvt dans la liste
                    list[depth] = a;


                    // Appel récursif pour les fils
                    fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth, ls_mvt);

                }
            }
        }
        i++;

     }



    a =IsMvtAlreadyDone(list, depth, B_10,ls_mvt);
    if (a>-1) {
          // Mouvement 7: Reculer de 10 m
          t_localisation backwardPos = moveTypeGround(node->loc, map, B_10);


          if (isValidLocalisation(backwardPos.pos, x_max, y_max)) {
              //printf("%d", node->sons[i]->value);
              node->sons[i]->value = map.costs[backwardPos.pos.y][backwardPos.pos.x];
              node->sons[i]->loc = backwardPos;

              // Ajout du mvt dans la liste
              list[depth] = a;

              // Appel récursif pour les fils
              fillTree(node->sons[i], map, y_max, x_max, list, depth + 1, maxDepth, ls_mvt);

          }
          i++;
      }

}

void displayTree(t_node *node){
    printf(" couche 0 : %d \n \n", node->value);
    printf(" couche 1 : ");

    for (int a=0; a<9; a++){
        printf("%d ",node->sons[a]->value);
    }
    printf(" \n \n couche 2 : ");
    for (int a=0; a<9; a++){
        printf("\n");
        for (int b=0; b<8; b++){
            printf("%d ",node->sons[a]->sons[b]->value);
        }
    }
    printf(" \n \n couche 3 : ");
    for (int a=0; a<9; a++){
        printf("\n");
        for (int b=0; b<8; b++){
            printf("\n");
            for (int c=0; c<7; c++) {
                printf("%d ", node->sons[a]->sons[b]->sons[c]->value);
            }
        }
    }
    printf(" \n \n couche 4 : ");
    for (int a=0; a<9; a++){
        for (int b=0; b<8; b++){
            for (int c=0; c<7; c++) {
                for (int d=0; d<5; d++) {
                    printf("%d ", node->sons[a]->sons[b]->sons[c]->sons[d]->value);
                }
            }
        }
    }
    printf(" \n \n couche 5 : ");
    for (int a=0; a<9; a++){
        for (int b=0; b<8; b++){
            for (int c=0; c<7; c++) {
                for (int d=0; d<6; d++) {
                    for (int e=0; e<5; e++) {
                        printf("%d ", node->sons[a]->sons[b]->sons[c]->sons[d]->sons[e]->value);
                    }
                }
            }
        }
    }

}


t_localisation moveTypeGround(t_localisation loc, t_map map, t_move move){
    switch(map.soils[loc.pos.y][loc.pos.x]) {
        case BASE_STATION :
            return loc;
        case PLAIN :
            if (move == F_10 || move == F_20 || move == F_30 || move == B_10 ){
                return translate(loc, move);
            }
            else{
                loc.ori = rotate(loc.ori, move);
                return loc;

            }
        case ERG :
            switch (move) {
                case F_10:
                    return loc;
                case F_20:
                    return translate(loc, F_10);
                case F_30:
                    return translate(loc, F_20);
                case B_10:
                    return loc;
                case T_LEFT:
                    return loc;
                case T_RIGHT:
                    return loc;
                case U_TURN:
                    loc.ori = rotate(loc.ori, T_RIGHT);
                    return loc;
                default: // should not happen
                    break;
            }
        case REG :

            loc.nbREG ++;
            if (move == F_10 || move == F_20 || move == F_30 || move == B_10 ){
                return translate(loc, move);
            }
            else {
                loc.ori = rotate(loc.ori, move);
                return loc;
            }


        case CREVASSE :
            if (move == F_10 || move == F_20 || move == F_30 || move == B_10 ){
                return translate(loc, move);
            }
            else{
                loc.ori = rotate(loc.ori, move);
                return loc;
            }
    }
}



t_node *searchmin(t_node *node, int *path){
    int maxdepth = node->loc.nbREG ;
    t_node *min = createNode(100000, 2);
    min->loc.nbREG = 10000;
    if (maxdepth == 5 )
    {
        return node;
    }


    if (maxdepth == 4 ) {
        for (int a = 0; a < 9; a++) {
            if (min->value > node->sons[a]->value || (min->value >= node->sons[a]->value && min->loc.nbREG > node->sons[a]->loc.nbREG)){
                min = node->sons[a];
                path[0] = a;
            }
        }
    }

    if (maxdepth == 3 ) {

        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 8; b++) {
                if (min->value > node->sons[a]->sons[b]->value || (min->value >= node->sons[a]->sons[b]->value && min->loc.nbREG > node->sons[a]->sons[b]->loc.nbREG)){
                    min = node->sons[a]->sons[b];
                    path[0] = a;
                    path[1] = b;
                }
            }
        }
    }
    if (maxdepth == 2 ) {

        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 8; b++) {
                printf("\n");
                for (int c = 0; c < 7; c++) {
                    if (min->value > node->sons[a]->sons[b]->sons[c]->value || (min->value >= node->sons[a]->sons[b]->sons[c]->value && min->loc.nbREG > node->sons[a]->sons[b]->sons[c]->loc.nbREG)){
                        min = node->sons[a]->sons[b]->sons[c];
                        path[0] = a;
                        path[1] = b;
                        path[2]= c;
                    }
                }
            }
        }
    }
    if (maxdepth == 1 ) {

        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 8; b++) {
                for (int c = 0; c < 7; c++) {
                    for (int d = 0; d < 5; d++) {
                        if (min->value > node->sons[a]->sons[b]->sons[c]->sons[d]->value || (min->value >= node->sons[a]->sons[b]->sons[c]->sons[d]->value && min->loc.nbREG > node->sons[a]->sons[b]->sons[c]->sons[d]->loc.nbREG)){
                            min = node->sons[a]->sons[b]->sons[c]->sons[d];
                            path[0] = a;
                            path[1] = b;
                            path[2]= c;
                            path[3] = d;
                        }
                    }
                }
            }
        }
    }
    if (maxdepth == 0 ) {

        for (int a = 0; a < 9; a++) {
            for (int b = 0; b < 8; b++) {
                for (int c = 0; c < 7; c++) {
                    for (int d = 0; d < 6; d++) {
                        for (int e = 0; e < 5; e++) {
                            if (min->value >= node->sons[a]->sons[b]->sons[c]->sons[d]->sons[e]->value || (min->value >= node->sons[a]->sons[b]->sons[c]->sons[d]->sons[e]->value && min->loc.nbREG > node->sons[a]->sons[b]->sons[c]->sons[d]->sons[e]->loc.nbREG)){
                                min = node->sons[a]->sons[b]->sons[c]->sons[d]->sons[e];
                                path[0] = a;
                                path[1] = b;
                                path[2]= c;
                                path[3] = d;
                                path[4] = e;
                            }
                        }
                    }
                }
            }
        }
    }

    return min;

}

t_move *trad_direction(t_move *ls_move, int nb_reg,int *path) {
    mvt_in_tree *tab_mvt = (mvt_in_tree *)malloc( 7 * sizeof(mvt_in_tree));
    for (int i = 0; i < 7; i++) {
        tab_mvt[i].nb_mvt = 0;
    }
    tab_mvt[0].mvt = F_10;
    tab_mvt[1].mvt = T_LEFT;
    tab_mvt[2].mvt = T_RIGHT;
    tab_mvt[3].mvt = U_TURN;
    tab_mvt[4].mvt = F_20;
    tab_mvt[5].mvt = F_30;
    tab_mvt[6].mvt = B_10;
    for (int i = 0; i< 9; i++){
        for (int j = 0; j< 7 ; j++){
            if (tab_mvt[j].mvt == ls_move[i]){
                tab_mvt[j].nb_mvt ++;
            }
        }
    }
    t_move * ls_mvt_ef = (t_move *) malloc((5-nb_reg) * sizeof (t_move));
    int trouve = 0;
    int j = 0;
    for (int i = 0; i < 5-nb_reg; i++){
        trouve = 0 ;
        j = 0;
        while (trouve == 0){
            for (int k = 0; k < 7; k++){
                if (tab_mvt[k].nb_mvt!=0){
                    if (j== path[i]){
                        trouve = 1;
                        tab_mvt[k].nb_mvt --;
                        ls_mvt_ef[i] = tab_mvt[k].mvt;

                    }
                    j++;
                }
            }

        }

    }
    return ls_mvt_ef;
}