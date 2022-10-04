//
// Created by Slayer on 04/10/2022.
//

#ifndef CBIN_SRC_CBIN_READER_H
#define CBIN_SRC_CBIN_READER_H

#include "common.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct cbin_reader_s {
    const void *_buffer;
    size_t _position;
    size_t _size;
    cbin_err_t _error;
} cbin_reader_t;

CBIN_HEADER_BEGIN

/// Initializes a reader with a buffer and a size.
/// \param reader The reader to initialize.
/// \param buffer The buffer to read from.
/// \param size The size of the buffer.
void cbin_reader_init(cbin_reader_t *reader, const void *buffer, size_t size);

/// Resets a reader to a clean state.
/// \param reader The reader to reset.
void cbin_reader_reset(cbin_reader_t *reader);

/// Discards the current error state of a reader.
/// \param reader The reader to discard the error state of.
void cbin_reader_discard_error(cbin_reader_t *reader);

/// Skips a number of bytes in the reader.
/// \param reader The reader to skip bytes in.
/// \param count The number of bytes to skip.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_BOUNDS \endcode
cbin_err_t cbin_reader_skip(cbin_reader_t *reader, size_t count);

/// Seeks to a position in the reader.
/// \param reader The reader to seek in.
/// \param position The position to seek to.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_BOUNDS \endcode
cbin_err_t cbin_reader_seek(cbin_reader_t *reader, size_t position);

/// Returns the buffer that the reader is reading from.
/// \param reader The reader to get the buffer from.
/// \return The buffer that the reader is reading from.
const void *cbin_reader_buffer(const cbin_reader_t *reader);

/// Returns the current position of the reader.
/// \param reader The reader to get the position from.
/// \return The current position of the reader.
size_t cbin_reader_position(const cbin_reader_t *reader);

/// Returns the size of the reader.
/// \param reader The reader to get the size from.
/// \return The size of the reader.
size_t cbin_reader_size(const cbin_reader_t *reader);

/// Returns the current error state of the reader.
/// \param reader The reader to get the error state from.
/// \return The current error state of the reader.
cbin_err_t cbin_reader_error(const cbin_reader_t *reader);

/// Returns the number of bytes left to read in the reader.
/// \param reader The reader to get the number of bytes left to read from
/// \return The number of bytes left to read in the reader.
size_t cbin_reader_remaining(const cbin_reader_t *reader);

/// Reads a number of bytes from the reader.
/// \param reader The reader to read from.
/// \param buffer The buffer to read into.
/// \param size The size of the buffer.
/// \return \code CBIN_ERR_OK \endcode
/// \code CBIN_ERR_OUT_OF_BOUNDS \endcode
cbin_err_t cbin_read(cbin_reader_t *reader, void *buffer, size_t size);


cbin_err_t cbin_read_u8(cbin_reader_t *reader, uint8_t *value);

cbin_err_t cbin_read_u16(cbin_reader_t *reader, uint16_t *value);
cbin_err_t cbin_read_u16_le(cbin_reader_t *reader, uint16_t *value);
cbin_err_t cbin_read_u16_be(cbin_reader_t *reader, uint16_t *value);

cbin_err_t cbin_read_u32(cbin_reader_t *reader, uint32_t *value);
cbin_err_t cbin_read_u32_le(cbin_reader_t *reader, uint32_t *value);
cbin_err_t cbin_read_u32_be(cbin_reader_t *reader, uint32_t *value);

cbin_err_t cbin_read_u64(cbin_reader_t *reader, uint64_t *value);
cbin_err_t cbin_read_u64_le(cbin_reader_t *reader, uint64_t *value);
cbin_err_t cbin_read_u64_be(cbin_reader_t *reader, uint64_t *value);

cbin_err_t cbin_read_i8(cbin_reader_t *reader, int8_t *value);

cbin_err_t cbin_read_i16(cbin_reader_t *reader, int16_t *value);
cbin_err_t cbin_read_i16_le(cbin_reader_t *reader, int16_t *value);
cbin_err_t cbin_read_i16_be(cbin_reader_t *reader, int16_t *value);

cbin_err_t cbin_read_i32(cbin_reader_t *reader, int32_t *value);
cbin_err_t cbin_read_i32_le(cbin_reader_t *reader, int32_t *value);
cbin_err_t cbin_read_i32_be(cbin_reader_t *reader, int32_t *value);

cbin_err_t cbin_read_i64(cbin_reader_t *reader, int64_t *value);
cbin_err_t cbin_read_i64_le(cbin_reader_t *reader, int64_t *value);
cbin_err_t cbin_read_i64_be(cbin_reader_t *reader, int64_t *value);

cbin_err_t cbin_read_f32(cbin_reader_t *reader, float *value);
cbin_err_t cbin_read_f32_le(cbin_reader_t *reader, float *value);
cbin_err_t cbin_read_f32_be(cbin_reader_t *reader, float *value);

cbin_err_t cbin_read_f64(cbin_reader_t *reader, double *value);
cbin_err_t cbin_read_f64_le(cbin_reader_t *reader, double *value);
cbin_err_t cbin_read_f64_be(cbin_reader_t *reader, double *value);

cbin_err_t cbin_read_bool(cbin_reader_t *reader, bool *value);

cbin_err_t cbin_reader_find(cbin_reader_t* reader, uint8_t byte, size_t* position);

CBIN_HEADER_END

#endif // CBIN_SRC_CBIN_READER_H
