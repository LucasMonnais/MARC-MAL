#include <stdio.h>
#include <malloc.h>
#include "map.h"
#include "Tree.h"
#include "moves.h"

int main() {
    t_map map;

    // The following preprocessor directive checks if the code is being compiled on a Windows system.
    // If either _WIN32 or _WIN64 is defined, it means we are on a Windows platform.
    // On Windows, file paths use backslashes (\), hence we use the appropriate file path for Windows.
#if defined(_WIN32) || defined(_WIN64)
    map = createMapFromFile("..\\maps\\example1.map");
#else
    map = createMapFromFile("../maps/example1.map");
#endif

    printf("Map created with dimensions %d x %d\n", map.y_max, map.x_max);
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%d ", map.soils[i][j]);
        }
        printf("\n");
    }
    // printf the costs, aligned left 5 digits
    for (int i = 0; i < map.y_max; i++)
    {
        for (int j = 0; j < map.x_max; j++)
        {
            printf("%-5d ", map.costs[i][j]);
        }
        printf("\n");
    }
    displayMap(map);




    // notre partie de code
    t_node *startnode = createNode(10,9);
    startnode->loc = loc_init(4,6,NORTH);
    startnode->loc.nbREG =0;
    t_tree starttree = createTree(9,startnode,4);
    t_node *end_node = startnode;
    int *list_mvt_already_done= (int *) malloc(5 *sizeof (int *));
    int maxDepth = 5;
    int it_boucle = 0;

    while (end_node->value !=0) {


        t_move *ls_mvt = getRandomMoves(9);

        printf("The list of moves in boucle %d is -> ", it_boucle);
        for (int i = 0; i < 9; i++) {
            printf("%s :", getMoveAsString(ls_mvt[i]));
        }

        printf("\n");
        free(list_mvt_already_done);
        list_mvt_already_done= (int *) malloc(5 *sizeof (int *));
        t_tree tree = createTree(end_node->value,end_node,9-5+end_node->loc.nbREG);

        //t_move ls_mvt[] = {F_10,F_20,F_10,U_TURN,U_TURN,B_10,F_30,B_10,T_LEFT};

        fillTree(end_node, map, map.y_max, map.x_max, list_mvt_already_done, 0, maxDepth-end_node->loc.nbREG, ls_mvt);

        int *path = (int *) malloc((maxDepth - (end_node->loc.nbREG)) * sizeof(int));
        //displayTree(starttree.root);

        end_node = searchmin(end_node, path);

        printf("valeur minimal de la boucle %d = %d avec %d passage par REG \n", it_boucle, end_node->value, end_node->loc.nbREG);
        //printf("%d %d %d %d %d \n",path[0], path[1], path[2], path[3], path[4]);
        t_move *ls_move_ef = trad_direction(ls_mvt, end_node->loc.nbREG, path);
        printf("The list of moves in boucle %d done is -> ", it_boucle);

        for (int i = 0; i < 5 - startnode->loc.nbREG; i++) {
            printf("%s :", getMoveAsString(ls_move_ef[i]));
        }
        printf("\n");
        it_boucle++;


    return 0;
}
