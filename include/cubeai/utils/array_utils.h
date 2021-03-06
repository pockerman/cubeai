#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include "cubeai/base/cubeai_types.h"
#include "cubeai/base/cubeai_consts.h"
#include "cubeai/base/cubeai_config.h"
#include "cubeai/utils/cubeai_concepts.h"

#ifdef CUBEAI_DEBUG
#include <cassert>
#endif

#include <vector>
#include <algorithm> // for std::max/min_element
#include <iterator> // for std::distance
#include <cmath> // std::pow

namespace cubeai {

///
/// \brief bin_index. Compute sequnce[i - 1] <= x sequnce[i] and returns the
/// index. Sequence should be sorted
///
template<typename SequenceTp>
uint_t bin_index(const typename SequenceTp::value_type& x, const SequenceTp& sequence){

    if(sequence.size() <= 1){
        return CubeAIConsts::invalid_size_type();
    }

    auto index = 1;
    auto begin = sequence.begin();
    auto prev_val = *begin;
    ++begin;
    auto end = sequence.end();

    for(; begin != end; ++begin, ++index){

        auto current_val = *begin;

        if( (prev_val <= x) && (x < current_val)){
            return index;
        }

        prev_val = current_val;
    }

    return CubeAIConsts::invalid_size_type();
}

///
///
///
template<utils::concepts::float_or_integral_vector VectorType>
VectorType
exponentiate(const VectorType& vec){
    VectorType vec_exp(vec.size());
    uint_t counter = 0;
    static auto func = [&counter](const auto& data){
        return std::pow(data, counter++);
    };
    std::transform(vec.begin(), vec.end(),
                   vec_exp.begin(), func);
    return vec_exp;
}


///
/// \brief Returns the index of the element that has the maximum
/// value in the array. Implementation taken from
/// http://www.jclay.host/dev-journal/simple_cpp_argmax_argmin.html
///
template <typename VectorType>
uint_t arg_max(const VectorType& vec) {
  return static_cast<uint_t>(std::distance(vec.begin(), max_element(vec.begin(), vec.end())));
}


///
/// \brief Returns the index of the element that has the minimum
/// value in the array. Implementation taken from
/// http://www.jclay.host/dev-journal/simple_cpp_argmax_argmin.html
///
template <typename VectorType>
uint_t arg_min(const VectorType& vec) {
  return static_cast<uint_t>(std::distance(vec.begin(), min_element(vec.begin(), vec.end())));
}

template<typename T>
std::vector<uint_t> max_indices(const DynVec<T>& vec){

    // find max value
    auto max_val = blaze::max(vec);

    auto result = std::vector<uint_t>();
    //auto counter = 0;

    for(uint_t i=0; i<vec.size(); ++i){
        T value = vec[i];
        if(value == max_val){
            result.push_back(i);
        }
    }

    return result;
}

///
/// \brief Returns the indices of vec
/// where the maximum value in vec occurs
///
template<typename VecTp>
std::vector<uint_t> max_indices(const VecTp& vec){

    // find max value
    auto max_val = std::max_element(vec.begin(), vec.end());

    auto result = std::vector<uint_t>();
    auto counter = 0;

    std::for_each(vec.begin(), vec.end(),
                  [&](auto val){
        if(val == max_val){
            result.push_back(counter);
        }
        ++counter;
    });

    return result;
}


template<typename T>
std::vector<T> extract_subvector(const std::vector<T>& vec, uint_t end){

#ifdef CUBEAI_DEBUG
    assert(end <= vec.size() && "Invalid end index");
#endif

    return std::vector<real_t>(vec.begin(), vec.begin() + end);

}

}

#endif // ARRAY_UTILS_H
