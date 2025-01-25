#include <cstdint>
#include <cstddef>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size == 0) {
        return 0;
    }

    try {
        std::string input(reinterpret_cast<const char*>(data), size);
        
        json j = json::parse(input, nullptr, false);
        json strictJ = json::parse(input);

        std::string serialized = j.dump();
        json parsedAgain = json::parse(serialized);

        if (j.is_object()) {
            for (auto& [key, value] : j.items()) {
                (void)value.dump();
                (void)j[key];
            }
        }

        if (j.is_object()) {
            j["fuzz_test"] = "data";
            j.erase("fuzz_test");
        }

        try {
            int num = j.get<int>();
            (void)num;
        } catch (...) {}

        try {
            std::vector<int> vec = j.get<std::vector<int>>();
            (void)vec;
        } catch (...) {}

        if (j.is_number()) {
            double val = j.get<double>();
            double sum = val + 42.0;
            double prod = val * 3.14;
            (void)sum;
            (void)prod;
        }

        json patch = json::parse(R"([{"op": "add", "path": "/new", "value": "patched"}])", nullptr, false);
        json mergePatch = json::parse(R"({"new_key": "merged_value"})", nullptr, false);
        
        try {
            json patchedJson = j.patch(patch);
            j.merge_patch(mergePatch);
        } catch (...) {}

        try {
            json nonExistent = j.at("non_existent_key");
        } catch (...) {}

        try {
            json invalidIndex = j[1000000];
        } catch (...) {}

    } catch (const json::parse_error&) {
    } catch (const json::exception&) {
    }

    return 0;
}
