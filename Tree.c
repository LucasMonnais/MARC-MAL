//
// Created by anton on 12/11/2024.
//

#include "Tree.h"
#include "loc.h"
#include <stdio.h>
#include <stdlib.h>


t_node *createNode(int val, int nb_sons)
{
    t_node *new_node;
    new_node = (t_node *)malloc(sizeof(t_node));
    new_node->value = val;
    new_node->nbSons = nb_sons;
    new_node->sons = (t_node **)malloc(nb_sons*sizeof(t_node *));
    for (int i=0; i <nb_sons; i++)
    {
        new_node->sons[i]=NULL;
    }
    return new_node;
}

t_tree createTree(int val){
    t_tree tree;
    tree.root = createNode(0,val);
    for(int i=0; i<val; i++){
        tree.root->sons[i] = createBranch(val-1);

    }

    return tree;

}

t_node *createBranch(int val){
    t_node *branch = createNode(0, val);
    if (val>1){
        for(int i=0; i<val; i++){
            branch->sons[i] = createBranch(val-1);
        }

    }

    return branch;
}


 void fillTree(t_node *node, int map[5][5], int x_max, int y_max) {
    if ( node == NULL) return;

    // Position de départ de Marc dans ce nœud
    t_position currentPos = node->loc.pos;

    // Mouvement 1: Avancer de 10 m
    t_position forwardPos = UP(currentPos);
    if (isValidLocalisation(forwardPos, x_max, y_max)) {
        node->sons[0]->value = map[forwardPos.y][forwardPos.x];
        node->sons[0]->loc.pos = forwardPos;
    }

    // Mouvement 2: Quart de tour à gauche
    t_orientation leftOri = (node->loc.ori + 3) % 4;
    node->sons[1]->value = node->value;  // Orientation change seulement
    node->sons[1]->loc.ori = leftOri;

    // Mouvement 3: Quart de tour à droite
    t_orientation rightOri = (node->loc.ori + 1) % 4;
    node->sons[2]->value = node->value;  // Orientation change seulement
    node->sons[2]->loc.ori = rightOri;

    // Mouvement 4: Avancer de 20 m (deux fois avancer)
    t_position forwardPos20 = UP(forwardPos);
    if (isValidLocalisation(forwardPos20, x_max, y_max)) {
        node->sons[3]->value = map[forwardPos20.y][forwardPos20.x];
        node->sons[3]->loc.pos = forwardPos20;
    }

    // Mouvement 5: Reculer de 10 m
    t_position backwardPos = DOWN(currentPos);
    if (isValidLocalisation(backwardPos, x_max, y_max)) {
        node->sons[4]->value = map[backwardPos.y][backwardPos.x];
        node->sons[4]->loc.pos = backwardPos;
    }

    // Appel récursif pour les fils
    for (int i = 0; i < node->nbSons; i++) {
        fillTree(node->sons[i], map, x_max, y_max);
    }
}