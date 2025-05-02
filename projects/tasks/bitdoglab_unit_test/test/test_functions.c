/**
 * @file    test_functions.c
 * @author  Ricardo Jorge Furlan
 * @brief   Run automatic tests on the adc_to_celsius function
 * @version 0.1
 * @date    2025-05-02
 */
#include "unity.h"
#include "app/functions.h"
#include <math.h>
#include <stdio.h>

void setUp(void) {}
void tearDown(void) {}

// Check conversion
void test_function_adc_to_celsius_1(void) {
    float    temp1[]    = { -50.0,  -20.0, -10.0,   0.0,   20.0,   25.0,   27.0,   50.0,  80.0,  100.0,  120.0,  150.0};
    float    temp2[]    = {-50.22, -19.79, -9.95, -0.12,  20.01,  25.17,  27.04,  49.98, 79.95, 100.09, 120.22, 150.19};
    uint16_t ad_value[] = {  1041,    976,   955,   934,    891,    880,    876,    827,   763,    720,    677,    613};

    const int n_values = sizeof(ad_value)/sizeof(ad_value[0]);
    
    for(int i=0;i<n_values;i++){
        TEST_ASSERT_FLOAT_WITHIN(0.01, temp2[i], adc_to_celsius(ad_value[i]));  // precision 0.01
    }
    for(int i=0;i<n_values;i++){
        //TEST_ASSERT_FLOAT_WITHIN(1.0, temp1[i], adc_to_celsius(ad_value[i]));   // precision 1.0
        // to fail:
        //TEST_ASSERT_FLOAT_WITHIN(0.1, temp1[i], adc_to_celsius(ad_value[i]));   // precision 0.1
    }
}

// Check invalid AD values
void test_function_adc_to_celsius_2(void) {
    TEST_ASSERT_TRUE( isnan(adc_to_celsius( 612))); // temperature  >  150.19
    TEST_ASSERT_FALSE(isnan(adc_to_celsius( 613))); // temperature  <= 150.19
    TEST_ASSERT_FALSE(isnan(adc_to_celsius(1041))); // temperature  >= -50.22
    // to fail:
    //TEST_ASSERT_FALSE(isnan(adc_to_celsius(1050))); 
    TEST_ASSERT_TRUE( isnan(adc_to_celsius(1042))); // temperature  <  -50.22
}

int main(void) {
    stdio_init_all();
    sleep_ms(2000);
    printf("********** Start test **********\n\n");

    UNITY_BEGIN();
    RUN_TEST(test_function_adc_to_celsius_1);
    RUN_TEST(test_function_adc_to_celsius_2);
    UNITY_END();

    printf("\n********** End test **********\n");

    while (1) {
        tight_loop_contents();
    }
}
