## Custom qmk_firmware tadahw layout
Just some keymap changes over the default tadahw layout using [qmk_firmware](https://github.com/qmk/qmk_firmware/)

### Changes from the default

##### Default layer
- Make the `caps` key send `esc` when tapped and `fn` when hold
- Put the `tilda` key instead of `esc`
- Put the `delete` key instead of `tilda`

##### Function layer
- Add vim-like arrow keys to `hjkl`
- Add `prev` `play/pause` and `next` keys to `qwe`
- Add `volup` `mute` `voldown` volume controls to `asd`
- Add win lock to `Super` key
- Add backlight controls to `zxcv` and `space`

##### Game layer
- Remove `fn` on `esc` hold
- Make `tilda` key send `fn` on hold

### Layout preview
![Layout preview](KLE/keyboard-layout.png)
(the json used to generate this preview is on the `KLE` folder on this repo)

### Building firmware
Since this is in a separate repo for now you have to clone it to
`qmk_firmware/keyboards/tadahw/keymaps/<name>`

Then run the below command to generate the `FLASH.bin` file
`$ make tadahw:<name>:flashbin`

Of course replacing `<name>` with the name you wish to use for the keymap