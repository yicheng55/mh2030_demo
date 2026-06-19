# AT32F403A DM9051 Smoke Test

## Build

Add to your Keil MDK project:

### Include paths
```
..\dm9051_driver\core\inc
..\dm9051_driver\hal\inc
..\dm9051_driver\ports\at32f403a
..\dm9051_driver\examples\at32f403a_demo
```

### Source files
```
dm9051_driver\core\src\dm9051_core.c
dm9051_driver\ports\at32f403a\dm9051_hal_at32f403a_spi1.c
dm9051_driver\ports\at32f403a\at32f403a_board.c
dm9051_driver\ports\at32f403a\delay.c
dm9051_driver\examples\at32f403a_demo\main_at32f403a_smoke.c
dm9051_driver\examples\at32f403a_demo\dm9051_at32f403a_smoke.c
```

### Defines
```
USE_STDPERIPH_DRIVER
```

## Expected Output

```
[AT32F403A] board init
[AT32F403A] SYSCLK=216000000 HCLK=216000000 PCLK1=54000000 PCLK2=108000000
[AT32F403A] DM9051 SPI bus initialized (polling transfer)
[DM9051] AT32F403A polling smoke start
[DM9051] open status=0 found=1 VID=0x0A46 PID=0x9051 CHIPR=0x19
```
