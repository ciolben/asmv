#ifndef TIMELINE_H
#define TIMELINE_H

#include <QWidget>
#include <QtQuick/QQuickView>
#include <QQuickPaintedItem>
#include <QPainter>
#include <QQuickItem>

#include <timelineQML/splinedrawer.h>

namespace Ui {
class Timeline;
}

class Timeline : public QWidget
{
    Q_OBJECT

public:
    explicit Timeline(QWidget *parent = 0);
    ~Timeline();

     QQuickItem* thisQML;

protected:
    void resizeEvent(QResizeEvent *event);

public slots:

signals:
    void setDimensions();

private:
    Ui::Timeline *ui;
};

#endif // TIMELINE_H
