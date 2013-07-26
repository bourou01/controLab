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
    bool setJson(QString *newJson);

    /// provider - for 'exec sensors'
    QList<QString> ports(void);

    QString nameAtPort(QString port);   /// deprecated
    double xAtPort(QString port);   /// deprecated
    double yAtPort(QString port);   /// deprecated

    /// provider - for 'get ressource'
    QString getKeyAt(int position);
    double getValueForKey(QString key);

    /// key-value-coding
    int count();
    double valueAtIndex(int index);


private:
    QMap<QString, QVariant> getMappedJson(void);
    QString *json;
};

#endif // FRDMJSONPARSER_H
