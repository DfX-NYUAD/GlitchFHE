#pragma once

using std::vector;
using namespace seal;

extern double error;

namespace crt
{

//template <class Number> vector<Number> CRT<Number>::coprimes;
//template <class Number> Number CRT<Number>::mod;
//template <class Number> vector<Number> CRT<Number>::nx;
//template <class Number> vector<Ciphertext> CRT<Number>::zero;

/*template <class Number> CKKSEncoder CRT<Number>::encoders;
template <class Number> Encryptor CRT<Number>::encryptors;
template <class Number> Evaluator CRT<Number>::evaluators;
template <class Number> Decryptor CRT<Number>::decryptors;
template <class Number> RelinKeys CRT<Number>::relinkeys;*/

template <class Number> vector<CKKSEncoder*> CRT<Number>::encoders;
template <class Number> vector<Encryptor*> CRT<Number>::encryptors;
template <class Number> vector<Evaluator*> CRT<Number>::evaluators;
template <class Number> vector<Decryptor*> CRT<Number>::decryptors;
template <class Number> vector<RelinKeys> CRT<Number>::relinkeys;
//template <class Number> vector<SEALContext*> CRT<Number>::context;
template <class Number> SEALContext* CRT<Number>::context;

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
//	std::cout << "from CRT Encode 2" << std::endl;
    *this = encode(a, encrypted);
}

template <class Number>
CRT<Number>::CRT(const vector<Ciphertext> & v)
{
    //if ( v.size() != coprimes.size() )
    //    throw "Size of vector<Ciphertext> during CRT constructor does not match size of coprimes";
	//std::cout << v.size() << std::endl;
    this->encrypted = true;
    vc = v;
}

template <class Number>
CRT<Number>::CRT(const vector<double> & a, bool encrypted)
{
    //std::cout << "here in crt" << std::endl;
    *this = encode(a, encrypted);
}

template <class Number>
CRT<Number>::CRT(const vector<vector<double>> & v, bool encrypted)
//CRT<Number>::CRT(const vector<double> & v, bool encrypted)
{
    this->encrypted = encrypted;

        Plaintext p;
        
//	std::cout << "in encode" << std::endl;	
        double scale2 = pow(2.0, 60);
        //double scale2 = pow(2.0, 30);
        encoders[0]->encode(v[0], scale2,p); // SEAL encoding
	//std::cout << log2(p.scale()) << std::endl;
        if (encrypted)
        {
            Ciphertext c;
            encryptors[0]->encrypt(p, c); // SEAL encryption
            vc.push_back(c);
        }
        else {vp.push_back(p);
	}
}



// operators

template <class Number>
CRT<Number> & CRT<Number>::operator+=(const CRT & a)
{
    if ( encrypted )
    {
            if ( a.encrypted ) {
             Ciphertext c1,c2;
//            std::cout << "in add here" << std::endl;
	    c2 = a.vc[0];
	    c1 = vc[0];
	    if (c1.scale() > c2.scale()){
//            std::cout << "in mod1" << std::endl;
	    c1.scale() = c2.scale(); 
	    parms_id_type last_parms_id = c1.parms_id();
            evaluators[0]->mod_switch_to_inplace(c2,last_parms_id);
	    }
            if (c1.scale() < c2.scale()){
//            std::cout << "in mod2" << std::endl;
	    c2.scale() = c1.scale(); 
	    parms_id_type last_parms_id = c2.parms_id();
            evaluators[0]->mod_switch_to_inplace(c1,last_parms_id);
	    }
            if (c1.scale() == c2.scale()){
//            std::cout << "in mod3" << std::endl;
	    auto context_data_ptr = context->get_context_data(c1.parms_id());
            auto target_context_data_ptr = context->get_context_data(c2.parms_id());
	    if (context_data_ptr->chain_index() > target_context_data_ptr->chain_index()){
	    parms_id_type last_parms_id = c2.parms_id();
            evaluators[0]->mod_switch_to_inplace(c1,last_parms_id);
	    }
	    if (context_data_ptr->chain_index() < target_context_data_ptr->chain_index()){
	    parms_id_type last_parms_id = c1.parms_id();
            evaluators[0]->mod_switch_to_inplace(c2,last_parms_id);
	    }

	    }


		    //evaluators[0]->add(c1, c2, c);
		    //evaluators[0]->add_inplace(vc[0], a.vc[0]);}
		    evaluators[0]->add_inplace(c1, c2);
                    vc[0] = c1;
    }

            else evaluators[0]->add_plain_inplace(vc[0], a.vp[0]);
    }
    else throw "Unencrypted addition not implemented";
    return *this;
}

template <class Number>
CRT<Number> & CRT<Number>::operator*=(const CRT & a)
{
    if ( encrypted )
    {
      //  for ( size_t i=0; i<coprimes.size(); i++ )
      //  {
            if ( a.encrypted )
            {
                evaluators[0]->multiply_inplace(vc[0], a.vc[0]);
                evaluators[0]->relinearize_inplace(vc[0], relinkeys[0],0,0);
            }
            else evaluators[0]->multiply_plain_inplace(vc[0], a.vp[0]);
       // }
    }
    else throw "Unencrypted multiplication not implemented";
    return *this;
}

template <class Number>
CRT<Number> & CRT<Number>::operator-=(const CRT & a)
{
    if ( encrypted )
    {
       // for ( size_t i=0; i<coprimes.size(); i++ )
       // {
            if ( a.encrypted ) evaluators[0]->sub_inplace(vc[0], a.vc[0]);
            else evaluators[0]->sub_plain_inplace(vc[0], a.vp[0]);
       // }
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
     //   for ( size_t i=0; i<coprimes.size(); i++ )
            evaluators[0]->negate(vc[0], r.vc[0]);
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
//	    std::cout << "in add operation" << std::endl;
            Ciphertext c,c1,c2;
            if ( a.encrypted ){ 
//	    std::cout << "in add operation 1" << std::endl;
	    c2 = a.vc[0];
	    c1 = vc[0];
	    if (c1.scale() > c2.scale()){
	    c1.scale() = c2.scale(); 
	    parms_id_type last_parms_id = c1.parms_id();
            evaluators[0]->mod_switch_to_inplace(c2,last_parms_id);
	    }
            else{
	    c2.scale() = c1.scale(); 
	    parms_id_type last_parms_id = c2.parms_id();
            evaluators[0]->mod_switch_to_inplace(c1,last_parms_id);
	    }

		    evaluators[0]->add(c1, c2, c);
//	    std::cout << "in add operation 1" << std::endl;
	    }
            else {
//	    std::cout << "in add operation 2" << std::endl;
	    parms_id_type last_parms_id = vc[0].parms_id();
	    Plaintext p1;
	  //  std::cout << a.vp << std::endl; 
	 //   auto p = CRT(a.vp[0], false);
	    p1 = a.vp[0];
	    c1 = vc[0];
	    c1.scale() = p1.scale(); 
            evaluators[0]->mod_switch_to_inplace(p1,last_parms_id);
            evaluators[0]->add_plain(c1, p1, c); 
           // evaluators[0]->add_plain(vc[0], p, c); 
//	    std::cout << "in add operation 2" << std::endl;
	    }
            vct.push_back(c);
       // }
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
            Ciphertext c,c1;
            if ( a.encrypted )
            {
//                std::cout << "in multiply cipher" << std::endl;	
                evaluators[0]->multiply(vc[0], a.vc[0], c);
                evaluators[0]->relinearize_inplace(c, relinkeys[0],0,0);
		if (context->last_parms_id() != c.parms_id()){
              //  evaluators[0]->rescale_to_next_inplace(c);
                evaluators[0]->rescale_to_next_inplace(c,0,0,0);}
            }
            else {
	    parms_id_type last_parms_id = vc[0].parms_id();
	    Plaintext p1;
	    p1 = a.vp[0];
	    c1 = vc[0];
	    c1.scale() = p1.scale(); 
            evaluators[0]->mod_switch_to_inplace(p1,last_parms_id);
		    //evaluators[0]->multiply_plain(vc[0], a.vp[0], c);
		    evaluators[0]->multiply_plain(c1, p1, c);
		    c1 = c;
		if (context->last_parms_id() != c.parms_id()){
                //    evaluators[0]->rescale_to_next_inplace(c);
                    evaluators[0]->rescale_to_next_inplace(c,0,0,0);
		}

	    }
            vct.push_back(c);
    }
    else throw "Unencrypted multiplication not implemented";
    return CRT<Number>(vct);
}



template <class Number>
//CRT<Number> CRT<Number>::operator^(const std::pair<const CRT<Number>&, double>& inputs) const
CRT<Number> CRT<Number>::operator^(const CRT & a) const
{
    vector<Ciphertext> vct;

    if ( encrypted )
    {
            Ciphertext c,c1;
            if ( a.encrypted )
            {
                  std::cout << "in encrypted multiply" << std::endl;

                    	
                  std::cout << "input 1" << std::endl;
                for (std::size_t i = 0; i < vc[0].dyn_array().size(); i++){
                    std::cout << vc[0][i] << " ";
                   }
                  std::cout << "" << std::endl;
                  std::cout << "input 2" << std::endl;

                for (std::size_t i = 0; i < a.vc[0].dyn_array().size(); i++){
                    std::cout << a.vc[0][i] << " ";
                 }

                evaluators[0]->multiply(vc[0], a.vc[0], c);

                  std::cout << "" << std::endl;
                  std::cout << "output after multiplication" << std::endl;

                for (std::size_t i = 0; i < c.dyn_array().size(); i++){
                    std::cout << c[i] << " ";
                 }

                evaluators[0]->relinearize_inplace(c, relinkeys[0],0,0);

                  std::cout << "" << std::endl;
                  std::cout << "output after relinearization" << std::endl;

                for (std::size_t i = 0; i < c.dyn_array().size(); i++){
                    std::cout << c[i] << " ";
                 }



		if (context->last_parms_id() != c.parms_id()){
                    evaluators[0]->rescale_to_next_inplace(c,error,error,1);}
                for (std::size_t i = 0; i < c.dyn_array().size(); i++){
                    std::cout << c[i] << " ";
                 }
            }
            else {
                  std::cout << "in plain multiply" << std::endl;
	    parms_id_type last_parms_id = vc[0].parms_id();
	    Plaintext p1;
	    p1 = a.vp[0];
	    c1 = vc[0];
	    c1.scale() = p1.scale(); 
            evaluators[0]->mod_switch_to_inplace(p1,last_parms_id);
		    evaluators[0]->multiply_plain(c1, p1, c);
		    c1 = c;
		if (context->last_parms_id() != c.parms_id()){
                    evaluators[0]->rescale_to_next_inplace(c,error,error,1);
		}

	    }
            vct.push_back(c);
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
            Ciphertext c;
            if ( a.encrypted ) evaluators[0]->sub(vc[0], a.vc[0], c);
            else evaluators[0]->sub_plain(vc[0], a.vp[0], c);
            vct.push_back(c);
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
    auto size = 1;
    vector<Plaintext> vp;
    if ( a.encrypted )
    {
        for ( size_t i=0; i<size; i++ )
        {
            Plaintext p;
            decryptors[0]->decrypt(a.vc[i], p); // SEAL decryption
            vp.push_back(p);
        }
    }
    else vp = a.vp;

    vector<vector<Number>> m;
    for ( size_t i=0; i<size; i++ )
    {
        vector<double> decoded;
        encoders[0]->decode(vp[i], decoded); // SEAL decode
        vector<Number> v;
        for ( auto e : decoded ) v.push_back( Number(e) );
        m.push_back(v);
    }
    auto nElems = m[0].size();
    vector<vector<Number>> vf( nElems, vector<Number>(size) );
    for ( size_t i=0; i<nElems; i++ )
        for ( size_t j=0; j<size; j++ ) vf[i][j] = m[j][i];

    vector<Number> vr;
    for ( auto f : vf )
    {
        Number r = 0;
        for ( auto & e : f ) r += e;
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
        n[i] = a[i];
    }
    vector<vector<double>> m;
    for ( size_t i=0; i<1; i++ )
    {	    
        vector<double> v;
        for ( size_t i=0; i<size; i++ ) v.push_back(double(n[i]) );
        m.push_back(v);
    }	
    return CRT<Number>(m, encrypted);
}

template <class Number> void
CRT<Number>::setParams(
    const vector<RelinKeys> & relinkeys,
    const vector<CKKSEncoder*> & encoders,
    const vector<Decryptor*> &  decryptors,
    const vector<Encryptor*> & encryptors,
    const vector<Evaluator*> & evaluators,
    SEALContext* context
)
{
    CRT<Number>::relinkeys = relinkeys;
    CRT<Number>::encoders = encoders;
    CRT<Number>::decryptors = decryptors;
    CRT<Number>::encryptors = encryptors;
    CRT<Number>::evaluators = evaluators;
    CRT<Number>::context = context;

    auto slots = encoders[0]->slot_count();
        Plaintext p;
        Ciphertext c;
}

template <class Number>
size_t CRT<Number>::slots()
{
    return encoders[0]->slot_count();
}

} // crt
