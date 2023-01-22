//
// Created by Slayer on 04/10/2022.
//

#include "reader.h"
#include <endianness/byte_swap.h>
#include <endianness/detection.h>
#include <string.h>
void cbin_reader_init(cbin_reader_t *reader, const void *buffer, size_t size) {
    reader->_buffer = buffer;
    reader->_position = 0;
    reader->_size = buffer ? size : 0;
    reader->_error = CBIN_ERR_OK;
}
void cbin_reader_reset(cbin_reader_t *reader) {
    reader->_position = 0;
    reader->_error = CBIN_ERR_OK;
}
void cbin_reader_discard_error(cbin_reader_t *reader) {
    reader->_error = CBIN_ERR_OK;
}
cbin_err_t cbin_reader_skip(cbin_reader_t *reader, size_t count) {
    if (reader->_error)
        return reader->_error;
    if (reader->_position + count > reader->_size) {
        return reader->_error = CBIN_ERR_OUT_OF_BOUNDS;
    }
    reader->_position += count;
    return CBIN_ERR_OK;
}
cbin_err_t cbin_reader_seek(cbin_reader_t *reader, size_t position) {
    if (reader->_error)
        return reader->_error;
    if (position > reader->_size) {
        return reader->_error = CBIN_ERR_OUT_OF_BOUNDS;
    }
    reader->_position = position;
    return CBIN_ERR_OK;
}
const void *cbin_reader_buffer(const cbin_reader_t *reader) {
    return reader->_buffer;
}
size_t cbin_reader_position(const cbin_reader_t *reader) {
    return reader->_position;
}
size_t cbin_reader_size(const cbin_reader_t *reader) { return reader->_size; }
cbin_err_t cbin_reader_error(const cbin_reader_t *reader) {
    return reader->_error;
}
size_t cbin_reader_remaining(const cbin_reader_t *reader) {
    return reader->_size - reader->_position;
}
cbin_err_t cbin_read(cbin_reader_t *reader, void *buffer, size_t size) {
    if (reader->_error)
        return reader->_error;
    if (reader->_position + size > reader->_size) {
        return reader->_error = CBIN_ERR_OUT_OF_BOUNDS;
    }
    if (CBIN_LIKELY(buffer != NULL)) {
        memcpy(buffer, (const uint8_t *)reader->_buffer + reader->_position,
               size);
    }
    reader->_position += size;
    return CBIN_ERR_OK;
}

#ifdef __LITTLE_ENDIAN__
#    define READ_LE(size, swap) return cbin_read(reader, value, (size) / 8)
#    define READ_BE(size, swap)                                                \
        cbin_read(reader, value, (size) / 8);                                  \
        if (CBIN_LIKELY(value != NULL)) {                                      \
            *value = swap(*value);                                             \
        }                                                                      \
        return cbin_reader_error(reader)

#elif defined(__BIG_ENDIAN__)
#    define READ_LE(size, swap)                                                \
        cbin_read(reader, value, (size) / 8);                                  \
        if (CBIN_LIKELY(value != NULL)) {                                      \
            *value = swap(*value);                                             \
        }                                                                      \
        return cbin_reader_error(reader)

#    define READ_BE(size, swap) return cbin_read(reader, value, (size) / 8)
#else
#    error "Unknown endianness"
#    define READ_LE(size, swap) return (CBIN_ERR_OK)
#    define READ_BE(size, swap) return (CBIN_ERR_OK)
#endif

#ifdef __LITTLE_ENDIAN__
#    define READ_VALUE(name) return (cbin_read_##name##_le(reader, value))
#elif defined(__BIG_ENDIAN__)
#    define READ_VALUE(name) return (cbin_read_##name##_be(reader, value))
#else
#    error "Unknown endianness"
#    define READ_VALUE(name) return (CBIN_ERR_OK)
#endif

cbin_err_t cbin_read_u8(cbin_reader_t *reader, uint8_t *value) {
    return cbin_read(reader, value, sizeof(uint8_t));
}

cbin_err_t cbin_read_u16(cbin_reader_t *reader, uint16_t *value) {
    READ_VALUE(u16);
}
cbin_err_t cbin_read_u16_le(cbin_reader_t *reader, uint16_t *value) {
    READ_LE(16, bswap16);
}
cbin_err_t cbin_read_u16_be(cbin_reader_t *reader, uint16_t *value) {
    READ_BE(16, bswap16);
}

cbin_err_t cbin_read_u32(cbin_reader_t *reader, uint32_t *value) {
    READ_VALUE(u32);
}
cbin_err_t cbin_read_u32_le(cbin_reader_t *reader, uint32_t *value) {
    READ_LE(32, bswap32);
}
cbin_err_t cbin_read_u32_be(cbin_reader_t *reader, uint32_t *value) {
    READ_BE(32, bswap32);
}
cbin_err_t cbin_read_u64(cbin_reader_t *reader, uint64_t *value) {
    READ_VALUE(u64);
}
cbin_err_t cbin_read_u64_le(cbin_reader_t *reader, uint64_t *value) {
    READ_LE(64, bswap64);
}
cbin_err_t cbin_read_u64_be(cbin_reader_t *reader, uint64_t *value) {
    return READ_BE(64, bswap64);
}
cbin_err_t cbin_read_i8(cbin_reader_t *reader, int8_t *value) {
    return cbin_read(reader, value, sizeof(uint8_t));
}
cbin_err_t cbin_read_i16(cbin_reader_t *reader, int16_t *value) {
    READ_VALUE(i16);
}
cbin_err_t cbin_read_i16_le(cbin_reader_t *reader, int16_t *value) {
    READ_LE(16, bswap16);
}
cbin_err_t cbin_read_i16_be(cbin_reader_t *reader, int16_t *value) {
    READ_BE(16, bswap16);
}
cbin_err_t cbin_read_i32(cbin_reader_t *reader, int32_t *value) {
    READ_VALUE(i32);
}
cbin_err_t cbin_read_i32_le(cbin_reader_t *reader, int32_t *value) {
    READ_LE(32, bswap32);
}
cbin_err_t cbin_read_i32_be(cbin_reader_t *reader, int32_t *value) {
    READ_BE(32, bswap32);
}
cbin_err_t cbin_read_i64(cbin_reader_t *reader, int64_t *value) {
    READ_VALUE(i64);
}
cbin_err_t cbin_read_i64_le(cbin_reader_t *reader, int64_t *value) {
    READ_LE(64, bswap64);
}
cbin_err_t cbin_read_i64_be(cbin_reader_t *reader, int64_t *value) {
    READ_BE(64, bswap64);
}
cbin_err_t cbin_read_f32(cbin_reader_t *reader, float *value) {
    READ_VALUE(f32);
}
cbin_err_t cbin_read_f32_le(cbin_reader_t *reader, float *value) {
    READ_LE(32, bswapf);
}
cbin_err_t cbin_read_f32_be(cbin_reader_t *reader, float *value) {
    READ_BE(32, bswapf);
}
cbin_err_t cbin_read_f64(cbin_reader_t *reader, double *value) {
    READ_VALUE(f64);
}
cbin_err_t cbin_read_f64_le(cbin_reader_t *reader, double *value) {
    READ_LE(64, bswapd);
}
cbin_err_t cbin_read_f64_be(cbin_reader_t *reader, double *value) {
    READ_BE(64, bswapd);
}

cbin_err_t cbin_read_bool(cbin_reader_t *reader, bool *value) {
    uint8_t u;
    if (cbin_read_u8(reader, &u))
        return reader->_error;
    *value = u;
    return CBIN_ERR_OK;
}

cbin_err_t cbin_reader_find(cbin_reader_t *reader, uint8_t byte,
                            size_t *position) {
    for (size_t i = reader->_position; i < reader->_size; i++) {
        if (*((const uint8_t *)(reader->_buffer) + i) == byte) {
            *position = i;
            return CBIN_ERR_OK;
        }
    }
    return CBIN_ERR_FAILED;
}
