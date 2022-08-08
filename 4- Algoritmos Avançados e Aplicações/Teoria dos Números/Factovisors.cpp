#include <iostream>
#include <cmath>
#include <bitset>
#include <vector>
#include <unordered_map>

#define TOTAL_PRIMES 65536    // sqrt(MAX_UINT32)

using namespace std;

typedef unordered_map<uint, uint> Divisors;


vector<uint> buildPrimeFactors() {
    
    bitset<TOTAL_PRIMES + 1> invalidPrimes;
    invalidPrimes[0] = true, invalidPrimes[1] = true;

    for (uint currNumber = 2; currNumber <= TOTAL_PRIMES; currNumber++) {
        if (!invalidPrimes[currNumber]) {
            for (uint multiple = currNumber * currNumber; multiple <= TOTAL_PRIMES; multiple += currNumber)
                invalidPrimes[multiple] = true;
        }
    }

    vector<uint> primeFactors;

    for (uint i = 0; i <= TOTAL_PRIMES; i++)
        if (!invalidPrimes[i])
            primeFactors.push_back(i);

    return primeFactors;
}


uint evaluateDivisorMultiplicity(uint number, uint divisor) {

    uint multiplicity = 0;

    while (number % divisor == 0) {
        number /= divisor;
        multiplicity++;
    }

    return multiplicity;
}


Divisors factorNumber(uint number, vector<uint> &primeFactors) {

    Divisors divisors;

    for (uint prime : primeFactors) {
        if (number == 1)
            break;
        while (number % prime == 0) {
            divisors[prime] = divisors.find(prime) == divisors.end() ? 1 : divisors[prime] + 1;
            number /= prime;
        }
    }

    if (number > 1)
        divisors[number] = 1;

    return divisors;
}


bool isDivisorOfFactorial(uint number, uint factorial, vector<uint> &primeFactors) {

    if (number <= 0)
        return false;
    
    if (factorial <= 1 && number <= factorial) 
        return true;

    Divisors numberDivisors = factorNumber(number, primeFactors);

    for (auto it = numberDivisors.begin(); it != numberDivisors.end(); it++) {
        uint primeFactor = it->first, divisorMultiplicity = it->second, factorialMultiplicity = 0;
        for (uint i = primeFactor; i <= factorial; i++) {
            factorialMultiplicity += evaluateDivisorMultiplicity(i, primeFactor);
            if (factorialMultiplicity >= divisorMultiplicity)
                break;
        }
        if (factorialMultiplicity < divisorMultiplicity)
            return false;
    }

    return true;
}


int main(void) {

    vector<uint> primeFactors = buildPrimeFactors();

    uint number, factorial;

    while (cin >> factorial >> number) {
        if (isDivisorOfFactorial(number, factorial, primeFactors))
            cout << number << " divides " << factorial << "!\n";
        else
            cout << number << " does not divide " << factorial << "!\n";
    }

    return 0;
}
