#ifndef FORMMUSIC_H
#define FORMMUSIC_H

#include <QWidget>

class MyMessageBox;

namespace Ui {
class Formmusic;
}

class Formmusic : public QWidget
{
    Q_OBJECT

public:
    explicit Formmusic(QWidget *parent = 0);
    ~Formmusic();

private:
    void initForm();

private slots:

private:
    Ui::Formmusic *ui;
};

#endif // FORMMUSIC_H
