#ifndef _BOARD_H_
#define _BOARD_H_

#include "MySystype.h"


#define SOUND_OUT_PORT                  (8)
#define PC_SERIAL_BAUDRATE         (115200)
#define WIRELESS_SERIAL_BAUDRATE    (19200)
#define WIRELESS_BUFF_SIZE            (128)
#define PC_BUFF_SIZE                  (128)
#define SOUND_TABLE_SIZE               (16)

typedef enum {
    E_STATE_NONE = 0,
    E_STATE_TRANSMIT,
    E_STATE_RECEIVE_START,
    E_STATE_RECEIVE,
    E_STATE_RECEIVE_OK_START,
    E_STATE_RECEIVE_OK,
    E_STATE_RECEIVE_NG_START,
    E_STATE_RECEIVE_NG,
    
    E_STATE_MAX
} E_STATE;

typedef struct {
    INT iRemain; // バッファ中の残データ数
    INT iRead;   // 読み出し位置
    INT iWrite;  // 書き込み位置
} S_BUFF_INFO;

typedef enum {
    E_TRANSMIT_DATA_POS_PREFIX = 0,
    E_TRANSMIT_DATA_POS_COMMAND1,
    E_TRANSMIT_DATA_POS_COMMAND2,
    E_TRANSMIT_DATA_POS_LENGTH1,
    E_TRANSMIT_DATA_POS_LENGTH2,
    E_TRANSMIT_DATA_POS_DATA,
    
    E_TRANSMIT_DATA_POS_MAX
} E_TRANSMIT_DATA_POS;

#endif // _BOARD_H_
