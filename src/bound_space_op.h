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

#ifndef BOUND_SPACE_OP_H_
#define BOUND_SPACE_OP_H_

#include "simulation.h"
#include "simulation_object.h"
#include "grid.h"
#include "param.h"

namespace bdm {

inline void ApplyBoundingBox(SimulationObject* sim_object, double lb, double rb) {
  // Need to create a small distance from the positive edge of each dimension;
  // otherwise it will fall out of the boundary of the simulation space
  double eps = 1e-10;
  auto pos = sim_object->GetPosition();
  for (int i = 0; i < 3; i++) {
    if (pos[i] < lb) {
      pos[i] = lb;
    } else if (pos[i] >= rb) {
      pos[i] = rb - eps;
    }
  }
  sim_object->SetPosition(pos);
}

/// Keeps the simulation objects contained within the bounds as defined in
/// param.h
class BoundSpace {
 public:
  BoundSpace() {}
  ~BoundSpace() {}

  void operator()(SimulationObject* sim_object) const {
    // set new positions after all updates have been calculated
    // otherwise some sim_objects would see neighbors with already updated
    // positions
    // which would lead to inconsistencies
    auto* sim = Simulation::GetActive();
    auto* grid = sim->GetGrid();
    auto* param = sim->GetParam();
    if (param->bound_space_) {
      ApplyBoundingBox(sim_object, param->min_bound_, param->max_bound_);
      grid->SetDimensionThresholds(param->min_bound_, param->max_bound_);  // FIXME what's this?
    }
  }
};

}  // namespace bdm

#endif  // BOUND_SPACE_OP_H_
