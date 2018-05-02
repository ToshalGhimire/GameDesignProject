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

/**
 * @brief Board::MakeBoard makes the game board using MakeTileColumn helper function
 * @param xPos location of board in scene
 * @param yPos location of board in scene
 */
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


/**
 * @brief Board::setSpawnTiles hard codes the spawn tiles for both players in Tile container
 */
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

/**
 * @brief Board::ResourceTiles hard codes the Rescource tiles for the board
 * @param israndom if israncom is true, board randomly sets the values of resource one and two
 */
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


/**
 * @brief Board::SpawnCard takes the card given and turns it into a tile and places it in right spot based on player, and card
 * @param card card object to summon
 * @param T whos turn
 */
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

/**
 * @brief Board::MoveTile handles the logics of moving hero tiles, takes current tile and destination tile
 * @param herotile the tile that needs to move
 * @param PosToPlace the tile location to be placed
 */
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
                qDebug() << "\nTile is Occupied by hero!";
                return;
            }
            SpawnReset();
            herotile->setPos(boardContainer[index_place]->pos());

        }else{
            qDebug() << "\nYou Cannot Move Opponents heroes!";
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
                qDebug() << "\nTile is Occupied by hero!";
                return;

            }
            SpawnReset();
            herotile->setPos(boardContainer[index_place]->pos());

        }else{
            qDebug() << "\nYou Cannot Move Opponents heroes!";
        }
    }

}

/**
 * @brief Board::AttackTile Handles the attack logic for cards given the attacker and their targer
 * @param attacker hero tile that is attacking
 * @param Target target tile that is being attacked, can be hero or spawn
 */
void Board::AttackTile(Tile *attacker, Tile *Target)
{
    if(Target == attacker) return;


    if(attacker->getHasAttacked() == true){
        qDebug() << "\nHero has already attacked!";
        return;
    }


    if(Target->getState() == state::spawn_p1){
        // Attacking player One
        int index = game->GameBoard.boardContainer.indexOf(Target);
        game->MinusPlayerHealth(1,index,attacker->getAttackPower());
        attacker->setAttackedTrue();
        qDebug() << "\nYou attacked Player one!";
        return;
    }

    if(Target->getState() == state::spawn_p2){
        // Attacking player two
        int index = game->GameBoard.boardContainer.indexOf(Target) - 43;
        game->MinusPlayerHealth(2,index,attacker->getAttackPower());
        attacker->setAttackedTrue();
        qDebug() << "\nYou attacked Player two!";
        return;
    }


    if(attacker->getOwner() == tileOwner::one && attacker != NULL){
        if(game->getTurn() == PlayerTurn::one){
           int targetIndex = P2_heros.indexOf(Target);
           int attackerIndex = P1_heros.indexOf(attacker);


           if(attacker->getAttackPower() > Target->getAttackPower()){
               //attacker has More Power

               attacker->setPos(Target->pos());
               P1_heros[targetIndex] = attacker;
               P1_heros[attackerIndex] = NULL;

               game->scene_->removeItem(P2_heros[targetIndex]);
               delete Target;
               P2_heros[targetIndex] = NULL;

               attacker->setAttackedTrue();



           }else if(attacker->getAttackPower() < Target->getAttackPower()){
               // Target has more Power
               game->scene_->removeItem(P1_heros[attackerIndex]);
               P1_heros[attackerIndex] = NULL;

           }else{
               // Equal Power
               game->scene_->removeItem(P1_heros[attackerIndex]);
               game->scene_->removeItem(P2_heros[targetIndex]);

               P1_heros[attackerIndex] = NULL;
               P2_heros[targetIndex] = NULL;

           }


        }else{
            qDebug() << "\nYou Cannot Attack with your Opponents heroes!";

        }
    }else if(attacker->getOwner() == tileOwner::two){
        if(game->getTurn() == PlayerTurn::two){
            int targetIndex = P1_heros.indexOf(Target);
            int attackerIndex = P2_heros.indexOf(attacker);



            if(attacker->getAttackPower() > Target->getAttackPower()){
                //attacker has More Power

                attacker->setPos(Target->pos());
                P2_heros[targetIndex] = attacker;
                P2_heros[attackerIndex] = NULL;

                game->scene_->removeItem(P1_heros[targetIndex]);
                delete Target;
                P1_heros[targetIndex] = NULL;

                attacker->setAttackedTrue();

            }else if(attacker->getAttackPower() < Target->getAttackPower()){
                // Target has more Power
                game->scene_->removeItem(P2_heros[attackerIndex]);
                P2_heros[attackerIndex] = NULL;


            }else{
                // Equal Power
                game->scene_->removeItem(P2_heros[attackerIndex]);
                game->scene_->removeItem(P1_heros[targetIndex]);

                P1_heros[targetIndex] = NULL;
                P2_heros[attackerIndex] = NULL;

            }

        }else{
            qDebug() << "\nYou Cannot Attack with your Opponents heroes!";

        }
    }


}


/**
 * @brief Board::SpawnReset after hero tile leaves spwan, this function resets its tilestate back to Spawn state
 */
void Board::SpawnReset(){
    for(int i = 0; i < 4; i++){
        if(P1_heros[i] == NULL){
            boardContainer[i]->setState(state::spawn_p1);
        }

        if(P2_heros[i+43] == NULL){
            boardContainer[i+43]->setState(state::spawn_p2);
        }
    }
}


/**
 * @brief Board::CapturedCaltapult checks who is in the caltapult tile
 * @return the player who controls the caltapult tile
 */
PlayerTurn Board::CapturedCaltapult(){
    if(P1_heros[23] != NULL){
        return PlayerTurn::one;
    }else if(P2_heros[23] != NULL){
        return PlayerTurn::two;
    }else{
        return PlayerTurn::none;
    }
}

/**
 * @brief Board::getResourceCount calcuates the ammount of extra gold to be given to a player
 * @param whos which player is trying to check
 * @return the ammount of bonus gold
 */
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

/**
 * @brief Board::makeTileColumn makes one column of the board based on paramater
 * @param x location
 * @param y location
 * @param row ammount of tiles to make
 */
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
