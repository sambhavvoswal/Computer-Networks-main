// RSA Algorithm in C with detailed comments

#include <stdio.h>

// Function to calculate GCD (Greatest Common Divisor)
int gcd(int a, int b) {
    // Euclidean algorithm
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the private key `d`
// such that (e * d) mod z = 1
int mod_of_d(int e, int z) {
    int d = 1;
    // Keep incrementing d until it satisfies the condition
    while ((e * d) % z != 1) 
        d++;

    return d;
}

// Modular exponentiation: (base^exp) % mod
int modPower(int base, int exp, int mod) {
    int result = 1;
    base = base % mod; // Bring base within mod range

    while (exp > 0) {
        // If exponent is odd, multiply the result
        if (exp % 2 == 1) 
            result = (result * base) % mod;

        exp = exp / 2;               // Reduce exponent by half
        base = (base * base) % mod;  // Square the base
    }
    return result;
}

int main() {
    int p, q;       // Two prime numbers
    int n, z;       // n = p * q, z = (p-1)*(q-1)
    int e, d;       // e = encryption key, d = decryption key
    int message;    // Message to encrypt
    int encrypted, decrypted;

    // Step 1: Input two prime numbers
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    // Step 2: Compute n and Euler's totient z
    n = p * q;             // Part of public key
    z = (p - 1) * (q - 1); // Totient function φ(n)

    // Step 3: Input public exponent 'e' such that gcd(e, z) = 1
    printf("Enter a value for e (1 < e < %d) such that gcd(e, %d) = 1: ", z, z);
    scanf("%d", &e);

    // Check if e is valid
    if (gcd(e, z) != 1) {
        printf("Invalid e! It must be coprime with %d.\n", z);
        return 1; // Exit if not valid
    }

    // Step 4: Compute private key 'd'
    d = mod_of_d(e, z); // d is the modular inverse of e mod z

    // Step 5: Display public and private keys
    printf("\nPublic Key: (%d, %d)", n, e);   // (n, e)
    printf("\nPrivate Key: (%d, %d)\n", n, d); // (n, d)

    // Step 6: Input message to encrypt (should be < n)
    printf("Enter message to encrypt (as integer < %d): ", n);
    scanf("%d", &message);

    // Step 7: Encrypt message using (message^e mod n)
    encrypted = modPower(message, e, n);
    printf("Encrypted message: %d\n", encrypted);

    // Step 8: Decrypt message using (encrypted^d mod n)
    decrypted = modPower(encrypted, d, n);
    printf("Decrypted message: %d\n", decrypted);

    return 0;
}
