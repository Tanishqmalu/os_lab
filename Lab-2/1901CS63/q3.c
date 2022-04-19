#include <stdio.h>

// Function to find xor of two numbers
long long XOR(long long num1, long long num2) {
    long long result = 0, power = 1;
    
    // Xoring the number bit by bit
    while (num1 != 0 || num2 != 0) {
    	
    	// A XOR B = (((NOT)A)*B) + (A*((NOT)B))
        int xorOfLSB = (num1 % 2) * !(num2 % 2) + !(num1 % 2) * (num2 % 2);
        
        //Update the result
        result += xorOfLSB * power;
        
        num1 /= 2;
        num2 /= 2;
        power *= 2;
    }
    return result;
}

// Main function
int main(int argc, char* argv[]) {
    // Argument count should be exactly 3.
    if (argc != 3) printf("Error: Please enter only 2 integers as arguments.");
    else {
        long long num1, num2;
        sscanf(argv[1], "%lld", &num1);
        sscanf(argv[2], "%lld", &num2);
        
        printf("Xor of %lld and %lld = %lld",num1,num2,XOR(num1, num2));
    }
}
