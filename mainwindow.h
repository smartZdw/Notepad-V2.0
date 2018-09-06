#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMessageBox>
#include <QPushButton>
#include <QFont>
#include <QFontDialog>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QColorDialog>
#include <QWheelEvent>   //滚轮事件 记事本V2.0添加

#include "outtext.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MakeMenu();
    void MakeToolBar();
    void MakeConnect();
    //重写事件过滤虚函数
    bool eventFilter(QObject*,QEvent*);
public slots:
    void AboutSlot();
    void FontSlot();
    void NewSlot();
    void ExitSlot();
    void OpenSlot();
    void SaveSlot();
    void ColorSlot();
private:
    Ui::MainWindow *ui;
    QMenu*   FileMenu;   //文件菜单
    QAction* NewAction;    //新建
    QAction* OpenAction;   //打开
    QAction* SaveAction;   //保存
    QAction* SaveAsAction; //另存为
    QAction* PageSetAction;//页面设置
    QAction* ExitAction;   //退出

    QMenu*   EditMenu;     //编辑菜单
    QAction* CopyAction;   //复制
    QAction* UndoAction;   //撤消
    QAction* PasteAction;  //粘贴

    QMenu*   FormatMenu;   //格式菜单
    QAction* WordWrapAction;//自动换行
    QAction* FontAction;    //字体
    QAction* ColorAction;   //颜色

    QMenu*   HelpMenu;      //帮助菜单
    QAction* AboutAction;   //关于

    QToolBar*  toolBar;

    QPushButton* saveBtn;
    QPushButton* nosaveBtn;
    QPushButton* cancelBtn;
    OutText * poutText;
};

#endif // MAINWINDOW_H
