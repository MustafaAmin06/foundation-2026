/*
 * ============================================================================
 *                  MASSIVE STRINGS IN C COMPILATION
 * ============================================================================
 *
 * This file is a comprehensive guide to strings in C. It covers:
 *
 *   SECTION 1: Char Array Fundamentals
 *              - Declaration and initialization
 *              - The null terminator '\0'
 *              - Array vs pointer notation
 *              - Pointer arithmetic with strings
 *              - String literals and memory layout
 *
 *   SECTION 2: Key Standard Library Functions
 *              - strlen   (get length of string)
 *              - strcpy   (copy one string to another)
 *              - strncpy  (bounded copy)
 *              - fgets    (safe line input from stdin/files)
 *
 *   SECTION 3: Strings with printf and scanf
 *              - printf format specifiers for strings
 *              - scanf pitfalls and proper usage
 *              - Mixing scanf and fgets
 *
 *   SECTION 4: Easy String Problems
 *   SECTION 5: Medium String Problems
 *   SECTION 6: Hard String Problems
 *
 * ============================================================================
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/* ============================================================================
 *  SECTION 1: CHAR ARRAY FUNDAMENTALS
 * ============================================================================
 *
 *  In C there is no built-in "string" type. A string is simply a contiguous
 *  sequence of characters (a char array) terminated by the null character '\0'.
 *
 *  ---- Declaration and Initialization ----
 *
 *  There are several ways to create a string:
 *
 *      char name[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
 *          - Manually fills each element; YOU must include '\0'.
 *
 *      char name[6] = "Hello";
 *          - The compiler appends '\0' automatically.
 *          - The array size (6) must be at least strlen("Hello") + 1.
 *
 *      char name[] = "Hello";
 *          - The compiler sizes the array to exactly 6 (5 chars + '\0').
 *
 *      char *name = "Hello";
 *          - name is a POINTER that points to a string literal stored in
 *            read-only memory. You CANNOT modify the characters through
 *            this pointer (undefined behavior).
 *
 *  ---- The Null Terminator '\0' ----
 *
 *  Every C string function depends on '\0' to know where the string ends.
 *  If you forget '\0', functions like printf("%s", ...) or strlen() will
 *  keep reading past the array into garbage memory until they happen to
 *  find a zero byte. This is a classic source of bugs and security holes.
 *
 *  Memory layout of char greeting[10] = "Hey";
 *
 *      Index:    0    1    2    3    4    5    6    7    8    9
 *      Value:   'H'  'e'  'y'  '\0'  ?    ?    ?    ?    ?    ?
 *
 *  Indices 4-9 are uninitialized (or zero-initialized if the array is global
 *  or static). Only indices 0-2 hold our characters; index 3 holds '\0'.
 *
 *  ---- Array / Pointer Duality ----
 *
 *  In C, when you use an array name in most expressions it "decays" into a
 *  pointer to its first element:
 *
 *      char msg[] = "Hello";
 *      char *p = msg;           // p points to msg[0], which is 'H'
 *
 *  After this, the following are equivalent:
 *
 *      msg[2]    is the same as  *(msg + 2)    => 'l'
 *      p[2]      is the same as  *(p + 2)      => 'l'
 *
 *  Key differences:
 *      - sizeof(msg) == 6   (full array size including '\0')
 *      - sizeof(p)   == 8   (size of a pointer on 64-bit systems)
 *      - msg is NOT reassignable (msg = other is illegal)
 *      - p IS reassignable (p = other is fine)
 *
 *  ---- Pointer Arithmetic ----
 *
 *  Since a pointer to char holds an address, adding 1 moves it forward by
 *  sizeof(char) == 1 byte — i.e., to the next character:
 *
 *      char word[] = "Code";
 *      char *ptr = word;       // ptr -> 'C'
 *      ptr++;                  // ptr -> 'o'
 *      ptr++;                  // ptr -> 'd'
 *      printf("%c\n", *ptr);   // prints 'd'
 *
 *  You can walk an entire string with a pointer:
 *
 *      char *p = word;
 *      while (*p != '\0') {
 *          printf("%c ", *p);
 *          p++;
 *      }
 *      // Output: C o d e
 *
 *  ---- String Literals and Memory ----
 *
 *  A string literal like "Hello" lives in a read-only section of memory.
 *
 *      char arr[] = "Hello";   // COPIES literal into arr on the stack.
 *                               // arr is modifiable.
 *      char *ptr  = "Hello";   // ptr points directly at the literal.
 *                               // Modifying *ptr is UNDEFINED BEHAVIOR.
 *
 *  Rule of thumb: if you need to modify the string, use an array.
 *  If you only need to read it, a pointer to a literal is fine.
 */


/* ============================================================================
 *  SECTION 2: KEY STANDARD LIBRARY FUNCTIONS
 * ============================================================================
 *
 *  All of these live in <string.h> (except fgets which is in <stdio.h>).
 *
 *  ---- strlen ----
 *
 *  size_t strlen(const char *s);
 *
 *  Returns the number of characters BEFORE the null terminator.
 *
 *      strlen("Hello")  => 5
 *      strlen("")        => 0
 *
 *  It does NOT count '\0'. It walks the array from the beginning until it
 *  hits '\0', so it runs in O(n) time. Calling strlen in a loop condition
 *  like  for (i = 0; i < strlen(s); i++)  recalculates the length every
 *  iteration — store it in a variable first.
 *
 *  ---- strcpy ----
 *
 *  char *strcpy(char *dest, const char *src);
 *
 *  Copies the string pointed to by src (including '\0') into dest.
 *  Returns dest.
 *
 *      char buf[20];
 *      strcpy(buf, "Hello");   // buf is now "Hello\0............"
 *
 *  WARNING: strcpy does NOT check bounds. If src is longer than dest can
 *  hold, it writes past the end of dest — a buffer overflow. This is one
 *  of the most common security vulnerabilities in C code.
 *
 *  ---- strncpy ----
 *
 *  char *strncpy(char *dest, const char *src, size_t n);
 *
 *  Copies at most n characters from src into dest.
 *    - If strlen(src) < n, the remaining bytes in dest are filled with '\0'.
 *    - If strlen(src) >= n, dest is NOT null-terminated!
 *
 *      char buf[6];
 *      strncpy(buf, "Hello, World!", 5);
 *      buf[5] = '\0';   // MUST manually null-terminate!
 *
 *  strncpy is safer than strcpy because it limits how many bytes are written,
 *  but you must always ensure the result is null-terminated.
 *
 *  ---- fgets ----
 *
 *  char *fgets(char *s, int n, FILE *stream);
 *
 *  Reads at most n-1 characters from stream into s, then appends '\0'.
 *  Stops early at a newline (which IS stored in s) or EOF.
 *  Returns s on success, NULL on failure or EOF with no chars read.
 *
 *      char line[100];
 *      fgets(line, 100, stdin);
 *      // If the user types "Hey\n", line contains "Hey\n\0"
 *
 *  fgets is the PREFERRED way to read a line of input because:
 *    1. It limits how many characters are read (prevents overflow).
 *    2. It reads spaces (unlike scanf("%s", ...)).
 *    3. It always null-terminates the result.
 *
 *  The trailing '\n' can be stripped:
 *      line[strcspn(line, "\n")] = '\0';
 */


/* ============================================================================
 *  SECTION 3: STRINGS WITH printf AND scanf
 * ============================================================================
 *
 *  ---- printf ----
 *
 *  %s   prints characters until '\0' is found.
 *
 *      char name[] = "Alice";
 *      printf("%s\n", name);           // Alice
 *      printf("%.3s\n", name);         // Ali       (print at most 3 chars)
 *      printf("%10s\n", name);         //      Alice (right-justified, width 10)
 *      printf("%-10s|\n", name);       // Alice     | (left-justified, width 10)
 *
 *  %c   prints a single character.
 *
 *      printf("%c\n", name[0]);        // A
 *
 *  ---- scanf ----
 *
 *  scanf("%s", buf) reads a single "word" — it stops at the first whitespace
 *  character and does NOT read spaces. It also has no built-in length limit,
 *  making it just as dangerous as gets().
 *
 *      char word[20];
 *      scanf("%s", word);
 *      // If user types "Hello World", word contains "Hello" and
 *      // " World" remains in the input buffer.
 *
 *  To limit input length, use a width specifier:
 *
 *      scanf("%19s", word);   // reads at most 19 chars + '\0' = 20 bytes
 *
 *  To read a full line with scanf (including spaces), use %[^\n]:
 *
 *      scanf(" %[^\n]", line);
 *      // The leading space skips any leftover whitespace/newlines.
 *
 *  ---- Mixing scanf and fgets ----
 *
 *  A common bug: after scanf("%d", &n), a '\n' remains in stdin.
 *  If you then call fgets(), it reads that leftover '\n' as an empty line.
 *
 *  Fix: consume the newline after scanf:
 *
 *      scanf("%d", &n);
 *      getchar();               // eat the trailing '\n'
 *      fgets(line, 100, stdin); // now reads the next real line
 *
 *  Or use scanf(" %[^\n]") with the leading space to skip whitespace.
 */


/* ============================================================================
 *  DEMONSTRATIONS: strlen, strcpy, strncpy, fgets, printf, scanf
 * ============================================================================ */

void demonstrateStrlen(void);
void demonstrateStrcpy(void);
void demonstrateStrncpy(void);
void demonstrateFgets(void);
void demonstratePrintfFormats(void);

/* ============================================================================
 *  SECTION 4 - EASY PROBLEMS: Forward Declarations
 * ============================================================================ */

int manualStrlen(const char str[]);
void manualStrcpy(char dest[], const char src[]);
void reverseString(char str[]);
int countVowels(const char str[]);
bool isPalindrome(const char str[]);
void toUpperCase(char str[]);

/* ============================================================================
 *  SECTION 5 - MEDIUM PROBLEMS: Forward Declarations
 * ============================================================================ */

bool isAnagram(const char s1[], const char s2[]);
int firstNonRepeatingChar(const char str[]);
void removeAllSpaces(char str[]);
void reverseWords(char str[]);
int longestWordLength(const char str[]);
void compressString(const char input[], char output[], int outputSize);

/* ============================================================================
 *  SECTION 6 - HARD PROBLEMS: Forward Declarations
 * ============================================================================ */

int longestSubstringWithoutRepeat(const char str[]);
void longestPalindromicSubstring(const char str[], char result[], int resultSize);
bool isInterleaved(const char s1[], const char s2[], const char s3[]);


/* ============================================================================
 *  MAIN — runs every demonstration and problem
 * ============================================================================ */

int main(void){
	printf("============================================================\n");
	printf("  SECTION 1-3: DEMONSTRATIONS\n");
	printf("============================================================\n\n");

	demonstrateStrlen();
	demonstrateStrcpy();
	demonstrateStrncpy();
	demonstratePrintfFormats();
	// demonstrateFgets(); // uncomment to test interactive fgets input

	printf("\n============================================================\n");
	printf("  SECTION 4: EASY PROBLEMS\n");
	printf("============================================================\n\n");

	// Problem 1: Manual strlen
	printf("--- manualStrlen ---\n");
	printf("Length of \"foundation\": %d\n", manualStrlen("foundation"));
	printf("Length of \"\": %d\n\n", manualStrlen(""));

	// Problem 2: Manual strcpy
	printf("--- manualStrcpy ---\n");
	char copied[50];
	manualStrcpy(copied, "Hello, C!");
	printf("Copied string: %s\n\n", copied);

	// Problem 3: Reverse a string in-place
	printf("--- reverseString ---\n");
	char rev1[] = "abcdef";
	reverseString(rev1);
	printf("Reversed \"abcdef\": %s\n", rev1);
	char rev2[] = "a";
	reverseString(rev2);
	printf("Reversed \"a\": %s\n\n", rev2);

	// Problem 4: Count vowels
	printf("--- countVowels ---\n");
	printf("Vowels in \"Education\": %d\n", countVowels("Education"));
	printf("Vowels in \"xyz\": %d\n\n", countVowels("xyz"));

	// Problem 5: Palindrome check
	printf("--- isPalindrome ---\n");
	printf("\"racecar\" palindrome? %s\n", isPalindrome("racecar") ? "true" : "false");
	printf("\"hello\" palindrome? %s\n", isPalindrome("hello") ? "true" : "false");
	printf("\"a\" palindrome? %s\n\n", isPalindrome("a") ? "true" : "false");

	// Problem 6: To uppercase
	printf("--- toUpperCase ---\n");
	char upper[] = "mixEd CaSe 123";
	toUpperCase(upper);
	printf("Uppercased: %s\n\n", upper);

	printf("============================================================\n");
	printf("  SECTION 5: MEDIUM PROBLEMS\n");
	printf("============================================================\n\n");

	// Problem 7: Anagram check
	printf("--- isAnagram ---\n");
	printf("\"listen\" & \"silent\": %s\n", isAnagram("listen", "silent") ? "true" : "false");
	printf("\"hello\" & \"world\": %s\n\n", isAnagram("hello", "world") ? "true" : "false");

	// Problem 8: First non-repeating character
	printf("--- firstNonRepeatingChar ---\n");
	printf("In \"aabbcdd\": index %d\n", firstNonRepeatingChar("aabbcdd"));
	printf("In \"aabb\": index %d\n\n", firstNonRepeatingChar("aabb"));

	// Problem 9: Remove all spaces
	printf("--- removeAllSpaces ---\n");
	char spacy[] = "  H e l l o  W o r l d  ";
	removeAllSpaces(spacy);
	printf("Without spaces: \"%s\"\n\n", spacy);

	// Problem 10: Reverse words in a sentence
	printf("--- reverseWords ---\n");
	char sentence[] = "the sky is blue";
	reverseWords(sentence);
	printf("Reversed words: \"%s\"\n\n", sentence);

	// Problem 11: Longest word length
	printf("--- longestWordLength ---\n");
	printf("In \"I love programming in C\": %d\n", longestWordLength("I love programming in C"));
	printf("In \"hi\": %d\n\n", longestWordLength("hi"));

	// Problem 12: Run-length compression
	printf("--- compressString ---\n");
	char compressed[100];
	compressString("aaabbbccdd", compressed, 100);
	printf("Compressed \"aaabbbccdd\": %s\n", compressed);
	compressString("abcd", compressed, 100);
	printf("Compressed \"abcd\": %s\n\n", compressed);

	printf("============================================================\n");
	printf("  SECTION 6: HARD PROBLEMS\n");
	printf("============================================================\n\n");

	// Problem 13: Longest substring without repeating characters
	printf("--- longestSubstringWithoutRepeat ---\n");
	printf("\"abcabcbb\": %d\n", longestSubstringWithoutRepeat("abcabcbb"));
	printf("\"bbbbb\": %d\n", longestSubstringWithoutRepeat("bbbbb"));
	printf("\"pwwkew\": %d\n\n", longestSubstringWithoutRepeat("pwwkew"));

	// Problem 14: Longest palindromic substring
	printf("--- longestPalindromicSubstring ---\n");
	char palResult[100];
	longestPalindromicSubstring("babad", palResult, 100);
	printf("In \"babad\": \"%s\"\n", palResult);
	longestPalindromicSubstring("cbbd", palResult, 100);
	printf("In \"cbbd\": \"%s\"\n", palResult);
	longestPalindromicSubstring("a", palResult, 100);
	printf("In \"a\": \"%s\"\n\n", palResult);

	// Problem 15: Interleaving strings
	printf("--- isInterleaved ---\n");
	printf("\"aab\",\"axy\",\"aaxaby\": %s\n",
		isInterleaved("aab", "axy", "aaxaby") ? "true" : "false");
	printf("\"abc\",\"def\",\"adbecf\": %s\n",
		isInterleaved("abc", "def", "adbecf") ? "true" : "false");
	printf("\"abc\",\"def\",\"abcfed\": %s\n",
		isInterleaved("abc", "def", "abcfed") ? "true" : "false");

	return 0;
}


/* ============================================================================
 *  DEMONSTRATIONS
 * ============================================================================ */

void demonstrateStrlen(void){
	printf("--- strlen ---\n");

	char greeting[] = "Hello";
	printf("strlen(\"%s\") = %lu\n", greeting, (unsigned long)strlen(greeting));

	char empty[] = "";
	printf("strlen(\"%s\") = %lu\n", empty, (unsigned long)strlen(empty));

	// Showing that strlen does not count '\0'
	char buf[20] = "Hi";
	printf("strlen(buf) = %lu, sizeof(buf) = %lu\n\n",
		(unsigned long)strlen(buf), (unsigned long)sizeof(buf));
}

void demonstrateStrcpy(void){
	printf("--- strcpy ---\n");

	char source[] = "Foundation";
	char dest[20];
	strcpy(dest, source);
	printf("strcpy result: \"%s\"\n", dest);

	// Overwriting dest with a shorter string
	strcpy(dest, "Hi");
	printf("After overwrite: \"%s\"\n\n", dest);
}

void demonstrateStrncpy(void){
	printf("--- strncpy ---\n");

	char source[] = "Hello, World!";
	char dest[6];

	// Copy at most 5 characters, then manually null-terminate
	strncpy(dest, source, 5);
	dest[5] = '\0';
	printf("strncpy first 5 chars: \"%s\"\n", dest);

	// When source is shorter than n, rest is padded with '\0'
	char padded[20];
	strncpy(padded, "Hi", 19);
	padded[19] = '\0';
	printf("strncpy with padding: \"%s\" (strlen=%lu)\n\n",
		padded, (unsigned long)strlen(padded));
}

void demonstrateFgets(void){
	/*
	 * Uncomment the call to this function in main() to test it
	 * interactively. fgets reads a full line including spaces.
	 */
	printf("--- fgets ---\n");
	printf("Type a line of text: ");

	char line[100];
	if(fgets(line, 100, stdin) != NULL){
		// Remove the trailing newline if present
		line[strcspn(line, "\n")] = '\0';
		printf("You entered: \"%s\"\n", line);
		printf("Length: %lu\n\n", (unsigned long)strlen(line));
	}
}

void demonstratePrintfFormats(void){
	printf("--- printf format specifiers for strings ---\n");

	char name[] = "Alice";

	printf("%%s      : [%s]\n", name);
	printf("%%.3s    : [%.3s]\n", name);
	printf("%%10s    : [%10s]\n", name);
	printf("%%-10s   : [%-10s]\n", name);
	printf("%%10.3s  : [%10.3s]\n\n", name);
}


/* ============================================================================
 *  SECTION 4: EASY PROBLEMS
 * ============================================================================ */

/*
 * Problem 1: Manual strlen
 *
 * Implement strlen from scratch. Walk the array until '\0' and count
 * the characters.
 *
 * Approach: Simple loop that increments a counter.
 * Time: O(n)   Space: O(1)
 */
int manualStrlen(const char str[]){
	int length = 0;
	while(str[length] != '\0'){
		length++;
	}
	return length;
}

/*
 * Problem 2: Manual strcpy
 *
 * Copy every character from src into dest, including the null terminator.
 *
 * Approach: Index through src, copy each byte, then place '\0'.
 * Time: O(n)   Space: O(1)
 */
void manualStrcpy(char dest[], const char src[]){
	int i = 0;
	while(src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

/*
 * Problem 3: Reverse a string in-place
 *
 * Use two pointers — one at the start, one at the end — and swap
 * characters moving inward.
 *
 * Time: O(n)   Space: O(1)
 */
void reverseString(char str[]){
	int left = 0;
	int right = manualStrlen(str) - 1;

	while(left < right){
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}

/*
 * Problem 4: Count vowels in a string
 *
 * Iterate through every character and check if it is a, e, i, o, or u
 * (case-insensitive).
 *
 * Time: O(n)   Space: O(1)
 */
int countVowels(const char str[]){
	int count = 0;
	for(int i = 0; str[i] != '\0'; i++){
		char c = str[i];
		if(c >= 'A' && c <= 'Z'){
			c = c + ('a' - 'A');
		}
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
			count++;
		}
	}
	return count;
}

/*
 * Problem 5: Check if a string is a palindrome
 *
 * Compare characters from both ends moving toward the center.
 *
 * Time: O(n)   Space: O(1)
 */
bool isPalindrome(const char str[]){
	int left = 0;
	int right = manualStrlen(str) - 1;

	while(left < right){
		if(str[left] != str[right]){
			return false;
		}
		left++;
		right--;
	}
	return true;
}

/*
 * Problem 6: Convert a string to uppercase in-place
 *
 * For each character, if it is a lowercase letter (between 'a' and 'z'),
 * subtract the offset ('a' - 'A') to get the uppercase equivalent.
 *
 * Time: O(n)   Space: O(1)
 */
void toUpperCase(char str[]){
	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] >= 'a' && str[i] <= 'z'){
			str[i] = str[i] - ('a' - 'A');
		}
	}
}


/* ============================================================================
 *  SECTION 5: MEDIUM PROBLEMS
 * ============================================================================ */

/*
 * Problem 7: Check if two strings are anagrams
 *
 * Two strings are anagrams if they contain the exact same characters
 * with the same frequencies. Use a frequency count array of size 128
 * (one slot per ASCII value). Increment for s1, decrement for s2,
 * then verify all counts are zero.
 *
 * Time: O(n)   Space: O(1) — fixed 128-element array
 */
bool isAnagram(const char s1[], const char s2[]){
	int freq[128] = {0};

	for(int i = 0; s1[i] != '\0'; i++){
		freq[(unsigned char)s1[i]]++;
	}
	for(int i = 0; s2[i] != '\0'; i++){
		freq[(unsigned char)s2[i]]--;
	}
	for(int i = 0; i < 128; i++){
		if(freq[i] != 0){
			return false;
		}
	}
	return true;
}

/*
 * Problem 8: First non-repeating character
 *
 * Return the index of the first character that appears exactly once.
 * Return -1 if all characters repeat.
 *
 * Approach: Build a frequency array, then scan the string again to
 * find the first character with count == 1.
 *
 * Time: O(n)   Space: O(1) — fixed 128-element array
 */
int firstNonRepeatingChar(const char str[]){
	int freq[128] = {0};

	for(int i = 0; str[i] != '\0'; i++){
		freq[(unsigned char)str[i]]++;
	}
	for(int i = 0; str[i] != '\0'; i++){
		if(freq[(unsigned char)str[i]] == 1){
			return i;
		}
	}
	return -1;
}

/*
 * Problem 9: Remove all spaces from a string in-place
 *
 * Use a read/write pointer pattern. Walk through the string; whenever
 * we see a non-space character, write it to the write position.
 *
 * Time: O(n)   Space: O(1)
 */
void removeAllSpaces(char str[]){
	int read = 0;
	int write = 0;

	while(str[read] != '\0'){
		if(str[read] != ' '){
			str[write] = str[read];
			write++;
		}
		read++;
	}
	str[write] = '\0';
}

/*
 * Problem 10: Reverse the order of words in a sentence
 *
 * "the sky is blue" => "blue is sky the"
 *
 * Approach (in-place, O(1) extra space):
 *   1. Reverse the entire string:           "eulb si yks eht"
 *   2. Reverse each individual word back:   "blue is sky the"
 *
 * Time: O(n)   Space: O(1)
 */
static void reverseRange(char str[], int left, int right){
	while(left < right){
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}

void reverseWords(char str[]){
	int len = manualStrlen(str);

	// Step 1: Reverse the whole string
	reverseRange(str, 0, len - 1);

	// Step 2: Reverse each word
	int start = 0;
	for(int i = 0; i <= len; i++){
		if(str[i] == ' ' || str[i] == '\0'){
			reverseRange(str, start, i - 1);
			start = i + 1;
		}
	}
}

/*
 * Problem 11: Length of the longest word in a string
 *
 * Walk through the string tracking the current word length.
 * When we hit a space or '\0', compare with the running max.
 *
 * Time: O(n)   Space: O(1)
 */
int longestWordLength(const char str[]){
	int maxLen = 0;
	int currentLen = 0;

	for(int i = 0; str[i] != '\0'; i++){
		if(str[i] == ' '){
			if(currentLen > maxLen){
				maxLen = currentLen;
			}
			currentLen = 0;
		} else {
			currentLen++;
		}
	}
	// Check the last word
	if(currentLen > maxLen){
		maxLen = currentLen;
	}
	return maxLen;
}

/*
 * Problem 12: Run-length encoding (string compression)
 *
 * "aaabbbccdd" => "a3b3c2d2"
 * "abcd"       => "a1b1c1d1"
 *
 * Walk the string counting consecutive identical characters.
 * Write each character followed by its count into the output buffer.
 *
 * Time: O(n)   Space: O(n)
 */
void compressString(const char input[], char output[], int outputSize){
	int write = 0;
	int i = 0;

	while(input[i] != '\0' && write < outputSize - 1){
		char current = input[i];
		int count = 0;

		while(input[i] == current){
			count++;
			i++;
		}

		// Write the character
		if(write < outputSize - 1){
			output[write++] = current;
		}

		// Write the count (handle multi-digit numbers)
		char countBuf[12];
		int digits = 0;
		int tmp = count;
		do {
			countBuf[digits++] = '0' + (tmp % 10);
			tmp /= 10;
		} while(tmp > 0);

		// countBuf is reversed, so write digits backwards
		for(int d = digits - 1; d >= 0 && write < outputSize - 1; d--){
			output[write++] = countBuf[d];
		}
	}
	output[write] = '\0';
}


/* ============================================================================
 *  SECTION 6: HARD PROBLEMS
 * ============================================================================ */

/*
 * Problem 13: Longest substring without repeating characters
 *
 * Given a string, find the length of the longest substring that contains
 * no duplicate characters.
 *
 * "abcabcbb" => 3 ("abc")
 * "bbbbb"    => 1 ("b")
 * "pwwkew"   => 3 ("wke")
 *
 * Approach: Sliding window with a "last seen index" array.
 *   - Maintain a window [start, i].
 *   - For each character, if it was last seen at index >= start,
 *     move start past its last occurrence.
 *   - Update the answer with the window size.
 *
 * Time: O(n)   Space: O(1) — fixed 128-element array
 */
int longestSubstringWithoutRepeat(const char str[]){
	int lastSeen[128];
	for(int i = 0; i < 128; i++){
		lastSeen[i] = -1;
	}

	int maxLen = 0;
	int start = 0;

	for(int i = 0; str[i] != '\0'; i++){
		unsigned char c = (unsigned char)str[i];
		if(lastSeen[c] >= start){
			start = lastSeen[c] + 1;
		}
		lastSeen[c] = i;

		int windowLen = i - start + 1;
		if(windowLen > maxLen){
			maxLen = windowLen;
		}
	}

	return maxLen;
}

/*
 * Problem 14: Longest palindromic substring
 *
 * Given a string, find the longest substring that is a palindrome.
 *
 * "babad" => "bab" (or "aba")
 * "cbbd"  => "bb"
 *
 * Approach: Expand around center. For each index i, try expanding
 * outward from (i, i) for odd-length palindromes and (i, i+1) for
 * even-length palindromes. Track the longest found.
 *
 * Time: O(n^2)   Space: O(1) — result is written to caller's buffer
 */
static void expandAroundCenter(const char str[], int left, int right,
		int *bestStart, int *bestLen){
	int len = manualStrlen(str);
	while(left >= 0 && right < len && str[left] == str[right]){
		left--;
		right++;
	}
	// After the loop, the palindrome is str[left+1 .. right-1]
	int palLen = right - left - 1;
	if(palLen > *bestLen){
		*bestLen = palLen;
		*bestStart = left + 1;
	}
}

void longestPalindromicSubstring(const char str[], char result[], int resultSize){
	int len = manualStrlen(str);
	if(len == 0){
		result[0] = '\0';
		return;
	}

	int bestStart = 0;
	int bestLen = 1;

	for(int i = 0; i < len; i++){
		// Odd-length palindromes centered at i
		expandAroundCenter(str, i, i, &bestStart, &bestLen);
		// Even-length palindromes centered between i and i+1
		expandAroundCenter(str, i, i + 1, &bestStart, &bestLen);
	}

	// Copy the result
	int copyLen = bestLen;
	if(copyLen >= resultSize){
		copyLen = resultSize - 1;
	}
	for(int i = 0; i < copyLen; i++){
		result[i] = str[bestStart + i];
	}
	result[copyLen] = '\0';
}

/*
 * Problem 15: Interleaving strings
 *
 * Given three strings s1, s2, s3, determine whether s3 is formed by
 * interleaving s1 and s2. An interleaving preserves the left-to-right
 * order of characters within each string.
 *
 * "aab", "axy", "aaxaby" => true
 *   a a x a b y
 *   ^       ^     from s1 (a, a, b)
 *     ^ ^   ^ ^   from s2 (a, x, y)
 *   Wait — let's trace: a(s1) a(s2) x(s2) a(s1) b(s1) y(s2) ✓
 *
 * Approach: Dynamic programming with a 2D boolean table.
 *   dp[i][j] = true if s3[0..i+j-1] can be formed by interleaving
 *              s1[0..i-1] and s2[0..j-1].
 *
 * Base case: dp[0][0] = true
 * Transition:
 *   dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1])
 *           || (dp[i][j-1] && s2[j-1] == s3[i+j-1])
 *
 * Time: O(m * n) where m = len(s1), n = len(s2)
 * Space: O(m * n)
 */
bool isInterleaved(const char s1[], const char s2[], const char s3[]){
	int len1 = manualStrlen(s1);
	int len2 = manualStrlen(s2);
	int len3 = manualStrlen(s3);

	if(len1 + len2 != len3){
		return false;
	}

	// Use a VLA for the DP table (fine for moderate input sizes)
	bool dp[len1 + 1][len2 + 1];

	// Initialize all to false
	for(int i = 0; i <= len1; i++){
		for(int j = 0; j <= len2; j++){
			dp[i][j] = false;
		}
	}

	dp[0][0] = true;

	// Fill first row: only using characters from s2
	for(int j = 1; j <= len2; j++){
		dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
	}

	// Fill first column: only using characters from s1
	for(int i = 1; i <= len1; i++){
		dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
	}

	// Fill the rest
	for(int i = 1; i <= len1; i++){
		for(int j = 1; j <= len2; j++){
			dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1])
				|| (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
		}
	}

	return dp[len1][len2];
}
