#ifndef FIELD_H
#define FIELD_H

#define FIELD_EMPTY 0
#define FIELD_PLAYER 1
#define FIELD_ENEMY 2

struct game
{
    int **field;
    int over;
};

typedef struct game Game;

Game *game_create();
void game_place_entity(Game *game, int entity, int x, int y);
void game_debug_print(Game *game);
void game_pretty_print(Game *game);
void game_free(Game *game);
int game_loop(Game *game);
void game_ai_move(Game *game);
Game *game_copy(Game *game);
int game_count_empty_fields(Game *game);

#endif