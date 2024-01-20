#ifndef NAVMODEL_H
#define NAVMODEL_H

#include <QObject>
#include <QQuickItem>

class NavModel : public QObject
{
    Q_OBJECT
public:
    NavModel();

 public slots:

    void itemSelected(QQuickItem * item, QObject * sender);

};

#endif // NAVMODEL_H
