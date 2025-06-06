# GlitchFHE - Attacking Fully Homomorphic Encryption (FHE) Using Fault Injection

![CoFHEE_EM](https://github.com/user-attachments/assets/b07500ba-2464-4ac4-b257-dd46c53d5954)

## Big Picture
GlitchFHE framework allows controlled Electro Magnetic (EM) fault injection during FHE evaluation operations, aiming to minimize the mean squared error (MSE) of the decrypted ciphertext relative to that obtained without fault injection. The main challenge addressed by GlitchFHE is determining the optimal timing and magnitude of the fault injection to achieve low MSE.

In this repository, we provide both a software framework and a hardware framework used by GlitchFHE.

## Repo Details
### Software Framework

### Hardware Framework
The hardware framework contains 
- Basic setup details of the  design under attack - [CoFHEE chip](https://github.com/momalab/CoFHEE), like how to interface with the host computer and its voltage/clock requirements.
- Python APIs to execute various polynomial operations in CoFHEE. One can inject faults during these API calls. There are also custom functions that can be used just to load and read back the polynomials to/from the internal SRAM memory. They're useful to find the right probe position in (x, y, z) dimension to inject the required amount of faults into the polynomials loaded in the memory; by injecting the fault after loading into the memory, then reading it back to check if it's corrupted and the amount of corruption.
- GlitchFHE Physical Attack Setup

#### Interfacing with CoFHEE chip
##### UART interface
We used the UART interface of CoFHEE to interact with the host PC. We used the FTDI's [UM232R development board](https://ftdichip.com/wp-content/uploads/2020/08/DS_UM232R.pdf) for USB to UART protocol conversion. 

##### Clock, Reset, and Voltage Supply
In addition to USB-to-UART conversion, the clock and I/O voltage of 3.3V required for CoFHEE are also sourced from the UM232R development board. And, one of the GPIO pins of the UM232R board can be used to control the reset pin of CoFHEE.
For the 1.2V core voltage supply, we used a simple [USB DC-DC converter](https://a.co/d/jcYxmFo).

##### Python APIs

##### Physical Attack Setup
![image](https://github.com/user-attachments/assets/07eb0188-c751-45bd-b891-2f5dc6696689)

## License
You can use our codes under the [GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.en.html). 

## Cite us!
If you wish to acknowledge or reference our work, please use the citation below:

