#include <stdio.h>
#include <malloc.h>
#include "map.h"
#include "Tree.h"
#include "moves.h"
#include <sys/time.h>

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


    struct timeval start1, end1, start2, end2, startGlob, endGlob;
    long seconds, microseconds;


    t_node *startnode = createNode(10,9);
    startnode->loc = loc_init(4,6,NORTH,0);
    startnode->loc.nbREG =0;
    t_tree starttree = createTree(9,startnode,4);
    t_node *end_node = startnode;
    int *list_mvt_already_done= (int *) malloc(5 *sizeof (int *));
    int maxDepth = 5;
    int it_boucle = 0;
    int basefound = 0;
    gettimeofday(&startGlob, NULL);
    while (end_node->value !=0 && it_boucle<10 && end_node->loc.nbREG < 5) {
//

        t_move *ls_mvt = getRandomMoves(9,(end_node->value+it_boucle)*14);

        printf("The list of moves in boucle %d is -> ", it_boucle);
        for (int i = 0; i < 9; i++) {
            printf("%s :", getMoveAsString(ls_mvt[i]));
        }

        printf("\n");

        list_mvt_already_done= (int *) malloc(5 *sizeof (int *));

        startnode = createNode(end_node->value,9);
        startnode->loc = end_node->loc;

        gettimeofday(&start1, NULL); // Début du chronométrage
        t_tree tree = createTree(9,startnode,4-startnode->loc.nbREG);
        // Calcul du temps écoulé en secondes et microsecondes
        gettimeofday(&end1, NULL);
        seconds = end1.tv_sec - start1.tv_sec;
        microseconds = end1.tv_usec - start1.tv_usec;
        double elapsed1 = seconds + microseconds * 1e-6;

        //t_move ls_mvt[] = {F_10,F_20,F_10,U_TURN,U_TURN,B_10,F_30,B_10,T_LEFT};

        //displayTree(startnode);
        fillTree(tree.root, map, map.y_max, map.x_max, list_mvt_already_done, 0, maxDepth-end_node->loc.nbREG, ls_mvt);

        int *path = (int *) malloc((maxDepth - (end_node->loc.nbREG)) * sizeof(int));

        gettimeofday(&start2, NULL);
        end_node = searchmin(startnode, path);
        gettimeofday(&end2, NULL);
        // Calcul du temps écoulé en secondes et microsecondes
        seconds = end2.tv_sec - start2.tv_sec;
        microseconds = end2.tv_usec - start2.tv_usec;
        double elapsed2 = seconds + microseconds * 1e-6;


        printf("valeur minimal de la boucle %d = %d avec %d passage par REG \n", it_boucle, end_node->value, end_node->loc.nbREG-startnode->loc.nbREG);

        t_move *ls_move_ef = trad_direction(ls_mvt, startnode->loc.nbREG, path);
        printf("The list of moves in boucle %d done is -> ", it_boucle);

        for (int i = 0; i < 5 - startnode->loc.nbREG; i++) {
            printf("%s :", getMoveAsString(ls_move_ef[i]));
        }
        printf("\n");
        if(end_node->value ==0){
            printf("marc a reussi a arriver a la base en %d serie de deplacement, yipie \n", it_boucle+1);
            basefound =1;
        }
        it_boucle++;
        printf("Time for creation Tree : %lf\n", elapsed1);
        printf("Time to find minValue and his path : %lf\n", elapsed1);
    }
    if(basefound ==0){
        printf("marc n'a pas reussi a revenir a la base, il devra donc rester seul sur sa planete pendant des annees a mourir a petit feu et a voir tout ces composant se degrader de plus en plus jusqu'a qu il devienne poussiere, quel dommage :( \n");
    }
    gettimeofday(&endGlob, NULL);
    if(end_node->value == 0){
        // Calcul du temps écoulé en secondes et microsecondes
        seconds = endGlob.tv_sec - startGlob.tv_sec;
        microseconds = endGlob.tv_usec - startGlob.tv_usec;
        double elapsed3 = seconds + microseconds * 1e-6;
        printf("Time to go to base (bed) : %lf", elapsed3);
    }
    return 0;

}
