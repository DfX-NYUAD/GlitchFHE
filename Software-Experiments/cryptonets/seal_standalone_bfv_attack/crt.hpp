#pragma once

#include <fstream>
using std::vector;
using namespace seal;
extern double error;

namespace crt
{

template <class Number> vector<Number> CRT<Number>::coprimes;
template <class Number> Number CRT<Number>::mod;
template <class Number> vector<Number> CRT<Number>::nx;
template <class Number> vector<Ciphertext> CRT<Number>::zero;

template <class Number> vector<BatchEncoder*> CRT<Number>::encoders;
template <class Number> vector<Encryptor*> CRT<Number>::encryptors;
template <class Number> vector<Evaluator*> CRT<Number>::evaluators;
template <class Number> vector<Decryptor*> CRT<Number>::decryptors;
template <class Number> vector<RelinKeys> CRT<Number>::relinkeys;

// constructors

template <class Number>
CRT<Number>::CRT(const CRT<Number> & a)
{
    encrypted = a.encrypted;
    if ( encrypted ) vc = a.vc;
    else vp = a.vp;
}

template <class Number>
CRT<Number>::CRT(const Number & a, bool encrypted)
{
    *this = encode(a, encrypted);
}

template <class Number>
CRT<Number>::CRT(const vector<Ciphertext> & v)
{
    if ( v.size() != coprimes.size() )
        throw "Size of vector<Ciphertext> during CRT constructor does not match size of coprimes";
    this->encrypted = true;
    vc = v;
}

template <class Number>
CRT<Number>::CRT(const vector<Number> & a, bool encrypted)
{
    *this = encode(a, encrypted);
}

template <class Number>
CRT<Number>::CRT(const vector<vector<uint64_t>> & v, bool encrypted)
{
    this->encrypted = encrypted;
    for ( size_t i=0; i<coprimes.size(); i++ )
    {
        Plaintext p;
        encoders[i]->encode(v[i], p); // SEAL encoding
        if (encrypted)
        {
            Ciphertext c;
            encryptors[i]->encrypt(p, c); // SEAL encryption
            vc.push_back(c);
        }
        else vp.push_back(p);
    }
}

// operators

template <class Number>
CRT<Number> & CRT<Number>::operator+=(const CRT & a)
{
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            if ( a.encrypted ) evaluators[i]->add_inplace(vc[i], a.vc[i]);
            else evaluators[i]->add_plain_inplace(vc[i], a.vp[i]);
        }
    }
    else throw "Unencrypted addition not implemented";
    return *this;
}

template <class Number>
CRT<Number> & CRT<Number>::operator*=(const CRT & a)
{
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            if ( a.encrypted )
            {
             std::cout << "flag check 1"<< std::endl;   
                evaluators[i]->multiply_inplace(vc[i], a.vc[i]);
                evaluators[i]->relinearize_inplace(vc[i], relinkeys[i],0,0);
            }
            else evaluators[i]->multiply_plain_inplace(vc[i], a.vp[i]);
        }
    }
    else throw "Unencrypted multiplication not implemented";
    return *this;
}

template <class Number>
CRT<Number> & CRT<Number>::operator-=(const CRT & a)
{
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            if ( a.encrypted ) evaluators[i]->sub_inplace(vc[i], a.vc[i]);
            else evaluators[i]->sub_plain_inplace(vc[i], a.vp[i]);
        }
    }
    else throw "Unencrypted subtraction not implemented";
    return *this;
}

template <class Number>
CRT<Number> CRT<Number>::operator-() const
{
    CRT r;
    r.encrypted = true;
    if ( r.encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
            evaluators[i]->negate(vc[i], r.vc[i]);
    }
    else throw "Unencrypted unary minus not implemented";
    return r;
}

template <class Number>
CRT<Number> CRT<Number>::operator+(const CRT & a) const
{
    vector<Ciphertext> vct;
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            Ciphertext c;
            if ( a.encrypted ){ 
	    //std::cout << "in add operation 1" << std::endl;
		    evaluators[i]->add(vc[i], a.vc[i], c);
   // std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
   //     << std::endl;
           }
            else {
	    //std::cout << "in add operation 2" << std::endl;
		    evaluators[i]->add_plain(vc[i], a.vp[i], c);}
   // std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
   //     << std::endl;
            vct.push_back(c);
        }
    }
    else throw "Unencrypted addition not implemented";
    return CRT<Number>(vct);
}

template <class Number>
CRT<Number> CRT<Number>::operator*(const CRT & a) const
{
    vector<Ciphertext> vct;
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            Ciphertext c;
            if ( a.encrypted )
            {
            // std::cout << "flag check 2"<< std::endl;   
                evaluators[i]->multiply(vc[i], a.vc[i], c);
                evaluators[i]->relinearize_inplace(c, relinkeys[i],0,0);
   // std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
   //     << std::endl;
            }
            else {
	//std::cout << log2(vc[i].scale()) << std::endl;
		    evaluators[i]->multiply_plain(vc[i], a.vp[i], c);}
    //std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
    //    << std::endl;
	//std::cout << log2(c.scale()) << std::endl;
            vct.push_back(c);
        }
    }
    else throw "Unencrypted multiplication not implemented";
    return CRT<Number>(vct);
}


/*
template <class Number>
CRT<Number> CRT<Number>::operator^(const CRT & a) const
{
    vector<Ciphertext> vct;
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            Ciphertext c;
            if ( a.encrypted )
            {
                evaluators[i]->multiply(vc[i], a.vc[i], c);
                evaluators[i]->relinearize_inplace(c, relinkeys[i],error,1);
    std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
        << std::endl;
            }
            else {
	//std::cout << log2(vc[i].scale()) << std::endl;
		    evaluators[i]->multiply_plain(vc[i], a.vp[i], c);}
    //std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
    //    << std::endl;
	//std::cout << log2(c.scale()) << std::endl;
            vct.push_back(c);
        }
    }
    else throw "Unencrypted multiplication not implemented";
    return CRT<Number>(vct);
}
*/















template <class Number>
CRT<Number> CRT<Number>::operator^(const CRT & a) const
{
std::ofstream outFile("output3.txt",std::ios::app);
    vector<Ciphertext> vct;
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            Ciphertext c;
            if ( a.encrypted )
            {
                evaluators[i]->multiply(vc[i], a.vc[i], c);
             //std::cout << "flag check "<< std::endl;   
             std::cout << "flag check 2"<< std::endl;   
             evaluators[i]->relinearize_inplace(c, relinkeys[i],error,1);
    std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
        << std::endl;
           outFile <<  decryptors[i]->invariant_noise_budget(c) << " "; 

            }
            else {
	std::cout << log2(vc[i].scale()) << std::endl;
		    evaluators[i]->multiply_plain(vc[i], a.vp[i], c);}
    //std::cout << "    + noise budget in encrypted_result: " << decryptors[i]->invariant_noise_budget(c) << " bits"
    //    << std::endl;
	//std::cout << log2(c.scale()) << std::endl;
            vct.push_back(c);
//           outFile <<  decryptors[i]->invariant_noise_budget(c) << " "; 
        }
    }
    else throw "Unencrypted multiplication not implemented";
    return CRT<Number>(vct);
}



template <class Number>
CRT<Number> CRT<Number>::operator-(const CRT & a) const
{
    vector<Ciphertext> vct;
    if ( encrypted )
    {
        for ( size_t i=0; i<coprimes.size(); i++ )
        {
            Ciphertext c;
            if ( a.encrypted ) evaluators[i]->sub(vc[i], a.vc[i], c);
            else evaluators[i]->sub_plain(vc[i], a.vp[i], c);
            vct.push_back(c);
        }
    }
    else throw "Unencrypted subtraction not implemented";
    return CRT<Number>(vct);
}

template <class Number>
CRT<Number> operator+(const Number & a, const CRT<Number> & b)
{
    return b + a;
}

template <class Number>
CRT<Number> operator*(const Number & a, const CRT<Number> & b)
{
    return b * a;
}


template <class Number>
CRT<Number> operator^(const Number & a, const CRT<Number> & b)
{
    return b ^ a;
}


template <class Number>
CRT<Number> operator-(const Number & a, const CRT<Number> & b)
{
    return -b + a;
}

// functions

template <class Number>
std::vector<Number> CRT<Number>::decode(bool is_signed) const
{
    return CRT::decode(*this, is_signed);
}

template <class Number>
vector<Number> CRT<Number>::decode(const CRT<Number> & a, bool is_signed)
{
    auto size = coprimes.size();

    vector<Plaintext> vp;
    if ( a.encrypted )
    {
        for ( size_t i=0; i<size; i++ )
        {
            Plaintext p;
            decryptors[i]->decrypt(a.vc[i], p); // SEAL decryption
            vp.push_back(p);
        }
    }
    else vp = a.vp;

    vector<vector<Number>> m;
    for ( size_t i=0; i<size; i++ )
    {
        vector<uint64_t> decoded;
        encoders[i]->decode(vp[i], decoded); // SEAL decode
        vector<Number> v;
        for ( auto e : decoded ) v.push_back( Number(e) );
        m.push_back(v);
    }

    auto nElems = m[0].size();
    vector<vector<Number>> vf( nElems, vector<Number>(size) );
    for ( size_t i=0; i<nElems; i++ )
        for ( size_t j=0; j<size; j++ ) vf[i][j] = m[j][i] * nx[j] % mod;

    vector<Number> vr;
    for ( auto f : vf )
    {
        Number r = 0;
        for ( auto & e : f ) r += e;
        r %= mod;
        r = (is_signed && r>mod/2) ? r-mod : r;
        vr.push_back(r);
    }
    return vr;
}

template <class Number>
CRT<Number> CRT<Number>::encode(const Number & a, bool encrypted)
{
    return encode( vector<Number>(encoders[0]->slot_count(), a), encrypted );
}

template <class Number>
CRT<Number> CRT<Number>::encode(const vector<Number> & a, bool encrypted)
{
    auto size = encoders[0]->slot_count();
    vector<Number> n(size);
    for ( size_t i=0; i<size; i++ )
    {
        n[i] = a[i] % mod;
        n[i] = n[i]<0 ? mod+n[i] : n[i];
    }
    vector<vector<uint64_t>> m;
    for ( auto e : coprimes )
    {
        vector<uint64_t> v;
        for ( size_t i=0; i<size; i++ ) v.push_back( uint64_t(n[i] % e) );
        m.push_back(v);
    }
    return CRT<Number>(m, encrypted);
}

template <class Number> void
CRT<Number>::setCoprimes(const vector<Number> & coprimes)
{
    CRT<Number>::coprimes = coprimes;
    mod = 1;
    for ( auto & e : coprimes ) mod *= e;
    nx.clear();
    for ( auto & coprime : coprimes )
    {
        Number ni = mod / coprime;
        Number nxi;
        for ( uint64_t xi=0; (nxi = xi * ni) % coprime != 1; xi++ );
        nx.push_back(nxi);
    }
}

template <class Number> void
CRT<Number>::setParams(
    const vector<RelinKeys> & relinkeys,
    const vector<BatchEncoder*> & encoders,
    const vector<Decryptor*> &  decryptors,
    const vector<Encryptor*> & encryptors,
    const vector<Evaluator*> & evaluators
)
{
    CRT<Number>::relinkeys = relinkeys;
    CRT<Number>::encoders = encoders;
    CRT<Number>::decryptors = decryptors;
    CRT<Number>::encryptors = encryptors;
    CRT<Number>::evaluators = evaluators;

    // create a vector of ciphertexts encrypting zero
    // one for each coprime since they have different keys
    zero.clear();
    auto slots = encoders[0]->slot_count();
    vector<uint64_t> z(slots, 0);
    for ( size_t i=0; i<encryptors.size(); i++ )
    {
        Plaintext p;
        encoders[i]->encode(z, p);
        Ciphertext c;
        encryptors[i]->encrypt(p, c);
        zero.push_back(c);
    }
}

template <class Number>
size_t CRT<Number>::slots()
{
    return encoders[0]->slot_count();
}

} // crt
