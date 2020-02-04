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
    //mozna zmienic nazwe podwojnym klikiem
   // dirmodel->setReadOnly(false);
    dirmodel->setReadOnly(true);

    dirmodel2 = new QFileSystemModel(this);
    dirmodel2->setRootPath(sPath);
    dirmodel2->setFilter(QDir::Dirs);
    dirmodel2->setReadOnly(false);

    ui->treeView->setModel(dirmodel);
    ui->treeView_2->setModel(dirmodel);

    ui->treeView->hideColumn(1);
    ui->treeView->hideColumn(2);
    ui->treeView->hideColumn(3);

    ui->treeView_2->hideColumn(1);
    ui->treeView_2->hideColumn(2);
    ui->treeView_2->hideColumn(3);

    ui->treeView->setSortingEnabled(true);

    filemodel=new QFileSystemModel(this);
    filemodel->setFilter(QDir::Files);
    filemodel->setRootPath(sPath);

    filemodel2=new QFileSystemModel(this);
    filemodel2->setFilter(QDir::Files);
    filemodel2->setRootPath(sPath);

   connect(ui->treeView,&QTreeView::clicked,this,&MainWindow::cdFolder);
    ui->listView->setModel(filemodel);

    ui->listView_2->setModel(filemodel2);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::cdFolder(const QModelIndex &index)
{
    QString sPath = dirmodel->fileInfo(index).canonicalFilePath();
    sciezkazycia=sPath;
    ui->listView->setRootIndex(filemodel->setRootPath(sPath));
    ui->textEdit->setText(sciezkazycia);
}

void MainWindow::on_pushButton_clicked()
{
    QModelIndex index=ui->treeView->currentIndex();
    if(!index.isValid())return;
    QString name = QInputDialog::getText(this,"Name","enter name folder");
    if(name.isEmpty())return;
    dirmodel->mkdir(index,name);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->setText(sciezkazycia);
  //  QModelIndex temp=ui->treeView->currentIndex();

    ui->textEdit_2->setText(temp1);
//    ui->textEdit_2->setText(temp.data(Qt::DisplayRole).toString());
    ui->textEdit_3->setText(sciezkazycia2);
}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    temp1=filemodel->fileInfo(index).canonicalFilePath();
    ui->textEdit_2->setText(temp1);
    nameFile=filemodel->fileInfo(index).fileName();
}
//zmienic na inny model bo sie zepsuje

void MainWindow::on_treeView_2_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel2->fileInfo(index).canonicalFilePath();
    sciezkazycia2=sPath;
    ui->listView_2->setRootIndex(filemodel2->setRootPath(sPath));
    ui->textEdit_3->setText(sciezkazycia2);
}

void MainWindow::on_copyButton_clicked()
{
    QString destinationFile=sciezkazycia2+"/"+nameFile;
    if (QFile::exists(destinationFile))
    {
        QMessageBox::warning(this,"error","this file exist in another directory");
        QFile::remove(destinationFile);
    }

    if(!QFile::copy(temp1, destinationFile)){
     QMessageBox::warning(this,"error","file not copy");
    }
}

void MainWindow::on_listView_2_clicked(const QModelIndex &index)
{
    temp2=filemodel->fileInfo(index).canonicalFilePath();
    ui->textEdit_4->setText(temp2);
    nameFile=filemodel->fileInfo(index).fileName();
}


void MainWindow::on_pushButton_3_clicked()
{

}
