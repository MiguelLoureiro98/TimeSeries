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
*
* @file TimeSeries.h
*
* @author Miguel Loureiro
*
* @brief This file contains all the class definitions for the TimeSeries
*   library.
*
* @copyright Copyright (c) 2024 Miguel Loureiro
*
******************************************************************************/

#ifndef __TIME_SERIES_H__
#define __TIME_SERIES_H__

#include <stdint.h>

/*******************************************************************************
*
* @namespace ts 
*
* @brief The library's namespace.
* 
* @details Namespace containing the classes provided by the TimeSeries library,
*   namely the AR and MA classes.
* 
********************************************************************************/
namespace ts{

    /*******************************************************************************
    *
    * @class AR model class template.
    * 
    * @brief Template for generating AR model classes.
    * 
    * @details This class template implements the operations associated with an
    *   autoregressive (AR) model. These include setting the model's weights and
    *   constant and forecasting future values.
    * 
    * @tparam p Order of the AR model.
    * 
    ********************************************************************************/
    template<int p>
    class AR{

        public:

            /*******************************************************************************
            * 
            * @brief Default class constructor.
            * 
            ********************************************************************************/
            AR() = default;

            /*******************************************************************************
            * 
            * @brief Class constructor.
            * 
            * @param[in] weights Array containing the model's weights.
            * @param[in] constant The model's intercept value.
            * 
            ********************************************************************************/
            AR(double (&weights)[p], double constant=0.0) : _constant(constant){

                for(size_t i=0; i<p; i++){

                    _weights[i] = weights[i];
                    
                }

            };

            /*******************************************************************************
            * 
            * @brief Get the current weights.
            * 
            * @return Array of model weights.
            * 
            ********************************************************************************/
            double* get_weights() const { return _weights; };

            /*******************************************************************************
            * 
            * @brief Get the current intercept.
            * 
            * @return Model intercept.
            * 
            ********************************************************************************/
            double get_constant() const { return _constant; };
            
            /*******************************************************************************
            * 
            * @brief Set model weights.
            * 
            * @param[in] weights Array of new weights.
            * 
            ********************************************************************************/
            void set_weights(double (&weights)[p]){ 
                
                for(size_t i=0; i<p; i++){

                    _weights[i] = weights[i];

                }
                
                return; 
            };

            /*******************************************************************************
            * 
            * @brief Set model intercept value.
            * 
            * @param[in] constant New intercept value.
            * 
            ********************************************************************************/
            void set_constant(double constant){

                _constant = constant;

                return;
            };

            /*******************************************************************************
            * 
            * @brief Compute model forecasts.
            * 
            * @details This method can be used to compute h step ahead forecasts, where h is
            *   the forecast horizon. Its time complexity is O(ph), where p is the order
            *   of the model and h is the forecast horizon.
            * 
            * @param[in] data Input data. The most recent data point must come last, and the 
            *   oldest one first.
            * @param[out] predictions Model forecasts. The prediction that goes further into
            *   the future comes last.
            * @param[in] horizon Forecast horizon. Optional parameter. Default=1.
            * 
            * @note The length l of the predictions array must satisfy the following 
            *   condition: l >= horizon. If l > horizon, the values in the first l 
            *   positions of the array will be overwritten.
            *
            * @warning This method resets the predictions array before storing any 
            *   prediction. This is to make sure that model predictions are not affected by
            *   a non-zero value in the array. Keep this in mind when supplying and 
            *   retrieving a predictions array.
            *
            ********************************************************************************/
            void forecast(double (&data)[p], double* predictions, int horizon=1){

                // Initialise indices and buffer.

                _writing_index = 0;
                _length_index = p;

                for(size_t i=0; i<p; i++){

                    _data_buffer[i] = data[i];

                }

                for(size_t i=0; i<horizon; i++){

                    predictions[i] = 0.0;

                }

                // Compute forecasts. Most recent data point last.

                for(size_t i=0; i<horizon; i++){

                    for(size_t j=_writing_index; j<_length_index; j++){

                        predictions[i] += _weights[j - _writing_index] * _data_buffer[j % p];

                    }

                    predictions[i] += _constant;
                    _data_buffer[i % p] = predictions[i]; // What's the right buffer index?
                    _writing_index++;
                    _length_index++;

                }

                return;

            };

        private:

            double _weights[p] = {0};
            double _constant = 0.0;
            double _data_buffer[p] = {0};
            size_t _writing_index = 0;
            size_t _length_index = 0;

    };

    /*******************************************************************************
    *
    * @class MA model class template.
    * 
    * @brief Template for generating MA model classes.
    * 
    * @details This class template implements the operations associated with a
    *   moving average (MA) model. These include setting the model's weights and
    *   constant and forecasting future values.
    * 
    * @tparam q Order of the MA model.
    * 
    ********************************************************************************/
    template<int q>
    class MA{

        public:

            /*******************************************************************************
            * 
            * @brief Default class constructor.
            * 
            ********************************************************************************/
            MA() = default;

            /*******************************************************************************
            * 
            * @brief Class constructor.
            * 
            * @details This constructor can be used to specify model parameters.
            * 
            * @param[in] weights Array containing the model's weights.
            * @param[in] constant The model's intercept value.
            * 
            ********************************************************************************/
            MA(double (&weights)[q], double constant=0.0) : _constant(constant){

                for(size_t i=0; i<q; i++){

                    _weights[i] = weights[i];

                }

            };

            /*******************************************************************************
            * 
            * @brief Get the current weights.
            * 
            * @return Array of model weights.
            * 
            ********************************************************************************/
            double* get_weights() const { return _weights; };
            
            /*******************************************************************************
            * 
            * @brief Get the current intercept.
            * 
            * @return Model intercept.
            * 
            ********************************************************************************/
            double get_constant() const { return _constant; };

            /*******************************************************************************
            * 
            * @brief Set model weights.
            * 
            * @param[in] weights Array of new weights.
            * 
            ********************************************************************************/
            void set_weights(double (&weights)[q]){ 
                
                for(size_t i=0; i<q; i++){

                    _weights[i] = weights[i];

                }
                
                return; 
            };

            /*******************************************************************************
            * 
            * @brief Set model intercept value.
            * 
            * @param[in] constant New intercept value.
            * 
            ********************************************************************************/
            void set_constant(double constant){

                _constant = constant;

                return;
            };

            /*******************************************************************************
            * 
            * @brief Compute model forecasts.
            * 
            * @details This method can be used to compute h step ahead forecasts, where h is
            *   the forecast horizon. Its time complexity is O(qh), where q is the order
            *   of the model and h is the forecast horizon.
            * 
            * @param[in] data Input data. The most recent data point must come last, and the 
            *   oldest one first.
            * @param[out] predictions Model forecasts. The prediction that goes further into
            *   the future comes last.
            * @param[in] horizon Forecast horizon. Optional parameter. Default=1.
            * 
            * @note The length l of the predictions array must satisfy the following 
            *   condition: l >= horizon. If l > horizon, the values in the first l 
            *   positions of the array will be overwritten.
            *
            * @warning This method resets the predictions array before storing any 
            *   prediction. This is to make sure that model predictions are not affected by
            *   a non-zero value in the array. Keep this in mind when supplying and 
            *   retrieving a predictions array.
            ********************************************************************************/
            void forecast(double (&data)[q], double* predictions, int horizon=1){

                // Initialise indices and buffer. "Reset" the offset of the array containing previous predictions.

                _writing_index = 0;
                _length_index = q;
                _pred_offset = _pred_offset % q;

                for(size_t i=0; i<q; i++){

                    _data_buffer[i] = data[i] - _pred_buffer[(i + _pred_offset) % q];

                }

                for(size_t i=0; i<horizon; i++){

                    predictions[i] = 0.0;

                }

                // Compute forecasts. Most recent data point last.

                for(size_t i=0; i<horizon; i++){

                    for(size_t j=_writing_index; j<_length_index; j++){

                        predictions[i] += _weights[j - _writing_index] * _data_buffer[j % q];

                    }

                    predictions[i] += _constant;
                    
                    if(i == 0){

                        _pred_buffer[_pred_offset % q] = predictions[i];
                        _pred_offset++;

                    }

                    _data_buffer[i % q] = 0.0;
                    _writing_index++;
                    _length_index++;

                }

                return;

            };

        private:

            double _weights[q] = {0};
            double _constant = 0.0;
            double _data_buffer[q] = {0};
            double _pred_buffer[q] = {0};
            size_t _writing_index = 0;
            size_t _length_index = 0;
            size_t _pred_offset = 0;

    };

};

#endif