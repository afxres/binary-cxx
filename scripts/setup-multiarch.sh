#!/bin/bash

declare -A dpkg_arch_names
dpkg_arch_names["arm64"]="aarch64"
dpkg_arch_names["amd64"]="x86-64"

for i in "$@"; do
    sudo dpkg --add-architecture "$i"
done
sudo apt-get update
sudo apt-get install -y qemu-user
for i in "$@"; do
    dpkg_arch_name="${dpkg_arch_names["$i"]:-"$i"}"
    sudo apt-get install -y "gcc-$dpkg_arch_name-linux-gnu" "g++-$dpkg_arch_name-linux-gnu" "libboost-test-dev:$i"
done
