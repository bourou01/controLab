#include "frdmjsonparser.h"

#include <QJsonDocument>

FRDMJSONParser::FRDMJSONParser() {
    this->json = 0;
}
FRDMJSONParser::~FRDMJSONParser() {

}

FRDMJSONParser* FRDMJSONParser::_instance = 0;

FRDMJSONParser* FRDMJSONParser::getInstance() {

    if (_instance == 0)
        _instance = new FRDMJSONParser;

    return _instance;
}
void FRDMJSONParser::setJson(QString *newJson) {
    this->json = newJson;
}
QMap<QString, QVariant> FRDMJSONParser::getMappedJson(void) {
    if (this->json == 0)
        this->json = new QString("");
    QJsonDocument doc = QJsonDocument::fromJson(this->json->toUtf8());
    QMap<QString, QVariant> mapped = doc.toVariant().toMap();
    return mapped;
}

/// provider 'exec sensors'
QList<QString> FRDMJSONParser::ports(void) {
    return getMappedJson().keys();
}
QString FRDMJSONParser::nameAtPort(QString port) {
    return getMappedJson().value(port).toMap().value("name").toString();
}
double FRDMJSONParser::xAtPort(QString port) {
    return getMappedJson().value(port).toMap().value("x").toDouble();
}
double FRDMJSONParser::yAtPort(QString port) {
    return getMappedJson().value(port).toMap().value("y").toDouble();;
}

/// get ressource
QString FRDMJSONParser::getKeyAt(int position) {
    QList<QString> keys = getMappedJson().keys();
    if (keys.length()>position)
        return keys.at(position);
    else
        return QString("");
}
double FRDMJSONParser::getValueForKey(QString key) {
    return getMappedJson().value(key).toDouble();
}
