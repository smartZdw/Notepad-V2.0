#include "mainwindow.h"
#include <QApplication>
/*
 *   Project:notepad V1.0
 *   Writer: Smart_Z
 *   Date: 2018-8-23
 *   内容:
 *   1.实现了新建 保存 退出 功能
 *   2.添加了 字体 颜色 图标功能
 *   3.相比微软记事本添加了工具栏功能 可左右停靠
 *   缺陷：
 *   1.新建文件算法不够严谨，没有先提醒用户保存
 *   2.没有实现另存为,页面设置,自动换行功能
 *   以上缺陷后期V2.0会进行部分修复
 *
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
