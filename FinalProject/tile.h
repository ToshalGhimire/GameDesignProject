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

    void SwapStates(Tile &t);
    void setState(state s);
    state getState(){return TileState_;}
    CardData * getData(){return data_;}
    tileOwner getOwner(){return owner_;}

    void SetColor();

    void MakeHero(CardData * data, tileOwner who);

    bool distanceCalcuate(Tile * current,Tile * dest);

    bool getHasMoved(){return hasMoved;}
    void setMovedFalse(){hasMoved = false;}
    void setMovedTrue(){hasMoved = true;}


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void test();

private:
    state TileState_;
    Button * moveButton_ = new Button(QString("Move"));
    static Tile* ShiftClickedPos_;

    tileOwner owner_ = tileOwner::none;
    CardData* data_;
    int cardMovement_;
    int cardPower_;
    int cardRange_;
    QString cardName_;
    bool hasMoved = false;

};

#endif // TILE_H
