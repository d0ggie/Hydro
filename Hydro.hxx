#pragma once

union
hydro__idesector
  {
char
  data__db[512];
std::uint32_t
  data__dw[128];
  };

constexpr
std::ptrdiff_t
  hydro__imagebase__offs = 0x100000;

constexpr
std::size_t
  hydro__idesector__size = sizeof(
hydro__idesector);
static_assert(
  hydro__idesector__size == 512);
constexpr
std::ptrdiff_t
  hydro__idesector__base =
  0x48c;
constexpr
std::ptrdiff_t
a__hydro__idesector__offs__cmos[] = {
  0x080,
  0x200
  };
constexpr
std::ptrdiff_t
a__hydro__idesector__offs__cmoscheck[] = {
  0x380,
  0x401
  };

union
hydro__dwstring
  {
char
  data__db[16];
std::uint32_t
  data__dw[4];
  };
