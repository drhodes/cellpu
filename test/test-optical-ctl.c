#include "stdio.h"
#include "stdlib.h"
#include "../err.h"
#include <check.h>
#include "../src/optical-ctl.c"

START_TEST (optical_ctl1) {
    OpticalCtl oc = opticalCtlNE();
    ck_assert(opticalCtlConfig(&oc, S, N));
}
END_TEST

START_TEST (optical_ctl2) {
    OpticalCtl oc = opticalCtlNE();
    ck_assert(!opticalCtlConfig(&oc, S, S));
}
END_TEST


Suite* suite_optical_ctl(void)
{
    Suite* s;
    s = suite_create("optical_ctl");
    
    TCase* tc1 = tcase_create("optical_ctl1");
    tcase_add_test(tc1, optical_ctl1);
    tcase_add_test(tc1, optical_ctl2);
    
    suite_add_tcase(s, tc1);
    return s;
}

int main(void)
{
    int number_failed;
    SRunner* sr;
    Suite* s = suite_optical_ctl();

    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
