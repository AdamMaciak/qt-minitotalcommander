#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QInputDialog>
#include <QFtp>
#include <QFile>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:

    void cdFolder(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_listView_clicked(const QModelIndex &index);

    void on_treeView_2_clicked(const QModelIndex &index);

    void on_listView_2_clicked(const QModelIndex &index);

    void on_copyButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *dirmodel2;
    QFileSystemModel *filemodel;
    QFileSystemModel *filemodel2;
    QString sciezkazycia;
    QString sciezkazycia2;
    QString temp1,temp2;
    QString nameFile;

};
#endif // MAINWINDOW_H
