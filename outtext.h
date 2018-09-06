#ifndef OUTTEXT_H
#define OUTTEXT_H

#include <QWidget>
#include <QTextEdit>
#include <QTextDocument>

class OutText : public QWidget
{
    Q_OBJECT
public:
    explicit OutText(QWidget *parent = 0);
    ~OutText();
    QTextEdit* textEdit;
signals:

public slots:
};

#endif // OUTTEXT_H
