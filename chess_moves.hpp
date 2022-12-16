bool is_samecolor(char ch, char c){
        if(!isalpha(ch) or !isalpha(c)) return false;
        return (ch>90 and c>90) or (ch<91 and c<91);
    }
bool is_black(char ch){
        if(isalpha(ch) and ch>90) return true;
        return false;
    }
    
bool in_range_not_same_color(int x, int y,int pos, std::string board){
    if(0>x or x>7 or 0>y or y>7) return false;
    if(isalpha(board[y*8+x]) and is_samecolor(board[y*8+x], board[pos])) return false;
    return true;
}
std::vector<int> king_moves(int pos, std::string board){
    int x = pos % 8, y;
    y = (pos-x)/8;
    std::vector<int> tmp = {1,1,1,-1,1,0,0,1},r;
    for(int i=0;i<tmp.size();i+=2){
        if(in_range_not_same_color( x+tmp[i], y+tmp[i+1], pos, board))
            r.push_back((y+tmp[i+1])*8+x+tmp[i]);
        if(in_range_not_same_color( x-tmp[i], y-tmp[i+1], pos, board))
            r.push_back((y-tmp[i+1])*8+x-tmp[i]);
        
    }
    return r;
}
std::vector<int> pawn_moves(int pos, std::string board){
    std::vector<int> v;
    if(board[pos] > 90){
        if((pos+8<64) and (board[pos+8] == '-'))
         v.push_back(pos+8);
        
    }
    else if(pos-8<64 and board[pos-8] == '-') v.push_back(pos-8);
    return v;
}
std::vector<int> rook_moves(int pos,std::string board){
    //if(board[pos] != 'R' or board[pos] != 'r') return {};
    std::vector<int> moves;
    int x = pos % 8;
    //y = (pos-x)/8;
    for(int i=1;x+i<8;i++){
        if(board[pos+i] != '-'){
            if(!is_samecolor(board[pos+i],board[pos]))
                moves.push_back(pos+i);
            break;
        }
        moves.push_back(pos+i);
    }
    for(int i=1;x-i>-1;i++){
        if(board[pos-i] != '-'){
            if(!is_samecolor(board[pos-i],board[pos]))
                moves.push_back(pos-i);
            break;
        }
        moves.push_back(pos-i);
    }
    for(int i=8;pos+i<64;i+=8){
        if(board[pos+i] != '-'){
            if(!is_samecolor(board[pos+i],board[pos]))
                moves.push_back(pos+i);
            break;
        }
        moves.push_back(pos+i);
    }
    for(int i=8;pos-i>-1;i+=8){
        if(board[pos-i] != '-'){
            if(!is_samecolor(board[pos-i],board[pos]))
                moves.push_back(pos-i);
            break;
        }
        moves.push_back(pos-i);
    }
    return moves;
}
std::vector<int> bishop_moves(int pos,std::string board){
    std::vector<int> moves;
    int x = pos % 8, y;
    y = (pos-x)/8;
    for(int i=1;x+i<8 and y+i<8;i++){
        if(board[pos+9*i] != '-'){
            if(!is_samecolor(board[pos+9*i],board[pos]))
                moves.push_back(pos+9*i);
            break;
        }
        moves.push_back(pos+9*i);
    }
    for(int i=1;x-i>-1 and y-i>-1;i++){
        if(board[pos-9*i] != '-'){
            if(!is_samecolor(board[pos-9*i],board[pos]))
                moves.push_back(pos-9*i);
            break;
        }
        moves.push_back(pos-9*i);
    }
    for(int i=1;x-i>-1 and y+i<8;i++){
        if(board[pos+7*i] != '-'){
            if(!is_samecolor(board[pos+7*i],board[pos]))
                moves.push_back(pos+7*i);
            break;
        }
        moves.push_back(pos+7*i);
    }
    for(int i=1;x+i<8 and y-i>-1;i++){
        if(board[pos-7*i] != '-'){
            if(!is_samecolor(board[pos-7*i],board[pos]))
                moves.push_back(pos-7*i);
            break;
        }
        moves.push_back(pos-7*i);
    }
    return moves;
}
std::vector<int> knight_moves(int pos, std::string board){
    int x = pos % 8, y;
    y = (pos-x)/8;
    std::vector<int> tmp = {2, 1,1,2,-1,2,-2,1,},r;
    
    for(int i=0;i<tmp.size();i+=2){
        if(in_range_not_same_color( x+tmp[i], y+tmp[i+1], pos, board))
            r.push_back((y+tmp[i+1])*8+x+tmp[i]);
        if(in_range_not_same_color( x-tmp[i], y-tmp[i+1], pos, board))
            r.push_back((y-tmp[i+1])*8+x-tmp[i]);
        
    }
    return r;
}