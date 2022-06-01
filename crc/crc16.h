#ifndef _CRC16_H_
#define _CRC16_H_
#include "portability.h"

// Bytewise precalculated IBM Bisync CRC-16 (also used by Modbus, LHA, ARC)
// Generator is x^16+x^15+x^2+1 = 0x8005
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check
// https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks
// NOTE: because RS-232/422/485 transmits LSB-first, the LSB-first variation
// of CRC-16-IBM would be preferable i.e. generator = 0xA001. Oh well...

u16 crc16(u16 accum, void *buf, int len);     // #ifdef _CRC16_PRECALC

void gen_crc16dyn();                          // #ifdef _CRC16_RUNTIME
u16 crc16dyn(u16 accum, void *buf, int len);

void dump_crc16dyn();                         // #ifdef _CRC16_DEBUG

#endif
/* vim: set textwidth=80 shiftwidth=2 softtabstop=2 expandtab : */
