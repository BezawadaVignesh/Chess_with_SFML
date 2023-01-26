#ifndef CHESS_MOVES_H_
#define CHESS_MOVES_H_

#include "vector.h"
#include <ctype.h>

bool is_samecolor(char, char);

bool is_black(char ch);
    
bool in_range_not_same_color(int , int ,int , char* );
vector_i* king_moves(int , char* );
vector_i* pawn_moves(int , char* );
vector_i* rook_moves(int ,char* );
vector_i* bishop_moves(int ,char* );
vector_i* knight_moves(int , char* );

#endif