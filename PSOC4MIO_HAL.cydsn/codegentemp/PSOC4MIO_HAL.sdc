# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Users\nray\Documents\GitHub\PSOC4MIOHAL\PSOC4MIO_HAL.cydsn\PSOC4MIO_HAL.cyprj
# Date: Wed, 01 Jun 2016 09:15:25 GMT
#set_units -time ns
create_clock -name {console_SCBCLK(FFB)} -period 4333.333333333333 -waveform {0 2166.66666666667} [list [get_pins {ClockBlock/ff_div_2}]]
create_clock -name {SPI_1_SCBCLK(FFB)} -period 62.5 -waveform {0 31.25} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {ADC_1_intClock(FFB)} -period 1000 -waveform {0 500} [list [get_pins {ClockBlock/ff_div_10}]]
create_clock -name {gpio1_SCBCLK(FFB)} -period 625 -waveform {0 312.5} [list [get_pins {ClockBlock/ff_div_4}]]
create_clock -name {LCD_SCBCLK(FFB)} -period 8687.5 -waveform {0 4343.75} [list [get_pins {ClockBlock/ff_div_5}]]
create_clock -name {CyRouted1} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/dsi_in_0}]]
create_clock -name {CyWCO} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/wco}]]
create_clock -name {CyLFCLK} -period 30517.578125 -waveform {0 15258.7890625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyIMO} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyHFCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/hfclk}]]
create_clock -name {CySYSCLK} -period 20.833333333333332 -waveform {0 10.4166666666667} [list [get_pins {ClockBlock/sysclk}]]
create_generated_clock -name {console_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 209 417} -nominal_period 4333.333333333333 [list]
create_generated_clock -name {SPI_1_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 3 7} [list]
create_generated_clock -name {ADC_1_intClock} -source [get_pins {ClockBlock/hfclk}] -edges {1 49 97} [list]
create_generated_clock -name {gpio1_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 31 61} [list]
create_generated_clock -name {LCD_SCBCLK} -source [get_pins {ClockBlock/hfclk}] -edges {1 417 835} [list]


# Component constraints for D:\Users\nray\Documents\GitHub\PSOC4MIOHAL\PSOC4MIO_HAL.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Users\nray\Documents\GitHub\PSOC4MIOHAL\PSOC4MIO_HAL.cydsn\PSOC4MIO_HAL.cyprj
# Date: Wed, 01 Jun 2016 09:15:21 GMT
