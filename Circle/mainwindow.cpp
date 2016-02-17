#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QDockWidget>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>
#include <QPalette>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::MainWindow) {
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
	connector = new Connector();
	connector->attachControlPanel(controlPanel);
	connector->attachDrawPanel(drawPanel);
	controlPanel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
}

void MainWindow::createMenus()
{
	QAction * openAct = new QAction(tr("&Open"), this);
	QMenu * fileMenu = menuBar()->addMenu(tr("&File"));
	QAction * saveAct = new QAction(tr("&Save"), this);
	fileMenu->addAction(saveAct);
	fileMenu->addAction(openAct);
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::saveFile() {
	QString filename = QInputDialog::getText(this, tr("Save as"),
											 tr("Filename:"), QLineEdit::Normal);
	if (filename != NULL)
		this->drawPanel->grab().save(filename);
}

void MainWindow::openFile() {
	QString path = QFileDialog::getOpenFileName(this,
												tr("Open JSON File"));
	QFile file;
	file.setFileName(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QJsonDocument document = QJsonDocument::fromJson(file.readAll());
	file.close();
	QJsonObject jsonObject = document.object();

	QJsonArray jsonArray = jsonObject["circles"].toArray();
	QJsonObject circle = jsonArray.at(0).toObject();
	QJsonObject position = circle["position"].toObject();
	int R = circle["R"].toInt();
	int x = position["x"].toInt();
	int y = position["y"].toInt();
	controlPanel->setParams(std::vector<int>{x, y, R});

	QJsonObject panel = jsonObject["panel"].toObject();
	QJsonObject size = panel["size"].toObject();
	qWarning() << size;
	int panelWidth = size["x"].toInt() * 2;
	int panelHeight = size["y"].toInt() * 2;
	resize(panelWidth + controlPanel->width(), panelHeight + controlPanel->height());
}


MainWindow::~MainWindow()
{

    delete ui;
}
