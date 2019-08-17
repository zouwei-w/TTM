#ifndef TABLE_H
#define TABLE_H
#include <QtGui>
#include <QTableWidget>
#include <QStyledItemDelegate>
#include "common.h"

class Table : public QTableWidget
{
    Q_OBJECT

public:
    Table(QWidget *parent = 0);
    ~Table();
    void setColumnValue(const int &columnSum, const QStringList &header);   //set header value
    void setHeaderWidth(const int &index, const int &width);    //set header and column widhth for each index
    void setHeaderHeight(const int &height);                    //set header height
    void addRowValue(const int &height, const QStringList &value); //添加一行值
    void setRowH(const int &index, const int &height);  //设置整个数据域高度
    void setItemFixed(bool flag);
    void clearAllContentsData(int flags); //清除表格数据,flag=0(不清除表头),flag=1(清除表头)
    void setTableWidthAndHeight(const int width, const int height);

    bool getSelectedRow(QList<int> &rowList);

protected:
    void contextMenuEvent(QContextMenuEvent *event);
    QModelIndex moveCursor(CursorAction cursorAction, Qt::KeyboardModifiers modifiers);
    void keyPressEvent(QKeyEvent *event);

private:
    void createActions();

private slots:
    void slotItemEntered(QTableWidgetItem *item);
    void slotActionRename();
    void slotItemSelectionChanged();
    void slotActionFlush();

signals:
    void BORROW_SIG();
    void DEVSEARCH_SIG();
    void LABDYNAMIC_SIG();
    void MEMBERSEARCH_SIG();

private:
    int tableWidth;
    int tableHeight;
    QList<int>rowHeghtList;
    QList<int>rowWidthList;

    QMenu *popMenu;
    QAction *actionName;
    QAction *actionSize;
    QAction *actionType;
    QAction *actionDate;
    QAction *actionOpen;
    QAction *actionDownload;
    QAction *actionFlush;
    QAction *actionDelete;
    QAction *actionRename;
    QAction *actionCreateFolder;
    QTableWidgetItem *rightClickedItem;
    QMap<QTableWidgetItem *, QString>fileMap;
    bool dupFlag;
};

// custom item delegate class
class NoFocusDelegate : public QStyledItemDelegate
{
protected:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};
#endif // TABLE_H
