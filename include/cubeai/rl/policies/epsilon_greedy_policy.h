#ifndef EPSILON_GREEDY_POLICY_H
#define EPSILON_GREEDY_POLICY_H

#include "cubeai/base/cubeai_types.h"
#include "cubeai/utils/array_utils.h"
#include "cubeai/maths/matrix_utilities.h"

#include <random>
#include <cmath>

namespace cubeai {
namespace rl {
namespace policies {


///
/// \brief The EpsilonDecayOption enum. Enumerate various decaying options.
///
enum class EpsilonDecayOption{NONE, EXPONENTIAL, INVERSE_STEP, CONSTANT_RATE};

///
/// \brief The EpsilonGreedyPolicy class
///
class EpsilonGreedyPolicy
{
public:

    ///
    /// \brief EpsilonGreedyPolicy
    /// \param eps
    /// \param reduce
    /// \param min_eps
    /// \param max_eps
    ///
    explicit EpsilonGreedyPolicy(real_t eps, uint_t n_actions, EpsilonDecayOption decay_op,
                                 real_t min_eps = 0.01, real_t max_eps=1.0,  uint_t seed=0 );

    ///
    /// \brief operator()
    ///
    template<typename QMapTp>
    uint_t operator()(const QMapTp& q_map, uint_t state)const;

    ///
    ///
    ///
    template<typename VectorType>
    uint_t choose_action_index(const VectorType& values)const;

    ///
    /// \brief adjust_on_episode
    /// \param episode
    ///
    void adjust_on_episode(uint_t episode)noexcept;

    ///
    /// \brief reset
    ///
    void reset()noexcept{eps_ = eps_init_;}

    ///
    /// \brief set_epsilon_decay_factor
    /// \param eps_decay
    ///
    void set_epsilon_decay_factor(real_t eps_decay)noexcept{epsilon_decay_ = eps_decay;}

    ///
    /// \brief eps_value
    ///
    real_t eps_value()const noexcept{return eps_;}

    ///
    /// \brief set_seed
    /// \param seed
    ///
    void set_seed(const uint_t seed)noexcept{seed_ = seed;}

private:

    real_t eps_init_;
    real_t eps_;
    real_t min_eps_;
    real_t max_eps_;
    real_t epsilon_decay_;
    uint_t n_actions_;
    uint_t seed_;
    EpsilonDecayOption decay_op_;
};

EpsilonGreedyPolicy::EpsilonGreedyPolicy(real_t eps, uint_t n_actions, EpsilonDecayOption decay_op,
                                         real_t min_eps, real_t max_eps,  uint_t seed)
    :
      eps_init_(eps),
      eps_(eps),
      min_eps_(min_eps),
      max_eps_(max_eps),
      epsilon_decay_(0.01),
      n_actions_(n_actions),
      seed_(seed),
      decay_op_(decay_op)
{}

template<typename QMapTp>
uint_t
EpsilonGreedyPolicy::operator()(const QMapTp& q_map, uint_t state)const{

    const auto& actions = q_map.find(state)->second;

    //std::random_device rd;
    std::mt19937 gen(seed_); //rd());

    // generate a number in [0, 1]
    std::uniform_real_distribution<> real_dist_(0.0, 1.0);

    if(real_dist_(gen) > eps_){
        // select greedy action with probability 1 - epsilon
        return blaze::argmax(actions);
    }

    //std::mt19937 another_gen(seed_);
    std::uniform_int_distribution<> distrib_(0,  n_actions_ - 1);
    return distrib_(gen);
}

template<>
uint_t
EpsilonGreedyPolicy::operator()(const DynMat<real_t>& q_map, uint_t state)const{

    const DynVec<real_t> actions = maths::get_row(q_map, state);
    std::mt19937 gen(seed_);

    // generate a number in [0, 1]
    std::uniform_real_distribution<> real_dist_(0.0, 1.0);

    if(real_dist_(gen) > eps_){
        // select greedy action with probability 1 - epsilon
        return blaze::argmax(actions);
    }

    //std::mt19937 another_gen(seed_);
    std::uniform_int_distribution<> distrib_(0,  n_actions_ - 1);
    return distrib_(gen);
}

template<typename VectorType>
uint_t
EpsilonGreedyPolicy::choose_action_index(const VectorType& values)const{

    std::mt19937 gen(seed_);

    // generate a number in [0, 1]
    std::uniform_real_distribution<> real_dist_(0.0, 1.0);

    if(real_dist_(gen) > eps_){
        // select greedy action with probability 1 - epsilon
        return arg_max(values);
    }

    //std::mt19937 another_gen(seed_);
    std::uniform_int_distribution<> distrib_(0,  n_actions_ - 1);
    return distrib_(gen);
}

void
EpsilonGreedyPolicy::adjust_on_episode(uint_t episode)noexcept{

    if(decay_op_ == EpsilonDecayOption::NONE)
        return;

    if(decay_op_  == EpsilonDecayOption::INVERSE_STEP ){

        if(episode == 0){
            episode = 1;
        }

        // there are various methods to do epsilon
        // reduction
        eps_ = 1.0 / episode;

        if(eps_ < min_eps_){
            eps_ = min_eps_;
        }
    }
    else if(decay_op_ == EpsilonDecayOption::EXPONENTIAL){
        eps_ = min_eps_ + (max_eps_ - min_eps_)*std::exp(-epsilon_decay_ * episode);
    }
    else if(decay_op_ == EpsilonDecayOption::CONSTANT_RATE){

        eps_ -= epsilon_decay_;

        if(eps_ < min_eps_){
            eps_ = min_eps_;
        }

    }
}

}
}
}

#endif // EPSILON_GREEDY_POLICY_H
