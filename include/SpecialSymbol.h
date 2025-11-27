#include <stdlib.h>
#include <iostream>

/**
 * @brief The following file defines special symbols used in the lexical analyzer.
 * These symbols include representations for the end of input, epsilon transitions,
 * error states, and specific grammar symbols like parentheses and operators.
 */

const char END = (char)0;
const char EPSILON = (char)5;
const int ERROR = 2000;
const int SKIP = 2001;
const int PC = 10;
const int ARROW = 20;
const int OR = 30;
const int SYMBOL = 40;

