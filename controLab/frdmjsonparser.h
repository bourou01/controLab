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

    /// provider - for 'exec sensors'
    QList<QString> ports(void);
    QString nameAtPort(QString port);
    double xAtPort(QString port);
    double yAtPort(QString port);

    /// provider - for 'get ressource'
    QString getKeyAt(int position);
    double getValueForKey(QString key);

private:
    QMap<QString, QVariant> getMappedJson(void);
    QString *json;
};

#endif // FRDMJSONPARSER_H
