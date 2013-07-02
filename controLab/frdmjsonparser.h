#ifndef FRDMJSONPARSER_H
#define FRDMJSONPARSER_H

#include <QStandardItemModel>
#include <QDebug>


class FRDMJSONParser : public QStandardItemModel
{
private:
    FRDMJSONParser();
    ~FRDMJSONParser();
    static FRDMJSONParser *_instance;



public:
    /// singleton
    static FRDMJSONParser *getInstance();

    /// configuration
    void setJson(QString *newJson);

    /// provider
    QList<QString> ports(void);
    QString nameAtPort(QString port);
    double xAtPort(QString port);
    double yAtPort(QString port);

private:
    QMap<QString, QVariant> getMappedJson(void);
    QString *json;
};

#endif // FRDMJSONPARSER_H
