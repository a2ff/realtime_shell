# CRC subroutines

Byte-wise precalculated (compile-time or run-time) CRC subroutines.
The run-time precalculation subroutine has been used for generated the compile-time constant table and is the bit-wise canonical CRC algorithm.

## ANSI/IBM Bisync CRC-16
Generator is x^16+x^15+x^2+1 = 0x8005; init = 0xFFFF; no final xor.

NOTE: because RS-232/422/485 transmits LSB-first, the reversed CRC-16-ANSI would have better error detection, i.e. generator 0xA001. 

## CCITT CRC-16
Generator is x^16+x^12+x^5+1 = 0x1021; init = 0xFFFF; prepend 0x0000; no final xor.

Prepending a null word16 to an existing in-memory buffer is a pain, but since we provide a chainable `memcrc16ccitt()` one can just start by calling it with initial crc value `0xFFFF` on a 1-word buffer containing `0x0000`, which yields `0x1D0F`.

Therefore it is equivalent to just start with `memcrc16ccitt(0x1D0F, …)` or `memcrc16ccitt(CRC16_CCITT_PREPEND,  …)`.

If instructed to compute with an initial 0xFFFF and no prepended 0x0000, then just call `memcrc16ccitt(0xFFFF, …)` — just be aware this is not strictly speaking CRC-16-CCITT.

NOTE: ditto, generator 0x8408 would be better. 

## API
Include `crc16.h` and compile with `-D_CRC_PRECALC` etc. (automated in `Makefile`).

`memcrc16xx()` can be chained on split buffers, so it is up to the caller to pass the initial CRC value and apply the final xor as needed for each CRC algorithm.

```C
#define CRC16_CCITT_PREPEND …

// #ifdef _CRC16_PRECALC
static inline uint16_t crc16ansi(uint16_t crc, uint8_t b);
uint16_t memcrc16ansi(uint16_t crc, const void *buf, size_t len);

static inline uint16_t crc16ccitt(uint16_t crc, uint8_t b);
uint16_t memcrc16ccitt(uint16_t crc, const void *buf, size_t len);

// #ifdef _CRC16_RUNTIME
void gen_crc16();
static inline uint16_t crc16ansi_rt(uint16_t crc, uint8_t b);
uint16_t memcrc16ansi_rt(uint16_t crc, const void *buf, size_t len);

static inline uint16_t crc16ccitt_rt(uint16_t crc, uint8_t b);
uint16_t memcrc16ccitt_rt(uint16_t crc, const void *buf, size_t len);

// #ifdef _CRC16_DEBUG
void dump_crc16();
```

## References
- https://en.wikipedia.org/wiki/Cyclic_redundancy_check
- https://en.wikipedia.org/wiki/Computation_of_cyclic_redundancy_checks
- http://srecord.sourceforge.net/crc16-ccitt.html

../..