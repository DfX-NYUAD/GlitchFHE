// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include <cstdlib>
#include <ctime>

#include "examples.h"

using namespace std;
using namespace seal;




void example_ckks_basics()
{
    print_example_banner("Example: Attacking CKKS");
   
    int depth = 2;  //Depth value indicates multiplicative depth, here, it is 2,3, or 4
    int flag = 1;  //Flag is 0 when fault-injection is not enabled, else 1
    std::string filename = "output_ckks_attack.txt";
 
    std::ofstream outputFile(filename);


    /*
    In this example we demonstrate evaluating a polynomial function

        PI*x^3 + 0.4*x + 1

    on encrypted floating-point input data x for a set of 4096 equidistant points
    in the interval [0, 1]. This example demonstrates many of the main features
    of the CKKS scheme, but also the challenges in using it.

    We start by setting up the CKKS scheme.
    */

    std::srand(std::time(0));


    double avg = 0;
    
    double curr_point1 = 0;

    for (int err_mult = 0; err_mult < 2; err_mult = err_mult+100){
    
    EncryptionParameters parms(scheme_type::ckks);
    

    //Therse are the errors calculated based on the CKKS parameters (coefficient modulus) for this polynomial evaluation

    if (depth == 2){

    double error =773092966401 * err_mult; // multiplicative depth - 2
    }

    
    if (depth == 3){

    double error =664226251776 * err_mult; //multiplicative depth - 3 

    }


    if (depth == 4){
    double error =962464259952701953 * err_mult; //multiplicative depth - 4 
    }

    
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, { 60, 40, 40, 60 }));

    double scale = pow(2.0, 40);

    SEALContext context(parms);
    
    std::cout << "printing coefficient modulus" << std::endl;

    for (auto &cm: parms.coeff_modulus())
        std::cout << cm.value() << std::endl;

    print_parameters(context);
    cout << endl;

    KeyGenerator keygen(context);
    auto secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    GaloisKeys gal_keys;
    keygen.create_galois_keys(gal_keys);
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    CKKSEncoder encoder(context);
    size_t slot_count = encoder.slot_count();
    cout << "Number of slots: " << slot_count << endl;

    vector<double> input;
    input.reserve(slot_count);
    double curr_point = curr_point1;
    double step_size = 1.0 / (static_cast<double>(slot_count) - 1);
    
    for (size_t i = 0; i < slot_count; i++)
    {
        input.push_back(curr_point);
        curr_point += step_size;
    }
    
    cout << "Input vector: " << endl;
    print_vector(input, 3, 7);

    cout << "Evaluating polynomial PI*x^3 + 0.4x + 1 ..." << endl;

    
    Plaintext plain_coeff3, plain_coeff1, plain_coeff0;
    encoder.encode(3.14159265, scale, plain_coeff3);
    encoder.encode(0.4, scale, plain_coeff1);
    encoder.encode(1.0, scale, plain_coeff0);

    Plaintext x_plain;
    print_line(__LINE__);
   
    cout << "Encode input vectors." << endl;
    encoder.encode(input, scale, x_plain);
    Ciphertext x1_encrypted;
    encryptor.encrypt(x_plain, x1_encrypted);

    /*
    To compute x^3 we first compute x^2 and relinearize. However, the scale has
    now grown to 2^80.
    */
    
    Ciphertext x3_encrypted;
    print_line(__LINE__);
    cout << "Compute x^2 and relinearize:" << endl;
    evaluator.square(x1_encrypted, x3_encrypted);
    evaluator.relinearize_inplace(x3_encrypted, relin_keys,0,0,0);
    cout << "    + Scale of x^2 before rescale: " << log2(x3_encrypted.scale()) << " bits" << endl;


    /*
    Now rescale; in addition to a modulus switch, the scale is reduced down by
    a factor equal to the prime that was switched away (40-bit prime). Hence, the
    new scale should be close to 2^40. Note, however, that the scale is not equal
    to 2^40: this is because the 40-bit prime is only close to 2^40.
    */
    
    print_line(__LINE__);
    cout << "Rescale x^2." << endl;

    
    if (flag == 1){
    if (depth == 4){
    

    evaluator.rescale_to_next_inplace(x3_encrypted,0,error,1); // multiplicative depth - 4

    }
    else{

    evaluator.rescale_to_next_inplace(x3_encrypted,0,0,0); // multiplicative depth - 4
     }
    }
    else{

    evaluator.rescale_to_next_inplace(x3_encrypted,0,0,0); // multiplicative depth - 4
    }
 
    cout << "    + Scale of x^2 after rescale: " << log2(x3_encrypted.scale()) << " bits" << endl;

    /*
    Now x3_encrypted is at a different level than x1_encrypted, which prevents us
    from multiplying them to compute x^3. We could simply switch x1_encrypted to
    the next parameters in the modulus switching chain. However, since we still
    need to multiply the x^3 term with PI (plain_coeff3), we instead compute PI*x
    first and multiply that with x^2 to obtain PI*x^3. To this end, we compute
    PI*x and rescale it back from scale 2^80 to something close to 2^40.
    */
    
    print_line(__LINE__);
    cout << "Compute and rescale PI*x." << endl;
    Ciphertext x1_encrypted_coeff3;
    evaluator.multiply_plain(x1_encrypted, plain_coeff3, x1_encrypted_coeff3);
    cout << "    + Scale of PI*x before rescale: " << log2(x1_encrypted_coeff3.scale()) << " bits" << endl;
    evaluator.rescale_to_next_inplace(x1_encrypted_coeff3,0,0,0);
    cout << "    + Scale of PI*x after rescale: " << log2(x1_encrypted_coeff3.scale()) << " bits" << endl;

    /*
    Since x3_encrypted and x1_encrypted_coeff3 have the same exact scale and use
    the same encryption parameters, we can multiply them together. We write the
    result to x3_encrypted, relinearize, and rescale. Note that again the scale
    is something close to 2^40, but not exactly 2^40 due to yet another scaling
    by a prime. We are down to the last level in the modulus switching chain.
    */
    print_line(__LINE__);
    cout << "Compute, relinearize, and rescale (PI*x)*x^2." << endl;
    evaluator.multiply_inplace(x3_encrypted, x1_encrypted_coeff3);
    evaluator.relinearize_inplace(x3_encrypted, relin_keys,0,0,0);
    cout << "    + Scale of PI*x^3 before rescale: " << log2(x3_encrypted.scale()) << " bits" << endl;

    std::cout << "print x3 before rescale" << std::endl;

    for (std::size_t i = 0; i < x3_encrypted.dyn_array().size(); i++)
        std::cout << x3_encrypted.data()[i] << " ";

    std::cout << std::endl;

    if (flag == 1){
    if (depth == 2){
    

    evaluator.rescale_to_next_inplace(x3_encrypted,0,error,1); // multiplicative depth - 2

    }
    else{

    evaluator.rescale_to_next_inplace(x3_encrypted,0,0,0); // multiplicative depth - 2
     }
    }
    else{

    evaluator.rescale_to_next_inplace(x3_encrypted,0,0,0); // multiplicative depth - 2
    }
    cout << "    + Scale of PI*x^3 after rescale: " << log2(x3_encrypted.scale()) << " bits" << endl;


    /*
    Next we compute the degree one term. All this requires is one multiply_plain
    with plain_coeff1. We overwrite x1_encrypted with the result.    */
    print_line(__LINE__);
    cout << "Compute and rescale 0.4*x." << endl;
    evaluator.multiply_plain_inplace(x1_encrypted, plain_coeff1);
    cout << "    + Scale of 0.4*x before rescale: " << log2(x1_encrypted.scale()) << " bits" << endl;

    if (flag == 1){
    if (depth == 3){
    

    evaluator.rescale_to_next_inplace(x1_encrypted,0,error,1); // multiplicative depth - 3

    }
    else{

    evaluator.rescale_to_next_inplace(x1_encrypted,0,0,0); // multiplicative depth - 3
     }
    }
    else{

    evaluator.rescale_to_next_inplace(x1_encrypted,0,0,0); // multiplicative depth - 3
    }

    cout << "    + Scale of 0.4*x after rescale: " << log2(x1_encrypted.scale()) << " bits" << endl;

    /*
    Now we would hope to compute the sum of all three terms. However, there is
    a serious problem: the encryption parameters used by all three terms are
    different due to modulus switching from rescaling.

    Encrypted addition and subtraction require that the scales of the inputs are
    the same, and also that the encryption parameters (parms_id) match. If there
    is a mismatch, Evaluator will throw an exception.
    */

    cout << endl;
    print_line(__LINE__);
    cout << "Parameters used by all three terms are different." << endl;
    cout << "    + Modulus chain index for x3_encrypted: "
         << context.get_context_data(x3_encrypted.parms_id())->chain_index() << endl;
    cout << "    + Modulus chain index for x1_encrypted: "
         << context.get_context_data(x1_encrypted.parms_id())->chain_index() << endl;
    cout << "    + Modulus chain index for plain_coeff0: "
         << context.get_context_data(plain_coeff0.parms_id())->chain_index() << endl;
    cout << endl;

    /*
    Let us carefully consider what the scales are at this point. We denote the
    primes in coeff_modulus as P_0, P_1, P_2, P_3, in this order. P_3 is used as
    the special modulus and is not involved in rescalings. After the computations
    above the scales in ciphertexts are:

        - Product x^2 has scale 2^80 and is at level 2;
        - Product PI*x has scale 2^80 and is at level 2;
        - We rescaled both down to scale 2^80/P_2 and level 1;
        - Product PI*x^3 has scale (2^80/P_2)^2;
        - We rescaled it down to scale (2^80/P_2)^2/P_1 and level 0;
        - Product 0.4*x has scale 2^80;
        - We rescaled it down to scale 2^80/P_2 and level 1;
        - The contant term 1 has scale 2^40 and is at level 2.

    Although the scales of all three terms are approximately 2^40, their exact
    values are different, hence they cannot be added together.
    */
    print_line(__LINE__);
    cout << "The exact scales of all three terms are different:" << endl;
    ios old_fmt(nullptr);
    old_fmt.copyfmt(cout);
    cout << fixed << setprecision(10);
    cout << "    + Exact scale in PI*x^3: " << x3_encrypted.scale() << endl;
    cout << "    + Exact scale in  0.4*x: " << x1_encrypted.scale() << endl;
    cout << "    + Exact scale in      1: " << plain_coeff0.scale() << endl;
    cout << endl;
    cout.copyfmt(old_fmt);

    /*
    There are many ways to fix this problem. Since P_2 and P_1 are really close
    to 2^40, we can simply "lie" to Microsoft SEAL and set the scales to be the
    same. For example, changing the scale of PI*x^3 to 2^40 simply means that we
    scale the value of PI*x^3 by 2^120/(P_2^2*P_1), which is very close to 1.
    This should not result in any noticeable error.

    Another option would be to encode 1 with scale 2^80/P_2, do a multiply_plain
    with 0.4*x, and finally rescale. In this case we would need to additionally
    make sure to encode 1 with appropriate encryption parameters (parms_id).

    In this example we will use the first (simplest) approach and simply change
    the scale of PI*x^3 and 0.4*x to 2^40.
    */



    print_line(__LINE__);
    cout << "Normalize scales to 2^40." << endl;
    x3_encrypted.scale() = pow(2.0, 40);
    x1_encrypted.scale() = pow(2.0, 40);

    /*
    We still have a problem with mismatching encryption parameters. This is easy
    to fix by using traditional modulus switching (no rescaling). CKKS supports
    modulus switching just like the BFV scheme, allowing us to switch away parts
    of the coefficient modulus when it is simply not needed.
    */
    print_line(__LINE__);
    cout << "Normalize encryption parameters to the lowest level." << endl;
    parms_id_type last_parms_id = x3_encrypted.parms_id();
    evaluator.mod_switch_to_inplace(x1_encrypted, last_parms_id);
    evaluator.mod_switch_to_inplace(plain_coeff0, last_parms_id);

    /*
    All three ciphertexts are now compatible and can be added.
    */
    print_line(__LINE__);
    cout << "Compute PI*x^3 + 0.4*x + 1." << endl;
    Ciphertext encrypted_result;
    evaluator.add(x3_encrypted, x1_encrypted, encrypted_result);
    evaluator.add_plain_inplace(encrypted_result, plain_coeff0);

    /*
    First print the true result.
    */
    Plaintext plain_result;
    print_line(__LINE__);
    cout << "Decrypt and decode PI*x^3 + 0.4x + 1." << endl;
    cout << "    + Expected result:" << endl;
    vector<double> true_result;
    for (size_t i = 0; i < input.size(); i++)
    {
        double x = input[i];
        true_result.push_back((3.14159265 * x * x + 0.4) * x + 1);
    }
    print_vector(true_result, 3, 7);

    /*
    Decrypt, decode, and print the result.
    */
    decryptor.decrypt(encrypted_result, plain_result);
    vector<double> result;
    encoder.decode(plain_result, result);
    cout << "    + Computed result ...... Correct." << endl;
    print_vector(result, 3, 7);

    if (result.size()==true_result.size()){
    double error = 0;	    
    double mse;
    for (int p = 0; p < result.size(); p++) {
		error += pow((result[p] - true_result[p]), 2);
	}
    cout << error << endl;
    mse = error / result.size();
    cout << result.size() << endl;
    cout << mse << endl;
    outputFile << err_mult << " "<<mse << std::endl;
    avg = avg + mse;    
    }
    }

}
