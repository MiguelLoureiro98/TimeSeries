#include "AUnit.h"
#include "TimeSeries.h"

int i = 0;

/*void testAR(){

  double w[2] = {1.2, 7.6};
  double cons = 3.5;
  ts::AR<2> model(w, cons);

  double *weights = model.get_weights();
  double constant = model.get_constant();

  assertTrue(1);
  //assertNear(constant, cons, 0.001);

}*/

void setup() {

  Serial.begin(9600);
  //aunit::TestRunner::setVerbosity(aunit::Verbosity::kAll);

}

void loop() {

  if(i == 0){

    double w[2] = {1.2, 7.6};
    double cons = 3.5;
    ts::AR<2> model(w, cons);

    double *weights = model.get_weights();
    double constant = model.get_constant();

    Serial.print(constant);
    Serial.print(",");
    Serial.println(cons);

    i++;

  }
  //aunit::TestRunner::run();

}
