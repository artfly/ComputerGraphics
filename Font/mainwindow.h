#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QString>
#include <QWidget>
#include "controlpanel.h"
#include "drawpanel.h"
#include "params.h"
#include "jsonhandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void saveImage(QString path);
    ~MainWindow();
    void openFile(char * filename, QSize * panelSize);
public slots:
private slots:
    void saveFile();
//	void saveJson();
private:
    void createMenus();
    void createPanels();
    QWidget * centralWidget;
    ControlPanel * controlPanel;
    DrawPanel * drawPanel;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
