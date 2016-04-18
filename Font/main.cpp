#include "mainwindow.h"
#include <QApplication>
#include <QImage>
#include <QFileDialog>
#include <QSize>
#include <iostream>

void saveImage(char * jsonFile, char * filename, QSize * panelSize) {
    Font * font = new Font();
    JsonHandler * handler = JsonHandler::getInstance();
    handler->parseJson(jsonFile);
    font->setGlyphs(handler->getGlyphs());
    font->setParams(handler->getParams());
    QImage * image = new QImage(* panelSize, QImage::Format_RGB888);
    memset(image->bits(), 255, image->byteCount());
    font->draw(image);
    image->save(filename);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    if (argc < 2 || argc > 5) {
        std::cout << "Usage : " << argv[0] << " JSON_FILE [IMAGE_FILE] [PANEL_WIDTH] [PANEL_HEIGHT]" << std::endl;
        return 1;
    }

    QSize * panelSize = new QSize(800, 600);
    if (argc > 3) {
        panelSize->setWidth(std::stoi(argv[argc - 2]));
        panelSize->setWidth(std::stoi(argv[argc - 1]));
    }

    if (argc % 2 == 0) {
        w.openFile(argv[1], panelSize);
        w.show();
        return a.exec();
    }

    saveImage(argv[1], argv[2], panelSize);
    return 0;
}

