#include "Hydro__Common.hxx"
#include "Hydro.hxx"

#include "Hydro__CmosCheck.hxx"

static
const
hydro__dwstring * __\
hydro__cmoscheck__magic(
  ) noexcept
  {
  static constexpr
  hydro__dwstring
  __hydro__cmoscheck__magic__storage = {
    .data__db = HYDRO__CMOSCHECK__MAGIC
    };
  return std::addressof(
  __hydro__cmoscheck__magic__storage);
  }

static
void __\
hydro__cmoscheck__compare(
  bool &
  __data__verdict,
  std::uint32_t
    data__0,
  std::uint32_t
    data__1,
  const
  char *
  const
    name
  )
  {
  if (
    data__0
      !=
    data__1
    ) [[unlikely]]
    {
  std::printf("!%" x32 " != %" x32 " (%s).\n",
    data__0,
    data__1,
    name);
  __data__verdict = false;
    }
  return;
  }

static
bool
hydro__cmoscheck__clean(
  const
  hydro__idesector *
  const
    data__ide
  )
  {
  bool
    data__verdict = true;
  std::uint32_t constexpr
  __data__dirty__comp = 0;
  std::uint32_t const
    data__dirty__cmos =
  data__ide->data__dw[HYDRO__CMOSCHECK__F__DIRTY];
__hydro__cmoscheck__compare(
    data__verdict,
    data__dirty__cmos,
  __data__dirty__comp,
    "dirty");
  return
    data__verdict;
  }

static
bool
hydro__cmoscheck__magic(
  const
  hydro__idesector *
  const
    data__ide
  )
  {
  bool
    data__verdict = true;

  for (unsigned
    data__ix = 0;
    data__ix < HYDRO__CMOSCHECK__S__MAGIC;
  ++data__ix)
    {
  std::uint32_t const
    data__magic__cmos =
  data__ide->data__dw[HYDRO__CMOSCHECK__F__MAGIC + data__ix],
    data__magic__comp =
__hydro__cmoscheck__magic(
    )->data__dw[data__ix];
__hydro__cmoscheck__compare(
    data__verdict,
    data__magic__cmos,
    data__magic__comp, "magic");
    }

  return
    data__verdict;
  }

static
bool
hydro__cmoscheck__checksum__a(
  const
  hydro__idesector *
  const
    data__ide
  )
  {
  bool
    data__verdict = true;

  std::uint32_t
    data__e__checksum__cmos,
    data__o__checksum__cmos;
  std::uint32_t
    data__e__checksum__comp = 0,
    data__o__checksum__comp = 0;
  for (unsigned
    data__ix = 0;
    data__ix < HYDRO__CMOSCHECK__S__CHECKSUM__A;)
    {
    std::uint32_t
      data__e =
    data__ide->data__dw[
      data__ix];
    if (
      data__ix
        ==
      HYDRO__CMOSCHECK__F__CHECKSUM__A__E
      )
      {
    constexpr
    std::uint32_t
    __data__e__init = 0;
    data__e__checksum__cmos =
      data__e;
      data__e =
    __data__e__init;
      }
    else
      data__e__checksum__comp +=
      data__e;

    ++data__ix;

    std::uint32_t
      data__o =
    data__ide->data__dw[
      data__ix];
    if (
      data__ix
        ==
      HYDRO__CMOSCHECK__F__CHECKSUM__A__O
      ) [[unlikely]]
      {
    constexpr
    std::uint32_t
    __data__o__init = 0;
      data__o__checksum__cmos =
      data__o;
      data__o =
    __data__o__init;
      }
    else
      data__o__checksum__comp +=
      data__o;

    ++data__ix;
    }

__hydro__cmoscheck__compare(
    data__verdict,
    data__e__checksum__cmos,
    data__e__checksum__comp,
    "checksum-a-even");
__hydro__cmoscheck__compare(
    data__verdict,
    data__o__checksum__cmos,
    data__o__checksum__comp,
    "checksum-a-odd");

  return
    data__verdict;
  }

static
bool
hydro__cmoscheck__checksum__b(
  const
  hydro__idesector *
  const
    data__ide
  )
  {
  bool
    data__verdict = true;

  std::uint32_t
    data__l__checksum__comp =
  data__ide->data__dw[HYDRO__CMOSCHECK__F__CHECKSUM__B__L],
    data__u__checksum__comp =
  data__ide->data__dw[HYDRO__CMOSCHECK__F__CHECKSUM__B__U];

  for (unsigned
    data__ix = 0;
    data__ix < HYDRO__CMOSCHECK__S__CHECKSUM__B;
  ++data__ix)
    {
    data__l__checksum__comp *= 5;
  ++data__l__checksum__comp;
    data__u__checksum__comp *= 5;
  ++data__u__checksum__comp;

  std::uint32_t const
    data__l__checksum__cmos =
  data__ide->data__dw[HYDRO__CMOSCHECK__O__LOWER + data__ix],
    data__u__checksum__cmos =
  data__ide->data__dw[HYDRO__CMOSCHECK__O__UPPER + data__ix];

__hydro__cmoscheck__compare(
    data__verdict,
    data__l__checksum__cmos,
    data__l__checksum__comp,
    "checksum-b-lower");
__hydro__cmoscheck__compare(
    data__verdict,
    data__u__checksum__cmos,
    data__u__checksum__comp,
    "checksum-b-upper");
    }

  return
    data__verdict;
  }

void
Hydro__CmosCheck(
  const
  hydro__idesector *
  const
    data__ide
  )
  {
  bool
    data__verdict = true;

  std::uint32_t const
    data__ident =
  data__ide->data__dw[HYDRO__CMOSCHECK__F__IDENT];
  std::printf("+%" x32 " (%s).\n",
    data__ident, data__ident ? "upper" : "lower");

  auto
    hydro__cmoscheck__routine__verdict = [&](
      bool (*
        hydro__cmoscheck__routine)(
          const
          hydro__idesector *
          const)
    )
    {
  if (!
    hydro__cmoscheck__routine(
      data__ide)
    ) [[unlikely]]
    data__verdict = false;
    return;
    };

  hydro__cmoscheck__routine__verdict(
  hydro__cmoscheck__clean);
  hydro__cmoscheck__routine__verdict(
  hydro__cmoscheck__magic);
  hydro__cmoscheck__routine__verdict(
  hydro__cmoscheck__checksum__a);
  hydro__cmoscheck__routine__verdict(
  hydro__cmoscheck__checksum__b);

  std::uint32_t const
    data__index__lo =
  data__ide->data__dw[HYDRO__CMOSCHECK__F__INDEX__LO],
    data__index__hi =
  data__ide->data__dw[HYDRO__CMOSCHECK__F__INDEX__HI]
    ;
  std::uint64_t const
    data__index =
  static_cast< std::uint64_t >(
    data__index__lo) |
  static_cast< std::uint64_t >(
    data__index__hi) << 32;

  std::printf("+%" x32 ":%" x32 " (%" u64 ").\n",
    data__index__hi,
    data__index__lo,
    data__index)
    ;

  if (!
    data__verdict
    ) [[unlikely]]
  std::puts("failed check");

  return;
  }
