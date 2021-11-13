#ifndef DISTANCEMANAGER_H
#define DISTANCEMANAGER_H

#include <QObject>
#include <QRegExpValidator>

/**
 * @brief The DistanceManager class
 */
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
        UNKNOWN_UNIT,
        UNKNOWN
    };
    Q_ENUM(eError)


public:
    DistanceManager(QObject* parent = nullptr);

    Q_INVOKABLE bool validateDistance(QString distance);

    Q_INVOKABLE void incrementDistanceByStep();

    Q_INVOKABLE void decrementDistanceByStep();

    Q_INVOKABLE QString getValidatedDistance();

    Q_INVOKABLE QString getLastErrorString();

public:
    double step() const;
    void setStep(double newStep);

private:
    void setCurrentDistance(double newCurrentDistance);
    void setCurrentDistanceUnit(eDistanceUnit newCurrentDistanceUnit);

signals:
    void distanceValidatedChanged();
    void errorOccurred();

private:
    double m_step = 1;
    double m_currentDistance;
    eDistanceUnit m_currentDistanceUnit = eDistanceUnit::M;

    eError m_lastError;
};

#endif // DISTANCEMANAGER_H
