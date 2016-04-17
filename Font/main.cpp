#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QFileDialog>
#include <iostream>

void saveImage(char * jsonFile, char * filename) {
////	Lemniscate * lemniscate = new Lemniscate();
//	JsonHandler * handler = JsonHandler::getInstance();
//	handler->parseJson(jsonFile);
////	lemniscate->setParams(handler->getParams());
//	QImage * image = new QImage(handler->getPanelSize(), QImage::Format_RGB888);
//	memset(image->bits(), 255, image->byteCount());
//	lemniscate->draw(image);
//	image->save(filename);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    if (argc != 2 && argc != 3) {
        std::cout << "Usage : " << argv[0] << " JSON_FILE [IMAGE_FILE]" << std::endl;
        return 1;
    }
    if (argc == 2) {
        w.openFile(argv[1]);
        w.show();
        return a.exec();
    }
    saveImage(argv[1], argv[2]);
    return 0;
}

