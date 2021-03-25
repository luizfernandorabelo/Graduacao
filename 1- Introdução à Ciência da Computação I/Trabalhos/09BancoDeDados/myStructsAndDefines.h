#ifndef __MY_STRUCTS_AND_DEFINES__
#define __MY_STRUCTS_AND_DEFINES__

#define bool char
#define TRUE 1
#define FALSE 0

#define DEBUG 0

#define FILE_OPEN_ERROR 0
#define FILE_EXTENSION_ERROR 0
#define FILE_READ_ERROR 0
#define FILE_WRITE_ERROR 0
#define PRIMITIVE_TYPE_NOT_FOUND 0

typedef enum { INT, FLOAT, DOUBLE, CHAR, STRING } type_code; 

typedef union{
    int intField;
    float floatField;
    double doubleFied;
    char charField;
    int *intPointerField;
    float *floatPointerField;
    double *doublePointerField;
    char *charPointerField;
    char *stringField;
}field_type;

typedef struct{
    char *datFileName;
    char *regFileName;
    char *idxFileName;
    char *extraFileName;
}file_names;

typedef struct{
    int typeCode;
    int typeSize;
}type_data;

typedef struct{
    char *name;
    type_data *typeData;
}field_data;

typedef struct{
    void *keyValue;
    int offset;
}idx_fields;

typedef struct{
    int offsetValue;
    int keysNumber;
    idx_fields **idxFields;
}index_data;

typedef struct{
    file_names files;
    field_data key;
    field_data *fields;
    int fieldsNumber;
    index_data idxFile;
}metadata;

#endif