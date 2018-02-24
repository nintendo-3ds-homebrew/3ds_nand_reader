
# 3ds_nand_reader
This tool is provided to help you perform a `NAND dump` on your `3DS`

### Prerequisites
* Unix system (Linux)
## Installation
You can either compile and install the tool from sources or directly download the binary.
#### via sources
```bash
git clone https://github.com/SegFault42/3ds_nand_reader.git && cd 3ds_nand_reader && make
```
#### via direct download 
1. download the latest version [3ds nand reader v0.1](https://github.com/SegFault42/3ds_nand_reader/releases/download/0.1/3ds_nand_reader.zip)
2. unzip it
3. open your terminal, go to `3ds_nand_validator` folder

## Usage

1. run the tool as root.
    ```bash
    sudo ./3ds_nand_reader 1
    ```
    ```bash
    Usage : ./3ds_nand_reader 1 (one dump)
		    ./3ds_nand_reader 2 (two dumps)
    ```
 
2. Plug your card reader in your computer.

3.  Press enter :) 
## Troubleshooting

If your `3DS` is not detected by the tool, please have a look at some  [known error codes](https://www.3dbrew.org/wiki/Bootloader#Error_Codes).
you should see:
```javascript
 BOOTROM  8046
 ERRCODE: 00F800FE
          00000000 00000000
          00000200 00400000
```

⚠️ **be sure to respect to following orders:** 
1. Launch the tool
2. Plug the reader in your `3DS`
3. Plug your `SD reader` in usb.
4. Press key.

If you do not have any `SD reader` you can make your own by following this [tutorial](https://gbatemp.net/threads/tutorial-noob-friendly-nand-dumping-2ds-3ds-3ds-xl-n3ds-n3ds-xl.414498/).
