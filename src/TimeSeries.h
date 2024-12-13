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

#include "Queue.h"
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
            AR(double& weights[p], double constant=0.0) : _weights(weights), _constant(constant){};

            /*******************************************************************************
            * 
            * @brief Get the current weights.
            * 
            * @return Array of model weights.
            * 
            ********************************************************************************/
            double& get_weights() const { return _weights; };

            /*******************************************************************************
            * 
            * @brief Get the current intercept.
            * 
            * @return Model intercept.
            * 
            ********************************************************************************/
            double& get_constant() const { return _constant; };
            
            /*******************************************************************************
            * 
            * @brief Set model weights.
            * 
            * @param[in] weights Array of new weights.
            * 
            ********************************************************************************/
            void set_weights(double& weights[p]){ 
                
                _weights = weights;
                
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

        private:

            double _weights[p] = {0};
            double _constant = 0.0;

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
            * @param[in] weights Array containing the model's weights.
            * @param[in] constant The model's intercept value.
            * 
            ********************************************************************************/
            MA(double& weights[q], double constant=0.0) : _weights(weights), _constant(constant){};

            /*******************************************************************************
            * 
            * @brief Get the current weights.
            * 
            * @return Array of model weights.
            * 
            ********************************************************************************/
            double& get_weights() const { return _weights; };
            
            /*******************************************************************************
            * 
            * @brief Get the current intercept.
            * 
            * @return Model intercept.
            * 
            ********************************************************************************/
            double& get_constant() const { return _constant; };

            /*******************************************************************************
            * 
            * @brief Set model weights.
            * 
            * @param[in] weights Array of new weights.
            * 
            ********************************************************************************/
            void set_weights(double& weights[q]){ 
                
                _weights = weights;
                
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

        private:

            double _weights[q] = {0};
            double _constant = 0.0;
    };

};

#endif