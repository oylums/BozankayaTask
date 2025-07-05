#include "XmlController.hpp"
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include <QCoreApplication>

XmlController::XmlController(QObject *parent) : QObject(parent) {}

void XmlController::setFilePath(const QString &path) {
    qDebug()<<path;
    m_filePath = path;
    watcher.addPath(m_filePath);
    connect(&watcher, &QFileSystemWatcher::fileChanged, this, &XmlController::onFileChanged);
    parseXml();
}

QStringList XmlController::values() const {
    return m_values;
}

void XmlController::onFileChanged() {
    watcher.removePath(m_filePath);
    watcher.addPath(m_filePath);
    parseXml();
    qDebug() << "file changed ";
}

void XmlController::loadXml() {
    parseXml();
}

void XmlController::parseXml() {

    // qDebug() << "Dosya yolu:" << m_filePath;
    // qDebug() << "Dosya var mı? " << QFile::exists(m_filePath);


    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        emit parseError("XML dosyası açılamadı!");
        qDebug() << "[XmlController] Dosya açılamadı ";
        return;
    }

    QDomDocument doc;
    QString errorStr;
    int errorLine, errorColumn;
    if (!doc.setContent(&file, &errorStr, &errorLine, &errorColumn)) {
        emit parseError(QString("XML Hatası: %1 (Satır %2, Sütun %3)").arg(errorStr).arg(errorLine).arg(errorColumn));
        return;
    }

    QStringList list;
    QDomNodeList items = doc.elementsByTagName("item");
    for (int i = 0; i < items.count(); ++i) {
        QDomElement el = items.at(i).toElement();
        list << el.text();
    }

    if (list != m_values) {
        m_values = list;
        emit valuesChanged();
    }
}
