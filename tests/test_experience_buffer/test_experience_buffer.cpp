#include "cubeai/base/cubeai_config.h"

#ifdef USE_PYTORCH

#include "cubeai/rl/algorithms/actor_critic/a2c.h"
#include "gymfcpp/cart_pole_env.h"


#include <torch/torch.h>
#include <boost/python.hpp>

#include <gtest/gtest.h>
#include <vector>

namespace{

using cubeai::rl::algos::ac::A2CConfig;
using cubeai::rl::algos::ac::A2C;
using gymfcpp::CartPole;
using gymfcpp::obj_t;

using cubeai::real_t;
using cubeai::uint_t;
using cubeai::torch_tensor_t;

class DummyEnv
{

public:


    DummyEnv(obj_t gym_namespace);

    uint_t n_workers()const noexcept{return 1;}


private:

    CartPole env_;


};

DummyEnv::DummyEnv(obj_t gym_namespace)
    :
      env_("v0", gym_namespace, true)

{}

class PolicyImpl: public torch::nn::Module
{
public:


    PolicyImpl();

    torch_tensor_t forward(torch_tensor_t){}

    //template<typename StateTp>
    //std::tuple<uint_t, real_t> act(const StateTp& state);
    //
    //template<typename LossValuesTp>
    //void update_policy_loss(const LossValuesTp& vals);
    //
    //void step_backward_policy_loss();
    //
    //torch_tensor_t compute_loss(){return loss_;}

private:

   torch::nn::Linear fc1_;
   torch::nn::Linear fc2_;

   // placeholder for the loss
   torch_tensor_t loss_;

};

PolicyImpl::PolicyImpl()
    :
      fc1_(nullptr),
      fc2_(nullptr)
{}

TORCH_MODULE(Policy);

}


TEST(TestA2C, Test_Constructor) {

    Py_Initialize();
    auto gym_module = boost::python::import("__main__");
    auto gym_namespace = gym_module.attr("__dict__");

    auto env = DummyEnv(gym_namespace);

    A2CConfig config;

    PolicyImpl policy;
    A2C<DummyEnv, PolicyImpl> agent(config, policy);

}

TEST(TestA2C, Test_on_training_episode) {

    Py_Initialize();
    auto gym_module = boost::python::import("__main__");
    auto gym_namespace = gym_module.attr("__dict__");

    auto env = DummyEnv(gym_namespace);

    A2CConfig config;

    PolicyImpl policy;
    A2C<DummyEnv, PolicyImpl> agent(config, policy);
    agent.on_training_episode(env, static_cast)

}
#endif
