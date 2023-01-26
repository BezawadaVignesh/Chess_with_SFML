#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#include "vector.h"
#include "chess_moves.c"

enum{
    HOME,
    PLAYING
} state = HOME;

/* Create the main g_window */
sfRenderWindow* g_window;
int g_ScreenWidth=1000,g_ScreenHeight=800;
sfEvent g_event;


int c_boardSize, c_active;
int c_pieceW;

char *c_board,*c_boardCopy;
char c_currentColor;
char *i_board = "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";

vector_i* c_allPossibleMoves[64];
vector_i* v;/*Holds current active piece moves*/

sfMusic *c_caputreSound, *c_moveSound;
sfTexture* c_img[13];
sfSprite* c_sprite[13];
sfCircleShape* canMoveSquare;

sfVector2i c_offset;

vector_i* get_possible_moves(int, char, char*);

