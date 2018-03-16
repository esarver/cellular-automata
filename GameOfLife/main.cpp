#include <QtWidgets>
#include <cstdio>

#include "golwindow.h"
#include "cell.h"

/*
 * NOTE: The base of this game was copied from https://github.com/sgelb/gameoflife
 * I did not create this from scratch. Thanks sgelb!
*/

int main(int argc, char *argv[])
{
    qsrand(3029);

    QApplication a(argc, argv);
    GolWindow window;
//    window.show();
//    a.exec();
    Cell test;

    printf("\nDNA Settings:\n");
    printf("\tAoR: %#X\n",test._dna->age_of_reproduction);
    printf("\tLifespan: %#X\n",test._dna->lifespan);
    printf("\tAppearance: %#X\n",test._dna->appearance);
    printf("\tCuriosity: %#X\n",test._dna->curiosity);
    printf("\tFearfullness: %#X\n",test._dna->fearfullness);
    printf("\tIntelligence: %#X\n",test._dna->intelligence);
    printf("\tMovement: %#X\n",test._dna->movement_speed);
    printf("\tSize: %#X\n",test._dna->size);
    printf("\tTolerance: %d\n",test._dna->tolerance);

    printf("\nBehavior Settings:\n");
    printf("\tLearned:\n");
    printf("\t\tBacteria: %#X\n", test._behavior->learned.bacteria);
    printf("\t\tCell: %#X\n", test._behavior->learned.cell);
    printf("\t\tFood: %#X\n", test._behavior->learned.food);
    printf("\t\tPoison: %#X\n", test._behavior->learned.poison);
    printf("\t\tPredator: %#X\n", test._behavior->learned.predator);
    printf("\t\tTainted: %#X\n", test._behavior->learned.tainted);
    printf("\t\tVirus: %#X\n", test._behavior->learned.virus);

    printf("\n\tOpinion:\n");
    printf("\t\tBacteria: %#X\n", test._behavior->opinion.bacteria);
    printf("\t\tCell: %#X\n", test._behavior->opinion.cell);
    printf("\t\tFood: %#X\n", test._behavior->opinion.food);
    printf("\t\tPoison: %#X\n", test._behavior->opinion.poison);
    printf("\t\tPredator: %#X\n", test._behavior->opinion.predator);
    printf("\t\tTainted: %#X\n", test._behavior->opinion.tainted);
    printf("\t\tVirus: %#X\n", test._behavior->opinion.virus);

    printf("\n\tPossible Directions:\n");
    printf("\t\tNorth: %#X\n", test._behavior->possible_direction.north);
    printf("\t\tEast: %#X\n", test._behavior->possible_direction.east);
    printf("\t\tSouth: %#X\n", test._behavior->possible_direction.south);
    printf("\t\tWest: %#X\n", test._behavior->possible_direction.west);

    printf("\n\tPreferred Directions:\n");
    printf("\t\tNorth: %#X\n", test._behavior->preferred_direction.north);
    printf("\t\tEast: %#X\n", test._behavior->preferred_direction.east);
    printf("\t\tSouth: %#X\n", test._behavior->preferred_direction.south);
    printf("\t\tWest: %#X\n", test._behavior->preferred_direction.west);




    return 0;
}
