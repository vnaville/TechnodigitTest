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
        BAD_FORMAT,     // Bad format for the distance entered
        UNKNOWN_UNIT,   // Unknown distance unit for the distance entered
        UNKNOWN         // Unknown error
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

    eError lastError() const;

private:
    void setCurrentDistance(double newCurrentDistance);
    void setCurrentDistanceUnit(eDistanceUnit newCurrentDistanceUnit);

signals:
    void distanceValidatedChanged();    /* emited when the stored validated distance or its unit is changed.*/
    void errorOccurred();               /* emited when an error occurred */

private:
    double m_step = 1;        /* Currrent value of a step used in incrementation or decrementation of distance */
    double m_currentDistance; /* current validated stored distance */
    eDistanceUnit m_currentDistanceUnit = eDistanceUnit::M;     /*current distanceunit of the current validated stored distance*/
    eError m_lastError;       /*Last error occurred when entering a distance*/
};

#endif // DISTANCEMANAGER_H
