/*
 * cmd_buffer.h
 *
 *  Created on: Oct 23, 2021
 *      Author: gideon
 */

#ifndef CMD_BUFFER_H_
#define CMD_BUFFER_H_

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

#define CMD_BUF_SIZE 1024
#define NUM_BUFFERS 8

typedef struct {
    uint8_t data[CMD_BUF_SIZE];
    int bufnr;
    int size;
    int slipEscape;
    int dropped;
} command_buf_t;

typedef struct {
    QueueHandle_t freeQueue;
    QueueHandle_t transmitQueue;
    QueueHandle_t receivedQueue;
    command_buf_t bufs[NUM_BUFFERS];
} command_buf_context_t;

void cmd_buffer_init(command_buf_context_t *context);
BaseType_t cmd_buffer_free(command_buf_context_t *context, command_buf_t *b);
BaseType_t cmd_buffer_get(command_buf_context_t *context, command_buf_t **b, TickType_t t);
BaseType_t cmd_buffer_transmit(command_buf_context_t *context, command_buf_t *b);
BaseType_t cmd_buffer_received(command_buf_context_t *context, command_buf_t **b, TickType_t t);
BaseType_t cmd_buffer_get_tx_isr(command_buf_context_t *context, command_buf_t **b, BaseType_t *w);
BaseType_t cmd_buffer_free_isr(command_buf_context_t *context, command_buf_t *b, BaseType_t *w);
BaseType_t cmd_buffer_get_free_isr(command_buf_context_t *context, command_buf_t **b, BaseType_t *w);
BaseType_t cmd_buffer_received_isr(command_buf_context_t *context, command_buf_t *b, BaseType_t *w);

#endif /* CMD_BUFFER_H_ */
