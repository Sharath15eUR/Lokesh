#!/bin/bash

echo "" >> errors.log 

search_dir() {
    local dir="$1"
    local keyword="$2"
    
    if [[ ! -d "$dir" ]]; then
        echo "$(date)::Error:No directory$dir exists" | tee -a errors.log
        exit 1
    fi
    for file in "$dir"/*; do
        if [[ -d "$file" ]]; then
            search_dir "$file" "$keyword"
        elif [[ -f "$file" ]]; then
            if grep -q "$keyword" "$file" 2>/dev/null; then
                echo "Keyword '$keyword' found in file  $file"
                grep --color=always -n "$keyword" "$file" 2>/dev/null
            fi
        fi
    done
}

disp_help() {
    cat << eof 
Options:
  --help          Display the help menu.
  -d <directory>  Directory to search.
  -k <keyword>    Keyword to search.
  -f <file>       File to search directly.
eof
}

check_args() {
    local keyword="$1"
    local file="$2"
    
    if [[ -n "$file" && ! -f "$file" ]]; then
        echo "$(date)::Error:$file, No such file exists" | tee -a errors.log
        exit 1
    fi
    
    if [[ -z "$keyword" || ! "$keyword" =~ ^[a-zA-Z0-9_]+$ ]]; then
        echo "$(date)::Error:$keyword is invaid keyword, either empty or in appropieate" | tee -a errors.log
        exit 1
    fi
}


if [ "$#" -eq 0 ];then
	echo "$(date)::Error:invalid usage of file analyzer ; refer below for valid usage pattern" | tee -a errors.log
	disp_help
fi

while getopts ":d:k:f:-:" opt; do
    case "$opt" in
        d) directory="$OPTARG" 
            ;;
        k) keyword="$OPTARG" 
            ;;
        f) file="$OPTARG" 
            ;;
        -) case "$OPTARG" in
               help) disp_help; exit 1 
                        ;;
               *) echo "$(date)::Error: Invalid option: --$OPTARG" | tee -a errors.log; exit 1 
                        ;;
           esac 
           ;;
	:) echo  "$(date)::Error: Option -$OPTARG requires an argument" | tee -a errors.log; exit 1 
	   ;;
        ?) echo "$(date)::Error: Invalid option: -$OPTARG" | tee -a errors.log; exit 1 
            ;;
    esac
done

if [[ -z "$keyword" ]]; then
    echo "$(date)::Error:keyword is mandatory to peform search, cannot be null" | tee -a errors.log
    exit 1
fi

check_args "$keyword" "$file"

if [[ -n "$directory" ]]; then
    search_dir "$directory" "$keyword"
elif [[ -n "$file" ]]; then
    echo "keyword $keyword found in file $file"
    grep --color=always -n  "$keyword" "$file"
else
    echo "$(date)::Error:specify either option -d || -f " | tee -a errors.log
    exit 1
fi
