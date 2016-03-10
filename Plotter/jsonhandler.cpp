#include "jsonhandler.h"
#include <QDebug>

JsonHandler * JsonHandler::instance = 0;

JsonHandler::JsonHandler() {}

JsonHandler * JsonHandler::getInstance() {
	if (!instance)
		instance = new JsonHandler();
	return instance;
}

void JsonHandler::parseJson(QString path) {
	QFile file;
	file.setFileName(path);
	file.open(QIODevice::ReadOnly | QIODevice::Text);
	QJsonDocument document = QJsonDocument::fromJson(file.readAll());
	file.close();
	QJsonObject jsonObject = document.object();

	QJsonObject lemniscate = jsonObject["lemniscate"].toObject();

	QJsonObject focus1 = lemniscate["focus1"].toObject();
	QJsonObject focus2 = lemniscate["focus2"].toObject();
	int x1 = focus1["x"].toInt();
	int y1 = focus1["y"].toInt();
	int x2 = focus2["x"].toInt();
	int y2 = focus2["y"].toInt();
	qDebug() << y1;
	params = new Params(x1, y1, x2, y2);

	QJsonObject panel = jsonObject["panel"].toObject();
	QJsonObject jsonSize = panel["size"].toObject();

	size.setHeight(jsonSize["width"].toInt());
	size.setWidth(jsonSize["height"].toInt());
}

void JsonHandler::saveJson(QString filename, Params * position, QSize panelSize) {
	QFile file;
	file.setFileName(filename);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	QJsonObject jsonLemniscate;
	QJsonObject jsonFocus1;
	QJsonObject jsonFocus2;

	jsonFocus1["x"] = position->getX1();
	jsonFocus1["y"] = position->getY1();
	jsonFocus2["x"] = position->getX2();
	jsonFocus2["y"] = position->getY2();

	jsonLemniscate["focus1"] = jsonFocus1;
	jsonLemniscate["focus2"] = jsonFocus2;

	QJsonObject jsonPanel;
	QJsonObject jsonSize;
	jsonSize["width"] = panelSize.width();
	jsonSize["height"] = panelSize.height();
	jsonPanel["size"] = jsonSize;

	QJsonObject json;
	json["lemniscate"] = jsonLemniscate;
	json["panel"] = jsonPanel;

	QJsonDocument document(json);
	file.write(document.toJson());
}

Params * JsonHandler::getParams() {
	return params;
}

QSize JsonHandler::getPanelSize() {
	return size;
}
