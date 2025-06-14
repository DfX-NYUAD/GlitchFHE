// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#include "examples.h"

using namespace std;
using namespace seal;

/*
In `1_bfv_basics.cpp' we showed how to perform a very simple computation using the
BFV scheme. The computation was performed modulo the plain_modulus parameter, and
utilized only one coefficient from a BFV plaintext polynomial. This approach has
two notable problems:

    (1) Practical applications typically use integer or real number arithmetic,
        not modular arithmetic;
    (2) We used only one coefficient of the plaintext polynomial. This is really
        wasteful, as the plaintext polynomial is large and will in any case be
        encrypted in its entirety.

For (1), one may ask why not just increase the plain_modulus parameter until no
overflow occurs, and the computations behave as in integer arithmetic. The problem
is that increasing plain_modulus increases noise budget consumption, and decreases
the initial noise budget too.

In these examples we will discuss other ways of laying out data into plaintext
elements (encoding) that allow more computations without data type overflow, and
can allow the full plaintext polynomial to be utilized.
*/
void example_batch_encoder()
{
    print_example_banner("Example: Encoders / Batch Encoder");

    /*
    [BatchEncoder] (For BFV scheme only)

    Let N denote the poly_modulus_degree and T denote the plain_modulus. Batching
    allows the BFV plaintext polynomials to be viewed as 2-by-(N/2) matrices, with
    each element an integer modulo T. In the matrix view, encrypted operations act
    element-wise on encrypted matrices, allowing the user to obtain speeds-ups of
    several orders of magnitude in fully vectorizable computations. Thus, in all
    but the simplest computations, batching should be the preferred method to use
    with BFV, and when used properly will result in implementations outperforming
    anything done without batching.
    */
    EncryptionParameters parms(scheme_type::bfv);
    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::BFVDefault(poly_modulus_degree));

    /*
    To enable batching, we need to set the plain_modulus to be a prime number
    congruent to 1 modulo 2*poly_modulus_degree. Microsoft SEAL provides a helper
    method for finding such a prime. In this example we create a 20-bit prime
    that supports batching.
    */
    parms.set_plain_modulus(PlainModulus::Batching(poly_modulus_degree, 20));

    SEALContext context(parms);
    print_parameters(context);
    cout << endl;

    /*
    We can verify that batching is indeed enabled by looking at the encryption
    parameter qualifiers created by SEALContext.
    */
    auto qualifiers = context.first_context_data()->qualifiers();
    cout << "Batching enabled: " << boolalpha << qualifiers.using_batching << endl;

    KeyGenerator keygen(context);
    SecretKey secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    /*
    Batching is done through an instance of the BatchEncoder class.
    */
    BatchEncoder batch_encoder(context);

    /*
    The total number of batching `slots' equals the poly_modulus_degree, N, and
    these slots are organized into 2-by-(N/2) matrices that can be encrypted and
    computed on. Each slot contains an integer modulo plain_modulus.
    */
    size_t slot_count = batch_encoder.slot_count();
    size_t row_size = slot_count / 2;
    cout << "Plaintext matrix row size: " << row_size << endl;

    /*
    The matrix plaintext is simply given to BatchEncoder as a flattened vector
    of numbers. The first `row_size' many numbers form the first row, and the
    rest form the second row. Here we create the following matrix:

        [ 0,  1,  2,  3,  0,  0, ...,  0 ]
        [ 4,  5,  6,  7,  0,  0, ...,  0 ]
    */
    vector<uint64_t> pod_matrix(slot_count, 0ULL);
    pod_matrix[0] = 0ULL;
    pod_matrix[1] = 1ULL;
    pod_matrix[2] = 2ULL;
    pod_matrix[3] = 3ULL;
    pod_matrix[row_size] = 4ULL;
    pod_matrix[row_size + 1] = 5ULL;
    pod_matrix[row_size + 2] = 6ULL;
    pod_matrix[row_size + 3] = 7ULL;

    cout << "Input plaintext matrix:" << endl;
    print_matrix(pod_matrix, row_size);

    /*
    First we use BatchEncoder to encode the matrix into a plaintext polynomial.
    */
    Plaintext plain_matrix;
    print_line(__LINE__);
    cout << "Encode plaintext matrix:" << endl;
    batch_encoder.encode(pod_matrix, plain_matrix);

    /*
    We can instantly decode to verify correctness of the encoding. Note that no
    encryption or decryption has yet taken place.
    */
    vector<uint64_t> pod_result;
    cout << "    + Decode plaintext matrix ...... Correct." << endl;
    batch_encoder.decode(plain_matrix, pod_result);
    print_matrix(pod_result, row_size);

    /*
    Next we encrypt the encoded plaintext.
    */
    Ciphertext encrypted_matrix;
    print_line(__LINE__);
    cout << "Encrypt plain_matrix to encrypted_matrix." << endl;
    encryptor.encrypt(plain_matrix, encrypted_matrix);
    cout << "    + Noise budget in encrypted_matrix: " << decryptor.invariant_noise_budget(encrypted_matrix) << " bits"
         << endl;

    /*
    Operating on the ciphertext results in homomorphic operations being performed
    simultaneously in all 8192 slots (matrix elements). To illustrate this, we
    form another plaintext matrix

        [ 1,  2,  1,  2,  1,  2, ..., 2 ]
        [ 1,  2,  1,  2,  1,  2, ..., 2 ]

    and encode it into a plaintext.
    */
    vector<uint64_t> pod_matrix2;
    for (size_t i = 0; i < slot_count; i++)
    {
        pod_matrix2.push_back((i & size_t(0x1)) + 1);
    }
    Plaintext plain_matrix2;
    batch_encoder.encode(pod_matrix2, plain_matrix2);
    cout << endl;
    cout << "Second input plaintext matrix:" << endl;
    print_matrix(pod_matrix2, row_size);

    /*
    We now add the second (plaintext) matrix to the encrypted matrix, and square
    the sum.
    */
    print_line(__LINE__);
    cout << "Sum, square, and relinearize." << endl;
    evaluator.add_plain_inplace(encrypted_matrix, plain_matrix2);
    evaluator.square_inplace(encrypted_matrix);
    double err_bit, err_ind;
    int flag;
    evaluator.relinearize_inplace(encrypted_matrix, relin_keys,err_bit,err_ind,flag);

    /*
    How much noise budget do we have left?
    */
    cout << "    + Noise budget in result: " << decryptor.invariant_noise_budget(encrypted_matrix) << " bits" << endl;

    /*
    We decrypt and decompose the plaintext to recover the result as a matrix.
    */
    Plaintext plain_result;
    print_line(__LINE__);
    cout << "Decrypt and decode result." << endl;
    decryptor.decrypt(encrypted_matrix, plain_result);
    batch_encoder.decode(plain_result, pod_result);
    cout << "    + Result plaintext matrix ...... Correct." << endl;
    print_matrix(pod_result, row_size);

    /*
    Batching allows us to efficiently use the full plaintext polynomial when the
    desired encrypted computation is highly parallelizable. However, it has not
    solved the other problem mentioned in the beginning of this file: each slot
    holds only an integer modulo plain_modulus, and unless plain_modulus is very
    large, we can quickly encounter data type overflow and get unexpected results
    when integer computations are desired. Note that overflow cannot be detected
    in encrypted form. The CKKS scheme (and the CKKSEncoder) addresses the data
    type overflow issue, but at the cost of yielding only approximate results.
    */
}

void example_ckks_encoder()
{
    print_example_banner("Example: Encoders / CKKS Encoder");

    /*
    [CKKSEncoder] (For CKKS scheme only)

    In this example we demonstrate the Cheon-Kim-Kim-Song (CKKS) scheme for
    computing on encrypted real or complex numbers. We start by creating
    encryption parameters for the CKKS scheme. There are two important
    differences compared to the BFV scheme:

        (1) CKKS does not use the plain_modulus encryption parameter;
        (2) Selecting the coeff_modulus in a specific way can be very important
            when using the CKKS scheme. We will explain this further in the file
            `ckks_basics.cpp'. In this example we use CoeffModulus::Create to
            generate 5 40-bit prime numbers.
    */
    EncryptionParameters parms(scheme_type::ckks);

    size_t poly_modulus_degree = 8192;
    parms.set_poly_modulus_degree(poly_modulus_degree);
    parms.set_coeff_modulus(CoeffModulus::Create(poly_modulus_degree, { 40, 40, 40, 40, 40 }));

    /*
    We create the SEALContext as usual and print the parameters.
    */
    SEALContext context(parms);
    print_parameters(context);
    cout << endl;

    /*
    Keys are created the same way as for the BFV scheme.
    */
    KeyGenerator keygen(context);
    auto secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);

    /*
    We also set up an Encryptor, Evaluator, and Decryptor as usual.
    */
    Encryptor encryptor(context, public_key);
    Evaluator evaluator(context);
    Decryptor decryptor(context, secret_key);

    /*
    To create CKKS plaintexts we need a special encoder: there is no other way
    to create them. The BatchEncoder cannot be used with the
    CKKS scheme. The CKKSEncoder encodes vectors of real or complex numbers into
    Plaintext objects, which can subsequently be encrypted. At a high level this
    looks a lot like what BatchEncoder does for the BFV scheme, but the theory
    behind it is completely different.
    */
    CKKSEncoder encoder(context);

    /*
    In CKKS the number of slots is poly_modulus_degree / 2 and each slot encodes
    one real or complex number. This should be contrasted with BatchEncoder in
    the BFV scheme, where the number of slots is equal to poly_modulus_degree
    and they are arranged into a matrix with two rows.
    */
    size_t slot_count = encoder.slot_count();
    cout << "Number of slots: " << slot_count << endl;

    /*
    We create a small vector to encode; the CKKSEncoder will implicitly pad it
    with zeros to full size (poly_modulus_degree / 2) when encoding.
    */
    vector<double> input{ 0.0, 1.1, 2.2, 3.3 };
    cout << "Input vector: " << endl;
    print_vector(input);

    /*
    Now we encode it with CKKSEncoder. The floating-point coefficients of `input'
    will be scaled up by the parameter `scale'. This is necessary since even in
    the CKKS scheme the plaintext elements are fundamentally polynomials with
    integer coefficients. It is instructive to think of the scale as determining
    the bit-precision of the encoding; naturally it will affect the precision of
    the result.

    In CKKS the message is stored modulo coeff_modulus (in BFV it is stored modulo
    plain_modulus), so the scaled message must not get too close to the total size
    of coeff_modulus. In this case our coeff_modulus is quite large (200 bits) so
    we have little to worry about in this regard. For this simple example a 30-bit
    scale is more than enough.
    */
    Plaintext plain;
    double scale = pow(2.0, 30);
    print_line(__LINE__);
    cout << "Encode input vector." << endl;
    encoder.encode(input, scale, plain);

    /*
    We can instantly decode to check the correctness of encoding.
    */
    vector<double> output;
    cout << "    + Decode input vector ...... Correct." << endl;
    encoder.decode(plain, output);
    print_vector(output);

    /*
    The vector is encrypted the same was as in BFV.
    */
    Ciphertext encrypted;
    print_line(__LINE__);
    cout << "Encrypt input vector, square, and relinearize." << endl;
    encryptor.encrypt(plain, encrypted);

    /*
    Basic operations on the ciphertexts are still easy to do. Here we square the
    ciphertext, decrypt, decode, and print the result. We note also that decoding
    returns a vector of full size (poly_modulus_degree / 2); this is because of
    the implicit zero-padding mentioned above.
    */
    double err_bit, err_ind;
    int flag;
    evaluator.square_inplace(encrypted);
    evaluator.relinearize_inplace(encrypted, relin_keys,err_bit,err_ind,flag);

    /*
    We notice that the scale in the result has increased. In fact, it is now the
    square of the original scale: 2^60.
    */
    cout << "    + Scale in squared input: " << encrypted.scale() << " (" << log2(encrypted.scale()) << " bits)"
         << endl;

    print_line(__LINE__);
    cout << "Decrypt and decode." << endl;
    decryptor.decrypt(encrypted, plain);
    encoder.decode(plain, output);
    cout << "    + Result vector ...... Correct." << endl;
    print_vector(output);

    /*
    The CKKS scheme allows the scale to be reduced between encrypted computations.
    This is a fundamental and critical feature that makes CKKS very powerful and
    flexible. We will discuss it in great detail in `3_levels.cpp' and later in
    `4_ckks_basics.cpp'.
    */
}

void example_encoders()
{
    print_example_banner("Example: Encoders");

    /*
    Run all encoder examples.
    */
    example_batch_encoder();
    example_ckks_encoder();
}
