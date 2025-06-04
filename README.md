# GlitchFHE - Attacking Fully Homomorphic Encryption Using Fault Injection

![CoFHEE_EM](https://github.com/user-attachments/assets/b07500ba-2464-4ac4-b257-dd46c53d5954)

## Repo Details
This repository contains a software framework for fault injection and Python APIs to execute various polynomial operations in the [CoFHEE chip](https://github.com/momalab/CoFHEE).

## Interfacing with CoFHEE chip
### UART interface
We used the UART interface of CoFHEE to interact with the host PC. We used the FTDI's [UM232R development board](https://ftdichip.com/wp-content/uploads/2020/08/DS_UM232R.pdf) for USB to UART protocol conversion. 

### Clock, Reset, and Voltage supply
In addition to USB-to-UART conversion, the clock and I/O voltage of 3.3V required for CoFHEE are also sourced from the UM232R development board. And, one of the GPIO pins of the UM232R board can be used to control the reset pin of CoFHEE.
For the 1.2V core voltage supply, we used a simple [USB DC-DC converter](https://a.co/d/jcYxmFo).

### Python APIs


## License
You can use our codes under the [GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.en.html). 

## Cite us!
If you wish to acknowledge or reference our work, please use the citation below:

