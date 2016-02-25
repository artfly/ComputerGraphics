#include "jsonhandler.h"
#include <QDebug>

JsonHandler *JsonHandler::instance = 0;

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

	QJsonArray jsonArray = jsonObject["circles"].toArray();
	QJsonObject circle = jsonArray.at(0).toObject();
	QJsonObject position = circle["position"].toObject();
	int R = circle["R"].toInt();
	int x = position["x"].toInt();
	int y = position["y"].toInt();
	params = new Params(x, y, R);

	QJsonObject panel = jsonObject["panel"].toObject();
	QJsonObject jsonSize = panel["size"].toObject();

	size.setHeight(jsonSize["y"].toInt());
	size.setWidth(jsonSize["x"].toInt());
}

void JsonHandler::saveJson(QString filename, Params * position, QSize panelSize) {
	QFile file;
	file.setFileName(filename);
	file.open(QIODevice::WriteOnly | QIODevice::Text);

	QJsonObject jsonPosition;
	QJsonObject jsonCircle;
	QJsonArray jsonCircles;
	jsonPosition["x"] = position->getX();
	jsonPosition["y"] = position->getY();
	qWarning() << (position->getR());
	jsonCircle["R"] = position->getR();
	jsonCircle["position"] = jsonPosition;
	jsonCircles.append(jsonCircle);

	QJsonObject jsonPanel;
	QJsonObject jsonSize;
	jsonSize["x"] = panelSize.width();
	jsonSize["y"] = panelSize.height();
	jsonPanel["size"] = jsonSize;

	QJsonObject json;
	json["circles"] = jsonCircles;
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
