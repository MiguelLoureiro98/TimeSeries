# Welcome to the documentation of the TimeSeries library

TimeSeries is an Arduino library for time series forecasting.

The library provides support for well-known statistical forecasting models, such as autoregressive and moving average models. Recursive multi-step forecasting is supported.

## Features

- **Dependency-free**: at the moment, this library is completely dependency-free;
- **Dynamic-memory-free**: every model provided by the library is implemented statically using templates and circular buffers;
- **Compatibility**: as it makes no use of any board-specific instructions/features, this library should be compatible with almost every Arduino board;
- **Support for multi-step forecasting**: the library supports recursive multi-step forecasting. Although only the recursive method is implemented directly, direct methods could of course be used by instantiating multiple models. See Sahoo et al. [[1]](#1) for more details on these multi-step forecasting methods.

## Documentation Guide

A quick and simple installation guide is available in our [First Steps](installation.md) page.

For detailed information regarding every class, function, or method provided by the library, please refer to our [API Reference](API_ref.md).

Finally, be sure to check out our [Examples](examples/index.md) page for guidance on how to use the library.

## References

<a id="1">[1]</a> Debashis Sahoo, Naveksha Sood, Usha Rani, George Abraham, Varun Dutt, and AD Dileep. Comparative analysis of multi-step time-series forecasting for network load dataset. In 2020 11th International Conference on Computing, Communication and Networking Technologies (ICCCNT), pages 1–7. IEEE, 2020.