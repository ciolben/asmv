#include "timeline.h"
#include "ui_timeline.h"

#include <timelineQML/splinedrawer.h>

Timeline::Timeline(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Timeline)
{
    qmlRegisterType<SplineDrawer>("Spline", 1, 0, "SplineDrawer");

    ui->setupUi(this);
    QQuickView *view = new QQuickView();
    QWidget *container = QWidget::createWindowContainer(view, this);
    container->setFocusPolicy(Qt::TabFocus);
    view->setSource(QUrl("timelineQML/timeline.qml"));
    ui->gridLayout->addWidget(container);

    QQuickItem* qmlitem = view->rootObject();
    this->thisQML = qmlitem;

}

Timeline::~Timeline()
{
    delete ui;
}

void Timeline::resizeEvent(QResizeEvent *event)
{
    thisQML->setProperty("width", this->width());
    thisQML->setProperty("height", this->height());
}
