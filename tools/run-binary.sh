#!/usr/bin/env bash
set -euo pipefail

build_dir=${1:-"$PWD/build/debug"}
mapfile -d '' -t binaries < <(find "$build_dir/modules" -type f -executable -print0 2>/dev/null)

if ((${#binaries[@]} == 0)); then
  echo "No built module executables found in $build_dir." >&2
  exit 1
fi

PS3='Choose a binary: '
select binary in "${binaries[@]}"; do
  [[ -n $binary ]] && exec "$binary"
  echo 'Invalid selection.' >&2
done
