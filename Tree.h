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

/**
 * @brief To create a tree
 * @param val : value of the all the nodes of the tree
 * @param startnode : the first node of the tree
 * @param maxdepth : the maximum depth of the tree
 * @return the tree
 */
t_tree createTree(int val,t_node *startnode, int maxdepth);

/**
 * @brief recursive function to create all the branch of a tree
 * @param val : value of the tree
 * @param maxdepth : depth maximum of the tree
 * @return pointer to the node that contain his branches
 */
t_node *createBranch(int val, int maxdepth);

/**
 * @brief recursive function that fills the tree with all the path the robot can do with a given possibilities of movements
 * @param node
 * @param map : the map
 * @param y_max : maximum y (south to north length)
 * @param x_max : maximum x (west to east length)
 * @param list_mvt_already_done : list of movement done in a certain depth
 * @param depth : depth we are in
 * @param maxDepth : maximum depth accepted
 * @param ls_mouvement_tot : list of all possible moves
 */
void fillTree(t_node *node, t_map map, int y_max, int x_max, int *list_mvt_already_done,int depth,int maxDepth, t_move *ls_mouvement_tot);

/**
 * @brief print the tree for each depth (comparable as layers) of a tree (might be quite ugly but used only for debugging purpose)
 * @param node : the first node of our tree
 */
void displayTree(t_node *node);

/**
 * @brief checks if a movement is possible and not overdone thanks to a list of possible movements
 * @param list : list of movement done
 * @param nbElt : number of element in the list of movement
 * @param move : movement you want to do
 * @param ls_mouvement_tot : list of movements you can do
 * @return if the movement can be done
 */
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
