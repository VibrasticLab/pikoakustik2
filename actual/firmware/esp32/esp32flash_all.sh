#!/bin/bash

make -j$(nproc) bootloader-flash
make -j$(nproc) partition_table-flash
make -j$(nproc) app-flash
