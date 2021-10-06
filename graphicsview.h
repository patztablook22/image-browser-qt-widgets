#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QObject>
#include <QWidget>

class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView();
};

#endif // GRAPHICSVIEW_H
