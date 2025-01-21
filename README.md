# TimeSeries

TimeSeries is an Arduino library for time series forecasting.

The library provides support for well-known statistical forecasting models, such as autoregressive and moving average models. Recursive multi-step forecasting is supported.

## Features

- **Dependency-free**: the library is completely dependency-free;
- **Dynamic-memory-free**: every model provided by the library is implemented statically using templates and circular buffers;
- **Compatibility**: as it makes no use of any board-specific instructions/features, this library should be compatible with almost every Arduino board;
- **Support for multi-step forecasting**: the library supports recursive multi-step forecasting. Although only the recursive method is implemented directly, direct methods could of course be used by instantiating multiple models. See Sahoo et al. [[1]](#1) for more details on these multi-step forecasting methods.

## Supported models

TimeSeries currently supports the following models:

| Model | Class | Description | One-step forecasting | Multi-step forecasting |
| :----: | :----: | :----: | :----: | :----: |
| AR(p) | AR | An autoregressive model of order p. | Fully tested. | Fully tested. |
| MA(q) | MA | A moving average model of order q. | Fully tested. | Fully tested. |

For more information on these models, see [[2](#2), [3](#3), [4](#4)].

When forecasting using an n<sup>th</sup> order model and a forecasting horizon of h, the time and memory complexities of the models are as follows:

| Model | Time complexity | Memory complexity |
| :----: | :----: | :----: |
| AR | O(nh) | O(2n) |
| MA | O(nh) | O(3n) |

**Note**: these values were simply derived from the code, and are thus purely indicative. Computational experiments will be conducted in the future.

## Installation

TimeSeries is available for installation via the official Arduino library index. You can therefore [download it using the Arduino IDE](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/). Alternatively, the library is available for [download directly from Github](https://www.youtube.com/watch?v=WuqEAUirXw0).

## Documentation

The official documentation is available at [https://miguelloureiro98.github.io/TimeSeries/](https://miguelloureiro98.github.io/TimeSeries/).

## Examples

Check out the following examples for some guidance on how to use the library:

- [Basic usage (one step ahead forecasting)](examples/basics/basics.ino);
- [Multi-step ahead forecasting](examples/multi_step/multi_step.ino);
- [Change model parameters](examples/change_parameters/change_parameters.ino).

## Future work

These features are currently not supported, but may be included in future versions of the library:

- **Non-stationary classical time series models** (e.g. ARIMA, SARIMA, ARCH);
- **Classical time series models with exogenous variables** (e.g. ARMAX, SARIMAX);
- **Classical control-oriented models** (e.g. CARIMA); 
- **Multivariate forecasting models** (e.g. VAR, VARIMA);
- **Time series deep learning models** (e.g. RNN, LSTM, GRU);
- **Confidence interval estimation**;
- **Prediction accuracy estimation (depending on the prediction horizon)**;
- **Support for directional forecasting**;
- **Support for interval forecasting**;
- **Support for online training** (for some models, at least);
- **Complementary Python libraries** (so the library can be used to deploy models trained in Python).

**Note**: some of these might actually result in separate libraries.

## References

<a id="1">[1]</a> Debashis Sahoo, Naveksha Sood, Usha Rani, George Abraham, Varun Dutt, and AD Dileep. Comparative analysis of multi-step time-series forecasting for network load dataset. In 2020 11th International Conference on Computing, Communication and Networking Technologies (ICCCNT), pages 1–7. IEEE, 2020.

<a id="2">[2]</a> George E.P. Box, Gwilym M. Jenkins, Gregory C. Reinsel, and Greta M. Ljung. Time series analysis: forecasting and control. John Wiley & Sons, 2015.

<a id="3">[3]</a> William W.S. Wei. Time Series Analysis: Univariate and Multivariate Methods. Addison-Wesley, 2006.

<a id="4">[4]</a> Aileen Nielsen. Practical time series analysis: Prediction with statistics and machine learning. O’Reilly Media, 2019.

## Licence

This library is licenced under the [Apache 2.0 licence](LICENSE).

## About

TimeSeries was developed and is currently maintained by Miguel Loureiro, a mechanical engineer who specialises in control systems, machine learning, and optimisation.
