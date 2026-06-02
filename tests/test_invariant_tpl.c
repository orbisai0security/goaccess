#include <check.h>
#include <stdlib.h>
#include <string.h>

/* Include tpl public API */
#include "tpl.h"

START_TEST(test_tpl_format_string_safety)
{
    /* Invariant: tpl_map must not crash or corrupt memory when given
       adversarial format strings; it must either succeed or return NULL safely */
    tpl_node *tn;
    int val = 0;

    /* Normal single-integer format: must succeed */
    tn = tpl_map("i", &val);
    ck_assert_msg(tn != NULL, "tpl_map with valid format 'i' should succeed");
    tpl_free(tn);

    /* Empty format string: must fail gracefully (return NULL), not crash */
    tn = tpl_map("");
    ck_assert_msg(tn == NULL, "tpl_map with empty format should return NULL");
}
END_TEST

Suite *tpl_suite(void)
{
    Suite *s = suite_create("tpl");
    TCase *tc = tcase_create("format_string_safety");
    tcase_add_test(tc, test_tpl_format_string_safety);
    suite_add_tcase(s, tc);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s = tpl_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
