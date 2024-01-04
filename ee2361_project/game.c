#include <stdlib.h>
#include "xc.h"
#include "game.h"

#define WALL1 0x0101010101010101
#define WALL2 0x8080808080808080
#define WALL3 0x00000000000000FF
#define WALL4 0xFF00000000000000

void game_init(game_t *game) {
    // initialize head and tail indices
    game->head = 0;
    game->tail = 0;

    // initialize snake position
    game->bits = 1;
    game->path[0] = 0;
    game->pmov = 1;

    // initialize food position
    do game->food = rand()&63;
    while ((1LL << game->food) & game->bits);
}

char game_step(game_t *game,char mov) {
    if (!~game->bits) return 2;

    // get previous head position
    char prev = game->path[game->head];

    // prevent backwards movement
    if (-mov == game->pmov) mov = game->pmov;

    // correct invalid moves and check if move hits wall
    long long wall;
    check: switch (mov) {
    case -1: wall = WALL1; break;
    case  1: wall = WALL2; break;
    case -8: wall = WALL3; break;
    case  8: wall = WALL4; break;
    default: mov = game->pmov; goto check;
    }
    if ((1LL << prev) & wall) return 1;

    // get new head position
    char new = prev + mov;

    if (game->food == new) {
        // change snake position
        game->bits |= 1LL << new;
        game->head++;
        game->head &= 0x3f;
        game->path[game->head] = new;

        // check if board filled
        if (!~game->bits) return 2;

        // generate new food
        do game->food = rand() & 63;
        while ((1LL << game->food) & game->bits);
    } else {
        // get collision bits
        long long cbits = game->bits & ~(1LL << game->path[game->tail]);
        long long hbit = 1LL << new;

        // check for collision
        if (cbits & hbit) return 1;

        // change position if no collision
        game->bits = cbits | hbit;
        
        // increment head and tail
        game->head++;
        game->tail++;
        game->head &= 0x3f;
        game->tail &= 0x3f;
        
        game->path[game->head] = new;
    }

    game->pmov = mov;
    return 0;
}

long long game_getSnake(game_t *game) { return game->bits; }

long long game_getFood(game_t *game) { return 1LL << game->food; }

char game_getScore(game_t *game) {
    char diff = game->head - game->tail;
    return diff < 0 ? diff + 64 : diff;
}