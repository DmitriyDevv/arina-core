#ifndef CORE_ARINA_STATE_H
#define CORE_ARINA_STATE_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    STATUS_IDLE,
    STATUS_INIT,
    STATUS_RUN,
    STATUS_ERROR
} Status;

typedef struct {
    uint32_t uptime_sec;
    uint8_t event_flag;
    uint8_t tick_1hz_flag;
    uint8_t error_flag;
    uint8_t vrl_flag;
    uint8_t nupr_5;
    uint8_t nupr_10;
    uint8_t nupr_20;
    uint8_t flag_5s;
    uint8_t flag_10s;
    uint8_t flag_20s;
    Status status;
} State;

void state_init(State *state);

void state_print(const State *state);

void state_set_event(State *state);

void state_clear_event(State *state);

void state_set_status(State *state, Status status);

void state_set_tick_1hz(State *state);

void state_clear_tick_1hz(State *state);

void state_inc_uptime(State *state);

void state_set_error(State *state);

void state_clear_error(State *state);

void state_process(State *state);

void state_set_vrl(State *state);

void state_clear_vrl(State *state);

#endif
