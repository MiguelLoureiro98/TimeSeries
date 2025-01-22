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

test(AR_setters){

  double w[3] = {5.2, 1.4, 8.1};
  double cons = 5.6;

  ts::AR<3> model;

  model.set_weights(w);
  model.set_constant(cons);

  double *new_weights = model.get_weights();
  double constant = model.get_constant();

  assertNear(constant, cons, 0.00001);
  assertNear(new_weights[0], w[0], 0.00001);
  assertNear(new_weights[1], w[1], 0.00001);
  assertNear(new_weights[2], w[2], 0.00001);

}

test(MA_getters){

  double w[2] = {1.2, 7.6};
  double cons = 3.5;
  ts::MA<2> model(w, cons);

  double *weights = model.get_weights();
  double constant = model.get_constant();

  assertNear(constant, cons, 0.00001);
  assertNear(weights[0], w[0], 0.00001);
  assertNear(weights[1], w[1], 0.00001);

}

test(MA_setters){

  double w[4] = {5.2, 1.4, 8.1, 3.7};
  double cons = 5.6;

  ts::MA<4> model;

  model.set_weights(w);
  model.set_constant(cons);

  double *new_weights = model.get_weights();
  double constant = model.get_constant();

  assertNear(constant, cons, 0.00001);
  assertNear(new_weights[0], w[0], 0.00001);
  assertNear(new_weights[1], w[1], 0.00001);
  assertNear(new_weights[2], w[2], 0.00001);
  assertNear(new_weights[3], w[3], 0.00001);

}

test(initialisation){

  ts::AR<6> ar_model;
  ts::MA<9> ma_model;

  double ar_constant = ar_model.get_constant();
  double *ar_weights = ar_model.get_weights();
  double ma_constant = ma_model.get_constant();
  double *ma_weights = ma_model.get_weights();

  assertNear(ar_constant, 0.0, 0.00001);
  assertNear(ma_constant, 0.0, 0.00001);

  for(int i=0; i<6; i++){

    assertNear(ar_weights[i], 0.0, 0.00001);

  }

  for(int i=0; i<9; i++){

    assertNear(ma_weights[i], 0.0, 0.00001);

  }

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
