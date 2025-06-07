# __GlitchFHE - Attacking Fully Homomorphic Encryption (FHE) Using Fault Injection -- Software-based Experiments__


This directory contains all the codes and corresponding documentation for the software-based experiments on:
- CKKS and BFV implementations of polynomial evaluation
- CKKS and BFV implementations of image classification
- CKKS implementation of image processing


### __Polynomial Evaluation__

We peform GlitchFHE on the CKKS and BFV implementations of polynomial evaluation that are opensourced by Microsoft SEAL-3.6 (https://github.com/microsoft/SEAL/tree/3.6.0)


#### __Installation Instructions__

- Follow the instructions to install SEAL-3.6 from https://github.com/microsoft/SEAL/tree/3.6.0
- Copy the modified SEAL repository from ./polynomial_evaluation/SEAL for the installation. We have modified evaluator.cpp and rns.cpp codes for GlitchFHE attack in ./polynomial_evaluation/SEAL/native/src/


#### __File Information__

- The codes for attacking CKKS and BFV-based polynomial evaluation are there in ./polynomial_evaluation/SEAL/native/examples/
- Attack on BFV-based polynomial evaluation is in ./polynomial_evaluation/SEAL/native/examples/1_bfv_basics.cpp
- Attack on CKKS-based polynomial evaluation is in ./polynomial_evaluation/SEAL/native/examples/4_ckks_basics.cpp


#### __Instructions for Running the Codes__

- cd ./polynomial_evaluation/SEAL/native/examples/build/
- make
- ./polynomial_evaluation/SEAL/native/examples/build/bin/sealexamples
- Enter 1 to run BFV-based attack and 4 to run CKKS-based attack


#### __Attacking BFV-based polynomial evaluation__

In ./polynomial_evaluation/SEAL/native/examples/1_bfv_basics.cpp, set the values for the following variables

- flag     - Set it to 1 to enable fault injection, else set it to 0
- filename - Provide the name for output log


#### __Attacking CKKS-based polynomial evaluation__

In ./polynomial_evaluation/SEAL/native/examples/4_bfv_basics.cpp, set the values for the following variables


- flag     - Set it to 1 to enable fault injection, else set it to 0
- filename - Provide the name for output log
- depth    - Indicates the multiplicative depth at which fault injection is to be performed. The valid values for this application are 2, 3 or 4.


### __Image Classification__

We perform GlitchFHE 

- on the BFV implementation of cryptonets - an image classification accelerator implementated in Microsoft SEAL-3.7.2 (https://github.com/microsoft/SEAL/tree/3.7.2). We have taken this implementatoon from [1][2]
- on the CKKS implementation of cryptonets. We have modified the BFV-based cryptonets implementation from [1][2] to obtain this implementation


#### __File Information__

- The implementation of CKKS-based cryptonets is in ./cryptonets/seal_standalone_ckks_attack
- The implementation of BFV-based cryptonets is in ./cryptonets/seal_standalone_bfv_attack


#### __Installation Instructions__

- Please follow instructions in https://github.com/microsoft/SEAL/tree/3.7.2 to install SEAL in the repository ./cryptonets/seal_standalone_bfv_attack/e3_seal.372/ and ./cryptonets/seal_standalone_ckks_attack/e3_seal.372/

- Note that we have modified the corresponding SEAL repositories to enable Fault injection

- Copy the corresponding lib.seal.a files to seal_unx/target and seal_unx/native directories


#### __Instructions to Run the codes__


##### __CKKS-based Cryptonets__

- make all
- make run


##### __BFV-based Cryptonets__

- make all
- make run


### __Image Processing__

We perform GlitchFHE 

- on the CKKS implementation of image processing in (https://github.com/microsoft/EVA). 

#### __Installation Instructions__

- Please follow the instructions in https://github.com/microsoft/EVA for installation
- We have modified rns.cpp in the SEAL source code to perform fault injection and copied the corresponding binary in the repository we shared in ./Image_Processing/EVA/

#### __Instructions for Running the Code__

- cp ./Image_Processing/EVA/examples/
- python image_processing.py 



#### __References__

[1] Chielle, E., Mazonka, O., Gamil, H., Tsoutsos, N. G., & Maniatakos, M. (2018). E3: A framework for compiling C++ programs with encrypted operands. Cryptology ePrint Archive, Report 2018/1013. Retrieved from https://ia.cr/2018/1013

[2] Chielle, E., Mazonka, O., Gamil, H., & Maniatakos, M. (2022). Accelerating fully homomorphic encryption by bridging modular and bit-level arithmetic. In Proceedings of the 41st International Conference on Computer-Aided Design (ICCAD '22). Association for Computing Machinery. https://doi.org/10.1145/3508352.3549415
