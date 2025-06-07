#include <chrono>
#include <iostream>
#include <vector>
#include "crt.h"
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

typedef __int128 Number;


//double error = 1847084341913;
//double error = 503394444520;
double error = 17592184717313;
//double error = 0;



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

std::ofstream outFile("output3.txt",std::ios::app);
for(int err_r = 1; err_r <= 100; err_r = err_r + 1){

    //double error1 = 1847084341913 * err_r;
    //double error1 = 503394444520 * err_r;
    double error1 = 17592184717313 * err_r;
   // double error1 = 0 * err_r;
    modifyGlobalVar(error1);
    outFile << err_r << " "<< error << " ";

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
    cout << "slots: " << n << '\n';

    // calculate scaling factors
    const size_t sbit = 6;
    const size_t ibit = sbit, w1bit = sbit, w4bit = sbit, w8bit = sbit;
    const size_t b1bit = ibit + w1bit;
    const size_t b4bit = 2*b1bit + w4bit + 2;
    const size_t b8bit = 2*b4bit + w8bit + 4;
    const Number scaler_i  = 1 << ibit;
    const Number scaler_w1 = 1 << w1bit;
    const Number scaler_w4 = 1 << w4bit;
    const Number scaler_w8 = 1 << w8bit;
    const Number scaler_b1 = shift( Number(1), size_t(b1bit) );
    const Number scaler_b4 = shift( Number(1), size_t(b4bit) );
    const Number scaler_b8 = shift( Number(1), size_t(b8bit) );
    cout << "Precision/scale:\n";
    cout << " input: " << ibit << '\n';
    cout << " weights: " << w1bit << " " << w4bit << " " << w8bit << '\n';
    cout << " biases: " << b1bit << " " << b4bit << " " << b8bit << '\n';
    cout << '\n';
    milliseconds elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "preamble .. ok ( " << (elapsed.count()/mstos) << " s )\n";

    // loading files
    cout << "load .. " << flush;
    t = high_resolution_clock::now();
    auto x0  = load<double>(inFilename, ',');
    auto xp  = reshape4d( x0, vector<size_t>{x0.size(),28,28,1} );
    auto yp  = load<size_t>(outFilename);
    auto w1d = reshape4d( load<double>(w1Filename, ','), vector<size_t>{5,5,1,5} );
    auto b1d = load<double>(b1Filename);
    auto w4d = reshape4d( load<double>(w4Filename, ','), vector<size_t>{5,5,5,10} );
    auto b4d = load<double>(b4Filename);
    auto w8d = load<double>(w8Filename, ',');
    auto b8d = load<double>(b8Filename);
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "ok ( " << (elapsed.count()/mstos) << " s )\n";

    if ( isSubset )
    {
        xp = subset(xp, interval_begin, interval_end);
        yp = subset(yp, interval_begin, interval_end);
    }

    cout << "scale .. " << flush;
    t = high_resolution_clock::now();
    auto xps = scale(xp , scaler_i);
    auto w1s = scale(w1d, scaler_w1);
    auto w4s = scale(w4d, scaler_w4);
    auto w8s = scale(w8d, scaler_w8);
    auto b1s = scale(b1d, scaler_b1);
    auto b4s = scale(b4d, scaler_b4);
    auto b8s = scale(b8d, scaler_b8);
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "ok ( " << (elapsed.count()/mstos) << " s )\n";

    // SEAL stuff
    const vector<Number> coprimes{65537, 114689, 147457, 163841, 557057};

    vector<RelinKeys> relinkeys;
    vector<BatchEncoder*> encoders;
    vector<Encryptor*> encryptors;
    vector<Evaluator*> evaluators;
    vector<Decryptor*> decryptors;

    EncryptionParameters p(scheme_type::bfv);
    p.set_poly_modulus_degree(n);
    p.set_coeff_modulus(CoeffModulus::BFVDefault(n));
    for ( auto & coprime : coprimes )
    {
        p.set_plain_modulus(coprime);
        auto context = SEALContext(p);
        auto & context_data = *context.key_context_data();
    	auto coeff_modulus = context_data.parms().coeff_modulus();
        cout << "-----------------------------------------------\n";
    	cout << "Plaintext modulus: " << int64_t(coprime) << "\n";
    	cout << "Coeff modulus size: " << context_data.total_coeff_modulus_bit_count() << " bits ( ";
    	for ( auto & c : coeff_modulus ) cout << c.bit_count() << " ";
    	cout << ")\n";
        KeyGenerator keygen(context);
        SecretKey secret_key = keygen.secret_key();
        PublicKey public_key;
        keygen.create_public_key(public_key);
        RelinKeys rk;
        keygen.create_relin_keys(rk);
        relinkeys.push_back(rk);
        encryptors.push_back( new Encryptor(context, public_key) );
        decryptors.push_back( new Decryptor(context, secret_key) );
        evaluators.push_back( new Evaluator(context) );
        encoders.push_back( new BatchEncoder(context) );
    }
    cout << "-----------------------------------------------\n";

    CRT<Number>::setCoprimes(coprimes);
    CRT<Number>::setParams(relinkeys, encoders, decryptors, encryptors, evaluators);

    cout << "coefficient modulus .. " << flush;
    for (auto &cm: p.coeff_modulus())
        std::cout << cm.value() << std::endl;



    cout << "encode/encrypt .. " << flush;
    t = high_resolution_clock::now();
    auto xps_reshaped = reshapeOrder(xps, vector<int>{1,2,3,0});
    auto xc_reshaped  = crtEncryptPack(xps_reshaped);
    auto xc = reshapeOrder(xc_reshaped, vector<int>{3,0,1,2} );
    //auto x_encrypted = xc[0][0][0][0].vc[0];
   // unsigned long long int temp;

//  for (int i = 0; i < 4096; i++){
    // if (i%2 == 0){
    // xc[0][7][7][0].vc[0].data()[i] = xc[0][7][7][0].vc[0].data()[i];//+(9999999999999999+9999);//99);//+1);
    // }
    // if (i%2 == 1){
    // xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[i]/2;//+(9999999999999999+9999);//99);//+1);
    // }

//    temp = xc[0][0][0][0].vc[0].data()[i];
//    xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[8191-i];
//    xc[0][0][0][0].vc[0].data()[8191-i] = temp;
     
 //   }
/*

    for (int i = 8192; i < 12288; i++){
    // if (i%2 == 0){
    // xc[0][7][7][0].vc[0].data()[i] = xc[0][7][7][0].vc[0].data()[i];//+(9999999999999999+9999);//99);//+1);
    // }
    // if (i%2 == 1){
    // xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[i]/2;//+(9999999999999999+9999);//99);//+1);
    // }

    temp = xc[0][0][0][0].vc[0].data()[i];
    xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[16383-i];
    xc[0][0][0][0].vc[0].data()[16383-i] = temp;
     
    }
    for (int i = 16384; i < 20480; i++){
    // if (i%2 == 0){
    // xc[0][7][7][0].vc[0].data()[i] = xc[0][7][7][0].vc[0].data()[i];//+(9999999999999999+9999);//99);//+1);
    // }
    // if (i%2 == 1){
    // xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[i]/2;//+(9999999999999999+9999);//99);//+1);
    // }

    temp = xc[0][0][0][0].vc[0].data()[i];
    xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[24575-i];
    xc[0][0][0][0].vc[0].data()[24575-i] = temp;
     
    }
    for (int i = 24576; i < 28672; i++){
    // if (i%2 == 0){
    // xc[0][7][7][0].vc[0].data()[i] = xc[0][7][7][0].vc[0].data()[i];//+(9999999999999999+9999);//99);//+1);
    // }
    // if (i%2 == 1){
    // xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[i]/2;//+(9999999999999999+9999);//99);//+1);
    // }

    temp = xc[0][0][0][0].vc[0].data()[i];
    xc[0][0][0][0].vc[0].data()[i] = xc[0][0][0][0].vc[0].data()[32767-i];
    xc[0][0][0][0].vc[0].data()[32767-i] = temp;
     
    }
*/



    auto & w1 = w1s;
    auto & w4 = w4s;
    auto & w8 = w8s;
    auto b1 = crtEncode(b1s);
    auto b4 = crtEncode(b4s);
    auto b8 = crtEncode(b8s);
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - t);
    cout << "ok ( " << (elapsed.count()/mstos) << " s )\n";

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
    outFile << acc << std::endl;
    elapsed = duration_cast<milliseconds>(high_resolution_clock::now() - tStart);
    cout << "Done! ( " << (elapsed.count()/mstos) << " s )\n";
}
}
catch (const string & e) { cout << "Exception: " << e << '\n'; }
catch (const char   * e) { cout << "Exception: " << e << '\n'; }
