#include "Hydro__Common.hxx"
#include "Hydro.hxx"

#include "Hydro__CmosCheck.hxx"
#include "PhaRL__UnpackROM.hxx"

// Sorry.

constexpr
std::uint32_t
  data__rom__addr__baseoffset = 0x100000;

/*
enum
{
  CMOSB__S__OPERATORSETTINGS      = 0x0059,
  CMOSB__O__OPERATORSETTINGS      = 0x0005,
  CMOSB__S__HISCORETABLE          = 0x0008 * 0x000A,
  CMOSB__O__HISCORETABLE          = 0x005F,
  CMOSB__N__HISCORETABLE          = 0x000D,
  CMOSB__S__HUDSPLITTIMES         = 0x000D,
  CMOSB__N__HUDSPLITTIMES         = 0x0005,
  CMOSB__O__HUDSPLITTIMES         = 0x0164,
  CMOSB__S__AIRABBITWINHISTORY    = 0x00B6,
  CMOSB__O__AIRABBITWINHISTORY    = 0x0475
};
*/

std::ifstream
if__file;
std::ofstream
of__file;

enum
__hydro__rominit__offset
{
  HYDRO__ROMINIT__OFFS__FUZZY =
    0x00f7000ul,
  HYDRO__ROMINIT__OFFS__V100D =
    0x00f7634ul,
  HYDRO__ROMINIT__OFFS__V101B =
    0x00f7b58ul
};
constexpr
std::uint64_t
  hydro__rominit__fuzzy = 0x005c3a41;

template
  <
    typename
     _Std__FStream
  >
void
__std__fstream__exceptions(
  _Std__FStream &
 f__stream
  )
  {
 f__stream.exceptions(std::fstream::failbit | std::fstream::badbit);
  return;
  }

static
inline
char __\
std__iostream__seekchar(
  std::ios_base::seekdir
    stream__seekdir
  )
  {
  switch (
    stream__seekdir)
    {
  case std::ios_base::beg: return '<';
  case std::ios_base::end: return '>';
  case std::ios_base::cur: return '@';
  [[unlikely]] default: return '?';
    }
  }

void
std__ifstream__seek(
  std::ifstream &
if__stream,
  std::ptrdiff_t
    stream__seek,
  std::ios_base::seekdir
    stream__seekdir
  )
  {
if__stream.seekg(static_cast< std::ifstream::pos_type >(
    stream__seek), stream__seekdir);
  std::size_t const
  __stream__seek__position = static_cast<
  std::size_t >(
if__stream.tellg());
  std::printf("@%" Xsz ": seek %" xsz " (%c).\n",
  __stream__seek__position,
    stream__seek & 0xfffffffful,
  __std__iostream__seekchar(
    stream__seekdir));
  return;
  }

[[nodiscard]]
std::size_t
std__ifstream__tell(
  std::ifstream &
if__stream
  )
  {
  std::size_t const
  __stream__tell__position = static_cast<
  std::size_t >(
if__stream.tellg());
  std::printf("@%" Xsz ".\n",
  __stream__tell__position);
  return
  __stream__tell__position;
  }

static
void
Main__Business__CmosCheck(
  const
  char *
  const
    file
  )
  {
if__file.open(
    file,
      std::ios_base::in |
      std::ios_base::binary);
  if (!
if__file.is_open()
    ) [[unlikely]]
    throw std::runtime_error(__printf__thread(
      "unable to open `%.1024s'",
        file));
__std__fstream__exceptions(
if__file);

  std__ifstream__seek__end(
if__file);
  std::size_t
    size =
  std__ifstream__tell(
if__file);

  constexpr
  std::size_t
  __size__min =
  hydro__idesector__base *
  hydro__idesector__size;

  if (
    size
      <
  __size__min
    ) [[unlikely]]
  throw std::runtime_error(__printf__thread(
    "`%.1024s' size `%" xpt "' too small, should be at least `%" xpt "'",
      file, size, __size__min));
  if (
  std::size_t const
  __size__sector__aligned =
  size__sector__aligned(
    size);
    size
      !=
  __size__sector__aligned
    ) [[unlikely]]
    {
  std::size_t const
  __size__sector__unalign =
  size__sector__unalign(
    size);
  std::printf("`%.1024s' size `%" xpt "' unaligned by `%" xpt "', attempting to use `%" xpt "'.\n",
    file,
    size,
  __size__sector__unalign,
  __size__sector__aligned);
    size =
  __size__sector__aligned;
    }

  std__ifstream__seek(
if__file,
   -hydro__idesector__base *
    hydro__idesector__size);
  std::size_t
  __hydro__idesector__base =
  std__ifstream__tell__sector(
if__file);

  std::printf("=%" xsz " sectors.\n",
  __hydro__idesector__base);

  std::ptrdiff_t
  __hydro__idesector__offs__cmoscheck__delta = 0;
  for (std::ptrdiff_t
    hydro__idesector__offs__cmoscheck
      :
 a__hydro__idesector__offs__cmoscheck)
    {
  __hydro__idesector__offs__cmoscheck__delta =
    hydro__idesector__offs__cmoscheck -
  __hydro__idesector__offs__cmoscheck__delta;
  std__ifstream__seek__sector(
if__file,
  __hydro__idesector__offs__cmoscheck__delta);
  hydro__idesector
  __hydro__idesector__storage;
  hydro__idesector *
  const
  __hydro__idesector =
  std::addressof(
  __hydro__idesector__storage);
if__file.read(reinterpret_cast< char * >(
  __hydro__idesector->data__db), sizeof(
  __hydro__idesector->data__db));
  __hydro__idesector__offs__cmoscheck__delta++;
  Hydro__CmosCheck(
  __hydro__idesector);
    }

  return;
  }

static
bool
Hydro__UnpackROM__Find(
  )
  {
std__ifstream__seek(
 if__file,
    HYDRO__ROMINIT__OFFS__FUZZY,
std__iostream__seek__absolute);
  for (unsigned n = 0; n < 1024; ++n)
    {
    union
      {
  char
    data__db[4];
  std::uint32_t
    data__dw;
      }
  __hydro__rominit__fuzzy;
  if__file.read(
  __hydro__rominit__fuzzy.data__db,
      sizeof(
  __hydro__rominit__fuzzy));
  if (
  __hydro__rominit__fuzzy.data__dw
      ==
    hydro__rominit__fuzzy
    )
    return true;
    }

  return false;
  }

static
void
Main__Business__UnpackROM(
  const
  char *
  const
    file,
  const
  char *
  const
    file__rominit
  )
  {
if__file.open(
    file,
      std::ios_base::in |
      std::ios_base::binary);
  if (!
if__file.is_open()
    ) [[unlikely]]
    throw std::runtime_error(__printf__thread(
      "unable to open `%.1024s'",
        file));
__std__fstream__exceptions(
if__file);

of__file.open(
    file__rominit,
      std::ios_base::in |
      std::ios_base::out |
      std::ios_base::binary);
  if (!
of__file.is_open()
    ) [[unlikely]]
    {
of__file.open(
    file__rominit,
      std::ios_base::out |
      std::ios_base::binary);
  if (!
of__file.is_open()
    ) [[unlikely]]
    throw std::runtime_error(__printf__thread(
      "unable to open `%.1024s'",
        file__rominit));
    }
__std__fstream__exceptions(
of__file);

  constexpr
  std::size_t
    size = 1024 * 1024;
  if (!
    Hydro__UnpackROM__Find()
    ) [[unlikely]]
    throw std::runtime_error("did not find rominit");
  std::size_t
    addr =
  std__ifstream__tell(
if__file);
  std::printf("=%" xsz ".\n",
    addr);

  std::unique_ptr<
    std::uint8_t [] >
  __data__storage =
  std::make_unique<
    std::uint8_t [] >(size);
  if (!
  __data__storage
    ) [[unlikely]]
    throw std::runtime_error("unable to allocate");

  std::uint8_t *
  const
    data = __data__storage.get();
if__file.read(reinterpret_cast< char * >(data), size);

  PharL__UnpackROM__Data(
    data,
    size);

  return;
  }

int
main(
  int
    argc,
  char **
    argv
  )
  {
  int
    retc = 1;

  auto
    argv__n__text = [&] [[nodiscard]] (
      unsigned
      __argi
      ) -> const char *
      {
    unsigned
    __argc = static_cast<
    unsigned >(
      argc);
    if (!
    __argc
      )
      throw std::runtime_error(
        "whoami?");
    else
    if (
    __argc - 1
        <
    __argi + 1
      ) [[unlikely]]
      throw std::runtime_error(__printf__thread(
        "too few arguments, need `%u' but only got `%u'",
      __argi + 1,
      __argc - 1));
    return
      argv[__argi + 1];
      };
  auto
    argv__n__char = [&] [[nodiscard]] (
    unsigned
    __argi
    )  -> char
    {
    const
    char *
    const
    __text =
    argv__n__text(
    __argi);
    return __text ? *__text : 0;
    };

  if (
    argc < 2
    )
  std::printf(R"__usage__(%.4096s: <action> [arguments...]
  unpack rominit:
    <x> <executable-file> <rominit-output>
  verify image:
    <i> <image-file>)__usage__",
    argv[0]);
  else
  try {

  char
    argv__mode =
  argv__n__char(0);

  switch (
    argv__mode)
    {
  case 'x':
    Main__Business__UnpackROM(
      argv__n__text(1),
      argv__n__text(2));
    break;

  case 'i':
    Main__Business__CmosCheck(
      argv__n__text(1));
    break;

  [[unlikely]] default:
    throw std::runtime_error(__printf__thread(
      "unknown working-mode `%c'",
      argv__mode));
    }

    retc = 0;
  } catch (
    std::exception &
      what
    )
    {
    std::cerr
      << "oops: ``"
        << what.what()
      << "''." << std::endl
      ;
    }
  catch (...)
    {
    std::cerr
      << "oops?" << std::endl
      ;
    }

  return
    retc;
  }
