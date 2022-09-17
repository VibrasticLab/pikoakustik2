#!/usr/bin/bash

make -j4 all
#st-flash --connect-under-reset erase
st-flash --reset --connect-under-reset --format ihex write ./build/pikof303rb.hex
