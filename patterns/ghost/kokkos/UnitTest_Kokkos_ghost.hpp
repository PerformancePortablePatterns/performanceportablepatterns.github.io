#ifndef UNIT_TEST_KOKKOS_GHOST
#define UNIT_TEST_KOKKOS_GHOST

#include <Kokkos_Core.hpp>
#include <gtest/gtest.h>

#include "ppp_ghost.hpp"

template <unsigned numLvl = 2, int neutrElement = -78>
struct CompatibleStruct {
  static constexpr unsigned numLevels = numLvl;
  static constexpr int neutralElement = neutrElement;
  using DataType                      = int;

  CompatibleStruct() {
    levels = static_cast<int*>(Kokkos::kokkos_malloc<Kokkos::SharedSpace>(
        "CompatibleStruct.levels", numLvl * sizeof(int)));

    for (int i = 0; i < numLvl; ++i) levels[i] = neutrElement;
  }

  CompatibleStruct(CompatibleStruct const& other) {
    levels = static_cast<int*>(Kokkos::kokkos_malloc<Kokkos::SharedSpace>(
        "CompatibleStruct.levels", numLvl * sizeof(int)));

    for (int i = 0; i < numLvl; ++i) levels[i] = other.levels[i];
  }

  ~CompatibleStruct() {
    if (levels) Kokkos::kokkos_free<Kokkos::SharedSpace>(levels);
  }

  int* levels = nullptr;
};

// 1 level
// nevertheless, our struct should have two fields so we can check for fields we
// do not touch
template <>
struct PPP::is_ghostable<CompatibleStruct<2>> : std::true_type {};

template <typename ExecutionSpace, typename T>
void test_ghost_lambda(ExecutionSpace const& exec_space, T& t) {
  static_assert(T::numLevels > 1, "T must allow registering more than 1 level");

  constexpr int N = 1;
  using Type      = typename T::DataType;
  Kokkos::View<Type*, typename ExecutionSpace::memory_space> result(
      "test_ghost_lambda::result", T::numLevels);
  PPP::Ghost ghost_a{t};

  Kokkos::parallel_for(
      Kokkos::RangePolicy(exec_space, 0, N), KOKKOS_LAMBDA(int i) {
        Kokkos::atomic_add(&ghost_a.get().levels[0], 1);
        for (int i = 0; i < T::numLevels; ++i)
          result[i] = ghost_a.get().levels[i];
      });

  auto host_result =
      Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace{}, result);

  EXPECT_EQ(host_result[0], T::neutralElement + N)
      << "result.level[0] was not increased by one\n";

  for (int i = 1; i < T::numLevels; ++i)
    EXPECT_EQ(host_result[i], T::neutralElement)
        << "result was not the neutralElement even though it should remain "
           "untouched\n";

  exec_space.fence("fence after test_ghost_lambda");
}

TEST(TEST_CATEGORY, ghost_lambda) {
  CompatibleStruct<2> data{};

  test_ghost_lambda(TEST_EXECSPACE{}, data);
}

// 2 levels
template <>
struct PPP::is_ghostable<CompatibleStruct<3>> : std::true_type {};

template <typename ExecutionSpace, typename T>
void test_ghost_lambda_2_levels(ExecutionSpace const& exec_space, T& t) {
  static_assert(T::numLevels > 2,
                "T must allow registering more than 2 levels");

  constexpr int N = 1;
  using Type      = typename T::DataType;
  Kokkos::View<Type*, typename ExecutionSpace::memory_space> result(
      "test_ghost_lambda::result", T::numLevels);
  PPP::Ghost ghost_a{t};

  Kokkos::parallel_for(
      Kokkos::RangePolicy(exec_space, 0, N), KOKKOS_LAMBDA(int i) {
        Kokkos::atomic_add(&ghost_a.get().levels[0], 1);

        auto internal = [=](void) -> void {
          Kokkos::atomic_add(&ghost_a.get().levels[1], 2);
        };
        internal();

        for (int i = 0; i < T::numLevels; ++i)
          result[i] = ghost_a.get().levels[i];
      });

  auto host_result =
      Kokkos::create_mirror_view_and_copy(Kokkos::HostSpace{}, result);

  EXPECT_EQ(host_result[0], T::neutralElement + N)
      << "result.level[0] was not increased by one\n";
  EXPECT_EQ(host_result[1], T::neutralElement + 2 * N)
      << "result.level[2] was not increased by two\n";

  for (int i = 2; i < T::numLevels; ++i)
    EXPECT_EQ(host_result[i], T::neutralElement)
        << "result was not the neutralElement even though it should remain "
           "untouched\n";

  exec_space.fence("fence after test_ghost_lambda_2_levels");
}

TEST(TEST_CATEGORY, ghost_lambda_2_levels) {
  CompatibleStruct<3> data{};

  test_ghost_lambda_2_levels(TEST_EXECSPACE{}, data);
}

#endif
