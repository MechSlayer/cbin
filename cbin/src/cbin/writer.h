//
// Created by Slayer on 04/10/2022.
//

#ifndef CBIN_SRC_CBIN_WRITER_H
#define CBIN_SRC_CBIN_WRITER_H
#include "common.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct cbin_writer_s {
    void *_buffer;
    size_t _capacity;

    size_t _position;
    size_t _written;
    bool _owns_buffer;
    cbin_err_t _error;
} cbin_writer_t;

CBIN_HEADER_BEGIN

/// Initializes a writer with a buffer and a capacity.
/// \param writer The writer to initialize.
/// \param buffer The buffer to write to.
/// \param size The size of the buffer.
void cbin_writer_init_fixed(cbin_writer_t *writer, void *buffer, size_t size);

/// Initializes a resizable writer with a capacity.
/// \param writer The writer to initialize.
/// \param initial_capacity The initial capacity of the writer.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_MEMORY \endcode
cbin_err_t cbin_writer_init_dynamic(cbin_writer_t *writer,
                                    size_t initial_capacity);

/// Destroys a writer, only required if the writer is dynamic.
/// \param writer The writer to destroy.
void cbin_writer_destroy(cbin_writer_t *writer);

/// Resets a writer to a clean state.
/// \param writer The writer to reset.
void cbin_writer_reset(cbin_writer_t *writer);

/// Discards the current error state of a writer.
/// \param writer The writer to discard the error state of.
void cbin_writer_discard_error(cbin_writer_t *writer);

/// Seeks to a position in the writer.
/// \param writer The writer to seek in.
/// \param position The position to seek to.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_BOUNDS \endcode
cbin_err_t cbin_writer_seek(cbin_writer_t *writer, size_t position);

/// Reserves a number of bytes in the writer and advances the position.
/// \param writer The writer to reserve bytes in.
/// \param count The number of bytes to reserve.
/// \param out The pointer to write the reserved bytes to.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_MEMORY \endcode
cbin_err_t cbin_writer_reserve(cbin_writer_t *writer, size_t count, void **out);

/// Writes a single byte to the writer.
/// \param writer The writer to write to.
/// \param value The value to write.
/// \param count The number of times to write the value.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_MEMORY \endcode
cbin_err_t cbin_writer_fill(cbin_writer_t *writer, uint8_t value, size_t count);

/// Returns the current buffer of the writer.
/// \param writer The writer to get the buffer of.
/// \return The current buffer of the writer.
const void *cbin_writer_buffer(const cbin_writer_t *writer);

/// Returns the current position of the writer.
/// \param writer The writer to get the position of.
/// \return The current position of the writer.
size_t cbin_writer_position(const cbin_writer_t *writer);

/// Returns the number of bytes written to the writer.
/// \param writer The writer to get the number of bytes written to.
/// \return The number of bytes written to the writer.
size_t cbin_writer_written(const cbin_writer_t *writer);

/// Returns the current capacity of the writer.
/// \param writer The writer to get the capacity of.
/// \return The current capacity of the writer.
size_t cbin_writer_capacity(const cbin_writer_t *writer);

/// Returns the current error state of the writer.
/// \param writer The writer to get the error state of.
/// \return The current error state of the writer.
cbin_err_t cbin_writer_error(const cbin_writer_t *writer);

/// Writes a number of bytes to the writer.
/// \param writer The writer to write to.
/// \param data The data to write.
/// \param size The size of the data to write.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_MEMORY \endcode
cbin_err_t cbin_write(cbin_writer_t *writer, const void *data, size_t size);


cbin_err_t cbin_write_u8(cbin_writer_t *writer, uint8_t value);
cbin_err_t cbin_write_i8(cbin_writer_t *writer, int8_t value);

cbin_err_t cbin_write_u16(cbin_writer_t *writer, uint16_t value);
cbin_err_t cbin_write_u16_le(cbin_writer_t *writer, uint16_t value);
cbin_err_t cbin_write_u16_be(cbin_writer_t *writer, uint16_t value);

cbin_err_t cbin_write_i16(cbin_writer_t *writer, int16_t value);
cbin_err_t cbin_write_i16_le(cbin_writer_t *writer, int16_t value);
cbin_err_t cbin_write_i16_be(cbin_writer_t *writer, int16_t value);

cbin_err_t cbin_write_u32(cbin_writer_t *writer, uint32_t value);
cbin_err_t cbin_write_u32_le(cbin_writer_t *writer, uint32_t value);
cbin_err_t cbin_write_u32_be(cbin_writer_t *writer, uint32_t value);

cbin_err_t cbin_write_i32(cbin_writer_t *writer, int32_t value);
cbin_err_t cbin_write_i32_le(cbin_writer_t *writer, int32_t value);
cbin_err_t cbin_write_i32_be(cbin_writer_t *writer, int32_t value);

cbin_err_t cbin_write_u64(cbin_writer_t *writer, uint64_t value);
cbin_err_t cbin_write_u64_le(cbin_writer_t *writer, uint64_t value);
cbin_err_t cbin_write_u64_be(cbin_writer_t *writer, uint64_t value);

cbin_err_t cbin_write_i64(cbin_writer_t *writer, int64_t value);
cbin_err_t cbin_write_i64_le(cbin_writer_t *writer, int64_t value);
cbin_err_t cbin_write_i64_be(cbin_writer_t *writer, int64_t value);

cbin_err_t cbin_write_f32(cbin_writer_t *writer, float value);
cbin_err_t cbin_write_f32_le(cbin_writer_t *writer, float value);
cbin_err_t cbin_write_f32_be(cbin_writer_t *writer, float value);

cbin_err_t cbin_write_f64(cbin_writer_t *writer, double value);
cbin_err_t cbin_write_f64_le(cbin_writer_t *writer, double value);
cbin_err_t cbin_write_f64_be(cbin_writer_t *writer, double value);

cbin_err_t cbin_write_bool(cbin_writer_t *writer, bool value);

CBIN_HEADER_END

#endif // CBIN_SRC_CBIN_WRITER_H
