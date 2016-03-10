#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QFileDialog>
#include <iostream>

void saveImage(char * jsonFile) {
//	Circle * circle = new Circle();
//	JsonHandler * handler = JsonHandler::getInstance();
//	handler->parseJson(jsonFile);
//	circle->setParams(handler->getParams());
//	QImage * image = new QImage(handler->getPanelSize(), QImage::Format_RGB888);
//	memset(image->bits(), 255, image->byteCount());
//	circle->draw(image);
//	QString filename = QFileDialog::getSaveFileName(NULL, "Save file");
//	image->save(filename);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
	if (argc > 2) {
		std::cout << "Usage : " << argv[0] << " [FILE]" << std::endl;
		return 1;
	}
	if (argc == 1) {
		w.show();
		return a.exec();
	}
	saveImage(argv[1]);
	return 0;
}

