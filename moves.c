//
// Created by flasque on 19/10/2024.
//

#include "moves.h"
#include "map.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/* definition of local functions */

t_orientation rotate(t_orientation ori, t_move move)
{
    int rst=0;
    switch (move)
    {
        case T_LEFT:
            rst=3;
            break;
        case T_RIGHT:
            rst=1;
            break;
        case U_TURN:
            rst=2;
            break;
        default: // should not happen
            rst=0;
            break;
    }
    return (ori+rst)%4;
}

t_localisation translate(t_localisation loc, t_move move)
{
    /** rules for coordinates:
     *  - x grows to the right with step of +1
     *  - y grows to the bottom with step of +1
     *  - the origin (x=0, y=0) is at the top left corner
     */
    t_position res=loc.pos;
    switch (move) {
        case F_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 1;
                    break;
                case EAST:
                    res.x = loc.pos.x + 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 1;
                    break;
                case WEST:
                    res.x = loc.pos.x - 1;
                    break;
                default:
                    break;
            }
            break;
        case F_20:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 2;
                    break;
                case EAST:
                    res.x = loc.pos.x + 2;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 2;
                    break;
                case WEST:
                    res.x = loc.pos.x - 2;
                    break;
                default:
                    break;
            }
            break;
        case F_30:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y - 3;
                    break;
                case EAST:
                    res.x = loc.pos.x + 3;
                    break;
                case SOUTH:
                    res.y = loc.pos.y + 3;
                    break;
                case WEST:
                    res.x = loc.pos.x - 3;
                    break;
                default:
                    break;
            }
            break;
        case B_10:
            switch (loc.ori) {
                case NORTH:
                    res.y = loc.pos.y + 1;
                    break;
                case EAST:
                    res.x = loc.pos.x - 1;
                    break;
                case SOUTH:
                    res.y = loc.pos.y - 1;
                    break;
                case WEST:
                    res.x = loc.pos.x + 1;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    return loc_init(res.x, res.y, loc.ori, loc.nbREG);

}

/* definitions of exported functions */

char *getMoveAsString(t_move move)
{
    return _moves[move];
}

t_localisation move(t_localisation loc, t_move move)
{
    t_localisation new_loc=loc;
    if ((move >=T_LEFT) && (move <= U_TURN))
    {
        new_loc.ori = rotate(loc.ori, move);
    }
    else
    {
        new_loc = translate(loc, move);
    }

    return new_loc;
}

void updateLocalisation(t_localisation *p_loc, t_move m)
{
    *p_loc = move(*p_loc, m);
    return;
}
/*
t_move *getRandomMoves(int N)
{
    int nbmoves[]={22,15,7,7,21,21,7};
    int total_moves=100;
    srand(time(NULL));
    t_move *moves = (t_move *)malloc(N * sizeof(t_move));
    for (int i = 0; i < N; i++)
    {
        int r = rand() % total_moves;
        int type=0;
        while (r >= nbmoves[type])
        {
            r -= nbmoves[type];
            type++;
        }
        nbmoves[type]--;
        total_moves--;
        moves[i] = (t_move )type;
    }
    return moves;
}
*/


//juste pour info c'est une méthode appelée LCG (Linear Congruential Generator) et qui va fonctonne en récursivité.

#include <stdint.h>


// Générateur congruentiel linéaire (LCG)
static uint64_t seed; // Variable globale pour la graine

void lcg_init(uint64_t s) {
    seed = s;
}

uint32_t lcg_random() {
    // Paramètres recommandés pour un LCG
    seed = (6364136223846793005ULL * seed + 1) & 0xFFFFFFFFFFFFFFFFULL; // 64 bits
    return (uint32_t)(seed >> 32); // Retourner les bits supérieurs
}

// Fonction principale pour générer des mouvements
t_move *getRandomMoves(int N, int al) {
    int nbmoves[] = {22, 15, 7, 7, 21, 21, 7};
    int total_moves = 100;

    // Allocation mémoire pour les mouvements
    t_move *moves = (t_move *)malloc(N * sizeof(t_move));
    if (moves == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Initialiser la graine pour le LCG
    lcg_init((uint64_t)time(NULL)); // Utiliser le timestamp comme graine

    for (int i = 0; i < N; i++) {
        // Générer un nombre pseudo-aléatoire borné
        int r = (lcg_random()+al) % total_moves;

        // Déterminer le type de mouvement correspondant
        int type = 0;
        while (r >= nbmoves[type]) {
            r -= nbmoves[type];
            type++;
        }

        // Réduire les mouvements disponibles
        nbmoves[type]--;
        total_moves--;

        // Stocker le type dans le tableau des mouvements
        moves[i] = (t_move)type;
    }

    return moves;
}




