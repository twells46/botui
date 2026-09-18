FROM debian:13.6

RUN dpkg --add-architecture arm64 \
    && apt update \
    && apt install -y \
        cmake \
        dpkg-dev \
        fd-find \
        file \
        fish \
        fzf \
        g++-aarch64-linux-gnu \
        gcc-aarch64-linux-gnu \
        git \
        gnupg \
        make \
        qt6-base-dev:arm64 \
        qt6-declarative-dev:arm64 \
        libssl-dev:arm64 \
        ripgrep \
        wget \
        zlib1g-dev:arm64 \
    && rm -rf /var/lib/apt/lists/*

# TODO Don't hardcode
RUN wget 'https://github.com/twells46/libkar/releases/download/v1.0.1/libkar-1.0.1-Linux.deb' 'https://github.com/twells46/pcompiler/releases/download/v1.0.1/pcompiler-1.0.1-Linux.deb' 'https://github.com/twells46/libwallaby/releases/download/v1.2.4/kipr-1.2.4-Linux.deb' \
    && printf 'b925d91433a08cd38d90bb4dfc9cb765e143f45ec7b6c87f177d1b82b16a1ebd libkar-1.0.1-Linux.deb\naee3d1385138a4a2eea339283a226db02c1efb08949e52bb919d92b32db37308 pcompiler-1.0.1-Linux.deb\n29dbfe1425fd84f8d974930f25fcccd64cd858a5ae5f12ecc65974c03bbcc27b kipr-1.2.4-Linux.deb' > pkgs.CHECKSUM \
    && sha256sum -c pkgs.CHECKSUM \
    && apt install ./libkar-1.0.1-Linux.deb ./pcompiler-1.0.1-Linux.deb ./kipr-1.2.4-Linux.deb \
    && rm libkar-1.0.1-Linux.deb pcompiler-1.0.1-Linux.deb kipr-1.2.4-Linux.deb pkgs.CHECKSUM

RUN groupadd --gid 1000 code \
    && useradd --uid 1000 --gid 1000 --create-home --shell /bin/bash code
