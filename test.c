#include <stdio.h>    // printf
#include <stdbool.h>  // to define a boolean type and true, false
#include <string.h>   // strcpy  to copy a string
#include <assert.h>

// Declaration of function from hasUniqueChars.c
bool hasUniqueChars(char *inputStr);

int main() {
    // ------------------------------------------------------------
    // Examples of declaring string constants
    /* Example 1 */
    char string1[] = "A string declared as an array.\n";

    /* Example 2 */
    char *string2 = "A string declared as a pointer.\n";

    /* Example 3 */
    char string3[128];   // can copy in up to 127 characters
                         // chose 128 because it is a multiple of 8 bytes
    strcpy(string3, "A string constant copied in.\n");

    // You can uncomment these to see how the strings were initialized above.
    // Then you can comment these out again once you see that the 
    // strings were created correctly
    // printf ("%s", string1);
    // printf ("%s", string2);
    // printf ("%s", string3);

    // -------------------------------------------------------------
    // Thorough and exhaustive tests of hasUniqueChars()  
    bool ok;    // holds the result of hasUniqueChars(); used in asserts

    // Test 1: This test should fail as it contains repeating characters.
    strcpy(string3, "Character duplication is present here (l, s, i, h).");
    ok = hasUniqueChars(string3);
    assert(!(ok)); // Expecting false

    // Test 2: This string contains unique characters and should pass.
    strcpy(string3, " abcdefghij.");
    ok = hasUniqueChars(string3);
    assert(ok); // Expecting true

    // Test 3: This should fail due to repeated special symbols.
    strcpy(string3, "Repeated symbols: ^*$^&*^.");
    ok = hasUniqueChars(string3);
    assert(!(ok)); // Expecting false

    // Test 4: This string has duplicates among numbers.
    strcpy(string3, "The number series 54321 repeats the 2 and 3.");
    ok = hasUniqueChars(string3);
    assert(!(ok)); // Expecting false

    // Test 5: This string should pass since all characters are distinct.
    strcpy(string3, "Unique name: harethrobleh.");
    ok = hasUniqueChars(string3);
    assert(ok); // Expecting true

    // Test 6: This contains both duplicate letters and special characters, so it should fail.
    strcpy(string3, "Check this mix: LH978gyb(*t7&gi*Igt68) for duplicates.");
    ok = hasUniqueChars(string3);
    assert(!(ok)); // Expecting false

    // Test 7: This string should trigger an error due to a newline character.
    strcpy(string3, "There are invalid characters here: a b cc\n");
    ok = hasUniqueChars(string3);
    // Invalid character check should cause the program to exit

    return 0;
}
