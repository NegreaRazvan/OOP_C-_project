#pragma once
#include "../Domain/Carte.h"
#include "../Repository/Repository.h"
#include "../Service/Service.h"

class Tests {
private:
    static void test_create_object();
    static void test_validate_object();

    static void test_add_element();
    static void test_delete_element();
    static void test_modify_element();
    static void test_search_element();
    static void test_copy_list();

    static void test_service_add_element();
    static void test_get_all_elements();
    static void test_service_delete_element();
    static void test_service_modify_element();
    static void test_service_search_element();
    static void test_filter_element();
    static void test_sort_element();

    void test_Vector();

public:
    void run();
};

