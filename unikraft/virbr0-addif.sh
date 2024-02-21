#!/bin/sh

set -o errexit
set -o nounset

ifconfig "$1" 0.0.0.0 promisc up
brctl addif virbr0 "$1"
