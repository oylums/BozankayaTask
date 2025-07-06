#ifndef QMLGLOBAL_HPP
#define QMLGLOBAL_HPP

#include <QObject>
#include "UdpController.hpp"  // ✅ Gerekli, doğru yerde
#include "XmlController.hpp"
#include "AppMessages.hpp"
#include "CanController.hpp"

class QmlGlobal : public QObject
{
    Q_OBJECT

    Q_PROPERTY(UdpController* udpController READ udpController CONSTANT)
    Q_PROPERTY(XmlController* xmlController READ xmlController CONSTANT)
    Q_PROPERTY(CanInterfaceController* canController READ canController CONSTANT)
    Q_PROPERTY(AppLogModel* logModel READ logModel CONSTANT)

    Q_PROPERTY(int zOrderTopMost READ zOrderTopMost CONSTANT)
    Q_PROPERTY(int zOrderHighlights READ zOrderHighlights CONSTANT)
    Q_PROPERTY(int zOrderWidgets READ zOrderWidgets CONSTANT)

public:
    explicit QmlGlobal(QObject* parent = nullptr);

    UdpController* udpController() const;
    XmlController* xmlController() const;
    CanInterfaceController* canController() const;
    AppLogModel* logModel() const;

    int zOrderTopMost()     const { return 1000; }
    int zOrderHighlights()  const { return 3;    }
    int zOrderWidgets()     const { return 1;    }

private:
    UdpController* _udpController;
    XmlController* _xmlController;
    CanInterfaceController* _canController;
};

#endif // QMLGLOBAL_HPP
