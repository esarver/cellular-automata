#include "cell.h"

Cell::Cell()
{
    GenerateRandomDna();
    GenerateRandomBehaviors();
}

Cell::Cell(DNA dna, Behavior behavior){
    _dna = &dna;
    _behavior = &behavior;
    age_ = 0;
}

void Cell::GenerateRandomDna(){
    uint64_t temp_dna = qrand() % (UINT64_MAX);

    _dna = (DNA*)&temp_dna; //pointer cast to DNA* from uint64_t
}

void Cell::GenerateRandomBehaviors(){
    uint32_t temp_behavior = qrand() % (UINT32_MAX);

    _behavior = (Behavior*)&temp_behavior;//pointer cast to Behavior* from uint32_t
}
