#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include "thread.h"
#include "payment.h"
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include "socket.h"

enum Location {MOVING=-1,HOME, TABLE1,TABLE2,TABLE3,TABLE4,TABLE5,INTERRUPTED}; // 0:home -1:moving n:tableN
class LocationXY {
    public:
        int x;
        int y;
};

///////////////////


namespace Ui {
class Home;
}

class Home : public QMainWindow
{

    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();
    QMediaPlayer* m_Media;
    QTimer* inputTimer;
unsigned char getOneByteValueOfExe(int chan);
void updateLocation();
    
public slots:
//    void stateListener();
    void addTable(int);
    void addTable1();
    void addTable2();
    void addTable3();
    void addTable4();
    void addTable5();
//    void movingStart();
//    void addTable6();
    void btnOrderOrServeClicked();
    void goToBellTable();
    void openPayment();
    void interruptMoving();

    void servingStart();
    int goToTable(Location);
    //void updateLocation();
    void addBellTable(int);
    void openHomeAgain();

signals:
    void stateLocationChanged();
    void restart();
    void goToBellTableSignal();
//    void movingStart();

private:
    Ui::Home *ui;
    Thread *t;
    payment *p;
    socket *s;
};

#endif // HOME_H
