#!/bin/bash

gcc  -fsanitize=address -g  -I ../ main.c ../cvec.c && ./a.out

