#include <stdlib.h>
#include <stdio.h>
#include <game.h>
#include <utility.h>

int main()
{
    Game *game = game_create();
    game_loop(game);
    game_free(game);
    return 0;
}