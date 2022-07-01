#ifndef _CRC16_H_
#define _CRC16_H_
#include <stdlib.h>
#include <stdint.h>

// Bytewise precalculated IBM Bisync CRC-16 (also used by Modbus, LHA, ARC)
// Generator is x^16+x^15+x^2+1 = 0x8005
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check
// https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks
// NOTE: because RS-232/422/485 transmits LSB-first, the LSB-first variation
// of CRC-16-IBM would be preferable i.e. generator = 0xA001. Oh well...

#ifdef _CRC16_PRECALC
static inline uint16_t crc16(uint16_t crc, uint8_t b) {
  extern const uint16_t _crc16[]; return (crc<<8)^_crc16[(crc>>8)^b]; }
uint16_t memcrc16(uint16_t crc, const void *buf, size_t len);
#endif

#ifdef _CRC16_RUNTIME
void gen_crc16();
static inline uint16_t crc16rt(uint16_t crc, uint8_t b) {
  extern uint16_t _crc16rt[]; return (crc<<8)^_crc16rt[(crc>>8)^b]; }
uint16_t memcrc16rt(uint16_t crc, const void *buf, size_t len);
#endif

#ifdef _CRC16_DEBUG
void dump_crc16rt();
#endif

#endif
/* vim: set textwidth=80 shiftwidth=2 softtabstop=2 expandtab : */
