#ifndef TEST_SYCL_CATEGORY_HPP
#define TEST_SYCL_CATEGORY_HPP

#define TEST_CATEGORY sycl
#define TEST_EXECSPACE Kokkos::SYCL
#define TEST_MEMSPACE Kokkos::SYCLDeviceUSMSpace
#define TEST_DEVICE Kokkos::Device<Kokkos::SYCL, Kokkos::SYCLDeviceUSMSpace>

#endif
