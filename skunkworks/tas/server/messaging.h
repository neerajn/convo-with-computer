/**
 * Server side messaging protocol definitions
 *
 */
#ifndef MESSAGING_H
#define MESSAGING_H

#include <stdint.h>

#define MAX_FILE_PATH_NAME_SIZE 512
#define RESPONSE_ERROR_MSG_SIZE 256
#define MAX_DATE_SIZE 256
#define MAX_PRIMES_LIST_SIZE 256


#pragma pack(push, 1)

// Request structures


struct RequestHeader
{
    int8_t m_msgType;
};

struct RequestTestPrime
{
    int64_t m_number;
};

struct RequestNextPrime
{
    int64_t m_number;
};

struct RequestNextNPrimes
{
    int64_t m_number;
    int64_t m_howMany;
};

struct RequestGetDate
{
    int8_t m_dummy;
};

struct RequestFileTestOperation
{
    char m_filepathname [MAX_FILE_PATH_NAME_SIZE];
};

// Response structures

struct ResponseHeader
{
    int8_t m_msgType;
};

struct ResponseTestPrime
{
    int8_t m_isPrime; // a bit can also represent, but lets keep it as 8bits for ease for now.
};

struct ResponseNextPrime
{
    int64_t m_number;
};

struct ResponseNextNPrime
{
    uint16_t m_size;
    int64_t m_number[MAX_PRIMES_LIST_SIZE];
};

struct ResponseGetDate
{
   char m_date [MAX_DATE_SIZE]; // can be struct with ints to represent dd,mm,yy,hh,mm,ss
};

struct ResponseFileTestOperation
{
    int8_t isFile; 
};

struct ResponseError
{
    char m_errorMsg [RESPONSE_ERROR_MSG_SIZE];
};

#pragma pack(pop)

#endif
