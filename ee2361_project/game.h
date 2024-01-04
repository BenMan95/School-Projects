#ifndef GAME_H
#define	GAME_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct {
        // indices of head and tail in path array
        unsigned char head;
        unsigned char tail;

        char food; // position of food on board
        long long bits; // tracks the area covered by the snake body
        char path[64]; // tracks order of snake segments
        char pmov; // gives the previous move
    } game_t;
    
    void game_init(game_t *game); // start a new game
    long long game_getSnake(game_t *game); // get bit representation of snake
    long long game_getFood(game_t *game); // get bit representation of food pos
    char game_getScore(game_t *game); // get the amount of food eaten
    
    /* performs the given move
     * directions are as follows:
     * 0 - neutral
     * 8 - left
     * -8 right
     * -1 - up
     * 1 - down
     * 
     * returns 2 and does nothing if max length is reached
     * returns 1 and does nothing if the step would result in a collision
     * returns 0 and moves otherwise
     */
    char game_step(game_t *game,char mov);
    
#ifdef	__cplusplus
}
#endif

#endif
