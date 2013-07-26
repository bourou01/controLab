#ifndef MANAGEDOBJECTSTORE_H
#define MANAGEDOBJECTSTORE_H


#include <QStandardItemModel>
#include <QDebug>


#include <QFile>
#include <QTextStream>




class ManagedObjectStore  : public QStandardItemModel
{
private:
    ManagedObjectStore();
    ~ManagedObjectStore();
    static ManagedObjectStore *_instance;

public:
    /// singleton
    static ManagedObjectStore *getInstance();

    void insertRow(QString );

    static QString base_filename;

    QFile *file;

};

#endif // MANAGEDOBJECTSTORE_H
