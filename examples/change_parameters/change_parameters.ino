/****************************************************************************   
    
    Copyright 2024 Miguel Loureiro

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

           http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
   
*****************************************************************************/

/*****************************************************************************

  This example illustrates how to change a model's weights after initialisation.

  Note: the weights and constant used in this example are completely
    arbitrary. This model will most likely perform poorly, and is used here
    for purely illustrative purposes.

*****************************************************************************/

#include <TimeSeries.h>
#include <stdint.h>

constexpr double elapsed_time = 10000.0; // Define sampling time (10 seconds = 10000 ms).
double time = millis(); // Initial time instant.

// Define initial model weights and constants.
double initial_AR_constant = 2.0;
double initial_AR_weights[1] = {-1.0};
double initial_MA_constant = -1.0;
double initial_MA_weights[1] = {3.0};

// Define new model weights and constants.
double new_AR_constant = -2.0;
double new_AR_weights[1] = {1.0};
double new_MA_constant = 1.0;
double new_MA_weights[1] = {-3.0};

// Instantiate the models using the initial weights.
ts::AR<1> ar_model(initial_AR_weights, initial_AR_constant);
ts::MA<1> ma_model(initial_MA_weights, initial_MA_constant);

void setup() {

  // Initial setup.
  Serial.begin(9600);

}

void loop() {
  
  double current_time = millis(); // Check the current time.
  double *weights = nullptr;

  // If enough time has passed, update the weights.
  if(current_time - time >= elapsed_time){

    // Print the initial AR weights and constant.
    weights = ar_model.get_weights();

    Serial.print("Old AR(1) model weight: ");
    Serial.print(weights[0]);
    Serial.print(",");
    Serial.print("Old AR(1) model constant: ");
    Serial.print(ar_model.get_constant());
    Serial.print(",");

    // Change the AR weights and constant and print them.
    ar_model.set_weights(new_AR_weights);
    ar_model.set_constant(new_AR_constant);
    weights = ar_model.get_weights();

    Serial.print("New AR(1) model weight: ");
    Serial.print(weights[0]);
    Serial.print(",");
    Serial.print("New AR(1) model constant: ");
    Serial.print(ar_model.get_constant());
    Serial.print(",");

    // Print the initial MA weights and constant.
    weights = ma_model.get_weights();

    Serial.print("Old MA(1) model weight: ");
    Serial.print(weights[0]);
    Serial.print(",");
    Serial.print("Old MA(1) model constant: ");
    Serial.print(ma_model.get_constant());
    Serial.print(",");

    // Change the MA weights and constant and print them.
    ma_model.set_weights(new_MA_weights);
    ma_model.set_constant(new_MA_constant);
    weights = ma_model.get_weights();

    Serial.print("New MA(1) model weight: ");
    Serial.print(weights[0]);
    Serial.print(",");
    Serial.print("New MA(1) model constant: ");
    Serial.print(ma_model.get_constant());
    Serial.print(",");

  }

}
