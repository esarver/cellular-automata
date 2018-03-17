#include "world.h"

World * World::instance_ = nullptr;

World::World(QObject *parent) : QObject(parent)
{
    Init();
}

World * World::GetInstance(){
    if(instance_ == nullptr){
        instance_ = new World();
    }

    return instance_;
}

void World::ClearInstance(){
    Init();
}

void World::Init(){
    iteration_ = 0;
    height_ = 100;
    width_ = 100;
    popRatio_ = 40;
    map_ = QVector<GridSite*>(width_ * height_);
}

void World::populateWorld(){
    //TODO - modifierRatio
    foreach(GridSite *site,  map_){
        int rnd = qrand() % (101);

        if(rnd < popRatio_){
            site->addCell(new Cell());
        }
    }
    emit changeLabel("iterationLabel", tr("Iterations: %1").arg(iteration_));
    emit changeLabel("aliveCellsLabel", tr("Alive cells: %1").arg("NOT IMPLEMENTED"));
}

void World::setPopRatio(int ratio){
    popRatio_ = ratio;
}


void World::setSize(unsigned int height, unsigned int width){
    height_ = height;
    width_ = width;
}
