#ifndef QMLGLOBAL_HPP
#define QMLGLOBAL_HPP

#include <QObject>

class QmlGlobal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int zOrderTopMost READ zOrderTopMost CONSTANT)
    Q_PROPERTY(int zOrderHighlights READ zOrderHighlights CONSTANT)
    Q_PROPERTY(int zOrderWidgets READ zOrderWidgets CONSTANT)
public:
    QmlGlobal(QObject* parent = nullptr);

    int zOrderTopMost()     const { return 1000; }
    int zOrderHighlights()  const { return 3;    }
    int zOrderWidgets()     const { return 1;    }
};

#endif
