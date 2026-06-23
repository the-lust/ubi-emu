# Multi-stage Docker build for cross-compiling UUES Windows DLLs on Linux
# Stage 1: install toolchain & build
FROM ubuntu:22.04 AS builder

RUN apt-get update && apt-get install -y \
    cmake \
    build-essential \
    mingw-w64 \
    ninja-build \
    git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . .

RUN mkdir -p Build && \
    cmake -B Build -G "Ninja" \
        -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-mingw.cmake \
        -DCMAKE_BUILD_TYPE=Release && \
    cmake --build Build --config Release

# Stage 2: minimal runtime image (TODO: extract only the DLLs we need)
FROM ubuntu:22.04
COPY --from=builder /workspace/Build/Bin /workspace/Bin
CMD ["bash"]