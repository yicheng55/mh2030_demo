# ISR, SPI, DMA, and Timeout Review

## SPI efficiency

Register access is byte-oriented and expected to be frequent during init, PHY
busy waits, link polling, and TX completion polling. RX and TX payload paths use
burst-style FIFO commands: one MRCMD/MWCMD opcode followed by all payload bytes.
That is the correct DM9051 access pattern.

Polling FIFO transfer still loops byte-by-byte through
`dm9051_mh2030a_transfer_byte()`. DMA mode improves only FIFO payload transfer;
register access remains polling, which is reasonable because registers are
short transactions.

## RX efficiency

RX checks MRCMDX twice, reads a 4-byte header, validates status/length, then
reads the payload in one FIFO transaction. Discard uses 32-byte chunks, which is
safe but slower for large malformed frames.

## TX efficiency

TX writes length registers, writes one contiguous FIFO payload, sets TXREQ, and
waits for TXREQ clear by default. The default wait can block up to
`DM9051_TX_WAIT_TIMEOUT_US` iterations with 1 us delays.

## Timeout design

- SPI polling timeout is a loop-count value from `config->spi_timeout`, not a
  calibrated time unit.
- DMA timeout multiplies `spi_timeout * len`; for full frames this can become a
  very long busy wait.
- PHY busy timeout is 500 iterations with 1 us delay.
- TX completion timeout is 100000 iterations with 1 us delay by default.

All timeout paths return error codes up through HAL/core, and lwIP maps send
failure to `ERR_IF`. The uIP adapter records last RX status.

## Recovery after timeout

Recovery is partial:

- RX malformed status/length can discard or reset/restart the chip after error
  thresholds.
- SPI/DMA timeout cleans up DMA enable/flags and releases CS.
- TX timeout returns `DM9051_ERR_TIMEOUT`, but does not reset TX FIFO or restart
  the chip.
- PHY timeout clears EPCR before returning.

## ISR safety

The EXTI ISR does not access SPI or DMA. It only records an event and clears
EXTI pending. That is suitable for bare-metal systems. SPI and DMA operations
should remain in the main loop.

