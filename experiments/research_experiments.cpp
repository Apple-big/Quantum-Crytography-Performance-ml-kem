#include <ml_kem/ml_kem_512.hpp>
#include <ml_kem/ml_kem_768.hpp>
#include <ml_kem/ml_kem_1024.hpp>
#include <randomshake/randomshake.hpp>
#include <vector>
#include <numeric>
#include <cmath>

#include <chrono>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;
using namespace chrono;

constexpr int NUM_TRANSACTIONS = 500000;
constexpr int NUM_TRIALS = 5;
double mean(const vector<double>& v)
{
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double stddev(const vector<double>& v)
{
    double m = mean(v);
    double sum = 0.0;

    for (double x : v)
        sum += (x - m) * (x - m);

    return sqrt(sum / (v.size() - 1));
}
// Todo: Test this function
void evaluate_ml_kem_512(ofstream& csv)
{
array<uint8_t, ml_kem_512::SEED_D_BYTE_LEN> seed_d{};
array<uint8_t, ml_kem_512::SEED_Z_BYTE_LEN> seed_z{};
array<uint8_t, ml_kem_512::SEED_M_BYTE_LEN> seed_m{};

array<uint8_t, ml_kem_512::PKEY_BYTE_LEN> pubkey{};    
array<uint8_t, ml_kem_512::SKEY_BYTE_LEN> seckey{};    

array<uint8_t, ml_kem_512::CIPHER_TEXT_BYTE_LEN> cipher{};    
array<uint8_t, ml_kem_512::SHARED_SECRET_BYTE_LEN> ss1{};    
array<uint8_t, ml_kem_512::SHARED_SECRET_BYTE_LEN> ss2{};    

randomshake::randomshake_t rng;    
vector<double> keygen_results;
vector<double> encap_results;
vector<double> decap_results;
vector<double> total_results;
vector<double> throughput_results;
// Warm-up (not timed)
ml_kem_512::keygen(seed_d, seed_z, pubkey, seckey);
ml_kem_512::encapsulate(seed_m, pubkey, cipher, ss1);
ml_kem_512::decapsulate(seckey, cipher, ss2);

for (int trial = 1; trial <= NUM_TRIALS; ++trial)
{
rng.generate(seed_d);    
rng.generate(seed_z);    
rng.generate(seed_m);    

auto t1 = high_resolution_clock::now();    

for (int i = 0; i < NUM_TRANSACTIONS; ++i)    
{    
    ml_kem_512::keygen(seed_d, seed_z, pubkey, seckey);    
}    

auto t2 = high_resolution_clock::now();    

for (int i = 0; i < NUM_TRANSACTIONS; ++i)    
{    
    auto ok = ml_kem_512::encapsulate(seed_m, pubkey, cipher, ss1);
if (!ok)
{
    cerr << "Encapsulation failed." << endl;
    return;
}
}    

auto t3 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_512::decapsulate(seckey, cipher, ss2);

    // Verify that both parties derived the same shared secret
    if (ss1 != ss2)
    {
        cerr << "Shared secret mismatch." << endl;
        return;
    }
}

auto t4 = high_resolution_clock::now();    


double keygen_latency = duration<double, micro>(t2 - t1).count() / NUM_TRANSACTIONS;    

double encap_latency = duration<double, micro>(t3 - t2).count() / NUM_TRANSACTIONS;    

double decap_latency = duration<double, micro>(t4 - t3).count() / NUM_TRANSACTIONS;

double total_latency = keygen_latency + encap_latency + decap_latency;

double total_time_seconds = total_latency * NUM_TRANSACTIONS / 1e6;

double throughput = NUM_TRANSACTIONS / total_time_seconds;

keygen_results.push_back(keygen_latency);
encap_results.push_back(encap_latency);
decap_results.push_back(decap_latency);
total_results.push_back(total_latency);
throughput_results.push_back(throughput);

cout << "\n====== ML-KEM-512 : Trial " << trial << " of " << NUM_TRIALS << " ======\n";
cout << "Key generation latency: " << keygen_latency << " us\n";
cout << "Encapsulation latency: " << encap_latency << " us\n";
cout << "Decapsulation latency: " << decap_latency << " us\n";
cout << "Total latency: " << total_latency << " us\n";
cout << "Throughput: " << throughput << " transactions/sec\n";
cout << "Public key size: " << sizeof(pubkey) << " bytes\n";
cout << "Secret key size: " << sizeof(seckey) << " bytes\n";
cout << "Ciphertext size: " << sizeof(cipher) << " bytes\n";

csv << trial << ","
    << "ML-KEM-512,"
    << NUM_TRANSACTIONS << ","
    << keygen_latency << ","
    << encap_latency << ","
    << decap_latency << ","
    << total_latency << ","
    << throughput << ","
    << sizeof(pubkey) << ","
    << sizeof(seckey) << ","
    << sizeof(cipher)
    << endl;
}

cout << "\n===== Summary (ML-KEM-512) =====\n";

cout << "Key generation latency: "
    << mean(keygen_results) << " ± "
    << stddev(keygen_results) << " us\n";

cout << "Encapsulation latency: "
    << mean(encap_results) << " ± "
    << stddev(encap_results) << " us\n";

cout << "Decapsulation latency: "
    << mean(decap_results) << " ± "
    << stddev(decap_results) << " us\n";

cout << "Total latency: "
    << mean(total_results) << " ± "
    << stddev(total_results) << " us\n";

cout << "Throughput: "
    << mean(throughput_results) << " ± "
    << stddev(throughput_results)
    << " transactions/sec\n";

cout << "Public key size: " << sizeof(pubkey) << " bytes\n";
cout << "Secret key size: " << sizeof(seckey) << " bytes\n";
cout << "Ciphertext size: " << sizeof(cipher) << " bytes\n";

}

void evaluate_ml_kem_768(ofstream& csv)
{
    array<uint8_t, ml_kem_768::SEED_D_BYTE_LEN> seed_d{};
    array<uint8_t, ml_kem_768::SEED_Z_BYTE_LEN> seed_z{};
    array<uint8_t, ml_kem_768::SEED_M_BYTE_LEN> seed_m{};

    array<uint8_t, ml_kem_768::PKEY_BYTE_LEN> pubkey{};
    array<uint8_t, ml_kem_768::SKEY_BYTE_LEN> seckey{};

    array<uint8_t, ml_kem_768::CIPHER_TEXT_BYTE_LEN> cipher{};
    array<uint8_t, ml_kem_768::SHARED_SECRET_BYTE_LEN> ss1{};
    array<uint8_t, ml_kem_768::SHARED_SECRET_BYTE_LEN> ss2{};

    randomshake::randomshake_t rng;

    vector<double> keygen_results;
    vector<double> encap_results;
    vector<double> decap_results;
    vector<double> total_results;
    vector<double> throughput_results;

    // Warm-up (not timed)
    ml_kem_768::keygen(seed_d, seed_z, pubkey, seckey);
    ml_kem_768::encapsulate(seed_m, pubkey, cipher, ss1);
    ml_kem_768::decapsulate(seckey, cipher, ss2);

    for (int trial = 1; trial <= NUM_TRIALS; ++trial)
    {
        rng.generate(seed_d);
        rng.generate(seed_z);
        rng.generate(seed_m);

        auto t1 = high_resolution_clock::now();

        for (int i = 0; i < NUM_TRANSACTIONS; ++i)
        {
            ml_kem_768::keygen(seed_d, seed_z, pubkey, seckey);
        }

        auto t2 = high_resolution_clock::now();

        for (int i = 0; i < NUM_TRANSACTIONS; ++i)
        {
        auto ok = ml_kem_768::encapsulate(seed_m, pubkey, cipher, ss1);

            if (!ok)
            {
                cerr << "Encapsulation failed." << endl;
                return;
            }
        }

        auto t3 = high_resolution_clock::now();

        for (int i = 0; i < NUM_TRANSACTIONS; ++i)
    {
    ml_kem_768::decapsulate(seckey, cipher, ss2);

    // Verify that both parties derived the same shared secret
    if (ss1 != ss2)
    {
        cerr << "Shared secret mismatch." << endl;
        return;
    }
    }
        auto t4 = high_resolution_clock::now();

        double keygen_latency =
            duration<double, micro>(t2 - t1).count() / NUM_TRANSACTIONS;

        double encap_latency =
            duration<double, micro>(t3 - t2).count() / NUM_TRANSACTIONS;

        double decap_latency =
            duration<double, micro>(t4 - t3).count() / NUM_TRANSACTIONS;

        double total_latency =
            keygen_latency + encap_latency + decap_latency;

        double total_time_seconds =
            total_latency * NUM_TRANSACTIONS / 1e6;

        double throughput =
            NUM_TRANSACTIONS / total_time_seconds;

        keygen_results.push_back(keygen_latency);
        encap_results.push_back(encap_latency);
        decap_results.push_back(decap_latency);
        total_results.push_back(total_latency);
        throughput_results.push_back(throughput);

        cout << "\n====== ML-KEM-768 : Trial " << trial << " of " << NUM_TRIALS << " ======\n";
        cout << "Key generation latency: " << keygen_latency << " us\n";
        cout << "Encapsulation latency: " << encap_latency << " us\n";
        cout << "Decapsulation latency: " << decap_latency << " us\n";
        cout << "Total latency: " << total_latency << " us\n";
        cout << "Throughput: " << throughput << " transactions/sec\n";
        cout << "Public key size: " << sizeof(pubkey) << " bytes\n";
        cout << "Secret key size: " << sizeof(seckey) << " bytes\n";
        cout << "Ciphertext size: " << sizeof(cipher) << " bytes\n";

        csv << trial << "," 
        << "ML-KEM-768,"
            << NUM_TRANSACTIONS << ","
            << keygen_latency << ","
            << encap_latency << ","
            << decap_latency << ","
            << total_latency << ","
            << throughput << ","
            << sizeof(pubkey) << ","
            << sizeof(seckey) << ","
            << sizeof(cipher)
            << endl;
    }

    cout << "\n===== Summary (ML-KEM-768) =====\n";

    cout << "Key generation latency: "
        << mean(keygen_results) << " ± "
        << stddev(keygen_results) << " us\n";

    cout << "Encapsulation latency: "
        << mean(encap_results) << " ± "
        << stddev(encap_results) << " us\n";

    cout << "Decapsulation latency: "
        << mean(decap_results) << " ± "
        << stddev(decap_results) << " us\n";

    cout << "Total latency: "
        << mean(total_results) << " ± "
        << stddev(total_results) << " us\n";

    cout << "Throughput: "
        << mean(throughput_results) << " ± "
        << stddev(throughput_results)
        << " transactions/sec\n";

    cout << "Public key size: " << sizeof(pubkey) << " bytes\n";
    cout << "Secret key size: " << sizeof(seckey) << " bytes\n";
    cout << "Ciphertext size: " << sizeof(cipher) << " bytes\n";
}

void evaluate_ml_kem_1024(ofstream& csv)
{
    array<uint8_t, ml_kem_1024::SEED_D_BYTE_LEN> seed_d{};
    array<uint8_t, ml_kem_1024::SEED_Z_BYTE_LEN> seed_z{};
    array<uint8_t, ml_kem_1024::SEED_M_BYTE_LEN> seed_m{};

    array<uint8_t, ml_kem_1024::PKEY_BYTE_LEN> pubkey{};
    array<uint8_t, ml_kem_1024::SKEY_BYTE_LEN> seckey{};

    array<uint8_t, ml_kem_1024::CIPHER_TEXT_BYTE_LEN> cipher{};
    array<uint8_t, ml_kem_1024::SHARED_SECRET_BYTE_LEN> ss1{};
    array<uint8_t, ml_kem_1024::SHARED_SECRET_BYTE_LEN> ss2{};

    randomshake::randomshake_t rng;

    vector<double> keygen_results;
    vector<double> encap_results;
    vector<double> decap_results;
    vector<double> total_results;
    vector<double> throughput_results;

    // Warm-up (not timed)
    ml_kem_1024::keygen(seed_d, seed_z, pubkey, seckey);
    ml_kem_1024::encapsulate(seed_m, pubkey, cipher, ss1);
    ml_kem_1024::decapsulate(seckey, cipher, ss2);

    for (int trial = 1; trial <= NUM_TRIALS; ++trial)
    {
        rng.generate(seed_d);
        rng.generate(seed_z);
        rng.generate(seed_m);

        auto t1 = high_resolution_clock::now();

        for (int i = 0; i < NUM_TRANSACTIONS; ++i)
        {
            ml_kem_1024::keygen(seed_d, seed_z, pubkey, seckey);
        }

        auto t2 = high_resolution_clock::now();

        for (int i = 0; i < NUM_TRANSACTIONS; ++i)
        {
            auto ok = ml_kem_1024::encapsulate(seed_m, pubkey, cipher, ss1);

            if (!ok)
            {
                cerr << "Encapsulation failed." << endl;
                return;
            }
        }

        auto t3 = high_resolution_clock::now();

        for (int i = 0; i < NUM_TRANSACTIONS; ++i)
        {
        ml_kem_1024::decapsulate(seckey, cipher, ss2);

    // Verify that both parties derived the same shared secret
    if (ss1 != ss2)
    {
        cerr << "Shared secret mismatch." << endl;
        return;
    }
}

        auto t4 = high_resolution_clock::now();

        double keygen_latency =
            duration<double, micro>(t2 - t1).count() / NUM_TRANSACTIONS;

        double encap_latency =
            duration<double, micro>(t3 - t2).count() / NUM_TRANSACTIONS;

        double decap_latency =
            duration<double, micro>(t4 - t3).count() / NUM_TRANSACTIONS;

        double total_latency =
            keygen_latency + encap_latency + decap_latency;

        double total_time_seconds =
            total_latency * NUM_TRANSACTIONS / 1e6;

        double throughput =
            NUM_TRANSACTIONS / total_time_seconds;

        keygen_results.push_back(keygen_latency);
        encap_results.push_back(encap_latency);
        decap_results.push_back(decap_latency);
        total_results.push_back(total_latency);
        throughput_results.push_back(throughput);

        cout << "\n====== ML-KEM-1024 : Trial " << trial << " of " << NUM_TRIALS << " ======\n";

        cout << "Key generation latency: " << keygen_latency << " us\n";
        cout << "Encapsulation latency: " << encap_latency << " us\n";
        cout << "Decapsulation latency: " << decap_latency << " us\n";
        cout << "Total latency: " << total_latency << " us\n";
        cout << "Throughput: " << throughput << " transactions/sec\n";
        cout << "Public key size: " << sizeof(pubkey) << " bytes\n";
        cout << "Secret key size: " << sizeof(seckey) << " bytes\n";
        cout << "Ciphertext size: " << sizeof(cipher) << " bytes\n";

        csv << trial << ","
            << "ML-KEM-1024,"
            << NUM_TRANSACTIONS << ","
            << keygen_latency << ","
            << encap_latency << ","
            << decap_latency << ","
            << total_latency << ","
            << throughput << ","
            << sizeof(pubkey) << ","
            << sizeof(seckey) << ","
            << sizeof(cipher)
            << endl;
    }

    cout << "\n===== Summary (ML-KEM-1024) =====\n";

    cout << "Key generation latency: "
        << mean(keygen_results) << " ± "
        << stddev(keygen_results) << " us\n";

    cout << "Encapsulation latency: "
        << mean(encap_results) << " ± "
        << stddev(encap_results) << " us\n";

    cout << "Decapsulation latency: "
        << mean(decap_results) << " ± "
        << stddev(decap_results) << " us\n";

    cout << "Total latency: "
        << mean(total_results) << " ± "
        << stddev(total_results) << " us\n";

    cout << "Throughput: "
        << mean(throughput_results) << " ± "
        << stddev(throughput_results)
        << " transactions/sec\n";

    cout << "Public key size: " << sizeof(pubkey) << " bytes\n";
    cout << "Secret key size: " << sizeof(seckey) << " bytes\n";
    cout << "Ciphertext size: " << sizeof(cipher) << " bytes\n";
}
int main()
{
    ofstream csv("results/experiment_results.csv");

    csv << "Trial,"
        << "ParameterSet,"
        << "Transactions,"
        << "KeyGenLatency,"
        << "EncapsulationLatency,"
        << "DecapsulationLatency,"
        << "TotalLatency,"
        << "Throughput,"
        << "PublicKeySize,"
        << "SecretKeySize,"
        << "CiphertextSize"
        << endl;

    evaluate_ml_kem_512(csv);
    evaluate_ml_kem_768(csv);
    evaluate_ml_kem_1024(csv);

    csv.close();

    return 0;
}