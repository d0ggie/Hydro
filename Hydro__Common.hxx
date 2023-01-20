#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <exception>
#include <memory>
#include <cstring>
#include <cstdint>
#include <cctype>
#include <cstdarg>
#include <cinttypes>

#define x16 "04" PRIx16
#define x32 "08" PRIx32
#define x64 "08" PRIx64
#define u64 "08" PRIu64
#define xsz "08" PRIxPTR
#define Xsz "08" PRIXPTR
#define xpt "08" PRIxPTR
#define Xpt "08" PRIXPTR
#define str "s"

[[noreturn]]
static
inline
void
__throw__unsupported(
  )
  {
  throw std::runtime_error("unsupported");
  }
[[noreturn]]
static
inline
void
__throw__unexpected(
  )
  {
  throw std::runtime_error("unexpected");
  }

static
inline
const
char *
__printf__thread(
  const
  char *
  const
    text__fmt, ...
  )
  {
  static thread_local
  char
  __text__local[64 * 1024];
  va_list
    text__ap;
  va_start(
    text__ap, text__fmt);
  std::vsnprintf(
  __text__local, sizeof(__text__local),
    text__fmt,
    text__ap);
  va_end(
    text__ap);
  return
  __text__local;
  }

extern
std::ifstream
if__file;
extern
std::ofstream
of__file;

constexpr
std::ios_base::seekdir
std__iostream__seek__relative =
std::ios_base::cur,
std__iostream__seek__absolute =
std::ios_base::beg,
std__iostream__seek__absolute__end =
std::ios_base::end;

extern
void
std__ifstream__seek(
  std::ifstream &
if__stream,
  std::ptrdiff_t
    stream__seek,
  std::ios_base::seekdir
    stream__seekdir =
std__iostream__seek__relative
  );

constexpr
std::size_t
  size__sector = 512;
constexpr
std::size_t
  size__sector__mask =
  size__sector - 1;

[[nodiscard]]
constexpr
std::size_t
size__sector__aligned(
  std::size_t
    size
  ) noexcept
  {
  return
    size &
   ~size__sector__mask;
  }
[[nodiscard]]
constexpr
std::size_t
size__sector__unalign(
  std::size_t
    size
  ) noexcept
  {
  return
    size &
    size__sector__mask;
  }

static
inline
void
std__ifstream__seek__sector(
  std::ifstream &
if__stream,
  std::ptrdiff_t
    stream__seek__sector,
  std::ios_base::seekdir
    stream__seekdir =
std__iostream__seek__relative
  )
  {
  return
std__ifstream__seek(
if__stream,
    stream__seek__sector * size__sector,
    stream__seekdir);
  }

[[nodiscard]]
extern
std::size_t
std__ifstream__tell(
  std::ifstream &
if__stream
  );

[[nodiscard]]
static
inline
std::size_t
std__ifstream__tell__sector(
  std::ifstream &
if__stream
  )
  {
  return
std__ifstream__tell(
if__stream) / size__sector;
  }

static
inline
void
std__ifstream__seek__end(
  std::ifstream &
if__stream
  )
  {
std__ifstream__seek(
if__stream, 0,
std__iostream__seek__absolute__end);
  return;
  }
