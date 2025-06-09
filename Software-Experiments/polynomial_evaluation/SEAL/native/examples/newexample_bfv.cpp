#include "examples.h"

using namespace seal;
using namespace std;

void example_bfv_basics() {
    stringstream ss;

    EncryptionParameters params(scheme_type::bfv);
    params.set_poly_modulus_degree(8);
    params.set_coeff_modulus({ 65537 });
    params.set_plain_modulus(17);
    SEALContext context(params, true, sec_level_type::none);
    KeyGenerator keygen(context);
    auto sk = keygen.secret_key();
    PublicKey pk;
    keygen.create_public_key(pk);
    BatchEncoder encoder(context);
    Plaintext pt;
    encoder.encode(vector<uint64_t>{ 1, 2, 3 }, pt);
    Encryptor encryptor(context, pk);
    Ciphertext ct; 
    encryptor.encrypt(pt, ct);
    cout << ct.dyn_array().size() << endl;
    for (int i = 0; i < 8; i++){
    ct.data()[i] = ct.data()[i]+(2000);
    }

    ct.save(ss);
    string ss_str = ss.str();
    cout << "length of ss_str: " << ss_str.length() << endl;

    stringstream ss_in(ss_str);
    Ciphertext ct2;
    ct2.load(context, ss_in);

    Decryptor decryptor(context, sk);
    Plaintext out;
    decryptor.decrypt(ct2, out);
    vector<uint64_t> res;
    encoder.decode(out, res);
    for (auto i : res) {
        cout << i << endl;
    }

}
