// -----------------------------------------------------------------------------
//
// Copyright (C) The BioDynaMo Project.
// All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
//
// See the LICENSE file distributed with this work for details.
// See the NOTICE file distributed with this work for additional information
// regarding copyright ownership.
//
// -----------------------------------------------------------------------------
#ifndef MY_SIMULATION_H_
#define MY_SIMULATION_H_

#include "biodynamo/core/simulation/biodynamo.h"

namespace bdm {

// Define compile time parameter
template <typename Backend>
struct CompileTimeParam : public DefaultCompileTimeParam<Backend> {};

inline int Simulate(int argc, const char** argv) {
  Simulation<> simulation(argc, argv);

  // Define initial model - in this example: single cell at origin
  auto* rm = simulation.GetResourceManager();
  auto&& cell = rm->New<Cell>(30);

  // Run simulation for one timestep
  simulation.GetScheduler()->Simulate(1);

  std::cout << "Simulation completed successfully!" << std::endl;
  return 0;
}

}  // namespace bdm

#endif  // MY_SIMULATION_H_
