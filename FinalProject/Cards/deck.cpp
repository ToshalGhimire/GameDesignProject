#include "deck.h"
#include <fstream>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <ctime>        // std::time


/**
 * @brief Deck::Deck gets data from CSV file then Stores it in a Container, is a Factory for Card
 */
Deck::Deck()
{
    std::srand(unsigned(std::time(0)));

    QString myResourceFile = ":/card/CardsFile.csv";
    QFile file(myResourceFile);


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error file not opened properly";


    QString Attributes = file.readLine();

    CardData temp;
    while(!file.atEnd()){
        QString line = file.readLine();

        temp.name = line.split(',')[0];
        temp.manaCost = line.split(',')[1].toInt();
        temp.power = line.split(',')[2].toInt();
        temp.movement = line.split(',')[3].toInt();
        temp.range = line.split(',')[4].toInt();
        temp.description = line.split(',')[5];

        Card * TempCard = new Card(temp);
        deck_.push_back(TempCard);
    }

    std::random_shuffle(deck_.begin(),deck_.end()); //suffleing deck
}

/**
 * @brief Deck::Shuffles the deck using std::random_shuffle
 */
void Deck::Shuffle()
{
    std::random_shuffle(deck_.begin(),deck_.end());
}

/**
 * @brief takes the first card out from the deck and returns it
 * @return
 */
Card * Deck::Draw()
{
    if(deck_.size() == 0){
        return NULL;
    }
    Card * out;
    out = deck_.takeFirst();
    return out;
}
