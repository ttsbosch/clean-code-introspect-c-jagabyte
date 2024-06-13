#define MAX_LINE_LENGTH 1024
#define MAX_RECORDS 1024
#define LOT_SIZE 100
#define MAX_CURRENCY_NAME_SIZE 256

typedef struct {
    char sourceCurrency[MAX_CURRENCY_NAME_SIZE]; 
    char destibationCurrency[MAX_CURRENCY_NAME_SIZE];
    float Lots;
    double Price;
} TradeRecord ;
