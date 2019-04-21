#!/bin/bash

aarch64-linux-gnu-as -c main.s -o main.o
aarch64-linux-gnu-ld main.o -o asm_example
