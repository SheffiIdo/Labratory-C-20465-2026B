FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-24.04

# Install specific tools for the OU course
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    gdb \
    valgrind \
    && rm -rf /var/lib/apt/lists/*