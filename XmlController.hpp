#ifndef XMLCONTROLLER_H
#define XMLCONTROLLER_H

#include <QObject>
#include <QVariantList>
#include <QFile>
#include <QDomDocument>

class XmlController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList shapes READ shapes NOTIFY shapesChanged)

public:
    explicit XmlController(QObject *parent = nullptr);
    Q_INVOKABLE void setFilePath(const QString &path);

    QVariantList shapes() const;

public slots:
    Q_INVOKABLE void parseXml();

signals:
    void shapesChanged();
    void parseError(const QString &error);

    void filePathChanged();

private:
    QString m_filePath;
    QVariantList m_shapes;
};

#endif // XMLCONTROLLER_H
