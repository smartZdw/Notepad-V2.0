#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

QString curr_file_name;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   //this->setFixedSize(640,480)
   resize(900,500);
   this->setWindowTitle("记事本V2.0");
   this->setWindowIcon(QIcon("./res/notepad.ico"));
   poutText=new OutText(this);
   //设置中心部件
   this->setCentralWidget(poutText);
   MakeMenu();
   MakeToolBar();

   //为textEdit添加事件过滤器
   poutText->textEdit->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MakeMenu()
{
   //新建
   NewAction=new QAction(QIcon("./res/new.jpg"),"新建",this);
   NewAction->setShortcut(QString("ctrl+N"));
   NewAction->setStatusTip("新建");
   //打开
   OpenAction=new QAction(QIcon("./res/open.jpg"),"打开",this);
   OpenAction->setShortcut(QString("ctrl+O"));
   OpenAction->setStatusTip("打开");
   //保存
   SaveAction=new QAction(QIcon("./res/save.jpg"),"保存",this);
   SaveAction->setShortcut(QString("ctrl+S"));
   SaveAction->setStatusTip("保存");

   SaveAsAction=new QAction(QIcon("./res/saveas.jpg"),"另存为",this);
   SaveAsAction->setStatusTip("另存为");

   PageSetAction=new QAction(QIcon(""),"页面设置",this);
   ExitAction=new QAction(QIcon("./res/exit.jpg"),"退出",this);
   ExitAction->setShortcut(QString("ctrl+X"));
   ExitAction->setStatusTip("退出");

   FileMenu=menuBar()->addMenu("文件(F)");
   FileMenu->addAction(NewAction);
   FileMenu->addAction(OpenAction);
   FileMenu->addAction(SaveAction);
   FileMenu->addAction(SaveAsAction);
   FileMenu->addAction(PageSetAction);
   FileMenu->addAction(ExitAction);

   CopyAction=new QAction(QIcon(),"复制",this);
   CopyAction->setShortcut(QString("Ctrl+C"));
   CopyAction->setStatusTip("复制");

   UndoAction=new QAction(QIcon(),"撤消",this);
   UndoAction->setShortcut(QString("Ctrl+Z"));
   UndoAction->setStatusTip("撤消");

   PasteAction=new QAction(QIcon(),"粘贴",this);
   PasteAction->setShortcut(QString("Ctrl+V"));
   PasteAction->setStatusTip("粘贴");

   EditMenu=menuBar()->addMenu("编辑(E)");
   EditMenu->addAction(CopyAction);
   EditMenu->addAction(UndoAction);
   EditMenu->addAction(PasteAction);

   WordWrapAction=new QAction("自动换行",this);
   FontAction=new QAction(QIcon("./res/font.png"),"字体",this);
   FontAction->setStatusTip("字体");
   ColorAction=new QAction(QIcon("./res/color.jpg"),"颜色",this);
   ColorAction->setStatusTip("颜色");

   FormatMenu=menuBar()->addMenu("格式(F)");
   FormatMenu->addAction(WordWrapAction);
   FormatMenu->addAction(FontAction);
   FormatMenu->addAction(ColorAction);

   AboutAction=new QAction("关于记事本",this);
   HelpMenu=menuBar()->addMenu("帮助(H)");
   HelpMenu->addAction(AboutAction);


   MakeConnect();
}

void MainWindow::MakeToolBar()
{
    //toolBar=new QToolBar(this);
    toolBar=addToolBar("工具栏");
    toolBar->setMovable(true);
    toolBar->setAllowedAreas(Qt::LeftToolBarArea|Qt::RightToolBarArea);
    toolBar->addAction(NewAction);
    toolBar->addAction(OpenAction);
    toolBar->addAction(SaveAction);
    toolBar->addAction(SaveAsAction);
    toolBar->addAction(ColorAction);
    toolBar->addAction(FontAction);
    toolBar->addAction(ExitAction);
}

void MainWindow::MakeConnect()
{
  connect(AboutAction,SIGNAL(triggered()),this,SLOT(AboutSlot()));    //关于
  connect(FontAction,SIGNAL(triggered()),this,SLOT(FontSlot()));      //字体
  connect(NewAction,SIGNAL(triggered()),this,SLOT(NewSlot()));        //新建
  connect(ExitAction,SIGNAL(triggered()),this,SLOT(ExitSlot()));
  connect(OpenAction,SIGNAL(triggered()),this,SLOT(OpenSlot()));      //打开文件
  connect(SaveAction,SIGNAL(triggered()),this,SLOT(SaveSlot()));
  connect(ColorAction,SIGNAL(triggered()),this,SLOT(ColorSlot()));
}
void MainWindow::FontSlot()
{
    bool ok;
    QFont font=QFontDialog::getFont(&ok,this);
   if(ok)
   {
       poutText->textEdit->setFont(font);
   }
}

void MainWindow::AboutSlot()
{
    QMessageBox::about(this,"copyright","        Copyright©2018-8-23 \n版权归旺旺科技所有  开放于广大旺旺用户");
}

void MainWindow::NewSlot()
{
   //当点击新建时,将textEdit上面的文字全面清空
   //已经测试过，下面两种都可以
   // poutText->textEdit->setText(QString(""));
    if(poutText->textEdit->document()->isModified())
    {
     QMessageBox::StandardButton msgBtn=QMessageBox::information(this,"记事本","是否保存文档？",QMessageBox::Save|QMessageBox::Discard|QMessageBox::Cancel);
   // connect(QMessageBox::Save,SIGNAL(clicked()),this,SLOT(SaveSlot()));
   switch(msgBtn)
   {
     //保存内容后新建文件
      case QMessageBox::Save:
       SaveSlot();
      case QMessageBox::Discard:
      break;
      //不保存文件 直接新建文件
       poutText->textEdit->clear();
      //取消新建文件
      case QMessageBox::Cancel:
      return ;
   }
   }
    poutText->textEdit->clear();
}

void MainWindow::ExitSlot()
{
    QApplication::exit();
}
void MainWindow::OpenSlot()
{
    QString path=QFileDialog::getOpenFileName(
                this,
                "打开",
     "C:\\Users\\Administrator\\Documents",
"文本文档(*.txt);;Cpp文件(*.cpp);;H头文件(*.h);;所有文件(*.*)");
    curr_file_name=path;
       if(!path.isEmpty()){
          QFile file(path);
          if(!file.open(QIODevice::ReadOnly)){
    QMessageBox::critical(this,tr("错误"),tr("不能打开文件"));       //弹出错误对话框
             return;
          }
    QTextStream ins(&file);
    poutText->textEdit->setText(ins.readAll());
    file.close();
}
}

void MainWindow::SaveSlot()
{
if(curr_file_name.isEmpty())
  {
        QString file_name=QFileDialog::getSaveFileName(this,"保存文件","C:\\Users\\Administrator\\Documents","文本文档(*.txt);;Cpp文件(*.cpp);;头文件(*.h);;所有文件(*.*)");
    if(!file_name.isEmpty())  //如果此文件名不为空
    {
        QFile file(file_name);
        if(!file.open(QIODevice::WriteOnly))
        {   //如果不能(只写)打开文件 弹出错误对话框
            QMessageBox::critical(this,"Critical","错误");
            return ;
        }
        QTextStream outs(&file);
        outs<<poutText->textEdit->toPlainText();
        outs.flush();
        file.close();   //关闭文件
    }
  }
  else  //如果curr_file_name不为空
  {
        QFile file(curr_file_name);
        if(file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this,"Critical","出现错误");
            return ;
        }
        QTextStream outs(&file);
        outs<<poutText->textEdit->toPlainText();    //写入文件
        outs.flush();
        file.close();
  }
}

void MainWindow::ColorSlot()
{
    QColor color=QColorDialog::getColor(Qt::white,this,"颜色");
    poutText->textEdit->setTextColor(color);
}


bool MainWindow::eventFilter(QObject *obj,QEvent* event)
{
    //先判断对象是否是textEdit对象
    if(obj==poutText->textEdit)
    {
        if(event->type()==QEvent::Wheel)
        {
            QWheelEvent* w=static_cast<QWheelEvent*> (event);
          //如果滚轮向上滑动
            if(w->delta()>0)
            {
                //放大文本
                poutText->textEdit->zoomIn();
            }
            if(w->delta()<0)
            {
                poutText->textEdit->zoomOut();
            }
            return true;
        }
        return false;
    }
    return MainWindow::eventFilter(obj,event);
}
