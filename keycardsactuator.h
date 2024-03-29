#ifndef KEYCARDSACTUATOR_H
#define KEYCARDSACTUATOR_H

#include <QObject>
#include <QSerialPort>

class KeyCardsActuator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int leftCardStatus READ leftCardStatus WRITE setLeftCardStatus NOTIFY leftCardStatusChanged)
    Q_PROPERTY(int rightCardStatus READ rightCardStatus WRITE setRightCardStatus NOTIFY rightCardStatusChanged)

public:
    explicit KeyCardsActuator(QSerialPort *serial, QObject *parent = nullptr);


    Q_INVOKABLE void approchLeftCard();
    Q_INVOKABLE void approchRightCard();


    int leftCardStatus() const;
    int rightCardStatus() const;

public slots:
    void setLeftCardStatus(int leftCardStatus);
    void setRightCardStatus(int rightCardStatus);

signals:
    void leftCardStatusChanged(int leftCardStatus);
    void rightCardStatusChanged(int rightCardStatus);

private slots:
    void handleReadyRead();

private:
    int m_leftCardStatus{0};
    int m_rightCardStatus{0};

    QSerialPort *m_serial{nullptr};
};

#endif // KEYCARDSACTUATOR_H
