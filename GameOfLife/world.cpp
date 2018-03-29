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
    map_ = QVector<GridSite*>();
}

void World::updateAliveCounter(){
    long aliveCellCount = 0;
    qDebug("Number Map Elements: %d", map_.count());
    foreach(GridSite * site, map_){
        if(site->isCell()){
            ++aliveCellCount;
        }
    }
    
    emit changeLabel("aliveCellsLabel", tr("Alive cells: %1").arg(aliveCellCount));
}

void World::populateWorld(){
    //TODO - modifierRatio
    Init();
    for(int i = 0; i < (width_ * height_); i++){
        GridSite *newSite = new GridSite();
        
        int rnd = qrand() % (101);

        if(rnd < popRatio_){
            newSite->addCell(new Cell());
        }
        map_.append(newSite);
    }
    emit changeLabel("iterationLabel", tr("Iterations: %1").arg(iteration_));
    updateAliveCounter();
}

void World::setPopRatio(int ratio){
    popRatio_ = ratio;
}


void World::setSize(unsigned int height, unsigned int width){
    height_ = height;
    width_ = width;
}
