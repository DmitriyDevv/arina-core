#include "state.h"
#include "tasks.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

static bool check_state(const State *state) {
    return state != NULL;
}

void state_init(State *state) {
    if (!check_state(state)) {
        return;
    }

    memset(state, 0, sizeof(State));
    state->status = STATUS_INIT;
}


static const char *status_to_string(Status status) {
    switch (status) {
        case STATUS_IDLE:
            return "IDLE";
        case STATUS_INIT:
            return "INIT";
        case STATUS_RUN:
            return "RUN";
        case STATUS_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

void state_print(const State *state) {
    if (!check_state(state)) {
        return;
    }

    printf("uptime_sec: %u\n", state->uptime_sec);
    printf("event_flag: %d\n", state->event_flag);
    printf("tick_1hz_flag: %d\n", state->tick_1hz_flag);
    printf("error_flag: %d\n", state->error_flag);
    printf("vrl_flag: %d\n", state->vrl_flag);
    printf("nupr_5: %d\n", state->nupr_5);
    printf("nupr_10: %d\n", state->nupr_10);
    printf("nupr_20: %d\n", state->nupr_20);
    printf("flag_5s: %d\n", state->flag_5s);
    printf("flag_10s: %d\n", state->flag_10s);
    printf("flag_20s: %d\n", state->flag_20s);
    printf("status: %s\n", status_to_string(state->status));
}

void state_set_event(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->event_flag = 1;
}

void state_clear_event(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->event_flag = 0;
}

void state_set_status(State *state, Status status) {
    if (!check_state(state)) {
        return;
    }

    state->status = status;
}

void state_set_tick_1hz(State *state) {
    if (!check_state(state)) {
        return;
    }

    if (state->status == STATUS_ERROR) {
        return;
    }

    state->tick_1hz_flag = 1;
    state->nupr_5++;
    state->nupr_10++;
    state->nupr_20++;
}

void state_clear_tick_1hz(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->tick_1hz_flag = 0;
}

void state_inc_uptime(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->uptime_sec++;
}

void state_process(State *state) {
    if (!check_state(state)) {
        return;
    }

    Status status = state->status;

    if (status != STATUS_ERROR) {
        if (state->tick_1hz_flag == 1) {
            task2(state);
        }

        if (state->vrl_flag == 1) {
            task3(state);
        }

        if (state->flag_5s == 1) {
            task5s(state);
        }

        if (state->flag_10s == 1) {
            task10s(state);
        }

        if (state->flag_20s == 1) {
            task20s(state);
        }
    }

    if (status == STATUS_INIT) {
        status = STATUS_IDLE;
    } else if (status == STATUS_IDLE && state->event_flag == 1) {
        task1(state);
        status = STATUS_RUN;
    } else if (status == STATUS_RUN && state->error_flag == 1) {
        status = STATUS_ERROR;
    } else if (status == STATUS_ERROR && state->error_flag == 0) {
        status = STATUS_IDLE;
    }

    state->status = status;
}

void state_set_error(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->error_flag = 1;
}

void state_clear_error(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->error_flag = 0;
}

void state_set_vrl(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->vrl_flag = 1;
}

void state_clear_vrl(State *state) {
    if (!check_state(state)) {
        return;
    }

    state->vrl_flag = 0;
}

