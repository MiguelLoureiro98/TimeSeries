

# File TimeSeries.h

[**File List**](files.md) **>** [**src**](dir_68267d1309a1af8e8297ef4c3efbcdba.md) **>** [**TimeSeries.h**](TimeSeries_8h.md)

[Go to the documentation of this file](TimeSeries_8h.md)


```C++


#ifndef __TIME_SERIES_H__
#define __TIME_SERIES_H__

#include <stdint.h>


namespace ts{


    template<int p>
    class AR{

        public:


            AR() = default;


            AR(double (&weights)[p], double constant=0.0) : _constant(constant){

                for(size_t i=0; i<p; i++){

                    _weights[i] = weights[i];
                    
                }

            };


            double* get_weights() const { return _weights; };


            double get_constant() const { return _constant; };
            

            void set_weights(double (&weights)[p]){ 
                
                for(size_t i=0; i<p; i++){

                    _weights[i] = weights[i];

                }
                
                return; 
            };


            void set_constant(double constant){

                _constant = constant;

                return;
            };


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


    template<int q>
    class MA{

        public:


            MA() = default;


            MA(double (&weights)[q], double constant=0.0) : _constant(constant){

                for(size_t i=0; i<q; i++){

                    _weights[i] = weights[i];

                }

            };


            double* get_weights() const { return _weights; };
            

            double get_constant() const { return _constant; };


            void set_weights(double (&weights)[q]){ 
                
                for(size_t i=0; i<q; i++){

                    _weights[i] = weights[i];

                }
                
                return; 
            };


            void set_constant(double constant){

                _constant = constant;

                return;
            };


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
```


