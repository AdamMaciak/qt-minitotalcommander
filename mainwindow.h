#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QModelIndex>
#include <QInputDialog>
#include <QFile>
#include <QMessageBox>
#include <ftpwindow.h>
#include <QFtp>
#include <QNetworkSession>
#include <QSettings>

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

    void on_ftpButton_clicked();

    void on_createFolderButton_clicked();

    void on_renameButton_clicked();

    void on_deleteButton_clicked();

  //FTP//

    void on_connectFtp_clicked();

    void on_importftp_clicked();

    void on_downloadftp_clicked();

    /*/////////////////////*/


    void connectOrDisconnect();
    void downloadFile();
    void connectToFtp();
    void ftpCommandFinished(int commandId, bool error);
    void addToList(const QUrlInfo &urlInfo);
    void processItem(QTreeWidgetItem *item, int column);
    void cdToParent();
    void enableDownloadButton();
    void enableConnectButton();


private:

    bool isConnected;

    QHash<QString, bool> isDirectory;
    QString currentPath;
    QFtp *ftp;
    QFile *file;

    QNetworkSession *networkSession;
    QNetworkConfigurationManager manager;


    Ui::MainWindow *ui;
    QFileSystemModel *dirmodel;
    QFileSystemModel *dirmodel2;
    QFileSystemModel *filemodel;
    QFileSystemModel *filemodel2;
    QString sciezkazycia;
    QString sciezkazycia2;
    QString temp1,temp2;
    QString nameFile,nameFile2;
    ftpwindow ftpWin;
    QMessageBox msgBox;
    QAbstractButton* pButtonYes;
    QAbstractButton* pButtonNo;

};
#endif // MAINWINDOW_H
