#ifndef UTILS_H
#define UTILS_H

const int POISON = 0xDEADFACE;

enum util_constants {
    END_WITH_SUC = 1
};

#define SAFE_CALLOC(name, size_of_buf, el_type)                                                             \
    el_type* temp_##name = (el_type*) calloc(size_of_buf, sizeof(el_type));                                 \
                                                                                                            \
    if (temp_##name == NULL)                                                                                \
        fprintf(stderr, "Allocation error of " #name " in %s (%s:%d)\n", __func__, __FILE__, __LINE__);     \
                                                                                                            \
    el_type* name = temp_##name;    
    
#define SAFE_FOPEN(name, file, mode)                                                                        \
    FILE* temp_##name = fopen(file, mode);                                                                  \
                                                                                                            \
    if (temp_##name == NULL)                                                                                \
        fprintf(stderr, "File opening error (" #name ") in %s (%s:%d)\n", __func__, __FILE__, __LINE__);    \
                                                                                                            \
    FILE* name = temp_##name; 

#define SAFE_SNPRINTF(str, size, ...)                                                                       \
    int snprintf_check_##str = snprintf(str, size, __VA_ARGS__);                                            \
                                                                                                            \
    if (snprintf_check_##str < 0)                                                                           \
        fprintf(stderr, "snprintf error (" #str ") in %s (%s:%d)\n", __func__, __FILE__, __LINE__);

#endif