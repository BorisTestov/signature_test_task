FROM ubuntu:20.04
LABEL maintainer="Testov Boris (boris.testov@gmail.com)"

# Set timezone
ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install gtest and boost
RUN apt update && apt install -y \
    googletest libboost-all-dev

# Set up ssh
RUN apt update && apt install -y \
    openssh-server
RUN ( \
    echo 'LogLevel DEBUG2'; \
    echo 'PermitRootLogin yes'; \
    echo 'PasswordAuthentication yes'; \
    echo 'Subsystem sftp /usr/lib/openssh/sftp-server'; \
  ) > /etc/ssh/sshd_config_clion \
  && mkdir /run/sshd

# Add user
# Credentials: user / password
RUN useradd -m user && yes password | passwd user && \
apt update && apt install -y sudo && \
echo "%user ALL=(ALL) ALL" >> /etc/sudoers && \
usermod -s /bin/bash user

# Install build tools
RUN apt update && apt install -y \
    rsync \
    cmake  \
    make  \
    build-essential  \
    gdb

# Copy gtest libs
RUN apt update && apt install -y  \
    libgtest-dev
WORKDIR  /usr/src/gtest/build
RUN cmake .. && make && \
cp /usr/src/googletest/googletest/build/lib/libgtest* /usr/lib/

CMD ["/usr/sbin/sshd", "-D", "-e", "-f", "/etc/ssh/sshd_config"]
