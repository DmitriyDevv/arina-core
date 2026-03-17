#include "state.h"
#include "tasks.h"
#include <stddef.h>
#include <stdio.h>

void task1(State *state) {
    if (state == NULL) {
        return;
    }

    state_clear_event(state);
}

void task2(State *state) {
    if (state == NULL) {
        return;
    }

    state_inc_uptime(state);

    if (state->nupr_5 >= 5) {
        state->flag_5s = 1;
        state->nupr_5 = 0;
    }

    if (state->nupr_10 >= 10) {
        state->flag_10s = 1;
        state->nupr_10 = 0;
    }

    if (state->nupr_20 >= 20) {
        state->flag_20s = 1;
        state->nupr_20 = 0;
    }

    state_clear_tick_1hz(state);
}

void task3(State *state) {
    if (state == NULL) {
        return;
    }

    state_clear_vrl(state);
}

void task5s(State *state) {
    if (state == NULL) {
        return;
    }

    printf("task5s fired\n\n");
    state->flag_5s = 0;
}

void task10s(State *state) {
    if (state == NULL) {
        return;
    }

    printf("task10s fired\n\n");
    state->flag_10s = 0;
}

void task20s(State *state) {
    if (state == NULL) {
        return;
    }

    printf("task20s fired\n\n");
    state->flag_20s = 0;
}