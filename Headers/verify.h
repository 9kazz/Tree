#ifndef VERIFY_H
#define VERIFY_H

enum error_codes {
    EC_MIN_CRITICAL_ERROR = 1 << 10, // All errors more than this constant are critical
    EC_NULL_POINTER       = 1 << 10
};

#define PRINT_ERROR(code, text)                                                                 \
                                                                                                \
    fprintf(Logfile, "<h3 style = \"color: red;\"> Node_Verify: " text " </h3>\n");             \
    fprintf(Logfile, "<h3 style = \"color: red;\"> Error code: %d </h3>\n\n", code);            \
                                                                                                \
    *Error_code = *Error_code | code;


TreeErr_t Node_Verify (TreeNode_t* node);
TreeErr_t if_null_pointer(void* pointer, TreeErr_t* Error_code);

#endif