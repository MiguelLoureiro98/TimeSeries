# Example - Multi-step ahead forecasting

This example showcases the library's multi-step forecasting capabilities. 

A 6<sup>th</sup> order Moving Average model is used to forecast the next three measurement values. Each of these forecasts is then compared to the corresponding sensor measurement (i.e. the one-step ahead value is compared to the next sensor measurement, and so on and so forth).

## Example code

```cpp
/*****************************************************************************

  This example illustrates how to use the library's MA template class to 
  create a simple Moving Average model of order 6 and use it to forecast
  up to three time steps ahead.

  Note: the weights and constant used in this example are completely
    arbitrary. This model will most likely perform poorly, and is used here
    for purely illustrative purposes.

*****************************************************************************/

#include <TimeSeries.h>
#include <stdint.h>

constexpr double Ts = 2000.0; // Define sampling time (2 seconds = 2000 ms).
double time = millis(); // Initial time instant.
constexpr uint8_t input_pin = A0; // Define input pin.

double constant = 2.0; // Define model intercept.
double weights[6] = {1.0, -5.0, 2.5, -1.5, 4.0, -6.0}; // Define model weights.
double data[6] = {0}; // Initialise data array.
double predictions[3] = {0}; // Initialise predictions array for one-step ahead forecasting.

ts::MA<6> model(weights, constant); // Instantiate the model. An MA(6) model will be used in this example.

void setup() {

  // Initial setup.
  Serial.begin(9600);
  pinMode(input_pin, INPUT);

}

void loop() {
  
  double current_time = millis(); // Check the current time.
  double forecast_3_steps_earlier[3] = {0}; // Array used to store the forecasts made three time-steps ago.
  double forecast_2_steps_earlier[3] = {0}; // Array used to store the forecasts made two time-steps ago.
  double forecast_1_step_earlier[3] = {0}; // Array used to store the forecasts made one time-step ago.

  // If enough time has passed, collect another sample.
  if(current_time - time >= Ts){

    // Prepare the data array to receive a measurement. 
    // Every sample must be shifted by one lag, as we have advanced one lag (i.e. time instant) into the future. 
    // The oldest measurement is discarded.
    for(size_t i=5; i<1; i--){

      data[i-1] = data[i];

    }

    // Collect a new data sample from the sensor. Update the data array (the most recent sample must come last).
    data[5] = analogRead(input_pin);

    // Three-step ahead forecast using the most recent data. A prediction horizon of 3 must be specified.
    model.forecast(data, predictions, 3);

    // Print the most recent measurement and the corresponding forecasts to the serial plotter.
    Serial.print("Sensor_measurement");
    Serial.print(data[5]); // Sensor measurement.
    Serial.print(",");
    Serial.print("3-steps earlier forecast");
    Serial.print(forecast_3_steps_earlier[2]); // 3-step ahead forecast made 3 time-steps ago.
    Serial.print(",");
    Serial.print("2-steps earlier forecast");
    Serial.print(forecast_2_steps_earlier[1]); // 2-step ahead forecast made 2 time-steps ago.
    Serial.print(",");
    Serial.print("1-step earlier forecast");
    Serial.println(forecast_1_step_earlier[0]); // 1-step ahead forecast made 1 time-step ago.

    // As we move forward by one time-step, the storage arrays must be shifted back in time (i.e. the forecasts made in the last time-step are shifted to the second-to-last time-step, etc.).
    for(size_t j=0; j<3; j++){

      forecast_3_steps_earlier[j] = forecast_2_steps_earlier[j];
      forecast_2_steps_earlier[j] = forecast_1_step_earlier[j];
      forecast_1_step_earlier[j] = predictions[j];

    }

    // Update reference time instant.
    time = millis();

  }

}
```

## See also

- [One-step ahead forecasting](basics.md): perform one-step ahead forecasting;
- [Change model parameters](change_param.md): change model parameters after initialising a model.