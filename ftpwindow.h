#ifndef FTPWINDOW_H
#define FTPWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QHash>
#include <QNetworkConfigurationManager>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFile;
class QFtp;
class QLabel;
class QLineEdit;
class QTreeWidget;
class QTreeWidgetItem;
class QProgressDialog;
class QPushButton;
class QUrlInfo;
class QNetworkSession;
QT_END_NAMESPACE

namespace Ui {
class ftpwindow;
}

class ftpwindow : public QDialog
{
    Q_OBJECT

public:
    explicit ftpwindow(QWidget *parent = nullptr);
    ~ftpwindow();
    QSize sizeHint() const;

private slots:
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

    QLabel *ftpServerLabel;
    QLineEdit *ftpServerLineEdit;
    QLabel *statusLabel;
    QTreeWidget *fileList;
    QPushButton *cdToParentButton;
    QPushButton *connectButton;
    QPushButton *downloadButton;
    QPushButton *quitButton;

    QHash<QString, bool> isDirectory;
    QString currentPath;
    QFtp *ftp;
    QFile *file;

    QNetworkSession *networkSession;
    QNetworkConfigurationManager manager;

    Ui::ftpwindow *ui;

};

#endif // FTPWINDOW_H
