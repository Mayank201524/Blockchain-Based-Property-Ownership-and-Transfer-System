#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

const unsigned int k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

unsigned int rightRotate(unsigned int value, unsigned int count) {
    return (value >> count) | (value << (32 - count));
}

class SHA256 {
public:
    static string hash(const string &input) {
        unsigned int h0 = 0x6a09e667;
        unsigned int h1 = 0xbb67ae85;
        unsigned int h2 = 0x3c6ef372;
        unsigned int h3 = 0xa54ff53a;
        unsigned int h4 = 0x510e527f;
        unsigned int h5 = 0x9b05688c;
        unsigned int h6 = 0x1f83d9ab;
        unsigned int h7 = 0x5be0cd19;

        vector<unsigned char> data(input.begin(), input.end());
        data.push_back(0x80);
        while (data.size() % 64 != 56) {
            data.push_back(0x00);
        }

        unsigned long long bitLength = input.size() * 8;
        for (int i = 7; i >= 0; --i) {
            data.push_back((bitLength >> (i * 8)) & 0xff);
        }

        for (size_t chunkStart = 0; chunkStart < data.size(); chunkStart += 64) {
            unsigned int w[64];
            for (int i = 0; i < 16; ++i) {
                w[i] = (data[chunkStart + i * 4] << 24) |
                       (data[chunkStart + i * 4 + 1] << 16) |
                       (data[chunkStart + i * 4 + 2] << 8) |
                       (data[chunkStart + i * 4 + 3]);
            }
            for (int i = 16; i < 64; ++i) {
                unsigned int s0 = rightRotate(w[i - 15], 7) ^ rightRotate(w[i - 15], 18) ^ (w[i - 15] >> 3);
                unsigned int s1 = rightRotate(w[i - 2], 17) ^ rightRotate(w[i - 2], 19) ^ (w[i - 2] >> 10);
                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }

            unsigned int a = h0;
            unsigned int b = h1;
            unsigned int c = h2;
            unsigned int d = h3;
            unsigned int e = h4;
            unsigned int f = h5;
            unsigned int g = h6;
            unsigned int h = h7;

            for (int i = 0; i < 64; ++i) {
                unsigned int S1 = rightRotate(e, 6) ^ rightRotate(e, 11) ^ rightRotate(e, 25);
                unsigned int ch = (e & f) ^ (~e & g);
                unsigned int temp1 = h + S1 + ch + k[i] + w[i];
                unsigned int S0 = rightRotate(a, 2) ^ rightRotate(a, 13) ^ rightRotate(a, 22);
                unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
                unsigned int temp2 = S0 + maj;

                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            h0 += a;
            h1 += b;
            h2 += c;
            h3 += d;
            h4 += e;
            h5 += f;
            h6 += g;
            h7 += h;
        }

        stringstream hash;
        hash << hex << setfill('0') << setw(8) << h0
             << setw(8) << h1
             << setw(8) << h2
             << setw(8) << h3
             << setw(8) << h4
             << setw(8) << h5
             << setw(8) << h6
             << setw(8) << h7;
        return hash.str();
    }
};

long long modExp(long long base, long long exponent, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % mod;
        exponent = exponent >> 1;
        base = (base * base) % mod;
    }
    return result;
}

class Transaction {
public:
    string user;
    long long x, y;
    Transaction(string user, long long x, long long y) : user(user), x(x), y(y) {}
};

class Blockchain {
private:
    vector<Transaction> transactions;
    long long p = 2147483647;
    long long g = 1000000087;
    string previousHash = "00000000000000000000000000000000";

public:
    bool verifyTransaction(long long x, long long y) {
    const int rounds = 20; // Number of rounds to make the verification more secure
    for (int i = 0; i < rounds; ++i) {
        long long r = rand() % (p - 1); // Alice's random number
        long long h = modExp(g, r, p);  // Compute h = g^r % p

        int b = rand() % 2; // Bob's random challenge bit (0 or 1)
        long long s = (r + b * x) % (p - 1); // Compute s = (r + b * x) % (p-1)

        long long left = modExp(g, s, p); // Compute g^s % p
        long long right = (h * modExp(y, b, p)) % p; // Compute (h * y^b) % p

        if (left != right) {
            return false; // If any round fails, the verification fails
        }
    }
    return true; // Only return true if all rounds pass
}


    bool createBlock(string user, long long x) {
        long long y = modExp(g, x, p);

        if (verifyTransaction(x, y)) {
            transactions.push_back(Transaction(user, x, y));
            cout << "Transaction verified! Mining block...\n";
            mineBlock();
            return true;
        } else {
            cout << "Verification failed! Transaction not added.\n";
            return false;
        }
    }

    void mineBlock() {
        long long nonce = 0;
        string blockData = previousHash;
        for (const auto &transaction : transactions) {
            blockData += transaction.user + to_string(transaction.x) + to_string(transaction.y);
        }

        string hash;
        int difficulty = 4;
        do {
            nonce++;
            string dataToHash = blockData + to_string(nonce);
            hash = SHA256::hash(dataToHash);
        } while (hash.substr(0, difficulty) != string(difficulty, '0'));

        cout << "Block mined successfully with nonce: " << nonce << "\n";
        cout << "Hash: " << hash << "\n";
        previousHash = hash;
    }

    void viewUser(string user) {
        cout << "Transactions for user: " << user << ":\n";
        bool found = false;
        for (const auto &transaction : transactions) {
            if (transaction.user == user) {
                cout << "x: " << transaction.x << ", y: " << transaction.y << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "No transactions found for user: " << user << "\n";
        }
    }
};

int main() {
    Blockchain blockchain;
    string user;
    long long x;
    int choice;

    do {
        cout << "\n--- Blockchain Menu ---\n";
        cout << "1. Create and Verify Transaction\n";
        cout << "2. View Transactions for a User\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Step 1: Ask for user's name and value of x
                cout << "Enter user's name: ";
                cin >> user;
                cout << "Enter the value of x: ";
                cin >> x;

                // Step 2: Verify and mine if successful
                if (blockchain.createBlock(user, x)) {
                    cout << "Transaction completed successfully!\n";
                } else {
                    cout << "Transaction failed. Try again.\n";
                }
                break;

            case 2:
                // Step 3: View all transactions for a user
                cout << "Enter user's name: ";
                cin >> user;
                blockchain.viewUser(user);
                break;

            case 3:
                cout << "Exiting... Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
