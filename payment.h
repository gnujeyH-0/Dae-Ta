#ifndef PAYMENT_H
#define PAYMENT_H

#include <QWidget>

namespace Ui {
class payment;
}

class payment : public QWidget
{
    Q_OBJECT

public:
    explicit payment(QWidget *parent = nullptr);
    ~payment();

    void updateSum();

    int m_listCount;

public slots:
    void addGetItem(int,int);
    void deleteItem(int,int);


private:
    Ui::payment *ui;
};

#endif // PAYMENT_H
