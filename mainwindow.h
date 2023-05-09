

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include "draw_all.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void autoMove(){game->autoMove();}
    void watch();
    void on_restartButton_clicked();
    void addSecond();

signals:
  void updateMap();

private:
    Ui::MainWindow *ui = nullptr;
    Draw * game = nullptr;
    QTimer* timer = nullptr;
    QTimer* gametime = nullptr;
    int time = 0;


};

