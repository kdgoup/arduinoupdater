#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtXml/QDomDocument>

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
protected:

    void openFile(const QString &);
    int parseCurrentFile();

    void showError(const QString &msg);

private:
    Ui::MainWindow *ui;
    QDomDocument *master;
};

#endif // MAINWINDOW_H
