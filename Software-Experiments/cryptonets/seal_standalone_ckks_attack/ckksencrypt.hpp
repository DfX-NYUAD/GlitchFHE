
#include <vector>
#include "seal/seal.h"


std::vector<seal::Ciphertext> ckksEncryptPack(const std::vector<double> & a,seal::CKKSEncoder encoder, double scale,seal::Encryptor encryptor)
{
    std::vector <double> v;
    v.assign(a.begin(), a.end());
    auto nElems = a.size();
    auto slots = encoder.slot_count();
    // auto mod = nElems % slots;
    auto mod = (slots - nElems) % slots; // changed from 'mod = nElems % slots;'
    v.resize(v.size()+mod, 0);
    std::vector <seal::Ciphertext> r;
    for ( size_t i=0; i<v.size(); i+=slots )
    {
	std::vector<double> tmp;
	seal::Plaintext p1;
	seal::Ciphertext c1;
        for ( size_t j=0; j<slots; j++ )
            tmp.push_back(v[i+j]);
	encoder.encode(tmp,scale,p1);
        encryptor.encrypt(p1,c1);		
        r.push_back(c1);
    }
    return r;
}

template <class T> std::vector<std::vector<seal::Ciphertext>>
ckksEncryptPack(const std::vector<std::vector<T>> & a,seal::CKKSEncoder encoder, double scale,seal::Encryptor encryptor)
{
	std::vector<std::vector<seal::Ciphertext>> r;
    for ( auto & e : a ) r.push_back( ckksEncryptPack(e,encoder,scale,encryptor) );
    return r;
}

template <class T> std::vector<std::vector<std::vector<seal::Ciphertext>>>
ckksEncryptPack(const std::vector<std::vector<std::vector<T>>> & a,seal::CKKSEncoder encoder, double scale,seal::Encryptor encryptor)
{
	std::vector<std::vector<std::vector<seal::Ciphertext>>> r;
    for ( auto & e : a ) r.push_back( ckksEncryptPack(e,encoder,scale,encryptor) );
    return r;
}

template <class T> std::vector<std::vector<std::vector<std::vector<seal::Ciphertext>>>>
ckksEncryptPack(const std::vector<std::vector<std::vector<std::vector<T>>>> & a,seal::CKKSEncoder encoder, double scale,seal::Encryptor encryptor)
{
	std::vector<std::vector<std::vector<std::vector<seal::Ciphertext>>>> r;
    for ( auto & e : a ) r.push_back( ckksEncryptPack(e,encoder,scale,encryptor) );
    return r;
}
