#include "managedobjectstore.h"

#include <QDebug>
#include <QDateTime>


QString ManagedObjectStore::base_filename="/Users/bourou01/Desktop/serial/samples[";

#include "frdmjsonparser.h"

ManagedObjectStore::ManagedObjectStore() {
    //get current date and time
    QDateTime dateTime = QDateTime::currentDateTime();

    QString filename = base_filename + dateTime.toString() + "].csv";

    file = new QFile(filename);
    file->setFileName(filename);
    file->open(QIODevice::ReadWrite | QIODevice::Text);
}
ManagedObjectStore::~ManagedObjectStore() {
    file->close();
}


ManagedObjectStore* ManagedObjectStore::_instance = 0;

ManagedObjectStore* ManagedObjectStore::getInstance() {
    if (_instance == 0)
        _instance = new ManagedObjectStore;
    return _instance;
}

void ManagedObjectStore::insertRow(QString row) {

    FRDMJSONParser::getInstance()->setJson(&row);
    QList<QString> keys = FRDMJSONParser::getInstance()->ports();
    int keysCount =  FRDMJSONParser::getInstance()->count();



    QTextStream stream(file);

//////// HEADER
///
///
///
///
    static bool headerAlreadyPerformed = false;
    /// executé une seule fois
    if (!headerAlreadyPerformed) {
        for (int i=keysCount-1; i>=0 ; i--) {
            QString key_i = keys.at(i);
            stream << key_i <<";";
        }
        stream << endl;
    }
    headerAlreadyPerformed = true;

///////////////////

    //stream << row << endl;

    for (int i=keysCount-1; i>=0 ; i--) {
        QString temp;

        double val_i = FRDMJSONParser::getInstance()->valueAtIndex(i);

        QString toPrint(QString("%1").arg(QString::number(val_i)));


        toPrint.replace('.', ',');
        stream << toPrint <<";";
    }

    stream << endl;
}

