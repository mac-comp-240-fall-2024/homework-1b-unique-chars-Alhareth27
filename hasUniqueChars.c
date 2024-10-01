/*
 * hasUniqueChars.c
 * 
 * TODO: replace this line with lines containing a description
 * 
 * Author: 
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  // Use ulong_to_bin_str to convert unsigned long to binary string
  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
}

/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}

/*
 * This function checks if a given input string contains all unique characters.
 * It returns true if all characters are unique, and false if there are duplicates.
 * It first checks for invalid characters and exits with an error if found.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  // unsigned long can handle 64 different chars in a string
  // if a bit at a position is 1, then we have seen that character
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp = 0;  // for checking ! through @ 

  char nextChar;         // next character in string to check

  // -------------------------------------------------------------
  // Debugging values initialization
  char debug_str_A_z[128];
  strcpy(debug_str_A_z, "checkBitsA_z before: \n");
  seeBits(checkBitsA_z, debug_str_A_z);
  
  char debug_str_excl_amp[128];
  strcpy(debug_str_excl_amp, "checkBitsexcl_amp before: \n");
  seeBits(checkBitsexcl_amp, debug_str_excl_amp);
  // -------------------------------------------------------------

  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];
    unsigned long index;
    unsigned long mask;

    // Skip space character
    if (nextChar == 32) {
      continue;
    }
    // Check if nextChar is between A-Z
    else if ((nextChar >= 65) && (nextChar <= 90)) {
      index = nextChar - 65;
      mask = 1l << index;
      if (mask & checkBitsA_z) {
        return false;  // duplicate found
      } else {
        checkBitsA_z |= mask; // mark this character as seen
      }
    }
    // Check if nextChar is between a-z
    else if ((nextChar >= 97) && (nextChar <= 122)) {
      index = nextChar - 97 + 26;
      mask = 1l << index;
      if (mask & checkBitsA_z) {
        return false;  // duplicate found
      } else {
        checkBitsA_z |= mask; // mark this character as seen
      }
    }
    // Check if nextChar is a special character
    else if (nextChar >= 33 && nextChar <= 64) {
      index = nextChar - 33;
      mask = 1l << index;
      if (checkBitsexcl_amp & mask) {
        return false;  // duplicate found
      } else {
        checkBitsexcl_amp |= mask; // mark this character as seen
      }
    }
    
    // -------------------------------------------------------------
    // Debugging print statements
    printf("nextchar int value: %d\n", nextChar);
    char char_str[2] = "\0";
    char_str[0] = nextChar;
    strcpy(debug_str_A_z, "nextchar: ");
    strcat(debug_str_A_z, char_str);
    strcat(debug_str_A_z, ", checkBitsA_z: \n");
    seeBits(checkBitsA_z, debug_str_A_z);
    // ------------------------------------------------------------- 
  }

  // if through all the characters, then no duplicates found
  return true;
}