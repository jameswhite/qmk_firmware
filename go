#!/bin/bash
#(
#  cd keyboard/ergodox/
#  make -f Makefile.lufa clean
#  make -f Makefile.lufa jameswhite
#  ./keymap_renderer.pl keymap_jameswhite.h > jameswhite.map
#  mv ergodox_lufa.hex ~/Downloads/_jameswhite_lufa.hex
#) && (clear; cat keyboard/ergodox/jameswhite.map)

(
  # cd qmk_firmware
  export KEYMAPNAME='jameswhite'
  make clean && \
  make ergodox_ez:${KEYMAPNAME} && \
  cp ergodox_ez_${KEYMAPNAME}.hex ~/Desktop/
  ls -l ~/Desktop/ergodox_ez_${KEYMAPNAME}.hex
)
