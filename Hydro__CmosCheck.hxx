#pragma once

#ifndef \
HYDRO__CMOSCHECK__MAGIC
#define \
HYDRO__CMOSCHECK__MAGIC "Steven E. Ranck"
#endif /*
HYDRO__CMOSCHECK__MAGIC */

enum
__hydro__cmoscheck__sector
{
  HYDRO__CMOSCHECK__S__A = 0x380
};
enum
__hydro__cmoscheck__field
{
// Note: Magic offset.
  HYDRO__CMOSCHECK__F__MAGIC = 0x20,

// Note: Checksum for even and off double words.
  HYDRO__CMOSCHECK__F__CHECKSUM__A__E = 0x24,
  HYDRO__CMOSCHECK__F__CHECKSUM__A__O = 0x25,
// Note: Dirty marker.  Shall be zero.
  HYDRO__CMOSCHECK__F__DIRTY = 0x26,
// Note: Index marker.  Always incremented when the bank is written.
  HYDRO__CMOSCHECK__F__INDEX__LO = 0x27,
  HYDRO__CMOSCHECK__F__INDEX__HI = 0x28,
// Note: Checksum random seed for lower and upper sections.  These are initialized
// from x64 hardware tick counter.
  HYDRO__CMOSCHECK__F__CHECKSUM__B__L = 0x29,
  HYDRO__CMOSCHECK__F__CHECKSUM__B__U = 0x2a,
// Note: Ident marker.  Zero if lower CMOS bank, non-zero if upper CMOS bank.
  HYDRO__CMOSCHECK__F__IDENT = 0x2b,
// Note: Write marker.  If all ones, successfully written (recovered).
  HYDRO__CMOSCHECK__F__WRITE = 0x2c
};
enum
__hydro__cmoscheck__size
{
  HYDRO__CMOSCHECK__S__MAGIC = 0x04,
  HYDRO__CMOSCHECK__S__CHECKSUM__A = 0x40,
  HYDRO__CMOSCHECK__S__CHECKSUM__B = 0x20
};
enum
__hydro__cmoscheck__offset
{
// Note: Lower offset.  Contains the actual data.
  HYDRO__CMOSCHECK__O__LOWER = 0x00,
// Note: Upper offset.  Contains checksum words.
  HYDRO__CMOSCHECK__O__UPPER = 0x60
};

extern
void
Hydro__CmosCheck(
  const
  hydro__idesector *
  const
    data__sector
  );
