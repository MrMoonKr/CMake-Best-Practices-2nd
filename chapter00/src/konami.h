#pragma once



typedef struct
{
    int nkeys;
    int *keys;
    int ok;
    
} KONAMI;

bool konami_push(KONAMI *konami, int ch);
