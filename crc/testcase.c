#include <stdio.h>
#include <stdlib.h>
#include "crc16.h"

int main(int argc, const char *argv[]) {
  printf("*** TEST CASE: crc16 ***\n");
  byte b[] = { 0xDD, 0x01, 0x14, 0x40, 0x5D, 0x97 }; u16 crc;
#ifdef _CRC16_PRECALC
  crc = crc16(0xFFFF, b, sizeof(b)-sizeof(u16));
  printf("\nPRECALCULATED crc16=%04X is %s (expected 0x5D97)\n", crc, crc==0x5D97 ? "correct" : "wrong");
  crc = crc16(0xFFFF, b, sizeof(b));
  printf("self-checking crc16=%04X is %s (expected 0)\n", crc, crc==0 ? "correct" : "wrong");
#endif

#ifdef _CRC16_RUNTIME
  gen_crc16dyn();
  crc = crc16dyn(0xFFFF, b, sizeof(b)-sizeof(u16));
  printf("\nRUNTIME crc16=%04X is %s (expected 0x5D97)\n", crc, crc==0x5D97 ? "correct" : "wrong");
  crc = crc16dyn(0xFFFF, b, sizeof(b));
  printf("self-checking crc16=%04X is %s (expected 0)\n", crc, crc==0 ? "correct" : "wrong");
#ifdef _CRC16_DEBUG
  dump_crc16dyn();
#endif
#endif

  printf("\n*** DONE ***\n"); return EXIT_SUCCESS;
}

/* vim: set textwidth=80 shiftwidth=2 softtabstop=2 expandtab : */
