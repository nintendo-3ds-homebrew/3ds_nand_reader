# 3ds_nand_reader

Tool for dumping 3ds nand (For unix system).

##Usage :

1) Dowload the tool here : https://github.com/SegFault42/3ds_nand_reader/releases/tag/v0.1

2) Extract 3ds_nand_reader from .zip in Desktop

3) Open a terminal

4) Go to the 3DS_nand_validator folder
    ```bash
    cd ~/Desktop/3ds_nand_reader
    ```
    
5) Launch the tool as root 
    ```bash
    sudo ./3ds_nand_reader 2
    ```
    ```bash
    Usage : ./3ds_nand_reader 1 (for one dump)
		    ./3ds_nand_reader 2 (for two dumps)
    ```
 
6) Plug your card reader in your PC/Mac

7) Press enter :)

# Troubleshooting

If your 3ds is not detected by the soft verify the error code :
https://www.3dbrew.org/wiki/Bootloader#Error_Codes

You should have :

```bash
    BOOTROM 8046
    ERRCODE: 00F800FE
            00000000 00000000
            00000200 00400000
```

Be sure to launch the soft first then plug the reader in your 3ds and then plug your sd reader in usb and press key.

If you don't have a sd reader you can make your own by following this link :
https://gbatemp.net/threads/tutorial-noob-friendly-nand-dumping-2ds-3ds-3ds-xl-n3ds-n3ds-xl.414498/
