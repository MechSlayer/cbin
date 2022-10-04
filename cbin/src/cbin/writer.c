//
// Created by Slayer on 04/10/2022.
//

#include "writer.h"
#include <endianness/endianness.h>
#include <string.h>

void cbin_writer_init_fixed(cbin_writer_t *writer, void *buffer, size_t size) {
    writer->_buffer = buffer;
    writer->_capacity = buffer ? size : 0;
    writer->_position = 0;
    writer->_written = 0;
    writer->_owns_buffer = false;
    writer->_error = CBIN_ERR_OK;
}
cbin_err_t cbin_writer_init_dynamic(cbin_writer_t *writer,
                                    size_t initial_capacity) {
    if (initial_capacity > 0) {
        writer->_buffer = CBIN_REALLOC(writer->_buffer, initial_capacity);
        if (!writer->_buffer) {
            return writer->_error = CBIN_ERR_OUT_OF_MEMORY;
        }
    } else {
        writer->_buffer = 0;
    }
    writer->_capacity = initial_capacity;
    writer->_position = 0;
    writer->_written = 0;
    writer->_owns_buffer = true;
    return writer->_error = CBIN_ERR_OK;
}
void cbin_writer_destroy(cbin_writer_t *writer) {
    if (writer->_owns_buffer && writer->_buffer) {
        CBIN_FREE(writer->_buffer);
    }
}

void cbin_writer_reset(cbin_writer_t *writer) {
    writer->_position = 0;
    writer->_written = 0;
    writer->_error = CBIN_ERR_OK;
}
void cbin_writer_discard_error(cbin_writer_t *writer) {
    writer->_error = CBIN_ERR_OK;
}
cbin_err_t cbin_writer_seek(cbin_writer_t *writer, size_t position) {
    if (writer->_error)
        return writer->_error;
    if (position > writer->_written) {
        return writer->_error = CBIN_ERR_OUT_OF_BOUNDS;
    }

    writer->_position = position;
    return CBIN_ERR_OK;
}

cbin_err_t cbin_writer_reserve(cbin_writer_t *writer, size_t count,
                               void **out) {
    if (writer->_error) return writer->_error;
    if (writer->_position + count > writer->_capacity) {
        if (!writer->_owns_buffer)
            return writer->_error = CBIN_ERR_OUT_OF_MEMORY;
        size_t new_capacity = writer->_capacity ? writer->_capacity : 8;
        // Align count to pointer size
        new_capacity += (count + sizeof(void *) - 1) & ~(sizeof(void *) - 1);
        new_capacity *= 2;
        void *new_buffer = CBIN_REALLOC(writer->_buffer, new_capacity);
        if (!new_buffer) {
            return writer->_error = CBIN_ERR_OUT_OF_MEMORY;
        }
        writer->_buffer = new_buffer;
        writer->_capacity = new_capacity;
    }

    if (out) {
        *out = (uint8_t *)writer->_buffer + writer->_position;
    }
    writer->_position += count;
    if (writer->_position > writer->_written) {
        writer->_written = writer->_position;
    }
    return CBIN_ERR_OK;
}

cbin_err_t cbin_writer_fill(cbin_writer_t *writer, uint8_t value,
                            size_t count) {
    void *buffer = NULL;
    if (cbin_writer_reserve(writer, count, &buffer))
        return writer->_error;
    memset(buffer, value, count);
    return CBIN_ERR_OK;
}
const void *cbin_writer_buffer(const cbin_writer_t *writer) {
    return writer->_buffer;
}
size_t cbin_writer_position(const cbin_writer_t *writer) {
    return writer->_position;
}
size_t cbin_writer_written(const cbin_writer_t *writer) {
    return writer->_written;
}
size_t cbin_writer_capacity(const cbin_writer_t *writer) {
    return writer->_capacity;
}
cbin_err_t cbin_writer_error(const cbin_writer_t *writer) {
    return writer->_error;
}
cbin_err_t cbin_write(cbin_writer_t *writer, const void *data, size_t size) {
    void *buffer = NULL;
    if (cbin_writer_reserve(writer, size, &buffer))
        return writer->_error;
    memcpy(buffer, data, size);
    return CBIN_ERR_OK;
}

#ifdef __LITTLE_ENDIAN__
#    define WRITE_LE(size, swap) (cbin_write(writer, &value, (size) / 8))
#    define WRITE_BE(size, swap)                                               \
        (value = swap(value), cbin_write(writer, &value, (size) / 8))
#elif defined(__BIG_ENDIAN__)
#    define WRITE_LE(size, swap)                                               \
        (value = swap(value), cbin_write(writer, &value, (size) / 8))
#    define WRITE_BE(size, swap) (cbin_write(writer, &value, (size) / 8))
#else
#    error "Unknown endianness"
#    define WRITE_LE(size, swap) (cbin_write(writer, &value, (size) / 8))
#    define WRITE_BE(size, swap) (cbin_write(writer, &value, (size) / 8))
#endif

#ifdef __LITTLE_ENDIAN__
#    define WRITE_VALUE(name) (cbin_write_##name##_le(writer, value))
#elif defined(__BIG_ENDIAN__)
#    define WRITE_VALUE(name) (cbin_write_##name##_be(writer, value))
#else
#    error "Unknown endianness"
#    define WRITE_VALUE(name) (cbin_write_##name##_le(writer, value))
#endif

cbin_err_t cbin_write_u8(cbin_writer_t *writer, uint8_t value) {
    return cbin_write(writer, &value, sizeof(value));
}
cbin_err_t cbin_write_i8(cbin_writer_t *writer, int8_t value) {
    return cbin_write(writer, &value, sizeof(value));
}
cbin_err_t cbin_write_u16(cbin_writer_t *writer, uint16_t value) {
    return WRITE_VALUE(u16);
}
cbin_err_t cbin_write_u16_le(cbin_writer_t *writer, uint16_t value) {
    return WRITE_LE(16, bswap16);
}
cbin_err_t cbin_write_u16_be(cbin_writer_t *writer, uint16_t value) {
    return WRITE_BE(16, bswap16);
}
cbin_err_t cbin_write_i16(cbin_writer_t *writer, int16_t value) {
    return WRITE_VALUE(i16);
}
cbin_err_t cbin_write_i16_le(cbin_writer_t *writer, int16_t value) {
    return WRITE_LE(16, bswap16);
}
cbin_err_t cbin_write_i16_be(cbin_writer_t *writer, int16_t value) {
    return WRITE_BE(16, bswap16);
}
cbin_err_t cbin_write_u32(cbin_writer_t *writer, uint32_t value) {
    return WRITE_VALUE(u32);
}
cbin_err_t cbin_write_u32_le(cbin_writer_t *writer, uint32_t value) {
    return WRITE_LE(32, bswap32);
}
cbin_err_t cbin_write_u32_be(cbin_writer_t *writer, uint32_t value) {
    return WRITE_BE(32, bswap32);
}
cbin_err_t cbin_write_i32(cbin_writer_t *writer, int32_t value) {
    return WRITE_VALUE(i32);
}
cbin_err_t cbin_write_i32_le(cbin_writer_t *writer, int32_t value) {
    return WRITE_LE(32, bswap32);
}
cbin_err_t cbin_write_i32_be(cbin_writer_t *writer, int32_t value) {
    return WRITE_BE(32, bswap32);
}
cbin_err_t cbin_write_u64(cbin_writer_t *writer, uint64_t value) {
    return WRITE_VALUE(u64);
}
cbin_err_t cbin_write_u64_le(cbin_writer_t *writer, uint64_t value) {
    return WRITE_LE(64, bswap64);
}
cbin_err_t cbin_write_u64_be(cbin_writer_t *writer, uint64_t value) {
    return WRITE_BE(64, bswap64);
}
cbin_err_t cbin_write_i64(cbin_writer_t *writer, int64_t value) {
    return WRITE_VALUE(i64);
}
cbin_err_t cbin_write_i64_le(cbin_writer_t *writer, int64_t value) {
    return WRITE_LE(64, bswap64);
}
cbin_err_t cbin_write_i64_be(cbin_writer_t *writer, int64_t value) {
    return WRITE_BE(64, bswap64);
}
cbin_err_t cbin_write_f32(cbin_writer_t *writer, float value) {
    return WRITE_VALUE(f32);
}
cbin_err_t cbin_write_f32_le(cbin_writer_t *writer, float value) {
    return WRITE_LE(32, bswapf);
}
cbin_err_t cbin_write_f32_be(cbin_writer_t *writer, float value) {
    return WRITE_BE(32, bswapf);
}
cbin_err_t cbin_write_f64(cbin_writer_t *writer, double value) {
    return WRITE_VALUE(f64);
}
cbin_err_t cbin_write_f64_le(cbin_writer_t *writer, double value) {
    return WRITE_LE(64, bswapd);
}
cbin_err_t cbin_write_f64_be(cbin_writer_t *writer, double value) {
    return WRITE_BE(64, bswapd);
}
cbin_err_t cbin_write_bool(cbin_writer_t *writer, bool value) {
    return cbin_write_u8(writer, value);
}
