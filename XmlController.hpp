#ifndef XMLCONTROLLER_H
#define XMLCONTROLLER_H

#include <QObject>
#include <QStringList>
#include <QFileSystemWatcher>

class XmlController : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList values READ values NOTIFY valuesChanged)

public:
    explicit XmlController(QObject *parent = nullptr);
    QStringList values() const;

    Q_INVOKABLE void loadXml();
    Q_INVOKABLE void setFilePath(const QString &path);

signals:
    void valuesChanged();
    void parseError(const QString &message);

private slots:
    void onFileChanged();

private:
    QStringList m_values;
    QString m_filePath;
    QFileSystemWatcher watcher;
    void parseXml();
};

#endif // XMLCONTROLLER_H
