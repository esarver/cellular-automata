#include "gridsite.h"
#include <assert.h>

GridSite::GridSite(QObject *parent) : QObject(parent), cell_(nullptr)
{
    modifier_ = QVector<SiteModifier>();
}

void GridSite::addCell(Cell *new_cell){
    cell_ = new_cell;
}

bool GridSite::isCell(){
    if(cell_){
        return true;
    } else {
        return false;
    }
}