#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "controlpanel.h"
#include "drawpanel.h"
#include "connector.h"

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
	void saveFile();
private slots:
	void openFile();
private:
	void createMenus();
	void createPanels();
    QWidget * centralWidget;
    ControlPanel * controlPanel;
	Connector * connector;
	DrawPanel * drawPanel;
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_H
