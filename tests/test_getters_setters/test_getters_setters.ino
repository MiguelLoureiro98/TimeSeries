#line 2 "test_getters_setters.ino"
#include <ArduinoUnit.h>
#include "TimeSeries.h"

//int i = 0;

test(AR_getters){

  double w[2] = {1.2, 7.6};
  double cons = 3.5;
  ts::AR<2> model(w, cons);

  double *weights = model.get_weights();
  double constant = model.get_constant();

  assertNear(constant, cons, 0.00001);
  assertNear(weights[0], w[0], 0.00001);
  assertNear(weights[1], w[1], 0.00001);

}

void setup() {

  Serial.begin(9600);
  while(!Serial) {}
  //aunit::TestRunner::setVerbosity(aunit::Verbosity::kAll);

}

void loop() {

  /*if(i == 0){

    double w[2] = {1.2, 7.6};
    double cons = 3.5;
    ts::AR<2> model(w, cons);

    double *weights = model.get_weights();
    double constant = model.get_constant();

    Serial.print(constant);
    Serial.print(",");
    Serial.println(cons);

    i++;

  }*/
  //aunit::TestRunner::run();
  Test::run();

}
