#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QString>
#include "controlpanel.h"
#include "drawpanel.h"
#include "params.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	void saveImage(QString path);
    ~MainWindow();
public slots:
private slots:
	void saveJson();
	void openFile();
private:
	void createMenus();
	void createPanels();
	void parseJson(QString path);
    QWidget * centralWidget;
    ControlPanel * controlPanel;
	DrawPanel * drawPanel;
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_H
