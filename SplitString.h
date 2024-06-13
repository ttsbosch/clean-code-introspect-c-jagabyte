char** SplitString(const char* inputString, char delimiter) {
    int delimiterCount = 0;
    const char* currentString = inputString;
    while (*currentString != '\0') {
        if (*currentString++ == delimiter) {
            delimiterCount++;
        }
    }

    char** tokens = (char**)malloc(sizeof(char*) * (delimiterCount + 2));
    int tokenIndex  = 0;
    currentString = inputString;
    char* token = (char*)malloc(strlen(inputString) + 1);
    int charIndex  = 0;
    while (*currentString != '\0') {
        if (*currentString == delimiter) {
            token[charIndex ] = '\0';
            tokens[tokenIndex ++] = strdup(token);
            charIndex  = 0;
        } else {
            token[charIndex ++] = *currentString;
        }
        currentString++;
    }
    token[charIndex ] = '\0';
    tokens[tokenIndex ++] = strdup(token);
    tokens[tokenIndex ] = NULL;
    free(token);
    return tokens;
}
