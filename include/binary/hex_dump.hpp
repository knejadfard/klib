#ifndef HEX_DUMP_HPP
#define HEX_DUMP_HPP

#include <string>
#include <algorithm>
#include <vector>
#include <cmath>

namespace klib {
namespace binary {

// columns per row to print
constexpr size_t COLUMNS = 16;
constexpr size_t COLUMN_WIDTH = 5;
constexpr unsigned char HEX_TABLE[] = "0123456789abcdef";

// row caption:
//     5 space characters to account for each row's byte offset
//     1 space character to account for the space after byte offset chars
//     For each column, consider 3 characters: 2 for hex chars and 1 space
constexpr unsigned char ROW_CAPTION[] = {
     ' ', ' ', ' ', ' ', ' ', '0', ' ', ' ', ' ', ' ',\
     '1', ' ', ' ', ' ', ' ', '2', ' ', ' ', ' ', ' ',\
     '3', ' ', ' ', ' ', ' ', '4', ' ', ' ', ' ', ' ',\
     '5', ' ', ' ', ' ', ' ', '6', ' ', ' ', ' ', ' ',\
     '7', ' ', ' ', ' ', ' ', '8', ' ', ' ', ' ', ' ',\
     '9', ' ', ' ', ' ', ' ', 'A', ' ', ' ', ' ', ' ',\
     'B', ' ', ' ', ' ', ' ', 'C', ' ', ' ', ' ', ' ',\
     'D', ' ', ' ', ' ', ' ', 'E', ' ', ' ', ' ', ' ',\
     'F', ' ', ' ', ' ', ' ', '\n'};
constexpr size_t ROW_SIZE = sizeof(ROW_CAPTION);

size_t size_t_to_hex(unsigned char *, size_t);
void pad_with_spaces(unsigned char *, size_t);

/*****************************************************
 * Generate and return the hex dump of the given data
 *****************************************************/
std::vector<unsigned char> hex_dump(unsigned char* data, size_t length)
{
    // there is always 1 row for caption
    // each full row can fit 16 bytes
    size_t num_rows = 1 + length / COLUMNS;
    // there may be 1 partial row needed
    if (length % COLUMNS > 0) {
        ++num_rows;
    }

    size_t result_size = num_rows * ROW_SIZE;
    std::vector<unsigned char> result;
    result.resize(result_size);

    std::fill(result.begin(), result.end(), 0);

    // copy the row caption
    std::copy(ROW_CAPTION, ROW_CAPTION + ROW_SIZE, result.begin());
    size_t result_write_offset = ROW_SIZE;

    size_t data_offset = 0;
    size_t bytes_written = 0;
    unsigned char buffer[COLUMN_WIDTH + 1];
    for (size_t row_counter = 0; row_counter < num_rows; ++row_counter) {
        if (data_offset == length) {
            break;
        }

        size_t row_label = row_counter * 16;
        bytes_written = sprintf(buffer, "%x", row_label);
        pad_with_spaces(buffer, bytes_written);
        std::copy(buffer, buffer + COLUMN_WIDTH, result.begin() + result_write_offset);
        result_write_offset += COLUMN_WIDTH;

        for (size_t column_counter = 0; column_counter < COLUMNS; ++column_counter) {
            if (data_offset == length) {
                break;
            }

            bytes_written = sprintf(buffer, "%02x", data[data_offset]);
            pad_with_spaces(buffer, bytes_written);

            std::copy(buffer, buffer + COLUMN_WIDTH, result.begin() + result_write_offset);
            result_write_offset += COLUMN_WIDTH;
            ++data_offset;
        }
        result.at(result_write_offset++) = '\n';
    }

    return result;
}

/************************************************************
 * Given a buffer array, pad bytes with 0x20 (space) after
 * the number of bytes given. That is, preserve a certain
 * number of bytes in the buffer and replace anything after
 * it with 0x20 until reaching the maximum column length.
 ************************************************************/
void pad_with_spaces(unsigned char *buffer, size_t bytes)
{
    size_t index = bytes;
    while (index < COLUMN_WIDTH) {
        buffer[index] = ' ';
        ++index;
    }
}

} // binary namespace
} // klib namespace

#endif
