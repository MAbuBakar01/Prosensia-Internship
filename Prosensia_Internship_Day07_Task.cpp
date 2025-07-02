//Muhammad Abu Bakar ProsenSia Internship Day # 07 task
#include <iostream>
#include <string>
using namespace std;

string reverseString(string str) {
    string result = "";
    for (int i=str.length()-1; i>=0; i--)
	 {
        result+=str[i];
    }
    return result;
}
bool isPalindrome(string str) {
    int start=0;
    int end=str.length()-1;
    while (start<end) {
        if (str[start]!= str[end]) {
            return false;
        }
        start++;
        end--;
    }   return true;
}
int countVowels(string str) {
    string vowels = "aeiou";
    int total=0;
    char last = ' ';
    for (int i=0; i<str.length(); i++) {
        char ch=str[i];
        bool isVowel=false;
        for (int j=0; j<vowels.length(); j++) {
            if(ch==vowels[j]) {
                isVowel = true;
                break;    } }
        if(isVowel && ch != last) {
            total++;
            last=ch;
        } else if(ch != last) {
            last= ch;
        } }
    return total;}
void toLowerCase(string& str) {
    for (int i =0; i <str.length(); i++) {
        if (str[i]>='A' && str[i] <= 'Z') {
            str[i]=str[i]+('a'-'A');
        }
    }}
bool hasSpace(string str) {
    for(int i=0; i<str.length(); i++) {
        if (str[i]== ' ') {
            return true;       }
    }
    return false;
}
int main() {
    string text;
    cout<<"Enter a single word without spaces: ";
    cin>>text;
    if (hasSpace(text)) {
        cout<<"Error: Input contains whitespace. Please enter a single word.";
        return 0;
    }
    toLowerCase(text);
    cout<<"Reversed: "<<reverseString(text)<<endl;

    if (isPalindrome(text)) {
        cout<<"It is a palindrome."<<endl;
    } else 
	{
        cout<<"It is not a palindrome."<<endl;
    }
    cout<<"Vowel count (no consecutive repeats): "<<countVowels(text)<<endl;
    return 0;
}
