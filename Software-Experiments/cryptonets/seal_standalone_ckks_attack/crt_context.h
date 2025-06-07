#pragma once

#include <vector>
#include "seal/seal.h"

namespace crt
{

template <class Number>
class CRT
{
    private:
        std::vector<seal::Plaintext> vp;
        std::vector<seal::Ciphertext> vc;
        bool encrypted;

       // static std::vector<Number> coprimes;
        static Number mod;
        static std::vector<Number> nx;
        static std::vector<seal::Ciphertext> zero;
        static std::vector<seal::CKKSEncoder*> encoders;
        static std::vector<seal::Encryptor*> encryptors;
        static std::vector<seal::Evaluator*> evaluators;
        static std::vector<seal::Decryptor*> decryptors;
        static std::vector<seal::RelinKeys> relinkeys;
        static std::vector<seal::SEALContext*> context;
        //static seal::SEALContext  context;
//        static double scale1;
        //static seal::CKKSEncoder encoders;
        //static seal::Encryptor encryptors;
        //static seal::Evaluator evaluators;
        //static seal::Decryptor decryptors;
        //static seal::RelinKeys relinkeys;

    public:
        CRT() : CRT( Number(0) ) {}
        CRT(const CRT & a);
        CRT(const Number &, bool encrypted=false);
        CRT(const std::vector<seal::Ciphertext> &);
        CRT(const std::vector<double> &, bool encrypted=false);
        CRT(const std::vector<std::vector<double>> &, bool encrypted);
        //CRT(const std::vector<double> &, bool encrypted);

        CRT & operator+=(const CRT &);
        CRT & operator*=(const CRT &);
        CRT & operator-=(const CRT &);

        CRT operator-() const;
        CRT operator+(const CRT &) const;
        CRT operator*(const CRT &) const;
        CRT operator-(const CRT &) const;

        template <class T> friend CRT<T> operator+(const Number &, const CRT<T> &);
        template <class T> friend CRT<T> operator*(const Number &, const CRT<T> &);
        template <class T> friend CRT<T> operator-(const Number &, const CRT<T> &);

        std::vector<Number> decode(bool is_signed=true) const;
        static std::vector<Number> decode(const CRT & a, bool is_signed=true);
        static CRT encode(const Number &, bool encrypted=false);
        static CRT encode(const std::vector<Number> &, bool encrypted=false);
        //static void setCoprimes(const std::vector<Number> & coprimes);
        static void setParams(
            //const seal::RelinKeys  relinkeys,
            //const seal::CKKSEncoder  encoders,
            //const seal::Decryptor  decryptors,
            //const seal::Encryptor encryptors,
            //const seal::Evaluator evaluators,
            const std::vector<seal::RelinKeys> & relinkeys,
            const std::vector<seal::CKKSEncoder*> & encoders,
            const std::vector<seal::Decryptor*> &  decryptors,
            const std::vector<seal::Encryptor*> & encryptors,
            const std::vector<seal::Evaluator*> & evaluators,
            const std::vector<seal::SEALContext*> & context
//	    const double  scale1
        );
        static size_t slots();
};

} // crt

#include "crt.hpp"
