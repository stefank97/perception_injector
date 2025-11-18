#!/usr/bin/env bash
set -e

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
WS="${ROOT}/ws"
SRC="${WS}/src"

echo ">>> Workspace root: ${ROOT}"
echo ">>> Klone Repos nach: ${SRC}"

mkdir -p "${SRC}"
cd "${SRC}"

clone_if_missing() {
    local repo_url="$1"
    local dir_name="$2"

    if [ ! -d "${dir_name}/.git" ]; then
        echo "➡️  Klone ${dir_name} ..."
        git clone "${repo_url}" "${dir_name}"
    else
        echo "✔️  ${dir_name} already exists, skipping."
    fi
}

clone_if_missing "https://github.com/stefank97/fake_object_tool.git"   "fake_object_tool"
clone_if_missing "https://github.com/stefank97/fake_transform.git"     "fake_transform"
clone_if_missing "https://github.com/stefank97/fake_object_filter.git" "fake_object_filter"
clone_if_missing "https://github.com/stefank97/ft_panel.git"           "ft_panel"

echo ">>> Finished. Components in ${SRC}:"
ls -1