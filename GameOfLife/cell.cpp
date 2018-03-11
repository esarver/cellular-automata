#include "cell.h"

Cell::Cell()
{
    GenerateRandomDna();
    GenerateRandomBehaviors();
}

Cell::Cell(DNA dna, Behavior behavior){
    _dna = &dna;
    _behavior = &behavior;
    _age = 0;
}

Cell::GenerateRandomDna(){
    _dna->age_of_reproduction = qrand() % UCHAR_MAX;
    _dna->appearance = qrand() % UCHAR_MAX;
    _dna->curiosity = qrand() % UCHAR_MAX;
    _dna->fearfullness = qrand() % UCHAR_MAX;
    _dna->intelligence = qrand() % UCHAR_MAX;
    _dna->lifespan = qrand() % UCHAR_MAX;
    _dna->movement_speed = qrand() % UCHAR_MAX;
    _dna->size = 1; //qrand() % UCHAR_MAX;
    _dna->tolerance = qrand() % UCHAR_MAX;
}

Cell::GenerateRandomBehaviors(){
    _behavior->direction = qrand() % UCHAR_MAX;
    _behavior->learned = qrand() % UCHAR_MAX;
    _behavior->opinion = qrand() % UCHAR_MAX;
}
