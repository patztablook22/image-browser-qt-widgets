#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    QGraphicsView* v = ui->graphicsView;
    v->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    v->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    v->setScene(scene);
    //v->verticalScrollBar()->blockSignals(true);
    //loadFiles({"/home/patz/Keep/Gallerby/Gustave Doré/Divine Comedy 1.png"});
    ui->centralwidget->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFiles(const QStringList &tmp)
{
    if (tmp.size() == 0)
        return;
    files = tmp;
    whichFile = 0;
    loadFile(
        files[whichFile]
    );
}

void MainWindow::loadFile(const QString& filename) {
    qpx.load(filename);
    if (!qpi)
        qpi = scene->addPixmap(qpx);
    else
        qpi->setPixmap(qpx);
    setWindowTitle(filename);
    setScale(1);
}

void MainWindow::cycleFiles(int i)
{
    if (files.size() == 0)
        return;
    whichFile += i;
    whichFile %= files.size();
    if (whichFile < 0)
        whichFile += files.size();
    loadFile(files[whichFile]);
}

void MainWindow::render() {
    if (!qpi)
        return;

    qpi->setScale(scale);
//    scene->setSceneRect(
//                0, 0,
//                qpx.width() * scale,
//                qpx.height() * scale
//    );
//    ui->graphicsView->centerOn(
//                qpi
//    );
}

void MainWindow::on_actionOpen_triggered()
{
    loadFiles(QFileDialog::getOpenFileNames());
}


void MainWindow::on_actionExit_triggered()
{
    close();
}


void MainWindow::setScale(float s) {
    if (s < 0.05)
        scale = 0.05;
    else if (s > 5)
        scale = 5;
    else
        scale = s;
    ui->horizontalSlider->setValue(scale * 100);
    render();
}


void MainWindow::on_actionScreenshot_triggered()
{
    ui->graphicsView->grab().save(
        QFileDialog::getSaveFileName()
    );
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    setScale((float)value / 100);
}

bool MainWindow::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* key = (QKeyEvent *)event;

        switch (key->key()) {
        case Qt::Key_Equal:
            setScale(scale + 0.1);
            break;
        case Qt::Key_Minus:
            setScale(scale - 0.1);
            break;
        case Qt::Key_W:
            cycleFiles(+1);
            break;
        case Qt::Key_B:
            cycleFiles(-1);
            break;
        }

        return true;
    }
    return false;
}

