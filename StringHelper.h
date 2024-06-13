int getIntegerFromString(const char* inputString, int* value) {
    char* endptr;
    *value = strtol(inputString, &endptr, 10);
    if (endptr == inputString) {
        return 0;
    }
    return 1;
}
