#ifndef GRIDSITE_H
#define GRIDSITE_H

#include <QObject>
#include "cell.h"

class GridSite : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief GridSite
     * @param parent
     */
    explicit GridSite(QObject *parent = nullptr);


signals:
    /**
     * @brief Inform the connected slots that this GridSite has changed.
     * @param gs - pointer to this GridSite
     */
    void changed(GridSite *gs);

public slots:
    /**
     * @brief addCell: adds a new cell to this gridsite.
     * @param new_cell
     */
    void addCell(Cell * new_cell);

private:
    Cell *cell_;
    QVector<SiteModifier> modifier_;
};

#endif // GRIDSITE_H
