# Supported models

TimeSeries currently supports the following models:

| Model | Class | Description | One-step forecasting | Multi-step forecasting |
| :----: | :----: | :----: | :----: | :----: |
| AR(p) | [AR](TimeSeries/classts_1_1AR.md) | An autoregressive model of order p. | Fully tested. | Fully tested. |
| MA(q) | [MA](TimeSeries/classts_1_1MA.md) | A moving average model of order q. | Fully tested. | Fully tested. |

For more information on these models, see [[1](#1), [2](#2), [3](#3)].

When forecasting using an n<sup>th</sup> order model and a forecasting horizon of h, the time and memory complexities of the models are as follows:

| Model | Time complexity | Memory complexity |
| :----: | :----: | :----: |
| AR | O(nh) | O(2n) |
| MA | O(nh) | O(3n) |

**Note**: these values were simply derived from the code, and are thus purely indicative. Computational experiments will be conducted in the future.

## References

<a id="1">[1]</a> George E.P. Box, Gwilym M. Jenkins, Gregory C. Reinsel, and Greta M. Ljung. Time series analysis: forecasting and control. John Wiley & Sons, 2015.

<a id="2">[2]</a> William W.S. Wei. Time Series Analysis: Univariate and Multivariate Methods. Addison-Wesley, 2006.

<a id="3">[3]</a> Aileen Nielsen. Practical time series analysis: Prediction with statistics and machine learning. O’Reilly Media, 2019.