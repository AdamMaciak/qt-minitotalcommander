#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString sPath="D:/";
    dirmodel = new QFileSystemModel(this);
    dirmodel->setRootPath(sPath);
    dirmodel->setFilter(QDir::Dirs);
    dirmodel->setReadOnly(false);
    ui->treeView->setModel(dirmodel);

    filemodel=new QFileSystemModel(this);
    filemodel->setFilter(QDir::Files);
    filemodel->setRootPath(sPath);

    ui->listView->setModel(filemodel);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).path();
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
}

void MainWindow::on_pushButton_clicked()
{
    QModelIndex index=ui->treeView->currentIndex();
    if(!index.isValid())return;
    QString name = QInputDialog::getText(this,"Name","enter name folder");

    if(name.isEmpty())return;

    dirmodel->mkdir(index,name);

}
