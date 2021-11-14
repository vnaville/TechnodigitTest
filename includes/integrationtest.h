#ifndef INTEGRATIONTEST_H
#define INTEGRATIONTEST_H

#include <QString>
#include "includes/distancemanager.h"

class IntegrationTest
{
public:
    IntegrationTest();

    bool doIntegrationTests();


private:
    bool testDistanceEnteredAndResult(int testNumber, const QString& distanceToTest,const QString& resultToHave);

private:
    DistanceManager m_distanceManager;

};

#endif // INTEGRATIONTEST_H
