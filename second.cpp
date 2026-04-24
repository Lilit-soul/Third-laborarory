#include <iostream>
#include <vector>
#include <random>
#include <set>
#include <cmath>
#include <iomanip>
#include <chrono>

using namespace std;
using namespace chrono;

mt19937_64 rng(steady_clock::now().time_since_epoch().count());

unsigned long long gcd(unsigned long long a, unsigned long long b) {
    while (b) { unsigned long long t = b; b = a % b; a = t; }
    return a;
}

unsigned long long modPow(unsigned long long a, unsigned long long e, unsigned long long m) {
    unsigned long long r = 1;
    for (a %= m; e; e >>= 1, a = (a * a) % m)
        if (e & 1) r = (r * a) % m;
    return r;
}
// Решето Эратосфена
vector<int> sieveOfEratosthenes(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= limit; ++i)
        if (isPrime[i])
            for (int j = i * i; j <= limit; j += i)
                isPrime[j] = false;
    vector<int> primes;
    for (int i = 2; i <= limit; ++i)
        if (isPrime[i]) primes.push_back(i);
    return primes;
}

unsigned long long randomBits(int bits) {
    if (bits <= 1) return 1;
    unsigned long long x = 1ULL << (bits - 1);
    for (int i = 0; i < bits - 1; ++i)
        if (rng() & 1) x |= (1ULL << i);
    return x;
}

// Генерация числа n = R*F + 1
bool generateN(int bits, const vector<int>& primes, 
               unsigned long long& n, unsigned long long& F, 
               vector<int>& qiList, unsigned long long& R) {
    
    int needBits = bits / 2 + 1;
    if (needBits < 2) needBits = 2;
    
    F = 1;
    qiList.clear();
    set<int> usedQ;
    
    unsigned long long targetMin = (1ULL << (needBits - 1));
    if (targetMin < 2) targetMin = 2;
    
    int attempts = 0;
    while (F < targetMin && attempts < 50) {
        int q = primes[rng() % primes.size()];
        if (usedQ.count(q)) continue;
        usedQ.insert(q);
        
        unsigned long long qp = q;
        if (F > (1ULL << 60) / qp) continue;
        
        F *= qp;
        qiList.push_back(q);
        attempts++;
    }
    
    if (F < targetMin) return false;
    
    int fbits = 0;
    unsigned long long tmp = F;
    while (tmp) { fbits++; tmp >>= 1; }
    int rbits = max(1, fbits - 1);
    
    int rAttempts = 0;
    do {
        R = randomBits(rbits);
        if (R % 2 != 0) R++;
        if (R < 2) R = 2;
        rAttempts++;
        if (rAttempts > 30) return false;
    } while (R >= F);
    
    n = R * F + 1;
    
    int nbits = 0;
    tmp = n;
    while (tmp) { nbits++; tmp >>= 1; }
    
    return (nbits == bits);
}

// Тест Поклингтона
bool pocklingtonTest(unsigned long long n, unsigned long long F, 
                      const vector<int>& qiList, int t) {
    unsigned long long n1 = n - 1;
    uniform_int_distribution<unsigned long long> dist(2, n - 1);
    
    for (int attempt = 0; attempt < 15; ++attempt) {
        vector<unsigned long long> aList;
        set<unsigned long long> usedA;
        
        while (aList.size() < (size_t)t) {
            unsigned long long a = dist(rng);
            if (usedA.count(a)) continue;
            usedA.insert(a);
            aList.push_back(a);
        }
        
        bool ok = true;
        for (auto a : aList)
            if (modPow(a, n1, n) != 1) { ok = false; break; }
        if (!ok) continue;
        
        ok = true;
        for (int q : qiList) {
            bool found = false;
            for (auto a : aList) {
                unsigned long long val = modPow(a, n1 / q, n);
                val = (val - 1 + n) % n;
                if (gcd(val, n) == 1) { found = true; break; }
            }
            if (!found) { ok = false; break; }
        }
        
        if (ok) return true;
    }
    return false;
}

// Проверка числа с дополнительной проверкой t=2
bool isPrimeNumber(unsigned long long n, unsigned long long F, 
                    const vector<int>& qiList, unsigned long long R) {
    
    if (gcd(R, F) != 1) return false;
    if (F <= (unsigned long long)sqrt(n) - 1) return false;
    
    if (!pocklingtonTest(n, F, qiList, 3)) return false;
    if (!pocklingtonTest(n, F, qiList, 2)) return false;
    
    return true;
}

int main() {
    int bits;
    cout << "bits: ";
    cin >> bits;
    
    vector<int> primes = sieveOfEratosthenes(500);
    
    cout << left << setw(5) << "№ "
         << left << setw(20) << "| Простое число "
         << left << setw(25) << "| Результат проверки "
         << left << setw(10) << "| Кол-во отвергнутых чисел (rejected)" << endl;
    cout << string(80, '-') << endl;
    
    for (int i = 1; i <= 10; ++i) {
        unsigned long long n = 0, F = 0, R = 0;
        vector<int> qiList;
        
        // Генерируем число-кандидат и считаем rejected
        int rejected = 0;
        bool generated = false;
        
        while (!generated) {
            generated = generateN(bits, primes, n, F, qiList, R);
            if (!generated) {
                rejected++;
            }
        }
        
        // Проверяем число тестом 
        bool isPrime = isPrimeNumber(n, F, qiList, R);
        
        // Доп проверка для простых чисел
        if (isPrime) {
        }
        
        cout << left << setw(10) << i
             << left << setw(15) << n
             << left << setw(25) << (isPrime ? "true" : "false")
             << left << setw(10) << rejected << endl;
    }
    return 0;
}
