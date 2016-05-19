#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QDockWidget>
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QPalette>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    centralWidget = new QWidget();
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::white);
    centralWidget->setAutoFillBackground(true);
    centralWidget->setPalette(pal);

    createPanels();
    QHBoxLayout * layout = new QHBoxLayout;
    layout->addWidget(drawPanel);
    layout->addWidget(controlPanel);
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);

    createMenus();
    resize(800, 600);
    setMouseTracking(true);
}

void MainWindow::createPanels() {
    controlPanel = new ControlPanel();
    drawPanel = new DrawPanel();
    QObject::connect(controlPanel, SIGNAL(paramsChanged(Params *)),
                     drawPanel, SLOT(redraw(Params *)));
    QObject::connect(drawPanel, SIGNAL(shifted(QPoint)),
                     controlPanel, SLOT(shift(QPoint)));
    controlPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void MainWindow::createMenus() {
    QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
    QAction * openAct = new QAction(tr("&Open"), this);
    fileMenu->addAction(openAct);
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::openFile() {
    QString path = QFileDialog::getOpenFileName(this,
                                                    tr("Open JSON File"));
    QImageReader reader(path);
    QImage image = reader.read();
    if (!image.isNull()) {
        drawPanel->setImage(image);
        drawPanel->redraw(controlPanel->getParams());
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
