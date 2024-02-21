#!/bin/sh

set -o errexit
set -o nounset

# The  command brctl addbr <name> creates a new instance of
# the ethernet bridge. The network interface corresponding to
# the bridge will be called <name>.
# See https://manpages.ubuntu.com/manpages/jammy/man8/brctl.8.html
brctl addbr virbr0

# Enable interface virbr0
ip link set dev virbr0 up

# Add IP address to it
ip addr add "$1/24" dev virbr0
