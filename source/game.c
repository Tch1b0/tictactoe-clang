#include <stdlib.h>
#include <game.h>
#include <stdio.h>
#include <utility.h>
#define TRUE 1
#define FALSE 0

Game *game_create()
{
    Game *game = malloc(sizeof(Game));
    game->over = FALSE;

    game->field = malloc(sizeof(int *) * 3);
    for (int i = 0; i <= 2; i++)
        game->field[i] = calloc(3, sizeof(int));

    return game;
}

Game *game_copy(Game *game)
{
    Game *new_game = game_create();
    new_game->over = game->over;
    for (int y = 0; y <= 2; y++)
    {
        for (int x = 0; x <= 2; x++)
        {
            new_game->field[y][x] = game->field[y][x];
        }
    }

    return new_game;
}

void game_place_entity(Game *game, int entity, int x, int y)
{
    if (game->field[y][x] == FIELD_EMPTY)
        game->field[y][x] = entity;
}

void game_debug_print(Game *game)
{
    for (int i = 0; i <= 2; i++)
    {
        printf("[%d][%d][%d]\n", game->field[i][0], game->field[i][1], game->field[i][2]);
    }
}

void game_pretty_print(Game *game)
{
    printf(" x -----\n");
    printf("y  %c|%c|%c\n", int_to_sign(game->field[0][0]), int_to_sign(game->field[0][1]), int_to_sign(game->field[0][2]));
    printf("| -------\n");
    printf("|  %c|%c|%c\n", int_to_sign(game->field[1][0]), int_to_sign(game->field[1][1]), int_to_sign(game->field[1][2]));
    printf("  -------\n");
    printf("   %c|%c|%c\n", int_to_sign(game->field[2][0]), int_to_sign(game->field[2][1]), int_to_sign(game->field[2][2]));
}

int game_count_empty_fields(Game *game)
{
    int count = 0;
    for (int y = 0; y <= 2; y++)
    {
        for (int x = 0; x <= 2; x++)
        {
            if (game->field[y][x] == FIELD_EMPTY)
                count++;
        }
    }

    return count;
}

void game_free(Game *game)
{
    for (int i = 0; i <= 2; i++)
    {
        free(game->field[i]);
    }
    free(game->field);
    free(game);
}

void game_ai_move(Game *game)
{
    for (int y = 0; y <= 2; y++)
    {
        for (int x = 0; x <= 2; x++)
        {
            if (game->field[y][x] == FIELD_EMPTY)
            {
                game_place_entity(game, FIELD_ENEMY, x, y);
                return;
            }
        }
    }
}

// Returns which player won, if any won
// 0 = Draw; 1 = Player; 2 = Enemy
int game_check_over(Game *game)
{
    for (int i = 0; i <= 2; i++)
    {
        if (game->field[i][0] != FIELD_EMPTY &&
            game->field[i][0] == game->field[i][1] &&
            game->field[i][1] == game->field[i][2])
        {
            game->over = TRUE;
            return game->field[i][0];
        }
    }

    for (int i = 0; i <= 2; i++)
    {
        if (game->field[0][i] != FIELD_EMPTY &&
            game->field[0][i] == game->field[1][i] &&
            game->field[1][i] == game->field[2][i])
        {
            game->over = TRUE;
            return game->field[i][0];
        }
    }

    if (game->field[0][0] != FIELD_EMPTY &&
        game->field[0][0] == game->field[1][1] &&
        game->field[1][1] == game->field[2][2])
    {
        game->over = TRUE;
        return game->field[0][0];
    }
    else if (game->field[0][2] != FIELD_EMPTY &&
             game->field[0][2] == game->field[1][1] &&
             game->field[1][1] == game->field[2][0])
    {
        game->over = TRUE;
        return game->field[0][0];
    }
    return -1;
}

// Starts the game loop
// Returns which player won
// 0 = Draw; 1 = Player; 2 = Enemy
int game_loop(Game *game)
{
    int players_turn = TRUE;
    int winner;

    while (!game->over)
    {
        printf("Turn of %s\n", players_turn ? "player" : "enemy");
        game_pretty_print(game);

        if (players_turn)
        {
            int y = prompt("y: ") - 1;
            int x = prompt("x: ") - 1;
            if (!bounds_valid(y, 0, 2) ||
                !bounds_valid(x, 0, 2) ||
                game->field[y][x] != FIELD_EMPTY)
            {
                printf("Invalid move!\n\n");
                continue;
            }
            game_place_entity(game, FIELD_PLAYER, x, y);
        }
        else
            game_ai_move(game);

        printf("\n\n");
        winner = game_check_over(game);
        players_turn = !players_turn;
    }

    game_pretty_print(game);
    printf("%s won!\n", winner == FIELD_EMPTY ? "No one" : (winner == FIELD_PLAYER ? "Player" : "Enemy"));
}
