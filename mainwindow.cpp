#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Draw(500,500);

    // Set the widget focus policy to accept keyboard events
    setFocusPolicy(Qt::StrongFocus);

    //pixmap = new QPixmap("C:/Users/spaj/Desktop/pix.png");
    //pixmapItem = new QGraphicsPixmapItem(*pixmap);
    //QGraphicsPixmapItem * pixmapItem2 = new QGraphicsPixmapItem(*pixmap);
    //pixmap = new QPixmap("C:/Users/spaj/Desktop/lawn.png");
    //lawn = new QGraphicsPixmapItem(*pixmap);

    //QGraphicsScene *scene = new QGraphicsScene;
    ui->graphicsView->setScene(game->getScene());
    game->redraw();






    //QGraphicsRectItem *rectItem = new QGraphicsRectItem(QRectF(0, 0, 50, 50));
    //scene->addItem(rectItem);

    //ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    //ui->graphicsView->setBackgroundBrush(QColor(240, 240, 240));
    //ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    //ui->graphicsView->setInteractive(true);
    //ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //ui->graphicsView->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case  Qt::Key_S: {game->updateDir(0);
        qDebug() << "Return S key released!";} break;
        case  Qt::Key_A: {game->updateDir(1);
        qDebug() << "Return A key released!";} break;
        case  Qt::Key_W: {game->updateDir(2);
        qDebug() << "Return W key released!";} break;
        case  Qt::Key_D: {game->updateDir(3);
        qDebug() << "Return D key released!";} break;
        default: {}
    }

    // Call the base class implementation to handle other events
    QWidget::keyReleaseEvent(event);
    game->redraw();
    ui->graphicsView->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

