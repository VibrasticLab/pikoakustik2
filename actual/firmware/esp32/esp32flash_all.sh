#!/bin/bash

# USE THIS EVERYTIME CHANGING UART NUMBER

make bootloader-flash
make partition_table-flash
make app-flash
