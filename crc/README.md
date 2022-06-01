# CRC subroutines

IBM Bisync CRC-16 with bytewise precalculated table (compile-time or run-time)

Include `crc16.h` and compile with `-D_CRC_PRECALC` etc. (automated in `Makefile`).

```C
// #ifdef _CRC16_PRECALC
u16 crc16(u16 accum, void *buf, int len);

// #ifdef _CRC16_RUNTIME
void gen_crc16dyn();
u16 crc16dyn(u16 accum, void *buf, int len);

// #ifdef _CRC16_DEBUG
void dump_crc16dyn();
```

Generator is x^16+x^15+x^2+1 = 0x8005, also used by Modbus, LHA, ARC, ...

NOTE: because RS-232/422/485 transmits LSB-first, the LSB-first variation
of CRC-16-IBM would be preferable i.e. generator = 0xA001. Oh well...

## References
- https://en.wikipedia.org/wiki/Cyclic_redundancy_check
- https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks
