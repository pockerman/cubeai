#ifndef ENVS_CONCEPTS_H
#define ENVS_CONCEPTS_H

#if __cplusplus >= 202002L

#include "cubeai/rl/worlds/discrete_world.h"
#include <type_traits>

namespace cubeai {
namespace rl {
namespace envs {

///
/// \brief The concept of discrete world
///
template<typename T>
concept discrete_world_concept = std::is_base_of<DiscreteWorldBase<typename T::time_step_type>, T>::value;

///
/// \brief The concept of a discrete action space
///
template<typename EnvTp>
concept discrete_action_space_concept = std::is_integral<typename EnvTp::action_type>::value;

///
/// \brief The concept of a discrete action space
///
template<typename EnvTp>
concept discrete_state_space_concept = std::is_integral<typename EnvTp::state_type>::value;


///
/// \brief The concept of a discrete action space
///
template<typename EnvTp>
concept has_transition_dynamics_concept = EnvTp::has_dynamics;


}

}

}
#else

static_assert (false,  "The discrete_world_concept requires C++20 support");

#endif

#endif // DISCRETE_WORLD_CONCEPT_H