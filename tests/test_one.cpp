#include <CppUTest/TestHarness.h>
#include <TimeSeries.h>

TEST_GROUP(hey){

};

TEST(hey, lol){

    double one = 1.0;

    DOUBLES_EQUAL(one, 1.0, 0.001);

};