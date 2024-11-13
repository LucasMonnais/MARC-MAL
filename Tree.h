//
// Created by anton on 12/11/2024.
//




#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#include "loc.h"

typedef struct s_node
{
    int value;
    t_localisation loc;
    struct s_node **sons;
    int nbSons; // taille physique du tableau
    // more to come !
} t_node;

typedef struct s_tree
{
    t_node *root;
} t_tree, *p_tree;

t_node *createNode(int val, int nb_sons);

t_tree createTree(int val);

t_node *createBranch(int val);

void fill_Tree(t_node *node);








#endif //UNTITLED1_TREE_H