#include "XmlController.hpp"

XmlController::XmlController(QObject *parent)
    : QObject(parent)
{
    connect(this,&XmlController::filePathChanged,this,&XmlController::parseXml);
    connect(&m_fileWatcher, &QFileSystemWatcher::fileChanged, this, &XmlController::onFileChanged);
}

void XmlController::setFilePath(const QString &path)
{
    if(m_filePath != path) {
        m_filePath = path;
        m_fileWatcher.removePaths(m_fileWatcher.files());
        if (QFile::exists(m_filePath)) {
            m_fileWatcher.addPath(m_filePath);
        }

        emit filePathChanged();
    }
}

QVariantList XmlController::shapes() const
{
    return m_shapes;
}

void XmlController::parseXml()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        emit parseError("XML dosyası açılamadı!");
        qDebug() << "XML file open error";
        return;
    }

    QDomDocument doc;
    QString errorStr;
    int errorLine, errorColumn;
    if (!doc.setContent(&file, &errorStr, &errorLine, &errorColumn)) {
        emit parseError(QString("XML Hatası: %1 (Satır %2, Sütun %3)").arg(errorStr).arg(errorLine).arg(errorColumn));
        return;
    }

    QDomNodeList shapesList = doc.elementsByTagName("Shapes");
    if (shapesList.isEmpty()) {
        emit parseError("Shapes etiketi bulunamadı!");
         qDebug() << "Shapes etiketi bulunamadı";
        return;
    }

    QVariantList newShapes;

    QDomNode shapesNode = shapesList.at(0);
    QDomNode child = shapesNode.firstChild();

    while (!child.isNull()) {
        QDomElement element = child.toElement();
        if (!element.isNull()) {
            QVariantMap shape;
            shape["type"] = element.tagName();
            shape["id"] = element.attribute("id");

            QDomNamedNodeMap attrs = element.attributes();
            for (int i = 0; i < attrs.count(); ++i) {
                QDomAttr attr = attrs.item(i).toAttr();
                if (attr.name() != "id") {
                    shape[attr.name()] = attr.value();
                }
            }


            if (element.tagName() == "Text") {
                shape["text"] = element.text().trimmed();
            }

            newShapes.append(shape);
        }

        child = child.nextSibling();
    }

    m_shapes = newShapes;
    emit shapesChanged();
}
void XmlController::onFileChanged(const QString &path)
{
    qDebug() << "XML dosyası değişti, tekrar parse ediliyor:" << path;
    if (QFile::exists(path)) {
        m_fileWatcher.addPath(path);
    }

    parseXml();
}
