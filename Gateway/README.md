# Gateway

For the Gateway a Raspberry Pi 3 is used. For the Setup please follow the instruction.
1. Download and install [raspian](https://www.raspberrypi.org/downloads/raspbian/)
    1. You can easily follow the instruction on the raspberry website
2. Install [LoWPAN](https://github.com/RIOT-OS/RIOT/wiki/How-to-install-6LoWPAN-Linux-Kernel-on-Raspberry-Pi)
3. Install [Crosscoap](https://github.com/ibm-security-innovation/crosscoap)
    1. If you have problems with GO -> Set correct PATH!
4. Launch Crossoap with this line: crosscoap -listen [::]:5683 -backend http://127.0.0.1:8000
    1. Important! Use http://
