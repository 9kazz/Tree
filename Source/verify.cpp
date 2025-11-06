#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Logfile.h"
#include "utils.h"
#include "tree.h"
#include "verify.h"

TreeErr_t Node_Verify (TreeNode_t* node) {

    static TreeErr_t Error_code = 0;

    #define IF_CRITICAL_ERR                                                                                                                    \
        if (Error_code >= EC_MIN_CRITICAL_ERROR) {                                                                                                   \
            fprintf(Logfile, "<h3 style = \"color: red;\"> List_Verify: verification ended with critical error: %d\n </h3>", Error_code);      \
            return Error_code;                                                                                                                 \
        }


    if_null_pointer(node,        &Error_code); IF_CRITICAL_ERR
    // if_null_pointer(node->left,  &Error_code); IF_CRITICAL_ERR
    // if_null_pointer(node->right, &Error_code); IF_CRITICAL_ERR

    fprintf(Logfile, "<h3 style = \"color: orange;\"> List_Verify: verification ended with warnings: %d\n </h3>", Error_code);
    return Error_code;
}

TreeErr_t if_null_pointer(void* pointer, TreeErr_t* Error_code) {

    if (pointer == NULL)                                                                                                                                                                            
        PRINT_ERROR(EC_NULL_POINTER, "NULL pointer")

    return *Error_code;
} 