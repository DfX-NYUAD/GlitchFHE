#pragma once

#include <vector>
#include "seal/seal.h"

namespace crt
{

template <class Number>
class CRT
{
    public:
        std::vector<seal::Plaintext> vp;
        std::vector<seal::Ciphertext> vc;
        bool encrypted;

    private:
        static std::vector<Number> coprimes;
        static Number mod;
        static std::vector<Number> nx;
        static std::vector<seal::Ciphertext> zero;

        static std::vector<seal::BatchEncoder*> encoders;
        static std::vector<seal::Encryptor*> encryptors;
        static std::vector<seal::Evaluator*> evaluators;
        static std::vector<seal::Decryptor*> decryptors;
        static std::vector<seal::RelinKeys> relinkeys;

    public:
        CRT() : CRT( Number(0) ) {}
        CRT(const CRT & a);
        CRT(const Number &, bool encrypted=false);
        CRT(const std::vector<seal::Ciphertext> &);
        CRT(const std::vector<Number> &, bool encrypted=false);
        CRT(const std::vector<std::vector<uint64_t>> &, bool encrypted);

        CRT & operator+=(const CRT &);
        CRT & operator*=(const CRT &);
        CRT & operator-=(const CRT &);

        CRT operator-() const;
        CRT operator+(const CRT &) const;
        CRT operator*(const CRT &) const;
        CRT operator^(const CRT &) const;
        CRT operator-(const CRT &) const;

        template <class T> friend CRT<T> operator+(const Number &, const CRT<T> &);
        template <class T> friend CRT<T> operator*(const Number &, const CRT<T> &);
        template <class T> friend CRT<T> operator^(const Number &, const CRT<T> &);
        template <class T> friend CRT<T> operator-(const Number &, const CRT<T> &);

        std::vector<Number> decode(bool is_signed=true) const;
        static std::vector<Number> decode(const CRT & a, bool is_signed=true);
        static CRT encode(const Number &, bool encrypted=false);
        static CRT encode(const std::vector<Number> &, bool encrypted=false);
        static void setCoprimes(const std::vector<Number> & coprimes);
        static void setParams(
            const std::vector<seal::RelinKeys> & relinkeys,
            const std::vector<seal::BatchEncoder*> & encoders,
            const std::vector<seal::Decryptor*> &  decryptors,
            const std::vector<seal::Encryptor*> & encryptors,
            const std::vector<seal::Evaluator*> & evaluators
        );
        static size_t slots();
};

} // crt

#include "crt.hpp"
