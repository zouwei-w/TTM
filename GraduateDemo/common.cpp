#include "common.h"

enum_widget CURRENT_WIDGET = E_NULL_WIDGET;

void myMessageBox(QString path, QString tile, QString text)
{
    QMessageBox message(QMessageBox::NoIcon, tile, text);
    message.setIconPixmap(QPixmap(path));
    message.exec();
}
