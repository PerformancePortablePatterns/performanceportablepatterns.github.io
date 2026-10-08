include(${CMAKE_SOURCE_DIR}/patterns/utils/kokkos/kokkos_setup.cmake)

performanceportablepatterns_add_kokkos_test(
  UnitTest_Kokkos_ghost HEADERS UnitTest_Kokkos_ghost.hpp INCLUDE_HEADERS
  ppp_ghost.hpp)
