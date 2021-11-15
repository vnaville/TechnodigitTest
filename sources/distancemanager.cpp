#include "includes/distancemanager.h"
#include <QDebug>

/**
 * @brief DistanceManager::textFromValue
 * @details Allow to convert an eDistanceUnit into a string
 * @param distanceUnit eDistanceUnit to convert
 * @return the result of conversion. Return "Unknown" if the conversion failed
 */
QString DistanceManager::textFromValue(eDistanceUnit distanceUnit)
{
    switch (distanceUnit)
    {
    case eDistanceUnit::M: return "m";
    case eDistanceUnit::MM: return "mm";
    case eDistanceUnit::KM: return "km";
    case eDistanceUnit::FT: return "ft";
    case eDistanceUnit::IN: return "in";
    default: return "Unknown";
    }
}

/**
 * @brief DistanceManager::eDistanceUnitFromString
 * @details Allow to convert a string into a eDistanceUnit
 * @param value QString to convert into a eDistanceUnit
 * @return the result of conversion. Return eDistanceUnit::UNKNOWN if the conversion failed
 */
DistanceManager::eDistanceUnit DistanceManager::eDistanceUnitFromString(const QString &value)
{
    QString valueLowerCase = value.toLower();

    if (valueLowerCase == "m")
        return eDistanceUnit::M;

    if (valueLowerCase == "mm")
        return eDistanceUnit::MM;

    if (valueLowerCase == "km")
        return eDistanceUnit::KM;

    if (valueLowerCase == "in")
        return eDistanceUnit::IN;

    if (valueLowerCase == "ft")
        return eDistanceUnit::FT;


    return eDistanceUnit::UNKNOWN;
}

/**
 * @brief DistanceManager::DistanceManager
 * @details Constructor of Distancemanager Class
 * @param parent Parent object of the class
 */
DistanceManager::DistanceManager(QObject* parent)
    : QObject (parent)
{
}

/**
 * @brief DistanceManager::validateDistance
 * @details validateDistance given in argument. If an error occured, a signal errorOccurred() is emited, If the distance is
 * validated, a signal distanceValidatedChanged() is emited
 * @param distance the distance to validate
 * @return True if the distance is validated, else , false.
 */
bool DistanceManager::validateDistance(QString distance)
{
    QRegExp regExp("([0-9]+(.[0-9]+)?) *([A-Za-z]*)");
    regExp.indexIn(distance);

    QRegExpValidator validator;
    validator.setRegExp(regExp);

    int pos = 0;
    QValidator::State s = validator.validate(distance, pos);

    if (s == QValidator::Acceptable)
    {
        double validatedDistance = regExp.cap(1).toDouble();

        eDistanceUnit validatedUnit = eDistanceUnitFromString(regExp.cap(3));

        // Special case: if no unit is written, KM is used as default value
        if (regExp.cap(3).isEmpty())
        {
            validatedUnit = eDistanceUnit::M;
        }

        if (validatedUnit == eDistanceUnit::UNKNOWN)
        {
            qWarning() << QString("Wrong distance unit: %1 is unknown").arg(regExp.cap(2));

            m_lastError = eError::UNKNOWN_UNIT;
            emit errorOccurred();

            return false;
        }

        setCurrentDistanceUnit(validatedUnit);
        setCurrentDistance(validatedDistance);

        emit distanceValidatedChanged();
        return true;
    }
    else
    {
        m_lastError = eError::BAD_FORMAT;
        emit errorOccurred();
        return false;
    }
}

/**
 * @brief DistanceManager::incrementDistanceByStep
 * @details increase current stored distance by the value of m_step. A signal distanceValidatedChanged() is emitted.
 */
void DistanceManager::incrementDistanceByStep()
{
    qDebug() << "Increment step";
    m_currentDistance = m_currentDistance + m_step;

    emit distanceValidatedChanged();
}

/**
 * @brief DistanceManager::decrementDistanceByStep
 * @details decrease current stored distance by the value of m_step. If the new value is < 0, nothing happen.
 *  A signal distanceValidatedChanged() is emitted.
 */
void DistanceManager::decrementDistanceByStep()
{
    qDebug() << "Décrement step";
    double newDistance = m_currentDistance - m_step;
    if (newDistance >= 0 )
    {
        m_currentDistance = newDistance;
    }

    emit distanceValidatedChanged();
}

/**
 * @brief DistanceManager::getValidatedDistance
 * @details Return the current validated distance.
 * @return The current validated distance.
 */
QString DistanceManager::getValidatedDistance()
{
    QString result = QString::number(m_currentDistance) + " " + textFromValue(m_currentDistanceUnit);
    return result;
}

/**
 * @brief DistanceManager::getLastErrorString
 * @details Return the string description of the last error occurred
 * @return The string description of the last error occurred
 */
QString DistanceManager::getLastErrorString()
{
    switch (m_lastError)
    {
    case eError::BAD_FORMAT:
        return "Distance not valid, bad format";
    case eError::UNKNOWN_UNIT:
        return "Unknown distance unit";
    default: return "Unkown error";
    }
}

/**
 * @brief DistanceManager::step
 * @details Return current value of step
 * @return The current value of step
 */
double DistanceManager::step() const
{
    return m_step;
}

/**
 * @brief DistanceManager::setStep
 * @details
 * @param newStep
 */
void DistanceManager::setStep(double newStep)
{
    m_step = newStep;
}

/**
 * @brief DistanceManager::setCurrentDistance
 * @details Set a new current distance value
 * @param newCurrentDistance the new value
 */
void DistanceManager::setCurrentDistance(double newCurrentDistance)
{
    if (m_currentDistance == newCurrentDistance)
        return;
    m_currentDistance = newCurrentDistance;
    emit distanceValidatedChanged();
}

/**
 * @brief DistanceManager::setCurrentDistanceUnit
 * @details Set a new distance unit of current distance
 * @param newCurrentDistanceUnit the new distance unit of current distance
 */
void DistanceManager::setCurrentDistanceUnit(eDistanceUnit newCurrentDistanceUnit)
{
    if (m_currentDistanceUnit == newCurrentDistanceUnit)
        return;

    m_currentDistanceUnit = newCurrentDistanceUnit;
    emit distanceValidatedChanged();
}

DistanceManager::eError DistanceManager::lastError() const
{
    return m_lastError;
}
