# __GlitchFHE - Attacking Fully Homomorphic Encryption Using Fault Injection: Software Framework__

This directory contains all the codes and corresponding documentation for the GlitchFHE experiments on:
- CKKS and BFV implementations of polynomial evaluation
- CKKS and BFV implementations of image classification
- CKKS implementation of image processing


## __Polynomial Evaluation__

We perform GlitchFHE on the CKKS and BFV implementations of polynomial evaluation provided with [Microsoft SEAL 3.6](https://github.com/microsoft/SEAL/tree/3.6.0). Importantly, please use the modified copy of
the SEAL library provided with this repository.

### __Installation Instructions__

The modified SEAL library is provided in [polynomial_evaluation/SEAL](polynomial_evaluation/SEAL). Specifically, we have modified the `evaluator.cpp` and `rns.cpp` codes in [polynomial_evaluation/SEAL/native/src/seal/](polynomial_evaluation/SEAL/native/src/seal/) to support GlitchFHE.
Please follow the instructions in [polynomial_evaluation/SEAL/README.md](polynomial_evaluation/SEAL/README.md) to build this version of SEAL.
Note that this follows the same instructions as the baseline SEAL library.

### __File Information__

The codes for GlitchFHE attacks are integrated into [polynomial_evaluation/SEAL/native/examples/](polynomial_evaluation/SEAL/native/examples/).
More specifically, the attack on BFV-based polynomial evaluation is integrated in [polynomial_evaluation/SEAL/native/examples/1_bfv_basics.cpp](polynomial_evaluation/SEAL/native/examples/1_bfv_basics.cpp), and the
attack on CKKS-based polynomial evaluation is integrated in [polynomial_evaluation/SEAL/native/examples/4_ckks_basics.cpp](polynomial_evaluation/SEAL/native/examples/4_ckks_basics.cpp)

### __Instructions for Running the Codes__

First, prepare the codes as follows.

In [polynomial_evaluation/SEAL/native/examples/1_bfv_basics.cpp](polynomial_evaluation/SEAL/native/examples/1_bfv_basics.cpp)
set the values for the following variables
- `flag` Set it to 1 to enable fault injection, else set it to 0
- `filename` Provide the name for output log

In [polynomial_evaluation/SEAL/native/examples/4_ckks_basics.cpp](polynomial_evaluation/SEAL/native/examples/4_ckks_basics.cpp)
set the values for the following variables
- `flag` Set it to 1 to enable fault injection, else set it to 0
- `filename` Provide the name for output log
- `depth` Defines the multiplicative depth at which fault injection is to be performed. The valid values for this application are 2, 3 or 4.

Second, compile and run the codes
```
cd ./polynomial_evaluation/SEAL/native/examples/build/
make
./polynomial_evaluation/SEAL/native/examples/build/bin/sealexamples
```
In the prompt, enter 1 to run BFV-based attack and 4 to run CKKS-based attack.

## __Image Classification__

We perform GlitchFHE 
- on the BFV implementation of CryptoNets, an image classification accelerator implemented in [Microsoft SEAL 3.7.2](https://github.com/microsoft/SEAL/tree/3.7.2). Note that, toward this end, we have modified the SEAL implementation by using [FURBO](https://github.com/momalab/furbo), but you don't need to run FURBO again at your end.
- on the CKKS implementation of CryptoNets. We have modified the BFV-based CryptoNets implementation obtained from [FURBO](https://github.com/momalab/furbo) toward this end.

### __Installation Instructions__

The modified SEAL implementations are provided in
[cryptonets/seal_standalone_bfv_attack/e3_seal.372/SEAL/](cryptonets/seal_standalone_bfv_attack/e3_seal.372/SEAL/)
and
[cryptonets/seal_standalone_ckks_attack/e3_seal.372/SEAL/](cryptonets/seal_standalone_ckks_attack/e3_seal.372/SEAL/), respectively.

First, follow the README instructions in the respective folders to build these versions.
As before, note that this follows the same instructions as the baseline SEAL library.

Second, copy the correspondingly obtained library files, like `lib.seal.a`, files to the matching `seal_unx/target` and `seal_unx/native` directories.

### __File Information__

As before, the codes for GlitchFHE attacks are integrated.
More specifically, the attack on
CKKS-based CryptoNets is integrated in [cryptonets/seal_standalone_ckks_attack](cryptonets/seal_standalone_ckks_attack), and the
attack on BFV-based CryptoNets is integrated in [cryptonets/seal_standalone_bfv_attack](cryptonets/seal_standalone_bfv_attack).

### __Instructions to Run the codes__

In the respective folders (described above), run
```
make all
make run
```

## __Image Processing__

We perform GlitchFHE on the CKKS implementation of image processing in [EVA](https://github.com/microsoft/EVA).
As before, please use the modified copy of the EVA library from this repository only.

### __Installation Instructions__

The modified EVA implementation is provided in [Image_Processing/EVA/](Image_Processing/EVA/).
Please follow the instructions in [Image_Processing/EVA/README.md](Image_Processing/EVA/README.md) to build this version of EVA.
Note that this follows the same instructions as the baseline EVA library.

### __File Information__

As before, the codes for GlitchFHE attacks are integrated.
<!--
More specifically, we have modified `rns.cpp` in the SEAL source code to perform fault injection and copied the corresponding binary in the repository we shared in 
[Image_Processing/EVA/](Image_Processing/EVA/).
-->

### __Instructions for Running the Code__

```
cd ./Image_Processing/EVA/examples/
python image_processing.py 
```

