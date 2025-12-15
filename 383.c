/**
    383.赎金信
    给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。
    如果可以，返回 true ；否则返回 false 。
    magazine 中的每个字符只能在 ransomNote 中使用一次。
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 *  
 */
bool canConstruct(char* ransomNote, char* magazine) {
    int ransomNoteSize = strlen(ransomNote);
    int magazineSize = strlen(magazine);
    if (ransomNoteSize > magazineSize) {
        return false;
    }

    int ransomNoteCount[26] = {0};
    int magazineCount[26] = {0};
    for (int i = 0; i < ransomNoteSize; i++) {
        ransomNoteCount[ransomNote[i] - 'a']++;
    }
    for (int i = 0; i < magazineSize; i++) {
        magazineCount[magazine[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++) {
        if (ransomNoteCount[i] > magazineCount[i]) {
            return false;
        }
    }
    return true;    
}

int main(){
    char ransomNote[] = "a";
    char magazine[] = "b";
    printf("%d\n", canConstruct(ransomNote, magazine));
    return 0;
}
