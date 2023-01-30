#include "main.h"

struct {
    int x,y;
    bool dragging;
} selected;



void set_board_size(int new_size){
    c_boardSize = new_size;
    c_pieceW = c_boardSize/8;
    c_offset.x = (int)(g_ScreenWidth-c_boardSize)/2;
    c_offset.y = 0;

    sfVector2f tmpvf;
    tmpvf.x = c_offset.x;
    tmpvf.y = c_offset.y;
    sfSprite_setPosition(c_sprite[0],tmpvf);
    tmpvf.x = c_boardSize/sfSprite_getLocalBounds(c_sprite[0]).width;
    tmpvf.y = c_boardSize/sfSprite_getLocalBounds(c_sprite[0]).height;
    sfSprite_setScale(c_sprite[0],tmpvf);
    int i=1;
    for(i=1;i<13;i++){
        tmpvf.x = c_boardSize/(8*sfSprite_getLocalBounds(c_sprite[i]).width);
        tmpvf.y = c_boardSize/(8*sfSprite_getLocalBounds(c_sprite[i]).height);
        sfSprite_setScale(c_sprite[i], tmpvf);
    }
}

void reset_board(){
    free(c_board);
    free(c_boardCopy);
    c_board = strdup(i_board);
    c_currentColor = 'K';
    c_boardCopy = strdup(c_board);
    c_active = -1;
}

void init(){
    sfVideoMode mode = {g_ScreenWidth, g_ScreenHeight, 32};
    
    g_window = sfRenderWindow_create(mode, "Chess",sfResize | sfClose, NULL);
    if (!g_window){
        printf("Cant create window ");
        exit(-1);
    }
    sfRenderWindow_setFramerateLimit(g_window,60);

    char* imgLoc = "";
    
    c_img[0] = sfTexture_createFromFile("..\\img\\board.png",NULL);
    c_img[1] = sfTexture_createFromFile("..\\img\\wk.png",NULL);
    c_img[2] = sfTexture_createFromFile("..\\img\\wq.png",NULL);
    c_img[3] = sfTexture_createFromFile("..\\img\\wr.png",NULL);
    c_img[4] = sfTexture_createFromFile("..\\img\\wbi.png",NULL);
    c_img[5] = sfTexture_createFromFile("..\\img\\wkn.png",NULL);
    c_img[6] = sfTexture_createFromFile("..\\img\\wp.png",NULL);
    c_img[7] = sfTexture_createFromFile("..\\img\\bk.png",NULL);
    c_img[8] = sfTexture_createFromFile("..\\img\\bq.png",NULL);
    c_img[9] = sfTexture_createFromFile("..\\img\\br.png",NULL);
    c_img[10] = sfTexture_createFromFile("..\\img\\bbi.png",NULL);
    c_img[11] = sfTexture_createFromFile("..\\img\\bkn.png",NULL);
    c_img[12] = sfTexture_createFromFile("..\\img\\bp.png",NULL);

    if(!c_img[0]){
        printf("Cant load img[0]");
        exit(EXIT_FAILURE);
    }

    c_sprite[0] = sfSprite_create();
    sfSprite_setTexture(c_sprite[0], c_img[0],sfTrue);

    c_caputreSound = sfMusic_createFromFile("..\\img\\capture.wav");
    c_moveSound = sfMusic_createFromFile("..\\img\\move-self.wav");

    if(!c_caputreSound or !c_moveSound){
        printf("cant load sound files");
    }

    int i=0;
    for(i=1;i<13;i++){
        if(!c_img[0]){
            printf("Cant load img[%d]", i);
            exit(EXIT_FAILURE);
        }
        c_sprite[i] = sfSprite_create();
        sfSprite_setTexture(c_sprite[i], c_img[i],sfTrue);
        
    }
    
    set_board_size(g_ScreenHeight);
    reset_board();

    for(i=0;i<64;i++){
        c_allPossibleMoves[i] = get_possible_moves(i, c_currentColor, c_board);
    }
    canMoveSquare = sfCircleShape_create();
    sfCircleShape_setFillColor(canMoveSquare, sfColor_fromRGBA(255,0,0,200));
    sfCircleShape_setRadius(canMoveSquare, c_pieceW/4);
    if(!canMoveSquare){
        printf("Memory full");
        exit(-1);
    }

    selected.dragging = false;
}

sfSprite* get_sprite(char piece){
        switch(piece){
                case 'K':
                    return c_sprite[1];
                case 'Q':
                    return c_sprite[2];
                case 'R':
                    return c_sprite[3];
                case 'B':
                    return c_sprite[4];
                case 'N':
                    return c_sprite[5];
                case 'P':
                    return c_sprite[6];
                case 'k':
                    return c_sprite[7];
                case 'q':
                    return c_sprite[8];
                case 'r':
                    return c_sprite[9];
                case 'b':
                    return c_sprite[10];
                case 'n':
                    return c_sprite[11];
                case 'p':
                    return c_sprite[12];  
                case '-':
                    break;
                default:
                    printf("Invalid string got %c",piece);
            }
}

void draw_pieces(){  
    sfRenderWindow_drawSprite(g_window,c_sprite[0]/*board*/, NULL);
    sfSprite* tmpSprite;
    sfVector2f tmpvf;
    
    int i,j;
    for(j=0;j<8;j++){
        for(i=0;i<8;i++){
            if(selected.dragging and selected.x == i and selected.y == j){
                continue;
            }else{
                tmpvf.x = c_offset.x+c_pieceW*i;
                tmpvf.y = c_offset.y+c_pieceW*j;
            }
            if(c_boardCopy[j*8+i] == '+'){
                if(c_board[j*8+i] != '-'){
                    tmpSprite = get_sprite(c_board[j*8+i]);
                    sfSprite_setPosition(tmpSprite, tmpvf);
                    sfRenderWindow_drawSprite(g_window , tmpSprite, NULL);
                }
                tmpvf.x = c_offset.x+(c_pieceW)/2-c_pieceW/4+c_pieceW*i;
                tmpvf.y = c_offset.y+(c_pieceW)/2-c_pieceW/4+c_pieceW*j;
                
                sfCircleShape_setPosition(canMoveSquare, tmpvf);
                sfRenderWindow_drawCircleShape(g_window, canMoveSquare, NULL);
            }
            else if(c_boardCopy[j*8+i] != '-'){
                
                tmpSprite = get_sprite(c_board[j*8+i]);
                sfSprite_setPosition(tmpSprite, tmpvf);
                sfRenderWindow_drawSprite(g_window, tmpSprite,NULL);
            }
        }
    }
    if(selected.dragging){
        tmpSprite = get_sprite(c_board[selected.y*8+selected.x]);
        sfVector2i tmpvi = sfMouse_getPositionRenderWindow(g_window);
        tmpvf.x = tmpvi.x-c_pieceW/2;
        tmpvf.y = tmpvi.y-c_pieceW/2;
        sfSprite_setPosition(tmpSprite, tmpvf);
        sfRenderWindow_drawSprite(g_window, tmpSprite,NULL);
    }
}

void finalize(){
    free(c_board);
    free(c_boardCopy);

    int i=0;
    for(i=0;i<64;i++)
        c_allPossibleMoves[i]->free(c_allPossibleMoves[i]);
    
    for(i=0;i<13;i++){
        sfTexture_destroy(c_img[i]);
        sfSprite_destroy(c_sprite[i]);
    }
    sfMusic_destroy(c_caputreSound);
    sfMusic_destroy(c_moveSound);
    sfCircleShape_destroy(canMoveSquare);
    sfRenderWindow_destroy(g_window);
}


bool in_check(char color, char* board){
    int i=0;
    for(i=0;i<strlen(board);i++)
        if(color == board[i])
            break;
    vector_i* posb;
    posb = rook_moves(i,board);
    {FOR(n, posb)
        if(isalpha(board[n])){
            if( !is_black(color)){
                if(board[n] == 'q' or board[n] == 'r') return true;
            }else if(board[n] == 'Q' or board[n] == 'R') return true;
        }
    }}
    posb->free(posb);
    posb = bishop_moves(i, board);
    {FOR(n, posb)
        if(isalpha(board[n])){
            if( !is_black(color)){
                if(board[n] == 'q' or board[n] == 'b') return true;
            }else if(board[n] == 'Q' or board[n] == 'B') return true;
        }
    }}
    posb->free(posb);
    posb = knight_moves(i, board);
    {FOR(n, posb)
        if(isalpha(board[n])){
            if( !is_black(color)){
                if(board[n] == 'n') return true;
            }else if(board[n] == 'N') return true;
        }
    }}
    posb->free(posb);
    return false;
}

char piece_selecter(char peice[]){
    sfVector2f tmpvf;
    sfVector2i pos, drawPeice;
    sfSprite* tmpSprite;
    int i;
    drawPeice.x = (g_ScreenWidth/2)-(2*c_pieceW);
    drawPeice.y = (g_ScreenHeight-c_pieceW)/2;
    bool selected = false;
    while(!selected){
        while (sfRenderWindow_pollEvent(g_window, &g_event)){
            switch(g_event.type){
                case sfEvtClosed:
                    sfRenderWindow_close(g_window);
                    return 'p';
                    break;
                case sfEvtMouseButtonReleased:
                    pos = sfMouse_getPositionRenderWindow(g_window);
                    //printf("pos: %d %d %d", pos.x, pos.y, (pos.x-drawPeice.x)/c_pieceW);
                    if(pos.x > drawPeice.x and pos.x < drawPeice.x + 4* c_pieceW and
                        pos.y > drawPeice.y and pos.y < drawPeice.y+c_pieceW){
                        pos.x -= drawPeice.x;
                        return peice[pos.x/c_pieceW];
                    }
                    else return peice[0]=='Q'?'P':'p';
                    break;
            }
        }
        tmpvf.y = drawPeice.y;
        draw_pieces();
        for(i=0;i<4;++i){
            tmpvf.x = drawPeice.x+i*c_pieceW;
            tmpSprite = get_sprite(peice[i]);
            sfSprite_setPosition(tmpSprite, tmpvf);
            sfRenderWindow_drawSprite(g_window , tmpSprite, NULL);
        }
        sfRenderWindow_display(g_window);
    }
    
}

vector_i* get_possible_moves(int pos,char color,char* board){
    VECTOR_INIT_EXPORT(v0);
    VECTOR_INIT_EXPORT(v1);
    if(!is_samecolor(color, board[pos])) return v0;
    switch(board[pos]){
            case 'r':
            case 'R':
                v0 = rook_moves(pos, board);
                break;
            case 'b':
            case 'B':
                v0= bishop_moves(pos, board);
                break;
            case 'n':
            case 'N':
                v0= knight_moves(pos,board);
                break;
            case 'K':
            case 'k':
                v0= king_moves(pos,board);
                break;
            case 'p':
            case 'P':
                v0= pawn_moves(pos, board);
                break;
            case 'q':
            case 'Q':
                 v0 = rook_moves(pos, board); v1 = bishop_moves(pos, board);
                 
                v0->extend(v0,v1);
                break;
            
        }
        char king = is_black(board[pos])?'k':'K';
        v1->clear(v1);
        int n;
        for(n=0;n<v0->size(v0);n++){
            char* tmpBoard = strdup(board);
            tmpBoard[v0->get(v0,n)] = tmpBoard[pos];
            tmpBoard[pos] = '-';
            if(!in_check(king, tmpBoard)){
                v1->append(v1, v0->get(v0,n));
            }
        }
        v0->free(v0);
        free(v0);
        return v1;
}

bool in_checkmate(char color, char* board, vector_i* allPieceMoves[]){
    VECTOR_INIT(tmp);
    bool checkmate = true;
    int i=0;
    for(i=0;i<64;i++){
        allPieceMoves[i]->free(allPieceMoves[i]);
        if(is_samecolor(board[i], color)){
            allPieceMoves[i] = get_possible_moves(i,color, board);
            if(allPieceMoves[i]->size(allPieceMoves[i])>0) checkmate = false;
        }
    }
    return checkmate;
}

void move_piece(int from, int to){
    
    /*if(c_board[from] == 'p' and to>55){
        char peice[] = {'q','r','b','n'};
        c_board[from] = piece_selecter(peice);
    }
    else if(c_board[from] == 'P'and to < 8){
        char peice[] = {'Q','R','B','N'};
        c_board[from] = piece_selecter(peice);
    }*/
    if(isalpha(c_board[to])) {
        sfMusic_play(c_caputreSound);
        sfMusic_setPlayingOffset(c_caputreSound, sfTime_Zero);
        
    }
    else {
        sfMusic_play(c_moveSound);
        sfMusic_setPlayingOffset(c_moveSound, sfTime_Zero);
    }
    c_board[to] = c_board[from];
    c_board[from] = '-';
    c_active = -1;
    c_currentColor = c_currentColor=='K'?'k':'K';
}


int evaluation(char color,  char* board){
    /* material = 100 * (wp - bp) + 320 * (wn - bn) 
                + 330 * (wb - bb) + 500 * (wr - br) 
                + 900 * (wq - bq)
    */
   //if(in_checkmate(color, board)) return color=='K'?-9999:9999;
    int counts[256] = { 0 };
    int pawnsq=0, knightsq=0, bishopsq=0,rooksq=0, queensq=0, kingsq=0;
    int i;
    size_t len = 64;
    for (i = 0; i < len; i++) {
        switch(board[i]){
            case 'p':
                pawnsq -= pawntable[i];
                break;
            case 'P':
                pawnsq += pawntable[i];
                break;
            case 'n':
                knightsq -= knightstable[i];
                break;
            case 'N':
                knightsq += knightstable[i];
                break;
            case 'b':
                bishopsq -= bishopstable[i];
                break;
            case 'B':
                bishopsq += bishopstable[i];
                break;
            case 'r':
                rooksq -= rookstable[i];
                break;
            case 'R':
                rooksq += rookstable[i];
                break;
            case 'q':
                pawnsq -= queenstable[i];
                break;
            case 'Q':
                pawnsq += queenstable[i];
                break;
            case 'k':
                kingsq -= kingstable[i];
                break;
            case 'K':
                kingsq += kingstable[i];
                break;
        }
        counts[board[i]]++;
    }
    int material = 100 * (counts['P'] - counts['p']) + 320 * (counts['N'] - counts['n'])
                    + 330 * (counts['B'] - counts['b']) + 500 * (counts['R'] - counts['r'])
                    + 900 * (counts['Q'] - counts['q']);
    
    return material + pawnsq + knightsq + bishopsq + rooksq + queensq + kingsq;
}
/*
int find_best(vector_i* possible, int depth, char* board, char color){
    if(depth<=0) return 0;
    int best=0, result=0, tmp;
    for(i=0;i<n;i++){
        FOR(n, possible[i])
            board[n] = board[i];
            board[i] = '-';
            tmp = evaluation(color, board);
            if(tmp > best){
                
            }
        }
    }
    return 0;
}*/


int runGame(sfRenderWindow* g_window){
    sfFloatRect view = {0, 0, g_ScreenWidth, g_ScreenHeight};
    sfVector2i pos;
    sfRenderWindow_clear(g_window, sfColor_fromRGB(25,25,25));
    
    while(sfRenderWindow_pollEvent(g_window, &g_event)){
        switch(g_event.type){
            case sfEvtClosed:
                sfRenderWindow_close(g_window);
                return true;
            case sfEvtResized:
                g_ScreenHeight = g_event.size.height;
                g_ScreenWidth = g_event.size.width;
                view.height = g_ScreenHeight;
                view.width = g_ScreenWidth;
                sfRenderWindow_setView(g_window,sfView_createFromRect(view));
                set_board_size(g_ScreenHeight);
                break;
            case sfEvtKeyPressed:
                if(sfKeyboard_isKeyPressed(sfKeyEscape))
                    return true;
                if(sfKeyboard_isKeyPressed(sfKeyQ))
                    reset_board();
                    return true;
            case sfEvtMouseButtonPressed:
                selected.dragging = true;
                pos = sfMouse_getPositionRenderWindow(g_window);
                pos.x = (pos.x - c_offset.x)/c_pieceW;
                pos.y = (pos.y - c_offset.y)/c_pieceW;
                selected.x = pos.x;
                selected.y = pos.y;
                if(c_active > -1){
                    selected.dragging = false;
                    if(v_find(v, pos.y*8+pos.x)){
                        if(c_board[c_active] == 'p' and pos.y *8 + pos.x>55){
                            char peice[] = {'q','r','b','n'};
                            char from = piece_selecter(peice);
                            if(from != 'p')
                            c_board[c_active] = from;
                            else break;
                        }
                        else if(c_board[c_active] == 'P'and pos.y *8 + pos.x < 8){
                            char peice[] = {'Q','R','B','N'};
                            char from = piece_selecter(peice);
                            if(from != 'P')
                            c_board[c_active] = from;
                            else break;
                        }
                        move_piece(c_active, pos.y *8 + pos.x);
                        free(c_boardCopy);
                        c_boardCopy = strdup(c_board);
                        //printf("eval : %d ", evaluation(c_currentColor, c_board));
                        
                        if(in_checkmate(c_currentColor, c_board, c_allPossibleMoves)){
                            printf("Game Over");
                            reset_board();
                            return true;
                        }
                        break;
                    }
                }
                if(isalpha(c_board[pos.y*8+pos.x]) and is_samecolor(c_board[pos.y *8 + pos.x], c_currentColor)){
                    free(c_boardCopy);
                    c_boardCopy = strdup(c_board);
                    c_active = pos.y*8+pos.x;
                    v = c_allPossibleMoves[pos.y*8+pos.x];
                    
                    FOR(n, v)
                        c_boardCopy[n] = '+';
                    }
                }else{
                    c_active = -1; 
                    free(c_boardCopy);
                    c_boardCopy = strdup(c_board);
                }
                break;
            case sfEvtMouseButtonReleased:
                pos = sfMouse_getPositionRenderWindow(g_window);
                pos.x = (pos.x - c_offset.x)/c_pieceW;
                pos.y = (pos.y - c_offset.y)/c_pieceW;
                selected.dragging = false;
                
                if(c_active > -1){
                    if(v_find(v, pos.y*8+pos.x)){
                        if(c_board[c_active] == 'p' and pos.y *8 + pos.x>55){
                            char peice[] = {'q','r','b','n'};
                            char from = piece_selecter(peice);
                            if(from != 'p')
                            c_board[c_active] = from;
                            else break;
                        }
                        else if(c_board[c_active] == 'P'and pos.y *8 + pos.x < 8){
                            char peice[] = {'Q','R','B','N'};
                            char from = piece_selecter(peice);
                            if(from != 'P')
                            c_board[c_active] = from;
                            else break;
                        }
                        move_piece(c_active, pos.y *8 + pos.x);
                        free(c_boardCopy);
                        c_boardCopy = strdup(c_board);
                        //printf("eval : %d ", evaluation(c_currentColor, c_board));
                        if(in_checkmate(c_currentColor, c_board, c_allPossibleMoves)){
                            printf("Game Over");
                            reset_board();
                            return true;
                        }
                        break;
                    }
                }

                break;
        }
    }

    draw_pieces();
    
    return false;
}

bool is_on(sfVector2i pos, sfText* text){
    sfVector2f buttPos = sfText_getPosition(text), size;
    size.x = sfText_getLocalBounds(text).width;
    size.y =sfText_getLocalBounds(text).height;
    if(pos.x > buttPos.x and pos.x < buttPos.x+size.x and 
        pos.y > buttPos.y and pos.y < buttPos.y+size.y){
        sfText_setCharacterSize(text, 70);
        return true;
    }
    return false;
}

int main(){
    init();
    
    
    sfVector2i pos;
    
    sfText *playText = sfText_create(), *quitText = sfText_create();
    
    sfText_setString(playText,"Play");
    sfText_setString(quitText,"Quit");
    sfText_setFont(playText, sfFont_createFromFile("MF.ttf"));
    sfText_setFillColor(playText, sfBlack);
    sfText_setCharacterSize(playText, 50);
    sfText_setFont(quitText, sfFont_createFromFile("MF.ttf"));
    sfText_setFillColor(quitText, sfBlack);
    sfText_setCharacterSize(quitText, 50);
    
    sfVector2f size, tmpvf;
    size.x = sfText_getLocalBounds(playText).width;
    size.y =sfText_getLocalBounds(playText).height;
    sfVector2f buttPos = {(g_ScreenWidth-size.x)/2,(g_ScreenHeight-size.y)/2 };
    size.x = sfText_getLocalBounds(quitText).width;
    size.y =sfText_getLocalBounds(quitText).height;
    sfVector2f buttPos1 = {(g_ScreenWidth-size.x)/2,(g_ScreenHeight+75+size.y)/2 };
    sfText_setPosition(playText, buttPos);
    sfText_setPosition(quitText, buttPos1);
    
    sfCircleShape* c = sfCircleShape_create();
    sfCircleShape_setFillColor(c, sfColor_fromRGB(0,0,0));
    bool drawCircle = false;
    float radius = 1;

    sfFloatRect view = {0, 0, g_ScreenWidth, g_ScreenHeight};
    /* Start the game loop */
    while (sfRenderWindow_isOpen(g_window)){
        /* Clear the screen */
        sfRenderWindow_clear(g_window, sfWhite);
        if(state == HOME){
            //sfRenderWindow_drawRectangleShape(g_window,button,NULL);
            sfRenderWindow_drawText(g_window, playText, NULL);
            sfRenderWindow_drawText(g_window, quitText, NULL);
            if(drawCircle){
                if(radius > g_ScreenHeight and radius >g_ScreenWidth) {
                    
                    state = PLAYING;
                    radius = 1;
                    drawCircle = false;
                }
                radius += radius>200?radius*0.07:radius*0.2;
                tmpvf.x = pos.x-radius;
                tmpvf.y = pos.y-radius;
                sfCircleShape_setRadius(c,radius);
                sfCircleShape_setPosition(c, tmpvf);
                sfRenderWindow_drawCircleShape(g_window, c, NULL);
            }
            while (sfRenderWindow_pollEvent(g_window, &g_event)){
                
                switch (g_event.type){
                    case sfEvtClosed:
                        sfRenderWindow_close(g_window);
                        break;
                    case sfEvtMouseButtonReleased:
                        pos = sfMouse_getPositionRenderWindow(g_window);
                        if(is_on(pos,playText)){
                            drawCircle = true;
                        }else if(is_on(pos,quitText)){
                            sfRenderWindow_close(g_window);
                        }
                        break;
                    case sfEvtMouseMoved:
                        pos = sfMouse_getPositionRenderWindow(g_window);
                        if(is_on(pos,playText)){
                            size.x = sfText_getLocalBounds(playText).width;
                            size.y =sfText_getLocalBounds(playText).height;
                            buttPos.x = (g_ScreenWidth-size.x)/2;
                            buttPos.y = (g_ScreenHeight-size.y)/2;
                            sfText_setPosition(playText, buttPos);
                        }else if(is_on(pos, quitText)){
                            size.x = sfText_getLocalBounds(quitText).width;
                            size.y =sfText_getLocalBounds(quitText).height;
                            buttPos1.x = (g_ScreenWidth-size.x)/2;
                            buttPos1.y = (g_ScreenHeight+size.y+75)/2;
                            sfText_setPosition(quitText, buttPos1);
                        }else if(sfText_getCharacterSize(playText) != 50){
                            sfText_setCharacterSize(playText, 50);
                            size.x = sfText_getLocalBounds(playText).width;
                            size.y =sfText_getLocalBounds(playText).height;
                            buttPos.x = (g_ScreenWidth-size.x)/2;
                            buttPos.y = (g_ScreenHeight-size.y)/2;
                            sfText_setPosition(playText, buttPos);
                        }
                        else if(sfText_getCharacterSize(quitText) != 50){
                            sfText_setCharacterSize(quitText, 50);
                            size.x = sfText_getLocalBounds(quitText).width;
                            size.y =sfText_getLocalBounds(quitText).height;
                            buttPos1.x = (g_ScreenWidth-size.x)/2;
                            buttPos1.y = (g_ScreenHeight+size.y+75)/2;
                            sfText_setPosition(quitText, buttPos1);
                        }
                        break;
                    case sfEvtResized:
                        g_ScreenHeight = g_event.size.height;
                        g_ScreenWidth = g_event.size.width;
                        view.height = g_ScreenHeight;
                        view.width = g_ScreenWidth;
                        sfRenderWindow_setView(g_window,sfView_createFromRect(view));
                        set_board_size(g_ScreenHeight);
                        
                        sfText_setCharacterSize(quitText, 50);
                        sfText_setCharacterSize(playText, 50);
                        size.x = sfText_getLocalBounds(playText).width;
                        size.y =sfText_getLocalBounds(playText).height;
                        buttPos.x = (g_ScreenWidth-size.x)/2;
                        buttPos.y = (g_ScreenHeight-size.y)/2;
                        sfText_setPosition(playText, buttPos);
                        size.x = sfText_getLocalBounds(quitText).width;
                        size.y =sfText_getLocalBounds(quitText).height;
                        buttPos1.x = (g_ScreenWidth-size.x)/2;
                        buttPos1.y = (g_ScreenHeight+size.y+75)/2;
                        sfText_setPosition(quitText, buttPos1);
                        break;
                } 
            }
        }else if(state == PLAYING){
            if(runGame(g_window)) state = HOME;
        }
        /* Update the g_window */
        sfRenderWindow_display(g_window);
    }

    /* Cleanup resources */
    sfText_destroy(playText);
    sfText_destroy(quitText);
    finalize();
    return EXIT_SUCCESS;
}
