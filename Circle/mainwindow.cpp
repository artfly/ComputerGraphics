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

	QHBoxLayout * layout = new QHBoxLayout;
	createPanels();
	layout->addWidget(drawPanel);
	layout->addWidget(controlPanel);
	centralWidget->setLayout(layout);
	this->setCentralWidget(centralWidget);

	createMenus();
	resize(800, 600);
}

void MainWindow::createPanels() {
	controlPanel = new ControlPanel();
	drawPanel = new DrawPanel();
	QObject::connect(controlPanel, SIGNAL(paramsChanged(Params *)),
					 drawPanel, SLOT(redraw(Params *)));
	controlPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void MainWindow::createMenus() {
	QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
	QAction * openAct = new QAction(tr("&Open"), this);
	QAction * saveAct = new QAction(tr("&Save"), this);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(openAct);
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::saveFile() {
	QString filename = QFileDialog::getSaveFileName(NULL, "Save file");
	if (filename == NULL)
		return;
	JsonHandler::getInstance()->saveJson(filename, controlPanel->getParams(),
													QSize(drawPanel->width(), drawPanel->height()));
}

void MainWindow::openFile() {
	QString path = QFileDialog::getOpenFileName(this,
												tr("Open JSON File"));
	JsonHandler * handler = JsonHandler::getInstance();
	handler->parseJson(path);
	controlPanel->setParams(handler->getParams());
	resize(handler->getPanelSize().width() + controlPanel->width(), handler->getPanelSize().height());
}

MainWindow::~MainWindow() {
    delete ui;
}
