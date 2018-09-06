#include "outtext.h"
#include <QHBoxLayout>
OutText::OutText(QWidget *parent) : QWidget(parent)
{
    textEdit=new QTextEdit(this);
    QHBoxLayout * layout=new QHBoxLayout(this);
    layout->addWidget(textEdit);

}

OutText::~OutText()
{

}

