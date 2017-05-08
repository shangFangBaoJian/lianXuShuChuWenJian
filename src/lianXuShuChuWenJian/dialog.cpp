#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <sys/time.h>
#include <unistd.h>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    connect(ui->openFile,SIGNAL(clicked(bool)),SLOT(onOpenFile()));
    connect(ui->writeData,SIGNAL(clicked(bool)),SLOT(onWriteData()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::open(QString fileName)
{
    file.setFileName(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    if(!file.isOpen())
    {
        qDebug() << "打开日志失败";
    }
}

void Dialog::log2(QString message)
{
    open("log2.text");
    QTextStream stream(&file);
    stream << message << "\r\n";
    file.close();
}

void Dialog::log1(QString message)
{
    QTextStream stream(&file);
    stream << message << "\r\n";
}

void Dialog::onOpenFile()
{
    struct timeval tv,te;
    qDebug() << "开始写入文件log1";
    gettimeofday(&tv,NULL);
    open("log1.text");
    for(int i = 0;i < 10000000;i++)
    {
        log1("0");
    }
    file.close();
    gettimeofday(&te,NULL);
    float time = (1000000*(te.tv_sec-tv.tv_sec)  +
            te.tv_usec - tv.tv_usec)/1000000.0;
    qDebug() << "打开一次文件发送所用的时间为：" << time;
    qDebug() << "te.tv_usec:" << 1000000*te.tv_sec+te.tv_usec;
    qDebug() << "tv.tv_usec:" << 1000000*tv.tv_sec+tv.tv_usec;
}

void Dialog::onWriteData()
{
    struct timeval tv,te;
    qDebug() << "开始写入文件log2";
    gettimeofday(&tv,NULL);
    for(int i = 0;i < 10000000;i++)
    {
        log2("0");
    }
    gettimeofday(&te,NULL);
    float time = (1000000*(te.tv_sec-tv.tv_sec)  +
            te.tv_usec - tv.tv_usec)/1000000.0;
    qDebug() << "频繁打开文件发送所用的时间为：" << time;
    qDebug() << "te.tv_usec:" << 1000000*te.tv_sec+te.tv_usec;
    qDebug() << "tv.tv_usec:" << 1000000*tv.tv_sec+tv.tv_usec;
}


