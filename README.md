# Smart Kitchen

The kitchen ist he heart of any apartment, so why should it not be intelligent?!
At the present time more and more devices are interconnected, the so-called IOT-Devices. 
No progress is a step backwards, that is why the Kitchen must also be smart. 
The project Smart Kitchen focus primarily on the intelligent fridge.

## Smart Fridge

With help of the smart fridge the existing food ingredients of the fridge will be presented on a website.
The foodstuffs are recognised and detected by means of NFC-tags.
To determine if the food is have changed, the weight will be measured by a pressure sensor.

![Concept](/images/concept.png)

## Hardware

The following hardware is used:

### RaspberryPi 3 with 6LoWPAN
<p align="center">
  <img src="/images/raspberryPi3.png" width="300"/>
</p>

### Ateml SAM R21 Xplained Pro
<p align="center">
  <img src="/images/atmel_board.png" width="350"/>
</p>

with an **NFC Shield PN532** to detected the NFC-tags and an analog pressure sensor to measure weight.


<p align="center">
  <img src="/images/PN532.PNG" width="250"/>
</p>

## Software Architecture

This project based on the following software architecture

<p align="center">
  <img src="/images/software_architecture.png" width="800"/>
</p>
