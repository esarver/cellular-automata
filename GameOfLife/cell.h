#ifndef CELL_H
#define CELL_H

#include <QtCore>

#include "support.h"

class Cell: public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructs a new cell with random DNA and Behavior.
     */
    Cell();

    /**
     * @brief Construct a new cell with inherited DNA and Behavior.
     * DNA and behavior are then mutated.
     * @param dna
     * @param behavior
     */
    Cell(DNA dna, Behavior behavior);

    /* TODO
    void checkBehavior(){
        if(_behavior->learned & (unsigned char) Factors::FOOD ){
            //Go toward food?
        }
    }
    */

public slots:

    /**
     * @brief Mutates the DNA and behavior of this cell.
     */
    void Mutate();

    /**
     * @brief Mutates the DNA of this cell using the given function.
     * @param mutateFunction - pointer to function to act upon dna. Must take _dna pointer as argument.
     */
    void Mutate(void* mutateFunction);

    /**
     * @brief Cell decides which way to move this turn.
     */
    void Move(); //TODO - set a mutex.

    /**
     * @brief Does all possible actions for this cell.
     */
    void TakeTurn(); //TODO - set a mutex?



private:
    void GenerateRandomDna();
    void GenerateRandomBehaviors();

    DNA * _dna;
    Behavior * _behavior;

    long _age;
};

#endif // CELL_H
