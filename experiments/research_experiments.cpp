
#include <ml_kem/ml_kem_512.hpp>
#include <ml_kem/ml_kem_768.hpp>
#include <ml_kem/ml_kem_1024.hpp>
#include <randomshake/randomshake.hpp>

#include <chrono>
#include <iostream>
#include <fstream>
#include <array>

using namespace std;
using namespace chrono;

constexpr int NUM_TRANSACTIONS = 1000000;

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

    rng.generate(seed_d);
    rng.generate(seed_z);
    rng.generate(seed_m);

    const int Num_Transactions = 1000000;


auto t1 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_512::keygen(seed_d, seed_z, pubkey, seckey);
}

auto t2 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_512::encapsulate(seed_m, pubkey, cipher, ss1);
}

auto t3 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_512::decapsulate(seckey, cipher, ss2);
}

auto t4 = high_resolution_clock::now();


 double keygen_latency = duration<double, micro>(t2 - t1).count() / NUM_TRANSACTIONS;

double encap_latency = duration<double, micro>(t3 - t2).count() / NUM_TRANSACTIONS;

double decap_latency = duration<double, micro>(t4 - t3).count() / NUM_TRANSACTIONS;

double total_latency = keygen_latency + encap_latency + decap_latency;

    double throughput = 1000000.0 / total_latency;

    size_t memory_usage =
        sizeof(seed_d) + sizeof(seed_z) + sizeof(seed_m) +
        sizeof(pubkey) + sizeof(seckey) +
        sizeof(cipher) + sizeof(ss1) + sizeof(ss2);

    size_t computational_overhead =
        sizeof(pubkey) + sizeof(seckey) + sizeof(cipher);

    cout << "\n===== ML-KEM-512 =====\n";
    cout << "Key generation latency: " << keygen_latency << " us\n";
    cout << "Encapsulation latency: " << encap_latency << " us\n";
    cout << "Decapsulation latency: " << decap_latency << " us\n";
    cout << "Total latency: " << total_latency << " us\n";
    cout << "Throughput: " << throughput << " transactions/sec\n";

    csv << "ML-KEM-512,"
    << NUM_TRANSACTIONS << ","
    << keygen_latency << ","
    << encap_latency << ","
    << decap_latency << ","
    << total_latency << ","
    << throughput << ","
    << sizeof(pubkey) << ","
    << sizeof(seckey) << ","
    << sizeof(cipher) << ","
    << memory_usage << ","
    << computational_overhead
    << endl;
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

    rng.generate(seed_d);
    rng.generate(seed_z);
    rng.generate(seed_m);

     const int Num_Transactions = 1000000;

auto t1 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_768::keygen(seed_d, seed_z, pubkey, seckey);
}

auto t2 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_768::encapsulate(seed_m, pubkey, cipher, ss1);
}

auto t3 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_768::decapsulate(seckey, cipher, ss2);
}

auto t4 = high_resolution_clock::now();
==
double keygen_latency = duration<double, micro>(t2 - t1).count() / NUM_TRANSACTIONS;

double encap_latency = duration<double, micro>(t3 - t2).count() / NUM_TRANSACTIONS;

double decap_latency = duration<double, micro>(t4 - t3).count() / NUM_TRANSACTIONS;

double total_latency = keygen_latency + encap_latency + decap_latency;

    double throughput = 1000000.0 / total_latency;

    size_t memory_usage =
        sizeof(seed_d) + sizeof(seed_z) + sizeof(seed_m) +
        sizeof(pubkey) + sizeof(seckey) +
        sizeof(cipher) + sizeof(ss1) + sizeof(ss2);

    size_t computational_overhead =
        sizeof(pubkey) + sizeof(seckey) + sizeof(cipher);

    cout << "\n===== ML-KEM-768 =====\n";

    csv << "ML-KEM-768,"
    << NUM_TRANSACTIONS << ","
    << keygen_latency << ","
    << encap_latency << ","
    << decap_latency << ","
    << total_latency << ","
    << throughput << ","
    << sizeof(pubkey) << ","
    << sizeof(seckey) << ","
    << sizeof(cipher) << ","
    << memory_usage << ","
    << computational_overhead
    << endl;
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

    rng.generate(seed_d);
    rng.generate(seed_z);
    rng.generate(seed_m);

     const int Num_Transactions = 1000000;

auto t1 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_1024::keygen(seed_d, seed_z, pubkey, seckey);
}

auto t2 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_1024::encapsulate(seed_m, pubkey, cipher, ss1);
}

auto t3 = high_resolution_clock::now();

for (int i = 0; i < NUM_TRANSACTIONS; ++i)
{
    ml_kem_1024::decapsulate(seckey, cipher, ss2);
}

auto t4 = high_resolution_clock::now();

double keygen_latency = duration<double, micro>(t2 - t1).count() / NUM_TRANSACTIONS;

double encap_latency = duration<double, micro>(t3 - t2).count() / NUM_TRANSACTIONS;

double decap_latency = duration<double, micro>(t4 - t3).count() / NUM_TRANSACTIONS;

double total_latency = keygen_latency + encap_latency + decap_latency;

    double throughput = 1000000.0 / total_latency;

    size_t memory_usage =
        sizeof(seed_d) + sizeof(seed_z) + sizeof(seed_m) +
        sizeof(pubkey) + sizeof(seckey) +
        sizeof(cipher) + sizeof(ss1) + sizeof(ss2);

    size_t computational_overhead =
        sizeof(pubkey) + sizeof(seckey) + sizeof(cipher);

    cout << "\n===== ML-KEM-1024 =====\n";

    csv << "ML-KEM-1024,"
    << NUM_TRANSACTIONS << ","
    << keygen_latency << ","
    << encap_latency << ","
    << decap_latency << ","
    << total_latency << ","
    << throughput << ","
    << sizeof(pubkey) << ","
    << sizeof(seckey) << ","
    << sizeof(cipher) << ","
    << memory_usage << ","
    << computational_overhead
    << endl;
}

int main()
{
    ofstream csv("results/experiment_results.csv");

    csv
        << "ParameterSet,"
        << "Transactions,"
        << "KeyGenLatency,"
        << "EncapsulationLatency,"
        << "DecapsulationLatency,"
        << "TotalLatency,"
        << "Throughput,"
        << "PublicKeySize,"
        << "SecretKeySize,"
        << "CiphertextSize,"
        << "MemoryUsage,"
        << "ComputationalOverhead"
        << endl;

    evaluate_ml_kem_512(csv);
    evaluate_ml_kem_768(csv);
    evaluate_ml_kem_1024(csv);

    csv.close();

    return 0;
}