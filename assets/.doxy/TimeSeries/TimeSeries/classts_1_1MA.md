

# Class ts::MA

**template &lt;int q&gt;**



[**ClassList**](annotated.md) **>** [**ts**](namespacets.md) **>** [**MA**](classts_1_1MA.md)



_template._ [More...](#detailed-description)






































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**MA**](#function-ma-12) () = default<br>_Default class constructor._  |
|   | [**MA**](#function-ma-22) (double(&) weights, double constant=0.0) <br>_Class constructor._  |
|  void | [**forecast**](#function-forecast) (double(&) data, double \* predictions, int horizon=1) <br>_Compute model forecasts._  |
|  double | [**get\_constant**](#function-get_constant) () const<br>_Get the current intercept._  |
|  double \* | [**get\_weights**](#function-get_weights) () const<br>_Get the current weights._  |
|  void | [**set\_constant**](#function-set_constant) (double constant) <br>_Set model intercept value._  |
|  void | [**set\_weights**](#function-set_weights) (double(&) weights) <br>_Set model weights._  |




























## Detailed Description


Template for generating [**MA**](classts_1_1MA.md) model classes.


This class template implements the operations associated with a moving average ([**MA**](classts_1_1MA.md)) model. These include setting the model's weights and constant and forecasting future values.




**Template parameters:**


* `q` Order of the [**MA**](classts_1_1MA.md) model. 




    
## Public Functions Documentation




### function MA [1/2]

_Default class constructor._ 
```C++
ts::MA::MA () = default
```




<hr>



### function MA [2/2]

_Class constructor._ 
```C++
inline ts::MA::MA (
    double(&) weights,
    double constant=0.0
) 
```



This constructor can be used to specify model parameters.




**Parameters:**


* `weights` Array containing the model's weights. 
* `constant` The model's intercept value. 




        

<hr>



### function forecast 

_Compute model forecasts._ 
```C++
inline void ts::MA::forecast (
    double(&) data,
    double * predictions,
    int horizon=1
) 
```



This method can be used to compute h step ahead forecasts, where h is the forecast horizon. Its time complexity is O(qh), where q is the order of the model and h is the forecast horizon.




**Parameters:**


* `data` Input data. The most recent data point must come last, and the oldest one first. 
* `predictions` Model forecasts. The prediction that goes further into the future comes last. 
* `horizon` Forecast horizon. Optional parameter. Default=1.



**Note:**

The length l of the predictions array must satisfy the following condition: l &gt;= horizon. If l &gt; horizon, the values in the first l positions of the array will be overwritten.




**Warning:**

This method resets the predictions array before storing any prediction. This is to make sure that model predictions are not affected by a non-zero value in the array. Keep this in mind when supplying and retrieving a predictions array. 





        

<hr>



### function get\_constant 

_Get the current intercept._ 
```C++
inline double ts::MA::get_constant () const
```





**Returns:**

Model intercept. 





        

<hr>



### function get\_weights 

_Get the current weights._ 
```C++
inline double * ts::MA::get_weights () const
```





**Returns:**

Array of model weights. 





        

<hr>



### function set\_constant 

_Set model intercept value._ 
```C++
inline void ts::MA::set_constant (
    double constant
) 
```





**Parameters:**


* `constant` New intercept value. 




        

<hr>



### function set\_weights 

_Set model weights._ 
```C++
inline void ts::MA::set_weights (
    double(&) weights
) 
```





**Parameters:**


* `weights` Array of new weights. 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `src/TimeSeries.h`

