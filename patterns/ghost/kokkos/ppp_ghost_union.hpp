#ifndef PPP_GHOST_HPP
#define PPP_GHOST_HPP

#include <cstring>

namespace PPP {

template <typename T>
constexpr bool is_ghostable_v = false;

template <class T>
KOKKOS_INLINE_FUNCTION void copy_member(T &dest, T const &src) noexcept {
  std::memcpy(static_cast<void *>(&dest), static_cast<const void *>(&src),
              sizeof(dest));
}

template <class Member>
class Ghost {
  union TrivialWrapper {
    explicit TrivialWrapper(Member &m) noexcept { copy_member(m_member, m); }

    KOKKOS_FUNCTION TrivialWrapper(const TrivialWrapper &other) noexcept {
      copy_member(m_member, other.m_member);
    }
    KOKKOS_FUNCTION TrivialWrapper(TrivialWrapper &&other) noexcept {
      copy_member(m_member, other.m_member);
    }
    KOKKOS_FUNCTION TrivialWrapper &operator=(
        const TrivialWrapper &other) noexcept {
      copy_member(m_member, other.m_member);
      return *this;
    }
    KOKKOS_FUNCTION TrivialWrapper &operator=(TrivialWrapper &&other) noexcept {
      copy_member(m_member, other.m_member);
      return *this;
    }
    KOKKOS_FUNCTION constexpr ~TrivialWrapper() noexcept {}

    Member m_member;
  } m_union;

 public:
  explicit Ghost(Member &m)
    requires is_ghostable_v<Member>
      : m_union(m) {}

  KOKKOS_FUNCTION constexpr Member &get() noexcept { return m_union.m_member; }
  KOKKOS_FUNCTION constexpr const Member &get() const noexcept {
    return m_union.m_member;
  }
};
}  // namespace PPP
#endif
