#ifndef ASTROFOCUS_DEVICE_HOST_PROTOCOL_INC
#define ASTROFOCUS_DEVICE_HOST_PROTOCOL_INC

#define AF_HOST_MAGIC 0x41464853UL /* AFHS */
#define AF_HOST_PROTOCOL_VERSION 1UL
#define AF_HOST_MAX_IMAGE_BYTES (512UL*1024UL*1024UL)

enum AfHostCommand {
    AFHC_NONE=0,
    AFHC_CONNECT_CAMERA=1,
    AFHC_CONNECT_FOCUSER=2,
    AFHC_DISCONNECT=3,
    AFHC_GET_BOOL=4,
    AFHC_GET_INT=5,
    AFHC_GET_DOUBLE=6,
    AFHC_SET_INT=7,
    AFHC_CALL_INT=8,
    AFHC_CALL_NOARGS=9,
    AFHC_START_EXPOSURE=10,
    AFHC_GET_IMAGE=11,
    AFHC_PING=12,
    AFHC_SHUTDOWN=13,
    AFHC_TEST_BLOCK=90,
    AFHC_TEST_CRASH=91
};

enum AfHostPayloadFormat {
    AFHP_NONE=0,
    AFHP_U32_IMAGE=1
};

#pragma pack(push,1)
struct AfHostRequest {
    DWORD magic;
    DWORD protocolVersion;
    DWORD structBytes;
    DWORD command;
    ULONGLONG requestId;
    ULONGLONG deadlineTick;
    LONG intArg;
    double doubleArg;
    DWORD boolArg;
    DWORD reserved;
    wchar_t progId[256];
    wchar_t member[64];
};

struct AfHostResponse {
    DWORD magic;
    DWORD protocolVersion;
    DWORD structBytes;
    DWORD command;
    ULONGLONG requestId;
    ULONGLONG completedTick;
    LONG hr;
    LONG intValue;
    double doubleValue;
    DWORD boolValue;
    LONG width;
    LONG height;
    LONG maxAdu;
    DWORD payloadFormat;
    DWORD payloadBytes;
    DWORD hostPid;
    DWORD reserved;
};
#pragma pack(pop)

#endif
