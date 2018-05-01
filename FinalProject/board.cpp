#include "game.h"
#include "board.h"
#include "board.h"
#include <ctime>        // std::time

extern Game * game;

Board& Board::getInstance()
{
    static Board instance;
    return instance;
}


void Board::MakeBoard(int xPos, int yPos)
{

    for(int i = 0; i < 47; i++){
        P1_heros.append(NULL);
        P2_heros.append(NULL);
    }

    double xSHIFT,ySHIFT;

    Tile * OffsetInfo = new Tile();

    xSHIFT =(OffsetInfo->SCALE_BY*(OffsetInfo->sideOffset+1));
    ySHIFT = OffsetInfo->SCALE_BY* OffsetInfo->sideOffset;

    delete OffsetInfo;

    makeTileColumn(xPos-2,yPos+ySHIFT*4,4);//1st column - index: 0-3
    makeTileColumn(xPos+xSHIFT,yPos+ySHIFT,7);//2nd column - index: 4-10

    makeTileColumn(xPos+xSHIFT*2,yPos,8); //3rd column - index: 11-18
    makeTileColumn(xPos+xSHIFT*3,yPos-ySHIFT,9); //4th column - index: 19-27
    makeTileColumn(xPos+xSHIFT*4,yPos,8); //5th column - index: 28-35

    makeTileColumn(xPos+xSHIFT*5,yPos+ySHIFT,7); //6th column - index: 36-42
    makeTileColumn(xPos+xSHIFT*6,yPos+ySHIFT*4,4); //7th column - index: 43-46



    setSpawnTiles();//seting Spawn points
    ResourceTiles();//seting Resource Tiles ResourceTiles(true) = RANDOM tiles

    //seting caltapult
    boardContainer[23]->setZValue(1);
    boardContainer[23]->setState(state::caltaput);
}

void Board::setSpawnTiles()
{
     boardContainer[0]->setState(state::spawn_p1);
     boardContainer[1]->setState(state::spawn_p1);
     boardContainer[2]->setState(state::spawn_p1);
     boardContainer[3]->setState(state::spawn_p1);
     boardContainer[43]->setState(state::spawn_p2);
     boardContainer[44]->setState(state::spawn_p2);
     boardContainer[45]->setState(state::spawn_p2);
     boardContainer[46]->setState(state::spawn_p2);
}

void Board::ResourceTiles(bool israndom)
{
    std::srand(unsigned(std::time(0)));

    if(israndom){
        int first = (rand() %2 ) + 11;
        int second = (rand() %2 ) + 14;
        int third = (rand() %2 ) + 17;

        boardContainer[first]->setState(state::resource_one);
        boardContainer[second]->setState(state::resource_one);
        boardContainer[third]->setState(state::resource_one);


        boardContainer[first+17]->setState(state::resource_one);
        boardContainer[second+17]->setState(state::resource_one);
        boardContainer[third+17]->setState(state::resource_one);

        boardContainer[21]->setState(state::resource_two);
        boardContainer[25]->setState(state::resource_two);
    }
    else{
        boardContainer[4]->setState(state::resource_one);
        boardContainer[10]->setState(state::resource_one);
        boardContainer[13]->setState(state::resource_one);
        boardContainer[16]->setState(state::resource_one);

        boardContainer[36]->setState(state::resource_one);
        boardContainer[42]->setState(state::resource_one);
        boardContainer[13+17]->setState(state::resource_one);
        boardContainer[16+17]->setState(state::resource_one);

        boardContainer[20]->setState(state::resource_two);
        boardContainer[26]->setState(state::resource_two);
    }
}



void Board::SpawnCard(Tile *card, PlayerTurn t)
{

    if(t == PlayerTurn::one){
        for(int i = 0; i < boardContainer.size(); i++){
            if(boardContainer[i]->getState() == state::spawn_p1){
                card->setPos(boardContainer[i]->pos());
                //boardContainer[i]->scene()->removeItem(boardContainer[i]);
                P1_heros[i] = card;
                boardContainer[i]->setState(state::empty);
                return;
            }
        }


    }else if(t == PlayerTurn::two){
        for(int i = 0; i < boardContainer.size(); i++){
            if(boardContainer[i]->getState() == state::spawn_p2){
                card->setPos(boardContainer[i]->pos());
                //boardContainer[i]->scene()->removeItem(boardContainer[i]);
                P2_heros[i] = card;
                boardContainer[i]->setState(state::empty);
                return;
            }
        }

    }
}

void Board::MoveTile(Tile *herotile, Tile *PosToPlace)
{
    if(herotile->getOwner() == tileOwner::one){
        if(game->getTurn() == PlayerTurn::one){
            int index_current = P1_heros.indexOf(herotile);
            int index_place = boardContainer.indexOf(PosToPlace);

            if(P1_heros[index_current]->getHasMoved() == true){
                qDebug() << "\nYou have already moved this hero!";
                return;
            }
            if(index_place == 43 || index_place == 44 || index_place == 45 || index_place == 46){
                qDebug() << "\nYou cannot moved to Opponent's Spawn!";
                return;
            }


            if(P1_heros[index_place] == NULL){
                P1_heros[index_current] = NULL;
                P1_heros[index_place] = herotile;
                P1_heros[index_place]->setMovedTrue();
            }else{
                qDebug() << "Tile is Occupied by hero!";
                return;
            }
            SpwanReset();
            herotile->setPos(boardContainer[index_place]->pos());

        }else{
            qDebug() << "You Cannot Move Opponents heroes!";
        }


    }else if(herotile->getOwner() == tileOwner::two){
        if(game->getTurn() == PlayerTurn::two){
            int index_current = P2_heros.indexOf(herotile);
            int index_place = boardContainer.indexOf(PosToPlace);

            if(P2_heros[index_current]->getHasMoved() == true){
                qDebug() << "\nYou have already moved this hero!";
                return;
            }
            if(index_place == 0 || index_place == 1 || index_place == 2 || index_place == 3){
                qDebug() << "\nYou cannot moved to Opponent's Spawn!";
                return;
            }

            if(P2_heros[index_place] == NULL){
                P2_heros[index_current] = NULL;
                P2_heros[index_place] = herotile;
                P2_heros[index_place]->setMovedTrue();
            }else{
                qDebug() << "Tile is Occupied by hero!";
                return;

            }
            SpwanReset();
            herotile->setPos(boardContainer[index_place]->pos());

        }else{
            qDebug() << "You Cannot Move Opponents heroes!";
        }
    }

}



void Board::SpwanReset(){
    for(int i = 0; i < 4; i++){
        if(P1_heros[i] == NULL){
            boardContainer[i]->setState(state::spawn_p1);
        }

        if(P2_heros[i+43] == NULL){
            boardContainer[i+43]->setState(state::spawn_p2);
        }
    }
}


PlayerTurn Board::CapturedCaltapult(){
    if(P1_heros[23] != NULL){
        return PlayerTurn::one;
    }else if(P2_heros[23] != NULL){
        return PlayerTurn::two;
    }
}

int Board::getResourceCount(PlayerTurn whos){

    int out = 0;
    if(whos == PlayerTurn::one){
        // +1 tile
        if(P1_heros[4] != NULL) out++;
        if(P1_heros[10] != NULL) out++;
        if(P1_heros[13] != NULL) out++;
        if(P1_heros[16] != NULL) out++;
        if(P1_heros[30] != NULL) out++;
        if(P1_heros[33] != NULL) out++;
        if(P1_heros[36] != NULL) out++;
        if(P1_heros[42] != NULL) out++;

        // +2 tile
        if(P1_heros[20] != NULL) out +=2;
        if(P1_heros[26] != NULL) out +=2;

        qDebug() << "\nResource Bonus: Player One Will Gain" << out << "Extra Gold!";

    }else if(whos == PlayerTurn::two){
        // +1 tile
        if(P2_heros[4] != NULL) out++;
        if(P2_heros[10] != NULL) out++;
        if(P2_heros[13] != NULL) out++;
        if(P2_heros[16] != NULL) out++;
        if(P2_heros[30] != NULL) out++;
        if(P2_heros[33] != NULL) out++;
        if(P2_heros[36] != NULL) out++;
        if(P2_heros[42] != NULL) out++;

        // +2 tile
        if(P2_heros[20] != NULL) out +=2;
        if(P2_heros[26] != NULL) out +=2;

        qDebug() << "\nResource Bonus: Player Two Will Gain" << out << "Extra Gold!";


    }
    return out;
}
void Board::makeTileColumn(int x, int y, int row)
{
    double yOffset;
    for(int i = 0; i < row;i++){
        Tile* temp = new Tile();
        yOffset = temp->SCALE_BY * (2 * temp->sideOffset) + 1;
        temp->setPos(x,y+yOffset*i);
        boardContainer.append(temp);
        game->scene_->addItem(temp);

    }
}
