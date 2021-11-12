#include "includes/distancemanager.h"
#include <QDebug>

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

DistanceManager::eDistanceUnit DistanceManager::eDistanceUnitFromString(const QString &value)
{
    QString valueLowerCase = value.toLower();

    if (valueLowerCase == "m")
        return eDistanceUnit::M;

    if (valueLowerCase == "mm")
        return eDistanceUnit::MM;

    if (valueLowerCase == "km")
        return eDistanceUnit::M;

    if (valueLowerCase == "in")
        return eDistanceUnit::M;

    return eDistanceUnit::UNKNOWN;
}

DistanceManager::DistanceManager(QObject* parent)
    : QObject (parent)
{
}

bool DistanceManager::validateDistance(QString distance)
{
    qDebug() << "VALIDATE";

    QRegExp regExp("([0-9]+) *([A-Za-z]{,2})");
    regExp.indexIn(distance);

    QRegExpValidator validator;
    validator.setRegExp(regExp);

    int pos = 0;
    QValidator::State s = validator.validate(distance, pos);

    if (s == QValidator::Acceptable)
    {
        double validatedDistance = regExp.cap(1).toDouble();

        eDistanceUnit validatedUnit = eDistanceUnitFromString(regExp.cap(2));

        if (validatedUnit == eDistanceUnit::UNKNOWN)
        {
            qWarning() << QString("Wrong distance unit: %1 is unknown").arg(regExp.cap(2));
            return false;
        }

        qWarning() << "Validated!";
        setCurrentDistance(validatedDistance);
        return true;
    }
    else
    {
        qWarning() << "Distance not valid, bad format";
        return false;
    }
}

void DistanceManager::incrementDistanceByStep()
{
    qDebug() << "Increment step";
    m_currentDistance = m_currentDistance + m_step;
}

void DistanceManager::decrementDistanceByStep()
{
    qDebug() << "Décrement step";
    int newDistance = m_currentDistance - m_step;
    if (newDistance >= 0 )
    {
        m_currentDistance = newDistance;
    }
}

double DistanceManager::step() const
{
    return m_step;
}

void DistanceManager::setStep(double newStep)
{
    m_step = newStep;
}

int DistanceManager::currentDistance() const
{
    return m_currentDistance;
}

void DistanceManager::setCurrentDistance(double newCurrentDistance)
{
    if (m_currentDistance == newCurrentDistance)
        return;
    m_currentDistance = newCurrentDistance;
    emit currentDistanceChanged();
}

DistanceManager::eDistanceUnit DistanceManager::currentDistanceUnit() const
{
    return m_currentDistanceUnit;
}

void DistanceManager::setCurrentDistanceUnit(eDistanceUnit newCurrentDistanceUnit)
{
    if (m_currentDistanceUnit == newCurrentDistanceUnit)
        return;
    m_currentDistanceUnit = newCurrentDistanceUnit;
    emit currentDistanceUnitChanged();
}
