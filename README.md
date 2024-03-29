# cubeAI

CubeAI is a C++ library containing implementations of various reinforcement learning, filtering and planning algorithms.
The library documentation (under development) can be found here <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/">CubeAI</a>
The Python flavor of the library can be found at <a href="https://github.com/pockerman/py_cube_ai">PyCubeAI</a>. 

The following is an indicative list of examples. More tutorials can be found at <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/">CubeAI</a>.
 

## Examples

### Reinforcement learning

- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_0.html">Example 0: DummyAgent on  ```MountainCar-v0```</a>
- <a href="examples/example_1/example_1.cpp">Example 1: Toy Markov chain</a>
- <a href="examples/example_2/example_2.cpp">Example 2: Multi-armed bandit with epsilon-greedy policy</a>
- <a href="examples/example_3/example_3.cpp">Example 3: Multi-armed bandit with soft-max policy</a>
- <a href="examples/example_4/example_4.cpp">Example 4: Advertisement placement</a>
- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_6.html">Example 6: Iterative policy evaluation on ```FrozenLake-v0```</a>
- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_7.html">Example 7: Policy iteration on ```FrozenLake-v0```</a>
- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_8.html">Example 8: Value iteration on ```FrozenLake-v0```</a>
- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_9.html">Example 9: SARSA on ```CliffWalking-v0```</a>
- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_10.html">Example 10: Q-learning on ```CliffWalking-v0```</a>
- <a href="examples/example_14/example_14.cpp">Example 14: Expected SARSA on ```CliffWalking-v0```</a>
- <a href="examples/example_15/example_15.cpp">Example 15: Approximate Monte Carlo on ```MountainCar-v0```</a>
- <a href="examples/example_16/example_16.cpp">Example 16: Monte Carlo tree search on ```Taxi-v3```</a>
- <a href="examples/example_17/example_17.cpp">Example 17: A* search on a road network  from Open Street Map data</a> 
- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_18.html">Example 18: Double Q-learning on  ```CartPole-v0``` </a> 

### Path planning

- <a href="#">Example 19: Path planning with rapidly-exploring random trees (TODO)</a> 
- <a href="#">Example 20: Path planning with dynamic windows (TODO) </a>   

### PyTorch based examples

- <a href="examples/example_11/example_11.cpp">Example 11: Simple linear regression</a>
- <a href="examples/example_12/example_12.cpp">Example 12: DQN on ```CartPole-v0```</a>
- <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/ExamplesCpp/rl/rl_example_13.html">Example 13: Reinforce algorithm on ```CartPole-v0```</a>
- <a href="examples/example_21/example_21.cpp">Example 21: Simple logistic regression</a>

## Installation

The cubeai library has a host of dependencies:
Installation instructions and dependencies can be found <a href="https://pockerman-py-cubeai.readthedocs.io/en/latest/install.html">here</a>.


### Documentation dependencies

There are extra dependencies if you want to generate the documentation. Namely,

- <a href="https://www.doxygen.nl/">Doxygen</a>
- <a href="https://www.sphinx-doc.org/en/master/">Sphinx</a>
- <a href="https://github.com/readthedocs/sphinx_rtd_theme">sphinx_rtd_theme</a>
- <a href="https://github.com/breathe-doc/breathe">breathe</a>
- <a href="https://github.com/crossnox/m2r2">m2r2</a>

Note that if Doxygen is not found on your system CMake will skip this. On a Ubuntu/Debian based machine, you can install
Doxygen using

```
sudo apt-get install doxygen
```

Similarly, install ```sphinx_rtd_theme``` using

```
pip install sphinx_rtd_theme
```

Install ```breathe``` using

```
pip install breathe
```

Install ```m2r2``` using

```
pip install m2r2
```


