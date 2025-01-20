# Example - One-step ahead forecasting

In the following example, a 5<sup>th</sup> Autoregressive model is used to forecast the future values of a measurement using past measurement data.

## Example code

```cpp
/*****************************************************************************

  This example illustrates how to use the library's AR template class to 
  create a simple Autoregressive model of order 5 and use it to obtain 
  a forecast for the next measurement value.

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
double weights[5] = {1.0, -5.0, 2.5, -1.5, 4.0}; // Define model weights.
double data[5] = {0}; // Initialise data array.
double predictions[1] = {0}; // Initialise predictions array for one-step ahead forecasting.

ts::AR<5> model(weights, constant); // Instantiate the model. An AR(5) model will be used in this example.

void setup() {

  // Initial setup.
  Serial.begin(9600);
  pinMode(input_pin, INPUT);

}

void loop() {
  
  double current_time = millis(); // Check the current time.
  double forecast = 0.0; // Variable that will contain the forecast.

  // If enough time has passed, collect another sample.
  if(current_time - time >= Ts){

    // Prepare the data array to receive a measurement. 
    // Every sample must be shifted by one lag, as we have advanced one lag (i.e. time instant) into the future. 
    // The oldest measurement is discarded.
    for(size_t i=4; i<1; i--){

      data[i-1] = data[i];

    }

    // Collect a new data sample from the sensor. Update the data array (the most recent sample must come last).
    data[4] = analogRead(input_pin);

    // One-step ahead forecast using the most recent data.
    model.forecast(data, predictions);

    // Print the most recent measurement and the corresponding forecast to the serial plotter.
    Serial.print("Sensor_measurement");
    Serial.print(data[4]);
    Serial.print(",");
    Serial.print("Forecast");
    Serial.println(forecast);

    // Store forecast so it can be plotted once another sample is collected.
    forecast = predictions[0];

    // Update reference time instant.
    time = millis();

  }

}
```

## See also

- [Multi-step ahead forecasting](multi-step.md): perform multi-step ahead forecasting using the recursive forecasting method;
- [Change model parameters](change_param.md): change model parameters after initialising a model.