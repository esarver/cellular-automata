#ifndef SUPPORT_H
#define SUPPORT_H

enum ModifierType{
    FOOD,
    POISON,
    TAINTED_FOOD
};

typedef struct direction_t {
    unsigned char north : 1;
    unsigned char east : 1;
    unsigned char south : 1;
    unsigned char west : 1;
} Direction;

typedef struct factors_t { //8-bits
     unsigned char cell : 1;
     unsigned char virus : 1;
     unsigned char bacteria : 1;
     unsigned char food : 1;
     unsigned char poison : 1;
     unsigned char tainted : 1;
     unsigned char predator : 1;
     unsigned char :0;
} Factor_Knowledge;

typedef struct dna_t { //64-bits
     unsigned char size: 4; //base size of cell (4-bits)
     unsigned char movement_speed: 4; //blocks moved per step
     unsigned char lifespan; //number of steps that cell can live if not acted upon by a factor.
     unsigned char age_of_reproduction; //number of steps until reproduction is possible
     unsigned char curiosity; //desire to move toward factors
     unsigned char fearfullness; //cower from unknow factors
     unsigned char intelligence; //discern between positive and negative factors.
     unsigned char appearance; //affects whether or not a cell can reproduce with another cell.
     unsigned char tolerance;  //affects what appearance is acceptable to this cell in order to reproduce.
} DNA;

typedef struct behavior_t { //32-bits
    Direction possible_direction; //representation of the directection a cell can go
    Direction preferred_direction; //representation of the direction a cell will tend to go
    Factor_Knowledge learned; // shows whether or not a cell knows what something is
    Factor_Knowledge opinion; // 1 = good, 0 = bad
} Behavior;

#endif // SUPPORT_H
