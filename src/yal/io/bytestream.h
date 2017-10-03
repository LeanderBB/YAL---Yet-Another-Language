#pragma once
#include <yal/yal.h>
#include <string>
namespace yal {
    class ByteStream {
    public:
        enum Mode {
            kModeRead = 1 << 0,
            kModeWrite= 1 << 1,
            kModeReadWrite = kModeRead | kModeWrite
        };

        enum Flags {
            kFlagSeekable = 1 << 8
        };

        virtual ~ByteStream();

        virtual size_t read(void* buffer,
                            const size_t bytes) = 0;

        virtual size_t write(const void* buffer,
                             const size_t bytes) = 0;

        virtual bool seek(const size_t position) = 0;

        virtual size_t getPosition() const = 0;

        virtual size_t getSizeBytes() const = 0;

        virtual void skipLine() = 0;

        virtual std::string readLine() = 0;

        virtual bool isSeekable() const = 0;

    };
}
