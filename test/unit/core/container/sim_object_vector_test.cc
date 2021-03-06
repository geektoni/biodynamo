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

#include "core/container/sim_object_vector.h"
#include "gtest/gtest.h"
#include "unit/test_util/test_sim_object.h"

namespace bdm {

TEST(SimObjectVectorTest, All) {
  std::string sim_name("simulation_object_vector_test_RunInitializerTest");
  Simulation simulation(sim_name);
  auto* rm = simulation.GetResourceManager();

  rm->push_back(new TestSimObject());
  rm->push_back(new TestSimObject());
  rm->push_back(new TestSimObject());

  SimObjectVector<int> vector;
  EXPECT_EQ(3u, vector.size(0));

  // values are not initialized
  vector[SoHandle(0, 0)] = 1;
  vector[SoHandle(0, 1)] = 2;
  vector[SoHandle(0, 2)] = 3;

  EXPECT_EQ(1, vector[SoHandle(0, 0)]);
  EXPECT_EQ(2, vector[SoHandle(0, 1)]);
  EXPECT_EQ(3, vector[SoHandle(0, 2)]);

  vector.clear();
  EXPECT_EQ(0u, vector.size(0));
}

}  // namespace bdm
