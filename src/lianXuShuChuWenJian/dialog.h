#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFile>
#include <QTextStream>


namespace Ui {
    class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void open(QString fileName);
    void log1(QString message);
    void log2(QString message);

private slots:
    void onOpenFile();
    void onWriteData();

private:
    Ui::Dialog *ui;
     QFile file;
};

#endif // DIALOG_H
