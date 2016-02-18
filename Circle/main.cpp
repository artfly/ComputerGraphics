#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
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
	w.saveImage(a.arguments().at(1));
	return 0;
}
