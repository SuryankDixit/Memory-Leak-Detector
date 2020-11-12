#include "memory-leak.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*Application Structures*/

typedef struct emp_ {

    char emp_name[30];
    unsigned int emp_id;
    unsigned int age;
    struct emp_ *mgr;
    float salary;
} emp_t;

typedef struct student_{

    char stud_name[32];
    unsigned int rollno;
    unsigned int age;
    float aggregate;
    struct student_ *best_colleague;
} student_t;

int
main(int argc, char **argv){

    /*Step 1 : Initialize a new structure database */
    struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
    mld_init_primitive_data_types_support(struct_db);


    /*Step 2 : Create structure record for structure emp_t*/
    static field_info_t emp_fields[] = {
        FIELD_INFO(emp_t, emp_name, CHAR,    0),
        FIELD_INFO(emp_t, emp_id,   UINT32,  0),
        FIELD_INFO(emp_t, age,      UINT32,  0),
        FIELD_INFO(emp_t, mgr,      OBJ_PTR, emp_t),
        FIELD_INFO(emp_t, salary,   FLOAT, 0)
    };
    /*Step 3 : Register the structure in structure database*/
    REGISTER_STRUCTURE(struct_db, emp_t, emp_fields);

    static field_info_t stud_fiels[] = {
        FIELD_INFO(student_t, stud_name, CHAR, 0),
        FIELD_INFO(student_t, rollno,    UINT32, 0),
        FIELD_INFO(student_t, age,       UINT32, 0),
        FIELD_INFO(student_t, aggregate, FLOAT, 0),
        FIELD_INFO(student_t, best_colleague, OBJ_PTR, student_t)
    };
    REGISTER_STRUCTURE(struct_db, student_t, stud_fiels);

    /*Step 4 : Verify the correctness of structure database*/
    // print_structure_db(struct_db);



    /*Working with object database*/
    /*Step 1 : Initialize a new Object database */
    object_db_t *object_db = calloc(1, sizeof(object_db_t));
    object_db->struct_db = struct_db;
    
    /*Step 2 : Create some sample objects, equivalent to standard 
     * calloc(1, sizeof(student_t))*/
    student_t *abhishek = xcalloc(object_db, "student_t", 1);
    mld_set_dynamic_object_as_root(object_db, abhishek);

    student_t *shivani = xcalloc(object_db, "student_t", 1);
    strncpy(shivani->stud_name, "shivani", strlen("shivani"));
    // abhishek->best_colleague = shivani;
    
    emp_t *joseph = xcalloc(object_db, "emp_t", 2);

    // print_object_db(object_db);

    printf("\n");
    
    run_mld_algorithm(object_db);
    report_leaked_objects(object_db);

    return 0;
}
