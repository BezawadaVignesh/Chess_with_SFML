
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "chess_moves.hpp"
#include "settings.hpp"

class Chess{
    private:
    sf::Music caputreSound, moveSound;
    sf::Texture img[13];
    sf::Sprite sprite[32];
    int boardSize = SCREEN_HEIGHT;
    int pieceW = boardSize/8; // if change size
    std::vector<int> v = {};
    sf::Vector2i offset = {(int)(SCREEN_WIDTH-boardSize)/2,0};
    char currentColor = 'K';
    
    std::string board = "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";
    std::string board_copy = board;
    int active = -1;
    sf::CircleShape canMoveSquare = sf::CircleShape(20);
    std::vector<int> allPiecesMoves[64];
    public:
    Chess(){
        std::string imgLoc = "..\\img";
        if(!img[0].loadFromFile(imgLoc+"\\board.png") or
        !img[1].loadFromFile(imgLoc+"\\wk.png") or
        !img[2].loadFromFile(imgLoc+"\\wq.png") or
        !img[3].loadFromFile(imgLoc+"\\wr.png") or
        !img[4].loadFromFile(imgLoc+"\\wbi.png") or
        !img[5].loadFromFile(imgLoc+"\\wkn.png") or
        !img[6].loadFromFile(imgLoc+"\\wp.png") or
        !img[7].loadFromFile(imgLoc+"\\bk.png") or
        !img[8].loadFromFile(imgLoc+"\\bq.png") or
        !img[9].loadFromFile(imgLoc+"\\br.png") or
        !img[10].loadFromFile(imgLoc+"\\bbi.png") or
        !img[11].loadFromFile(imgLoc+"\\bkn.png") or
        !img[12].loadFromFile(imgLoc+"\\bp.png")){
            printf("Cant load image");
        }
        else{
            sprite[0].setPosition(offset.x,offset.y);
            sprite[0].setTexture(img[0]);
            sprite[0].setScale(boardSize/sprite[0].getLocalBounds().width,boardSize/sprite[0].getLocalBounds().height);

        for(int i=1;i<13;i++){
            sprite[i].setTexture(img[i]);
            sprite[i].setScale(boardSize/(8*sprite[i].getLocalBounds().width),boardSize/(8*sprite[i].getLocalBounds().height));
        }
        }
        
        if(!caputreSound.openFromFile(imgLoc+"\\capture.wav")){
            printf("cant load sound files");
        }
        if(!moveSound.openFromFile(imgLoc+"\\move-self.wav")){
            printf("cant load sound files");
        }
    }
    
    void set_board_size(int newSize){
        boardSize = newSize;
        pieceW = boardSize/8;
        offset.x = (int)(SCREEN_WIDTH-boardSize)/2;
        sprite[0].setPosition(offset.x,offset.y);
            sprite[0].setScale(boardSize/sprite[0].getLocalBounds().width,boardSize/sprite[0].getLocalBounds().height);
        for(int i=1;i<13;i++)
            sprite[i].setScale(boardSize/(8*sprite[i].getLocalBounds().width),boardSize/(8*sprite[i].getLocalBounds().height));
        
    }

    void resetBoard(){
        board = "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";
        currentColor = 'K';
        board_copy = board;
    }

    sf::Sprite get_sprite(char piece){
        switch(piece){
                case 'K':
                    return sprite[1];
                case 'Q':
                    return sprite[2];
                case 'R':
                    return sprite[3];
                case 'B':
                    return sprite[4];
                case 'N':
                    return sprite[5];
                case 'P':
                    return sprite[6];
                case 'k':
                    return sprite[7];
                case 'q':
                    return sprite[8];
                case 'r':
                    return sprite[9];
                case 'b':
                    return sprite[10];
                case 'n':
                    return sprite[11];
                case 'p':
                    return sprite[12];  
                case '-':
                    break;
                default:
                    printf("Invalid string got %c",piece);
            }
    }

    void draw_pieces( sf::RenderWindow& window, std::string board_copy){
        
        window.draw(sprite[0]);
        sf::Sprite tmpSprite;
        for(int j=0;j<8;j++){
            for(int i=0;i<8;i++){
                if(board_copy[j*8+i] == '+'){
                    if(board[j*8+i] != '-'){
                        tmpSprite = get_sprite(board[j*8+i]);
                        tmpSprite.setPosition(offset.x+pieceW*i,offset.y+pieceW*j);
                        window.draw(tmpSprite);
                    }
                    canMoveSquare.setFillColor(sf::Color(255,0,0,200));
                    canMoveSquare.setPosition(offset.x+(pieceW)/2-20+pieceW*i,offset.y+(pieceW)/2-20+pieceW*j);
                    window.draw(canMoveSquare);
                    
                }
                else if(board_copy[j*8+i] != '-'){
                    
                    tmpSprite = get_sprite(board_copy[j*8+i]);
                    tmpSprite.setPosition(offset.x+pieceW*i,offset.y+pieceW*j);
                    window.draw(tmpSprite);
                }
            }
        }
    }
    
    bool in_checkmate(char color,std::string board){
        std::vector<int> tmp;
        bool checkmate = true;
        for(int i=0;i<64;i++){
            allPiecesMoves[i].clear();
            if(is_samecolor(board[i], color)){
                allPiecesMoves[i] = get_possible_moves(i, board, color);
                if(allPiecesMoves[i].size() > 0) checkmate = false;
            }
        }
        return checkmate;
    }

    bool in_check(char color ,std::string board){
        int i;
        for(i=0;i<board.length();i++){
            if(color == board[i])
                break;
        }
        std::vector<int> posb = rook_moves(i, board);
        for(int n:posb){
            if(isalpha(board[n])){
                if( !is_black(color)){
                    if(board[n] == 'q' or board[n] == 'r') return true;
                }else if(board[n] == 'Q' or board[n] == 'R') return true;
            }
        }
        posb = bishop_moves(i, board);
        for(int n:posb){
            if(isalpha(board[n])){
                if( !is_black(color)){
                    if(board[n] == 'q' or board[n] == 'b') return true;
                }else if(board[n] == 'Q' or board[n] == 'B') return true;
            }
        }
        posb = knight_moves(i, board);
        for(int n:posb){
            if(isalpha(board[n])){
                if( !is_black(color)){
                    if(board[n] == 'n') return true;
                }else if(board[n] == 'N') return true;
            }
        }
        return false;
        
    }
    
    
    std::vector<int> get_possible_moves(int pos, std::string board,char color){
        std::vector<int> v0,v1;
        if(!is_samecolor(color, board[pos])) return {};
        switch(board[pos]){
            case 'r':
            case 'R':
                v0 = rook_moves(pos, board);
                break;
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
                v0.insert(v0.end(),v1.begin(),v1.end());
                break;
            default:
                v0= {};
        }
        char king = is_black(board[pos])?'k':'K';
        v1.clear();
        for(int n=0;n<v0.size();n++){
            std::string tmpBoard = board;
            tmpBoard[v0[n]] = tmpBoard[pos];
            tmpBoard[pos] = '-';
            if(!in_check(king, tmpBoard))
                v1.push_back(v0[n]);
            
        }
        return v1;
    }
    
    void move_piece(int from, int to){
        if(isalpha(board[to])) caputreSound.play();
        else moveSound.play();
        
        board[to] = board[from];
        board[from]='-';
        active = -1;
        currentColor = currentColor=='K'?'k':'K';
    }
    
    bool run(sf::RenderWindow& window){

        sf::Event event;
        if(in_checkmate(currentColor, board)){
            std::cout<<"Game Over";
            return true;
        }
        sf::FloatRect view;
        while(window.pollEvent(event)){
            // "close requested" event: we close the window
            switch(event.type){
                case sf::Event::Closed :
                    window.close();
                case sf::Event::Resized:
                    SCREEN_WIDTH = event.size.width;
                    SCREEN_HEIGHT = event.size.height;
                    view = sf::FloatRect(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(view));
                    set_board_size(SCREEN_HEIGHT);
                    break;
                case sf::Event::MouseButtonReleased:
                    sf::Vector2i pos = (sf::Mouse::getPosition(window)-offset)/ pieceW;
                    
                    if(active > -1){
                        
                        if(std::find(v.begin(),v.end(),pos.y *8 + pos.x) != v.end()){
                            move_piece(active, pos.y *8 + pos.x);
                            board_copy=board;
                            caputreSound.setPlayingOffset(sf::seconds(0.f));
                            moveSound.setPlayingOffset(sf::seconds(0.f));
                            break;
                        }
                    } if(isalpha(board[pos.y *8 + pos.x]) and is_samecolor(board[pos.y *8 + pos.x], currentColor)){
                        board_copy = board;
                        active = pos.y *8 + pos.x;
                        v = allPiecesMoves[pos.y *8 + pos.x];
                        
                        for(int i: v){
                            board_copy[i] = '+';
                        }
                    }else {active = -1;board_copy=board;}
                break;
            }
        }
        window.clear(sf::Color(255,255,255));
        window.draw(sprite[0]);

        draw_pieces(window, board_copy);//"rnbqkbnrpppppppp-------------------------------PPPPPPPPRNBKQKBNR"
        return false;
    }
};
