#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include "gridsite.h"

class World : public QObject
{
    Q_OBJECT
public:
   static World * GetInstance();

   void ClearInstance();

signals:
   void changeLabel(QString, QString);

    void worldChanged();

public slots:

   void populateWorld();
   
   void updateAliveCounter();

   void setPopRatio(int ratio);

   void setSize(unsigned int height, unsigned int width);

private:

    void Init();
    explicit World(QObject *parent = nullptr);

    static World * instance_;
    QVector<GridSite *> map_;
    int height_, width_;
    int popRatio_;
    int iteration_;
};

#endif // WORLD_H
