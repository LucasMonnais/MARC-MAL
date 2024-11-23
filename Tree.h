//
// Created by anton on 12/11/2024.
//




#ifndef UNTITLED1_TREE_H
#define UNTITLED1_TREE_H
#include "loc.h"
#include "map.h"
#include "moves.h"


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

t_tree createTree(int val,t_node *startnode, int maxdepth);

t_node *createBranch(int val, int maxdepth);

void fillTree(t_node *node, t_map map, int y_max, int x_max, int *list_mvt_already_done,int depth,int maxDepth, t_move *ls_mouvement_tot);

void displayTree(t_node *node);

int IsMvtAlreadyDone(int *list, int nbElt, t_move move, t_move *ls_mouvement_tot);

/**
 * @brief function to translate the robot according to a move, a position and the type of ground it is on
 * @param loc : the localisation of the robot
 * @param mapGround : map with all type of ground
 * @param move : the move initially doing
 * @return the move really done according to the type of ground
 */
t_localisation moveTypeGround(t_localisation loc, t_map map, t_move move);







#endif //UNTITLED1_TREE_H
