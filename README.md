# __GlitchFHE - Attacking Fully Homomorphic Encryption (FHE) Using Fault Injection__

![CoFHEE_EM](https://github.com/user-attachments/assets/b07500ba-2464-4ac4-b257-dd46c53d5954)

## __Big Picture__
GlitchFHE framework allows controlled Electro Magnetic (EM) fault injection during FHE evaluation operations, aiming to minimize the mean squared error (MSE) of the decrypted ciphertext relative to that obtained without fault injection. The main challenge addressed by GlitchFHE is determining the optimal timing and magnitude of the fault injection to achieve low MSE.

In this repository, we provide both a software framework and a hardware framework used by GlitchFHE.

## __Repo Details__
### __GlitchFHE Software Framework__

This directory (Software-Experiments) contains all the codes and corresponding documentation for the software-based experiments on:
- CKKS and BFV implementations of polynomial evaluation
- CKKS and BFV implementations of image classification
- CKKS implementation of image processing

### __GlitchFHE Hardware Framework__
The hardware framework contains 
- Basic setup details of the  design under attack - [CoFHEE chip](https://github.com/momalab/CoFHEE), like how to interface with the host computer and its voltage/clock requirements.
- Python APIs to execute various polynomial operations in CoFHEE. One can inject faults during these API calls. There are also custom functions that can be used just to load and read back the polynomials to/from the internal SRAM memory. They're useful to find the right probe position in (x, y, z) dimension to inject the required amount of faults into the polynomials loaded in the memory; by injecting the fault after loading into the memory, then reading it back to check if it's corrupted and the amount of corruption.
- GlitchFHE Physical Attack Setup

#### __Interfacing with CoFHEE chip__
##### __UART interface__
We used the UART interface of CoFHEE to interact with the host PC. We used the FTDI's [UM232R development board](https://ftdichip.com/wp-content/uploads/2020/08/DS_UM232R.pdf) for USB to UART protocol conversion. 

##### __Clock, Reset, and Voltage Supply__
In addition to USB-to-UART conversion, the clock and I/O voltage of 3.3V required for CoFHEE are also sourced from the UM232R development board. And, one of the GPIO pins of the UM232R board can be used to control the reset pin of CoFHEE.
For the 1.2V core voltage supply, we used a simple [USB DC-DC converter](https://a.co/d/jcYxmFo).

##### __[Python APIs](CoFHEE_API)__
###### __Important Files__: 
- [CoFHEE Memory Map](CoFHEE_API/CoFHEE_header.py)
- Files to update the FTDI parameters.
   - Update CBUS# used as gpio to reset CoFHEE in [CoFHEE_API/reset.c](CoFHEE_API/reset.c)
   - Update VID/PID in (CoFHEE_API/reset.c)
   - Update ser.port and ser.baudrate in files [CoFHEE_API/boost_baudrate.py (CoFHEE_API/boost_baudrate.py) and [CoFHEE_API/CoFHEE_tasks.py](CoFHEE_API/CoFHEE_tasks.py).
 - [CoFHEE Reset code](CoFHEE_API/reset.c) . Compile and execute this code to reset CoFHEE.
   
###### __Important Functions__:
All the main functions to perform polynomial-level operations like NTT/iNTT/HadamardMul/PwiseAdd/PwiseSub and high-level operations like polynomial multiplication, Rescale, etc, on the CoFHEE chip are in file : [CoFHEE_API/CoFHEE_tasks.py](CoFHEE_API/CoFHEE_tasks.py). Refer to [CoFHEE documentation](https://arxiv.org/abs/2204.08742) for more details.
 - fhe_rescale_mod (all_pre_tow, qi,    N,   addri, scratch_addr, towL_twiddle_addr): To perform rescale operation when the polynomials are stored in iNTT format
 - fhe_rescale_ntt_mod (all_pre_tow, qi,    N,   addri, scratch_addr, towL_twiddle_addr): To perform rescale operation when the polynomials are stored in NTT format
 - fault_load_coeff (poly, q, N): To load the polynomial to internal SRAM with base address CoFHEE_header.FHEMEM5_BASE
 - fault_load_read_full_range (poly, k, N) - Read back the data from the SRAM with base address CoFHEE_header.FHEMEM5_BASE
 
###### __Pseudo Code to detect the right probe position for a successful fault injection__
```text
while (No fault detected):
    Load seal_coeffs.coeff1 to internal SRAM:
        CoFHEE_main.CoFHEE_tasks.fault_load_coeff(seal_coeffs.coeff1, 1099510890497, 8192)

    Manually change the probe’s voltage and/or (x, y, z) coordinates

    Read back seal_coeffs.coeff1 from internal SRAM:
        CoFHEE_main.CoFHEE_tasks.fault_load_read_full_range(seal_coeffs.coeff1, 0, 8192)
```
##### __Physical Attack Setup__
![image](https://github.com/user-attachments/assets/07eb0188-c751-45bd-b891-2f5dc6696689)

## License
You can use our codes under the [GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.en.html). 

<!--
## Cite us!
If you wish to acknowledge or reference our work, please use the citation below:
-->
