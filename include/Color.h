#pragma once

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#define TICK "\u2713"

const int MAX_BUFFER_LEN =5000;
const int MAX_COMMAND_LEN = 200;
const int MAX_PACKET_CHUNK_LEN = 1024;
const char* const SERVER_SHARED_DIR = "shared";
const char* const SERIALIZATION_DELIMITER = ";";