#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

// HashType
struct HashType
{
    struct RecordType* head;
};

// Compute the hash function
int hash(int x, int hashSz)
{
    return x % hashSz;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Error\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
            pRecord->next = NULL;
        }

        fclose(inFile);
    }

    return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// display records in the hash structure
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;
    struct RecordType* pRecord;

    for (i=0;i<hashSz;++i)
    {
        pRecord = pHashArray[i].head;
        if (pRecord != NULL)
        {
            printf("Index %d:\n", i);
            while (pRecord != NULL)
            {
                printf("ID: %d, Name: %c, Order: %d\n", pRecord->id, pRecord->name, pRecord->order);
                pRecord = pRecord->next;
            }
        }
    }
}

void hashRecords(struct RecordType pData[], int dataSz, struct HashType *pHashArray, int hashSz)
{
    int i;
    int hashIndex;
    struct RecordType* pRecord;

    for (i = 0; i < dataSz; ++i)
    {
        hashIndex = hash(pData[i].id, hashSz);
        pRecord = (struct RecordType*) malloc(sizeof(struct RecordType));
        *pRecord = pData[i];
        pRecord->next = pHashArray[hashIndex].head;
        pHashArray[hashIndex].head = pRecord;
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    struct HashType *pHashArray;
    int hashSz = 10;  // You can adjust the size of the hash array as needed

    pHashArray = (struct HashType*) malloc(sizeof(struct HashType) * hashSz);

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);
    hashRecords(pRecords, recordSz, pHashArray, hashSz);
    displayRecordsInHash(pHashArray, hashSz);

    return 0;
}
