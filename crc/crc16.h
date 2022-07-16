#ifndef _CRC16_H_
#define _CRC16_H_
#include <stdlib.h>
#include <stdint.h>

// Byte-wise precalculated CRC-16
// ANSI generator x^16+x^15+x^2+1 = 0x8005; init = 0xFFFF; no final xor
// CCITT generator x^16+x^12+x^5+1 = 0x1021; init = 0xFFFF; no final xor
// https://en.wikipedia.org/wiki/Cyclic_redundancy_check
// https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks
// http://srecord.sourceforge.net/crc16-ccitt.html

#ifdef _CRC16_PRECALC
static inline uint16_t crc16ansi(uint16_t crc, uint8_t b) {
  extern const uint16_t _crc16ansi[];
  return (crc<<8)^_crc16ansi[(crc>>8)^b]; }
uint16_t memcrc16ansi(uint16_t crc, const void *buf, size_t len);

static inline uint16_t crc16ccitt(uint16_t crc, uint8_t b) {
  extern const uint16_t _crc16ccitt[];
  return (crc<<8)^_crc16ccitt[(crc>>8)^b]; }
uint16_t memcrc16ccitt(uint16_t crc, const void *buf, size_t len);
#endif

#ifdef _CRC16_RUNTIME
void gen_crc16();
static inline uint16_t crc16ansi_rt(uint16_t crc, uint8_t b) {
  extern uint16_t _crc16ansi_rt[];
  return (crc<<8)^_crc16ansi_rt[(crc>>8)^b]; }
uint16_t memcrc16ansi_rt(uint16_t crc, const void *buf, size_t len);

static inline uint16_t crc16ccitt_rt(uint16_t crc, uint8_t b) {
  extern uint16_t _crc16ccitt_rt[];
  return (crc<<8)^_crc16ccitt_rt[(crc>>8)^b]; }
uint16_t memcrc16ccitt_rt(uint16_t crc, const void *buf, size_t len);
#endif

#define CRC16_CCITT_PREPEND 0x1D0F

#ifdef _CRC16_DEBUG
void dump_crc16();
#endif

#endif
/* vim: set textwidth=80 shiftwidth=2 softtabstop=2 expandtab : */
