#ifndef TILE_H
#define TILE_H

#include "game.h"
#include "button.h"
#include <QObject>

#include <QGraphicsPolygonItem>

enum class state {empty,spawn_p1,spawn_p2,hero,resource_one,resource_two,caltaput,shop};
enum class tileOwner {none, one, two};

struct CardData;

class Tile : public QObject, public QGraphicsPolygonItem
{
    Q_OBJECT
public:
    Tile(QGraphicsItem* parent = NULL);

    int SCALE_BY = 50;//scale
    double sideOffset = 0.70710678118;//hexagon side offset

    // Getters/Setters
    void SwapStates(Tile &t);
    void setState(state s);
    state getState(){return TileState_;}
    CardData * getData(){return data_;}
    tileOwner getOwner(){return owner_;}
    int getAttackPower(){return cardPower_;}
    int getMovement(){return cardMovement_;}
    int getRange() {return cardRange_;}
    bool getHasMoved(){return hasMoved;}
    void setMovedFalse(){hasMoved = false;}
    void setMovedTrue(){hasMoved = true;}
    bool getHasAttacked(){return hasAttacked;}
    void setAttackedFalse(){hasAttacked = false;}
    void setAttackedTrue(){hasAttacked = true;}
    static Tile * GetLeftClickedItem() {return leftClickedHeroTile_;}
    void SetColor(); // Acts like paint function


    // Hero Specific Functions
    void MakeHero(CardData * data, tileOwner who);
    bool distanceCalcuate(Tile * current,Tile * dest,bool attack = false);
    void removePrevButtons();
    static void clearClickedItems();
    static void RemoveButtons();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void Move();
    void Attack();

private:
    state TileState_;

    static Button * prevMoveButton_;
    static Button * prevAttackButton_;

    static Tile* rightClickedTile_;
    static Tile* leftClickedHeroTile_;

    // Hero specific data
    tileOwner owner_ = tileOwner::none;
    CardData* data_;
    int cardRange_ = -1;
    int cardMovement_ = -1;
    int cardPower_ = -1;
    QString cardName_;
    bool hasMoved = false;
    bool hasAttacked = false;

};

#endif // TILE_H
