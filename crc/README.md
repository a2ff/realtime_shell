# CRC subroutines

IBM Bisync CRC-16 with bytewise precalculated table (compile-time or run-time)

Include `crc16.h` and compile with `-D_CRC_PRECALC` etc. (automated in `Makefile`).

```C
// #ifdef _CRC16_PRECALC
static inline uint16_t crc16(uint16_t crc, uint8_t b);
uint16_t memcrc16(uint16_t crc, const void *buf, size_t len);

// #ifdef _CRC16_RUNTIME
void gen_crc16();
static inline uint16_t crc16rt(uint16_t crc, uint8_t b);
uint16_t memcrc16rt(uint16_t crc, const void *buf, size_t len);

// #ifdef _CRC16_DEBUG
void dump_crc16rt();
```

Generator is x^16+x^15+x^2+1 = 0x8005, also used by Modbus, LHA, ARC, ...

NOTE: because RS-232/422/485 transmits LSB-first, the LSB-first variation
of CRC-16-IBM would be preferable i.e. generator = 0xA001. Oh well...

## References
- https://en.wikipedia.org/wiki/Cyclic_redundancy_check
- https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks
