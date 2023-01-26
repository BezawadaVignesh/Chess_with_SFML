#include "chess_moves.h"

bool is_samecolor(char ch, char c){
        if(!isalpha(ch) or !isalpha(c)) return false;
        return (ch>90 and c>90) or (ch<91 and c<91);
    }
bool is_black(char ch){
        if(isalpha(ch) and ch>90) return true;
        return false;
    }
    
bool in_range_not_same_color(int x, int y,int pos, char* board){
    if(0>x or x>7 or 0>y or y>7) return false;
    if(isalpha(board[y*8+x]) and is_samecolor(board[y*8+x], board[pos])) return false;
    return true;
}
vector_i* king_moves(int pos, char* board){
    int x = pos % 8, y;
    y = (pos-x)/8;
    int tmp[] = {1,1,1,-1,1,0,0,1};
    VECTOR_INIT_EXPORT(r);
    for(int i=0;i<8;i+=2){
        if(in_range_not_same_color( x+tmp[i], y+tmp[i+1], pos, board))
            r->append(r,(y+tmp[i+1])*8+x+tmp[i]);
        if(in_range_not_same_color( x-tmp[i], y-tmp[i+1], pos, board))
            r->append(r,(y-tmp[i+1])*8+x-tmp[i]);
        
    }
    return r;
}
vector_i* pawn_moves(int pos, char* board){
    VECTOR_INIT_EXPORT(v);
    if(board[pos] > 90){
        if((pos+8<64)){
            if(board[pos+8] == '-'){
            v->append(v,pos+8);
            if(pos < 16 and pos > 7 and board[pos+16] == '-') v->append(v, pos+16);}/*2 first steps*/
            if(pos%8 != 0 and board[pos+7] != '-' and !is_samecolor(board[pos+7], board[pos])) v->append(v, pos+7);/*kill left*/
            if(pos%8 != 7 and board[pos+9] != '-' and !is_samecolor(board[pos+9], board[pos])) v->append(v, pos+9);/*kill right*/
        } 
    }
    else {
        if(pos-8>0){
            if(board[pos-8] == '-'){
                v->append(v,pos-8);
            if(pos < 56 and pos > 47 and board[pos-16] == '-') v->append(v, pos-16);
            }
            if(pos%8 != 0 and board[pos-9] != '-' and !is_samecolor(board[pos-9], board[pos])) v->append(v, pos-9);
            if(pos%8 != 7 and board[pos-7] != '-' and !is_samecolor(board[pos-7], board[pos])) v->append(v, pos-7);
        }
    }
    return v;
}
vector_i* rook_moves(int pos,char* board){
    //if(board[pos] != 'R' or board[pos] != 'r') return {};
    VECTOR_INIT_EXPORT(moves);
    int x = pos % 8;
    //y = (pos-x)/8;
    for(int i=1;x+i<8;i++){
        if(board[pos+i] != '-'){
            if(!is_samecolor(board[pos+i],board[pos]))
                moves->append(moves,pos+i);
            break;
        }
        moves->append(moves,pos+i);
    }
    for(int i=1;x-i>-1;i++){
        if(board[pos-i] != '-'){
            if(!is_samecolor(board[pos-i],board[pos]))
                moves->append(moves,pos-i);
            break;
        }
        moves->append(moves,pos-i);
    }
    for(int i=8;pos+i<64;i+=8){
        if(board[pos+i] != '-'){
            if(!is_samecolor(board[pos+i],board[pos]))
                moves->append(moves,pos+i);
            break;
        }
        moves->append(moves,pos+i);
    }
    for(int i=8;pos-i>-1;i+=8){
        if(board[pos-i] != '-'){
            if(!is_samecolor(board[pos-i],board[pos]))
                moves->append(moves,pos-i);
            break;
        }
        moves->append(moves,pos-i);
    }
    return moves;
}
vector_i* bishop_moves(int pos,char* board){
    VECTOR_INIT_EXPORT(moves);
    int x = pos % 8, y;
    y = (pos-x)/8;
    for(int i=1;x+i<8 and y+i<8;i++){
        if(board[pos+9*i] != '-'){
            if(!is_samecolor(board[pos+9*i],board[pos]))
                moves->append(moves,pos+9*i);
            break;
        }
        moves->append(moves,pos+9*i);
    }
    for(int i=1;x-i>-1 and y-i>-1;i++){
        if(board[pos-9*i] != '-'){
            if(!is_samecolor(board[pos-9*i],board[pos]))
                moves->append(moves,pos-9*i);
            break;
        }
        moves->append(moves,pos-9*i);
    }
    for(int i=1;x-i>-1 and y+i<8;i++){
        if(board[pos+7*i] != '-'){
            if(!is_samecolor(board[pos+7*i],board[pos]))
                moves->append(moves,pos+7*i);
            break;
        }
        moves->append(moves,pos+7*i);
    }
    for(int i=1;x+i<8 and y-i>-1;i++){
        if(board[pos-7*i] != '-'){
            if(!is_samecolor(board[pos-7*i],board[pos]))
                moves->append(moves,pos-7*i);
            break;
        }
        moves->append(moves,pos-7*i);
    }
    return moves;
}
vector_i* knight_moves(int pos, char* board){
    int x = pos % 8, y;
    y = (pos-x)/8;
    int tmp[] = {2, 1,1,2,-1,2,-2,1,};
    VECTOR_INIT_EXPORT(r);
    
    for(int i=0;i<8;i+=2){
        if(in_range_not_same_color( x+tmp[i], y+tmp[i+1], pos, board))
            r->append(r,(y+tmp[i+1])*8+x+tmp[i]);
        if(in_range_not_same_color( x-tmp[i], y-tmp[i+1], pos, board))
            r->append(r,(y-tmp[i+1])*8+x-tmp[i]);
        
    }
    return r;
}

// void main(){
//     char* s = "---------------------------n------------------------------------";
//     VECTOR_INIT(r);
//     r = knight_moves(27,s);
//     r.display(&r);
//     r.free(&r);
//     r = king_moves(27, s);
//     r.display(&r);
//     r.free(&r);
//     r = bishop_moves(27, s);
//     r.display(&r);
//     r.free(&r);
//     r = rook_moves(27,s);
//     r.display(&r);
//     r.free(&r);
    
// }