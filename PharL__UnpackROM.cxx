#include "Hydro__Common.hxx"
#include "Hydro.hxx"

#include "PhaRL__UnpackROM.hxx"

enum
__pharl__unpackrom__recordtype
{
  PHARL__UNPACKROM__STOP = 0x00,

// Note: Jumps input address forward by two bytes.  Any payload is ignored.
  PHARL__UNPACKROM__JUMP__REL = 0x01,
// Note: Jumps to a predetermined fixed address.  Not supported.
  PHARL__UNPACKROM__JUMP__ABS = 0x02,

// Note: Copies data by filling using a pattern of `size__fill'.  If pattern is
// empty, the data is simply zeroed.  Output address is either 16- or 32-bit.
  PHARL__UNPACKROM__COPY__16__F = 0x03,
  PHARL__UNPACKROM__COPY__32__F = 0x04,
// Note: Copies data by copying payload.  Ditto.
  PHARL__UNPACKROM__COPY__16 = 0x05,
  PHARL__UNPACKROM__COPY__32 = 0x06
};

static
const
char *
UnpackROM__Data__Sanitize(
  const
  std::uint8_t *
  const
    data,
  std::size_t
    size
  )
  {
  static thread_local
  char
    text[128];
  std::size_t
  __size = std::max(sizeof(text), size);
  std::memcpy(
    text, data, __size);
  char *
it__text;
  for (
it__text =
    text;
it__text <
   &text[
  __size - 1];
it__text++)
    if (!
      std::isprint(
   *it__text)
      )
   *it__text = '.';
   *it__text = 0;
  return
    text;
  }

template
  <
    typename
     _UnpackROM__Copy
  >
[[nodiscard]]
constexpr
std::size_t __\
UnpackROM__Copy__Size(
  const
 _UnpackROM__Copy *
  const
  ) noexcept
  {
  return sizeof(_UnpackROM__Copy);
  }

template
  <
    typename
     _UnpackROM__Copy
  >
[[nodiscard]]
constexpr
std::size_t __\
UnpackROM__Copy__Size__Payload(
  const
 _UnpackROM__Copy *
  const
    data__rom
  ) noexcept
  {
  return data__rom->size;
  }

template
  <
    typename
     _UnpackROM__Copy
  >
[[nodiscard]]
constexpr
std::size_t __\
UnpackROM__Copy__Size__Payload__f(
  const
 _UnpackROM__Copy *
  const
    data__rom
  ) noexcept
  {
  return data__rom->size * data__rom->size__fill;
  }

struct __attribute__((packed))
pharl__unpackrom__copy__16__f
{
  std::uint16_t
    addr;
  std::uint16_t
    size;
  std::uint8_t
    size__fill;
  std::uint8_t
    data[];
};

[[nodiscard]]
static
constexpr
UnpackROM__Copy__Size(
  const
  pharl__unpackrom__copy__16__f *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size(
    data__rom);
  }

[[nodiscard]]
static
std::size_t
UnpackROM__Copy__Size__Payload(
  const
  pharl__unpackrom__copy__16__f *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size__Payload__f(
    data__rom);
  }

struct __attribute__((packed))
pharl__unpackrom__copy__32__f
{
  std::uint32_t
    addr;
  std::uint16_t
    size;
  std::uint8_t
    size__fill;
  std::uint8_t
    data[];
};

[[nodiscard]]
static
constexpr
UnpackROM__Copy__Size(
  const
  pharl__unpackrom__copy__32__f *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size(
    data__rom);
  }

[[nodiscard]]
static
std::size_t
UnpackROM__Copy__Size__Payload(
  const
  pharl__unpackrom__copy__32__f *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size__Payload__f(
    data__rom);
  }

struct __attribute__((packed))
pharl__unpackrom__copy__16
{
  std::uint16_t
    addr;
  std::uint16_t
    size;
  std::uint8_t
    data[];
};

[[nodiscard]]
static
constexpr
UnpackROM__Copy__Size(
  const
  pharl__unpackrom__copy__16 *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size(
    data__rom);
  }

[[nodiscard]]
static
std::size_t
UnpackROM__Copy__Size__Payload(
  const
  pharl__unpackrom__copy__16 *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size__Payload(
    data__rom);
  }

struct __attribute__((packed))
pharl__unpackrom__copy__32
{
  std::uint32_t
    addr;
  std::uint16_t
    size;
  std::uint8_t
    data[];
};

[[nodiscard]]
static
constexpr
UnpackROM__Copy__Size(
  const
  pharl__unpackrom__copy__32 *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size(
    data__rom);
  }

[[nodiscard]]
static
std::size_t
UnpackROM__Copy__Size__Payload(
  const
  pharl__unpackrom__copy__32 *
  const
    data__rom
  )
  {
  return __\
UnpackROM__Copy__Size__Payload(
    data__rom);
  }

std::fstream
f__exe;

template
  <
    typename
     _UnpackROM__Copy
  >
static
void
UnpackROM__Dump__F(
  const
 _UnpackROM__Copy *
  const
    data__rom
  )
  {
  if (
    data__rom->size__fill
    ) [[unlikely]]
  std::printf(">%" x32 ":%" x16 ": ``%.*s'' (%u)\n",
    data__rom->addr,
    data__rom->size,
    data__rom->size,
      UnpackROM__Data__Sanitize(
    data__rom->data,
    data__rom->size),
    data__rom->size__fill);
  else
  std::printf(">%" x32 ":%" x16 ".\n",
    data__rom->addr,
    data__rom->size);
  return;
  }

template
  <
    typename
     _UnpackROM__Copy
  >
static
void
UnpackROM__Seek(
  const
 _UnpackROM__Copy *
  const
    data__rom
  )
  {
  constexpr
  std::size_t
    data__rom__addr__baseoffset =
  hydro__imagebase__offs;

  if (
    data__rom->addr
      <
    data__rom__addr__baseoffset
    ) [[unlikely]]
    std::runtime_error(__printf__thread(
      "address `%" xpt "' less than base `%" xpt "'",
    data__rom->addr,
    data__rom__addr__baseoffset));

of__file.seekp(
    data__rom->addr -
    data__rom__addr__baseoffset);

  return;
  }

static
void
UnpackROM__Copy__Blob(
  const
  std::uint8_t *
  const
    data,
  std::size_t
    size
  )
  {
of__file.write(reinterpret_cast< const char * >(
    data),
    size);
  return;
  }

template
  <
    typename
     _UnpackROM__Copy
  >
static
void
UnpackROM__Copy__F(
  const
 _UnpackROM__Copy *
  const
    data__rom
  )
  {
  static
  const
  std::uint8_t
  __data__fill__0[16] = { 0 };

  std::size_t
    size__fill;
  const
  std::uint8_t *
    data__fill;

  if (
    data__rom->size__fill > 0
    )
    {
    size__fill =
      data__rom->
    size__fill;
    data__fill =
      data__rom->
    data;
    }
  else
    {
    size__fill = sizeof(
  __data__fill__0);
    data__fill =
  __data__fill__0;
    }

  if (
of__file.is_open()
      ) [[likely]]
    {
  UnpackROM__Seek(
    data__rom);

  std::size_t
    size__left = data__rom->size;
  while (
    size__left)
    {
  const
  std::size_t
  __size__fill = std::min(
    size__fill,
    size__left);
  UnpackROM__Copy__Blob(
    data__fill,
  __size__fill);
    size__left -=
  __size__fill;
    }

    }

  return;
  }

template
  <
    typename
     _UnpackROM__Copy
  >
static
void
UnpackROM__Copy(
  const
 _UnpackROM__Copy *
  const
    data__rom
  )
  {
  if (
of__file.is_open()
    ) [[likely]]
    {
  UnpackROM__Seek(
    data__rom);
  UnpackROM__Copy__Blob(
    data__rom->data,
    data__rom->size);
    }
  return;
  }

template
  <
    typename
     _UnpackROM__Copy
  >
static
void
UnpackROM__Dump(
  const
 _UnpackROM__Copy *
  const
    data__rom
  )
  {
  std::printf(">%" x32 ":%" x16 ": ``%.*s''\n",
    data__rom->addr,
    data__rom->size,
    data__rom->size,
      UnpackROM__Data__Sanitize(
    data__rom->data,
    data__rom->size));
  return;
  }

template
  <
    typename
     _UnpackROM__Copy
  >
static
void
UnpackROM__NextRecord(
  const
  std::uint8_t *&
    data,
  const
 _UnpackROM__Copy *
  const
    data__rom
  )
  {
    data +=
  UnpackROM__Copy__Size(
    data__rom) +
  UnpackROM__Copy__Size__Payload(
    data__rom);
  return;
  }

static
void
PharL__UnpackROM__Copy__16__F(
  const
  std::uint8_t *&
    data
  )
  {
  const
  pharl__unpackrom__copy__16__f *
  const
    data__rom =
  reinterpret_cast<
  const
  pharl__unpackrom__copy__16__f * >(
    data);

  UnpackROM__Dump__F(
    data__rom);
  UnpackROM__Copy__F(
    data__rom);
  UnpackROM__NextRecord(
    data,
    data__rom);

  return;
  }

static
void
PharL__UnpackROM__Copy__32__F(
  const
  std::uint8_t *&
    data
  )
  {
  const
  pharl__unpackrom__copy__32__f *
  const
    data__rom =
  reinterpret_cast<
  const
  pharl__unpackrom__copy__32__f * >(
    data);

  UnpackROM__Dump__F(
    data__rom);
  UnpackROM__Copy__F(
    data__rom);
  UnpackROM__NextRecord(
    data,
    data__rom);

  return;
  }

static
void
PharL__UnpackROM__Copy__16(
  const
  std::uint8_t *&
    data
  )
  {
  const
  pharl__unpackrom__copy__16 *
  const
    data__rom =
  reinterpret_cast<
  const
  pharl__unpackrom__copy__16 * >(
    data);

  UnpackROM__Dump(
    data__rom);
  UnpackROM__Copy(
    data__rom);
  UnpackROM__NextRecord(
    data,
    data__rom);

  return;
  }

static
void
PharL__UnpackROM__Copy__32(
  const
  std::uint8_t *&
    data
  )
  {
  const
  pharl__unpackrom__copy__32 *
  const
    data__rom =
  reinterpret_cast<
  const
  pharl__unpackrom__copy__32 * >(
    data);

  UnpackROM__Dump(
    data__rom);
  UnpackROM__Copy(
    data__rom);
  UnpackROM__NextRecord(
    data,
    data__rom);

  return;
  }

void
PharL__UnpackROM__Data(
  const
  std::uint8_t *
  const
    data,
  std::size_t
    size
  )
  {
  const
  std::uint8_t *
    data__readptr =
  data;
  const
  std::uint8_t *
  const
    tail =
  data + size;

  do
    {
  const
  std::uint8_t
    unpackrom__recordtype =
 *data__readptr++;

  std::printf("@%" Xpt " (%02x)\n",
    static_cast< std::uintptr_t >(
      data__readptr -
      data),
    unpackrom__recordtype);
  switch (
    unpackrom__recordtype)
    {
  case PHARL__UNPACKROM__STOP:
    return;

  case PHARL__UNPACKROM__JUMP__REL:
    data__readptr += 2;
  std::printf(">%" xpt "\n", reinterpret_cast< std::uintptr_t >(
    data__readptr));
    break;

  case PHARL__UNPACKROM__JUMP__ABS:
  __throw__unsupported();

  case PHARL__UNPACKROM__COPY__16:
    PharL__UnpackROM__Copy__16(
      data__readptr);
    break;
  case PHARL__UNPACKROM__COPY__16__F:
    PharL__UnpackROM__Copy__16__F(
      data__readptr);
    break;

  case PHARL__UNPACKROM__COPY__32:
    PharL__UnpackROM__Copy__32(
      data__readptr);
    break;
  case PHARL__UNPACKROM__COPY__32__F:
    PharL__UnpackROM__Copy__32__F(
      data__readptr);
    break;

  [[unlikely]] default:
  std::printf("don't know how to handle %x\n", unpackrom__recordtype);
  __throw__unexpected();
    }

    } while (
  data__readptr < tail);
  std::printf("overflow?\n");
__throw__unexpected();
  }
