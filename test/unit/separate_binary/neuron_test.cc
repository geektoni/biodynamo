#include "neuroscience/neuron.h"
#include "gtest/gtest.h"

#include "compile_time_param.h"
#include "neuroscience/compile_time_param.h"

#include "unit/test_util.h"
// FIXME move to neuroscience directory

namespace bdm {

namespace neuroscience {
BDM_SIM_OBJECT(SpecializedNeurite, Neurite) {
  BDM_SIM_OBJECT_HEADER(SpecializedNeuriteExt, 1, foo_);
public:
  SpecializedNeuriteExt() {}
private:
  vec<int> foo_;
};
}

template <typename TBackend>
struct CompileTimeParam
    : public DefaultCompileTimeParam<TBackend>,
      public neuroscience::DefaultCompileTimeParam<TBackend> {
  using TNeuron = neuroscience::SpecializedNeuron;
  using TNeurite = neuroscience::SpecializedNeurite;
  using AtomicTypes = VariadicTypedef<neuroscience::SpecializedNeuron, neuroscience::SpecializedNeurite>;
};

namespace neuroscience {

TEST(NeuronTest, Scalar) {
  Neurite neurite;
  Neuron neuron;
  typename Neuron::template Self<Scalar> neuron1;
  SpecializedNeuron sneuron;
}

TEST(NeuronTest, Soa) {
  SoaNeuron neuron;
  SoaSpecializedNeuron sneuron;
  typename SpecializedNeuron::template Self<Soa> soan;
  typename CompileTimeParam<>::TNeuron soan1;
}

TEST(NeuronTest, ExtendNewNeurite) {
  auto* rm = Rm();
  Rm()->Clear();
  const double kEpsilon = abs_error<double>::value;

  // create neuron
  std::array<double, 3> origin = {0, 0, 0};
  auto neuron = rm->New<SpecializedNeuron>(origin);
  neuron.SetDiameter(20);

  // new neurite
  auto neurite = neuron.ExtendNewNeurite({0, 0, 1}).Get();
  neurite.SetDiameter(2);

  // verify
  EXPECT_ARR_NEAR(neurite.GetPosition(), {0, 0, 10.5});
  EXPECT_ARR_NEAR(neurite.GetMassLocation(), {0, 0, 11});
  EXPECT_ARR_NEAR(neurite.GetXAxis(), {0, 0, 1});
  EXPECT_ARR_NEAR(neurite.GetYAxis(), {0, 1, 0});
  EXPECT_ARR_NEAR(neurite.GetZAxis(), {-1, 0, 0});
  EXPECT_ARR_NEAR(neurite.GetSpringAxis(), {0, 0, 1});
  EXPECT_NEAR(3.1415926535897931, neurite.GetVolume(), kEpsilon);
  EXPECT_NEAR(2, neurite.GetDiameter(), kEpsilon);
  EXPECT_NEAR(0, neurite.GetBranchOrder(), kEpsilon);
  EXPECT_NEAR(1, neurite.GetActualLength(), kEpsilon);
  EXPECT_NEAR(0, neurite.GetTension(), kEpsilon);
  EXPECT_NEAR(10, neurite.GetSpringConstant(), kEpsilon);
  EXPECT_NEAR(1, neurite.GetRestingLength(), kEpsilon);

  EXPECT_EQ(1, rm->Get<SpecializedNeuron>()->size());
  EXPECT_EQ(1, rm->Get<SpecializedNeurite>()->size());
}

TEST(NeuronTest, ExtendNeuriteAndElongate) {
  auto* rm = Rm();
  Rm()->Clear();
  const double kEpsilon = abs_error<double>::value;
  std::array<double, 3> origin = {0, 0, 0};

  auto neuron = rm->New<SpecializedNeuron>(origin);
  neuron.SetDiameter(20);

  auto neurite_segment = neuron.ExtendNewNeurite({0, 0, 1}).Get();
  neurite_segment.SetDiameter(2);

  std::cout << neurite_segment << std::endl;
  for (int i = 0; i < 140; ++i) {
    std::cout << "index: " << i << std::endl;
    neurite_segment.ElongateTerminalEnd(10, {0, 0, 1});
    neurite_segment.RunDiscretization();
  }

  std::cout << std::endl << neurite_segment << std::endl;


  EXPECT_NEAR(7.5, neurite_segment.GetLength(), kEpsilon);
  // EXPECT_NEAR(21, getTotalLength(ne->getPhysicalCylinder()), 1e-5);
}


}  // namespace neuroscience
}  // namespace bdm


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}