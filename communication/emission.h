#ifndef COMMUNICATION_EMISSION_H
#define COMMUNICATION_EMISSION_H

// Une valeur acceptable
#define BUFF_SIZE 40

#ifdef __cplusplus
extern "C" {
#endif


int send_val(char* buffer, const char *val_key, int value);

int send_cmd(char* buffer, const char *com_key);


#ifdef __cplusplus
}
#endif


#endif  // COMMUNICATION_EMISSION_H
