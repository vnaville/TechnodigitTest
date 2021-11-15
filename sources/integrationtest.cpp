#include "includes/integrationtest.h"
#include <QDebug>
#include <iostream>
/**
 * @brief IntegrationTest::IntegrationTest
 */
IntegrationTest::IntegrationTest()
{

}

/**
 * @brief IntegrationTest::doIntegrationTests
 * @details Execute all integration tests. If any test failed return false.
 * @return True if all tests succeed. Else, false.
 */
bool IntegrationTest::doIntegrationTests()
{
    DistanceManager distanceManager;

    int testNumber = 1;

    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: 5 m";
    if (testDistanceEnteredAndResult(testNumber, "5 m", "5 m"))
        return false;
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: 5m";
    if (testDistanceEnteredAndResult(testNumber, "5m", "5 m"))
        return false;
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: 42mm";
    if (testDistanceEnteredAndResult(testNumber, "42 mm", "42 mm"))
        return false;
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: 22km";
    if (testDistanceEnteredAndResult(testNumber, "42 km", "42 km"))
        return false;
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: 22ft";
    if (testDistanceEnteredAndResult(testNumber, "42 ft", "42 ft"))
        return false;
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: 22in";
    if (testDistanceEnteredAndResult(testNumber, "42 in", "42 in"))
        return false;
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: 22xx";
    if (!m_distanceManager.validateDistance("22 xx")
            && m_distanceManager.lastError() == DistanceManager::eError::UNKNOWN_UNIT)
    {
        qInfo() << QString("Test %1 OK").arg(testNumber);
    } else {
        qInfo() << QString("Test %1 NOK").arg(testNumber);
        return false;
    }
    testNumber++;


    qInfo() << QString("Test %1:").arg(testNumber) << "Enter: xx 56";
    if (!m_distanceManager.validateDistance("xx 56")
            && m_distanceManager.lastError() == DistanceManager::eError::BAD_FORMAT)
    {
        qInfo() << QString("Test %1 OK").arg(testNumber);
    } else {
        qInfo() << QString("Test %1 NOK").arg(testNumber);
        return false;
    }
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Test incrementation from 55m with default step";
    m_distanceManager.validateDistance("55m");
    m_distanceManager.incrementDistanceByStep();
    if (m_distanceManager.getValidatedDistance() == "55.1 m")
    {
        qInfo() << QString("Test %1 OK").arg(testNumber);
    } else {
        qInfo() << QString("Test %1 NOK").arg(testNumber);
        return false;
    }
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Test decrementation from 55m with default step";
    m_distanceManager.validateDistance("55m");
    m_distanceManager.decrementDistanceByStep();
    if (m_distanceManager.getValidatedDistance() == "54.9 m")
    {
        qInfo() << QString("Test %1 OK").arg(testNumber);
    } else {
        qInfo() << QString("Test %1 NOK").arg(testNumber);
        return false;
    }
    testNumber++;

    qInfo() << QString("Test %1:").arg(testNumber) << "Test decrementation from 0m with default step";
    m_distanceManager.validateDistance("0m");
    m_distanceManager.decrementDistanceByStep();
    if (m_distanceManager.getValidatedDistance() == "0 m")
    {
        qInfo() << QString("Test %1 OK").arg(testNumber);
    } else {
        qInfo() << QString("Test %1 NOK").arg(testNumber);
        return false;
    }
    testNumber++;

    return true;
}

bool IntegrationTest::testDistanceEnteredAndResult(int testNumber, const QString &distanceToTest, const QString &resultToHave)
{
    m_distanceManager.validateDistance(distanceToTest);
    if (m_distanceManager.getValidatedDistance() == resultToHave)
    {
        qDebug() << QString("Test %1 OK").arg(testNumber);
        return false;
    } else {
        qDebug() << QString("Test %1 NOK").arg(testNumber);
        return false;
    }
    return true;
}
