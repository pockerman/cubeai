#include "cubeai/optimization/pytorch_optimizer_factory.h"

#ifdef USE_PYTORCH

#include "cubeai/base/cubeai_types.h"

namespace cubeai{
namespace optim {
namespace pytorch{

std::unique_ptr<torch::optim::OptimizerOptions>
build_pytorch_optimizer_options(OptimzerType type, const std::map<std::string, std::any>& options){

    std::unique_ptr<torch::optim::OptimizerOptions> ptr;

    auto lr = std::any_cast<real_t>(options.find("lr")->second);

    switch(type){

        case OptimzerType::SGD:
        {

            ptr = std::make_unique<torch::optim::SGDOptions>(lr);
            break;
        }
        case OptimzerType::ADAM:
        {
            ptr = std::make_unique<torch::optim::AdamOptions>(lr);
            break;
        }
        case OptimzerType::RSPROP:
        {
            ptr = std::make_unique<torch::optim::RMSpropOptions>(lr);
            break;
        }
#ifdef CUBEAI_DEBUG
        default:
        {
          throw std::logic_error("Invalid PyTorch optimizer type");
        }
#endif
    }
    return ptr;
}


std::unique_ptr<torch::optim::Optimizer>
build_pytorch_optimizer(OptimzerType type, torch::nn::Module& model, const torch::optim::OptimizerOptions& options){

    std::unique_ptr<torch::optim::Optimizer> ptr;

    switch(type){

        case OptimzerType::SGD:
        {
        ptr = std::make_unique<torch::optim::SGD>(model.parameters(), torch::optim::SGDOptions{options.get_lr()});
            break;
        }
        case OptimzerType::ADAM:
        {
        ptr = std::make_unique<torch::optim::Adam>(model.parameters(), torch::optim::AdamOptions{options.get_lr()});
            break;
        }
        case OptimzerType::RSPROP:
        {
        ptr = std::make_unique<torch::optim::RMSprop>(model.parameters(), torch::optim::RMSpropOptions{options.get_lr()});
            break;
        }
#ifdef CUBEAI_DEBUG
        default:
        {
          throw std::logic_error("Invalid PyTorch optimizer type");
        }
#endif
    }

    return ptr;
}

}

}
}

#endif
