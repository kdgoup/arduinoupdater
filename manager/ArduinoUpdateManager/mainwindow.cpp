#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDebug"
#include "QtXml/QXmlReader"
#include "QErrorMessage"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    master(NULL)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpen()
{
    QFileDialog *d = new QFileDialog(this,
                                     "Open file",
                                     ".",
                                     "*.xml");

    d->exec();
    if (d->result()) {
        QStringList fileNames;
        openFile( d->selectedFiles().first() );
    }
    delete(d);
}

void MainWindow::onExit()
{

}

void MainWindow::openFile(const QString &name)
{
    QDomDocument *d = new QDomDocument();
    if (master) {
        delete(master);
        master=NULL;
    }
    qDebug()<<"Opening "<<name;
    QFile file(name);
    if (d->setContent(&file)) {
        master=d;
        if (parseCurrentFile()<0)
        {
            delete(master);
            master=NULL;
        }
    }
    file.close();
}

void MainWindow::showError(const QString &msg)
{
    QErrorMessage m;
    m.showMessage(msg);
    m.exec();

}
int MainWindow::parseCurrentFile()
{
    if (master==NULL)
        return -1;

    QDomElement docElem = master->documentElement();

    if (docElem.tagName() != "UpdateList") {
        showError("Invalid XML file specified.");
        return -1;
    }
    return 0;

}
