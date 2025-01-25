#include <cstdint>
#include <cstddef>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }
    try {
        auto j = json::parse(data, data + size);
    } catch (const json::parse_error&) {
        // Parsing failed, which is expected for invalid inputs
    }
    return 0;
}
