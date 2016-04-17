#include "jsonhandler.h"
#include <QDebug>

JsonHandler * JsonHandler::instance = 0;

JsonHandler::JsonHandler() {}

JsonHandler * JsonHandler::getInstance() {
    if (!instance) {
        instance = new JsonHandler();
    }
    return instance;
}

void JsonHandler::parseJson(QString path) {
    QFile file;
    file.setFileName(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    file.close();
    QJsonObject jsonObject = document.object();

    QJsonObject position = jsonObject["position"].toObject();
    int x = position["x"].toInt();
    int y = position["y"].toInt();

    int scale = jsonObject["scale"].toInt();
    bool fill = jsonObject["fill"].toBool();
    bool outline = jsonObject["outline"].toBool();

    QJsonArray glyphsArray = jsonObject["glyphs"].toArray();
    QJsonArray glyphArray;
    QJsonObject pointObject;
    for (auto glyph : glyphsArray) {
        glyphArray = glyph.toArray();
        std::vector<GlyphPoint * > glyphPoints;
        for (auto point : glyphArray) {
            pointObject = point.toObject();
            position = pointObject["position"].toObject();
            glyphPoints.push_back(new GlyphPoint(position["x"].toInt(), position["y"].toInt(), pointObject["oncurve"].toBool()));
        }
        glyphs.push_back(glyphPoints);
    }

    params =  new Params(x, y, scale, fill, outline);
}

void JsonHandler::saveJson(QString filename, Params * position, QSize panelSize) {
//	QFile file;
//	file.setFileName(filename);
//	file.open(QIODevice::WriteOnly | QIODevice::Text);

//	QJsonObject jsonLemniscate;
//	QJsonObject jsonFocus1;
//	QJsonObject jsonFocus2;

//	jsonFocus1["x"] = position->getX1();
//	jsonFocus1["y"] = position->getY1();
//	jsonFocus2["x"] = position->getX2();
//	jsonFocus2["y"] = position->getY2();

//	jsonLemniscate["focus1"] = jsonFocus1;
//	jsonLemniscate["focus2"] = jsonFocus2;

//	QJsonObject jsonPanel;
//	QJsonObject jsonSize;
//	jsonSize["width"] = panelSize.width();
//	jsonSize["height"] = panelSize.height();
//	jsonPanel["size"] = jsonSize;

//	QJsonObject json;
//	json["lemniscate"] = jsonLemniscate;
//	json["panel"] = jsonPanel;

//	QJsonDocument document(json);
//	file.write(document.toJson());
}

Params * JsonHandler::getParams() const {
    return params;
}

const std::vector< std::vector<GlyphPoint *> > & JsonHandler::getGlyphs() const {
    return glyphs;
}
