#!/usr/bin/bash

#st-flash --connect-under-reset erase
st-flash --reset --connect-under-reset --format ihex write ./build/stm32ht.hex
