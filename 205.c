/**
    205.同构字符串
    给定两个字符串 s 和 t，判断它们是否是同构的。
    如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
    映射关系可能是字母到字母的映射，也可以是其他字符到其他字符的映射。
    例如，给定 s = "egg"，t = "add"，返回 true ；给定 s = "foo"，t = "bar"，返回 false ；给定 s = "paper"，t = "title"，返回 true ；
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

bool isIsomorphic(char* s, char* t) {
    int sSize = strlen(s);
    int tSize = strlen(t);
    if (sSize != tSize) {
        return false;
    }
    
    // Arrays to store the last seen position of each character.
    // Using 256 for extended ASCII support.
    int mapS[256] = {0};
    int mapT[256] = {0};

    for (int i = 0; i < sSize; i++) {
        // If the last seen positions of the current characters don't match,
        // it means they are not isomorphic.
        // We use i + 1 because the array is initialized to 0.
        if (mapS[(unsigned char)s[i]] != mapT[(unsigned char)t[i]]) {
            return false;
        }
        
        // Update the last seen position.
        mapS[(unsigned char)s[i]] = i + 1;
        mapT[(unsigned char)t[i]] = i + 1;
    }

    return true;
}

int main(){
    char s[] = "bbbaaaba";
    char t[] = "aaabbbba";
    printf("%d\n", isIsomorphic(s, t));
    return 0;
}
