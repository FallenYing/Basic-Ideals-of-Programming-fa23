#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_line(char line[], int max);
int strindex(const char source[], const char searchfor[]);
int grep(const char* pattern);
bool test_getline(void);
bool test_strindex(void);
bool test_grep(void);
bool compare_files(const char *file1, const char *file2);


int main(const int argc, const char* argv[]) {
    if (test_getline()) {
        printf("test_getline pass\n");
    }
    else {
        printf("test_getline fail\n");
        exit(1);
    }

    if (test_strindex()) {
        printf("test_strindex pass\n");
    }
    else {
        printf("test_strindex fail\n");
        exit(1);
    }

    if (test_grep()) {
        printf("test_grep pass\n");
    }
    else {
        printf("test_grep fail\n");
        exit(1);
    }
    if (argc != 2) {
        printf("usage: grep pattern\n");
        exit(1);
    }
    freopen("CON","r",stdin);
    grep(argv[1]);
    return 0;
}

/* get_line: get line into s, return length */
int get_line(char s[], int lim) {
    int len = 0;
    for (; len < lim; len++) {
        char ch = getchar();
        if (ch == EOF) {
            s[len] = '\0';
            return len - 1;
        }
        s[len] = ch;
        if (ch == '\n') {
            s[len + 1] = '\0';
            return len;
        }
    }
    s[lim - 1] = '\0';
    return lim;
}

/* strindex: return index of t in s, -1 if none */
int strindex(const char s[], const char t[]) {
    for (int i = 0; s[i] != '\0'; i++) {
        for (int j = 0; t[j] != '\0'; j++) {
            if (s[i + j] != t[j]) {
                break;
            }
            if (t[j + 1] == '\0') {
                return i;
            }
        }
    }
    return -1;
}

/* grep: print the line match the pattern, return count of matches */
int grep(const char* pattern) {
    #define MAXLINE 1000
    char line[MAXLINE];
    int count = 0;
    while (!feof(stdin)) {
        get_line(line, MAXLINE);
        if (strindex(line, pattern) != -1) {
            count++;
            printf("%s", line);
        }
    }
#undef MAXLINE
    return count;
}

bool test_getline(void) {
    FILE* fp_stdin = freopen("test.txt", "r", stdin);
    FILE* file = fopen("test.txt", "r");
    #define LINE_LENGTH 50
    char expected[LINE_LENGTH], actual[LINE_LENGTH];
    if (fgets(expected, 50, file)) {
        get_line(actual, LINE_LENGTH);
        if (strcmp(expected, actual)) {
            fclose(fp_stdin);
            fclose(file);
            return false;
        }
    }
    #undef LINE_LENGGTH
    fclose(file);
    fclose(fp_stdin);
    return true;
}

bool test_strindex(void) {
    char s[] = "hello world";
    char t1[] = "world";
    char t2[] = "worL";
    char t3[] = "l";
    if (strindex(s, t1) != 6) return false;
    if (strindex(s, t2) != -1) return false;
    if (strindex(s, t3) != 2) return false;
    return true;
}

bool test_grep(void) {
    FILE* fp_stdout = freopen("output.txt", "w", stdout);
    FILE* fp_stdin = freopen("test.txt", "r", stdin);
    grep("hello");
    fclose(fp_stdout);
    fclose(fp_stdin);
    freopen("CON","w",stdout);
    return compare_files("output.txt", "test_expected.txt");
}

bool compare_files(const char *file1, const char *file2) {
    FILE *fp1, *fp2;
    char line1[1000], line2[1000];

    fp1 = fopen(file1, "r");
    if (fp1 == NULL) {
        printf("can't open file %s\n", file1);
        exit(1);
    }

    fp2 = fopen(file2, "r");
    if (fp2 == NULL) {
        printf("can't open file %s\n", file2);
        fclose(fp1);
        exit(1);
    }

    while (true) {
        char* _1 = fgets(line1, 1000, fp1);
        char* _2 = fgets(line2, 1000, fp2);
        if (!_1|| !_2) {
            break;
        }
        if (strcmp(line1, line2)) {
            fclose(fp1);
            fclose(fp2);
            return false;
        }
    }

    if (feof(fp1) && feof(fp2)) {
        fclose(fp1);
        fclose(fp2);
        return true;
    }

    fclose(fp1);
    fclose(fp2);
    return false;
}