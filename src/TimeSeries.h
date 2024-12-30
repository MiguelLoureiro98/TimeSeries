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
#include "Gaussian.h"

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
            * @brief Compute forecasts.
            * 
            * @details This method can be used to compute h step ahead forecasts, where h is
            *   the forecast horizon. Its time complexity is O(ph**2), where p is the order
            *   of the model and h is the forecast horizon.
            * 
            * @param[in] data Data points to feed into the model. The most recent data point 
            *   must come last, and the oldest one first.
            * @param[out] predictions Model forecasts. The prediction that goes further into
            *   the future comes last.
            * @param[in] horizon Forecast horizon.
            * 
            ********************************************************************************/
            void forecast(double (&data)[p], double* predictions, int horizon=1){

                // Initialise indices and buffer.

                _wrinting_index = 0;
                _length_index = p;

                for(size_t i=0; i<p; i++){

                    _data_buffer[i] = data[i];

                }

                for(size_t i=0; i<horizon; i++){

                    predictions[i] = 0.0;

                }

                // Compute forecasts. Most recent data point last.

                for(size_t i=0; i<horizon; i++){

                    for(size_t j=_wrinting_index; j<_length_index; j++){

                        predictions[i] += _weights[j - _wrinting_index] * _data_buffer[j % p];

                    }

                    predictions[i] += _constant;
                    _data_buffer[i % p] = predictions[i]; // What's the right buffer index?
                    _wrinting_index++;
                    _length_index++;

                }

                return;

            };

        private:

            double _weights[p] = {0};
            double _constant = 0.0;
            double _data_buffer[p] = {0};
            size_t _wrinting_index = 0;
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
            * @param[in] sigma2 Estimated variance.
            * 
            ********************************************************************************/
            MA(double (&weights)[q], double constant=0.0, double sigma2=0.0) : _constant(constant), _sigma2(sigma2){

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
            * @brief Get the current variance.
            * 
            * @return Variance.
            * 
            ********************************************************************************/
            double get_variance() const { return _sigma2; };

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
            * @brief Set variance.
            * 
            * @param[in] constant New variance.
            * 
            ********************************************************************************/
            void set_variance(double sigma2){

                _sigma2 = sigma2;

                return;
            };

            /*******************************************************************************
            * 
            * @brief Compute forecasts.
            * 
            * @details This method can be used to compute h step ahead forecasts, where h is
            *   the forecast horizon. Its time complexity is O(qh**2), where q is the order
            *   of the model and h is the forecast horizon.
            * 
            * @param[out] predictions Model forecasts. The prediction that goes further into
            *   the future comes last.
            * @param[in] horizon Forecast horizon.
            * 
            ********************************************************************************/
            void forecast(double* predictions, int horizon=1){

                // Initialise indices and buffer.

                _wrinting_index = 0;
                _length_index = q;
                Gaussian dist(0, _sigma2);

                for(size_t i=0; i<q; i++){

                    _data_buffer[i] = dist.random();

                }

                for(size_t i=0; i<horizon; i++){

                    predictions[i] = 0.0;

                }

                // Compute forecasts. Most recent data point last.

                for(size_t i=0; i<horizon; i++){

                    for(size_t j=_wrinting_index; j<_length_index; j++){

                        predictions[i] += _weights[j - _wrinting_index] * _data_buffer[j % q];

                    }

                    predictions[i] += _constant;
                    _data_buffer[i % q] = dist.random(); // What's the right buffer index?
                    _wrinting_index++;
                    _length_index++;

                }

                return;

            };

        private:

            double _weights[q] = {0};
            double _constant = 0.0;
            double _sigma2 = 0.0;
            double _data_buffer[q] = {0};
            size_t _wrinting_index = 0;
            size_t _length_index = 0;

    };

};

#endif