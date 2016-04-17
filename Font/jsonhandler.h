#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QSize>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "params.h"
#include "glyphpoint.h"

class JsonHandler
{
public:
    static JsonHandler * getInstance();
    Params * getParams() const;
    const std::vector<std::vector<GlyphPoint *> > & getGlyphs() const;
    QSize getPanelSize();
    void parseJson(QString path);
    QByteArray createJson();
    void saveJson(QString filename,  Params * position, QSize panelSize);
private:
    JsonHandler();
    static JsonHandler * instance;
    std::vector< std::vector<GlyphPoint *> > glyphs;
    Params * params;
};

#endif // JSONHANDLER_H
