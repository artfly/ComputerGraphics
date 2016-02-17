#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
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
    ~MainWindow();
public slots:
private slots:
	void saveFile();
	void openFile();
private:
	void createMenus();
	void createPanels();
    QWidget * centralWidget;
    ControlPanel * controlPanel;
	DrawPanel * drawPanel;
    Ui::MainWindow *ui;    
};

#endif // MAINWINDOW_H
