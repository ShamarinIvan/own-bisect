#!/bin/bash

is_good_commit() {
    python3 -m unittest "$1"
    return $?
}

git_bisect() {
    local repo_path=$1
    local good_commit=$2
    local bad_commit=$3
    local test_command=$4

    cd "$repo_path" || { echo "Directory $repo_path was not found"; exit 1; }

    commits=($(git rev-list --reverse "$good_commit..$bad_commit"))
    low=0
    high=$((${#commits[@]} - 1))
    while [[ $low -le $high ]]; do
        mid=$(( (low + high) / 2 ))
        current_commit=${commits[$mid]}
        git checkout -q "$current_commit"
        if is_good_commit "$test_command"; then
            low=$((mid + 1))
        else
            high=$((mid - 1))
        fi
        
    done

    echo "The first bad commit: ${commits[$low]}"
    git checkout -q "${commits[$low]}"
}
git_bisect "$1" "$2" "$3" "$4"