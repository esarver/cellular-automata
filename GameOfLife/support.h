#ifndef SUPPORT_H
#define SUPPORT_H

enum Factors{
    CELL        = 0b00000001,
    VIRUS       = 0b00000010,
    BACTERIA    = 0b00000100,
    FOOD        = 0b00001000,
    POISON      = 0b00010000,
    TAINTED     = 0b00100000,
    PREDATOR    = 0b01000000
};

enum Directions {
    NORTH   = 0b0001,
    EAST    = 0b0010,
    SOUTH   = 0b0100,
    WEST    = 0b1000
};

typedef struct dna_t {
     unsigned char size; //base size of cell
     unsigned char lifespan; //number of steps that cell can live if not acted upon by a factor.
     unsigned char age_of_reproduction; //number of steps until reproduction is possible
     unsigned char movement_speed; //blocks moved per step
     unsigned char curiosity; //desire to move toward factors
     unsigned char fearfullness; //cower from unknow factors
     unsigned char intelligence; //discern between positive and negative factors.
     unsigned char appearance; //affects whether or not a cell can reproduce with another cell.
     unsigned char tolerance;  //affects what appearance is acceptable to this cell in order to reproduce.
} DNA;

typedef struct behavior_t {
    unsigned char direction; //representation of the directection a cell will tend to go
    unsigned char learned; // shows whether or not a cell knows what something is
    unsigned char opinion; // 1 = good, 0 = bad
} Behavior;

#endif // SUPPORT_H
