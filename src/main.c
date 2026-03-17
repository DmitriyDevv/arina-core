#include <stdio.h>
#include "state.h"

static void test_init_to_idle(void) {
    State state;

    state_init(&state);
    state_process(&state);

    printf("test_init_to_idle:\n");
    state_print(&state);
    printf("\n");
}

static void test_idle_to_run(void) {
    State state;

    state_init(&state);
    state_process(&state);
    state_set_event(&state);
    state_process(&state);

    printf("test_idle_to_run:\n");
    state_print(&state);
    printf("\n");
}

static void test_single_tick_in_run(void) {
    State state;

    state_init(&state);
    state_process(&state);
    state_set_event(&state);
    state_process(&state);

    state_set_tick_1hz(&state);
    state_process(&state);

    printf("test_single_tick_in_run:\n");
    state_print(&state);
    printf("\n");
}

static void test_periodic_flags(void) {
    State state;

    state_init(&state);
    state_process(&state);
    state_set_event(&state);
    state_process(&state);

    printf("=== test_periodic_flags ===\n");

    for (int i = 0; i < 20; i++) {
        state_set_tick_1hz(&state);
        state_process(&state);

        printf("tick %2d | uptime=%u | n5=%u n10=%u n20=%u",
               i + 1,
               state.uptime_sec,
               state.nupr_5,
               state.nupr_10,
               state.nupr_20);

        if (i + 1 == 5 || i + 1 == 15) {
            printf(" | task5s");
        }
        if (i + 1 == 10) {
            printf(" | task5s task10s");
        }
        if (i + 1 == 20) {
            printf(" | task5s task10s task20s");
        }

        printf("\n");
    }

    printf("\n");
}

static void test_error_blocks_tick(void) {
    State state;

    state_init(&state);
    state_process(&state);
    state_set_event(&state);
    state_process(&state);

    state_set_tick_1hz(&state);
    state_process(&state);

    printf("test_error_blocks_tick: before error\n");
    state_print(&state);
    printf("\n");

    state_set_error(&state);
    state_process(&state);

    printf("test_error_blocks_tick: in error before tick\n");
    state_print(&state);
    printf("\n");

    state_set_tick_1hz(&state);
    state_process(&state);

    printf("test_error_blocks_tick: in error after tick\n");
    state_print(&state);
    printf("\n");
}

int main(void) {
    test_periodic_flags();

    return 0;
}