#ifndef Q_LEARNING_H
#define Q_LEARNING_H

#include "cubeai/base/cubeai_types.h"
#include "cubeai/rl/algorithms/td/td_algo_base.h"

#include "cubeai/base/cubeai_consts.h"
#include "cubeai/base/cubeai_config.h"

#ifdef CUBEAI_DEBUG
#include <cassert>
#endif

#include "boost/accumulators/accumulators.hpp"
#include <boost/accumulators/statistics/stats.hpp>
#include "boost/accumulators/statistics/mean.hpp"
#include "boost/bind/bind.hpp"
#include "boost/ref.hpp"

namespace cubeai {
namespace rl{
namespace algos {
namespace td {

using namespace boost::placeholders;

///
/// \brief The QLearning class. Table based implementation
/// of the Q-learning algorithm using epsilon-greedy policy.
/// The implementation also allows for exponential decay
/// of the used epsilon
///
template <typename TimeStepTp, typename ActionSelector>
class QLearning: public TDAlgoBase<TimeStepTp>
{

public:

    ///
    /// \brief env_t
    ///
    typedef typename TDAlgoBase<TimeStepTp>::env_t env_t;

    ///
    /// \brief action_t
    ///
    typedef typename TDAlgoBase<TimeStepTp>::action_t action_t;

    ///
    /// \brief state_t
    ///
    typedef typename TDAlgoBase<TimeStepTp>::state_t state_t;

    ///
    /// \brief action_selector_t
    ///
    typedef ActionSelector action_selector_t;

    ///
    /// \brief Constructor
    ///
    QLearning(uint_t n_episodes, real_t tolerance,
              real_t gamma, real_t eta, uint_t plot_f,
              env_t& env, uint_t max_num_iterations_per_episode, const ActionSelector& selector);

    ///
    /// \brief on_episode. Performs the iterations for
    /// one training episode
    ///
    virtual void on_episode()override final;

private:

    ///
    /// \brief current_score_counter_
    ///
    uint_t current_score_counter_;

    ///
    /// \brief action_selector_
    ///
    action_selector_t action_selector_;

    ///
    /// \brief update_q_table_
    /// \param action
    ///
    void update_q_table_(const action_t& action, const state_t& cstate,
                         const state_t& next_state, const  action_t& next_action, real_t reward);

};

template <typename TimeStepTp, typename ActionSelector>
QLearning<TimeStepTp, ActionSelector>::QLearning(uint_t n_episodes, real_t tolerance,
                                                 real_t gamma, real_t eta, uint_t plot_f,
                                                 env_t& env, uint_t max_num_iterations_per_episode, const ActionSelector& selector)
    :
      TDAlgoBase<TimeStepTp>(n_episodes, tolerance, gamma, eta, plot_f, max_num_iterations_per_episode, env),
      current_score_counter_(0),
      action_selector_(selector)
{}


template <typename TimeStepTp, typename ActionSelector>
void
QLearning<TimeStepTp, ActionSelector>::on_episode(){

    std::cout<<"Starting episode="<<this->current_episode_idx()<<std::endl;

    // total score for the episode
    auto score = 0.0;
    auto state = this->env_ref_().reset().observation();

    // select an action
    auto action = action_selector_(this->q_table(), state);

    uint_t itr=0;
    for(;  itr < this->max_num_iterations_per_episode(); ++itr){

        // select an action
        auto action = action_selector_(this->q_table(), state);
        if(this->is_verbose()){
            std::cout<<"Episode iteration="<<itr<<" of="<<this->max_num_iterations_per_episode()<<std::endl;
            std::cout<<"State="<<state<<std::endl;
            std::cout<<"Action="<<action<<std::endl;
        }

        // Take a on_episode
        auto step_type_result = this->env_ref_().step(action);

        auto next_state = step_type_result.observation();
        auto reward = step_type_result.reward();
        auto done = step_type_result.done();

        // accumulate score
        score += reward;

        if(!done){
            auto next_action = action_selector_(this->q_table(), state);
            update_q_table_(action, state, next_state, next_action, reward);
            state = next_state;
            action = next_action;
        }
        else{

            update_q_table_(action, state, CubeAIConsts::invalid_size_type(),
                            CubeAIConsts::invalid_size_type(), reward);

            this->tmp_scores()[current_score_counter_++] = score;

            if(current_score_counter_ >= this->plot_frequency()){
                current_score_counter_ = 0;
            }

            if(this->is_verbose()){
                std::cout<<"============================================="<<std::endl;
                std::cout<<"Break out from episode="<<this->current_episode_idx()<<std::endl;
                std::cout<<"============================================="<<std::endl;
            }

            break;
        }
    }

    // make any adjustments to the way
    // actions are selected given the experience collected
    // in the episode
    action_selector_.adjust_on_episode(this->current_episode_idx());
    if(current_score_counter_ >= this->plot_frequency()){
        current_score_counter_ = 0;
    }

    std::cout<<"Finished on_episode="<<this->current_episode_idx()<<std::endl;
}

template <typename TimeStepTp, typename ActionSelector>
void
QLearning<TimeStepTp, ActionSelector>::update_q_table_(const action_t& action, const state_t& cstate,
                                                       const state_t& next_state, const  action_t& next_action, real_t reward){
#ifdef CUBEAI_DEBUG
    assert(action < this->env_ref_().n_actions() && "Inavlid action idx");
    assert(cstate < this->env_ref_().n_states() && "Inavlid state idx");

    if(next_state != CubeAIConsts::invalid_size_type())
        assert(next_state < this->env_ref_().n_states() && "Inavlid next_state idx");

    if(next_action != CubeAIConsts::invalid_size_type())
        assert(next_action < this->env_ref_().n_actions() && "Inavlid next_action idx");
#endif

    auto q_current = this->q_table()[cstate][action];
    auto q_next = next_state != CubeAIConsts::invalid_size_type() ? blaze::max(this->q_table()[next_state]) : 0.0;
    auto td_target = reward + this->gamma() * q_next;
    this->q_table()[cstate][action] = q_current + (this->eta() * (td_target - q_current));

}



}
}
}
}

#endif // Q_LEARNING_H
