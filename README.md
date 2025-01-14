# TimeSeries

TimeSeries is an Arduino library for time series forecasting.

The library provides support for well-known statistical forecasting models, such as autoregressive models and moving average models. Recursive multi-step forecasting is supported.

## Features

- **Dependency-free**: at the moment, this library is completely dependency-free;
- **Dynamic-memory-free**: every model provided by the library is implemented statically using templates and circular buffers;
- **Compatibility**: as it makes no use of any board-specific instructions/features, this library should be compatible with almost every Arduino board;
- **Support for multi-step forecasting**: the library supports recursive multi-step forecasting. Although only the recursive method is implemented directly, direct methods could of course be used by instantiating multiple models. See Sahoo et al. [1](1) for more details on these multi-step forecasting methods.

[1] Debashis Sahoo, Naveksha Sood, Usha Rani, George Abraham, Varun Dutt, and AD Dileep. Comparative analysis of multi-step time-series forecasting for network load dataset. In 2020 11th International Conference on Computing, Communication and Networking Technologies (ICCCNT), pages 1–7. IEEE, 2020.

## Supported models

TimeSeries currently supports the following models:

| Model | Class | Description | One-step forecasting | Multi-step forecasting |
| :----: | :----: | :----: | :----: | :----: |
| AR(p) | AR | An autoregressive model of order p. | Fully tested. | Fully tested. |
| MA(q) | MA | A moving average model of order q. | Fully tested. | Fully tested. |

When forecasting using an n^th-order^ model and a forecasting horizon of h, the time and memory complexities of the models are as follows:

| Model | Time complexity | Memory complexity |
| :----: | :----: | :----: |
| AR | O(nh) | O(n) |
| MA | O(nh) | O(n) |

**Note**: these values were simply derived from the code, and are thus purely indicative. Computational experiments will be conducted in the future.

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
- **Support for online training** (for some models, at least).

## Installation

TimeSeries will soon be submitted to the official Arduino library index. Once it is accepted, it will be available for download using the Arduino IDE. Alternatively, once the first release is published, the library will be available for [download directly from Github](https://www.youtube.com/watch?v=WuqEAUirXw0).

## Documentation

An official documentation website will soon be made available.

## Licence

This library is licenced under the [Apache 2.0 licence](LICENSE).

## About

TimeSeries was developed and is currently maintained by Miguel Loureiro, a mechanical engineer who specialises in control systems, machine learning, and optimisation.
