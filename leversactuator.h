#ifndef LEVERSACTUATOR_H
#define LEVERSACTUATOR_H


#include <QObject>

#include <QSerialPort>

class LeversActuator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int leftPosition READ leftPosition WRITE setLeftPosition NOTIFY leftPositionChanged)
    Q_PROPERTY(int rightPosition READ rightPosition WRITE setRightPosition NOTIFY rightPositionChanged)

public:
    explicit LeversActuator(QSerialPort *serial, QObject *parent = nullptr);

    enum Direction{
        forward,
        reverse
    };
    Q_ENUM(Direction);

    enum Lever{
        left,
        right
    };
    Q_ENUM(Lever);


    void homeLeft();
    void homeRight();
    Q_INVOKABLE void move(Lever lever, Direction direction, int steps);
    Q_INVOKABLE void moveBoth(Direction direction, int steps);
    Q_INVOKABLE void moveTest();
    Q_INVOKABLE void startMoving();
    Q_INVOKABLE void stopMoving();

    int leftPosition() const;
    int rightPosition() const;


public slots:
    void home();
    void setLeftPosition(int leftPosition);
    void setRightPosition(int rightPosition);


signals:
    void leftPositionChanged(int leftPosition);
    void rightPositionChanged(int rightPosition);


private slots:
    void handleReadyRead();

private:
    QSerialPort *m_serial{nullptr};

    bool m_isInit{false};

    bool m_isHomeRight{false};
    bool m_isHomeLeft{false};

    int m_leftPosition{0};
    int m_rightPosition{0};

};


#endif // LEVERSACTUATOR_H
