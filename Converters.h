int tryToConvertDouble(const char* inputString, double* value) { 
    char* endptr;
    *value = strtod(inputString, &endptr);
    if (endptr == inputString) {
        return 0;
    }
    return 1;
}
