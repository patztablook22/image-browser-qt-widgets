#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QScrollBar>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOpen_triggered();

    void on_actionExit_triggered();

    void on_actionScreenshot_triggered();

    void on_horizontalSlider_valueChanged(int value);

protected:
    bool eventFilter(QObject*, QEvent*);

private:
    Ui::MainWindow *ui;
    QPixmap qpx;
    QGraphicsPixmapItem* qpi = nullptr;
    QGraphicsScene* scene;
    void loadFiles(const QStringList&);
    void loadFile(const QString&);
    void cycleFiles(int);
    void setScale(float);
    void render();
    float scale = 1;
    QStringList files;
    int whichFile = 0;
};
#endif // MAINWINDOW_H
