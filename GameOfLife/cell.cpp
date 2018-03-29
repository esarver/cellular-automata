#include "cell.h"

Cell::Cell()
{
    _dna = new DNA;
    _behavior = new Behavior;
    age_ = 0;
    
    GenerateRandomDna();
    GenerateRandomBehaviors();
}

Cell::Cell(DNA dna, Behavior behavior){
    _dna = &dna;
    _behavior = &behavior;
    age_ = 0;
}

void Cell::GenerateRandomDna(){
    uint64_t rnd = qrand() % (UINT64_MAX);

    DNA *temp_dna = (DNA*)&rnd;
    
    *_dna = *temp_dna; //pointer cast to DNA* from uint64_t
}

void Cell::GenerateRandomBehaviors(){
    uint32_t rnd = qrand() % (UINT32_MAX);

    Behavior *temp_behavior = (Behavior*)&rnd;
    
    *_behavior = *temp_behavior;//pointer cast to Behavior* from uint32_t
}
