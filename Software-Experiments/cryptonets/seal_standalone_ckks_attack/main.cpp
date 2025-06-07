#include <chrono>
#include <iostream>
#include <vector>
#include "crt.h"
//#include "ckksencrypt.hpp"
//#include "crt_ckks.h"
#include "encryption.h"
#include "io.h"
#include "ml.h"
#include "numpy.h"
#include "seal/seal.h"
#include <fstream>

using namespace crt;
using namespace io;
using namespace numpy;
using namespace seal;
using namespace std;
using namespace std::chrono;
using DataType = double;

typedef double Number;

//double error = 3659537959120; // Error for last multiplicative depth 
double error = 387584609905099617;
//double error = 375532408642620938;



void modifyGlobalVar(double newVal) {
    error = newVal;
}


int main(int argc, char * argv[])


try {
    if ( argc < 10 )
    {
        cout << "Inform the input, weights, biases, output, and N\n";
        return 1;
    }

    std::ofstream outFile("output1.txt");

for(int err_mult =1; err_mult <= 50000; err_mult = err_mult + 1000){

   // double error1 = 3659537959120 * err_mult; // mult depth - last
    double error1 = 387584609905099617 * err_mult;
  //  double error1 = 375532408642620938 * err_mult;
     modifyGlobalVar(error1);
    const double mstos = 1000;
    high_resolution_clock::time_point t = high_resolution_clock::now();
    high_resolution_clock::time_point tStart = t;
    // get file names
    auto inFilename  = string( argv[1] );
    auto w1Filename  = string( argv[2] );
    auto w4Filename  = string( argv[3] );
    auto w8Filename  = string( argv[4] );
    auto b1Filename  = string( argv[5] );
    auto b4Filename  = string( argv[6] );
    auto b8Filename  = string( argv[7] );
    auto outFilename = string( argv[8] );
    size_t n = 1 << stoull( argv[9] );
    cout << "Polynomial degree: " << n << "\n";

    const bool isSubset = true;
    size_t interval_begin = 0, interval_end = 8192;
//    size_t interval_begin = 0, interval_end = 16384;
    cout << "slots: " << n/2 << '\n';

    // calculate scaling factors
    const size_t sbit = 6;
    const size_t ibit = sbit, w1bit = sbit, w4bit = sbit, w8bit = sbit;
    const size_t b1bit = ibit + w1bit;
    const size_t b4bit = 2*b1bit + w4bit + 2;
    const size_t b8bit = 2*b4bit + w8bit + 4;
    const DataType scaler_i  = 1 << ibit;
    const DataType scaler_w1 = 1 << w1bit;
    const DataType scaler_w4 = 1 << w4bit;
    const DataType scaler_w8 = 1 << w8bit;
    const DataType scaler_b1 = shift( Number(1), size_t(b1bit) );
    const DataType scaler_b4 = shift( Number(1), size_t(b4bit) );
    const DataType scaler_b8 = shift( Number(1), size_t(b8bit) );
    cout << "Precision/scale:\n";
    cout << " input: " << ibit << '\n';
    cout << " weights: " << w1bit << " " << w4bit << " " << w8bit << '\n';
    cout << " biases: " << b1bit << " " << b4bit << " " << b8bit << '\n';
    cout << '\n';
    milliseconds elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
//cout << "here\n";
    cout << "preamble .. ok ( " << (elapsed.count()/mstos) << " s )\n";

    // loading files
    cout << "load .. " << flush;
    t = high_resolution_clock::now();
    auto x0  = load<double>(inFilename, ',');
    auto xp  = reshape4d( x0, vector<size_t>{x0.size(),28,28,1} );
    auto yp  = load<size_t>(outFilename);
    //auto w1 = reshape4d( load<double>(w1Filename, ','), vector<size_t>{5,5,1,5} );
    auto w1 = reshape4d( load<DataType>(w1Filename, ','), vector<size_t>{5,5,1,5} );
    auto b1d = load<DataType>(b1Filename);
    auto w4 = reshape4d( load<DataType>(w4Filename, ','), vector<size_t>{5,5,5,10} );
    auto b4d = load<DataType>(b4Filename);
    auto w8 = load<DataType>(w8Filename, ',');
    auto b8d = load<DataType>(b8Filename);
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "ok ( " << (elapsed.count()/mstos) << " s )\n";

    if ( isSubset )
    {
        xp = subset(xp, interval_begin, interval_end);
        yp = subset(yp, interval_begin, interval_end);
    }

    cout << "scale .. " << flush;
    t = high_resolution_clock::now();


    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "ok ( " << (elapsed.count()/mstos) << " s )\n";

    // SEAL stuff
    cout << "encrypt .. " << flush;
    auto xps_reshaped = reshapeOrder(xp, vector<int>{1,2,3,0});

    


    double scale1 = pow(2.0, 120);

    EncryptionParameters parms(scheme_type::ckks);
    parms.set_poly_modulus_degree(n);
    vector<SEALContext*> contexts;

    parms.set_coeff_modulus(CoeffModulus::Create(n, {60,50,40,60,60,60,60,60 })); 

    SEALContext context(parms);
    

    KeyGenerator keygen(context);
    auto secret_key = keygen.secret_key();
    PublicKey public_key;
    keygen.create_public_key(public_key);
    RelinKeys relin_keys;
    keygen.create_relin_keys(relin_keys);

    vector<RelinKeys> relinkeys;
    vector<CKKSEncoder*> encoders;
    vector<Encryptor*> encryptors;
    vector<Evaluator*> evaluators;
    vector<Decryptor*> decryptors;

    relinkeys.push_back(relin_keys);
    encryptors.push_back( new Encryptor(context, public_key) );
    decryptors.push_back( new Decryptor(context, secret_key) );
    evaluators.push_back( new Evaluator(context) );
    encoders.push_back( new CKKSEncoder(context) );


    CRT<Number>::setParams(relinkeys, encoders ,decryptors, encryptors, evaluators,&context);//,scale1);

    t = high_resolution_clock::now();

    auto xc_reshaped  = crtEncryptPack(xps_reshaped);//,encoders,encryptors);
    auto xc = reshapeOrder(xc_reshaped, vector<int>{3,0,1,2} );

    auto context_data = context.key_context_data();
        for (const auto &prime : context_data->parms().coeff_modulus())
        {
            cout << prime.value() << " ";
        }
        cout << endl;


      auto b1 = b1d;
      auto b4 = b4d;
      auto b8 = b8d;
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "ok ( " << (elapsed.count()/mstos) << " s )\n";

    cout << xc[0][0][0][0].vc[0].data()[0] << endl;

    cout << "\nDimensions:\n";
    cout << "x0 "; print(shape(x0));
    cout << "xp "; print(shape(xp));
    cout << "xc "; print(shape(xc));
    cout << "yp "; print(shape(yp));
    cout << "w1 "; print(shape(w1));
    cout << "b1 "; print(shape(b1));
    cout << "w4 "; print(shape(w4));
    cout << "b4 "; print(shape(b4));
    cout << "w8 "; print(shape(w8));
    cout << "b8 "; print(shape(b8));
    cout << "\nPredict\n";
    double acc;
    t = high_resolution_clock::now();
    auto y_test_hat = ml::predict(xc,yp,w1,b1,w4,b4,w8,b8,acc);
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "The accuracy on test data for MNIST: " << acc << " ( " << (elapsed.count()/mstos) << " s )\n";
    outFile << err_mult << " "<< error << " " << acc << std::endl;
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - tStart);
    cout << "Done! ( " << (elapsed.count()/mstos) << " s )\n";
}
}
catch (const string & e) { cout << "Exception: " << e << '\n'; }
catch (const char   * e) { cout << "Exception: " << e << '\n'; }
