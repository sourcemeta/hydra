#!/bin/sh

set -o errexit
set -o nounset

brctl delif virbr0 "$1"
ifconfig "$1" down
