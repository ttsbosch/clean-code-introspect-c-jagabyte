#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ConvertCSVTradeDataToXML.h>
#include <SplitString.h>
#include <StringHelper.h>
#include <Converters.h>

void convertCSVTradeDataToXML(FILE* stream) {
    char line[MAX_LINE_LENGTH];
    TradeRecord  records[MAX_RECORDS];
    int lineCount = 0;
    int recordCount = 0;

    while (fgets(line, sizeof(line), stream)) {
        char* fields[3];
        int fieldCount = 0;
        char* token = strtok(line, ",");
        while (token != NULL) {
            fields[fieldCount++] = token;
            token = strtok(NULL, ",");
        }

        if (fieldCount != 3) {
            fprintf(stderr, "WARN: Line %d malformed. Only %d field(s) found.\n", lineCount + 1, fieldCount);
            continue;
        }

        if (strlen(fields[0]) != 6) {
            fprintf(stderr, "WARN: Trade currencies on line %d malformed: '%s'\n", lineCount + 1, fields[0]);
            continue;
        }

        int tradeAmount;
        if (!getIntegerFromString(fields[1], &tradeAmount)) {
            fprintf(stderr, "WARN: Trade amount on line %d not a valid integer: '%s'\n", lineCount + 1, fields[1]);
        }

        double tradePrice;
        if (!tryToConvertDouble(fields[2], &tradePrice)) {
            fprintf(stderr, "WARN: Trade price on line %d not a valid decimal: '%s'\n", lineCount + 1, fields[2]);
        }

        strncpy(records[recordCount].sourceCurrency, fields[0], 3);
        strncpy(records[recordCount].destibationCurrency, fields[0] + 3, 3);
        records[recordCount].Lots = tradeAmount / LotSize;
        records[recordCount].Price = tradePrice;
        recordCount++;
        lineCount++;
    }

    FILE* outFile = fopen("output.xml", "w");
    fprintf(outFile, "<TradeRecords>\n");
    for (int recordIndex  = 0; recordIndex  < recordCount; recordIndex ++) {
        fprintf(outFile, "\t<TradeRecord>\n");
        fprintf(outFile, "\t\t<SourceCurrency>%s</SourceCurrency>\n", records[recordIndex ].sourceCurrency);
        fprintf(outFile, "\t\t<DestinationCurrency>%s</DestinationCurrency>\n", records[i].destibationCurrency);
        fprintf(outFile, "\t\t<Lots>%d</Lots>\n", records[recordIndex ].Lots);
        fprintf(outFile, "\t\t<Price>%f</Price>\n", records[recordIndex ].Price);
        fprintf(outFile, "\t</TradeRecord>\n");
    }
    fprintf(outFile, "</TradeRecords>");
    fclose(outFile);
    printf("INFO: %d trades processed\n", recordCount);
}

