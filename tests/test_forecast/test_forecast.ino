#include <TimeSeries.h>
#include <ArduinoUnit.h>

test(AR_single_step){

  ts::AR<2> null_model;
  
  double odd_weights[5] = {1.0, -2.0, 3.5, -1.0, 0.0};
  double even_weights[8] = {7.0, -4.5, 8.0, -11.5, 0.0, 0.0, 0.0, 1.0};

  ts::AR<5> odd_model(odd_weights, 5.0);
  ts::AR<8> even_model(even_weights);

  double null_data[2] = {1.0, 2.0};
  double odd_data[5] = {1.0, 1.0, 1.0, 3.0, 2.0};
  double even_data[8] = {1.0, 1.0, -2.0, 3.0, 5.0, 0.0, 0.0, 2.0};

  double null_pred[1] = {1.0};
  double odd_model_pred[1] = {0.0};
  double even_model_pred[1] = {0.0};

  null_model.forecast(null_data, null_pred);
  odd_model.forecast(odd_data, odd_model_pred);
  even_model.forecast(even_data, even_model_pred);

  assertNear(null_pred[0], 0.0, 0.00001);

}

//test(MA_single_step){



//}

void setup() {

  Serial.begin(9600);
  while(!Serial) {}

}

void loop() {

  Test::run();

}
