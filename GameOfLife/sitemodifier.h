#ifndef SITEMODIFIER_H
#define SITEMODIFIER_H

#include <QObject>
#include "support.h"

class SiteModifier : public QObject
{
    Q_OBJECT
public:
    explicit SiteModifier(QObject *parent = nullptr);

signals:

public slots:

private:
    ModifierType type_;
};

#endif // SITEMODIFIER_H
