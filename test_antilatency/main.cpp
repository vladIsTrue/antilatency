#include <cstdint>
#include <cstddef>
#include <array>
#include <algorithm>

#define percent(percentageValue, number) ((percentageValue / 100.0) * number)

struct ChannelDescription {
    std::size_t pwmDuty;
    std::size_t activePeriodsCount;
};

static constexpr std::size_t N = 255;
static constexpr std::size_t M = 100;

static constexpr std::size_t COUNT_OF_CHANNEL = 16;

using BitstreamT = std::array<std::uint16_t, N * M>;

BitstreamT bitstream;

void generateBitstream(BitstreamT& bitstream, std::array<ChannelDescription, COUNT_OF_CHANNEL> description) {
    std::fill(bitstream.begin(), bitstream.end(), 0);

    for (size_t count = 0; count < COUNT_OF_CHANNEL; ++count) {
        for (size_t i = 0; i < description[count].activePeriodsCount; ++i) {
            for (size_t j = 0; j < percent(description[count].pwmDuty, M); ++j) {
                bitstream[j + i * M] |= (1 << count);
            }
        }
    }
}

int main() {
    generateBitstream(bitstream, {
        ChannelDescription{100, 1},
        ChannelDescription{25, 2},
        ChannelDescription{50, 2},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 3},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0},
        ChannelDescription{100, 0}
        });

    return 0;
}