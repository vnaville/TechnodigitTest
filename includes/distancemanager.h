#ifndef DISTANCEMANAGER_H
#define DISTANCEMANAGER_H

#include <QObject>
#include <QRegExpValidator>

class DistanceManager: public QObject
{
    Q_OBJECT

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

    Q_INVOKABLE QString getValidatedDistance();

public:
    double step() const;
    void setStep(double newStep);

    int currentDistance() const;
    void setCurrentDistance(double newCurrentDistance);

    eDistanceUnit currentDistanceUnit() const;
    void setCurrentDistanceUnit(eDistanceUnit newCurrentDistanceUnit);

signals:
    void distanceValidatedChanged();

private:
    double m_step = 1;
    double m_currentDistance;
    eDistanceUnit m_currentDistanceUnit = eDistanceUnit::M;
};

#endif // DISTANCEMANAGER_H
