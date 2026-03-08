#include <stdio.h>
#include <stdbool.h>

int stringLength(const char str[]);
void stringCopy(char destination[], const char source[]);
void stringConcat(char destination[], const char source[], int destinationSize);
int stringCompare(const char first[], const char second[]);
void stringReverse(char str[]);
bool isPalindromeString(const char str[]);
int countVowels(const char str[]);
int countCharacterOccurrences(const char str[], char target);
int findFirstChar(const char str[], char target);
int findSubstring(const char str[], const char pattern[]);
void removeCharacter(char str[], char target);
void toUpperCase(char str[]);
void toLowerCase(char str[]);
int countWords(const char str[]);

bool isLowercaseLetter(char character);
bool isUppercaseLetter(char character);
bool isVowel(char character);
bool isWhitespace(char character);

int main(void){
	char greeting[100] = "hello";
	char copied[100];
	char reversible[100] = "foundation";
	char removable[100] = "banana";
	char uppercaseSample[100] = "mixEd CaSe";
	char lowercaseSample[100] = "MIXED CASE";
	char spacedText[100] = "  C makes string practice useful  ";

	stringCopy(copied, "world");
	stringConcat(greeting, " there", 100);

	printf("Length: %d\n", stringLength(greeting));
	printf("Copied: %s\n", copied);
	printf("Concatenated: %s\n", greeting);
	printf("Compare apple/apple: %d\n", stringCompare("apple", "apple"));
	printf("Compare apple/apricot: %d\n", stringCompare("apple", "apricot"));

	stringReverse(reversible);
	printf("Reversed: %s\n", reversible);
	printf("Is palindrome (level): %s\n", isPalindromeString("level") ? "true" : "false");
	printf("Vowel count in education: %d\n", countVowels("education"));
	printf("Occurrences of a in banana: %d\n", countCharacterOccurrences("banana", 'a'));
	printf("First index of t in foundation: %d\n", findFirstChar("foundation", 't'));
	printf("Index of stone in foundation stone: %d\n", findSubstring("foundation stone", "stone"));

	removeCharacter(removable, 'a');
	printf("Without a: %s\n", removable);

	toUpperCase(uppercaseSample);
	toLowerCase(lowercaseSample);
	printf("Uppercase: %s\n", uppercaseSample);
	printf("Lowercase: %s\n", lowercaseSample);
	printf("Word count: %d\n", countWords(spacedText));

	return 0;
}

int stringLength(const char str[]){
	int length = 0;
	while(str[length] != '\0'){
		length++;
	}
	return length;
}

void stringCopy(char destination[], const char source[]){
	int index = 0;
	while(source[index] != '\0'){
		destination[index] = source[index];
		index++;
	}
	destination[index] = '\0';
}

void stringConcat(char destination[], const char source[], int destinationSize){
	int destinationIndex = stringLength(destination);
	int sourceIndex = 0;

	while(source[sourceIndex] != '\0' && destinationIndex < destinationSize - 1){
		destination[destinationIndex] = source[sourceIndex];
		destinationIndex++;
		sourceIndex++;
	}

	destination[destinationIndex] = '\0';
}

int stringCompare(const char first[], const char second[]){
	int index = 0;

	while(first[index] != '\0' && second[index] != '\0'){
		if(first[index] != second[index]){
			return first[index] - second[index];
		}
		index++;
	}

	return first[index] - second[index];
}

void stringReverse(char str[]){
	int left = 0;
	int right = stringLength(str) - 1;

	while(left < right){
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}

bool isPalindromeString(const char str[]){
	int left = 0;
	int right = stringLength(str) - 1;

	while(left < right){
		if(str[left] != str[right]){
			return false;
		}
		left++;
		right--;
	}

	return true;
}

int countVowels(const char str[]){
	int count = 0;

	for(int index = 0; str[index] != '\0'; index++){
		if(isVowel(str[index])){
			count++;
		}
	}

	return count;
}

int countCharacterOccurrences(const char str[], char target){
	int count = 0;

	for(int index = 0; str[index] != '\0'; index++){
		if(str[index] == target){
			count++;
		}
	}

	return count;
}

int findFirstChar(const char str[], char target){
	for(int index = 0; str[index] != '\0'; index++){
		if(str[index] == target){
			return index;
		}
	}

	return -1;
}

int findSubstring(const char str[], const char pattern[]){
	if(pattern[0] == '\0'){
		return 0;
	}

	for(int i = 0; str[i] != '\0'; i++){
		int j = 0;

		while(pattern[j] != '\0' && str[i + j] == pattern[j]){
			j++;
		}

		if(pattern[j] == '\0'){
			return i;
		}
	}

	return -1;
}

void removeCharacter(char str[], char target){
	int readIndex = 0;
	int writeIndex = 0;

	while(str[readIndex] != '\0'){
		if(str[readIndex] != target){
			str[writeIndex] = str[readIndex];
			writeIndex++;
		}
		readIndex++;
	}

	str[writeIndex] = '\0';
}

void toUpperCase(char str[]){
	for(int index = 0; str[index] != '\0'; index++){
		if(isLowercaseLetter(str[index])){
			str[index] = str[index] - ('a' - 'A');
		}
	}
}

void toLowerCase(char str[]){
	for(int index = 0; str[index] != '\0'; index++){
		if(isUppercaseLetter(str[index])){
			str[index] = str[index] + ('a' - 'A');
		}
	}
}

int countWords(const char str[]){
	int count = 0;
	bool insideWord = false;

	for(int index = 0; str[index] != '\0'; index++){
		if(str[index] == ' '){
			insideWord = false;
		} else if(!insideWord){
			count++;
			insideWord = true;
		}
	}

	return count;
}

bool isLowercaseLetter(char character){
	return character >= 'a' && character <= 'z';
}

bool isUppercaseLetter(char character){
	return character >= 'A' && character <= 'Z';
}

bool isVowel(char character){
	char normalizedCharacter = character;

	if(isUppercaseLetter(normalizedCharacter)){
		normalizedCharacter = normalizedCharacter + ('a' - 'A');
	}

	return normalizedCharacter == 'a' || normalizedCharacter == 'e' || normalizedCharacter == 'i' || normalizedCharacter == 'o' || normalizedCharacter == 'u';
}

bool isWhitespace(char character){
	return character == ' ' || character == '\n' || character == '\t';
}



bool isAnagram(char *s1, char *s2){
    // Step 1: check same length
    int i = 0;
    int j = 0;
    while(s1[i] != '\0') i++;
    while(s2[j] != '\0') j++;
    if(i != j) return false;

    // Step 2: for every character in s1, count how many times
    // it appears in s1 vs s2 — they must match
    for(int k = 0; s1[k] != '\0'; k++){
        char target = s1[k];
        int count1 = 0;
        int count2 = 0;

        for(int m = 0; s1[m] != '\0'; m++){
            if(s1[m] == target) count1++;
        }
        for(int m = 0; s2[m] != '\0'; m++){
            if(s2[m] == target) count2++;
        }

        if(count1 != count2) return false;
    }

    return true;
}
