#ifndef BUTTONS_H
#define BUTTONS_H

#include <QObject>

class Buttons : public QObject
{
    Q_OBJECT
public:
    explicit Buttons(QObject *parent = nullptr);

    void pressDock();
    void pressSync();
    void pressStation();

signals:

private:
    bool m_isDockPressed{false};
    bool m_isSyncPressed{false};
    bool m_isStationPressed{false};

};

#endif // BUTTONS_H
