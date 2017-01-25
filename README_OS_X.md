#### get the build deps
```
brew tap osx-cross/avr
brew install avr-libc
brew install dfu-programmer dfu-util

brew tap PX4/homebrew-px4
brew update
brew install gcc-arm-none-eabi
```

#### Choose a keymap name
```
export KEYMAPNAME="${LOGNAME}"
```

#### Get the code
```
git clone https://github.com/jackhumbert/qmk_firmware
(
  cd qmk_firmware/lib
  rmdir chibios         && git clone https://github.com/ChibiOS/ChibiOS chibios
  rmdir chibios-contrib && git clone https://github.com/ChibiOS/ChibiOS-Contrib chibios-contrib
  rmdir ugfx            && git clone https://git.ugfx.io/ugfx/ugfx.git
  # rmdir ugfx            && git clone https://github.com/Tecnologic/uGFX ugfx
)

( cd qmk_firmware; git submodule update --init --recursive)
```

#### Get a starting point
```
(
  cd qmk_firmware
  mkdir -p keyboards/ergodox/keymaps/${KEYMAPNAME}
  cp keyboards/ergodox/keymaps/default/keymap.c  keyboards/ergodox/keymaps/${KEYMAPNAME}/keymap.c
)
```

#### Customization and Flashing:

#### Hack up your file
```
vi qmk_firmware/keyboards/ergodox/keymaps/${KEYMAPNAME}/keymap.c
```

#### Build left hand firmware with:
```
( cd qmk_firmware/keyboards/ergodox; make subproject=infinity keymap=${KEYMAPNAME} ) 2>left.err |tee left.out
# Plug in the left hand keyboard only.
# Press the program button (back of keyboard, above thumb pad).
# Install the firmware with:
(cd qmk_firmware/keyboards/ergodox/infinity; sudo make infinity-${KEYMAPNAME}-dfu-util)
```


#### Build right hand firmware with:
```
(cd qmk_firmware/keyboards/ergodox/infinity; make infinity-${KEYMAPNAME} MASTER=right) 2>right.err |tee right.out
# Plug in the right hand keyboard only.
# Press the program button (back of keyboard, above thumb pad).
# Install the firmware with:
(cd qmk_firmware/keyboards/ergodox/infinity; sudo make infinity-${KEYMAPNAME}-dfu-util MASTER=right)
```
