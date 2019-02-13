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

#ifndef CORE_EXECUTION_CONTEXT_IN_PLACE_EXEC_CTXT_H_
#define CORE_EXECUTION_CONTEXT_IN_PLACE_EXEC_CTXT_H_

#include <functional>
#include <unordered_map>
#include <vector>
#include "core/sim_object/so_uid.h"

namespace bdm {

class SimObject;

/// This execution context updates simulation objects in place. \n
/// Let's assume we have two sim objects `A, B` in our simulation that we want
/// to update to the next timestep `A*, B*`. If we have one thread it will first
/// update `A` and afterwards `B` and write the updates directly to the same
/// data structure. Therefore, before we start updating `B` the array looks
/// like this: `A*, B`. `B` already observes the updated `A`. \n
/// Operations in method `Execute` are executed in order given by the user.
/// Subsequent operations observe the changes of earlier operations.\n
/// In-place updates can lead to race conditions if simulation objects not only
/// modify themselves, but also neighbors. Therefore, a protection mechanism has
/// been added. If neighbors are not modified, this protection can be turned off
///  to improve performance using `DisableNeighborGuard()`. By default it is
/// turned on.\n
/// New sim objects will only be visible at the next iteration. \n
/// Also removal of a sim object happens at the end of each iteration.
class InPlaceExecutionContext {
 public:
  InPlaceExecutionContext();

  virtual ~InPlaceExecutionContext();

  /// This function is called at the beginning of each iteration.
  /// This function is not thread-safe.
  void SetupIteration();

  /// This function is called at the end of each iteration. \n
  /// This function is not thread-safe. \n
  /// NB: Invalidates references and pointers to simulation objects.
  void TearDownIteration();

  /// Execute a series of operations on a simulation object in the order given
  /// in the argument
  void Execute(SimObject* so,
               const std::vector<std::function<void(SimObject*)>>& operations);

  void push_back(SimObject* new_so);

  /// Forwards the call to `Grid::ForEachNeighborWithinRadius`
  /// Could be used to cache the results.
  void ForEachNeighborWithinRadius(
      const std::function<void(const SimObject*)>& lambda,
      const SimObject& query, double squared_radius);

  SimObject* GetSimObject(SoUid uid);

  const SimObject* GetConstSimObject(SoUid uid);

  void RemoveFromSimulation(SoUid uid);

  /// If a sim objects modifies other simulation objects while it is updated,
  /// race conditions can occur using this execution context. This function
  /// turns the protection mechanism off to improve performance. This is safe
  /// simulation objects only update themselves.
  void DisableNeighborGuard();

 private:
  /// Contains unique ids of sim objects that will be removed at the end of each
  /// iteration.
  std::vector<SoUid> remove_;

  /// Pointer to new sim objects
  std::unordered_map<SoUid, SimObject*> new_sim_objects_;
};

}  // namespace bdm

#endif  // CORE_EXECUTION_CONTEXT_IN_PLACE_EXEC_CTXT_H_