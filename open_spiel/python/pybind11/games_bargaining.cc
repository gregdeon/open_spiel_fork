// Copyright 2022 DeepMind Technologies Limited
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "open_spiel/python/pybind11/games_bargaining.h"

#include "open_spiel/games/bargaining.h"
#include "open_spiel/python/pybind11/pybind11.h"
#include "open_spiel/spiel.h"

namespace py = ::pybind11;
using open_spiel::Game;
using open_spiel::State;
using open_spiel::bargaining::BargainingState;
using open_spiel::bargaining::Instance;

PYBIND11_SMART_HOLDER_TYPE_CASTERS(BargainingState);

void open_spiel::init_pyspiel_games_bargaining(py::module& m) {
  py::class_<Instance>(m, "Instance")
      .def_readwrite("pool", &Instance::pool)
      .def_readwrite("values", &Instance::values);

  py::classh<BargainingState, State>(m, "BargainingState")
      .def("instance", &BargainingState::instance)
      .def("agree_action", &BargainingState::AgreeAction)
      // Pickle support
      .def(py::pickle(
          [](const BargainingState& state) {  // __getstate__
            return SerializeGameAndState(*state.GetGame(), state);
          },
          [](const std::string& data) {  // __setstate__
            std::pair<std::shared_ptr<const Game>, std::unique_ptr<State>>
                game_and_state = DeserializeGameAndState(data);
            return dynamic_cast<BargainingState*>(
                game_and_state.second.release());
          }));
}
