#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isConnected(false)
    , ftp(0)
    , networkSession(0)
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


   // ui->treeFTP->hide();

    filemodel=new QFileSystemModel(this);
    filemodel->setFilter(QDir::Files);
   // filemodel->setFilter(QDir::System);
    filemodel->setRootPath(sPath);

    filemodel2=new QFileSystemModel(this);
    filemodel2->setFilter(QDir::Files);
//    filemodel2->setFilter(QDir::System);
    filemodel2->setRootPath(sPath);

    msgBox.setText(tr("which panel?"));

    msgBox.addButton(tr("First"), QMessageBox::YesRole);
    msgBox.addButton(tr("Second"), QMessageBox::NoRole);

    connect(ui->treeView,&QTreeView::clicked,this,&MainWindow::cdFolder);
    ui->listView->setModel(filemodel);

    ui->listView_2->setModel(filemodel2);

    connect(ui->treeFTP, &QTreeWidget::itemActivated,
            this, &MainWindow::processItem);
    connect(ui->treeFTP, &QTreeWidget::currentItemChanged,
            this, &MainWindow::enableDownloadButton);

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

void MainWindow::on_treeView_2_clicked(const QModelIndex &index)
{
    QString sPath = dirmodel2->fileInfo(index).canonicalFilePath();
    sciezkazycia2=sPath;
    ui->listView_2->setRootIndex(filemodel2->setRootPath(sPath));
    ui->textEdit_3->setText(sciezkazycia2);
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
//    ui->textEdit->setText(sciezkazycia);
  //  QModelIndex temp=ui->treeView->currentIndex();

 //   ui->textEdit_2->setText(temp1);
//    ui->textEdit_2->setText(temp.data(Qt::DisplayRole).toString());
 //   ui->textEdit_3->setText(sciezkazycia2);
    ui->treeView->reset();
   // ui->treeView->

}

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    temp1=filemodel->fileInfo(index).canonicalFilePath();
    ui->textEdit_2->setText(temp1);
    nameFile=filemodel->fileInfo(index).fileName();
}
//zmienic na inny model bo sie zepsuje



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
    temp2=filemodel2->fileInfo(index).canonicalFilePath();
    ui->textEdit_4->setText(temp2);
    nameFile2=filemodel2->fileInfo(index).fileName();
}

void MainWindow::on_ftpButton_clicked()
{
    ftpWin.show();
}

void MainWindow::on_createFolderButton_clicked()
{


    QMessageBox::StandardButton reply;

      reply = QMessageBox::question(this, "where?", "yes first panel, no second panel",
                                    QMessageBox::Yes|QMessageBox::No);

      if (reply == QMessageBox::Yes) {
          QModelIndex index=ui->treeView->currentIndex();
          if(!index.isValid())return;
          QString name = QInputDialog::getText(this,"Name 1","enter name folder");
          if(name.isEmpty())return;
          dirmodel->mkdir(index,name);
      } else if(reply == QMessageBox::No){
          QModelIndex index=ui->treeView_2->currentIndex();
          if(!index.isValid())return;
          QString name = QInputDialog::getText(this,"Name 2","enter name folder");
          if(name.isEmpty())return;
          dirmodel2->mkdir(index,name);
      }

//    if(msgBox.exec()==QMessageBox::YesRole){
//        QModelIndex index=ui->treeView->currentIndex();
//        if(!index.isValid())return;
//        QString name = QInputDialog::getText(this,"Name 1","enter name folder");
//        if(name.isEmpty())return;
//        dirmodel->mkdir(index,name);
//    }
//    else{
//        QModelIndex index=ui->treeView_2->currentIndex();
//        if(!index.isValid())return;
//        QString name = QInputDialog::getText(this,"Name 2","enter name folder");
//        if(name.isEmpty())return;
//        dirmodel2->mkdir(index,name);
//    }
}

void MainWindow::on_renameButton_clicked()
{
//    msgBox.exec();

//    if(msgBox.clickedButton()==pButtonYes){
//        QModelIndex index=ui->treeView->currentIndex();
//        if(!index.isValid())return;
//        QString name = QInputDialog::getText(this,"Name","for what?");
//        if(name.isEmpty())return;

//        dirmodel->mkdir(index,name);

//    }
//    else if (msgBox.clickedButton()==pButtonNo){
//        QModelIndex index=ui->treeView_2->currentIndex();
//        if(!index.isValid())return;
//        QString name = QInputDialog::getText(this,"Name","for what?");
//        if(name.isEmpty())return;
//        dirmodel2->mkdir(index,name);
//    }
}

void MainWindow::on_deleteButton_clicked()
{
    //QString destinationFile=sciezkazycia2+"/"+nameFile2;
    QFile::remove(temp2);
}

void MainWindow::on_connectFtp_clicked()
{
//    connectDisconnect();
//    ui->treeView_2->hide();
//    ui->listView_2->setEnabled(false);
    connectOrDisconnect();
}


void MainWindow::on_importftp_clicked()
{
    ui->treeView_2->show();
    ui->listView_2->setEnabled(true);
}


void MainWindow::on_downloadftp_clicked(){

}

void MainWindow::connectOrDisconnect(){
    if (ftp) {
        ftp->abort();
        ftp->deleteLater();
        ftp = 0;
        ui->treeFTP->setEnabled(false);
        //ui->backButtonFtp->setEnabled(false);
        ui->downloadftp->setEnabled(false);
        ui->connectFtp->setEnabled(true);
        ui->connectFtp->setText(tr("Connect"));
        ui->statusLabel->setText(tr("Please enter the name of an FTP server."));
        return;
    }

    if (!networkSession || !networkSession->isOpen()) {
        if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
            if (!networkSession) {
                // Get saved network configuration
                QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
                settings.beginGroup(QLatin1String("QtNetwork"));
                const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
                settings.endGroup();

                // If the saved network configuration is not currently discovered use the system default
                QNetworkConfiguration config = manager.configurationFromIdentifier(id);
                if ((config.state() & QNetworkConfiguration::Discovered) !=
                    QNetworkConfiguration::Discovered) {
                    config = manager.defaultConfiguration();
                }

                networkSession = new QNetworkSession(config, this);
                connect(networkSession, SIGNAL(opened()), this, SLOT(connectToFtp()));
                connect(networkSession, SIGNAL(error(QNetworkSession::SessionError)), this, SLOT(enableConnectButton()));
            }
            ui->connectFtp->setEnabled(false);
            ui->statusLabel->setText(tr("Opening network session."));
            networkSession->open();
            return;
        }
    }
    connectToFtp();
}
void MainWindow::downloadFile(){
    QString fileName = ui->treeFTP->currentItem()->text(0);

    if (QFile::exists(fileName)) {
        QMessageBox::information(this, tr("FTP"),
                                 tr("There already exists a file called %1 in "
                                    "the current directory.")
                                 .arg(fileName));
        return;
    }


    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("FTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg(fileName).arg(file->errorString()));
        delete file;
        return;
    }

    file = new QFile(QString("D:/%1").arg(fileName));

    ftp->get(ui->treeFTP->currentItem()->text(0), file);

    ui->downloadftp->setEnabled(false);
}

void MainWindow::connectToFtp(){
    ftp = new QFtp(this);
    connect(ftp, SIGNAL(commandFinished(int,bool)),
            this, SLOT(ftpCommandFinished(int,bool)));
    connect(ftp, SIGNAL(listInfo(QUrlInfo)),
            this, SLOT(addToList(QUrlInfo)));
    connect(ftp, SIGNAL(dataTransferProgress(qint64,qint64)),
            this, SLOT(updateDataTransferProgress(qint64,qint64)));

    ui->treeFTP->clear();
    currentPath.clear();
    isDirectory.clear();


    QString user = "ftpuser";
    QString pass = "Ughlk6969";
    //TODO
    QUrl url(ui->adressftp->text());
    if (!url.isValid() || url.scheme().toLower() != QLatin1String("ftp")) {
        ftp->connectToHost(ui->adressftp->text(), 21);
        ftp->login(user,pass);
    } else {
        ftp->connectToHost(url.host(), url.port(21));

        if (!url.userName().isEmpty())
            ftp->login(QUrl::fromPercentEncoding(url.userName().toLatin1()), url.password());
        else
            ftp->login();
        if (!url.path().isEmpty())
            ftp->cd(url.path());
    }

    ui->treeFTP->setEnabled(true);
    ui->connectFtp->setEnabled(false);
    ui->connectFtp->setText(tr("Disconnect"));
    ui->statusLabel->setText(tr("Connecting to FTP server %1...")
                         .arg(ui->adressftp->text()));
}
void MainWindow::ftpCommandFinished(int commandId, bool error){
    if (ftp->currentCommand() == QFtp::ConnectToHost) {
        if (error) {
            QMessageBox::information(this, tr("FTP"),
                                     tr("Unable to connect to the FTP server "
                                        "at %1. Please check that the host "
                                        "name is correct.")
                                     .arg(ui->adressftp->text()));
            connectOrDisconnect();
            return;
        }
        ui->statusLabel->setText(tr("Logged onto %1.")
                             .arg(ui->adressftp->text()));
        ui->treeFTP->setFocus();
        ui->downloadftp->setDefault(true);
        ui->connectFtp->setEnabled(true);
        return;
    }

    if (ftp->currentCommand() == QFtp::Login)
        ftp->list();

    if (ftp->currentCommand() == QFtp::Get) {
        if (error) {
            ui->statusLabel->setText(tr("Canceled download of %1.")
                                 .arg(file->fileName()));
            file->close();
            file->remove();
        } else {
            ui->statusLabel->setText(tr("Downloaded %1 to current directory.")
                                 .arg(file->fileName()));
            file->close();
        }
        delete file;
        enableDownloadButton();

    } else if (ftp->currentCommand() == QFtp::List) {
        if (isDirectory.isEmpty()) {
            ui->treeFTP->addTopLevelItem(new QTreeWidgetItem(QStringList() << tr("<empty>")));
            ui->treeFTP->setEnabled(false);
        }
    }
}
void MainWindow::addToList(const QUrlInfo &urlInfo){
    QTreeWidgetItem *item = new QTreeWidgetItem;
    item->setText(0, urlInfo.name());
    item->setText(1, QString::number(urlInfo.size()));
    item->setText(2, urlInfo.owner());
    item->setText(3, urlInfo.group());
    item->setText(4, urlInfo.lastModified().toString("MMM dd yyyy"));

    QPixmap pixmap(urlInfo.isDir() ? ":/images/dir.png" : ":/images/file.png");
    item->setIcon(0, pixmap);

    isDirectory[urlInfo.name()] = urlInfo.isDir();
    ui->treeFTP->addTopLevelItem(item);
    if (!ui->treeFTP->currentItem()) {
        ui->treeFTP->setCurrentItem(ui->treeFTP->topLevelItem(0));
        ui->treeFTP->setEnabled(true);
    }
}
void MainWindow::processItem(QTreeWidgetItem *item, int column){
    QString name = item->text(0);
    if (isDirectory.value(name)) {
        ui->treeFTP->clear();
        isDirectory.clear();
        currentPath += '/';
        currentPath += name;
        ftp->cd(name);
        ftp->list();
        ui->backButtonFtp->setEnabled(true);
        return;
    }
}
void MainWindow::cdToParent(){
    ui->treeFTP->clear();
    isDirectory.clear();
    currentPath = currentPath.left(currentPath.lastIndexOf('/'));
    if (currentPath.isEmpty()) {
         ui->backButtonFtp->setEnabled(false);
        ftp->cd("/");
    } else {
        ftp->cd(currentPath);
    }
    ftp->list();
}
void MainWindow::enableDownloadButton(){
    QTreeWidgetItem *current = ui->treeFTP->currentItem();
    if (current) {
        QString currentFile = current->text(0);
        ui->downloadftp->setEnabled(!isDirectory.value(currentFile));
    } else {
        ui->downloadftp->setEnabled(false);
    }
}
void MainWindow::enableConnectButton(){
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

    ui->connectFtp->setEnabled(true);
    ui->statusLabel->setText(tr("Please enter the name of an FTP server."));
}
