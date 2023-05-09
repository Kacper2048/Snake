#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new Draw(680,680);

    // Set the widget focus policy to accept keyboard events
    setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    gametime = new QTimer(this);

    // connect the timeout() signal of the timer to a slot
    connect(timer, SIGNAL(timeout()), this, SLOT(watch()));
    connect(gametime, SIGNAL(timeout()), this, SLOT(addSecond()));
    timer->start(400);
    gametime->start(1000);

    ui->graphicsView->setScene(game->getScene());
    ui->graphicsView->update();

}

void MainWindow::watch()
{
     autoMove();
}

void MainWindow::addSecond()
{
    if(game->getState())
    {
        game->incrementTime();
        ui->timePoints->setText(QString::number( game->getTime()));
        ui->foodPoints->setText(QString::number( game->getFood()));
        ui->totalPoints->setText(QString::number( game->calcPoints()));
    }
    else
    {
        ui->timePoints->setText(QString::number( game->getTime()));
        ui->foodPoints->setText(QString::number( game->getFood()));
        ui->totalPoints->setText(QString::number( game->calcPoints()));

        ui->game_over->setText(QString("GAME OVER"));
        timer->stop();
        gametime->stop();
    }
}


void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(game->getState() == true)
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

        game->autoMove();
        ui->graphicsView->update();

        //restart clock
        timer->stop();
        timer->start(400);
    }

    // Call the base class implementation to handle other events
    QWidget::keyReleaseEvent(event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_restartButton_clicked()
{
    ui->game_over->setText(QString(""));
    game->restart();
    timer->start(400);
    gametime->start(1000);
}

