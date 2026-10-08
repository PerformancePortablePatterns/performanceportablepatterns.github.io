#ifndef PPP_GHOST_HPP
#define PPP_GHOST_HPP

#include <Kokkos_Core.hpp>

#include <new>
#include <type_traits>

namespace PPP {

template <typename Member>
struct is_ghostable : std::false_type {};

template <typename Member>
inline constexpr bool is_ghostable_v =
    is_ghostable<std::remove_cv_t<Member>>::value;

template <typename Member>
class Ghost {
  static_assert(is_ghostable_v<Member>,
                "Member must explicitly satisfy the is_ghostable guarantee "
                "given by the programmer by opt-in");

 public:
  // We take an externally constructed Member and copy its bit representation.
  // This MUST be a valid representation, thus the user has to guarantee this
  // via an opt-in trait (is_ghostable)
  explicit Ghost(Member &src) noexcept {
    const auto *src_ptr = reinterpret_cast<const unsigned char *>(&src);
    for (size_t i = 0; i < sizeof(Member); ++i) {
      m_storage[i] = src_ptr[i];
    }
  }

  // We need to pretend that an object is alive in the raw storage we used to
  // store the representation of an (externally) constructed object This also
  // implies that the lifetime of the object we ghost is managed appropriately
  // by the user
  KOKKOS_FUNCTION Member &get() noexcept {
    return *std::launder(reinterpret_cast<Member *>(m_storage));
  }

  KOKKOS_FUNCTION const Member &get() const noexcept {
    return *std::launder(reinterpret_cast<const Member *>(m_storage));
  }

 private:
  // We need the alignment to be the same on host and device.
  // Additionally, we need to prevent the compiler from optimizing away storage.
  // To do this we use the special protection a char array has
  alignas(Member) unsigned char m_storage[sizeof(Member)];
};

}  // namespace PPP
#endif
