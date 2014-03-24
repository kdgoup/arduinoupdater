#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml/QDomDocument>
#include "updatelistmodel.h"
#include "manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onOpen();
    void onExit();
    void onNewRelease();
protected:

    void openFile(const QString &);
    int parseCurrentFile();
    void showError(const QString &msg);

private:
    Ui::MainWindow *ui;
    QDomDocument *master;
    Manager manager;
};

#endif // MAINWINDOW_H
