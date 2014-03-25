#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QDebug"
#include "QtXml/QXmlReader"
#include "QErrorMessage"
#include <QStandardItemModel>
#include "scanner.h"
#include "releasedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    master(NULL)
{
    ui->setupUi(this);
    ui->centralWidget->hide();

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

void MainWindow::onOSChanged(QString name)
{
    qDebug()<<"OS changed to"<<name;

    // Update release list.

}

void MainWindow::onNewRelease()
{
    ReleaseDialog d(this,true);
    /*
    foreach (const QString &r, manager.getReleaseList(ui->osComboBox->currentText())) {
        d.addRelease(r);
        }
        */
    d.exec();

    uint newfiles=0, modifiedfiles=0, removedfiles=0;

    QString dir = d.getDirectory();

    if (dir.size()==0)
        return;

    Scanner scanner;
    ReleaseFileList l;
    scanner.scan(l, dir);
//    qDebug()<<"Found "<<l.size()<<" files";

    foreach(const ReleaseFile &f, l) {
        if (manager.exists(f)) {
        } else {
            manager.add(f);
            newfiles++;
        }
    }
    //    qDebug()<<"Of those,"<<newfiles<<" are new.";

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

void MainWindow::onTreeItemClicked(QModelIndex index)
{
    qDebug()<<"Custom menu"<<index;

    ui->newReleaseButton->setEnabled(true);
    ui->deleteReleaseButton->setEnabled(true);

}


int MainWindow::parseCurrentFile()
{
    if (master==NULL)
        return -1;

    QDomElement docElem = master->documentElement();

    if (docElem.tagName() != "ManagerConfig") {
        showError("Invalid XML file specified.");
        return -1;
    }

    QDomElement operatingSystems = docElem.firstChildElement("OperatingSystems");

    ui->osComboBox->clear();

    QDomElement os = operatingSystems.firstChildElement("OS");
    ui->osComboBox->setEnabled(false);

    for (; !os.isNull(); os = os.nextSiblingElement("OS")) {
        QString osname =  os.attribute("name");
        ui->osComboBox->addItem(osname);

    }
    ui->osComboBox->setEnabled(true);

    QDomElement releases = docElem.firstChildElement("Releases");
    manager.updateReleasesFromXML(releases);
    

    /* Parse the configuration items */
    /*
     <Configuration>
 <URL base="http://localhost/~alvieboy/arduino/"/>
 <Branches>
  <Branch name="master" leaf="1.0.0">
    <Description lang="en">Arduino 1.0.X Series</Description>
  </Branch>
  <Branch name="1.5" leaf="1.0.0">
    <Description lang="en">Arduino 1.5.X Series</Description>
  </Branch>
  <Branch name="development" leaf="1.0.1">
    <Description lang="en">Arduino 1.5.X Development</Description>
  </Branch>
 </Branches>
</Configuration>
*/
    QTreeView *view = ui->treeView;

    QStandardItemModel *standardModel = new QStandardItemModel ;

    QStandardItem *rootNode = standardModel->invisibleRootItem();

    /* Load all releases */




    //defining a couple of items
     QStandardItem *americaItem = new QStandardItem("America");
     QStandardItem *mexicoItem =  new QStandardItem("Canada");
     QStandardItem *usaItem =     new QStandardItem("USA");
     QStandardItem *bostonItem =  new QStandardItem("Boston");
     QStandardItem *europeItem =  new QStandardItem("Europe");
     QStandardItem *italyItem =   new QStandardItem("Italy");
     QStandardItem *romeItem =    new QStandardItem("Rome");
     QStandardItem *veronaItem =  new QStandardItem("Verona");


     //building up the hierarchy
     rootNode->    appendRow(americaItem);
     rootNode->    appendRow(europeItem);
     americaItem-> appendRow(mexicoItem);
     americaItem-> appendRow(usaItem);
     usaItem->     appendRow(bostonItem);
     europeItem->  appendRow(italyItem);
     italyItem->   appendRow(romeItem);
     italyItem->   appendRow(veronaItem);

    view->setModel( standardModel );

    ui->centralWidget->show();
    ui->newReleaseButton->setEnabled(false);
    ui->deleteReleaseButton->setEnabled(false);


    return 0;

}
