#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "crc16.h"

#define WRONG(c, s) ((c) ? "CORRECT": \
 "\e[31m\e[5m\e[7mWRONG (expected "s")\e[39m\e[49m\e[0m")
// ...VSCode's terminal has incomplete VT100 emulation (blink, bg color)
// hence the "reverse"+"fg color red" escape sequence

static inline uint64_t ts_ns(const struct timespec *ts) {
  return ts->tv_sec*1000000000+ts->tv_nsec; }
static inline uint64_t ts() {
  struct timespec ts; int b = timespec_get(&ts, TIME_UTC); assert(b==TIME_UTC); return ts_ns(&ts); }

int main(int argc, const char *argv[]) {
  printf("*** TEST CASE: crc16ansi, crc16ccitt ***\n");
  uint16_t crc; uint64_t t1, t2;
  uint8_t b[] = { 0xDD, 0x01, 0x14, 0x40, 0x5D, 0x97 };
  uint8_t b2[] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', 0xE5, 0xCC };

#ifdef _CRC16_PRECALC
  crc = memcrc16ansi(0xFFFF, b, sizeof(b)-sizeof(uint16_t));
  printf("\nPRECALCULATED crc16ansi=%04X is %s\n", crc, WRONG(crc==0x5D97, "0x5D97"));
  crc = memcrc16ansi(0xFFFF, b, sizeof(b));
  printf("self-checking crc16ansi=%04X is %s\n", crc, WRONG(crc==0, "0"));

  crc = memcrc16ccitt(CRC16_CCITT_PREPEND, b2, sizeof(b2)-sizeof(uint16_t));
  printf("\nPRECALCULATED crc16ccitt=%04X is %s\n", crc, WRONG(crc==0xE5CC, "0xE5CC"));
  crc = memcrc16ccitt(CRC16_CCITT_PREPEND, b2, sizeof(b2));
  printf("self-checking crc16ccitt=%04X is %s\n", crc, WRONG(crc==0, "0"));

  extern const uint16_t _crc16ansi[256];
  t1 = ts();
  for(int i = 0; i<1000; ++ i) crc = memcrc16ansi(0xFFFF, _crc16ansi, 16);
  t2 = ts();
  printf("\n16-byte crc16ansi=%04X is %s elapsed=%lluns\n",
   crc, WRONG(crc==0x07F2, "0x07F2"), (t2-t1)/1000);

  t1 = ts();
  for(int i = 0; i<100; ++ i) crc = memcrc16ansi(0xFFFF, _crc16ansi, sizeof(_crc16ansi));
  t2 = ts();
  printf("%lu-byte crc16ansi=%04X is %s elapsed=%lluns\n",
   sizeof(_crc16ansi), crc, WRONG(crc==0xE668, "0xE668"), (t2-t1)/100);
#endif

#ifdef _CRC16_RUNTIME
  gen_crc16();
  crc = memcrc16ansi_rt(0xFFFF, b, sizeof(b)-sizeof(uint16_t));
  printf("\nRUNTIME crc16ansi=%04X is %s\n", crc, WRONG(crc==0x5D97, "0x5D97"));
  crc = memcrc16ansi_rt(0xFFFF, b, sizeof(b));
  printf("self-checking crc16ansi=%04X is %s\n", crc, WRONG(crc==0, "0"));

  crc = memcrc16ccitt_rt(CRC16_CCITT_PREPEND, b2, sizeof(b2)-sizeof(uint16_t));
  printf("\nRUNTIME crc16ccitt=%04X is %s\n", crc, WRONG(crc==0xE5CC, "0xE5CC"));
  crc = memcrc16ccitt_rt(CRC16_CCITT_PREPEND, b2, sizeof(b2));
  printf("self-checking crc16ccitt=%04X is %s\n", crc, WRONG(crc==0, "0"));
#ifdef _CRC16_DEBUG
  puts("\nByte-wise precalculated tables:\n"); dump_crc16();
#endif
#endif

  printf("*** DONE ***\n"); return EXIT_SUCCESS;
}

/* vim: set textwidth=80 shiftwidth=2 softtabstop=2 expandtab : */
