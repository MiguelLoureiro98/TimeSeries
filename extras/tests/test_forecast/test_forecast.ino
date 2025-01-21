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
  assertNear(odd_model_pred[0], 4.5, 0.00001);
  assertNear(even_model_pred[0], -46.0, 0.00001);

}

test(MA_single_step){

  ts::MA<2> null_model;

  double odd_weights[5] = {1.0, -2.0, 3.5, -1.0, 0.0};
  double even_weights[8] = {7.0, -4.5, 8.0, -11.5, 0.0, 0.0, 0.0, 1.0};

  ts::MA<5> odd_model(odd_weights, 5.0);
  ts::MA<8> even_model(even_weights);

  double null_data[2] = {1.0, 2.0};
  double odd_data[5] = {1.0, 1.0, 1.0, 3.0, 2.0};
  double even_data[8] = {1.0, 1.0, -2.0, 3.0, 5.0, 0.0, 0.0, 2.0};

  double null_pred[1] = {1.0};
  double odd_model_pred[1] = {0.0};
  double even_model_pred[1] = {0.0};

  null_model.forecast(null_data, null_pred);
  odd_model.forecast(odd_data, odd_model_pred);
  even_model.forecast(even_data, even_model_pred);

  assertNear(null_pred[0], 0.0, 0.0001);
  assertNear(odd_model_pred[0], 4.5, 0.0001);
  assertNear(even_model_pred[0], -46.0, 0.0001);

}

test(AR_multi_step){

  ts::AR<2> null_model;
  
  double odd_weights[5] = {1.0, -2.0, 3.5, -1.0, 0.0};
  double even_weights[8] = {7.0, -4.5, 8.0, -11.5, 0.0, 0.0, 0.0, 1.0};

  ts::AR<5> odd_model(odd_weights, 5.0);
  ts::AR<8> even_model(even_weights);

  double null_data[2] = {1.0, 2.0};
  double odd_data[5] = {1.0, 1.0, 1.0, 3.0, 2.0};
  double even_data[8] = {1.0, 1.0, -2.0, 3.0, 5.0, 0.0, 0.0, 2.0};

  double null_pred[2] = {1.0, 1.0};
  double null_true[2] = {0.0, 0.0};
  double odd_model_pred[6] = {0};
  double odd_model_true[6] = {4.5, 12.5, 2.5, 7.25, 39.25, -14.0};
  double even_model_pred[3] = {0};
  double even_model_true[3] = {-46.0, -63.5, -51.0};

  null_model.forecast(null_data, null_pred, 2);
  odd_model.forecast(odd_data, odd_model_pred, 6);
  even_model.forecast(even_data, even_model_pred, 3);

  assertNear(null_pred[0], 0.0, 0.00001);
  assertNear(null_pred[1], 0.0, 0.00001);

  for(int i=0; i<6; i++){

    assertNear(odd_model_pred[i], odd_model_true[i], 0.00001);

  }

  for(int i=0; i<3; i++){

    assertNear(even_model_pred[i], even_model_true[i], 0.00001);

  }

}

test(MA_multi_step){

  ts::MA<2> null_model;
  
  double null_data[2] = {1.0, 2.0};
  double odd_data[5] = {1.0, 1.0, 1.0, 3.0, 2.0};
  double new_odd_data[5] = {1.0, 1.0, 3.0, 2.0, 6.0};
  double even_data[8] = {1.0, 1.0, -2.0, 3.0, 5.0, 0.0, 0.0, 2.0};
  double new_even_data[8] = {1.0, -2.0, 3.0, 5.0, 0.0, 0.0, 2.0, -50.0};

  double odd_weights[5] = {1.0, -2.0, 3.5, -1.0, 0.0};
  double even_weights[8] = {7.0, -4.5, 8.0, -11.5, 0.0, 0.0, 0.0, 1.0};

  ts::MA<5> odd_model(odd_weights, 5.0);
  ts::MA<8> even_model(even_weights);

  double null_pred[2] = {1.0, 1.0};
  double null_true[2] = {0.0, 0.0};
  double odd_model_pred[6] = {0};
  double odd_model_true[6] = {4.5, 12.5, 7.0, 4.0, 7.0, 5.0};
  double new_odd_model_true[6] = {12.5, 5.5, 9.25, 4.0, 6.5, 5.0};
  double even_model_pred[3] = {0};
  double even_model_true[3] = {-46.0, -17.5, 12.5};
  double new_even_model_true[3] = {-21.5, 12.5, -1.5};

  null_model.forecast(null_data, null_pred, 2);
  odd_model.forecast(odd_data, odd_model_pred, 6);
  even_model.forecast(even_data, even_model_pred, 3);

  assertNear(null_pred[0], 0.0, 0.00001);
  assertNear(null_pred[1], 0.0, 0.00001);

  for(int i=0; i<6; i++){

    assertNear(odd_model_pred[i], odd_model_true[i], 0.00001);

  }

  for(int i=0; i<3; i++){

    assertNear(even_model_pred[i], even_model_true[i], 0.00001);

  }

  odd_model.forecast(new_odd_data, odd_model_pred, 6);
  even_model.forecast(new_even_data, even_model_pred, 3);

  for(int i=0; i<6; i++){

    assertNear(odd_model_pred[i], new_odd_model_true[i], 0.00001);

  }

  for(int i=0; i<3; i++){

    assertNear(even_model_pred[i], new_even_model_true[i], 0.00001);

  }

}

void setup() {

  Serial.begin(9600);
  while(!Serial) {}

}

void loop() {

  Test::run();

}
