#ifndef DISTANCEMANAGER_H
#define DISTANCEMANAGER_H

#include <QObject>
#include <QRegExpValidator>

class DistanceManager: public QObject
{
    Q_OBJECT

    Q_PROPERTY(double step READ step WRITE setStep)
    Q_PROPERTY(int currentDistance READ currentDistance WRITE setCurrentDistance NOTIFY currentDistanceChanged)
    Q_PROPERTY(eDistanceUnit currentDistanceUnit READ currentDistanceUnit WRITE setCurrentDistanceUnit NOTIFY currentDistanceUnitChanged)

public:
    enum class eDistanceUnit
    {
        M,  // Meter
        MM, // Millimeter
        KM, // Kilometter
        FT, // Feet
        IN, // Inch
        UNKNOWN
    };
    Q_ENUM(eDistanceUnit)

    QString textFromValue(eDistanceUnit distanceUnit);
    eDistanceUnit eDistanceUnitFromString(const QString& value);

    enum class eError
    {
        BAD_FORMAT,
        BUNKNOWN_UNIT,
        UNKNOWN
    };
    Q_ENUM(eError)


public:
    DistanceManager(QObject* parent = nullptr);

    Q_INVOKABLE bool validateDistance(QString distance);

    Q_INVOKABLE void incrementDistanceByStep();

    Q_INVOKABLE void decrementDistanceByStep();

public:
    double step() const;
    void setStep(double newStep);

    int currentDistance() const;
    void setCurrentDistance(double newCurrentDistance);

    eDistanceUnit currentDistanceUnit() const;
    void setCurrentDistanceUnit(eDistanceUnit newCurrentDistanceUnit);

signals:
    void currentDistanceChanged();
    void errorOccured();
    void currentDistanceUnitChanged();

private:
    double m_step = 1;
    double m_currentDistance;
    eDistanceUnit m_currentDistanceUnit = eDistanceUnit::KM;
};

#endif // DISTANCEMANAGER_H
