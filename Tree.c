//
// Created by anton on 12/11/2024.
//

#include "Tree.h"
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
/*
void fill_Tree(t_node *node){
    if (node->nb_sons <= 0) {
        return;
    }
    node->nbSons = node->sons;
    node->value = (t_node **)malloc(node->nbSons* sizeof(t_node *));

}
*/