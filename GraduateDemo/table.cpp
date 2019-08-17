#include "table.h"
#include <QHeaderView>
#include <QScrollBar>
#include <QMenu>
#include <QMessageBox>
#include <QToolTip>
#include "common.h"

Table::Table(QWidget *parent)
    : QTableWidget(parent)
    , rightClickedItem(NULL)
    , dupFlag(false)
{
    /*############################## 创建及配置一张表 开始 ##############################*/
    rowHeghtList.clear();
    rowWidthList.clear();
    fileMap.clear();
    this->setMouseTracking(true);
    horizontalHeader()->setDefaultSectionSize(100);
    verticalHeader()->setDefaultSectionSize(30);    //设置默认行高
    tableWidth = 100;
    tableHeight = 30;
    horizontalHeader()->setSectionsClickable(false);  //设置表头不可点击（默认点击后进行排序

    QFont font = horizontalHeader()->font();    //设置表头字体加粗
    font.setBold(true);
    horizontalHeader()->setFont(font);
    horizontalHeader()->setStretchLastSection(true);  //设置充满表宽度

    //setFrameShape(QFrame::NoFrame);      //设置无边框
    //setShowGrid(false);                //设置不显示格子线
    //verticalHeader()->setVisible(false); //设置垂直头不可见
    setSelectionMode(QAbstractItemView::ExtendedSelection);  //可多选（Ctrl、Shift、  Ctrl+A都可以）
    setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
    setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑

    setStyleSheet("selection-background-color:lightblue;");  //设置选中背景色
    horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
    //setStyleSheet("background: rgb(56,56,56);alternate-background-color:rgb(48,51,55);selection-background-color:qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgb(56,56,56),stop:1 rgb(76,76,76));"); //设置选中背景色
    //horizontalHeader()->setStyleSheet("QHeaderView::section{background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 rgba(134, 245, 99, 255),stop:0.5 rgba(134, 148, 99, 255),stop:1 rgba(115, 87, 128, 255));color:rgb(25, 70, 100);padding-left: 1px;border: 1px solid #FFFF00;}"); //设置表头背景色
    setAlternatingRowColors(true);

    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置水平、垂直滚动条样式
    horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:12px;}"
                                         "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                         "QScrollBar::handle:hover{background:gray;}"
                                         "QScrollBar::sub-line{background:transparent;}"
                                         "QScrollBar::add-line{background:transparent;}");

    verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width:12px;}"
                                       "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                                       "QScrollBar::handle:hover{background:gray;}"
                                       "QScrollBar::sub-line{background:transparent;}"
                                       "QScrollBar::add-line{background:transparent;}");

    // set the item delegate to your table widget
    setItemDelegate(new NoFocusDelegate());    //虚线边框去除
    //setFocusPolicy(Qt::NoFocus);   //去除选中虚线框
    horizontalHeader()->setHighlightSections(false);    //点击表时不对表头行光亮（获取焦点）

    /*############################## 创建及配置一张表 结束 ##############################*/

    createActions();
    setItemFixed(false);
    connect(this, SIGNAL(itemEntered(QTableWidgetItem*)), this , SLOT(slotItemEntered(QTableWidgetItem*)));
    connect(this, SIGNAL(itemSelectionChanged()), this , SLOT(slotItemSelectionChanged()));
    //this->resize(600, 600);
}

Table::~Table()
{

}

void Table::setColumnValue(const int &columnSum, const QStringList &header)
{
    setColumnCount(columnSum);                //设置列数
    this->setHorizontalHeaderLabels(header);  //设置列的标签
}

//表头的宽度
void Table::setHeaderWidth(const int &index, const int &width)
{
    horizontalHeader()->resizeSection(index,width);
}

//设置表头的高度
void Table::setHeaderHeight(const int &height)
{
    horizontalHeader()->setFixedHeight(height);
}


//添加行
void Table::addRowValue(const int &height, const QStringList &value)
{
    int row_count = rowCount();    //获取表单行数
    insertRow(row_count);          //插入新行
    setRowHeight(row_count, height);//设置新增行的高度
    for (int index = 0; index < columnCount(); index++) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setTextAlignment(Qt::AlignCenter); //文字居中显示
        item->setText(value.at(index));//文字内容
        setItem(row_count, index, item);//插入内容，row_count(行)，index(列)，item(插入对象)
    }
}


void NoFocusDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);
    if (itemOption.state & QStyle::State_HasFocus)
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;
    QStyledItemDelegate::paint(painter, itemOption, index);
}

//设置行高
void Table::setRowH(const int &index, const int &height)
{
  setRowHeight(index, height);
}

void Table::createActions()
{
  popMenu = new QMenu();
  actionName = new QAction(this);
  actionSize = new QAction(this);
  actionType = new QAction(this);
  actionDate = new QAction(this);
  actionOpen = new QAction(this);
  actionDownload = new QAction(this);
  actionFlush = new QAction(this);
  actionDelete = new QAction(this);
  actionRename = new QAction(this);
  actionCreateFolder = new QAction(this);

  actionOpen->setText(tr("打开"));
  actionDownload->setText(tr("下载"));
  actionFlush->setText(tr("刷新"));
  actionDelete->setText(tr("删除"));
  actionRename->setText(tr("重命名"));
  actionCreateFolder->setText(tr("新建文件夹"));
  actionName->setText(tr("名称"));
  actionSize->setText(tr("大小"));
  actionType->setText(tr("项目类型"));
  actionDate->setText(tr("修改日期"));

  actionFlush->setShortcut(QKeySequence::Refresh); //刷新的快捷键
  connect(actionRename, SIGNAL(triggered()), this, SLOT(slotActionRename())); //重命名槽函数
  connect(actionFlush,SIGNAL(triggered()),this,SLOT(slotActionFlush()));//刷新槽函数
}

//内容选项框
void Table::contextMenuEvent(QContextMenuEvent *event)
{
  popMenu->clear();
  QPoint point = event->pos();
  rightClickedItem = this->itemAt(point);
  if(rightClickedItem != NULL) {
    popMenu->addAction(actionDownload);  //下载
    popMenu->addAction(actionFlush); //刷新
    popMenu->addSeparator(); //分界线
    popMenu->addAction(actionDelete); //删除
    popMenu->addAction(actionRename); //重命名
    popMenu->addSeparator(); //分界线
    popMenu->addAction(actionCreateFolder); //新建文件夹
    QMenu *sortStyle = popMenu->addMenu(tr("排序"));
    sortStyle->addAction(actionName); //排序子选项1：名称
    sortStyle->addAction(actionSize); //排序子选项2：大小
    sortStyle->addAction(actionType); //排序子选项3：项目类型
    sortStyle->addAction(actionDate); //排序子选项4：修改日期

    popMenu->exec(QCursor::pos());
    event->accept();
  }
}

QModelIndex Table::moveCursor(QAbstractItemView::CursorAction cursorAction, Qt::KeyboardModifiers modifiers)
{
    //重写移动光标事件，当存在编辑项的时候，让光标永远位于当前项（编辑项）,否则返回父类
    if(rightClickedItem && rightClickedItem->row() >= 0) {
        return currentIndex();
    }
    else {
       return QTableWidget::moveCursor(cursorAction, modifiers);
    }
}

//按键事件
void Table::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QTableWidgetItem *item = currentItem();
        if (item) {
            closePersistentEditor(item);
            openPersistentEditor(item);
            slotItemSelectionChanged();
            dupFlag = false;
        }
    }
}

void Table::slotItemSelectionChanged()
{
    //关闭编辑项
    if (rightClickedItem && dupFlag == false) {
        int editRow = rightClickedItem->row();
        QTableWidgetItem *item = this->item(editRow, 0);
        QMap<QTableWidgetItem *, QString>::iterator it;
        for (it = fileMap.begin(); it != fileMap.end(); ++it) {
            if (it.key() != item) {
                if (it.value() == item->text()) {
                    dupFlag = true;
                }
            }
        }
        if (dupFlag == false) {
            this->closePersistentEditor(item);
            rightClickedItem = NULL;
        }
        else {
            QMessageBox::critical(this,tr("错误提示"),tr("文件重名"), tr("确定"));
            setCurrentItem(item);
        }
    }
    else {
        dupFlag = false;
    }
}

void Table::setItemFixed(bool flag)
{
  if (flag == true)
      horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
  else
      horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
}

//清除表格数据,flag=0(不清除表头),flag=1(清除表头)
void Table::clearAllContentsData(int flags)
{
    if(flags == 1)
    {
        clear();
    }
    else if(flags == 0)
    {
      setRowCount(0);
      clearContents();
    }
}

void Table::setTableWidthAndHeight(const int width, const int height)
{
   resize(width, height); //表的宽高
}


bool Table::getSelectedRow(QList<int> &rowList)
{
    //多选并获取所选行
    QList<QTableWidgetItem *> items = this->selectedItems();
    int itemCount = items.count();
    if(itemCount <= 0) {
        return false;
    }
    for (int index = 0; index < itemCount; index++) {
        int itemRow = this->row(items.at(index));
        rowList.append(itemRow);
    }
    return  true;
}

void Table::slotItemEntered(QTableWidgetItem *item)
{
  if(!item)
    return;
  QString name = item->text();
  if (name.isEmpty())
    return;
  QToolTip::showText(QCursor::pos(), name);
}

//重命名实现
void Table::slotActionRename()
{
    //获得当前节点并获取编辑名称
    if (rightClickedItem) {
        int editRow = rightClickedItem->row();
        QTableWidgetItem *item = this->item(editRow, 0);   //编辑的行号及第一列
        this->setCurrentCell(editRow, 0);
        this->openPersistentEditor(item);                  //打开编辑项
        this->editItem(item);
    }
}

/*********************
 *  E_BOOROW_WIDGET = 2,        //借用查询
    E_DEVSEARCH_WIDGET,         //设备查询
    E_LABENVDYNAMIC_WIDGET,     //实验动态
    E_LABENV_WIDGET,            //实验环境
    E_MEMBERINFO_WIDGET,        //人员查询
    E_MUSIC_WIDGET,             //音乐
    E_REMOTEOPERA_WIDGET        //远程操作
    void BORROW_SIG();
    void DEVSEARCH_SIG();
    void LABDYNAMIC_SIG();
    void MEMBERSEARCH_SIG();
********************/
//刷新实现
void Table::slotActionFlush()
{
    if(CURRENT_WIDGET != E_NULL_WIDGET)
    {
        int row_count = rowCount();    //获取表单行数
        qDebug() << "行数: " + QString::number(row_count);
        clearAllContentsData(0);
    }

    switch(CURRENT_WIDGET)
    {
    case E_BOOROW_WIDGET://借用查询
        qDebug() << "刷新 借用查询";
        emit BORROW_SIG();
        break;

    case E_DEVSEARCH_WIDGET://设备查询
        qDebug() << "刷新 设备查询";
        emit DEVSEARCH_SIG();
        break;

    case E_LABENVDYNAMIC_WIDGET://实验动态
        qDebug() << "刷新 实验动态";
        emit LABDYNAMIC_SIG();
        break;

    case E_MEMBERINFO_WIDGET://人员查询
        qDebug() << "刷新 人员查询";
        emit MEMBERSEARCH_SIG();
        break;

    default:break;
    }
}




