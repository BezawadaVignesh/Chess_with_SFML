#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "chess_moves.hpp"


class Chess{
    private:
    sf::Music caputreSound, moveSound;
    sf::Texture img[13];
    sf::Sprite sprite[32];
    int pieceW = 600/8;
    std::vector<int> v = {};
    char currentColor = 'K';
    std::string board = "rnbqkbnrpppppppp--------------------------------PPPPPPPPRNBQKBNR";
    std::string board_copy = board;
    int active = -1;
    sf::RectangleShape canMoveSquare = sf::RectangleShape(sf::Vector2f(pieceW,pieceW));
    std::vector<int> allPiecesMoves[64];
    public:
    Chess(){
        if(!img[0].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\board.png") or
        !img[1].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\wk.png") or
        !img[2].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\wq.png") or
        !img[3].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\wr.png") or
        !img[4].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\wbi.png") or
        !img[5].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\wkn.png") or
        !img[6].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\wp.png") or
        !img[7].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\bk.png") or
        !img[8].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\bq.png") or
        !img[9].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\br.png") or
        !img[10].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\bbi.png") or
        !img[11].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\bkn.png") or
        !img[12].loadFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\bp.png")){
            printf("Cant load image");
        }
        else{
            sprite[0].setTexture(img[0]);
            sprite[0].setScale(600/sprite[0].getLocalBounds().width,600/sprite[0].getLocalBounds().height);
        for(int i=1;i<13;i++){
            sprite[i].setTexture(img[i]);
            sprite[i].setScale(600/(8*sprite[i].getLocalBounds().width),600/(8*sprite[i].getLocalBounds().height));
        }
        }
        
        if(!caputreSound.openFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\capture.wav")){
            printf("cant load sound files");
        }
        if(!moveSound.openFromFile("C:\\Users\\Lokanadh\\Documents\\vignesh\\learnSFML\\img\\move-self.wav")){
            printf("cant load sound files");
        }
    }
    
    
    void draw_pieces( sf::RenderWindow& window, std::string board_copy){
        
        window.draw(sprite[0]);
        for(int j=0;j<8;j++){
            for(int i=0;i<8;i++){
            switch(board_copy[j*8+i]){
                case 'K':
                    sprite[1].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[1]); break;
                case 'Q':
                    sprite[2].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[2]); break;
                case 'R':
                    sprite[3].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[3]); break;
                case 'B':
                    sprite[4].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[4]); break;
                case 'N':
                    sprite[5].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[5]); break;
                case 'P':
                    sprite[6].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[6]); break;
                case 'k':
                    sprite[7].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[7]); break;
                case 'q':
                    sprite[8].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[8]); break;
                case 'r':
                    sprite[9].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[9]); break;
                case 'b':
                    sprite[10].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[10]); break;
                case 'n':
                    sprite[11].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[11]); break;
                case 'p':
                    sprite[12].setPosition(pieceW*i,pieceW*j);
                    window.draw(sprite[12]); break;
                case '+':
                    canMoveSquare.setFillColor(sf::Color(255,0,0,125));
                    canMoveSquare.setPosition(pieceW*i,pieceW*j);
                    window.draw(canMoveSquare);
                    //if(isalpha(board[j*8+i]))
                    break;
                case '-':
                    break;
                default:
                    printf("Invalid string got %c",board_copy[j*8+i]);
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
                    if(board[n] == 'k') return true;
                }else if(board[n] == 'K') return true;
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
    
    void run(sf::RenderWindow& window){
        
        
        sf::Event event;
        if(in_checkmate(currentColor, board)){
            window.close();
            printf("Game Over");
        }
        while(window.pollEvent(event)){
            // "close requested" event: we close the window
            switch(event.type){
                case sf::Event::Closed :
                    window.close();
                case sf::Event::MouseButtonReleased:
                    sf::Vector2i pos = sf::Mouse::getPosition(window)/ pieceW;
                    
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
    }
};