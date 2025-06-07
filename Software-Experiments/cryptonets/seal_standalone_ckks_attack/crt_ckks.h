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

        static std::vector<Number> coprimes;
        static Number mod;
        static std::vector<Number> nx;
        static std::vector<seal::Ciphertext> zero;

        static seal::CKKSEncoder encoder;
        static seal::Encryptor encryptor;
        static seal::Evaluator evaluator;
        static seal::Decryptor decryptor;
        static seal::RelinKeys relinkeys;

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
        CRT operator-(const CRT &) const;

        template <class T> friend CRT<T> operator+(const Number &, const CRT<T> &);
        template <class T> friend CRT<T> operator*(const Number &, const CRT<T> &);
        template <class T> friend CRT<T> operator-(const Number &, const CRT<T> &);

        std::vector<Number> decode(bool is_signed=true) const;
        static std::vector<Number> decode(const CRT & a, bool is_signed=true);
        static CRT encode(const Number &, bool encrypted=false);
        static CRT encode(const std::vector<Number> &, bool encrypted=false);
        static void setCoprimes(const std::vector<Number> & coprimes);
        static void setParams(
            const seal::RelinKeys relinkeys,
            const seal::BatchEncoder  encoder,
            const seal::Decryptor   decryptor,
            const seal::Encryptor  encryptor,
            const seal::Evaluator  evaluator
        );
        static size_t slots();
};

} // crt

#include "crt_ckks.hpp"
