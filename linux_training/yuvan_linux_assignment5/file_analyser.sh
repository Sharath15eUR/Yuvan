#!/bin/bash

LOG_FILE="errors.log"

# Problem1
search_directory() {
    local target_dir=$1
    local search_term=$2
    for item in "$target_dir"/*; do
        if [[ -d "$item" ]]; then
            search_directory "$item" "$search_term"
        elif [[ -f "$item" ]]; then
            if grep -q "$search_term" "$item"; then
                echo "Match found: '$search_term' inside $item"
            fi
        fi
    done
}

#problem3
show_help() {
    cat << EOF
Usage: $0 [OPTIONS]

Options:
  -d <directory>   Search for a keyword recursively in a specified directory
  -k <keyword>     Define the keyword to be searched
  -f <file>        Search for a keyword in a specific file
  --help           Display this help message

EOF
}

# Problem2
log_error() {
    echo "$1" | tee -a "$LOG_FILE"
}

# Problem5
validate_inputs() {
    local target_file=$1
    local search_term=$2
    if [[ ! -e "$target_file" ]]; then
        log_error "Error: Specified file '$target_file' does not exist."
        exit 1
    fi
    if [[ -z "$search_term" ]]; then
        log_error "Error: Search keyword cannot be empty."
        exit 1
    fi
}

#Problem6
while getopts ":d:k:f:-:" option; do
    case $option in
        d) target_directory=$OPTARG ;;
        k) search_keyword=$OPTARG ;;
        f) target_file=$OPTARG ;;
        -) case $OPTARG in
               help) show_help; exit 0 ;;
               *) log_error "Error: Unknown option --$OPTARG"; exit 1 ;;
           esac ;;
        \?) log_error "Error: Invalid option -$OPTARG"; exit 1 ;;
        :) log_error "Error: Option -$OPTARG requires an argument."; exit 1 ;;
    esac
done

#Main
if [[ -n "$target_directory" && -n "$search_keyword" ]]; then
    if [[ ! -d "$target_directory" ]]; then
        log_error "Error: Directory '$target_directory' does not exist."
        exit 1
    fi
    echo "Initiating search in '$target_directory' for term '$search_keyword'..."
    search_directory "$target_directory" "$search_keyword"
elif [[ -n "$target_file" && -n "$search_keyword" ]]; then
    validate_inputs "$target_file" "$search_keyword"
    echo "Looking for '$search_keyword' in file '$target_file'..."
    grep --color=always "$search_keyword" "$target_file" || echo "No matches for '$search_keyword' in '$target_file'."
else
    log_error "Error: Incorrect usage. Refer to --help for guidance."
    exit 1
fi

# Problem4
final_status=$?
echo "Process completed with status code: $final_status"
exit $final_status