#include <stdio.h>
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
    t_node *startnode = createNode(10,7);
    startnode->loc = loc_init(4,6,NORTH);

    t_tree starttree = createTree(7,startnode,2);

    int list_mvt_already_done[7];

    int maxDepth = 5;
    t_move ls_mvt[] = {F_10,F_20,F_10,U_TURN,U_TURN,B_10,F_30,B_10,T_LEFT};
    fillTree(starttree.root, map,map.y_max,map.x_max,list_mvt_already_done,0,maxDepth,ls_mvt);

    displayTree(starttree.root);


    return 0;
}
