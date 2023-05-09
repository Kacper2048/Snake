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

    //design part of code
    //QPixmap bkgnd("C:/Users/spaj/Desktop/back.jpg");
    //ui->restartButton->setStyleSheet("background-color: yellow");
    ui->restartButton->setStyleSheet(//"color: qlineargradient(spread:pad, x1:0 y1:0, x2:1 y2:0, stop:0 salmon, stop:1 rgba(255, 255, 255, 255));"
                                     "color: rgba(246, 208, 156, 255);"
                                     "background: qlineargradient( x1:0 y1:0, x2:1 y2:0, stop:0 rgba(78, 190, 204,255), stop:1 rgba(144, 102, 240, 255));"
                                     "border-radius: 15px;"
                                     "font-family: Calibri; font-size: 25px;"
                                     "font-weight: 900;"

                                     ); // set the stylesheet


    ui->graphicsView->setStyleSheet("background: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 rgba(177, 227, 62, 255), stop:1 rgba(227, 186, 62, 255));"
                                    "border-radius: 25px;"
                                    "font-weight: 800;"

                                    ); // set the stylesheet

    //ui->label->setStyleSheet("QLabel { background: rgba(0,0,0,0); color: rgba(246, 210, 210, 255); font-size: 15px; font-weight: 800;}"); // set the stylesheet
    qApp->setStyleSheet("QLabel{background-color: yellow; color: rgba(14, 63, 92, 255); font-size: 15px; font-weight: 800;}");
    ui->label->setStyleSheet("QLabel { background: rgba(0,0,0,0);}");
    ui->label_2->setStyleSheet("QLabel { background: rgba(0,0,0,0);}");
    ui->label_3->setStyleSheet("QLabel { background: rgba(0,0,0,0);}");
    ui->foodPoints->setStyleSheet("QLabel { background: rgba(0,0,0,0);}");
    ui->timePoints->setStyleSheet("QLabel { background: rgba(0,0,0,0);}");
    ui->totalPoints->setStyleSheet("QLabel { background: rgba(0,0,0,0);}");
    ui->game_over->setStyleSheet("QLabel { background: rgba(0,0,0,0);font-size: 25px; color: rgba(31, 13, 70, 255);}");

    //--HERE MY FRIEND--
    ui->centralwidget->setStyleSheet("background-image:url(\"C:/Users/spaj/Desktop/snake/images/back.jpg\"); background-position: center; ");
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
