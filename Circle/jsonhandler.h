#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QSize>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "params.h"

class JsonHandler
{
public:
	static JsonHandler * getInstance();
	Params * getParams();
	QSize getPanelSize();
	void parseJson(QString path);
	QByteArray createJson();
	void saveJson(QString filename,  Params * position, QSize panelSize);
private:
	JsonHandler();
	static JsonHandler * instance;
	Params * params;
	QSize size;
};

#endif // JSONHANDLER_H
