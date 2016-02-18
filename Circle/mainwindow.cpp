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
	connect(saveAct, SIGNAL(triggered()), this, SLOT(saveJson()));
	connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));
}

void MainWindow::saveImage(QString path) {
	QString filename = QInputDialog::getText(this, tr("Save as"),
											 tr("Filename:"), QLineEdit::Normal);
	if (filename == NULL)
		return;
//		this->drawPanel->grab().save(filename);
	parseJson(path);
	drawPanel->grab().save(filename);
}

void MainWindow::openFile() {
	QString path = QFileDialog::getOpenFileName(this,
												tr("Open JSON File"));
	parseJson(path);
}

void MainWindow::parseJson(QString path) {
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
	Params * params = new Params(x, y, R);
	controlPanel->setParams(params);

	QJsonObject panel = jsonObject["panel"].toObject();
	QJsonObject size = panel["size"].toObject();
	int panelWidth = size["x"].toInt();
	int panelHeight = size["y"].toInt();
	resize(panelWidth + controlPanel->width(), panelHeight + controlPanel->height());
}

void MainWindow::saveJson() {
	QString filename = QInputDialog::getText(this, tr("Save as"),
											 tr("Filename:"), QLineEdit::Normal);
	if (filename == NULL)
		return;
	QFile file;
	file.setFileName(filename);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	Params * params = controlPanel->getParams();

	QJsonObject position;
	QJsonObject circle;
	QJsonArray circles;
	position["x"] = params->getX();
	position["y"] = params->getY();
	position["R"] = params->getR();
	circle["position"] = position;
	circles.append(circle);

	QJsonObject panel;
	QJsonObject size;
	size["x"] = drawPanel->width();
	size["y"] = drawPanel->height();
	panel["size"] = size;

	QJsonObject json;
	json["circles"] = circles;
	json["panel"] = panel;

	QJsonDocument document(json);
	file.write(document.toJson());

}

MainWindow::~MainWindow() {
    delete ui;
}
