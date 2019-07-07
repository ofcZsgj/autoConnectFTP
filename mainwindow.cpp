#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QTextCodec>

FILE * fp = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actiontianjiawenjian_triggered()
{
    QString fileName = QFileDialog::getOpenFileName();
    QTextCodec * codec = QTextCodec::codecForName("GBK");
    char * file = codec->fromUnicode(fileName).data();
    //file = NULL;
    fp = fopen(file,"r");
    if(!fp) {
        ui->label_4->setText(codec->toUnicode("OPEN FILE ERROP!"));//label_4显示中文乱码
        return;
    }
}
